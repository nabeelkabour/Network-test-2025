cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(server "src/server/main.cpp"  "src/shared/olcPixelGameEngine.cpp" "src/server/Networking.cpp" "src/server/GameServer.cpp" "src/shared/GameMechanics/Player.cpp" "src/shared/Resources.cpp" "src/client/PieceActor.cpp" "src/client/Blood.cpp" "src/client/GunShotEffect.cpp" "src/shared/GameMechanics/Zombie.cpp" "src/server/ZombieSpawner.cpp" "src/server/ZombieServer.cpp" "src/shared/NetworkCommon.cpp" "src/shared/GameMechanics/Object.cpp" "src/server/PlayerServer.cpp")
add_executable(client "src/client/main.cpp"  "src/shared/olcPixelGameEngine.cpp" "src/client/GameClient.cpp" "src/client/Client.cpp" "src/shared/GameMechanics/Player.cpp" "src/shared/Resources.cpp" "src/client/PieceActor.cpp" "src/client/Blood.cpp" "src/client/GunShotEffect.cpp" "src/shared/GameMechanics/Zombie.cpp" "src/client/ZombieClient.cpp" "src/shared/NetworkCommon.cpp" "src/shared/GameMechanics/Object.cpp" "src/client/Drawable.cpp" "src/client/ObjectClient.cpp" "src/client/PlayerClient.cpp")
target_compile_features(server PRIVATE cxx_std_17)
target_link_libraries(server PRIVATE SFML::Graphics SFML::Network)
target_link_libraries(client PRIVATE SFML::Graphics SFML::Network)
