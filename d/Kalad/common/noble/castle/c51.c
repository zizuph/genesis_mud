// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a small bedroom in the High-Lord's Castle");
    INSIDE;
    set_long("You are now within a small bedroom. The oak-paneled "+
    "walls are modestly decorated with paintings. There is a "+
    "round bed in the center, covered with many pillows. A dresser "+
    "stands in one corner, while a wardrobe is in another. The floor "+
    "is covered with a thick blue rug. A table and a few chairs are "+
    "set up against another wall.\n");

    add_item("walls","The walls are smooth and polished.\n");
    add_item("paintings","The paintings are of cute forest animals.\n");
    add_item("bed","The round bed is covered with soft pillows and down "+
    "filled blankets.\n");
    add_item("dresser","The dresser contains many clothes in it.\n");
    add_item("clothes","The latest fasions of Kabal.\n");
    add_item("wardrobe","The wardrobe is empty, save for one coat.\n");
    add_item("coat","It is a fur coat made out of black panther skin.\n");
    add_item("rug","The rug is soft, but made out of strange blue fur.\n");
    add_item("table","An oak table. A pen lays on top of it.\n");
    add_item("chairs","Oak chairs with a cusioned seats.\n");
    add_item("pen","An ink pen for writing.\n");

    add_exit(NOBLE + "castle/c52", "east", 0, 0);
}


