/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "temple13": 9,
    "temple21": 10,
    "temple18": 10,
    "temple14": 10,
    "temple09": 10,
    "temple05": 10,
    "temple02": 10,
    "temple01": 11,
    "temple03": 11,
    "temple06": 11,
    "temple10": 11,
    "temple15": 11,
    "temple19": 11,
    "temple22": 11,
    "temple24": 11,
    "temple23": 12,
    "temple20": 12,
    "temple16": 12,
    "temple11": 12,
    "temple07": 12,
    "temple04": 12,
    "temple12": 13,
    "temple17": 13,
]);
mapping yGrid = ([
    "temple13": 6,
    "temple21": 8,
    "temple18": 7,
    "temple14": 6,
    "temple09": 5,
    "temple05": 4,
    "temple02": 3,
    "temple01": 2,
    "temple03": 3,
    "temple06": 4,
    "temple10": 5,
    "temple15": 6,
    "temple19": 7,
    "temple22": 8,
    "temple24": 9,
    "temple23": 8,
    "temple20": 7,
    "temple16": 6,
    "temple11": 5,
    "temple07": 4,
    "temple04": 3,
    "temple12": 5,
    "temple17": 6,
]);
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    add_item(({"walls"}), "The black stone looks almost charred.\n");
    add_item(
      ({"skull", "skulls"}), "Forbidding skulls adorn much of area.\n");
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(TEMPLE_DIR));
    return ({xGrid[room], yGrid[room], -3});
}
