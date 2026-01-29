
// file name: apparition
// creator(s): Ilyian (16 August, 1995)
// last update:
// purpose: Standard apparition for the Isle of Dead area
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
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/guilds.h"

#include "/d/Genesis/gems/gem.h"

string *randadj;
int     alarm_id;

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
create_monster()
{
  randadj = ({"lovely","pale","sad","glowing",
              "bright-eyed","long-armed","willowy"});
  set_name(({"apparition","_Dead_Isle_Apparition","ghost","undead"}));
  set_pname(({"apparitions"}));
  set_race_name("apparition");
  set_gender(G_FEMALE);
  set_adj(randadj[random(sizeof(randadj))]);

  set_long("The beautiful apparition floats before you "
          +"like a sullen dream. Her long face stares gently "
          +"into yours, and her white robes flow all about.\n");

  set_alarm(1.0,0.0,"set_m_in","flows in");
  set_alarm(1.0,0.0,"set_m_out","flows");
  set_alignment(0);

  set_stats(adjust(({115,75,110,60,50,60})));
  set_hp(query_max_hp());
  set_restrain_path(MARSH);

  set_skill(SS_AWARENESS, 5);

  set_random_move(1,0);
  set_aggressive(1);

  set_attack_unarmed(0,20,35,W_BLUDGEON,50,"right fist");
  set_attack_unarmed(1,20,35,W_BLUDGEON,50,"left fist");

  /* Almost impervious to impale, slash and bludgeon work better */
  set_hitloc_unarmed(0,({60,35,10}),25,"head");
  set_hitloc_unarmed(1,({60,35,10}),50,"body");
  set_hitloc_unarmed(2,({60,25,20}),25,"legs");

  add_prop(LIVE_I_SEE_DARK,10);
  add_prop(LIVE_I_UNDEAD,8);
  add_prop(LIVE_I_NEVERKNOWN,1);
  add_prop(LIVE_I_NO_CORPSE, 1);
  add_prop(NPC_I_NO_LOOKS,1);

  set_cact_time(10);
   add_cact("emote raises her head to the cavern ceiling above.");
   add_cact("emote makes a strange gesture with her right arm.");
   add_cact("emote gets a strange gleam in her eye.");

  set_act_time(20);
   add_act("moan sadly");
   add_act("emote shakes her head wildly.");
   add_act("beckon");
   add_act("emote raises her arm upwards.");
   add_act("emote whispers softly.");
}

/* For the solamnic Knights */
query_knight_prestige() { return(-1); }

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
  string *ways = ({"brief","resp","warm","cold","soft",
                   "sensual","slightly","slow","nice"});
  command("nod "+ways[random(sizeof(ways))]+" "+TP->query_real_name());
  return;
}

/* Shoul I attack this guy? */
int
do_this_check(object tp)
{
    string  occ;
    int i;
    alarm_id = 0;

 
    if (query_attack())
    {    return 0;    }  // always concentrate on fighting

    if (!present(tp, environment(TO)))
        return 0;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 2)
            command("bow respect "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +" I am "+
                "prepared for Sybarus' hour of need!");
        if (i == 6)
            command("say to "+ tp->query_real_name() +" I would "+
                "that I had lived a life so worthy of the "+
                "Gods' regard as you.");
        return 0;
    }
    if (IS_INFIDEL(tp))
    {        
        if (i < 6)
        {
            command("shout Infidel! Only by your death may I "+
                "redeem myself!");
            command("kill "+ tp->query_real_nme());
        }
        return 1;
    }    

    if (UND(TP) > 0)     // respect my friends
    {
        set_alarm(3.0, 0.0, &do_respect(this_player()));
        return 0;
    }

    if (TP->query_npc())
    {    return 0;     } // don't kill each other

    do_slay(tp); 
    return 1; // Yes.
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &do_this_check(this_player()));
    }
}  

void
do_die(object killer)
{
   command("emote explodes in a violent flash of light.");
   ::do_die(killer);
}
