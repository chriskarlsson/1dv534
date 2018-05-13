# CMakeList.txt : CMake project for 1dv534_3_2_framework, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (My1dv53432framework 
                "1dv534_3_2_framework.cpp"
                "Blackjack/BlackjackGame.cpp"
                "Blackjack/BlackjackPlayer.cpp"
                "Crap/CrapGame.cpp"
                "Crap/CrapGameWrapper.cpp"
                "Crap/CrapPlayer.cpp"
                "UserInput.cpp")

set(LIB_DIR ../../../libs)

include_directories(./)
include_directories(${LIB_DIR}/include/)
include_directories(./Blackjack)
include_directories(./Crap)