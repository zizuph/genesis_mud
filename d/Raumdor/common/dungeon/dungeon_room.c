#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "dungeon05": 47,
    "dungeon06": 48,
    "dungeon01": 48,
    "dungeon11": 48,
    "dungeon07": 49,
    "dungeon02": 49,
    "dungeon12": 49,
    "dungeon08": 50,
    "dungeon03": 50,
    "dungeon13": 50,
    "dungeon09": 51,
    "dungeon04": 51,
    "dungeon14": 51,
    "dungeon10": 52,
]);
mapping yGrid = ([
    "dungeon05": -1,
    "dungeon06": -1,
    "dungeon01": -2,
    "dungeon11": 0,
    "dungeon07": -1,
    "dungeon02": -2,
    "dungeon12": 0,
    "dungeon08": -1,
    "dungeon03": -2,
    "dungeon13": 0,
    "dungeon09": -1,
    "dungeon04": -2,
    "dungeon14": 0,
    "dungeon10": -1,
]);

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    add_item(({"ceiling"}), "It drips water.\n");
    add_prop(ROOM_I_LIGHT, 0);
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(DUNGEON_DIR));
    return ({xGrid[room], yGrid[room], -2});
}
