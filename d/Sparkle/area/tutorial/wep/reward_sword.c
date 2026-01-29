/*
 *  /d/Sparkle/area/tutorial/wep/reward_sword.c
 *
 *  This reward is given to players who give Stanley a beer in the
 *  Red Weasel Tavern in Greenhollow. Only one is given per character.
 *
 *  Given by: /d/Sparkle/area/tutorial/npc/bar_patron1.c
 *  At Location: /d/Sparkle/area/tutorial/town/tavern2.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2015 by Cherek
 *  To make the tutorial easier for newbies this weapon is now magical
 *  in order to make it lighter than what is otherwise allowed. 
 *
 */
#pragma strict_types
inherit "/std/weapon.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("sword");
    add_name( ({ "shortsword", "short-sword"}) );
    add_adj( ({ "ornate", "short" }) );

    set_short("ornate shortsword");
    set_long("This is a very attractive weapon indeed! Though perhaps not"
      + " the most powerful weapon ever crafted, it is clearly capable of"
      + " damaging an opponent.\n");

    set_default_weapon(12, 12, W_SWORD, W_SLASH | W_IMPALE, W_ANYH, 0);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(MAGIC_AM_MAGIC, ({0, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO, ({"To ease the struggle of new players"
	                           + "Lars has made this weapon extra light.\n", 1}));
    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_WEAPON(12, W_SWORD) / 3));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12, 12) + random(15));
} /* create_weapon */

