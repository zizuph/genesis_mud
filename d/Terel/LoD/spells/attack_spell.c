/*
 * attack_spell.c
 *
 * Inheriting objects should redefine:
 *
 * spell_fail()
 * spell_damage()
 * spell_resist()
 * spell_message()
 *
 */
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>

int damage_type;    /* Type of damage this spell does. */
int mana;           /* How much mana the spell costs */

/*
 * Prototype
 */
void tell_watcher(string str, object me, object enemy);

/*
 * Function Name: set_mana_cost
 * Description: Sets the mana cost for this spell.
 */
public void
set_mana_cost(int m)
{
    mana = m;
}

/*
 * Function Name: query_mana_cost
 * Returns: the mana cost for this spell.
 */
public int
query_mana_cost()
{
    return mana;
}

/*
 * Function name: set_damage_type
 * Description: set the damage type this spell is of. Most spells would have
 *              type MAGIC_DT, but a spell like magic missiles could be of
 *              W_IMPALE type.
 * Arguments:   dt - The damage type
 */
public void
set_damage_type(int dt)
{
    damage_type = dt;
}

/*
 * Function name: query_damage_type
 * Returns: The damage type of this spell
 */
public int
query_damage_type()
{
    return damage_type;
}

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
    mana = 10;
    create_attack_spell();
}

/*
 * Function name: spell_fail
 * Description: This function should be redefined to perform a test for
 * success.
 *    It should also generate appropriate success messages.
 * Returns: 1 if the spell fails, 0 for success.
 */
public int
spell_fail()
{
    return 0;
}

/* Function name: do_spell
 * Description:   Carry out a generic attack spell.
 * Arguments:     str - string describing the enemy
 * Returns: 0 for success
            1 -- No target found
            2 -- Player is a ghost
            3 -- No magical attacks allowed on target
            4 -- not enough discipline to attack target
            5 -- Not enough mana to cast spell
            6 -- Spell attempted and failed.
 */
nomask int
do_spell(string str)
{
    object obj, *a;

    if (str)
    {
        a = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");
        if (sizeof(a))
            obj = a[0];
    }
    if (!obj)
        obj = this_player()->query_attack();
    if (!obj)
        return 1;  /* No target*/

    if (this_player()->query_ghost())
        return 2;  /* ghost */

    if (NPMATTACK(obj))
        return 3;  /* No magic attacks allowed */

    if (!F_DARE_ATTACK(this_player(), obj))
        return 4;  /* Don't dare */

    if (this_player()->query_mana() < mana)
        return 5;  /* Not enough mana */

    if (spell_fail())
    {
        this_player()->add_mana(-mana / 3);
        return 6;  /* Spell attempted and failed. */
    }

    this_player()->add_mana(-mana);
    
    if (this_player()->query_npc())
        this_player()->set_spell_prop(this_object());
    else
        this_player()->add_prop(LIVE_O_SPELL_ATTACK, this_object());

    this_player()->attack_object(obj);

    return 0; /* Spell succeeded */
}

/*
 * Function name: spell_damage
 * Description: this function should be redefined within the inheriting object.
 * Arguments: 'target' the attacked living.
 * Returns: raw damage done to target, in hit points.
 */
public int
spell_damage(object attacker, object target)
{
    return 10;
}

/*
 * Function name: spell_resist
 * Description: this function should be redefined within the inheriting object.
 * Arguments: 'target' the attacked living.
 * Returns: Resistance of target to our spell, as percentage of damage avoided.
 */
public int
spell_resist(object target)
{
    return 0;
}

/*
 * Function name: spell_message
 * Description: this function should be redefined within the inheriting object.
 * Arguments: 'target' the attacked living.
 *            'phurt' the percentage of remaining hp the attack did to target.
 */
public void
spell_message(object attacker, object target, int phurt)
{
}

/*
 * Function name: spell_attack
 * Description: this function is called from within the combat system.
 * Arguments: 'attacker' -- the player doing the attacking
 *            'target'   -- the player about to get hurt.
 */
public void
spell_attack(object attacker, object target)
{
    int hurt;
    mixed *hitresult;

    hurt = spell_damage(attacker, target);
    hurt -= (hurt * spell_resist(target))/100;
    if (hurt <   0) hurt = 0;
    if (hurt > 100) hurt = 100;

    hitresult = target->hit_me(hurt, damage_type, attacker, -1);

    spell_message(attacker, target, hitresult[0]);

    if (target->query_hp() <= 0)
        target->do_die(attacker);
    
    if (attacker->query_npc())
        attacker->delay_set_spell_prop(attacker);
}

/* Function name: kill_access
 * Description:   This is to filter out not killable things in the CMDPARSE
 *                macro.
 * Arguments:     ob - Object to test
 * Returns:       1 - keep object.
 */
public int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == this_player())
        return 0;
    else
        return 1;
}

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
void
tell_watcher(string str, object me, object enemy)
{
    object *ob;
    int i;

    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD))
            ob[i]->catch_msg(str);
}
