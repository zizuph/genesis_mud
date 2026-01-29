/*
 *  /d/Sparkle/area/tutorial/wep/demon_weapon.c
 *
 *  This is the weapon object that the demon guards in the castle
 *  area wield.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2015 by Cherek
 *  To make the tutorial easier for newbies this weapon is now magical
 *  in order to make it lighter than what is otherwise allowed. 
 *
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* Definitions */
#define        DEMON_HIT    20    /* the hit rating of the weapon */
#define        DEMON_PEN    20    /* the pen rating of the weapon */

/* Global Variables */
public string        Weapon_Type = "";   /* what class of weapon is it? */

/* Prototypes */
public void        create_demon_weapon();
public void        create_weapon();
public void        configure_it();

public void        set_dw_type(string s) { Weapon_Type = s; }
public string      query_dw_type() { return Weapon_Type; }


/*
 * Function name:        create_demon_weapon
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_demon_weapon()
{
} /* create_demon_weapon */


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("_tutorial_demon_weapon");
    add_adj( ({ "filthy", "black" }) );

    create_demon_weapon();
    configure_it();
} /* create_weapon */


/*
 * Function name:        configure_it
 * Description  :        set up all the properties of the weapon.
 */
public void
configure_it()
{
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(MAGIC_AM_MAGIC, ({0, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO, ({"To ease the struggle of new players"
	                           + "Lars has made this weapon extra light.\n", 1}));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(DEMON_HIT, DEMON_PEN));
    switch(Weapon_Type)
    {
        case "sword":
            add_name( ({ "sword", "longsword", "blade" }) );
            set_short("filthy black longsword");
            set_long("Though long and rather deadly, this sword looks as"
              + " if it has never been cleaned. Dried blood stains the"
              + " slender blade, and has somewhat dulled its otherwise"
              + " sharp edge.\n");
            set_default_weapon(DEMON_HIT, DEMON_PEN,
                               W_SWORD, W_SLASH, W_ANYH, 0);
            add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(
                     DEMON_HIT, W_SWORD) / 3);
            break;
        case "axe":
            add_name( ({ "axe", "battleaxe", "battle-axe" }) );
            set_short("filthy black battleaxe");
            set_long("The wide blade of this axe is coated with the"
              + " dried blood of many battles. The fool who first owned"
              + " this otherwise excellent weapon never took the time to"
              + " clean it, it seems, leaving it less effective than it"
              + " might otherwise be.\n");
            set_default_weapon(DEMON_HIT, DEMON_PEN,
                               W_AXE, W_SLASH, W_ANYH, 0);
            add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(
                     DEMON_HIT, W_AXE) / 3);
            break;
        case "club":
            add_name( ({ "club", "morningstar", "morning-star" }) );
            set_short("filthy black morningstar");
            set_long("The cruel iron spikes which are affixed to the"
              + " bludgeon of this morningstar are coated with the dried"
              + " blood of what must be many victims. It seems that"
              + " this weapon has been rarely, if ever, cared for.\n");
            set_default_weapon(DEMON_HIT, DEMON_PEN,
                               W_CLUB, W_BLUDGEON, W_ANYH, 0);
            add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(
                     DEMON_HIT, W_CLUB) / 3);
            break;
        case "knife":
            add_name( ({ "knife", "dagger", "blade" }) ); 
            set_short("filthy black dagger");
            set_long("The blade of this dagger looks as if it has been"
              + " dipped in blood, coated with dirt, and then allowed to"
              + " bake in the sun. Though clearly uncared for by its"
              + " former owner, it is still deadly as ever.\n");
            /*
             * knives can't be 20-20 here, so don't use DEMON defs
             */
            set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH, 0);
            add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10, W_KNIFE) / 3);
            add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10, 10));
            break;
    }
	add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
} /* configure_it */

