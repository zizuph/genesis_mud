inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>


create_monster() {
   
   if (!IS_CLONE)
      return;
   
   set_race_name("human"); 
  set_living_name("townsman");
   set_name("villager");
   set_adj(age());
   add_adj(face());
   
   set_gender(random(2));
   
   set_base_stat(SS_STR, random(10)+4);
   set_base_stat(SS_DEX, 13);
   set_base_stat(SS_CON, 12);
   set_base_stat(SS_INT, 15);
   set_base_stat(SS_WIS, 11);
   set_base_stat(SS_DIS, 6);
   set_hp(1000); /* reduced to correct level according to con. */
   
   set_skill(SS_WEP_KNIFE, 4);
   set_random_move(2);
   
   set_all_hitloc_unarmed(8);
   set_all_attack_unarmed(random(5) + 5);
   
   set_chat_time(5);
   
   enable_commands();
   set_act_time(1);
/*
 * the line below calls a non-existent function   /Vader
   call_out("get_wepon", random (8));
 */
   get_money();
}

age() {
   string *ages;
    ages = ({"old", "weary", "senile", "graying", "timeworn",
      "venerable", "middle-aged", "tall", "fat", "slim", "young",
     "youthful", "short", "portly", "brawny", "lean", "slender",
     "robust", "hearty", "withered"});
   return ages[random(sizeof(ages))];
}

face() {
   string *faces;
    faces = ({"happy", "sad", "melancholy", "imposing", "black-haired",
      "pale", "leathery", "green-eyed", "blonde-haired", "proud",
      "blue-eyed", "noble", "cheerful", "simple", "grey-eyed", 
      "brown-haired", "hazel-eyed", "brown-eyed"});
   return faces[random(sizeof(faces))];
}

get_money() {
   if (random(10)<3) {
      make_money(random(8)+2,"copper");
      if (!random(100)) make_money(1,"silver");
   }
}


make_money(i,type) {
   object money;
   
#ifndef UNDEF
      MONEY_MOVE(i, type, 0, this_object());
#else
      money = clone_object("/std/coins");
   money->set_heap_size(i);
   money->set_coin_type(type);
   money->move(this_object(),1);
#endif
}

