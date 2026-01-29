/*
 *  A random orc with random stuff
 *  Cloned by ~Shire/common/hobbiton/camp[2-4]
 */

inherit "/std/monster";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define RADJ ({ "short", "ugly", "scary", "injured", "nasty", "thin", \
                "fierce" })
#define RLONG ({ \
     "This orc is a bit shorter than the avarage orc. He makes his " \
   + "small length more than good with his muscular build.\n", \
     "This orc is not quite beautiful, in fact, he is kind of ugly. " \
   + "His ugliness makes him look more ferocious than the others.\n", \
     "The orc is scary, and judging by his many scars, he must have " \
   + "fought in many battles.\n", \
     "The orc has a big, bleeding scar on his right arm. It seems he has " \
   + "been in a fight with someone else who cleaved his axe in the arm.\n", \
     "Orcs are known to be not nice, but this one really looks nasty.\n", \
     "Unlike normal orcs, this one is very thin for an orc.\n", \
     "The fierce orc looks with his piercing eyes straight through you.\n" \
   + "This is one bad orc to mess with, for sure!\n" })
#define RWEIGHT ({ 80, 107, 103, 99, 87, 70, 112 })
                  /* str dex con int wis dis */
#define RSTAT ({ \
                   ({ 32, 33, 33, 12, 13, 65 }), \
                   ({ 29, 31, 30, 12, 12, 65 }), \
                   ({ 34, 33, 27, 10, 12, 65 }), \
                   ({ 16, 32, 17, 11, 13, 65 }), \
                   ({ 26, 24, 25,  8,  8, 65 }), \
                   ({ 24, 24, 19, 10, 16, 65 }), \
                   ({ 36, 30, 37, 15, 14, 65 }) })

#define RWEAPON ({ "orc_knife","orc_scimitar","orc_sword" })
#define RWSHORT ({ "knife","scimitar","sword" })

#define SKUCOM ({ 23, 47, 51, 17, 49, 33, 55 })
#define SKDEF  ({ 33, 40, 42, 13, 40, 35, 47 })

create_monster() {
   int ran;

   if (!IS_CLONE)
      return;

   seteuid(getuid());
   ran = random(7);
   set_name(({"_random_orc_","orc"}));
   set_pname("orcs");
   set_pshort(RADJ[ran] + " orcs");
   set_race_name("orc"); 
   set_adj(RADJ[ran]);
    set_alignment(-150 + random(50));
   set_long(break_string(RLONG[ran],70));
   add_prop(CONT_I_WEIGHT,RWEIGHT[ran] * 1000);
   add_prop(CONT_I_HEIGHT,RWEIGHT[ran] * 1000);
   add_prop(LIVE_I_NEVERKNOWN,1);

   set_stats(RSTAT[ran]);
   set_hp(10000); /* Heal fully */

   set_skill(SS_UNARM_COMBAT, SKUCOM[ran]);
   set_skill(SS_WEP_SWORD, SKUCOM[ran]);
   set_skill(SS_WEP_AXE, SKUCOM[ran]);
   set_skill(SS_WEP_KNIFE, SKUCOM[ran]);
   set_skill(SS_DEFENCE, SKDEF[ran]);
   set_skill(SS_PARRY, SKDEF[ran]);
   set_pick_up(75);

   set_aggressive(1);
   set_attack_chance(90);

   set_chat_time(5 + random(6));
   add_chat("What are you doing here?");
   add_chat("Go away while you still live!");
   add_chat("I don't like the looks of you!");
   add_chat("Hey, an intruder!");
   add_chat("I'll chop yer legs off!");
   add_chat("I'll chop yer arms off!");
   add_chat("I thought our camp was secured!");
   add_chat("I'll get that lousy guard of ours...");
   add_chat("Hey you! Stop!");
   add_chat("Come here and I'll bite your head off!");

   set_cchat_time(3 + random(6));
   add_cchat("Ha! You chose the wrong one to attack!");
   add_cchat("In a moment me be getting very mad!");
   add_cchat("Who do you think you are?!?");

   /* Triggers */
   trig_new("%s 'smiles' %s", "react_smile");
   trig_new("%s 'sighs' %s", "react_sigh");

   call_out("arm",0);

}

arm() {
  int ran;
  ran = random(3);
  clone_object(STAND_PARENT + "weapon/" +RWEAPON[ran])->move(this_object());
  command("wield " + RWSHORT[ran]);
}

/********************************************************************
 *
 *  Some feelings to make the orc more vivid.
 *  The feelings are split in two parts: the part that is called by
 *  a trigger function, and a part that is called after a random time.
 *  This is done to get a feeling of reality in the game.
 */

react_sigh(who, dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_sigh", 4+random(9), who);
      return 1;
   }
}

return_sigh(who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I am glad you are depressed, "
               + obj->query_nonmet_name() + ".");
      if (ran == 1)
         command("grin");
      if (ran == 2)
      {
         command("say It makes me happy to see you depressed, bloody "
              + obj->query_race_name() + ".");
         command("poke " + who);
      }
   }
}

react_smile(who, dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 4+random(9), who);
      return 1;
   }
}

return_smile(who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Get that grin off your face, "
               + obj->query_nonmet_name() + "!");
      if (ran == 1)
         command("growl at " + who);
      if (ran == 2)
         command("say Damn " + LANG_PWORD(obj->query_race_name())
               + ", always smiling!");
   }
}

/* For the solamnic Knights */

query_knight_prestige() { return(50); }
