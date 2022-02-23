echo "Run ab_opencv_test"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/sd/TestData/lib/
echo "LD_LIBRARY_PATH:"$LD_LIBRARY_PATH
cd /mnt/sd/TestData/Sample/OpenCVSample
./ab_opencv_test &
cd ~
