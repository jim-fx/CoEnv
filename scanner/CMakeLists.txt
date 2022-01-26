cmake_minimum_required(VERSION 3.10)
PROJECT(scanner)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED core imgproc)

add_executable (scanner src/main.cpp include/helpers.h include/webcam.h include/MFRC522.h include/MFRC522.cpp)  
target_link_libraries (scanner ${raspicam_CV_LIBS} libbcm2835.a libliquidcrystali2c.a libi2c.a)
target_link_libraries(scanner sioclient)
target_link_libraries(scanner pthread )
target_include_directories(scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/local/include)
set_property(TARGET scanner PROPERTY CXX_STANDARD 11)
set_property(TARGET scanner PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable (lcd_test src/lcd.cpp)
target_link_libraries(lcd_test libliquidcrystali2c.a libi2c.a)

add_executable (rfid_test src/rfid.cpp include/MFRC522.h include/MFRC522.cpp)
target_link_libraries(rfid_test libbcm2835.a)
target_include_directories(rfid_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable (rfidled_test src/rfidled.cpp include/MFRC522.h include/MFRC522.cpp)
target_link_libraries(rfidled_test libbcm2835.a libliquidcrystali2c.a libi2c.a)
target_include_directories(rfidled_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
