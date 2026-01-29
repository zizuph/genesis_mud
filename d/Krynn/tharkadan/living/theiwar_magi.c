/*
 * Coded by Arman July 2017
 *
 * A powerful Theiwar dark savant who is capable of casting a number of 
 * spells
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

#define BODY1      ARMOUR + "theiwar_leather"
#define HELM       ARMOUR + "theiwar_helm"
#define GREAVES    ARMOUR + "theiwar_greaves"
#define MAG_GAUNT  ARMOUR + "umberhulk_bracers"
#define GAUNT      ARMOUR + "theiwar_gauntlets"
#define ROBE       ARMOUR + "grey_robe"

#define STAFF      WEP + "bone_staff"
#define MAG_STAFF  WEP + "staff_of_skulls"

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define DARK_DWARF_ENEMY  "_dark_dwarf_enemy_"

void get_me_soul();
int soul_id;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({ "dark_dwarf" }));
    set_max_team_size_auto_join(8);

    set_name("vosil");
    add_name("dwarf");
    add_name("lord");
    add_name("savant");
    add_name("dark_dwarf");
    set_living_name("vosil");
    set_title("Grudgeback, Savant Lord of the Obsidian Circle");
    set_race_name("dwarf");
    set_adj("cunning");
    add_adj("dwarven");
    add_adj("savant");
    set_short("cunning dwarven savant lord");
    set_gender(G_MALE);
    set_long("Before you stands the leader of the dark savants of the " +
          "Theiwar clan, the Savant Lord of the Obsidian Circle! " +
          "Skilled in the Dark Arts, this is an advisary not to be " +
          "taken lightly!\n");

    set_appearance(-75);
    set_stats(({160,240,360,360,320,300}));

    set_hp(10000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
 
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_ATTACK_THIEF, 1);

    // minor resistance to cold
    add_prop(OBJ_I_RES_COLD, 15);
    add_prop(OBJ_I_RES_POISON, 15);

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

    set_all_hitloc_unarmed(15);

    set_act_time(25);
    add_act("rsay A Theiwar will be the next High King of Thorbardin. " +
        "And I will be the puppet master pulling the strings!");
    add_act("emote looks at you with deep suspicion and distrust.");
    add_act("rsay Embracing the Dark Arts was the greatest event in the " +
        "history of the Theiwar clan...");
    add_act("rsay The Obsidian Circle grows stronger! Soon we will " +
        "challenge even the numbers of the Wizards of High Sorcery!");

    set_cact_time(25);
    add_cact("rsay By the Devouring Darkness, you will not walk away " +
        "from this battle!");
    add_cact("rsay The tortures I will put you through!");
    add_cact("rsay Slay the intruder!");

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
   
    clone_object(BODY1)->move(TO,1);
    clone_object(HELM)->move(TO,1);
    clone_object(ROBE)->move(TO,1);
    clone_object(GREAVES)->move(TO,1);
    clone_unique(MAG_GAUNT, 10, GAUNT)->move(this_object(),1);

    command("wear all");

    clone_object(TOBJ + "black_disk")->move(TO, 1);
}

void
return_intro()
{
    command("introduce myself");
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(1.0, 0.0, return_intro);
    }
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
    int     switchspell = random(4);
 
    if (attacktype == 0 || attacktype == 1)
    {
       if(!("/d/Krynn/guilds/sohm/spells/reflect_damage"->has_spell_object(TO)))
       {
         // Cast the retributive ward spell if not in effect
          command("viraxregpos");
          return 1;
       }
       if(!("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(TO)))
       {
         // Cast the greater magic shield if not in effect
          command("jennufethos");
          return 1;
       }
       if(switchspell == 1)
          command("tonashkepesk"); // Meteor storm spell
       else if(switchspell == 2)
          command("edarvirednith"); // Eruption spell
       else
          command("tonashingis"); // Ballistic spray spell
       return 1;
    }

    return 0;
}

void
attack_func(object enemy)
{
    if ( !CAN_SEE(TO, enemy) )
    {
        if ( !random(2) )
            command("curse");

	return;
    }
    
    command("shout Scum! Die ye bastard!");
    action_attack(enemy);
}

void
init_living()
{
    ::init_living();
    init_team_pickup();  

    int light_level = E(TO)->query_prop(OBJ_I_LIGHT);

    if(light_level > 0)
    {
        if(light_level > random(10))
        {
           if(random(2))
             command("emote is dazzled by the bright light.");
           else
             command("emote winces in pain at the light.");
        }
    }

    if ( TP->query_prop(DARK_DWARF_ENEMY) )
    {
	set_alarm(0.5, 0.0, &attack_func(TP));
        return;
    }
    
}
