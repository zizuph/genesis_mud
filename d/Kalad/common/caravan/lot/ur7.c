#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

object ob1;
object ob2;
object ob3;
object ob4;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Entrance to an underground lair");
    set_long("An entrance room to an underground lair.\n"+
      "This room is remarkably clean of the filth that was all too common "+
      "in the passages to the southwest. Here the passage is made of solid, "+
      "dry stone and is lit by torches placed along the side walls. A dark "+
      "passage leads southwest, while a lit passage leads eastward.\n");

    add_item(({ "passage" }), "The entire area is constructed out of dry "+
      "stone.\n");

    add_item(({ "stone" }), "Its hard and dry, just like regular stone.\n");

    add_item(({ "walls" }),
      "The walls, along with the rest of this passageway are built of solid "+
      "granite blocks, held together by mortared stone.\n");

    add_item(({ "torches" }),
      "Standard torches, the kind you would find in your general store. "+
      "Several have been placed along the walls to provide light.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur6", "southwest");
    add_exit(CVAN + "lot/ur9", "east");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "lknight1");
	ob1->arm_me();
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "lknight1");
	ob2->arm_me();
	ob2->move_living("M",TO);
    }

    if(!ob3)
    {
	ob3 = clone_object(NPC + "lknight1");
	ob3->arm_me();
	ob3->move_living("M",TO);
    }

    if(!ob4)
    {
	ob4 = clone_object(NPC + "lknight1");
	ob4->arm_me();
	ob4->move_living("M",TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
	ob1->team_join(ob4);
	tell_room(TO, "Several guardian knights of Thanar arrive to take their "+
	  "guard posts.\n");
    }
}

int
query_move()
{
    object *ob;
    int pres,i;

    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;

    for (i = 0; i < sizeof(ob); i++)
    {
	if (ob[i]->query_name() == "Knight")
	{
	    pres = 1;
	}
    }

    if (pres == 1)
    {
	write("The guardian knight of Thanar prevents you "
    +"from going east.\n");
	say("The guardian knight of Thanar prevents " + QTNAME(TP) + 
    " from going east.\n");
    }
    return pres;
}
