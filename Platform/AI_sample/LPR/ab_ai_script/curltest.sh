# Curl test
echo "Run curl test"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/sd/TestData/lib/libcurl
echo "LD_LIBRARY_PATH:"$LD_LIBRARY_PATH
cd /mnt/sd/TestData/Sample/CurlSample
./ab_curl_test &
cd ~

