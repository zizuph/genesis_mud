/*
 *	/d/Gondor/harondor/room/ford01.c
 *  A room in the Fords of the River Poros in Harondor.
 *  October 9, 2004, Serif.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/harondor/lib/std_funcs.c";
inherit "/d/Gondor/harondor/lib/ford_funcs.c";

#define HARD_TO_SWIM 16 

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public int     ford();

public void
create_area_room()
{
    set_areatype(5);
    set_area("southern");
    set_areadesc("ford");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("Across the river to the north, the Harad Road "
        + "resumes on its way through Ithilien. And to the south " 
        + "it resumes its way through Harondor. Above you the "
        + "bridge looms. To the east, the peaks of the Ephel " 
        + "Duath loom ominously. You feel unsafe standing here "
        + "as the swift waters flow around you, "
        + "drenching you completely.");

    add_item(({"road", "harad road"}), "The ancient trade road "
        + "between Gondor and Harad, the Harad Road, resumes "
        + "on its path through Ithilien just north across the "
        + "river. In the distance to the south, the Road cuts "
        + "across the land of Harondor.\n");
    add_item(({"river", "poros", "river poros", "current"}), "The River "
        + "Poros widens here as it flows swiftly toward the "
        + "west. It is shallow enough to cross here most times of "
        + "the year, although the current is still swift.\n");
    add_item(({"ford", "fords"}), "The river is very wide here, "
        + "its flow shallow but swift. It is possible to travel "
        + "south across the ford here without swimming.\n");
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "slope", "slopes"}), "The peaks of the Ephel Duath "
        + "loom ominously in the east.\n");
    add_item(({"water", "waters", "flow", "current", "currents"}), 
        "The waters of the River Poros flow all around you on their way "
        + "west toward the sea. The water is shallow but swift here, and " 
        + "seems deeper to the north as well as further south.\n");
    add_item(({"surroundings"}), "You are standing in the middle of a "
        + "wide river. The water is shallow but flows swiftly all around "
        + "you. The currents seem stronger to the immediate north, and "
        + "further south as well.\n");
    add_item(({"harondor"}), "South of the river, the scrublands of "
        + "Harondor spread out to the south, east and west.\n");
    add_item(({"ithilien", "shore", "north shore", "forest", "forests"}), 
        "The forests of Ithilien line the north shore of the river.\n");
    add_item(({"plant", "plants", "bush", "bushes", "dense bushes", 
        "thicket", "thickets", "thorn", "thorns", "vegetation"}), "On "
        + "the riverbanks, dense thickets of bushes and other plants rise "
        + "above the grass, many of them armed with thorns.\n");
    add_item(({"grass", "tall grass", "lush grass", "tall lush grass"}), 
        "Tall, lush grass grows thickly on the banks across the river "
        + "to the north and south, sprouting out beside the road "
        + "and between the bushes.\n");
    add_item(({"insect", "insects"}), "Numerous insects fly through "
        + "the air and dart above the water.\n");
    add_item(({"scrub", "scrublands", "land", "lands", "horizons",
        "horizon", "savannah", "savannahs", "scrubland", "harondor"}), 
        "Scrublands and savannahs spread out to the south across the "
        + "river, filled with lush grass, dense bushes and occasional "
        + "trees. To the east, dark mountains rise out of the "
        + "scrublands.\n");
    add_item(({"ripple", "ripples", "surface"}), "Ripples spread "
        + "and intertwine across the surface of the river.\n");
    add_item(({"bank", "banks", "edge", "riverbank", "riverbanks", "mud",
        "willow", "willows", "tangle", "muddy riverbanks", "muddy bank",
        "muddy banks", "muddy riverbank", "shore", "north shore", 
        "south shore"}), "The banks of the river rise muddily "
        + "out of the river in the distance to the north and "
        + "south. They are thick with grass and willows, obscuring "
        + "what might lie beyond.\n");
    add_item(({"rock", "stone", "rocks", "stones"}), "Rocks and stones "
        + "fill the riverbed here, shifting with the weight of the "
        + "of the water and making passage difficult.\n");
    add_item(({"riverbed", "channel", "river channel"}), "The riverbed "
        + "is wide and shallow here.\n");

    add_cmd_item(({"river", "the river", "ford", "the ford", "poros",
        "river poros", "the river poros", "north"}), ({"swim", "cross",
        "ford", "wade"}), "@@ford_river");

    set_no_exit_msg(({"east", "west", "southwest", "northwest",
        "northeast", "southeast"}), "You wade away from the ford "
        + "a few yards, but find the river too treacherous.\n");
    set_no_exit_msg(({"north"}), "You start to wade north, but "
        + "realize that you will have to swim.\n");
    set_no_exit_msg(({"south"}), "You realize that the current is "
        + "too swift in that direction.\n");

    set_drink_from( ({ "river", "poros", "river poros", "River Poros", 
        "Poros" }) );
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_ford_tells();
    add_ford_items();

    set_tell_time(50);
    add_tell("The river rushes around you.\n");
    add_tell("The river rushes around you.\n");
    add_tell("The surface of the river ripples.\n");
    add_tell("The surface of the river ripples.\n");
}

public void
drink_message(string from)
{
    write("You drink some silty water from the River Poros.\n"
        + "It tastes a little bitter, but you feel refreshed.\n");
    say(QCTNAME(TP) + " drinks some silty water from the river.\n");
}

public void
init()
{
    ::init();
    init_drink();
}

int
ford_river()
{
    if (TP->query_prop(LIVE_O_STEED) != 0) /*On a steed, can't cross.*/
    {
	write("It is unsafe to lead your steed into the treacherous ford!\n");
	say(QCTNAME(this_player())+" tries cross the ford while mounted, "
        + "but "+this_player()->query_possessive()+" steed shies "
        + "away from the river.\n",this_player());
        return 1;
    }
    if (TP->query_prop(LIVE_O_STEED) == 0) /*No steed, ok to cross.*/
    {
    if (TP->query_skill(SS_SWIM) > 20+random(10)) /*Swims well, can cross.*/
        {
    write("You manage to wade through the swift currents and ford the river, "
        + "safely reaching the northern shore.\n");
        say(QCTNAME(TP)+" leaves fording the river to the north.\n");
        TP->move_living("M", "/d/Gondor/harondor/room/road00s", 1);
        say(QCNAME(TP) + " arrives wading through the river.\n");
       return 1;  /*Player is moved across the river.*/
        }
    else  /*Can't swim well, can't cross.*/
    write("You struggle to cross the river, but you cannot keep your "
      + "footing while you fight against the current.\n");
    say(QCTNAME(TP)+" tries to ford the river, but fails.\n");
    return 1;
    }
    return 1;
}

public int
ford()
{   
    object  tp = TP;
    int     ford_try = (HARD_TO_SWIM / 2 + random(HARD_TO_SWIM) + 1),
    skill = tp->query_skill(SS_SWIM);

    if (skill < ford_try)
    {
	tp->reduce_hit_point(ford_try - skill);
	write("You stumble crossing the ford and inhale some water.\n");
	say(QCTNAME(tp) + " stumbles and falls into the water.\n");
	return 1;
    }

    write("You wade through the river.\n");
    return 0;
}

/* This function causes dropped items to be swept downstream.
   Objects are not destructed, though, but are moved to an
   underwater room. */
public void
drop_item(object ob, int silent)
{
  string down_room;

  down_room = "/d/Gondor/harondor/room/riverbottom";
  if (ob && present(ob))
  {
    if (!silent)
    {
	  switch( ob->num_heap() )
	  {
	    case 0:
	        tell_room(TO,
		    "The "+ob->short()+" is swept downstream by the current.\n");
            ob->move(down_room);
            tell_room(down_room, CAP(LANG_ADDART(ob->query_short())) + " is "
                + "swept in by the current.\n");
            down_room->drop_item(ob);

	     break;
	    case 1:
	        tell_room(TO,
		    CAP(ob->short())+" is swept downstream by the current.\n");
            ob->move(down_room);
            tell_room(down_room, CAP(ob->short())+" is swept in by the "
                + "current.\n");
            down_room->drop_item(ob);

	     break;
	    default:
	        tell_room(TO,
		    CAP(ob->short())+" are swept downstream by the current.\n");
            ob->move(down_room);
            tell_room(down_room, CAP(ob->short())+" are swept in by the "
                + "current.\n");
            down_room->drop_item(ob);

	     break;
	    }
      }
   }
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if(interactive(ob))
      start_room_tells();

  if(!living(ob))
      set_alarm(1.0, 0.0, &drop_item(ob));
}
