#include "../default.h"
inherit CVAN_ROOM;

#define EGUARD	(NPC + "tceguard")

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You've reached the exact center of this hallway. Looking "+
      "towards the north and south you can faintly see where this "+
      "passageway reached an end and turns into another hallway. This hallway, "+
      "like most others in the building is sparsely furnished. The only "+
      "noteworthy item in this passage is the intricately carved sign "+
      "placed above the platinum door in the west.\n");

    add_item(({ "hallway", "passageway", "passage" }), "The floor is covered "+
      "in beautiful and expensive-looking marble tiles. They are such a "+
      "brilliant white in color that you are nearly blinded from looking at "+
      "them.\n");

    add_item(({ "sign" }), "There are several words on it? Perhaps you "+
      "should read them?\n");

    add_exit(CVAN + "company/s74", "north");
    add_exit(CVAN + "company/s78", "south");

    clone_object(CVAN + "door/isdoor")->move(TO);

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(EGUARD);
	ob1->move_living("M", TO);
    }

    if (!ob2)
    {
	ob2 = clone_object(EGUARD);
	ob2->move_living("M", TO);
	ob1->team_join(ob2);
    }
}

string
sign()
{
    return "\n"+
    "                      &&&&&&&&&&&&&&&&&&&&&&&&&&\n"+
    "                      &{}{}{}{}{}{}{}{}{}{}{}{}&\n"+
    "                      &{}         THE        {}&\n"+
    "                      &{}        INNER       {}&\n"+
    "                      &{}       SANCTUM      {}&\n"+
    "                      &{}{}{}{}{}{}{}{}{}{}{}{}&\n"+
    "                      &&&&&&&&&&&&&&&&&&&&&&&&&&\n";
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
