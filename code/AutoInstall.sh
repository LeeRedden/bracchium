sudo apt-get install libusb-1.0-0-dev

# install the library components
cd libphidget-2.1.8.20140319
./configure 
make 
sudo make install 

# about half way through testing out the code here
#    http://www.phidgets.com/docs/OS_-_Linux


# change directories and run an example
cd ../phidget21-c-examples-2.1.8.20140319
gcc HelloWorld.c -o HelloWorld -lphidget21
gcc AdvancedServo-simple.c -o AdvancedServo -lphidget21

