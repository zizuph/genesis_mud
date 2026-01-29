#include "defs.h"
inherit STD_ROOM;

mapping yGrid = ([
    "crypt1": -1,
    "crypt2": -2,
    "crypt3": -3,
    "crypt4": -4,
]);

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("In a secret lair");
    add_prop(ROOM_I_LIGHT,0);
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(FOREST_DIR));
    return ({12, yGrid[room], 0});
}
