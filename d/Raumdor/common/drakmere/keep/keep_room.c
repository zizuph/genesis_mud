#include "defs.h"
inherit STD_ROOM;
mapping xGrid = ([
    "keep12": 61,
    "keep09": 61,
    "keep03": 61,
    "keep06": 61,
    "keep22": 61,
    "keep27": 61,
    "keep21": 61,
    "keep16": 61,
    "keep15": 61,
    "keep25": 61,
    "keep11": 62,
    "keep08": 62,
    "keep02": 62,
    "keep05": 62,
    "keep14": 62,
    "keep17": 62,
    "keep20": 62,
    "keep23": 62,
    "keep10": 63,
    "keep07": 63,
    "keep01": 63,
    "keep04": 63,
    "keep13": 63,
    "keep26": 63,
    "keep18": 63,
    "keep24": 63,
    "keep28": 63,
]);

mapping yGrid = ([
    "keep12": 0,
    "keep09": -1,
    "keep03": -2,
    "keep06": -3,
    "keep22": -3,
    "keep27": -3,
    "keep21": -2,
    "keep16": -1,
    "keep15": 0,
    "keep25": 0,
    "keep11": 0,
    "keep08": -1,
    "keep02": -2,
    "keep05": -3,
    "keep14": 0,
    "keep17": -1,
    "keep20": -2,
    "keep23": -3,
    "keep10": 0,
    "keep07": -1,
    "keep01": -2,
    "keep04": -3,
    "keep13": 0,
    "keep26": 0,
    "keep18": -1,
    "keep24": -3,
    "keep28": -3,
]);

mapping zGrid = ([
    "keep12": 0,
    "keep09": 0,
    "keep03": 0,
    "keep06": 0,
    "keep22": 1,
    "keep27": 2,
    "keep21": 1,
    "keep16": 1,
    "keep15": 1,
    "keep25": 2,
    "keep11": 0,
    "keep08": 0,
    "keep02": 0,
    "keep05": 0,
    "keep14": 1,
    "keep17": 1,
    "keep20": 1,
    "keep23": 1,
    "keep10": 0,
    "keep07": 0,
    "keep01": 0,
    "keep04": 0,
    "keep13": 1,
    "keep26": 2,
    "keep18": 1,
    "keep24": 1,
    "keep28": 2,
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
    string room = extract(MASTER_OB(TO), strlen(KEEP_DIR));
    return ({xGrid[room], yGrid[room], zGrid[room]});
}
