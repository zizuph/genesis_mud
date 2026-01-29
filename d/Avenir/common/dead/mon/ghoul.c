// file name: ghoul
// creator(s): Ilyian (16 August, 1995)
// last update:
// purpose: Standard ghoul for the Isle of Dead area
// note:
// bug(s):
// to-do:

inherit "/std/creature";
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

int *adjust(int *stat)
{
   int   i,
        *ret = allocate(6);

   for(i=0;i<sizeof(stat);i++)
     ret[i] = stat[i] + random(stat[i] / 5) - random(stat[i] / 5);

   return ret;
}

void
create_creature()
{
  randadj = ({"dreadful","nasty","rotting","smelly",
              "violent","long-armed","rickety"});
  set_name(({"ghoul","_Dead_Isle_Ghoul","undead"}));
  set_pname(({"ghouls"}));
  set_race_name("ghoul");
  set_gender(random(3));
  set_adj(randadj[random(sizeof(randadj))]);

  set_long("This nasty and rotting corpse stands "
          +"before you as a mockery of life. "
          +CAP(query_pronoun())+" seems "
          +"to move with some difficulty, but "
          +query_possessive()+" long "
          +"arms threaten to hold a terrible strength.\n");

  set_alarm(1.0,0.0,"set_m_in","staggers in");
  set_alarm(1.0,0.0,"set_m_out","staggers");
  set_alignment(0);

  set_stats(adjust(({115,25,80,20,30,60})));
  set_hp(query_max_hp());
  set_restrain_path(MARSH);

  set_skill(SS_AWARENESS, 5);

  set_random_move(1,0);
  set_aggressive(1);

  set_attack_unarmed(0,20,35,W_BLUDGEON,50,"right fist");
  set_attack_unarmed(1,20,30,W_BLUDGEON,50,"left fist");

  /* Almost imprevious to bludgeon, vulnerable to impale & slash */
  set_hitloc_unarmed(0,({5,15,60}),25,"head");
  set_hitloc_unarmed(1,({10,25,60}),50,"body");
  set_hitloc_unarmed(2,({10,25,60}),25,"legs");

  add_prop(LIVE_I_SEE_DARK,10);
  add_prop(LIVE_I_UNDEAD,8);
  add_prop(LIVE_I_NEVERKNOWN,1);

  set_cact_time(10);
   add_cact("emote shakes its head back and forth furiously.");
   add_cact("emote opens its mouth, but no sound comes out.");
   add_cact("emote opens its arms wide, as if to embrace you.");

  set_act_time(20);
   add_act("moan soft");
   add_act("emote sways slightly.");
   add_act("emote seems to whisper soundlessly.");
   add_act("emote stumbles slightly.");
   add_act("emote stares into space.");
   add_act("emote tears some rotten flesh off "+query_possessive()+" face.");
}

/* For the solamnic Knights */

query_knight_prestige() { return(50); }
    
int
do_this_check()
{
   if(query_attack())
     { return 0; }  // always concentrate on fighting

    if (TP->query_npc())
      { return 0; } // don't kill each other

    if (TP->query_alignment() > 20)
      { return 1; }

    if(UND(TP) > 0)
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

void
do_slay(object victim)
{
   if(query_attack())
     { return; }  // always concentrate on fighting

   command("kill "+victim->query_real_name());
}

void
do_respect(object undead)
{
  string *ways = ({"deep","resp","arch","cold","menac"});
  command("bow "+ways[random(sizeof(ways))]+" "+TP->query_real_name());
  return;
}

