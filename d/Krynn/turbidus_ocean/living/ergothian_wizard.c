/*
 * Coded by Arman Jan 2021
 *
 * An Ergothian sailor-wizard capable of the following spells:
 *           retributive ward (greater evade spell)
 *           lightning bolt (lesser harm spell)
 *           ice shard (at will harm spell)
 *           light spell
 *           blink spell
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit M_FILE
inherit "/lib/unique";

#define MAGIC_WAND      TOBJ + "wand_ice"
#define WAND            "/d/Krynn/solace/poolbottom/obj/wand"
#define MAGIC_ROBE      TOBJ + "ergothian_robe"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define ATTACKED_ERGOTHIANS "_attacked_ergothian_sailors"

void get_me_soul();
int soul_id;
object wand;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("battlemage");
    add_name("mage");
    add_name("_ergothian_sailor");
    set_adj("royal");
    add_adj("ergothian");
    set_race_name("human");
    set_short("royal Ergothian battlemage");
    set_long("Before you stands a grizzled battlemage of the royal " +
        "Ergothian navy. Uncommon on your average merchant vessel, " +
        "these battlemages are usually only seen on ships guarding " +
        "noble members of the royal Ergothian family or very valuable " +
        "cargo.\n");

    set_appearance(15);

    set_stats(({180, 180, 220, 250, 250, 250}));

    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(CONT_I_HEIGHT, 170 + random(10));
    add_prop(CONT_I_WEIGHT, 70000 + random(30000));
    add_prop(CONT_I_VOLUME, 70000 + random(30000));

    set_alignment(0);
    set_knight_prestige(0);

    set_skill(SS_WEP_POLEARM, 70 + random(30));
    set_skill(SS_DEFENSE, 70 + random(30));
    set_skill(SS_PARRY, 40 + random(60));
    set_skill(SS_AWARENESS, 70 + random(30));
    set_skill(SS_BLIND_COMBAT, 30 + random(70));
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_FORM_ENCHANTMENT, 90);
    set_skill(SS_FORM_CONJURATION, 90);
    set_skill(SS_FORM_DIVINATION, 90);
    set_skill(SS_FORM_ABJURATION, 90);
    set_skill(SS_FORM_ILLUSION, 90);
    set_skill(SS_FORM_TRANSMUTATION, 90);
    set_skill(SS_ELEMENT_FIRE, 90);
    set_skill(SS_ELEMENT_EARTH, 90);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_AIR, 100);

    set_all_hitloc_unarmed(30);

    // Good natural armour and very good spells
    set_exp_factor(135);

    set_act_time(20);
    add_act("emote gazes across the deck for pirate raiders.");
    add_act("say These pirates are brazen!");
    add_act("emote traces arcane runes in the air.");
    add_act("say The treasures of the ruins of Daltigoth will not " +
        "fall in to pirate hands!");
    add_act("say The winds foil us! We won't get to Gywnned before " +
        "solstice at this rate!");

    set_cact_time(10);
    add_cact("emote mutters a curse in Ergothian.");
    add_cact("assist");

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

    object robe;
    robe = clone_unique(MAGIC_ROBE, 15, 0);

    wand = clone_unique(MAGIC_WAND, 15, WAND);
    wand->move(this_object(), 1);
    command("hold wand");

    if(objectp(robe))
        robe->move(this_object(), 1);

    command("wear all");
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

    // If he can't see he casts light spell if not in effect
    if(!CAN_SEE_IN_ROOM(TO))
    {
       if(!("/d/Krynn/guilds/sohm/spells/light_spell"->has_spell_object(TO)))
       {
          command("shirak");
          return 1;
       }
    }

    // Activate blink spell if not active.
    if(!("/d/Krynn/guilds/sohm/spells/blink"->has_spell_object(TO)))
    {
        command("ripeidronik");
        return 1;
    }
 
    if (attacktype == 0 || attacktype == 1)
    {
        object * effects = TO->query_prop("_live_o_maintained_effects");

        foreach (object effect : effects)
        {
            if (objectp(effect))
            {
                if (environment(effect)->query_prop("_sohm_retributive_ward_effect") != 
                   "battlemage")
                {
                    // Cast the retributive ward spell if not in effect
                    command("viraxregpos");
                    return 1;
                 }
             }
        }

       // Lightning bolt, ice shard
       if(switchspell == 1)
          command("shochraos");
       else
          command("xarzithinloilfrey");
       return 1;
    }

    if(objectp(wand))
        if(wand->id("ivory wand"))
          command("freeze");

    return 0;
}

void
prepare_spells(object enemy)
{
    if(enemy->query_npc())
        return;

    // If he can't see he casts light spell
    if(!CAN_SEE_IN_ROOM(TO))
    {
        command("emote narrows his eyebrows suspiciously.");
        command("shirak");
	return;
    }

    // Casts retributive ward when someone enters the room.
    command("viraxregpos");
    return;
}

void
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(ATTACKED_ERGOTHIANS))
        ob->add_prop(ATTACKED_ERGOTHIANS, 1);
}

void
attack_enemy_again(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        return;
    }

    if(!random(3))
        command("say More intruders Captain Geral! Time to repel!");
    command("kill " +enemy->query_name());
    return;
}

void
attack_enemy(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        set_alarm(6.5, 0.0, &attack_enemy_again(enemy));
        return;
    }

    if(!CAN_SEE_IN_ROOM(TO))
    {
        command("say Pirates! We need light!");
        return;
    }

    
    if(!random(3))
        command("say More intruders Captain Geral! Time to repel!");
    command("kill " +enemy->query_name());
    return;
}

void 
init_living() 
{
    set_alarm(0.5, 0.0, &prepare_spells(TP));

    if(this_player()->query_prop(ATTACKED_ERGOTHIANS))
        set_alarm(3.5, 0.0, &attack_enemy(this_player()));

    ::init_living(); 
}