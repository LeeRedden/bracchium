# http://ai.stanford.edu/~mquigley/doku.php?id=inkscapekerfcorrection

# on ubuntu 12.04   1-26-2015
sudo apt-get install build-essential autoconf automake intltool libglib2.0-dev libpng12-dev libgc-dev libfreetype6-dev liblcms1-dev libgtkmm-2.4-dev libxslt1-dev libboost-dev libpopt-dev libgsl0-dev libaspell-dev libpoppler-dev libpoppler-glib-dev libgnome-vfsmm-2.6-dev libssl-dev libwpg-dev bzr
# no longer available libmagick++9-dev
sudo apt-get install autopoint



# make inkscape. 35 minutes
mkdir ~/inkscape-kerf
cd ~/inkscape-kerf
bzr checkout lp:inkscape
cd inkscape
./autogen.sh
./configure --prefix=$HOME/inkscape-kerf
make



# examine the patch, there is a version cached in this folder too
wget http://ai.stanford.edu/~mquigley/static/linked_offset_from_preferences.diff 
patch -p0 < linked_offset_from_preferences.diff
make install


