#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Tower");
    set_long("You've just arrived at the second level of the tower. This room "+
      "has nothing of interest save for the iron door to the west. Also, "+
      "the staircase heads up and down from here.\n");

    add_item(({ "iron door", "door" }),
      "It's a regular old iron door. You see a bronze sign nailed on the "+
      "door.\n");

    add_item(({ "bronze sign", "sign" }),
      "There are words on it, maybe you should read it?\n");

    add_item(({ "staircase" }),
      "A steel staircase that leads up to the top of the tower and down to "+
      "the ground floor.\n");

    add_exit(CVAN + "gateway/tower3", "up", "@@query_move");
    add_exit(CVAN + "gateway/tower1", "down");

    clone_object(CVAN + "door/idoor")->move(this_object());

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "kguard");
	ob1->arm_me();
	ob1->move_living("M",TO);
	tell_room(TO, "A guardsman of Kabal arrives climbing the staircase.\n");
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
	if(ob[i]->query_name() == "Guard")
	{
	    pres = 1;
	}
    }

    if (pres == 1)
    {
	write("You are stopped by the guardsman of Kabal.\n");
	say("The guardsman of Kabal stops " + QTNAME(TP) + " from going up.\n");
    }
    return pres;
}

void
init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    "                    {}{}{}{}{}{}{}{}{}{}\n"+
    "                    {}     OFFICE     {}\n"+
    "                    {}       OF       {}\n"+
    "                    {}     HAHMAL     {}\n"+
    "                    {}   CAPTAIN OF   {}\n"+
    "                    {} THE CITY GUARD {}\n"+
    "                    {}{}{}{}{}{}{}{}{}{}\n";
}
