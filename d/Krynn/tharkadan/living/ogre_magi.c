/*
 * Coded by Arman Mar 2017
 *
 * A powerful ogre magi who is capable of casting a number of spells:
 *           omens and portents (greater evade spell)
 *           scouring winds (lesser harm spell)
 *           ballistic spray (at will harm spell)
 *           dazzle (slow spell)
 *           gravity (negative featherweight spell)
 *
 * Can also summon up to five winter wolves to assist him in battle.
 * Each wolf vanishes after 75 seconds. 
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit M_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

#define TRINKET  ARMOUR + "ogre_trinkets"
#define ARM1     ARMOUR + "ogre_leather"
#define ARM2     ARMOUR + "magi_robe"

#define STAFF      WEP + "ironwood_staff"
#define MAG_STAFF  WEP + "magic_ironwood_staff"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"


int st_bonus = random(50);
object trinket1, trinket2, key, robe, wolf;
void get_me_soul();
int soul_id, wolf_count;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"wolf"}));
    set_max_team_size_auto_join(6);

    set_name("ogre");
    add_name("magi");
    set_adj("cunning");
    set_race_name("ogre");
    set_short("cunning ogre magi");
    set_long("Before you stands an ogre of the Tharkadan mountain " +
       "barbarian tribes, although no ordinary ogre - an ogre magi! " +
       "One of the rare legendary ogre mages of Ansalon, they combine " +
       "the strength and constitution of their ogre brethren with " +
       "the intelligence and cunning of a wizard. They are not a foe " +
       "to be taken lightly!\n");

    set_appearance(-75);

    set_stats(({200 + st_bonus, 200 + st_bonus, 300 + st_bonus, 
                300 + st_bonus, 300 + st_bonus, 200 + st_bonus}));

    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(CONT_I_HEIGHT, 300 + random(100));
    add_prop(CONT_I_WEIGHT, 400000 + random(300000));
    add_prop(CONT_I_VOLUME, 420000 + random(300000));
  
    add_prop(LIVE_I_SEE_DARK, 5);

    // minor resistance to cold
    add_prop(OBJ_I_RES_COLD, 15);
    add_prop(OBJ_I_RES_POISON, 25);

    set_alignment(-1150);
    set_knight_prestige(200);

    set_skill(SS_WEP_POLEARM, 70 + random(30));
    set_skill(SS_DEFENSE, 70 + random(30));
    set_skill(SS_PARRY, 40 + random(60));
    set_skill(SS_AWARENESS, 70 + random(30));
    set_skill(SS_BLIND_COMBAT, 30 + random(70));
    set_skill(SS_SPELLCRAFT, 90);
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

    // Good natural armour and spells
    set_exp_factor(135);

    set_act_time(10);
    add_act("say Why are you here?");
    add_act("emote raises a warty hand towards the burning brazier.");
    add_act("emote concentrates while tracing arcane runes in the air.");
    add_act("emote traces arcane runes in the air while throwing some " +
       "dark powder into the flaming brazier.");

    set_cact_time(10);
    add_cact("emote rises up ominously to his full height.");
    add_cact("say Fool! You know not my might!");

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

    clone_unique(MAG_STAFF, 15, STAFF)->move(this_object(),1);
    command("wield all");

    trinket1 = clone_object(TRINKET);
    trinket1->make_the_trinket();
    trinket1->move(TO, 1);
    trinket2 = clone_object(TRINKET);
    trinket2->make_the_trinket();
    trinket2->move(TO, 1);

    clone_object(TOBJ + "chest_key")->move(TO, 1);     
    clone_object(ARM1)->move(TO, 1);

    robe = clone_object(ARM2);
    robe->random_set_color();
    robe->move(TO, 1);

    command("wear all");
}

/* Added so that special attack function manages the spell rotations */
public int
no_repeat_harm_spell()
{
    return 1;
}

void
dispel_wolf(object wolf)
{
   if(objectp(wolf))
   {
      tell_room(environment(wolf), "The summoning of the ogre magi " +
         "ends, and the " +wolf->query_short()+ " disappears.\n", 
         ({ TO }), TO);
      wolf->remove_object();
    }
   return;
}

int
special_attack(object enemy)
{
    int     attacktype = random(6);
    int     switchspell = random(4);
 
    if (attacktype == 0 || attacktype == 1)
    {
       if(!("/d/Krynn/guilds/sohm/spells/portents_and_omens"->has_spell_object(TO)))
       {
         // Cast the portents and omens if not in effect
          command("xiekxilunwai");
          return 1;
       }
       if(switchspell == 1)
          command("iniksuaco");
       else if(switchspell == 2)
          command("haddross");
       else
          command("tonashingis");
       return 1;
    }
    if (attacktype == 2)
    {
       if(random(2) && random(2))
       {
        if(!objectp(wolf) && (wolf_count < 5))
        {
           seteuid(getuid(this_object()));
           command("emote raises his hands and summons a beast to do " +
               "his bidding!");
           wolf = clone_object(LIVING + "winter_wolf");
           wolf->move(E(TO), 1);
           wolf->command("kill " +enemy->query_real_name());
           set_alarm(75.0, 0.0, &dispel_wolf(wolf));
           wolf_count = wolf_count + 1;
        }
        return 1;
       }
    }
    return 0;
}

void
attack_intruder(object enemy, string race)
{
    if(!CAN_SEE(TO, enemy))
    {
	return;
    }

    if(TO->query_attack())
      return;

    command("say I warned you " +race+ "! Feel my wrath!");
    command("kill " +enemy->query_real_name());
    command("okiai");
    return;
}

void
prepare_spells(object enemy, string race)
{
    if(enemy->query_npc())
        return;

    if(!CAN_SEE(TO, enemy))
    {
        command("emote narrows his eyebrows suspiciously.");
        command("say Hidden intruder, you should leave. Now.");
        command("vistoma");
        set_alarm(15.0, 0.0, &attack_intruder(TP, race));
	return;
    }

    command("say to " +enemy->query_real_name()+ " You shouldn't be " +
        "here. Leave before you feel my wrath.");
    command("xiekxilunwai");
    set_alarm(15.0, 0.0, &attack_intruder(TP, race));
    return;
}

void 
init_living() 
{
    string race_name = TP->query_race_name();
    set_alarm(1.0, 0.0, &prepare_spells(TP, race_name));
 
    ::init_living(); 
}