#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

#define KG	(NPC + "kguard_t")

object ob1, ob2;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Tower");
    set_long("You've entered the ground floor of the guard tower here in "+
      "the Caravan district. Looking around the rather spacious room you see "+
      "a small wooden table with several chairs surrounding it. In the "+
      "center of the room you see a spiral staircase leading up.\n");

    add_item(({ "table" }),
      "It's a five foot wide round table with small spindly legs supporting "+
      "the top. There are some cards scattered on the top.\n");

    add_item(({ "cards" }),
      "They're your usual playing cards. The cards look a bit dirty.\n");

    add_item(({ "chairs", "chair" }),
      "These are what the guards sit on.\n");

    add_item(({ "staircase" }),
      "A steel staircase that leads up to the second floor of the tower.\n");

    add_exit(CVAN + "wall_gate", "out");
    add_exit(CVAN + "gateway/tower2", "up", "@@query_move");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(KG);
	ob1->arm_me();
	ob1->move_living("M",TO);
	tell_room(TO, "A guardsman of Kabal arrives at his post.\n");
    }

    if(!ob2)
    {
	ob2 = clone_object(KG);
	ob2->arm_me();
	ob2->move_living("M",TO);
	ob1->team_join(ob2);
	tell_room(TO, "A guardsman of Kabal arrives from the stairs, then takes "+
	  "his post.\n");
    }
}

int
query_move()
{
    object *ob;
    int pres, i;

    ob = FILTER_LIVE(all_inventory(this_object()));
    pres = 0;

    for (i = 0; i < sizeof(ob); i++)
    {
	if (ob[i]->query_name() == "Guard")
	{
	    pres = 1;
	}
    }

    if (pres == 1)
    {
	write("You are stopped by the guardsman of Kabal.\n");
	say(QCTNAME(TP) + " is prevented from going up the stairs by the guardsman of Kabal.\n");
    }
    return pres;
}
