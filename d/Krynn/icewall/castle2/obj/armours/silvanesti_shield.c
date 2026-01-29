/* silvanest_shield.c is a reward item for slaying the Icewall yeti
   and laying the spirit of a dead Royal Guard of Sylvanos to rest.

   creator: Kessie
   final version: november 2001
*/


/*
 * Note by Navarre, November 22th 2005:
 *
 * - It has been discussed many times that this shield ought to be downgraded.
 *   It used to cover all of the body with ac 50, plus giving 40 in all categories
 *   of magical resistances.
 *   I lowered the crap_shield (the non unique counter part), to 30 from 40, and 
 *   lowered this shield from 50 to 40.
 *   I also lowered the magical resistances to 10 in each, instead of 40 in each.
 *   Which was too good for 1 item to carry.
 *   The shield remains the best shield in the game, but it is a little more within
 *   reason now. It was even discussed to remove all the magical resistances 
 *   but I have left them at 10 for now.
 */

/*
 * Nav Feb 2007, Removed A_HEAD protection. Increased weight of shield
 */

/*
 * Navarre June 2008, Since no one wanted to follow with the decrease of Ac on shields
 *                    and purchased shields give same protection, same coverage and ac,
 *                    and being lighter than this shield. I am giving it back 50 ac.
 *                    They do have to defeat a big myth creature to get it after all.
 */

/*
 *  Arman August 2017, Fixed the long_desc function. It was causing some bug issues when
 *                     its long description was being altered by other code (i.e neidar 
 *                     forge).  
 */


#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/icewall/local.h"

int id = 120 + random(65);

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj("tower");
    add_adj("silvanesti");
    set_short("silvanesti tower shield");
    set_pshort("silvanesti tower shields");
    set_ac(50);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("@@long_desc");
    add_prop(OBJ_I_VOLUME, 8500);
    //add_prop(OBJ_I_WEIGHT,  2*F_WEIGHT_DEFAULT_ARMOUR(40, A_SHIELD));

    // Such as fancy magical shield is worth a little extra.
    add_prop(OBJ_I_VALUE, 5*F_VALUE_ARMOUR(40)+random(500));

    set_af(TO);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(MAGIC_AM_ID_INFO,
        ({"This shield was forged by the magicsmiths of Silvanesti " +
        "for use by the Royal Guard of Sylvanos. Made out of elven " +
        "steel and enchanted by the magic of the White Robed " +
        "Wizards of High Sorcery, as well as blessed by the High " +
        "Priests of Paladine, it offers unrivaled protection.\n",25}));
    add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
    add_prop(OBJ_M_NO_BUY, 1);
         
}


int
identify(object ob)
{
    int race = (ob->query_race() == "elf" ? 3 : 2);
    int wis = ob->query_stat(SS_WIS);
    int skill = ob->query_skill(SS_APPR_OBJ);

    if ((wis + skill * race / 3) > id)
	return 1;
    else
	return 0;
}

string
long_desc()
{
    if (identify(TP))
    {
        return "You look upon a true shield of the Sylvanos Royal " +
            "Guard, crafted in ancient Silvanesti at the height of the " +
            "elven kingdom, when dragons and demons still stalked the " + 
            "lands. Made to protect those the elves beloved most, the " +
            "royal family, the shields were handed to the most trustworthy " +
            "of warriors. They came as a great gift, but also, as a great " +
            "responsibility - the life of royalty always came first, no " +
            "matter the odds, no matter the sacrifice. It is no wonder that " +
            "the heavily blessed and magical shields often outlived their " +
            "owners...\n";
    }
    else
    {
        return "A sturdy, yet light tower shield with a definitely " +
            "elven touch to it. The emblem tells you nothing, yet the " +
            "shield itself looks amazingly sturdy. Maybe it would be " +
            "wise to seek someone better versed in elven lore and ask " +
            "about it? Who knows, it might even be an artifact... or " +
            "something.\n";
    }
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (protectee == query_worn())
      {
      if (prop == MAGIC_I_RES_FIRE)
        return ({ 10, 0}); /* non-additive */
      if (prop == MAGIC_I_RES_COLD)
        return ({ 10, 0}); /* non-additive */
      if (prop == MAGIC_I_RES_ACID)
        return ({ 10, 0}); /* non-additive */
      if (prop == MAGIC_I_RES_ELECTRICITY)
        return ({ 10, 0}); /* non-additive */
      if (prop == MAGIC_I_RES_POISON)
        return ({ 10, 0}); /* non-additive */
      }
    else
      return ::query_magic_protection(prop, protectee);
}

mixed
wear(object what)
{
    object player = wearer; // query_worn() doesn't work in wear. Only in remove.
    if (identify(player))
    {
        player->catch_tell("As you wear the silvanesti tower shield upon " +
            "your forearm, you feel the legacy of its previous owners " +
            "rest heavily upon your shoulders. Many of them died, sacrificing " +
            "themselves to protect those beloved most, loyal to the very " +
            "end. Will you prove yourself worthy of their name? " +
            "You feel as if their ghosts were watching you...\n");

        tell_room(environment(player), QCTNAME(player) + " shivers slightly as " 
            + HE(player) + " equips the silvanesti " +
            "tower shield, and grows solemn. You wonder why.\n", 
            ({ player }), player);
        player->add_magic_effect(TO);
        return 1;
    }    
      
    player->catch_tell("For reasons unknown, the shield feels quite good on " +
        "your forearm.\n");

    tell_room(environment(player), QCTNAME(player) + " smiles in a manner " +
        "of the simple folks as " + 
        HE(player) + " equips the silvanesti tower shield. You wonder " +
        "what caught " + HIS(player) + " fancy.\n",
        ({ player }), player);

    return 0;

}     

mixed
remove(object what)
{
    object player = query_worn();
    if (identify(player))
    {
        player->catch_tell("With definite regret you remove the tower " +
            "shield from your forearm.\n");
        tell_room(environment(player), QCTNAME(player) + " sighs as " 
            + HE(player) + " removes the tower shield from " 
            + HIS(player) + " forearm.\n", ({ player }), player);
        player->remove_magic_effect(TO);
        return 1;
    }

    return 0;
}
