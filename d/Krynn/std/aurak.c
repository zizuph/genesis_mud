/*
 * This is an Aurak spellcasting draconian 
 *
 *  September 2018: Arman @ Genesis, updated to the new spellcasting system.
 *  Can utilise three spells... a blast of damaging flame, a mind control stun,
 *  and a disarm spell. The spell code can be found in 
 *  /d/Krynn/guilds/sohm/spells/ as aurak_flame_spell.c, aurak_disarm_spell.c
 *  and dominate.c
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "draconian.h"
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Genesis/magic/spellcasting";
inherit DRACONIAN;

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

void get_me_soul();
int soul_id;
static int gAurak_died = 0;

/*
 * Function name: set_aurak_skills
 * Description:   Calc and set the stats and skills for the draconian.
 */
nomask static void
set_aurak_skills()
{
    int i, level;

    for (i = 0; i < 6; i++) /* 108 - 172 */
        set_base_stat(i, (random(6) + 7) * 12 + 24 + random(5));

    level = query_draconian_level();

    set_skill(SS_2H_COMBAT,             90 + random(11));
    set_skill(SS_DEFENCE,               level * 6 + random(20) + 15);
    set_skill(SS_PARRY,                 level * 6 + random(8) + 15);
    set_skill(SS_WEP_SWORD,             level * 6 + random(8) + 15);
    set_skill(SS_WEP_KNIFE,             level * 6 + random(8) + 15);
    set_skill(SS_WEP_CLUB,              level * 6 + random(8) + 15);
    set_skill(SS_WEP_POLEARM,           level * 6 + random(8) + 15);
    set_skill(SS_WEP_JAVELIN,           level * 6 + random(8) + 15);
    set_skill(SS_WEP_AXE,               level * 6 + random(8) + 15);
    set_skill(SS_ELEMENT_FIRE,          level * 6 + random(8) + 15);
    set_skill(SS_FORM_CONJURATION,      level * 6 + random(8) + 15);
    set_skill(SS_ELEMENT_WATER,         level * 6 + random(8) + 15);
    set_skill(SS_FORM_ENCHANTMENT,      level * 6 + random(8) + 15);
    set_skill(SS_AWARENESS,   level * 5);

    set_draconian_alignment();
}

/*
 * Function name: create_aurak
 * Description:
 */
public void
create_aurak()
{
}

/*
 * Function name: create_draconian
 * Description:
 */
nomask public void
create_draconian()
{
    int i;

    set_aurak_skills();
    set_draconian_type(AURAK);
    set_smart_fighting();

    create_aurak();

    if (!query_long())
        set_default_long();

    set_name("aurak");

    set_exp_factor(160);
    add_prop(OBJ_I_RES_FIRE, 100);
    add_prop(OBJ_I_RES_ACID, 100);    
    add_prop(LIVE_I_SEE_DARK, 3);

    /* 20% chance of cloning a flame lance scroll */
    if(random(5) == 1)
    {
       clone_object("/d/Krynn/common/scrolls/flame_lance_scroll")->move(TO);
       seteuid(getuid(TO));
    }

    clone_object(MANA_SHADOW)->shadow_me(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    seteuid(getuid());
}

void
get_me_soul()
{
    add_cmdsoul(SOHM_SOUL);
    add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    add_cmdsoul(SPELL_MANAGER_SOUL);
    add_cmdsoul(MANA_SHADOW);
    update_hooks(); 
    remove_alarm(soul_id);
}

/* If anyone is up for selecting the best of weapons available in
 * our inventory for wielding, go ahead. :)
 *
 * There are eight different possobilities. Wielding either of one
 * single handed weapon, two single handed weapons or a two-handed
 * weapon. Then one can pick up any of those. 2^3 combinations makes
 * 8. What to unwield if any and what to wield if any.
 */
#ifdef 0
object
query_best_weapon(object *arr)
{
    object wep = arr[0];
    int x = 0, size = sizeof(arr);
    
    while (++x < size)
    {
        if ((arr[x]->query_hit() + arr[x]->query_pen()) >
            (wep->query_hit() + wep->query_pen()))
        wep = arr[x];
    }

    return wep;
}

void
check_best_weapon()
{
    object *weps, *arr = all_inventory(this_object());
    int x = -1, size;

    arr = filter(arr, &operator(==)(1) @ &->check_weapon());

    size = sizeof(arr);
    if (!size)
        return;

    switch (sizeof(query_weapon(-1)))
    {
        case 2:
            /* We wield two weapons */
            while (++x < size)
                if (sizeof(arr))
                {
                    weps += ({ query_best_weapon(arr) });
                    arr -= ({ weps[sizeof(weps) - 1] });
                }

            break;
        case 1:
            /* We wield one weapon */
            if ((query_weapon(-1)[0])->query_hands() == W_BOTH)
                weps += ({ query_best_weapon(arr) });
            else
            {
                while (++x < size)
                    if (sizeof(arr))
                    {
                        weps += ({ query_best_weapon(arr) });
                        arr -= ({ weps[sizeof(weps) - 1] });
                    }
            }

            break;
        case 0:
            /* We wield no weapons */
            while (++x < size)
                if (sizeof(arr))
                {
                    weps += ({ query_best_weapon(arr) });
                    arr -= ({ weps[sizeof(weps) - 1] });
                }

            break;
    }

    for (x = 0, size = sizeof(weps) ; x < weps ; x++)
    {
        if (member_array(weps[x], query_weapon(-1)) >= 0)
            weps = exclude_array(weps, x, x);
    }
    
    if (!sizeof(weps))
        return;
}
/*    switch (*/
#endif            

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object victim)
{
    if(!random(4))
    {
        command("cast aurakfire");
        return 1;
    }

    if(!random(3))
    {
        command("cast reelojawa");
        return 1;
    }

    if(!random(4))
    {
        command("cast aurakdisarm");
        return 1;
    }

    return 0;
}

public void
notify_death(object killer)
{
    ::notify_death(killer);
    
    if (gAurak_died)
    {
        tell_room(environment(TO), "The remains of the draconian slowly " +
            "start to rise upwards and turn into clouds.\n");
    }
}
        
/*
 * Function name: do_draconian_die
 * Description:   This happens when an Aurak dies.
 * Arguments:     killer - The object who killed it
 */
public void
do_draconian_die(object killer)
{
    object *dummy, corpse;

    /* This should never happen but guards from bugabusing if it
     * should happen.
     */
    if (gAurak_died > 1)
        return;

    if (!killer)
        killer = previous_object();

    if (!query_combat_object())
        combat_reload();

    if (gAurak_died)
    {
        gAurak_died++;

        setuid();
        seteuid(getuid());
        
        corpse = clone_object(LIGHTNING);
        corpse->set_my_victims(query_enemy(-1));
        corpse->move(environment(this_object()));
        return;
    }
    else
    {
        gAurak_died++;

        tell_room(E(TO), QCTNAME(TO) + " died.\n", TO);
        killer->catch_msg("You killed " + QTNAME(TO) + ".\n");
        killer->notify_you_killed_me(this_object());

        tell_room(E(TO),
            "No! The draconian is still alive and goes berserk!\n");

        add_tmp_stat(0, 100, 1);
        add_tmp_stat(1, 90, 1);
        add_tmp_stat(2, 10, 1);
        add_tmp_stat(3, -50, 1);
        add_tmp_stat(4, -50, 1);
        add_tmp_stat(5, 100, 1);
        heal_hp(350);
        return;
    }
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
