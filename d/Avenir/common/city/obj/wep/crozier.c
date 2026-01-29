/* bronze crozier        /d/Avenir/common/city/obj/wield/crozier.c
 * creator(s):           Zizuph, August 2021
 * purpose:              To be held by the dej-minha.
 * notes:                
 *                       It is cloned by /d/Avenir/common/city/mon/dej-minha.c
 *                       When held, this staff will increase the number of
 *                       attacks per round.  As it is held in both hands,
 *                       this will mean attacks will all come from the feet.
 *         Requirements: At least 75 points of unarmed combat and 130 dexterity.
 *                       No benefits are given unless the requirements are met.
 *              Effects: Increases cb_attackuse from 100 to 140.  This will
 *                       increase the number of white-hit attacks, but will not
 *                       boost special rates.  This provides a portion of the
 *                       benefits that two-handed combat normally would, while
 *                       requiring both hands to be occupied.  Since it is held
 *                       and not wielded, it will not negatively affect acrobat
 *                       and unarmed combat's effects on cb_tohit.
 *
 *     Associated files: /d/Avenir/common/city/obj/wep/crozier_sh.c
 *                       To add descriptions to the enhanced attacks and
 *                       apply the changes to attackuse.
 *
 * Updates:  Lilith Oct 2021: Fleshed-out magic id info.
 *           Lilith Feb 2022: Made a spell-enhancer
 *           Lilith Jun 2022: Added in the stat_object and stat_object_spellpower
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/lib/keep";

#include "/d/Avenir/common/city/city.h"

#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

object shadow;

void create_object()
{
    set_name("crozier");
    add_adj(({ "bronze-headed", "bronze", "flexible", "kesoit" }));
    set_short("bronze-headed kesoit crozier");
    set_long("This is a flexible kesoit pole with a trefoil knot on one " +
       "end.  The pole is about the height of an elf and nearly half the " +
       "thickness of your wrist.  It seems to be made from a single branch " +
       "of the kesoit tree, peeled of its bark and polished, but retaining " +
       "some of the knots and texture so that hands holding it won't slip." +
       "  The head of the crozier is a trefoil knot cast in bronze. When " +
       "held in combat, this crozier provides balance and lift, aiding " +
       "those who fight with their feet and improving their damage and " +
       "reach.\n");
       
    add_item(({ "head", "trefoil knot", "marking", "knot" }),
        "The top of the crozier bears the marking of the Hegemon.\n");
    
    set_slots(W_BOTH);
    
    setuid();
    seteuid(getuid());
    if (IS_CLONE)
    {
        LISTENER_NOTIFY(this_object());
        set_item_expiration();
    }
    set_keep(1);
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 2000); 
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 3000); /* Magical version */

    set_magic_spellpower(40);
    /* Designate this as a magic weapon (even though it is held) */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "A gift of the Hegemon of Sybarus to his honor-guard, the "+
	"dej-minha,\n", 10,
        "This seemingly ornamental object has been enchanted to "+
	"improve their abilities\n", 15,
	"To fight unarmed, using just their feet to inflict injury "+
	"upon their opponents.\n", 20,
	"When holding it it both hands,\n", 25,
	"Those with enough skill in the arts of unarmed combat\n", 30,
	"And enough dexterity to make use of the pole's flexibility\n", 35,
	"May vault with it and get in a flurry of extra kicks.\n", 40 }));

    /* Let wizards know what the crozier does */
    add_prop(OBJ_S_WIZINFO, "This crozier increases attackuse " +
        "from 100 to 140, which will be foot-based attacks.  " +
        "You need high enough DEX and UNARMED to use this ability.");
}

public mixed
hold()
{
    if (holder->query_skill(SS_UNARM_COMBAT) >= 75 &&
        holder->query_stat(SS_DEX) >= 130)
    {
        // We reset attackuse, just in case something had modified
        // it unexpectedly.
        holder->query_combat_object()->cb_calc_attackuse();
        write("You admire the balance and flexible nature of this crozier.\n");
        shadow = clone_object(OBJ + "wep/crozier_sh");
        shadow->add_crozier_shadow(holder, this_object(), 
            20 + (holder->query_skill(SS_ACROBAT) / 10));
    }
    add_expiration_combat_hook(holder);
    return 0;
}

public mixed
release()
{
    remove_expiration_combat_hook(holder);
    if (shadow) 
    {
        holder->catch_msg(
            "You feel less mobile as you release the crozier.\n");
        holder->remove_crozier_shadow();
        // We reset attackuse, just in case something had modified
        // it unexpectedly.
        holder->query_combat_object()->cb_calc_attackuse();
    }
    shadow = 0;
    return 0;
}

void leave_env(object from, object to)
{
    ::leave_env(from, to);

    holdable_item_leave_env(from, to);
 }

void appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

string query_recover()
{
    return MASTER + ":" + query_item_expiration_recover() +
    (query_prop(OBJ_I_BROKEN) ? "#BR#" : "");
}

void init_recover(string arg)
{
    init_item_expiration_recover(arg);
    string foobar;
    if (sscanf(arg, "%s#BR#%s", foobar, foobar))
    {
        add_prop(OBJ_I_BROKEN, 1);
    }
}

string stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
