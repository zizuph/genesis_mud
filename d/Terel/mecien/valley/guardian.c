inherit "/std/creature";
inherit "/std/combat/unarmed"; 
inherit "/std/act/chat";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/asking";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>

#define TO this_object()
#define TP this_player()

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

query_mm_in(){
   return "appears from a mysterious cloud.";
}

query_mm_out(){
   return "summons a cloud about him and disappears within it.";
}

ok_key(){
   object key;
  seteuid(getuid(TO));
   key=clone_object("/d/Terel/mecien/valley/guild/crypt/mkey");
  key->move(TO);
}

create_creature()
{
   set_living_name("asrafar");
   set_name("asrafar");
   add_name("lion");
   add_name("guardian");
   add_name("winged lion"); 
   set_race_name("lion");
   
   set_title("the Guardian of the Ancients");
   
   set_act_time(3);
   add_act("introduce myself");
   add_act("smile");
   
   set_chat_time(1);
   add_chat("Greetings");
   add_chat("I am Guardian of the Ancients");
   add_chat("Wisdom is near");
      add_chat("Truth is what I guard");
     add_chat("Be warned, let no evil come here");
   
  set_cact_time(3);
   add_cact("@@heal");
   set_short("winged lion");
   set_adj(({"golden", "noble" }));
   set_long("This beautiful golden winged lion seems to be the\n" +
      "guardian of the valley. It looks very mighty.\n");
   
   
   set_stats(({ 110, 110, 170, 100, 100, 110}));
   
   add_prop(LIVE_I_SEE_DARK, 1);
   add_prop(LIVE_I_SEE_INVIS, 100);    
   add_prop(LIVE_I_QUICKNESS, 100);
   set_skill(SS_AWARENESS,    100);
   set_skill(SS_UNARM_COMBAT, 75);
   set_skill(SS_CLIMB,        80);
   set_skill(SS_LOC_SENSE,    90);
   set_skill(SS_HUNTING,      90);  
   set_skill(SS_DEFENCE, 150);
   set_skill(SS_SWIM, 80);
   set_hp(99999);
   set_alignment(810);
   
   add_ask("for key", "@@get_key", 1);

   
   set_attack_unarmed(A_BITE,  60, 70, W_IMPALE, 90, "jaws");
   set_attack_unarmed(A_LCLAW, 99, 90, W_SLASH,  80, "left paw");
   set_attack_unarmed(A_RCLAW, 99, 89, W_SLASH,  80, "right paw");
   
   set_hitloc_unarmed(H_HEAD, 90, 20, "head");
   set_hitloc_unarmed(H_BODY, 100, 80, "body");

   set_alarm(1.0, -1.0, "ok_key");
}

heal(){
   TO->command("emote is surrounded by a golden light!\n");
   TO->heal_hp(444);
}

get_key(){
   object key;
   key = present("sacred_key", TO);
   if(key){
      if(TP->query_guild_member("The Ancient Mystic Order")){
         TO->command("give key to " + TP->query_real_name());
         TO->command("smile");
      }
   }
   
}


