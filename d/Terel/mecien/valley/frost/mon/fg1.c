inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

#define PATH "/d/Terel/mecien/valley/frost/"

create_monster(){
   
   set_race_name("giant");
   set_name("giant");
   set_adj("frost");
   
   set_stats(({ 110 + random(50), 75 + random(40), 125 + random(60), 20, 20, 75}));
   set_alignment(-(250 + random(400)));
   set_hp(99999);
   set_skill(SS_WEP_SWORD, 70 + random(30));
   set_skill(SS_WEP_CLUB, 85 + random(35));
   set_skill(SS_WEP_AXE, 70 + random(35));
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_PARRY, 70);
   set_skill(SS_UNARM_COMBAT, 80);
   set_skill(SS_2H_COMBAT, 80);
   
   
   set_all_hitloc_unarmed(50);
   
   set_act_time(10);
   add_act("growl");
   add_act("laugh");
   add_act("grin");
   
   set_random_move(25);
   set_attack_chance(75);

   call_out("equip", 1);
    call_out("protect", 2);
}

equip(){
   
   object ob1, ob2, ob3, ob4;
   int wep;
   
   
   seteuid(getuid(this_object()));
   
   wep = random(3);
   if(wep == 0){
      ob1=clone_object(PATH + "obj/club");
      ob1->move(this_object());
      this_object()->command("wield club");
   }
   if(wep == 1){
      ob1=clone_object(PATH + "obj/axe");
      ob1->move(this_object());
      this_object()->command("wield axe");
   }
   if(wep == 2){
      ob1=clone_object(PATH + "obj/club");
      ob1->move(this_object());
      this_object()->command("wield club");
      ob2=clone_object(PATH + "obj/axe");
      ob2->move(this_object());
      this_object()->command("wield axe");
   }
   
   if(wep < 2){
      if(random(2)) return 0;
      ob3=clone_object(PATH + "obj/shield");
      ob3->move(this_object());
      this_object()->command("wear shield");
   }
   
return 1;
}

protect(){

object ob1, ob2, ob3;

seteuid(getuid(this_object()));

if(random(2)){
ob1=clone_object(PATH + "obj/fur");
ob1->move(this_object());
this_object()->command("wear fur");
}
if(random(2)){
ob2=clone_object(PATH + "obj/helm");
ob2->move(this_object());
this_object()->command("wear helm");
}
if(random(2)){
ob3=clone_object(PATH + "obj/shirt");
ob3->move(this_object());
this_object()->command("wear shirt");
}

}


