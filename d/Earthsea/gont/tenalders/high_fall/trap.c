/*
*  coded by Amelia 12/25/97
*  old forest room north of Ten Alders
*  specials:  room_tell.c and search for herbs
*
*/

inherit "/d/Earthsea/std/room";

#pragma no_clone
#pragma strict_types

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/sys/ss_types.h"
#define UP HIGH_FALL + "trail3"


int climb(string str);
int get_out(object tp);

void
create_earthsea_room()
{

    set_short("Dark pit");
    set_long(BS("You find yourself at the bottom of a "+
	"dark pit, which functions as an effective trap since "+
	"the walls are nearly vertical. On the ground are "+
	"sharp rocks and briars. There is not much else "+
	"here.\n", 70));
    add_item((({"rocks", "sharp rocks", "briars"})),
      "You landed on sharp rocks and briars when you "+
      "fell.\n");
    add_item("walls", "The walls of the pit are nearly vertical, "+
      "and slimy with mud and sludge, are very difficult to "+
      "climb.\n");
    add_item((({"ground", "floor"})),
      "The floor of the pit is oozing with sludge, and sharp "+
      "rocks lay all over it.\n");

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 0);

}

void
init()
{
    object tp = this_player();
    int hp = (tp->query_max_hp() / 5) * -1;

    ::init();
    add_action(&climb(), "climb");
    tp->catch_msg("Ouch!\n");
    tp->heal_hp(hp);
}

int
climb(string str)
{

    object tp = this_player();
    int ran = random(20);
    int hp = (tp->query_max_hp() / 20) * -1;
    int fat = (tp->query_max_fatigue() / 5) * -1;

    if (str == "up" || str == "out")
    {
	if ((tp->query_skill(SS_CLIMB) > 29) &&
	  (tp->query_stat(SS_DEX) > 20))
	{
	    TO->get_out(tp);
	    return 1;
	}
	if (ran > 14)
	{
	    TO->get_out(tp);
	    return 1;
	}
	tp->add_fatigue(fat);
	tp->heal_hp(hp);
	tp->catch_msg("You try to climb up the nearly vertical "+
	  "wall but fall back in a heap!\n");
	tell_room(TO, QCTNAME(tp) + " tries to climb up the "+
	  "wall, but falls back in a heap.\n", ({tp}));
	return 1;
    }
    notify_fail("Climb where?\n");
    return 0;
}

int
get_out(object tp)
{
    tp->move_living("M", UP, 1, 1);
    tp->catch_msg("You scramble up the nearly vertical sides "+
      "of the pit!\n");
    tell_room(TO, QCTNAME(tp) + " scrambles up the sides of "+
      "the pit.\n", ({tp}));
    tell_room(environment(tp), QCTNAME(tp) + " climbs in.\n",
      ({tp}));
    return 1;
}
