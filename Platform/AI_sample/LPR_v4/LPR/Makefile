.PHONY: all clean prepare
default: all

APP_AB_BASIC_AI_TEST     := LPR
#APP_AB_OPTIMIZED_AI_TEST := ab_optimized_ai_test
#APP_AB_STREAMING_TEST    := ab_streaming_test
#APP_AB_CGI_AI_TEST       := ai_cgi_app
#APP_AB_OPENCV_TEST       := ab_opencv_test
#APP_AB_CURL_TEST         := ab_curl_test

OUTPUT_DIR     := bin
SAMPLE_BIN_DIR := Data/Sample
USE_LATEST_OPENVINO := true
INCLUDE_DIR :=  \
	-I./include \
	-I./include/libusb-1.0 \
	-I./include/inference_engine \
	-I./include/inference_engine/common/vpu \
	-I./include/inference_engine/src/transformations/ngraph_ops \
	-I./include/inference_engine/src/transformations/transformations \
	-I./include/libjpeg \
	-I./include/opencv \
	-I./include/opencv2 \
	-I./include/fcgi2-2.4.2 \
	-I./src/CgiSample/qdecoder \
	-I./include/curl \
	-I./src/sort-tracker \
	-I./src/AbilityInit \
	-I./src/EventHandle \
	-I./src/LicensePlateDetect \
	-I./src/LicensePlateRecognize


#--------- ENVIRONMENT SETTING --------------------
INCLUDES	:= $(INCLUDE_DIR)
WARNING		:= -Wall -Wundef -Wsign-compare -Wno-missing-braces
COMPILE_OPTS	:= $(INCLUDES) -I. -fPIC -ffunction-sections -fdata-sections -DABILITY_CUSTOMIZED

BASIC_FLAGS     := -std=c++14 -lstdc++ -lpthread -lm
AI_IF_FLAGS     := -labipc -lssl -lcrypto -lwlssut -labprocipc -labos -labhost -labcv -lusb-1.0 -labdev
ifeq ($(USE_LATEST_OPENVINO), true)
AB_IE_FLAGS  	:= -linference_engine -lmyriadPlugin -lngraph -linference_engine_preproc -linference_engine_legacy -linference_engine_transformations -linference_engine_lp_transformations
else
AB_IE_FLAGS     := -linference_engine -lmyriadPlugin
endif
OPENCV_FLAGS    := -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_videoio -lopencv_video -lopencv_imgcodecs
JPEG_FLAGS      := -ljpeg -lturbojpeg
STREAMING_FLAGS := -labstreamgetapi -labipc -lssl -lcrypto -lwlssut -labprocipc -labos
CGI_FLAGS       := -lfcgi
CURL_FLAGS      := -lssl -lcrypto -lwlssut -lcurl

CPPFLAGS	:= 
CFLAGS		:= $(PLATFORM_CFLAGS) $(PRJCFG_CFLAGS)
C_FLAGS		:= $(COMPILE_OPTS) $(CPPFLAGS) $(CFLAGS) $(WARNING)
LD_FLAGS	:= -L./libs -L./libs/inference_engine -L./libs/libjpeg -L./libs/opencv -L./libs/fcgi2-2.4.2 -L./libs/libcurl
LD_FLAGS	+= $(BASIC_FLAGS)

$(info  ================ AI Framework Env Info ====================)
$(info  >> INCLUDES: $(INCLUDES))
$(info  >> WARNING: $(WARNING))
$(info  >> COMPILE_OPTS: $(COMPILE_OPTS))
$(info  >> CPPFLAGS: $(CPPFLAGS))
$(info  >> PLATFORM_CFLAGS: $(PLATFORM_CFLAGS))
$(info  >> PRJCFG_CFLAGS: $(PRJCFG_CFLAGS))
$(info  >> CFLAGS: $(CFLAGS))
$(info  >> C_FLAGS: $(C_FLAGS))
$(info  >> LD_FLAGS: $(LD_FLAGS))
$(info  >> AI_IF_FLAGS: $(AI_IF_FLAGS))
$(info  >> AB_IE_FLAGS: $(AB_IE_FLAGS))
$(info  >> OPENCV_FLAGS: $(OPENCV_FLAGS))
$(info  >> JPEG_FLAGS: $(JPEG_FLAGS))
$(info  ===========================================================)

#--------- END OF ENVIRONMENT SETTING -------------
DEP_LIBRARIES :=

#--------- Definitions --------------------
CP := cp -avf
RM := rm -rvf

copy = if [ ! -z $(1) ]; then $(CP) $(1) $(2); fi

#--------- Compiling --------------------
SRC_PATH := src
OBJ_PATH := obj

BASIC_AITEST_SRC_FILE := \
	$(SRC_PATH)/main.cpp \
	$(SRC_PATH)/AbilityInit/ability_init.cpp \
	$(SRC_PATH)/CameraHostApiSample/ab_camera_host_api_sample.cpp \
	$(SRC_PATH)/CameraCvSample/ab_camera_cv_sample.cpp \
	$(SRC_PATH)/LicesenPlateRecognize/cnn.cpp \
	$(SRC_PATH)/LicesenPlateRecognize/text_detection.cpp \
	$(SRC_PATH)/LicesenPlateRecognize/text_recognition.cpp \
	$(SRC_PATH)/LicesenPlateRecognize/LPR_process.cpp \
	$(SRC_PATH)/EventHandle/event_handle.cpp \
	$(SRC_PATH)/LicesenPlateRecognize/LPD_process.cpp \
	$(SRC_PATH)/sort-tracker/Hungarian.cpp \
	$(SRC_PATH)/sort-tracker/KalmanTracker.cpp \
	$(SRC_PATH)/sort-tracker/ObjectTracker.cpp \
	$(SRC_PATH)/sort-tracker/TrackerManager.cpp 
	
BASIC_AITEST_OBJ_FILE := $(BASIC_AITEST_SRC_FILE:.c=.o)
BASIC_AITEST_BIN_FILE := $(OUTPUT_DIR)/LPR/$(APP_AB_BASIC_AI_TEST)


# Normal compile
all: clean $(APP_AB_BASIC_AI_TEST) $(APP_AB_OPTIMIZED_AI_TEST) $(APP_AB_STREAMING_TEST) $(APP_AB_CGI_AI_TEST) $(APP_AB_OPENCV_TEST) $(APP_AB_CURL_TEST) update

$(APP_AB_BASIC_AI_TEST): $(BASIC_AITEST_SRC_FILE)
	@echo -e "\e[1;35m>>>>>>>>>>>>> "$(APP_AB_BASIC_AI_TEST)" Procedure: compiling >>>>>>>>>>>>> \e[0m"
	mkdir -p "${OUTPUT_DIR}/LPR/"
	${CC} ${C_FLAGS} ${LD_FLAGS} ${AI_IF_FLAGS} ${AB_IE_FLAGS} -o ${BASIC_AITEST_BIN_FILE} ${BASIC_AITEST_SRC_FILE} ${OPENCV_FLAGS}
	@echo -e "\e[1;35m<<<<<<<<<<<<< "$(APP_AB_BASIC_AI_TEST)" make all done <<<<<<<<<<<<<\e[0m" 

	
clean:
	@echo -e "\e[1;35m>>>>>>>>>>>>>  AI Framework Samples make clean >>>>>>>>>>>>> \e[0m"
	$(RM) ./${OUTPUT_DIR}
	$(RM) ./${SAMPLE_BIN_DIR}

update:
	@echo -e "\e[1;35m>>>>>>>>>>>>>  AI Framework Samples update >>>>>>>>>>>>> \e[0m"
	${CP} -R ./$(OUTPUT_DIR) ./$(SAMPLE_BIN_DIR)
	
prepare:
	@echo -e "\e[1;35m>>>>>>>>>>>>> AI Framework libs prepare >>>>>>>>>>>>> \e[0m"
	$(RM) -Rf ./include/libusb-1.0
	$(RM) -Rf ./include/inference_engine
	$(RM) -Rf ./include/fcgi2-2.4.2
	${CP} -R $(LIBRARY_DIR)/output/include/libusb-1.0 ./include/libusb-1.0
	${CP} -R $(LIBRARY_DIR)/output/include/inference_engine ./include/inference_engine
	#${CP} -R $(LIBRARY_DIR)/output/include/inference_engine/common/vpu ./include/inference_engine/common/vpu
	#${CP} -R $(LIBRARY_DIR)/output/include/inference_engine/src/transformations ./include/inference_engine/src/transformations
	${CP} -R $(LIBRARY_DIR)/output/include/fcgi2-2.4.2 ./include/fcgi2-2.4.2	
	${CP} $(LIBRARY_DIR)/output/include/ab_host_api.h ./include/ab_host_api.h
	${CP} $(LIBRARY_DIR)/output/include/ab_host_types.h ./include/ab_host_types.h
	${CP} $(LIBRARY_DIR)/output/include/ab_host_event_types.h ./include/ab_host_event_types.h
	${CP} $(LIBRARY_DIR)/output/include/ab_cv_api.h ./include/ab_cv_api.h
	${CP} $(LIBRARY_DIR)/output/include/ab_cv_types.h ./include/ab_cv_types.h
	${CP} $(LIBRARY_DIR)/output/include/ab_os_api.h ./include/ab_os_api.h
	${CP} $(LIBRARY_DIR)/output/include/ab_os_types.h ./include/ab_os_types.h
	${CP} $(LIBRARY_DIR)/output/include/libabos_version.h ./include/libabos_version.h
	${CP} $(LIBRARY_DIR)/output/include/ab_stream_get_api.h ./include/ab_stream_get_api.h

	#libs
	${CP} $(LIBRARY_DIR)/output/lib/libabstreamgetapi.so.1.0.0 ./libs/libabstreamgetapi.so
	$(RM) -Rf ./libs/inference_engine
	${CP} -R $(LIBRARY_DIR)/openvino/bin/ia32/Release/lib ./libs/inference_engine
	${CP} $(LIBRARY_DIR)/output/lib/libabhost.so ./libs/libabhost.so
	${CP} --remove-destination $(LIBRARY_DIR)/output/lib/libabipc.so.0.2.2 ./libs/libabipc.so
	${CP} --remove-destination $(LIBRARY_DIR)/output/lib/libabos.so.0.3.2 ./libs/libabos.so
	${CP} $(LIBRARY_DIR)/output/lib/libabcv.so ./libs/libabcv.so
	${CP} $(LIBRARY_DIR)/output/lib/libusb-1.0.so.0.3.0 ./libs/libusb-1.0.so
	${CP} $(LIBRARY_DIR)/output/lib/libwlssut.so.1.0.0 ./libs/libwlssut.so

	${CP} $(LIBRARY_DIR)/output/lib/libabprocipc.so.1.0.0 ./libs/libabprocipc.so
	${CP} $(LIBRARY_DIR)/output/lib/libabdev.so.0.2.2 ./libs/libabdev.so
	
	$(RM) -Rf ./libs/fcgi2-2.4.2
	mkdir ./libs/fcgi2-2.4.2
	${CP} $(LIBRARY_DIR)/output/lib/libfcgi.so.0.0.0 ./libs/fcgi2-2.4.2/libfcgi.so
	${CP} $(LIBRARY_DIR)/output/lib/libfcgi++.so.0.0.0 ./libs/fcgi2-2.4.2/libfcgi++.so
