#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;
object ob3;
object ob4;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Cage");
    set_long("You enter the cage to the smell of dried urine and "+
      "undisposed fecal matter. Straw litters the floor, which is covered "+
      "with dried blood stains, among other things.\n");

    add_item(({ "straw" }),
      "From the color and texture of the straw, it appears to have been here "+
      "for weeks, perhaps months.\n");

    add_item(({ "floor" }),
      "The floor is nothing but packed-down dirt, covered here and there by "+
      "straw and dried blood.\n");

    add_item(({ "dried blood", "blood", "stains" }),
      "There are patches of it here and there, scattered all over the cage's "+
      "floor.\n");

    add_item(({ "other things" }),
      "You notice that the center of the cage's surface seems to have less "+
      "filth on it.\n");

    add_item(({ "center" }),
      "There seems to be a trap door here, covered by dirt and filth. Perhaps "+
      "you could go down here...\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "slave/s4", "out");
    add_exit(CVAN + "slave/ugroom", "down");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "slave");
	ob1->move_living("M", this_object());
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "slave");
	ob2->move_living("M", this_object());
    }

    if(!ob3)
    {
	ob3 = clone_object(NPC + "slave");
	ob3->move_living("M", this_object());
    }

    if(!ob4)
    {
	ob4 = clone_object(NPC + "bhslave");
	ob4->move_living("M", this_object());
    }
}
