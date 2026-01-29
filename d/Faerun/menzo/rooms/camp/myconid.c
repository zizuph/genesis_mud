/*
 * /d/Faerun/menzo/npc/myconid.c
 *
 * Myconid NPC/Underdark
 * Clyptas, February, 2018
 */
 
inherit "/std/monster";

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_monster()
{
    seteuid(getuid());
    set_name("myconid");
	set_short("short smelly myconid");

    set_race_name("human");

    set_adj( ({"funguslike","fleshy"}) );

    set_alignment(0);

    set_gender(G_MALE);
    
    set_act_time(10);
    set_cact_time(10);
	
    add_act("emote reaches towards you with his syncytial arms.");
    add_act("emote releases a cloud of spores that waft through the air.");
	add_act("emote groans and chews nonchalantly, smacking his...lips?");
}


