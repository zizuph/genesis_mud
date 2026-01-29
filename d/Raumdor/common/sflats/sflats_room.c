#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "sflats01": 2,
    "sflats02": 3,
    "sflats03": 4,
    "sflats07": 4,
    "sflats04": 5,
    "sflats08": 5,
    "sflats11": 5,
    "sflats05": 6,
    "sflats09": 6,
    "sflats12": 6,
    "sflats06": 7,
    "sflats10": 7,
]);
mapping yGrid = ([
    "sflats01": -4,
    "sflats02": -4,
    "sflats03": -4,
    "sflats07": -5,
    "sflats04": -4,
    "sflats08": -5,
    "sflats11": -6,
    "sflats05": -4,
    "sflats09": -5,
    "sflats12": -6,
    "sflats06": -4,
    "sflats10": -5,
]);
void
create_room()
{
    ::create_room();
    set_short("Amid bleak and dusty flats");
    set_long(
      "You are within a deserted plain, south of a dark forest and north of " +
      "tall mountains. There is a strange silence here, even as the wind " +
      "kicks up dust around you.\n");

    add_item(({"mountains", "tall mountains"}),
      "Mighty mountains rise high up into the sky to the south.\n");
    add_item(({"forest"}),
      "It is dark and creepy. You can feel eyes within staring at you.\n");
    add_item(({"ground", "flats"}), "It is dusty and very flat.\n");
    add_item(({"dust"}),
      "The ground is covered with it and the wind tosses it around.\n");

    add_room_tell(({
      "Dust swirls around your feet.\n",
      "You think you hear some moaning coming from somewhere nearby.\n",
      "You feel eyes at your back.\n",
    }));
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(SFLATS_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
