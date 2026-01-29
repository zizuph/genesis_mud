// file name: spirit
// creator(s): Ilyian (16 August, 1995)
// last update:
// purpose: Standard spirit for the Isle of Dead area
// note:
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Genesis/gems/gem.h"
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
  randadj = ({"misty","pale","white","solemn",
              "ghostly","terrible","translucent"});
  set_name(({"spirit","ghost","_Dead_Isle_Spirit","undead"}));
  set_pname(({"spirits"}));
  set_race_name("spirit");
  set_gender(random(3));
  set_adj(randadj[random(sizeof(randadj))]);

  set_long("This being of light has transcended "
          +query_possessive()+" mortal "
          +"coil, and stares down at you with a mixture of "
          +"pity and contempt. "+CAP(query_possessive())
          +" long white arms end in "
          +"long and strange claws that glimmer with an "
          +"eerie glow.\n");

  set_alarm(1.0,0.0,"set_m_in","drifts in");
  set_alarm(1.0,0.0,"set_m_out","drifts");
  set_alignment(0);

  set_stats(adjust(({95,100,110,70,70,60})));
  set_hp(query_max_hp());
  set_restrain_path(MARSH);

  set_skill(SS_AWARENESS, 20);

  set_random_move(1,0);
  set_aggressive(1); 

  set_attack_unarmed(0,35,35,W_SLASH,50,"right claw");
  set_attack_unarmed(1,35,35,W_SLASH,50,"left claw");

  /* Impaling weapons are deadly to it */
  set_hitloc_unarmed(0, ({2,35,20}),25,"head");
  set_hitloc_unarmed(1, ({2,35,40}),50,"body");
  set_hitloc_unarmed(2, ({2,35,20}),25,"legs");

  add_prop(LIVE_I_NO_CORPSE,1);
  add_prop(LIVE_I_SEE_DARK,10);
  add_prop(LIVE_I_UNDEAD,18);
  add_prop(LIVE_I_NEVERKNOWN,1);

  set_cact_time(10);
   add_cact("emote lets out a wail of anger and pain.");
   add_cact("scream");
   add_cact("emote opens "+query_possessive()
           +" arms wide, as if to embrace you.");

  set_act_time(20);
   add_act("emote looks around and smiles briefly.");
   add_act("emote seems to flicker in and out for a moment.");
   add_act("emote reaches down and gets something from the weeds.");
}

/* For the solamnic Knights */
query_knight_prestige() { return(-1); }

/* Shoul I attack this guy? */
int
do_this_check()
{
   if(query_attack())
     { return 0; }  // always concentrate on fighting

    if(UND(TP) > 0)  // respect my friends
      {
        set_alarm(3.0, 0.0, &do_respect(this_player()));
        return 0;
       }

    if (TP->query_npc())
      { return 0; } // don't kill each other

    if (TP->query_alignment() < 20)  // slay the evil
      { return 1; }
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
  string *ways = ({"brief","resp","cold","soft",
                   "slightly","slow","nice"});
  command("nod "+ways[random(sizeof(ways))]+" "+TP->query_real_name());
  return;
}

