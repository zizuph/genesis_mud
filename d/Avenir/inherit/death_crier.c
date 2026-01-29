// -*-C++-*-
// file name:    /d/Avenir/common/gods/obj/death_crier.c
// creator(s):   Lilith Aug 2001
// purpose:      This file makes the person who kills the npc
//               that inherits this file subject to the judgement
//               of Plalgus for murdering them.
// note:         If the monster that inherits this file ALSO uses 
//               the function do_die() this WON'T WORK.
// bug(s):
// to-do:  
// last update:
//
// 	Lucius Mar 2009: Various fixups with relation.h changes.
//      Lilith May 2022: included new do_judge func.
//

// To use this file, simply inherit this rather than /std/monster.c

inherit "/std/monster";
#include "/d/Avenir/include/relation.h"

public void
do_die(object killer)
{
    if (query_hp() > 0)
	return;

    if (IS_UNION(killer))
    {
        command("say My life is yours to take, Noble One.");
	return ::do_die(killer);
    }
    else  
    {
        WRATHOBJ->load_me(); 
        command("say May Plalgus smite you for this crime.");

        if (random(4))
        {        
            WRATHOBJ->do_judge(killer);
            return ::do_die(killer);
        }        
        else // 1 in 4 chance they won't be punished.
	{
            WRATHOBJ->test_wrath(killer);
	}
    }
        
    ::do_die(killer);
}
