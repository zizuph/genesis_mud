/*
 * /d/Gondor/common/guild2/spells/attack_object.c
 *
 * Generic object for attack spells (using LIVE_O_SPELL_ATTACK)
 * 
 */
#pragma save_binary
#pragma strict_types

#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define DEBUG 0

int     damage_type;

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object me, object enemy)
{
    object *ob;
    int i;

    tell_room(ENV(me), str, ({ me, enemy, }));
}

/*
 * Function name: spell_success
 * Description:   Does the spell fail? Add skill checks etc here
 * Arguments:     attacker - we
 *                target - the attacked living.
 * Returns:       >=1 for success (output of resolve_task)
 */
int
spell_success(object attacker, object target)
{
    return 0;
}

/*
 * Function name: set_damage_type
 * Description: set the damage type this spell is of. Most spells would have 
 *              type MAGIC_DT, but a spell like magic missiles could be of 
 *              W_IMPALE type.
 * Arguments:	dt - The damage type
 */
void set_damage_type(int dt) { damage_type = dt; }

/*
 * Function name: query_damage_type
 * Returns: The damage type of this spell
 */
int query_damage_type() { return damage_type; }

/*
 * Function name: create_attack_spell
 * Description: Inheriting objects may redefine this.
 */
public void
create_attack_spell()
{
}

/*
 * Function name: create
 * Description: sets up defaults for global vars.
 */
nomask void
create()
{
    damage_type = MAGIC_DT;
    create_attack_spell();
}

/* Function name: cast_spell
 * Description:   Carry out the spell attack
 * Arguments:     str - argument of the spell
 *                ingr - array with ingredient names
 *                mana_cost - mana cost of spell
 *                min_level - minimum level to be able to cast this spell
 * Returns: 1 for success
 *          else reason for failure
 */
nomask mixed
cast_spell(string str, string *ingr, int mana_cost, int min_level)
{
    int     result;
    object *all,
           *ingr_arr,
            tp = this_player(),
            victim;
    string  fail;

    if (stringp(str))
    {
	all = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");
	if (sizeof(all))
	    victim = all[0];
    }

    if (!objectp(victim))
        victim = tp->query_attack();
    if (!objectp(victim))
        return "Cast the spell at whom?\n";	// no victim

    if (NPMATTACK(victim)) 
        return MORGUL_S_SPELL_FAIL;		// no magic attack allowed

    if (stringp(fail = MORGUL_SPELL_FILE->check_player(tp, ingr, mana_cost, min_level)))
        return fail;

    if (objectp(tp->query_prop(LIVE_O_SPELL_ATTACK)))
        return "You are already concentrating on another spell.\n";

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";
    
    if ((!F_DARE_ATTACK(tp, victim)) && (tp->query_attack() != victim))
	return "You do not dare to cast the spell.\n";

    ingr_arr = MORGUL_SPELL_FILE->find_ingr(ingr, tp);
    if (!(result = spell_success(tp, victim)))
    {
#if DEBUG
        tp->catch_msg("DEBUG attack_object: cast_spell failed - result = " + result + ".\n");
#endif
        tp->add_mana(-mana_cost / 3);
        MORGUL_SPELL_FILE->fail_cast(tp, ingr_arr);
        return 0;
    }
#if DEBUG
        tp->catch_msg("DEBUG attack_object: cast_spell succeeded - result = " + result + ".\n");
#endif
    tp->add_prop(MORGUL_I_SPELL_POWER, result);

    tp->add_mana(-mana_cost);
    MORGUL_SPELL_FILE->remove_ingr(ingr_arr);

    tp->attack_object(victim); /* This MUST be called! */
    tp->add_prop(LIVE_O_SPELL_ATTACK, this_object());

    return 1; /* Spell succeeded */
}

/*
 * Function name: spell_damage
 * Description:   this function should be redefined within the inheriting object.
 * Arguments:     attacker - we
 *                target - the attacked living.
 * Returns:       raw damage done to target, in hit points.
 */
int
spell_damage(object attacker, object target)
{
    return 0;
}

/* 
 * Function name: spell_resist 
 * Description:   this function should be redefined within the inheriting object.
 * Arguments:     target - the attacked living.
 * Returns:       Resistance of target to our spell, as percentage of damage avoided.
 */
int
spell_resist(object target)
{
    return 0;
}

/* 
 * Function name: spell_message 
 * Description:   this function should be redefined within the inheriting object.
 * Arguments:     attacker - we,
 *                target - the attacked living,
 *                phurt  - ratio of damage to current hp of target in %
 */
void
spell_message(object attacker, object target, mixed hitresult)
{
}

/*
 * Function name: spell_attack
 * Description:   this function is called from within the combat system.
 * Arguments:     attacker - we
 *                target - the attacked living.
 */
public void
spell_attack(object attacker, object target)
{
    int hurt;
    mixed *hitresult;
    string how;

    hurt = spell_damage(attacker, target);
    hurt -= hurt * spell_resist(target)/100;

    hitresult = target->hit_me(hurt, damage_type, attacker, -1);

    spell_message(attacker, target, hitresult);
#if DEBUG
    attacker->catch_msg("DEBUG attack object: damage " + hurt + "; phurt " + hitresult[0] + ".\n");
#endif
    attacker->remove_prop(MORGUL_I_SPELL_POWER);
  
    if (target->query_hp() <= 0)
        target->do_die(attacker);
}

/* Function name: kill_access
 * Description:   This is to filter out not killable things in the CMDPARSE
 *		  macro.
 * Arguments:     ob - Object to test
 * Returns:	  1 - keep object.
 */
int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == this_player())
	return 0;
    else
	return 1;
}

/*
 * Function name: query_mana_cost
 * Description:   the basic mana cost of the spell
 * Returns:       mana
 */
int
query_mana_cost()
{
    return 0;
}

void
notify_spell_enemy_gone(object target)
{
    // The spell fails because the target disappeared - restore mana.
    TP->add_mana(query_mana_cost());
    write("You have lost your target! Your spell is lost in the void!\n");
}
