/*
 * roof.c
 *
 * Skippern 20(c)02
 *
 * A roof, you have arrived from the tree, if you start to fight
 *  with anybody you should fall down (into either one of the gardens or
 *  the balcony). To get down you must find out what chimny are safe and
 *  climbe down it.
 */
inherit "/d/Gondor/std/room";

#include "../../defs.h"
#include "../defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Global variables */
int           Dam;
object        ob;

/* Prototypes */
public int     do_climb(string arg);
       mixed   falling(object ob);
       string  chimn_desc_n();
       string  chimn_desc_s();


void
create_gondor()
{
    set_short("on a roof");
    set_long("You find yourself on top of a roof. From high up here you " +
	     "can see the entire city of Dol Amroth. To the north you see " +
	     "the lower part of the city, with all its activity. To the " +
	     "southwest you see a large castle, and from there goes a wall " +
	     "all the way to the city gate in southeast.\n");

    add_item( ({ "chimny", "chimnies" }), "There are two chimnies here, " +
	      "one to the north, and one to the south.\n");
    add_item("north chimney", &chimn_desc_n());
    add_item("south chimney", &chimn_desc_s());

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_AMROTH_ROOF);
    add_prop(ROOM_M_NO_ATTACK, &falling(this_player()));
}

void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

string
chimn_desc_n()
{
    if (FIREMASTER->query_smoke_n())
        return "Thick white smoke is coming out of the north chimney.\n";
    else
        return "The north chimney is a solid brick chimney. It looks " +
	  "climbable.\n";
}

string
chimn_desc_s()
{
    if (FIREMASTER->query_smoke_s())
        return "Thick white smoke is coming out of the south chimney.\n";
    else
        return "The south chimney is a solid brick chimney. It looks " +
	  "climbable.\n";
}

public int
do_climb(string arg)
{
    notify_fail("Climb what?\n");

    if (arg == "chimney")
    {
	notify_fail("Climb which chimney? North or south?\n");
	return 0;
    }

    if (arg == "north chimney")
    {
	if (FIREMASTER->query_smoke_n())
	{
	    notify_fail("Its too smoky. You will probably die in the " +
			"attempt.\n");
	    return 0;
	}
        write("You climbs into the chimny.\n");
        say(this_player()->query_nonmet_name() + " leaves climbing into " +
	    "the northern chimny.\n");
        this_player()->move_living("M", DOL_HILLS + "m-11/N_chimn", 1, 0);
	return 1;
    }
    else if (arg == "south chimney")
    {
        if (FIREMASTER->query_smoke_s())
        {
            notify_fail("Its too smoky. You will probably die in the " +
                        "attempt.\n");
            return 0;
        }
        write("You climbs into the chimny.\n");
        say(this_player()->query_nonmet_name() + " leaves climbing into " +
	    "the southern chimny.\n");
        this_player()->move_living("M", DOL_HILLS + "m-11/S_chimn", 1, 0);
	return 1;
    }
    return 0;
}

mixed
falling(object ob)
{
    int r, stores, hp;
    int dex = ob->query_stat(SS_DEX);
    int con = ob->query_stat(SS_CON);
    int enc = ob->query_encumberance_weight();
    int hpm = ob->query_max_hp(); 

    switch(random(4))
    {
    case 1:
      write("In the action you stumble on a loose tile and falls down.\n");
      say(QCTNAME(ob) + " stumbles and falls " +
	  "down.\n");
      ob->move_living("M", DOL_HILLS + "m-11/balcony", 1, 0);
      write("You crashes to the ground with enormouse force.\n");
      say(QCTNAME(ob) + " arrives through the air " +
	  "and lands infront of you with a loud splat!\n");
      stores = 1;
      break;
    case 2:
      write("In the action you stumble on a loose tile and falls down.\n");
      say(QCTNAME(ob) + " stumbles and falls " +
          "down.\n");
      ob->move_living("M", DOL_HILLS + "m-11/garden2", 1, 0);
      write("You crashes to the ground with enormouse force.\n");
      say(QCTNAME(ob) + " arrives through the air " +
          "and lands infront of you with a loud splat!\n");
      stores = 3;
      break;
    case 3:
    case 4:
    default:
      write("In the action you stumble on a loose tile and falls down.\n");
      say(QCTNAME(ob) + " stumbles and falls " +
          "down.\n");
      ob->move_living("M", DOL_HILLS + "m-11/garden1", 1, 0);
      write("You crashes to the ground with enormouse force.\n");
      say(QCTNAME(ob) + " arrives through the air " +
          "and lands infront of you with a loud splat!\n");
      stores = 2;
      break;
    }
    if (stores < 1)
      stores = 1;
    r = enc * stores;
    r = r + (con);
    r = r - (dex / 2);
    Dam = hpm * r / 100;

#ifdef DEBUG
    if (ob->query_wiz_level())
	write("FALLDAMAGE: " + Dam + ".\n");
#endif

    hp = ob->query_hp();
    ob->heal_hp(-Dam);
    if (Dam > hp)
        ob->do_die();

    return "";
}
