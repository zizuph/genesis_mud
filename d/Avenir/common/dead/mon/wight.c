// file name: Wight
// creator(s): Ilyian (16 August, 1995)
// last update: Lilith 20 August 2001: added falcata and update unarmed attacks
//              Lilith 5  August 2021: tweaked unarmed attacks since their 
//                          hit/pen was higher than that of the khopesh and 
//                          it was causing monk's karma to fail.  
//              Lilith Feb 2022: changed randomizing code to use one_of_list 
//                  
// purpose: Standard wight for the Isle of Dead area
// note:      clones the magical falcata, which is a bane
//            to enemies of Sybarus
// bug(s):
// to-do:

inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/asking";
inherit "/lib/unique";
inherit "/d/Avenir/inherit/defeat";

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
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"


#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define DEATH_LOG   "/d/Avenir/log/deaths/wight"

string *randadj;

void   do_slay(object victim);
void   do_respect(object undead);
int    alarm_id;

int *adjust(int *stat)
{
   int   i,
        *ret = allocate(6);

   for(i=0;i<sizeof(stat);i++)
     ret[i] = stat[i] + random(stat[i] / 5) - random(stat[i] / 5);

   return ret;
}


void
arm_me()
{
    object sword, gem;

    seteuid(getuid());

    /* 33% chance of the weapon being magical. */
    sword = clone_unique("/d/Avenir/common/dead/obj/falcata", 6,
                "/d/Avenir/common/obj/knife", 1, 33);
    sword->move(TO);
    command("wield all");
    if (random(2))
    {
        gem = RANDOM_GEM(GEM_EXTREMELY_RARE);
        gem->move(this_object());    
    }
}

void
create_monster()
{
  randadj = ({"terrifying","horrible","ghastly","menacing",
              "fearful","pale","winged"});
  set_name(({"wight","apparition","_Dead_Isle_Wight","undead"}));
  set_pname(({"wights"}));
  set_race_name("wight");
  set_gender(random(3));
  set_adj(one_of_list(randadj));

  set_long("This enormous beast seems to have once been "
          +"humanoid, but "+query_possessive()
          +" flesh has sunken in so that "
          + query_possessive()
          +" bones show through. Great black wings spread "
          +"out from "+query_possessive()
          +" back, ending in long sharp talons.\n");

  set_alarm(1.0,0.0,"set_m_in","flies in");
  set_alarm(1.0,0.0,"set_m_out","beats its great wings and flies");
  set_alignment(0);

  set_stats(adjust(({125,130,150,90,100,120})));
  set_hp(query_max_hp());
  set_restrain_path(MARSH);

  set_skill(SS_WEP_SWORD, 90 + random(9));
  set_skill(SS_AWARENESS, 185);
  set_skill(SS_BLIND_COMBAT, 90 + random(9));
  set_skill(SS_PARRY, 90 + random(9));

  set_random_move(1,0);
  set_aggressive(1);  // This should be better!

  set_attack_unarmed(0,35,50,W_IMPALE,50,"right talon");
  set_attack_unarmed(1,35,50,W_SLASH,50,"left talon");

  set_hitloc_unarmed(A_HEAD, (10),5,"head");
  set_hitloc_unarmed(A_BODY,({20,35,50}),25,"body");
  set_hitloc_unarmed(A_R_FOOT,({40,25,30}),10,"right leg");
  set_hitloc_unarmed(A_L_FOOT,({40,25,30}),10,"left leg");
  set_hitloc_unarmed(A_L_ARM,({30,25,50}),25,"left wing");
  set_hitloc_unarmed(A_R_ARM,({30,25,50}),25,"right wing");
 
  add_prop(LIVE_I_SEE_INVIS, 5);
  add_prop(LIVE_I_ATTACK_THIEF, 1);
  add_prop(LIVE_I_SEE_DARK,20);
  add_prop(LIVE_I_NO_CORPSE,1);
  add_prop(LIVE_I_UNDEAD,50);
  add_prop(LIVE_I_NEVERKNOWN,1);
  add_prop(LIVE_I_QUICKNESS, 75 + random(25));
  add_prop(NPC_I_NO_RUN_AWAY,1);
  add_prop(NPC_I_NO_LOOKS,1);

  set_cact_time(10);
   add_cact("emote lets out a wail of anger and pain.");
   add_cact("scream");
   add_cact("emote raises "+query_possessive()
           +" great wings for a strike.");
   add_cact("emote wheezes: This form you may destroy, but I "+
            "am cursed to inhabit another again.");

  set_act_time(20);
   add_act("growl evil");
   add_act("emote stretches "+query_possessive()+" great wings out.");
   add_act("emote beats "+query_possessive()+" great wings and "+
       "rises above the ground.");
   add_act("emote wheezes: Here I remain until I redeem myself.");
   add_act("emote wheezes: There is no death for me, only respite "+
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
        "ourselves in eyes of the Gods.", 1);

}

/* For the solamnic Knights */
query_knight_prestige() { return(80); }

/* Should I attack this guy? */
int
do_this_check(object tp)
{
    string  occ;
    int i;
    alarm_id = 0;

    if (query_attack())
        return 0;   // always concentrate on fighting

    if (!present(tp, environment(TO)))
        return 0;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 2)
            command("bow respect "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +" Upon "+
                "wings of wrath shall the Enemies of Sybarus "+
                "meet their ends!");
        if (i == 6)
            command("say to "+ tp->query_real_name() +" I will "+
                "not fail Sybarus again!");
        return 0;
    }
    if (IS_INFIDEL(tp))
    {        
        if (i < 6)
        {
            command("shout Infidel! Only by your death may I "+
                "redeem myself!");
            command("wield all");
        }
        return 1;
    }    
    if (UND(tp) > 0)     // respect my friends
    {
        set_alarm(1.0, 0.0, &do_respect(this_player()));
        return 0;
    }
    if (tp->query_npc())
        return 0;       // don't kill each other

    return 1; // Yes. Kill anyone else.
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
    if (do_this_check(this_player()) &&
        (monster_attack_chance == 0) || 
        (random(100) < monster_attack_chance))
        alarm_id = set_alarm(itof(random(4) + 1), 0.0,
            &do_slay(this_player()));
}

void
init_living()
{
    ::init_living();

    if (alarm_id)
        return;
    if (do_this_check(this_player())) 
       alarm_id = set_alarm(itof(random(4) + 1), 0.0, 
           &do_slay(this_player()));
}  

/* 
 * Ok, I'll attack, but only if I'm not busy killing
 * someone else right now.
 */
void
do_slay(object victim)
{
    if (query_attack())
        return; // always concentrate on fighting
   command("kill "+victim->query_real_name());
}

/*
 * Show respect to my undead comrades.
 */
void
do_respect(object undead)
{
    string *ways = ({"deep","resp","arch","cold","menac"});
    command("bow "+ one_of_list(ways) +" "+
        TP->query_real_name());
    return;
}

void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    foos -= ({ killer });
    killers = (foos)->query_name();

    /* Logging death for various reasons */
    // This line is causing problems with call to do_die, so not logging
    // STATSERV_LOG_EVENT("dead", "Wights killed");
    SCROLLING_LOG(DEATH_LOG, "Wight killed by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

   command("cackle insane");
   command("emote dissipates into a swirling cloud of "
         +"black smoke.");

   ::do_die(killer);
}
