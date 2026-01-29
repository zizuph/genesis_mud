#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "nflats01": 1,
    "nflats09": 2,
    "nflats02": 2,
    "nflats10": 3,
    "nflats03": 3,
    "nflats11": 4,
    "nflats04": 4,
    "nflats16": 5,
    "nflats12": 5,
    "nflats05": 5,
    "nflats20": 6,
    "nflats17": 6,
    "nflats13": 6,
    "nflats06": 6,
    "nflats24": 7,
    "nflats21": 7,
    "nflats18": 7,
    "nflats14": 7,
    "nflats07": 7,
    "nflats22": 8,
    "nflats19": 8,
    "nflats15": 8,
    "nflats08": 8,
    "nflats23": 9,
]);
mapping yGrid = ([
    "nflats01": 4,
    "nflats09": 5,
    "nflats02": 4,
    "nflats10": 5,
    "nflats03": 4,
    "nflats11": 5,
    "nflats04": 4,
    "nflats16": 6,
    "nflats12": 5,
    "nflats05": 4,
    "nflats20": 7,
    "nflats17": 6,
    "nflats13": 5,
    "nflats06": 4,
    "nflats24": 8,
    "nflats21": 7,
    "nflats18": 6,
    "nflats14": 5,
    "nflats07": 4,
    "nflats22": 7,
    "nflats19": 6,
    "nflats15": 5,
    "nflats08": 4,
    "nflats23": 7,
]);

void
create_room()
{
    ::create_room();
    set_short("Amid bleak and dusty flats");
    set_long(
      "You are within a deserted plain, north of a dark forest and south of " +
      "tall mountains. There is a strange silence here, even as the wind " +
      "kicks up dust around you.\n");

    add_item(({"mountains", "tall mountains"}),
      "Mighty mountains rise high up into the sky to the north.\n");
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
    string room = extract(MASTER_OB(TO), strlen(NFLATS_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
