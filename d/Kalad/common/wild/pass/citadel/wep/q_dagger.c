/*
 * Made by Korat
 * September 1996
 * 
 * A dagger that is a part of a quest.
 * 
 */
inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

/* A definition that returns all objects in array x that are corpses */
#define FILTER_CORPSE(x) \
      filter((x), &operator(==)("corpse") @ &->query_name())


int has_sacrified = 0;
string what_race;

create_weapon()
{
   ::create_weapon();
   set_name("dagger");
   set_adj("black");
   add_adj("adamantine");
   set_long("The adamantine of this dagger shines strongly in the light, "+
      "even though it seems to be made of some black metal. Along its "+
      "curving blade, you see several engraved letters.\n");

   add_item(({"letters","letter","engraved letters"}),VBFC_ME("words"));

   set_hit(12);
   set_pen(12);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE | W_SLASH);
   set_wf(TO);
   add_prop(OBJ_I_VALUE,1);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_M_NO_BUY,1);
   
   /* the dagger will randomly demand a special race to be sacrificed */
   switch (random(3))
   {
      case 0: what_race = "darthiir"; break;
      case 1: what_race = "rivvil"; break;
      case 2: what_race = "gol"; break;
      default: what_race = "rivvil"; break;
   }
}

string
words()
{
   if (TP->query_skill(SS_LANGUAGE) < 20)
      return "You do not understand anything of the letters.\n";

   /* has sacrifice been done ? */
   if (has_sacrified)
      return "The words now seems to form into a shape more than "+
         "letters to read. It resembles a cavern beneath a tall "+
         "tower. A cavern with many paths but none visible.\n";

/* Translation:
 * To give(belbau) ??? blood(qu'ilth) to(ulu) 
 * honoured(malla) Lolth(quarvalsharess) 
 * commands(quarthen) this one(usstan)
 * to be(tlu) the(lil) guide(mrimm) 
 * on(pholor) the(lil) path(colbauth).
 *
 * elf:    darthiir
 * human:  rivvil
 * goblin: gol
 */

   return "They read: Belbau " + what_race +
          " qu'ilth ulu malla quarvalsharess quarthen usstan "+
          "tlu lil mrimm pholor lil colbauth.\n";
}

init()
{
   ::init();
   add_action("sacrifice","sacrifice");
}

int
sacrifice(string what)
{
   object *corpses;
   string race;
   int i, ran;
   
   NF("What?\n");
   if (!TO->query_wielded()) return 0;

   NF("Sacrifice what?\n");
   if (!what || what != "corpse") return 0;

   NF("But there is not a corpse here that can be sacrificed!\n");
   corpses = FILTER_CORPSE(all_inventory(E(TP)));

   if(!sizeof(corpses))
      return 0;

   NF("You get a feeling that only one corpse should be present "+
      "in this ritual.\n");
   if (sizeof(corpses) > 1) return 0;

   /* the player sacrifices a corpse to Lolth */

   NF("You slice up the corpse, but nothing special happens.\n");
   if (has_sacrified)
   {
      say(QCTNAME(TP)+" slices up the corpse with his dagger.\n");
      return 0;
   }

   race=corpses[0]->query_prop(CORPSE_S_RACE);

   write("You slowly slice the body up with the black "+
      "dagger, revealing the silent heart to your eyes. "+
      "With quick movements you cut the heart out, lift it up "+
      "above you  -  and without knowing why you suddenly "+
      "shout out aloud!\n");
   say(QCTNAME(TP)+" slices the corpse open and "+
      "cuts the heart out, for then to lift the heart into the air.\n");

   TP->command("shout Z'RESS ULU LOLTH! XAL USSTAN ZHAUN "+
      "QUARVALSHARESS ZHAUNIL ...'.");

   write("As you utter the last word, you pierce the heart "+
      "with the dagger. The dagger sparkles of darkness and "+
      "looks a little different.\n");

   say(QCTNAME(TP)+" finally pierces the heart "+
      "with the dagger.\n");

   has_sacrified = 1;
   if (corpses[0]->query_leftover("heart")) corpses[0]->remove_leftover("heart");

   ran = random(6) + 1;
   if (what_race == "darthiir" && race == "elf")
   {
      TO->add_prop("_korat_is_kabal_dagger",ran);
      return 1;
   }
   if (what_race == "rivvil" && race == "human")
   {
      TO->add_prop("_korat_is_kabal_dagger",ran);
      return 1;
   }
   if (what_race == "gol" && race == "goblin")
   {
      TO->add_prop("_korat_is_kabal_dagger",ran);
      return 1;
   }

   TO->add_prop("_korat_is_kabal_dagger",-1);
   return 1;
}

   



