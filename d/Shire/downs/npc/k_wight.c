/*
 *  Ghast in the barrow downs
 *  The randomize func's are originally Rogon's
 *  Cloned by ~Shire/common/downs/stone4*.c
 *
 *  Modified a little by Odin, 9. March 1994
 *
 *  The king wight for the cleans the barrow quest
 *  By finwe, January 2002
 */

inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/make_money.h"

string crown_descr = "is made of white gold, with a hammered look";
string crown_num = "_shire_crown_1_";

int alarm_id;

void add_stuff();

create_monster()
{
    set_short("terrible barrow wight");
    set_name("wight");
    add_name ("terrible wight");
    add_name ("terrible barrow wight");
    add_name ("barrow wight");

    set_race_name("wight");
    if (!IS_CLONE)
      return;
   
    set_long("This is a "+short()+". It is more terrible then all " +
        "the other wights both in size and stature. It looks like " +
        "it was once a great king, and commands still, even in " +
        "its current state. Its dark eye sockets are cruel as they " +
        "bore into your soul, feeding on your deepest fears.\n");

    add_prop(CONT_I_WEIGHT,70000);   /* 70 kg  */
    add_prop(CONT_I_HEIGHT,180);     /* 180 cm */
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
    add_prop(LIVE_I_UNDEAD, 38);      /*Is an undead*/
    add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
    add_prop("_ranger_i_not_blind",1);

            /*   STR  DEX  CON INT WIS DIS */
    set_stats(({ 125, 120, 120, 71, 34, 89}));
    set_alignment(-900 - random (100));
    set_skill(SS_UNARM_COMBAT, 90 + random(8));
    set_skill(SS_WEP_SWORD, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));
    set_skill(SS_PARRY, 80+random(20));
    set_skill(SS_BLIND_COMBAT, 80+random(20));
    set_skill(SS_AWARENESS, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));

    set_aggressive(99);
    set_attack_chance(99);

    set_hp(900); /* Heal fully */

    set_act_time(15+random(30));
    add_act("emote hisses: Kneeeel bevore me, puny mortal!");
    add_act("emote hisses something unintelligible at you.");
    add_act("emote hisses: Ahhh, I shall have your soul...");
    add_act("emote hisses: Sooo good to seee you...");
    add_act("emote hisses: Come, and I sshall make youuu grreat.");
    add_act("emote looks you up and down, smiling evilly.");
    add_act("emote smiles evilly at you.");
    add_act("emote hisses at you.");

    set_cact_time(15+random(30));
    add_cact("emote howls devilishly at you.");
    add_cact("emote hisses: I sshall veast on your corpse.");
    add_cact("emote hisses: Soon I shall chew your bones!!");
    add_cact("emote reaches out and chills you to the bone with a " +
        "skeletal hand.");
   alarm_id = set_alarm(2.0,0.0,&add_stuff());


   
    MAKE_MONEY;
    make_gold(5+random(9));
}

add_stuff()
{
	object sword, plate, money, crown;

    FIXEUID;

    remove_alarm(alarm_id);
	sword	= clone_object(DOWNS_WEP +"w_sword");
	sword->move(this_object());

	plate = clone_object(DOWNS_ARM +"w_plate");
	plate->move(this_object());	

    crown = clone_object("/d/Shire/downs/obj/crown");
//    crown->add_name(crown_num);
    crown->move(this_object);
	
 	command ("grin demonically");

    command("wear all");
    command("wield sword");

}
