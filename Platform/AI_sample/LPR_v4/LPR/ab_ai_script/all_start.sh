# Run default sample
read -p "Sample (a) Basic (b) Optimization (c) OpenCV (d) Http client post:" target_sample
case "$target_sample" in
  a|A) echo "Run ab_ai_test"
     /mnt/sd/TestData/Sample/BasicSample/ab_ai_test &
     ;;
  b|B) echo "Run ab_optimized_ai_test"
     export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/sd/TestData/lib/libjpeg/
     /mnt/sd/TestData/Sample/OptimizedSample/ab_optimized_ai_test &
     ;;
  c|C) echo "Run ab_opencv_test"
     export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/sd/TestData/lib/
     echo "LD_LIBRARY_PATH:"$LD_LIBRARY_PATH
	 cd /mnt/sd/TestData/Sample/OpenCVSample
     ./ab_opencv_test &
	 cd ~
     ;;
  d|D) echo "Run curl test"
     export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/sd/TestData/lib/libcurl
     echo "LD_LIBRARY_PATH:"$LD_LIBRARY_PATH
	 cd /mnt/sd/TestData/Sample/CurlSample
	 ./ab_curl_test &
	 cd ~
     ;;	 
  *) echo "Invalid input"
esac
