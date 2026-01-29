/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/npc_soul.c
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide emotes, attacks, and abilities common
 *                to all humanoid sybarites
 * note:          See below for list of functions/abilities
 * last update:             9/26/97
 * bug(s):
 * to-do:
 *
 *      Available combat specials:
 *  Function       Soul cmd  Effect
 *  ===================================================================
 *  cloak_disarm   cdisarm   Disarms (non-damaging attack).
 *  double_punch   punch     Damaging unarmed attack.
 *  hit_neck       neck      Damaging weapon attack, targets neck.
 *  knife_pluck    pluck     Damaging weapon attack.
 *  pommel_smash   pommel    Damaging weapon attack, targets face.
 *  stun_kick      skick     Damage&stun unarmed attack, targets legs.
 *  dej_smash      smash     Dej-minha elbow attack.
 *
 *      Non-combat special abilities:
 *  Function       Soul cmd  Effect
 *  ===================================================================
 *  poison_cure    cure      Cures npc of poisons.
 *  health_heal    heal      40% change of healing w/ random messages.
 *
 *     Emotions:
 *  ===================================================================
 *  slaugh         laugh the chilling laugh of someone who is w/o fear.
 */
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"

/* Checks used in combat specials */

int check_volume(object ob){    return (ob->query_prop(CONT_I_VOLUME));    }
int check_weight(object ob){    return (ob->query_prop(CONT_I_WEIGHT));    }

object
check_boots(object ob)
{
    object *o_worn;
    object  boots;
    int i;

    o_worn = ob->query_armour(-1);
    for (i = 0; i < sizeof(o_worn); i++)
    {
        if (o_worn[i]->query_at() == A_FEET)
            boots = o_worn[i];
    }
    return boots;
}
object
check_cloak(object ob)
{
    object *o_worn;
    object  cloak;
    int i;

    o_worn = ob->query_armour(-1);
    for (i = 0; i < sizeof(o_worn); i++)
    {
        if (o_worn[i]->query_at() == A_ROBE)
            cloak = o_worn[i];
    }
    return cloak;
}
object
check_gloves(object ob)
{
    object *o_worn;
    object  gloves;
    int i;

    o_worn = ob->query_armour(-1);
    for (i = 0; i < sizeof(o_worn); i++)
    {
        if (o_worn[i]->query_at() == A_HANDS)
            gloves = o_worn[i];
    }
    return gloves;
}
object
check_weapon(object ob)
{
    object *o_weapons;
    object w, w0, w1;
    int i, wnum, wnum0, wnum1, j;

    /* Am I wielding anything? */
    o_weapons = ob->query_weapon(-1);
    if (sizeof(o_weapons) == 1)
    {
        for (i = 0; i < sizeof(o_weapons); i++)
	      w = o_weapons[i];
    }
    /* Am I wielding more than one weapon? */
    if (sizeof(o_weapons) == 2)
    {
        w0 = o_weapons[0];
	  w1 = o_weapons[1];
    }
    if ((w0) && (w1))
    {
      /* I'll average the hit and pen and choose which 
         to use for this special */
	wnum0 = ((w0->query_hit() + w0->query_pen()) / 2);
	wnum1 = ((w1->query_hit() + w1->query_pen()) / 2);
      
	if (wnum0 >= wnum1)
	    return w0;
	else
	    return w1;
    }
    if (w)
        return w;      
}

/*
 * Function:    can_attack
 * Description: Checks to determine if npc can attack his target.
 * Arguments:   actor - the one using this soul.
 *		victim - the victim of the attacks.
 */
int
can_attack(object me, object victim)
{ 
    string str;

    /* I don't exist */
    notify_fail("I don't exist\n");
    if (!objectp(me))           
        return 0;
    
    /* I can't hurt something w/o a body */
    notify_fail("Its non-corporeal.\n");
    if (victim->query_prop(LIVE_I_NO_BODY))
        return 0;

    /* I'm not going to add insult to injury */
    notify_fail("Its a ghost.\n");
    if (victim->query_ghost())
        return 0;

    /* No fighting in non-fight room */
    notify_fail("You can't fight here!\n");
    if ((!me->query_attack()) && (str = ENV(me)->query_prop(ROOM_M_NO_ATTACK)))
        return 0;

    /* No fighting enemies w/ no_attack prop */
    notify_fail("You can't fight him!\n");
    if (str = victim->query_prop(OBJ_M_NO_ATTACK))
        return 0;

    /* Has someone defined this to block all special attacks */
    notify_fail("All attacks are blocked!\n");
    if (victim->query_not_attack_me(me, -1))
        return 0;

    /* Don't dare attack */
    notify_fail("You don't dare!\n"); 
    if ((!F_DARE_ATTACK(me, victim)) &&
        (member_array(victim, (object *)me->query_enemy(-1)) == -1))
        return 0;

    /* I'm too stunned to attack */
    notify_fail("You're too stunned to fight!\n");
    if (me->query_prop(LIVE_I_ATTACK_DELAY) || me->query_prop(LIVE_I_STUNNED))
        return 0;
    
    /* No enemy here! */
    notify_fail("You can't figh an enemy who isn't here!\n");
    if (!objectp(victim) || 
        (environment(me) != environment(victim))) 
        return 0;

    /* All is clear, proceed */    
    return 1;
}


/* special attacks code */
#include "lib/cloak_disarm.h"
#include "lib/double_punch.h"
#include "lib/hit_neck.h"
#include "lib/knife_pluck.h"
#include "lib/pommel_smash.h"
#include "lib/stun_kick.h"
#include "lib/dej_smash.h"

/* non-combat specials code */
#include "lib/non_combat.h"

/* emote code */
#include "lib/syb_emotes.h"

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Sybarite NPC soul"; }

/********************************************************************
 * The list of verbs and functions. 
 *******************************************************************/
public mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
    /* Combat specials */
         "cdisarm" : "cloak_disarm",
         "neck"    : "hit_neck",
         "pluck"   : "knife_pluck",
         "pommel"  : "pommel_smash",
         "punch"   : "double_punch",
         "skick"   : "stun_kick",
         "smash"   : "dej_smash",
    /* Non-combat specials */     
         "cure"    : "poison_cure",
         "heal"    : "health_heal",
    /* Emotes */
         "slaugh"  : "s_laugh",
	   ]);
}                   


