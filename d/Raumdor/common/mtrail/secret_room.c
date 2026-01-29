/* SARR */
#include "defs.h"
inherit STD_ROOM;
mapping xGrid = ([
    "secret1": 33,
    "secret2": 34,
    "secret3": 35,
    "true_room": 36,
    "death_room": 36,
    "secret4": 37,
    "secret5": 38,
    "secret6": 39,
]);

mapping yGrid = ([
    "secret1": 11,
    "secret2": 11,
    "secret3": 11,
    "true_room": 12,
    "death_room": 12,
    "secret4": 11,
    "secret5": 11,
    "secret6": 11,
]);

mapping zGrid = ([
    "secret1": -1,
    "secret2": -1,
    "secret3": -1,
    "true_room": -1,
    "death_room": -2,
    "secret4": -1,
    "secret5": -1,
    "secret6": -1,
]);

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Inside a secret passage");
    
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(MTRAIL_DIR));
    return ({xGrid[room], yGrid[room], zGrid[room]});
}
