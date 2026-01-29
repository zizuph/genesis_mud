#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "house01": 63,
    "house02": 64,
    "house03": 65,
    "house04": 65,
    "house06": 67,
    "house09": 68,
    "house17": 68,
    "house10": 69,
    "house16": 69,
    "house11": 70,
    "house12": 70,
    "house13": 70,
    "house14": 70,
    "house15": 70,
]);
mapping yGrid = ([
    "house01": 6,
    "house02": 6,
    "house03": 6,
    "house04": 5,
    "house06": 6,
    "house09": 6,
    "house17": -1,
    "house10": 6,
    "house16": -1,
    "house11": 6,
    "house12": 5,
    "house13": 4,
    "house14": 1,
    "house15": -1,
]);

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(DRAKMERE_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
