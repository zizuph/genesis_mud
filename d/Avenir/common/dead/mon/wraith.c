// file name: wraith
// creator(s): Ilyian (16 August, 1995)
// last update:  Lilith: 23 Aug 2001, updated add_asks.
// purpose: Standard wraith for the Isle of Dead area
// note:
// bug(s):
// to-do:

inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "../dead.h"
#include "money.h";
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#include "/d/Genesis/gems/gem.h"
string *randadj;

void   do_slay(object victim);
void   do_respect(object undead);

void 
arm_me() 
{
   object gem;

   seteuid(getuid());
   MONEY_MAKE_CC(2)->move(this_object());


   gem = RANDOM_GEM(GEM_RARE);
   gem->move(this_object());  
}

void
create_monster()
{
  randadj = ({"misty","pale","white","menacing",
              "fearful","angry","translucent"});
  set_name(({"wraith","apparition","_Dead_Isle_Wraith","undead"}));
  set_pname(({"wraiths","wraithes","apparitions"}));
  set_race_name("wraith");
  set_gender(random(2));
  set_adj(randadj[random(sizeof(randadj))]);

  set_long("This shadowy apparition floats a foot from "
          +"the ground, eyeing you with unrestrained "
          +"malice. Its long misty arms end in fierce "
          +"claws that look almost metallic.\n");

  set_alarm(1.0,0.0,"set_m_in","drifts in");
  set_alarm(1.0,0.0,"set_m_out","drifts");
  set_alignment(0);

  set_stats(({95,100,110,70,70,60}));
  set_hp(query_max_hp());
  set_restrain_path(MARSH);

  set_skill(SS_AWARENESS, 20);

  set_random_move(1,0);
  set_aggressive(1);  // This should be better!

  set_attack_unarmed(0,35,35,W_SLASH,50,"right claw");
  set_attack_unarmed(1,35,35,W_SLASH,50,"left claw");

  set_all_hitloc_unarmed(({50,35,20}));

  add_prop(LIVE_I_NO_CORPSE,1);
  add_prop(LIVE_I_SEE_DARK,10);
  add_prop(LIVE_I_UNDEAD,18);
  add_prop(LIVE_I_NEVERKNOWN,1);

  set_cact_time(10);
   add_cact("emote lets out a wail of anger and pain.");
   add_cact("scream");
   add_cact("emote opens its arms wide, as if to embrace you.");
   add_cact("emote warns:  This form you may destroy, but I "+
            "am cursed to inhabit another again.");


  set_act_time(20);
   add_act("emote moans softly.");
   add_act("emote seems to flicker in and out for a moment.");
   add_act("emote sighs: Here I remain until I redeem myself.");
   add_act("emote mourns: There is no death for me, only respite "+
       "from unlife.");      


    add_ask(({"unlife","undead",}),
       "say I failed to do the will of the Gods. Mascarvin rejected "+
       "me when I died, so I am cursed to remain here until I "+
       "redeem myself.", 1);

    add_ask(({"redeem","redemption","curse", "cursed"}),
        "say We are the last bastion of protection. We are the army "+
        "which rises to save Sybarus when all others fail, and we "+
        "redeem ourselves by killing those who threaten it.", 1);

    add_ask(({"falcata", "falcatta", "sword" }),
        "say It is truly a god-given gift. With them we slay the "+
        "enemies of Sybarus, to which they are specially attuned.", 1);

    add_ask(({"army","undead army","bastion",}),
        "say All of us who wander this island have one purpose: To "+
        "fulfill the promise of the Gods that the People of Sybarus "+
        "will have sanctuary upon these islands.", 1);

    add_ask(({ "promise","gods promise", "sanctuary"}),
        "say Should an army threaten the shores of Sybarus, we "+
        "will be mustered to fight them, an entire army of undead, "+
        "that we may fulfill the promise of sanctuary, and redeem "+
        "ourselves in eyes of the Gods.\n", 1);
   

}

/* For the solamnic Knights */
query_knight_prestige() { return(80); }

/* Shoul I attack this guy? */
int
do_this_check()
{
   if(query_attack())
     { return 0; }  // always concentrate on fighting

    if (TP->query_npc())
      { return 0; } // don't kill each other

    if (TP->query_alignment() > 20)  // slay the good
      { return 1; }

    if(UND(TP) > 0)  // respect my friends
      {
        set_alarm(3.0, 0.0, &do_respect(this_player()));
        return 0;
       }
}

/*
 * Function name: init_attack
 * Description:   Called from init_living() i monster.c
 */
public void
init_attack()
{
    int i = check_call(monster_aggressive);
    if ((!i) || (this_player()->query_npc()))
        return;
    if (do_this_check() &&
        (monster_attack_chance == 0) || (random(100) < monster_attack_chance))
        set_alarm(itof(random(4) + 1), 0.0, &do_slay(this_player()));
}

/* 
 * Ok, I'll attack, but only if I'm not busy killing
 * someone else right now.
 */
void
do_slay(object victim)
{
   if(query_attack())
     { return; }  // always concentrate on fighting

   command("kill "+victim->query_real_name());
}

/*
 * Show respect to my undead comrades.
 */
void
do_respect(object undead)
{
  string *ways = ({"deep","resp","arch","cold","menac"});
  command("bow "+ways[random(sizeof(ways))]+" "+TP->query_real_name());
  return;
}

do_die(object killer)
{
   command("emote melts into a whorl of haze.");
   ::do_die(killer);
}
