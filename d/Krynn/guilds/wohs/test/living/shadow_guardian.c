/*
 * Coded by Arman Jan 2018
 * Npc for the WoHS test
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit M_FILE

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define DMG_TAKEN       "_wohs_test_damage_taken"

void get_me_soul();
int soul_id, max_hp;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("guardian");
    add_name("shadow");
    set_adj("guardian");
    set_race_name("shadow");
    set_short("shadowy guardian");
    set_long("Strangely, this guardian looks nothing other than a " +
        "black shadow of you!\n");
    set_appearance(0);
    set_stats(({120, 120, 120, 120, 120, 120}));

    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
  
    add_prop(LIVE_I_SEE_DARK, 5);

    // resistance to magic, vulnerability to illusion
    add_prop(OBJ_I_RES_FIRE, 40);
    add_prop(OBJ_I_RES_ACID, 40);
    add_prop(OBJ_I_RES_COLD, 40);
    add_prop(OBJ_I_RES_WATER, 40);
    add_prop(OBJ_I_RES_EARTH, 40);
    add_prop(OBJ_I_RES_AIR, 40);
    add_prop(OBJ_I_RES_ILLUSION, -100);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_alignment(0);
    set_knight_prestige(0);

    set_skill(SS_DEFENSE, 60);
    set_skill(SS_PARRY, 40);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_BLIND_COMBAT, 30 + random(70));
    set_skill(SS_SPELLCRAFT, 90);
    set_skill(SS_UNARM_COMBAT, 90);	
    set_skill(SS_FORM_ENCHANTMENT, 90);
    set_skill(SS_FORM_CONJURATION, 90);
    set_skill(SS_FORM_DIVINATION, 90);
    set_skill(SS_FORM_ABJURATION, 90);
    set_skill(SS_FORM_ILLUSION, 90);
    set_skill(SS_FORM_TRANSMUTATION, 90);
    set_skill(SS_ELEMENT_FIRE, 90);
    set_skill(SS_ELEMENT_EARTH, 90);
    set_skill(SS_ELEMENT_WATER, 90);
    set_skill(SS_ELEMENT_AIR, 90);

    set_all_hitloc_unarmed(50);

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
    add_cmdsoul("/d/Genesis/specials/guilds/shadows/mana_shadow");
    update_hooks(); 
    remove_alarm(soul_id);
}

void 
arm_me()
{
    seteuid(getuid(this_object()));

}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}


int
special_attack(object enemy)
{
    int     attacktype = random(5);
    int     switchspell = random(3);
 
    if (attacktype == 0 || attacktype == 1)
    {
       if(switchspell == 1)
          command("ricindenthanus");
       else
          command("reelojawa");
       return 1;
    }

    return 0;
}

public void
attack_object(object ob)
{
    max_hp = ob->query_hp();
    //DEBUG("Max hp called in attack_object");

    ::attack_object(ob);
}

public void
attacked_by(object ob)
{
    max_hp = ob->query_hp();
    //DEBUG("Max hp called in attacked_by");

    ::attacked_by(ob);
}

public void
do_die(object killer)
{
    int hp = killer->query_hp();
    int dmg_taken = killer->query_prop(DMG_TAKEN);

    dmg_taken = dmg_taken + (max_hp - hp);

    //DEBUG("Max hp: "+ max_hp+ ", hp: "+ hp);
    //DEBUG("Damage taken to "+ killer->query_real_name()+ " "+ dmg_taken);
    killer->add_prop(DMG_TAKEN, dmg_taken);
    SOHM_MANAGER->add_wohs_test_props(killer, DMG_TAKEN, dmg_taken);

    ::do_die(killer);
}

