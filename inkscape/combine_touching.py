#!/usr/bin/env python 
# -*- coding: utf-8 -*-
'''
Copyright (C) 2009 Sandro KnauÃŸ, bugs@sandroknauss.de

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
'''
import inkex, simplepath,copy

class Net:
    '''
    this class creats a net of points that are bonded via lines or subpathes
    for input it used the method createNet(commands); commands are svg commands parsed with simplepath
    to give out a new svg command line use createD to symolize that the output of this function can directly put into the d-argument in the svg:path tag 
    there are two different modes like the net will be created:
    bTogether=True: all subpathes will be kept together and only the start and endpoint of that subpath will be reconized
    bTogether=False: all subpathes will be destroyed into single lines 
    '''
    def __init__(self,bTogether=False):
        self.bTogether=bTogether

    #internal functions
    def __updateStartpoint(self,point):
        '''
        This function takes care about, that points will be thrown out that are connected to other points
        -> closed figures will have no startingpoint
        '''
        if point in self.startpoints:
            self.startpoints.remove(point)

    def __addPoint(self,pfrom,pto,via,args=None):
        '''
        adds an bond to the net between the two points pfrom and pto
        "pfrom","pto" are points which are tuples of type (x,y)
        "via" is the method of bond, can be L,C or path (view createD - method variable)
            L - is a single line
            C - a bezier curve
            path - a complex path; the list of bonds is nested in "args" 
        "args" - args for the "via" command
        '''
        for point in (pfrom,pto):
            if not self.points.has_key(point):
                self.points[point]=[]
        self.points[pfrom].append({"point":pto,"via":via,"args":args})
        self.points[pto].append(self.rbond(pfrom,via,args))


    def createNet(self,path):
        '''
        main function for creating the net
        "path" is a command list which is parsed through sipmlepath
        mainly it only goes through all commands and execute the corresbonding function in the methods variable
        M - Move To - will execute self.moveto
        L - Line To - will execute self.lineto
        C - Curve To - will execute self.curve
        Z - Close figure - will execute self.close
        '''
        methods={"M":self.moveto,"L":self.lineto,"C":self.curve,"Z":self.close,"EOL":self.endsubpath}
        self.lastpoint=()           #will be the actual point where the subpath is 
        self.startpoint=()          #starting point of the actual subpath
        self.startpoints=[]         #list of the startingpoints
        self.points={}              #THE NET
        self.bSaveLast=False        #should the last Point be saved to have one startingpoint
        path.append(['EOL',[0,0]])  #end of subpath should be handeld as last command

        for point in path:
            method=point[0]
            methods[method](point[1])

    #there are the methods that will be executed from createNet from special commands - see createNet:methods bellow for the binding
    def endsubpath(self,point=None):
        '''
        handles the end of subpathes
        "point" - is not used 
        '''
        if self.bTogether:                  #if were are handle subpath -> save old subpath
            self.savepath() 
        if self.bSaveLast:                  #save endpoint
            self.startpoints.append(self.lastpoint)

        self.startpoint=()
        self.lastpoint=()
        self.args=[]

    def moveto(self,point):
        '''
        The moveto command this is the first command of an subpath, now we know that the old path has ended
        '''
        point=tuple(point)
        
        self.endsubpath()

        if point in self.startpoints:       #ok the new startpoint point has also be used as startpoint in another subpath 
                                            #->delete the startpoint and add the endpoint of the subpath 
            self.startpoints.remove(point)
            self.bSaveLast=True
        else:
            self.bSaveLast=False            #normal startpoint
            if not self.points.has_key(point) or len(self.points[point])%2==0: #the startpoint was actually an endpoint
                self.startpoints.append(point)
        
        self.startpoint=point
        self.lastpoint=point

   
    def lineto(self,point):
        '''
        will be executed if an 'L' command is be executed and adds an bond from the previous point to the actual point
        for bTogether=True it only creates the bond in self.args 
        '''
        point=tuple(point)
        if self.bTogether:
            self.args.append({'via':'L','point':point,'args':None})
        else:
            self.__addPoint(self.lastpoint,point,"L")
            self.__updateStartpoint(point)
        self.lastpoint=point
    
    def close(self,point):
        '''
        is executed for "Z" command (closing the figure to the startpoint) 
        '''
        self.lineto(self.startpoint)

    def curve(self,points):
        '''
        is executed for 'C' command
        for futher infomation see lineto 
        '''
        point=tuple(points[4:6])
        args=[tuple(points[0:2]),tuple(points[2:4])]
        if self.bTogether:
            self.args.append({'via':'C','point':point,'args':args})
        else:
            self.__addPoint(self.lastpoint,point,"C",args)
            self.__updateStartpoint(point)
        self.lastpoint=point

    def rbond(self,pfrom,cmd,args):
        '''
        creates an reverse version of an point
        '''
        def path(args):
            rargs=[]                                    #ok change the direction of the commands and arguments
                                                        #example path 0 A1 B2 C3 D4  (letters are commds, numbers points)
                                                        #will become 4 D3 C2 B1 A0 
            args=copy.deepcopy(args[::-1])              #change the direction of commands; D4 C3 B2 A1
            args.append({'point':pfrom})                #endpoint is now the startpoint; D4 C3 B2 A1  0
            lastarg=args[0]                             #get last arg; D4
            for arg in args[1:]:
                rargs.append(self.rbond(arg['point'],lastarg['via'],lastarg['args']))                   
                lastarg=arg
            return rargs
        
        methods={
                "L":lambda args:None,
                "C":lambda args: args[::-1],
                "path":path 
                }


        return {'point':pfrom,'via':cmd,'args':methods[cmd](args)}

    def savepath(self):
        '''
        saves the subpath in one bond 
        '''
        if self.startpoint:
            self.__addPoint(self.startpoint,self.lastpoint,"path",self.args)
            self.__updateStartpoint(self.lastpoint)     #handle like a normal bond




    def createD(self):
        '''
        creates the d command to use directly in svg:path
        '''
        ret=[]
        for startpoint in self.startpoints:         #use all startpoints for creating subpathes
            rets=self.follow_path(startpoint)       
            if not rets == "":                      #was there an subpath, than add it
                ret.append(rets)

        #closed figures
        while True:
            for point in self.points:           
                if not self.points[point] == []:    #we have already points that aren't in any subpath
                    ret.append(self.follow_path(point))
                    break
            else:
                return " ".join(ret)                #we are ready: no more free points 


    def follow_path(self,startpoint):
        '''
        follow a path to it's end via the net self.points
        "startpoint" is the point to start - is a tuple (x,y)
        '''
        #method to handle diffenent command:
        #L will give back "L x,y" 
        #C will give back "C x1,y1 x2,y2 x,y" x1-y2 are in args
        #path is an nested command -> it uses L and C
        methods={"L":lambda element:"L %s" %(",".join([str(i) for i in element["point"]])),
                "C":lambda element:"C %s %s" %
                (" ".join([",".join([str(i) for i in j]) for j in element["args"]]),
                    ",".join([str(i) for i in element["point"]])),
                "path":lambda element:" ".join([methods[i["via"]](i) for i in element["args"]])}


        ret=[]                                              #return list (is joind via " ")
        pfrom=startpoint                        
        
        while len(self.points[pfrom])>0:                    #we are at the end of the subpath

            element=self.points[pfrom].pop(0)               #to next point
            pto=element['point']

            ret.append(methods[element["via"]](element))    #print next command
            if  element["point"] == startpoint:             #close figure if it is the startingpoint
                ret.append("Z")

                             #delete coresbonding element
            self.points[pto].remove(self.rbond(pfrom,element['via'],element['args']))

            pfrom=pto                                       #update the position
        
        if len(ret)>0:
            ret.insert(0,"M %s"%(",".join([str(i) for i in startpoint]))) #moveto command, only there is a subpath

        return " ".join(ret)


class Combine(inkex.Effect):
    def __init__(self):
        inkex.Effect.__init__(self)
        self.OptionParser.add_option("--together",
                        action="store", type="inkbool", 
                        dest="together", default=True,
                        help="Keep subpaths together")    

    def effect(self):
        for id in self.options.ids:                 
            node = self.selected[id]
            if node.tag ==inkex.addNS('path','svg'):                #for all selected pathes
                net=Net(self.options.together)                      
                net.createNet(simplepath.parsePath(node.get('d')))  #create the net
                #create the new node
                attribs = {'style':node.get('style'),'d':net.createD()}
                new = inkex.etree.SubElement(self.current_layer,inkex.addNS('path','svg'), attribs)

e = Combine()
e.affect()

def same_unorderd(points1,points2):
    '''
    a function that only test weather all elements are in both lists
    '''
    try:
        for point in points1:
            args1=points1[point]
            args2=points2[point]
            for arg in args1:
                if not arg in args2:
                    return False
    except:
        return False
    else:
        return True


def test():
    #test simplepath - only for knowing, that the input is ok
    tmp=simplepath.parsePath("M 439,300 L 439,655 C 41,65 37,75 36,65 M 36,65 L 36,30 Z")
    if not tmp == [['M', [439, 300]],
 ['L', [439, 655]],
 ['C', [41,65,37,75,36,65]],
 ['M', [36,65]],
 ['L', [36, 30]],
 ['Z', []]]:
        raise "Test-simplepath"

    #easy tests with "unessisary" moe-to commands
    net1=Net()
    net2=Net()
    net1.createNet([['M', [439, 300]], ['L', [439, 655]],['M', [439, 655]], ['L', [360, 655]], ['M', [360, 655]], ['L', [360, 300]]])
    net2.createNet([['M', [439, 300]], ['L', [439, 655]],['L', [360, 655]],['L', [360, 300]]])
    
    if not same_unorderd(net1.points,{(439, 300):[{"point":(439, 655),"via":"L","args":None}],
        (439, 655):[{"point":(439, 300),"via":"L","args":None},{"point":(360, 655),"via":"L","args":None}],
        (360, 655):[{"point":(439, 655),"via":"L","args":None},{"point":(360, 300),"via":"L","args":None}],
        (360, 300):[{"point":(360, 655),"via":"L","args":None}]}):
            raise "point-net"

    if not net1.startpoints == [(439, 300)]:
        raise "startpoints"

    if not same_unorderd(net1.points, net2.points) or not net1.startpoints == net2.startpoints:
        raise "Continue not same"
    
    if not net1.createD() == "M 439,300 L 439,655 L 360,655 L 360,300":
        raise "create D problem"

    if not net1.points=={(439, 300):[],
        (439, 655):[],
        (360, 655):[],
        (360, 300):[]}:
        raise "not all points used"

    if not net2.createD() == "M 439,300 L 439,655 L 360,655 L 360,300":
        raise "create D2 problem"

    #two pathes to one point should get one path
    net1.createNet([['M', [1,1]], ['L', [2,2]],['M', [2,2]], ['L', [3,3]], ['M', [3,3]], ['L', [4,4]]])
    net2.createNet([['M', [1,1]], ['L', [2,2]],['M', [4,4]], ['L', [3,3]], ['L', [2,2]]])

    if not net2.startpoints==[(1,1),(4,4)]:
        raise "diffrent pathes-startpoint"

    if not same_unorderd(net1.points,net2.points):
        raise "different pathes"

    if not net1.createD() == net2.createD():
        raise "create D problem - diffent pathes"

    if not net1.points=={(1,1):[],(2,2):[],(3,3):[],(4,4):[]}:
        raise "not all points used"


    #what about closed pathes are they handled right? -> should give out an closed path
    net1.createNet([['M', [1,1]], ['L', [2,2]],['L', [3,3]],['L',[1,1]]])
    net2.createNet([['M', [1,1]], ['L', [2,2]],['L', [3,3]],['Z', []]])

    if not net1.startpoints == []:
        raise "close figure"

    if not same_unorderd(net1.points, net2.points) or not net1.startpoints == net2.startpoints:
        raise "Z-Parameter"

    if not net1.createD() == "M 3,3 L 2,2 L 1,1 L 3,3 Z":
        raise "create D problem - Z"

    if not net1.points=={(1,1):[],(2,2):[],(3,3):[]}:
        raise "Z-not all points used"

    #is the C command handled right
    net1.createNet([['M', [1,2]],['C',[3,4,5,6,7,8]],['M', [7,8]],['L', [9,10]]])
    
    if not same_unorderd(net1.points,{(1,2):[{"point":(7,8),"via":"C","args":[(3,4),(5,6)]}],
        (7,8):[{"point":(1,2),"via":"C","args":[(5,6),(3,4)]},{"point":(9,10),"via":"L","args":None}],
        (9,10):[{"point":(7,8),"via":"L","args":None}]}):
        raise "C-parameter"

    if not net1.createD() == "M 1,2 C 3,4 5,6 7,8 L 9,10":
        raise "createD problem - C"

    if not net1.points=={(1,2):[],(7,8):[],(9,10):[]}:
        raise "C-not all points used"

    #test the keeping subpath command
    net1=Net(True)
    net1.createNet([['M', [1,2]],['C',[3,4,5,6,7,8]],['L', [9,10]],['M', [1,2]],['L', [-1,-2]],['L', [-3,-4]]])
    #okok: a littlebit nested ;) but it's easy to understand: he only put all comands of a subpath into "args"(starts with an M command end ens with end of the command or with a new M command)
    if not same_unorderd(net1.points,{(1,2):[{"point":(9,10),"via":"path","args":
            [{'via':'C', 'point':(7,8),'args':[(3,4),(5,6)]},{'via':'L', 'point':(9,10),'args':None}]},
        {"point":(-3,-4),"via":"path","args":
            [{'via':'L', 'point':(-1,-2),'args':None},{'via':'L', 'point':(-3,-4),'args':None}]}],
        (9,10):[{"point":(1,2),"via":"path","args":
            [{'via':'L', 'point':(7,8),'args':None},{'via':'C', 'point':(1,2),'args':[(5,6),(3,4)]}]}],
        (-3,-4):[{"point":(1,2),"via":"path","args":
            [{'via':'L', 'point':(-1,-2),'args':None},{'via':'L', 'point':(1,2),'args':None}]}]}):
        raise "keep subpaths"

    if not (net1.startpoints==[(-3,-4)] or net1.startpoint==[(9,10)]):
            raise "middle point is not starting point"
    
    if not net1.createD()=="M -3,-4 L -1,-2 L 1,2 C 3,4 5,6 7,8 L 9,10":
        raise "keeping subpathes D problem"

