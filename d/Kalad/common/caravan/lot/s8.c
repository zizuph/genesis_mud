#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Lion Cage in Caravan Lot");
    set_long("You enter the cage to the smell of fresh blood and the musty "+
      "odor of some animal. The floor is covered with still wet blood and "+
      "several gnawed bones. The iron bars of the cage door look quite sturdy.\n");

    add_item(({ "floor" }),
      "It is just hard-packed earth. Chewed-out bones and fresh blood "+
      "completely cover it.\n");

    add_item(({ "blood" }),
      "It is sticky, half dried and blankets the floor. You can't be sure, "+
      "but believe it to be human blood.\n");

    add_item(({ "bones" }),
      "The decayed remains of a human being!\n");

    add_item(({ "iron bars", "bars" }),
      "They cover the eastern side of the cage, and look to be very strong. "+
      "The bars themselves don't look too close to one another, maybe you could "+
      "squeeze out through them?\n");

    add_item(({ "cage door", "door" }), "It is locked and shut.\n");

    set_noshow_obvious(1);

    add_cmd_item(({ "east", "out" }), "squeeze", "@@squeeze");
    add_cmd_item("out", "squeeze", "@@squeeze");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "hmlion");
	ob1->move_living("M",TO);
    }
}

int
block()
{
    write("The cage doors have been locked!\n");
    return 1;
}

string
squeeze()
{
    write("You suck in your breath and squeeze through the bars!\n");
    set_dircmd("out");
    TP->move_living("out between the iron bars of the cage", CVAN + "lot/s9");
    return "You let out your breath, you've escaped the cage!\n";
}

void
init()
{
    ::init();
    write("As you enter the cage, the door locks shut!\n");
}
