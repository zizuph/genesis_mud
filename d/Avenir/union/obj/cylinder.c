/*
 * /d/Gondor/common/dwarf_guild/obj/whetstone.c
 *
 * It is a whetstone or grindstone. You can buy it from Borin, the
 * smith and use it to sharpen an axe or other weapon type if you are
 * skilled enough.
 *
 * /Mercade, 30 July 1994
 *
 * Revision history:
 *   Modified by Cirion, January 29th, 1997, for use by the
 *   Union of the Warriors of Shadow. Specificly, I removed
 *   the 'keep' functionality and replaced it with an inheritance
 *   of /lib/keep, as well as changing some of the messages
 *   the object produces.
 *
 *   Lucius OCT 2009: Some cleanups, must have in possession to use now.
 */
#pragma save_binary

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

#define STONE_ID       ("_Union_whetstone")
#define CHECK_WEAPON   "check_weapon"
#define STD_WEAPON     "/std/weapon"
#define WEAPON_SKILL   (30 + random(20))


public void
create_object(void)
{
    set_name("stone");
    add_name(STONE_ID);
    add_name("cylinder");
    set_short("narrow onyx cylinder");
    add_adj(({"narrow","small","onyx","stone","black","dark"}));
    add_adj("union");
    set_long("This is a heavy, narrow cylinder made from "+
	"very rough textured onyx.\nCarved in one end of the cylinder "+
	"is the initial 'H'\n");

    add_prop(OBJ_I_VALUE,   450 + random(100));
    add_prop(OBJ_I_VOLUME,  300 + random(91));
    add_prop(OBJ_I_WEIGHT,  400 + random(201));

    if (IS_CLONE)
      set_item_expiration(); 
}

public int 
f_sharpen(string str)
{
    object obj, *to_whet;

    if (!strlen(str))
	return NF(CAP(query_verb()) + " what?\n");

    if ((!parse_command(str, TP, "[the] %i", to_whet)) ||
	(!sizeof(to_whet = NORMAL_ACCESS(to_whet, 0, 0))))
    {
	return NF(CAP(query_verb()) + " the what?\n");
    }

    if (objectp(obj = TP->query_attack()))
    {
	NF("You are too busy to " + query_verb() + " anything.\n");
	return 0;
    }

    if (sizeof(to_whet) != 1)
    {
	NF("You can only " + query_verb() + " one weapon at a time.\n");
	return 0;
    }
    else
    {
	obj = to_whet[0];
    }

    if (!IS_WEAPON_OBJECT(obj))
    {
	NF("You can only " + query_verb() + " weapons.\n");
	return 0;
    }

    if (!(obj->query_dt() & (W_IMPALE | W_SLASH)))
    {
	NF("Only bladed weapons may be thus sharpened.\n");
	return 0;
    }

    int repair = obj->query_repair_dull();
    int dull   = obj->query_dull();

    switch(dull - repair)
    {
    case 0:
	NF("Your " + obj->short() + " is as sharp as it can be.\n");
	return 0;

    case 1..2:
	break;

    default:
	NF("The " + obj->short() + " is too dull to be thus sharpened.\n");
	return 0;
    }

    if (!F_LEGAL_WEAPON_REPAIR_DULL(repair, dull))
    {
	NF("The " + obj->short() + " has been sharpened too many " +
	  "times now, further wear would only damage it.\n");
	return 0;
    }

    say(QCTNAME(TP) + " slides the edge of " + LANG_ASHORT(obj) +
	" along " + LANG_ASHORT(TO) + ".\n");

    /* If the player does not have enough skill, the weapon will
     * actually get worse. Regardless of your skill, there is a chance of
     * failure :-)
     */
    if (!random(7) || (TP->query_skill(
		SS_WEP_FIRST - W_FIRST + obj->query_wt()) < WEAPON_SKILL))
    {
	obj->set_dull(++dull);
	write("You start to slide " + LANG_THESHORT(obj) +" along "+
	    LANG_THESHORT(TO) + ".\nYou accidently catch the edge of "+
	    "the blade against the rough stone, further dulling "+
	    LANG_THESHORT(obj) + ".\n");
	return 1;
    }

    write("You slide "+ LANG_THESHORT(obj) +" along "+ LANG_THESHORT(TO) +
	", further honing its blade.\n");

    obj->set_repair_dull(++repair);
    return 1;
}

public void
init(void)
{
    ::init();

    if (TP != environment())
	return;

    add_action(f_sharpen, "sharpen");
    add_action(f_sharpen, "whet");
}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);

}
