#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"


#define EN environment
#define TO this_object
#define TP this_player()
#define COST ([ "heal":80, "fire":70, "light":35, "armistice":100, "respect":10,\
      "humility":15, "stun":70 ])
#define SP query_skill(SS_SPELLCRAFT)
#define DIS query_stat(SS_DIS)


verbum(string str){
   
   object who;
   string *word;
   string type;
   string *good;
   
   word = ({ "heal", "fire", "light", "armistice", "respect", "humility",
         "stun" });
   if(!str) return "Mystical word what?\n";
   
   if(!parse_command(str, EN(TP), " %w [on] %o ", type, who ))
      return "What mystcal word on who?\n";
   if(!who) return "Mystic word on who?\n";
   if(member_array(type, word) < 0) return "There is no such mystical word.\n";
   
   if(TP->query_mana() < COST[type]) return "You do not have the strength.\n";
   
   if(TP->query_skill(SS_SPELLCRAFT) + random(100) < 100) return "You fail to grasp the mystical word.\n";
   
   good = ({ "heal" });
   write("You intone one of the ancient mystic words.\n");
   say(QCTNAME(TP) + " intones an ancient mystical word.\n");
   if(member_array(type, good) < 0){
      if(who->DIS + who->SP + random(100) > TP->DIS + TP->SP + 100) return "The mystical word was resisted.\n";
   }
   if(type == "heal") set_alarmv(2.0, -1.0, "heal", ({ who, TP }));
   if(type == "respect") set_alarmv(2.0, -1.0, "bow", ({ who, TP }));
   if(type == "fire") set_alarmv(2.0, -1.0, "fire", ({ who, TP }));
   if(type == "humility") set_alarmv(2.0, -1.0, "humility", ({ who, TP }));
   if(type == "stun") set_alarmv(2.0, -1.0, "stun", ({ who, TP }));
   if(type == "light") set_alarmv(2.0, -1.0, "light", ({ who, TP }));
   if(type == "armistice") set_alarmv(2.0, -1.0, "armistice", ({ who, TP }));
   TP->add_mana(-COST[type]);
   
   return 1;
}

heal(object who, object me){
  object dis;
   dis = present("_plague_", who);
     if(dis) dis->heal_disease(10);
   me->catch_msg("You feel the spirits of life pass through you.\n");
   tell_room(EN(me), QCTNAME(me) + " glows with an eerie radiance.\n", me);
   who->catch_msg("A powerful sense of healing enters your body.\n");
   who->heal_hp(300 + random(200));
}

bow(object who, object me){
   me->catch_msg("You are filled with a spirit of nobility.\n");
   tell_room(EN(me), QCTNAME(TP) + " stands tall and proud, like a noble of some forgotten ancient kingdom.\n");
   who->catch_msg("You feel compelled to bow before " + QTNAME(TP) + ".\n");
   who->command("bow " + me->query_real_name());
}


light(object who, object me){
   me->catch_msg("The spirits of light pass through you.\n");
   tell_room(EN(who), "A magnificent burst of mysterious light shines down upon " +
      QTNAME(who) + ".\n", who);
   who->catch_msg("A magnificent burst of mysterious light shines down upon you!\n");
   EN(who)->add_prop(ROOM_I_LIGHT, 10);
   if(who->query_prop(LIVE_I_UNDEAD)){
      who->catch_msg("The light burns away your flesh!\n");
      who->hit_me(60, MAGIC_DT, me, 1);
      who->add_panic(random(50) + 10);
   }
}

humility(object who, object me){
   tell_room(EN(me), QCTNAME(me) + " looks at " + QTNAME(who) + " with disdain and contempt.\n", ({ who, me }));
   who->catch_msg(QCTNAME(me) + " looks upon you with disdain and contempt.\n");
   me->catch_msg("You look upon " + QTNAME(who) + " with disdain and contempt.\n");
   who->catch_msg("You feel a deep sense of humility and show your reverence and respect for the Ancients.\n");
   tell_room(EN(who), QCTNAME(who) + " lowers " + who->query_objective() +
      "self and calls upon the Ancients to forgive " + who->query_objective() + ".\n", who);
}

fire(object who, object me){
   int my_fire;
   my_fire = random(me->query_skill(SS_ELEMENT_FIRE));
   tell_room(EN(me), "The eyes of " + QTNAME(me) + " flicker with a crimson fire.\n", me);
   me->catch_msg("The spirits of fire pass through you.\n");
   who->catch_msg("A terrible crimson fire blazes all over your body!\n");
   who->hit_me(90 + my_fire, MAGIC_DT, me, 1);
   tell_room(EN(who), QCTNAME(who) +  " is suddenly covered by a blaze of crimson fire!\n", who);
}

check_again(object who, object what){
   who->command("wield " + what->query_name());
}

check_wield(object what){
   object who;
   who = what->query_wielded();
   if(who){
      who->command("unwield " + what->query_name());
      if(!interactive(who)) set_alarm(30.0, -1.0, "check_again", ({ who, what }));
   }
}

stun(object who, object me){
   me->catch_msg("You point a gnarled hand at " + QTNAME(who) + ".\n");
   tell_room(EN(me), QCTNAME(me) + " points a gnarled hand at " + QTNAME(who) + ".\n", ({ who, me }));
   who->catch_msg(QCTNAME(TP) + " points a gnarled hand at you.\n");
   who->add_attack_delay(10, 0);
   who->catch_msg("A numbness passes through your body.\n");
}

armistice(object who, object me){
   tell_room(EN(me), QCTNAME(me) + " stretches out a hand towards " + QTNAME(who) + ".\n", me);
   me->catch_msg("You stretch out your hand towards " +QTNAME(who) + ".\n");
   who->catch_msg("You lose all desire for battle.\n");
   map(all_inventory(who), check_wield);
}

