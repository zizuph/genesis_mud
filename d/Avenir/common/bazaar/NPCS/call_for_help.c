// -*-C++-*-
/* To be inherited by (humaniod) monsters that should call for help
 * The stockade guards will show up and fetch the killer if he doesn't
 * disappear fast enough. Note that if the monster that inherits this
 * file also uses the function do_die() this won't work.
 * Coded by Mortricia for Avenir, Dec. 1994
 *
 *	Lucius Mar 2009: Various fixups with relation.h changes.
 *      Lilith May, 2022: update to logic for punishments.
 *
 */
inherit "/std/monster";
#include "/d/Avenir/include/relation.h"

#define STOCKADE_ROOM	"/d/Avenir/common/bazaar/extr/hill"

public void
do_die(object killer)
{
    if (query_hp() > 0)
	return;

    int i = random(10) + 1;

    // Union gets a pass.
    if (IS_UNION(killer))
    {
        command("say My life is yours to take, Noble One.");
        return ::do_die(killer);
    }
    WRATHOBJ->load_me();
    // You killed an official? Jail + Hammered  
    if (this_object()->query_name() == "official")
    {
        command("shouts with his dying breath: Take this sin'ur to "+
           "the pillory!");
        WRATHOBJ->do_judge(killer);        
        (STOCKADE_ROOM)->call_for_guards(killer, environment(killer));
        return ::do_die(killer);
    }
    // Serial murderer? Jail + Hammered
    if (IS_EVILDOER(killer))
    {
        (STOCKADE_ROOM)->call_for_guards(killer, environment(killer));
        killer->add_prop(EVILDOER,
	    IS_EVILDOER(killer) + 1);
        WRATHOBJ->do_judge(killer);
        return ::do_die(killer);
    }
    //Jail them but no hammer-- this time.
    command("shout May Plalgus smite thee for my murder, sin'ur!");    
    (STOCKADE_ROOM)->call_for_guards(killer, environment(killer));
    WRATHOBJ->test_wrath(killer);        
    ::do_die(killer);
}
