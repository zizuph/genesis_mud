// /d/Avenir/common/outpost/npc/call_for_help
//  This file should be inherited by npcs that 
//  call for help when the fighting starts.
//  This results in the ones fighting being hauled
//   off to gaol.


inherit "/std/monster";
#include "/d/Avenir/include/relation.h"

#define GAOL	"/d/Avenir/common/outpost/gaol_cell"

/*
 * Function name: attacked_by
 * Description  : This routine is called when we are attacked.
 * Arguments    : object attacker - the attacker.
 */
public void attacked_by(object attacker)
{
    (GAOL)->call_for_guards(attacker);
        attacker->add_prop(EVILDOER, IS_EVILDOER(attacker) + 1);
	command("shout Hey punishers! Someone's starting a fight with me!"); 
		
    ::attacked_by(attacker);
}

