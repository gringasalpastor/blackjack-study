set(TEST_SOURCES 
	PieViewTest.cpp
  ../NewSessionAssistant/PercentModel.cpp
  ../NewSessionAssistant/PieView.cpp)

add_executable(PieViewTest ${TEST_SOURCES})
add_test(NAME PieViewTest COMMAND PieViewTest)
target_link_libraries(PieViewTest Qt5::Test Qt5::Core Qt5::Widgets Qt5::Gui)
