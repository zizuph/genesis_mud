/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * child.c
 *
 * This is Edward.  He is the subject of the child_quest (see
 * ~Terel/open/BITS for more information).  He is a standard
 * monster, very weak.  He also will follow a player, if that
 * player types 'say follow.' .  Upon following, if ever the
 * player wishes to get rid of this tag-along (which cannot
 * be shaken very easily), he or she can type 'say goaway.'.
 *
 * Coded by Vader September 1992
 * recoded by Sorgum 950707
 * recoded by Mortricia May 1996  removed trig_new
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <macros.h>

/* Global variables for quest specific code */
/* as well as the following code            */
object leader = 0;

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    
    set_name("edward");
    set_living_name("edward");
    set_race_name("human");
    set_adj(({"young", "crying"}));
    set_long("This child is crying.  He has lost his mommy!!  He will " +
             "follow, if you ask him so.  If he follows you, and you " +
             "want him to go away, just ask him to leave.\n");

    default_config_npc(3);
    set_all_hitloc_unarmed(12);

    set_chat_time(10);
    add_chat("Where's my MOMMY???");
    add_chat("I want my MOMMY!!!");
    set_act_time(1);
    add_act("cry");
    
    add_ask(({"follow", "follow me", "to follow", "to follow me"}),
            "@@my_follow", 1);
    add_ask(({"go away", "to go away", "leave", "to leave"}),
            "@@my_leave", 1);
}

public string
my_follow()
{
    if (leader)
        return "confused";
        
    TP->catch_msg("You ask " + QTNAME(TO) + " to follow you.\n");
    set_follow(TP->query_real_name());
    leader = TP;
    return "sob";
}

public string
my_leave()
{
    if (!leader)
        return "confused";
        
    TP->catch_msg("You ask " + QTNAME(TO) + " to leave you.\n");
    set_follow(0);
    leader = 0;
    return "cry";
}

public object
query_solver()
{
    return leader;
}


