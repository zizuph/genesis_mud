
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <money.h>
#include <stdproperties.h>
#include <macros.h>


inherit "/d/Krynn/std/dragon_base";


#define ICEWALL "/d/Krynn/icewall/outside/path_5"
#define SLEET "/d/Krynn/icewall/castle/monsters/sleet"

int    at_void      = 0;
object void_room    = find_object(VOID);
object icewall_room = find_object(ICEWALL);

void
create_dragon_npc()
{
    set_name("sleet");
    set_gender( G_FEMALE );

    set_colour("white");
    set_age("adult");

    seteuid(getuid(TO));
    MONEY_MAKE_GC(random(15)+5)->move(TO);
    
    set_alarm(180.0,180.0,"move_me");
    set_act_time(1);
    CUTLEFTOVER("tail");
    LEFTOVER("claw");
    
    add_act("emote reaches down and tears some flesh "
	    + "from the corpse.");
    add_act("emote turns to face you causing waves of fear to course "
	    + "through your body.");

}

void 
move_me() 
{
    if(P(SLEET, icewall_room) && P(SLEET, void_room))
    {
	tell_room(E(TO),"A bolt of lighting crashes down from the heavens "
		  + "and the dragon is no more.\n");
	set_alarm(1.0,0.0,"remove_object");
	return;
    }
    /* The above if statement should be unecessary but is
       there in case of a freik bug. */
    if(!query_enemy(0) || !P(query_enemy(0), E(TO)))
    {
	if (at_void) 
	{
	    TO->move_living("M", ICE_OUT+"path_5");
	    tell_room( ICE_OUT + "path_5", QCTNAME(TO)
		      + " arrives swooping down "
		      + "from the sky.\n");
	    at_void = 0;
	    return;
	}
	TO->move_living("leaping into the air",
			"/d/Krynn/common/void");
	at_void = 1;
	return;
    }
}

void 
do_die(object killer) 
{
    object bits = clone_object("/std/leftover");
    bits->leftover_init("chunk", QRACE(killer));
    bits->move(TO);
    
    ::do_die(killer);
/*
  command("emote emits a loud screech for "
  + "help.");
  set_alarm(2.0,0.0,"call_friend",killer);
*/
}

void 
call_friend(object killer)
{
    object friend;
    
    friend = clone_object(ICE_CAST_M+"red_dragon");
    tell_room(E(TO),"A very large red dragon arrives.\n");
    friend->move(E(TO));
    friend->command("kill "+killer->query_real_name());
    ::do_die(killer);
}
