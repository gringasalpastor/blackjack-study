project (BlackjackStudy)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/NewSessionAssistant)
include_directories(../submodule/lskat/src/fromlibkdegames/)

add_subdirectory(tests)
add_executable(HardHands HardHands.cpp)
target_link_libraries(HardHands Qt5::Core)

# Generate HardHandsData.h from HardHands binary
ADD_CUSTOM_COMMAND( OUTPUT HardHandData.cpp COMMAND HardHands DEPENDS HardHands)
ADD_CUSTOM_TARGET(HardHandData ALL DEPENDS HardHandData.cpp)

set(BlackjackStudy_SRCS
  Main.cpp
  MainWindow.cpp
  HandDisplay.cpp
  HandValidator.cpp
  GameConfigurationGenerater.cpp
  SideBar.cpp
  SessionSettings.cpp
  ../submodule/lskat/src/fromlibkdegames/cardcache.cpp
  ../submodule/lskat/src/fromlibkdegames/carddeckinfo.cpp
  ../submodule/lskat/src/fromlibkdegames/kcarddialog.cpp)

set(NewSessionAssistant_SRCS 
  NewSessionAssistant/NewSessionAssistant.cpp
  NewSessionAssistant/PercentModel.cpp
  NewSessionAssistant/PercentDelegate.cpp
  NewSessionAssistant/GameRulesSelector.cpp
  NewSessionAssistant/LasVegasStripSelection.cpp
  NewSessionAssistant/LasVegasSelection.cpp
  NewSessionAssistant/RenoSelection.cpp
  NewSessionAssistant/AlanticCitySelection.cpp
  NewSessionAssistant/ManualSelection.cpp
  NewSessionAssistant/GameRuleSelection.cpp
  NewSessionAssistant/TwoTabledPage.cpp
  NewSessionAssistant/PercentTableView.cpp
  NewSessionAssistant/OverallPage.cpp
  NewSessionAssistant/AbstractPage.cpp
  NewSessionAssistant/PieView.cpp)

ecm_qt_declare_logging_category(BlackjackStudy_SRCS HEADER lskat_debug.h
                                IDENTIFIER LSKAT_LOG CATEGORY_NAME org.kde.lskat
                                DEFAULT_SEVERITY Debug)

add_executable(BlackjackStudy ${BlackjackStudy_SRCS} ${NewSessionAssistant_SRCS} )
target_link_libraries(BlackjackStudy 
  Qt5::Core
  Qt5::Widgets
  Qt5::Gui
  Qt5::Svg
  Qt5::WebKitWidgets
  KF5::GuiAddons
  KF5::ItemModels
  KF5::CoreAddons
  KF5::I18n
  KF5::XmlGui
  KF5::ConfigWidgets
  KF5::WidgetsAddons
  KF5::KIOCore
  KF5KDEGames)

install(TARGETS BlackjackStudy DESTINATION ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES BlackjackStudyui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/BlackjackStudy)
