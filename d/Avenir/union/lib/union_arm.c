/*
 * Armour for Union members. It can become dirty or
 * bloody.
 *   Cirion 021398
 *
 * Revisions:
 *	Achdram, Jan 2005: Added checks for the new terraintypes.
 *	Lucius,  May 2009: Small cleanup, updated for new ships,
 *			   added bits to control buff/clean actions.
 *			   Adjusted blood increment as well.
 *  Lilith, Dec 2021: Global changes to fatigue make the fatigue 
 *                    cost to wash the cape too high. Removing.
 *
 */
#pragma strict_types
#include "../defs.h"

#include <macros.h>
#include <terrain.h>
#include <ss_types.h>
#include <stdproperties.h>

public int allow_buff, allow_clean, dirt, blood;

public void
union_stain_with_blood(int how_much)
{   /* Cap amount added per call. */
    blood += min(10, random(how_much / 2));
}

public int
do_clean(string str)
{
    object ob;
    string nil;

    if (!strlen(str) || !parse_command(str, ENV(TO),
	    "[the] / [a] / [an] %o %s", ob, nil) || ob != TO) {
	return NF(CAP(query_verb())+" what?\n");
    }

    if (!allow_clean)
    {
	write("You cannot "+ query_verb() +" the "+ ob->short() +".\n");
	return 1;
    }

    if (ob->query_worn() == TP)
    {
	write("You would need to remove it first.\n");
	return 1;
    }

    int type = ENV(TP)->query_prop(ROOM_I_TYPE);

    /* Check the room type for water */
    if (type == ROOM_BEACH ||
	type == ROOM_IN_WATER ||
	type == ROOM_UNDER_WATER ||
	ENV(TP)->query_prop(TERRAIN_ONWATER) ||
	ENV(TP)->query_prop(TERRAIN_UNDERWATER) ||
	ENV(TP)->query_prop(OBJ_I_CONTAIN_WATER))
    {
	write("You "+ query_verb() +" "+LANG_THESHORT(TO) +" in the water.\n");
	say(QCTNAME(TP)+" washes "+HIS(TP)+" "+QSHORT(TO)
	  +" in the water.\n");

	dirt--;
	blood -= random(TP->query_stat(SS_STR) / 2);


	if (dirt < 0) dirt = 0;
	if (blood < 0) blood = 0;

	return 1;
    }

    /* Am I on a ship? */
    if (ENV(TP)->query_is_deck() ||
	function_exists("create_deck", ENV(TP)) ||
	function_exists("create_ship", ENV(TP)))
    {
	write("You lean over the side of the ship and "+
	    query_verb()+" "+LANG_THESHORT(TO)+" in the sea water.\n");
	say(QCTNAME(TP)+" leans over the side of the ship and "
	  +"washes "+HIS(TP)+" "+QSHORT(TO)+" in the sea water.\n");

	blood -= random(TP->query_stat(SS_STR) / 2);

	if (--dirt < 0) dirt = 0;
	if (blood < 0) blood = 0;

	return 1;
    }

    write("There is no water to clean it in.\n");
    return 1;
}

public int
do_buff(string str)
{
    object ob;
    string nil;

    if (!strlen(str) || !parse_command(str, TP,
	    "[the] / [a] / [an] %o %s", ob, nil) || ob != TO) {
	return NF(CAP(query_verb())+" what?\n");
    }

    if (!allow_buff)
    {
	write("You cannot "+ query_verb() +" the "+ ob->short() +".\n");
	return 1;
    }

    if (ob->query_worn() == TP)
    {
	write("You would need to remove it first.\n");
	return 1;
    }

    write("You take out a cloth and "+query_verb()+" "+
	LANG_THESHORT(TO) +" with it.\n");
    say(QCTNAME(TP)+" "+ query_verb() +"s "+HIS(TP)+" "+QSHORT(TO) +
	" with a small cloth.\n");
    if (--dirt < 0)
	dirt = 0;

    return 1;
}

public void
init_union_arm(void)
{
    add_action(do_buff,  "shine");
    add_action(do_buff,  "buff");
    add_action(do_clean, "wash");
    add_action(do_clean, "clean");
}
