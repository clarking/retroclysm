

cmake_minimum_required(VERSION 3.0)

project(retroclysm)

set(SRC
        src/bionics.cpp
        src/bodypart.cpp
        src/crafting.cpp
        src/event.cpp
        src/faction.cpp
        src/field.cpp
        src/game.cpp
        src/help.cpp
        src/item.cpp
        src/itypedef.cpp
        src/iuse.cpp
        src/keypress.cpp
        src/line.cpp
        src/main.cpp
        src/map.cpp
        src/mapgen.cpp
        src/mapitemsdef.cpp
        src/monattack.cpp
        src/mondeath.cpp
        src/mongroupdef.cpp
        src/monitemsdef.cpp
        src/monmove.cpp
        src/monster.cpp
        src/mtypedef.cpp
        src/newcharacter.cpp
        src/npc.cpp
        src/npcmove.cpp
        src/npctalk.cpp
        src/output.cpp
        src/overmap.cpp
        src/player.cpp
        src/rng.cpp
        src/settlement.cpp
        src/setvector.cpp
        src/skill.cpp
        src/trapdef.cpp
        src/trapfunc.cpp
        src/wish.cpp)

add_executable(retroclysm ${SRC})
target_include_directories(retroclysm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(retroclysm ncurses )
