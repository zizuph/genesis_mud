#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;

#define GUARD	(NPC + "tcguard")

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Barracks");
    set_long("You enter a guard barracks.\n"+
      "This spacious room looks to be the quarters of the Trading Company "+
      "guardsmen. Looking around the room you note several tables and chairs "+
      "as well as a few posters pinned on the wall. The room continues to "+
      "the north.\n");

    add_item(({ "tables" }),
      "A few tables lie around the room. The guards probably use them to "+
      "eat their food off of or to play some card games.\n");

    add_item(({ "chairs" }),
      "Small wooden seats, standing on spindly legs.\n");

    add_item(({ "posters" }),
      "Most of the posters are old and faded, with little writing still "+
      "legible. You manage to read a few and figure out these are wanted "+
      "ads of people that have somehow wronged the Company.\n");

    add_exit(CVAN + "company/s27", "north");

    clone_object(CVAN + "door/bdoor1")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1 || !ob2)
    {
	ob1 = clone_object(GUARD);
	ob1->move_living("M", TO);
	ob2 = clone_object(GUARD);
	ob2->move_living("M", TO);
	ob1->team_join(ob2);
    }
}
