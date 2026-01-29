/*
 * This is a draconian magician 
 *
 * Changes:
 *  000911: Stralle @ Genesis, increased their spellcraft skill so
 *          that their magic missile damage would not be too constant.
 *          If wearing a shield, one will take less damage when they die.
 *
 *  August 2018: Arman @ Genesis, updated to the new spellcasting system.
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "draconian.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Genesis/magic/spellcasting";
inherit DRACONIAN;

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

void get_me_soul();
int soul_id;

/*
 * Function name: set_bozak_skills
 * Description:
 * Arguments:
 * Returns:
 */
nomask static void
set_bozak_skills()
{
    int i, level;

    for (i = 0; i < 6; i++) /* 40 - 99 */
        set_base_stat(i, (random(5) + 3) * 13 + 1 + random(8));

    level = query_draconian_level();

    set_skill(SS_DEFENCE,     level * 6 + random(20) + 15);
    set_skill(SS_PARRY,       level * 6 + random(8) + 15);
    set_skill(SS_WEP_SWORD,   level * 6 + random(8) + 15);
    set_skill(SS_WEP_KNIFE,   level * 6 + random(8) + 15);
    set_skill(SS_WEP_CLUB,    level * 6 + random(8) + 15);
    set_skill(SS_WEP_POLEARM, level * 6 + random(8) + 15);
    set_skill(SS_WEP_JAVELIN, level * 6 + random(8) + 15);
    set_skill(SS_WEP_AXE,     level * 6 + random(8) + 15);
    set_skill(SS_AWARENESS,   level * 5);

    set_skill(SS_ELEMENT_FIRE, level * 6 + random(8) + 30);
    set_skill(SS_ELEMENT_AIR, level * 6 + random(8) + 30);
    set_skill(SS_FORM_CONJURATION, level * 6 + random(8) + 30);
    set_skill(SS_SPELLCRAFT, level * 6 + random(8) + 50);

    set_draconian_alignment();

}

/*
 * Function name: create_bozak
 * Description:
 */
public void
create_bozak()
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

    set_bozak_skills();
    set_draconian_type(BOZAK);

    create_bozak();

    add_name("bozak");

    set_exp_factor(145);
    add_prop(OBJ_I_RES_FIRE, 80);
    add_prop(OBJ_I_RES_ACID, 80);    

    /* 5% chance of cloning an acid arrow scroll */
    if(random(20) == 1)
    {
       clone_object("/d/Krynn/common/scrolls/acid_arrow_scroll")->move(TO);
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

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

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
    if(!random(3))
    {
        command("cast arcanisvaes");
        tell_room(environment(TO), QCTNAME(TO) + " slowly " +
            "raises " + TO->query_possessive() + " clawed hand.\n");
    }

    return 1;
}

/*
 * Function name: bozak_hurt_one
 * Desciption:    Hurt someone when a Bozak explodes.
 * Arguments:     who - The object to hurt.
 */
static void
bozak_hurt_one(object who)
{
    mixed *hit_result;
    int pen;
    string str;
    
    /* Hurting less if we wear a shield */
    pen = F_PENMOD(20 + random(10) -
        (objectp(who->query_armour(A_SHIELD)) ? random(20) : 0),
        query_draconian_level() * 5 + random(10));

    hit_result = who->hit_me(pen, W_IMPALE | W_SLASH, this_object(), -1);
    if (!sizeof(hit_result))
	return;

    switch (hit_result[0])
    {
        case 70..100:
            str = "multiple shards of bone that hits you hard";
            break;
        case 40..69:
            str = "some shards of bone, hitting you where it hurts";
            break;
        case 20..39:
            str = "shards of bone, that hits you";
            break;
        default:
            str = "shards of bone hitting you, barely hurting you";
            break;
    }

    tell_object(who, "You are struck by " + str + ".\n");

    if (who->query_hp() <= 0)
        who->do_die();

#ifdef 0
    object cb_obj = who->query_combat_object();
    int *hitlocs = cb_obj->query_hitloc_id();
    mixed *hloc, *ac;
    int i, hits, sum = 0;

    for (i = 0; i < sizeof(hitlocs); i++)
    {
        hloc = cb_obj->query_hitloc(hitlocs[i]);
        ac = hloc[0];

        if (!pointerp(ac))
            /* Set the impale (= 0) hitlocation value; Shards impale! */
            ac = ({ ac });

        /* hloc[1] is the percentage of the hits for the location */
        sum += hloc[1] * ac[0];
    }

    sum /= 100;  /* The sum of perc_hit = 100 */
    hits = - query_draconian_level() * random(50) - 50;
    hits -= sum;
    /* Hurt less if we are wearing a shield */
    hits += (objectp(who->query_armour(A_SHIELD)) ? random(100) : 0);
    hits = ((hits > 0) ? 0 : hits);

    /* We are very friendly here! Especially so newbies won't die 
     * just TOO fast... 
     */
    if (who->query_hp() < hits)
        hits = -random(who->query_hp() + 1);

    who->heal_hp(hits);
    tell_object(who, "You are struck by shards of bone. " + 
        ((hits >= 0) ? "You are not harmed though.\n" :
        "Ouch, that hurts.\n"));

    if (!who->query_ghost())
        who->do_die(TO);
#endif
}

/*
 * Function name: second_life
 * Description:
 * Arguments:     killer - 
 * Returns:
 */
public int
second_life(object killer)
{
    int i;
    object *things;

    tell_watcher("The skin and flesh of the draconian dries out and " +
        "crumbles from the bones!\n");
    tell_room(E(TO),"BANG! The bones of the draconian explode!\n");

    things = all_inventory(E(TO));
    i = sizeof(things);

    while (i--)
        if (!things[i]->query_ghost() && things[i]->query_prop(LIVE_I_IS) && 
            (things[i] != TO) && !(QRACE(things[i]) == "draconian"))
            /* Don't hurt myself :-) I'm dead, right? */
            bozak_hurt_one(things[i]);
}
