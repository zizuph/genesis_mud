inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
/* by Korat */
create_monster()
{
   ::create_monster();
   set_name("budhead");
   add_name("trainer");
   set_race_name("human");
   set_adj("huge");
   add_adj("athletic");
   set_long("This human has as his task to train other adventurers "+
      "in the skills of all weapons. It goes without saying that he "+
      "knows how to fight pretty well himself. So you better leave this "+
      "guy alone. If you want to he will train you too, for a fee.\n");
   set_stats(({100,120,120,70,70,140}));
   set_alignment(500);
   set_skill(SS_WEP_POLEARM,100);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_WEP_KNIFE,100);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,70);
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,1); /* won't accept gifts */
      add_prop(CONT_I_WEIGHT, 80000);  /* weights 80 kilo's */
   add_prop(CONT_I_HEIGHT, 195);    /* 160 cm high */
   set_hp(query_max_hp()); /* heal fully */
   set_title(", Master trainer of the arena of Kabal.");
   add_prop(OBJ_M_NO_ATTACK,"You decide not to attack Budhead after "+
      "all. How would he be able to teach you anything if he was dead??\n");
   add_ask(({"train","practise"}),"Budhead says: Grab a weapon and pay me!\n");
   add_ask(({"fight","arena","games","participate"}),
      "Well, right now the arena is under construction...so no games are held.\n");
   
   set_act_time(2);
   add_act(({"emote appraises you thoroughly.",
            "say Are you here to train?",
            "grin greedily"}));
   add_act(({"ponder my god, they are hopeless...","sigh"}));
   add_act("say Spread your feet out to get better balance!");
   add_act("emote walks over to the student of his and shows them a "+
      "perfectly executed axe-swing in slow-motion.");
   add_act(({"emote scratches his cheek.","say Only way to get it right "+
            "is to train until its right!"}));
   add_act(({"emote grumbles abit before he tells a student how to hold "+
            "@@weapon@@ the correct way.","say Don't do that! Here..I'll show you "+
            "how to do it right."}));
   add_act(({"say Students! Watch me and learn!!","emote grabs a "+
            "sword and stabs the air in front of him with delicate motions.\n"}));
   
   set_knight_prestige(-10);
   add_speak("Ahh, so you want to train? Just pay me and I'll help you.\n");
}


weapon()
{
   switch(random(4)){
      case 0:
      return("his axe");
      break;
      case 1:
      return("her club");
      break;
      case 2:
      return("his sword");
      break;
      case 3:
      return("his polearm");
      break;
      case 4:
      return("her knife");
      break;
   }
}