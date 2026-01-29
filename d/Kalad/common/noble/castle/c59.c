// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object ob;

void reset_room();

void
create_noble_room()
{
    set_short("A bedroom");
    INSIDE;
    set_long("You stand inside a cozy bedroom. The walls are decorated "+
    "with many paintings. There is a large, canopy bed in the center "+
    "of the room. The ground is covered by a thin, red carpet. The "+
    "east wall has a large mirror. There is a dresser and a chest "+
    "here as well. On the south wall, there is a table and two chairs.\n");
    add_item("paintings","They are of mostly wilderness scense. Some "+
    ", however, show pictures of a far away place, covered with a "+
    "substance known as snow...\n");
    add_item("bed","The bed has white satin sheets, and big pillows, as "+
    "well as a see-through canopy.\n");
    add_item("carpet","The carpet is thin, but soft.\n");
    add_item("mirror","@@mirror@@");
    add_item("dresser","A large, oak dresser. It have a few bottles "+
    "of perfume on it, and many clothes in the drawers.\n");
    add_item("perfume","Only the rich and expensive kind.\n");
    add_item("clothes","They are women's clothes.\n");
    add_item("chest","The chest is made of black wood. It is locked "+
    "tight.\n");
    add_item("table","The table is made of white pine. There are stuffed "+
    "animals on it.\n");
    add_item("chairs","The chairs are padded with soft down cusions.\n");
    add_item("animals","There are teddy bears, and little stuffed cats.\n");

    add_exit(NOBLE + "castle/c60", "east", 0, 0);

    reset_room();
}

void
reset_room()
{
    ob = clone_npcs(ob, NOBLE + "npc/maid");
}

string
mirror()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
        return "You see the wall behind you.\n";
    return "You see yourself looking back.\n";
}
