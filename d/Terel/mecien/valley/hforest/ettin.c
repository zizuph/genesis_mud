inherit "/std/monster";
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>


#define TO this_object()
#define EN environment
#define TP this_player()


create_monster(){

set_race_name("ettin");
set_name("glorock");
set_living_name("glorock");
set_adj(({ "horrible", "red-eyed" }));
set_aggressive(1);
set_random_move(1);
set_long(
"A horrible monster, standing some twenty feet high. A two headed giant, "
+"with red blood-shot eyes, stubby black horns, a mass of tangled " +
"hair, reaching down over its body. Its feet and skin are dried " +
"and almost scaled. It seems to have a fury within itself.\n");


set_act_time(2);
add_act("growl");
add_act("emote starts to froth at the mouth.");
add_act("emote knocks his heads together.");
add_act("emote bares his teeth.");
set_stats(({ 199, 197, 122, 80, 56, 155 }));

add_prop(CONT_I_WEIGHT, 1000000);
add_prop(CONT_I_VOLUME, 1000000);
add_prop(CONT_I_MAX_WEIGHT, 2000000);
add_prop(CONT_I_MAX_VOLUME, 2000000);
set_skill(SS_WEP_SWORD, 90);
  set_skill(SS_AWARENESS, 80);
set_skill(SS_WEP_POLEARM, 120);
set_skill(SS_DEFENCE, 85);
set_skill(SS_TRACKING, 80);
set_skill(SS_SWIM, 30);
set_skill(SS_CLIMB, 80);
set_skill(LIVE_O_ENEMY_CLING, 1);
set_skill(SS_2H_COMBAT, 70);
set_skill(SS_UNARM_COMBAT, 70);
set_skill(SS_BLIND_COMBAT, 100);

set_gender(0);
set_alignment(-659);

set_all_attack_unarmed(115);
set_all_hitloc_unarmed(70);

set_alarm(1.0, -1.0, "get_stuff");


}

get_stuff(){
  object ob1, ob2, ob3, ob4, ob5, ob6;

  MONEY_MOVE(random(200) + 10, "copper", 0, TO);
  MONEY_MOVE(random(150) + 5, "silver", 0, TO);
  MONEY_MOVE(random(50) + 1, "gold", 0, TO);
  ob1=clone_object("/d/Terel/mecien/valley/hforest/g_spear");
  ob1->move(TO);
  TO->command("wield spear");
  ob2=clone_object("/d/Terel/mecien/mountains/fur");
  ob2->move(TO);
   TO->command("wear coat");
   


}

