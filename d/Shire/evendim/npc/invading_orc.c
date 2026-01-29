/*
*  A random orc with random stuff adapted to be slightly weaker than
*  the original random_orc.
*  This file cloned by ~Shire/common/evendim/ev17
*/
inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"
#define RADJ ({ "short", "ugly", "scary", "injured", "nasty", "thin", \
      "fierce" })
#define RLONG ({ \
      "This orc is a bit shorter than the average orc. He makes his " \
      + "small length more than good with his muscular build.\n", \
      "This orc is not quite beautiful, in fact, he is kind of ugly. " \
      + "His ugliness makes him look more ferocious than the others.\n", \
      "The orc is scary, and judging by his many scars, he must have " \
      + "fought in many battles.\n", \
      "The orc has a big, bleeding scar on his right arm. It seems he has " \
      + "been in a fight with someone else who cleaved an axe in his arm.\n", \
      "Orcs are known to be not nice, but this one really looks nasty.\n", \
      "Unlike normal orcs, this one is very thin for an orc.\n", \
      "The fierce orc looks with his piercing eyes straight through you.\n" \
      + "This is one bad orc to mess with, for sure!\n" })
#define RWEIGHT ({ 80, 107, 103, 99, 87, 70, 112 })
/* str dex con int wis dis */
#define RSTAT ({ \
      ({ 12, 23, 13, 9, 10, 45 }), \
      ({ 19, 21, 20, 5, 8, 35 }), \
      ({ 14, 23, 17, 10, 12, 45 }), \
      ({ 6, 22, 17, 11, 13, 15 }), \
      ({ 16, 24, 15,  8,  8, 25 }), \
      ({ 14, 24, 19, 10, 16, 55 }), \
      ({ 9, 20, 27, 5, 14, 5 }) })
#define RWEAPON ({ "orc_knife","orc_axe","orc_sword" })
#define RWSHORT ({ "knife","axe","sword" })
#define SKUCOM ({ 23, 17, 31, 17, 29, 23, 15 })
#define SKDEF  ({ 23, 20, 12, 13, 20, 25, 37 })


//   Prototypes
void arm();
void return_smile(string who);
void return_sigh(string who);


void
create_monster()
{
   int ran;
   ran = random(7);
   set_name(({"_invading_orc_","orc"}));
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
   set_alarm(1.0,0.0,&arm());
   MAKE_MONEY;
}
void
arm()
{
   int ran;
   ran = random(3);
   clone_object(EVENDIM_DIR + "wep/" +RWEAPON[ran])->move(this_object());
   command("wield " + RWSHORT[ran]);
}
/********************************************************************
*
*  Some feelings to make the orc more vivid.
*  The feelings are split in two parts: the part that is called by
*  a trigger function, and a part that is called after a random time.
*  This is done to get a feeling of reality in the game.
*/
void
return_sigh(string who)
{
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
void
return_smile(string who) {
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

void
emote_hook(string emote, object actor, string adverb = 0)
{
   string name = actor->query_real_name();
   
   switch(emote)
   {
      case "smile":
      set_alarm(itof(4+random(9)),0.0,&return_smile(name));
      break;
      case "sigh":
      set_alarm(itof(4+random(9)),0.0,&return_sigh(name));
      break;
   }
}
/* For the solamnic Knights */
query_knight_prestige() { return(50); }

