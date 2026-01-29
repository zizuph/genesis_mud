/*
*
* This is the ruling Troll of the trollshaws, its not agressive
* but it is rather tough- Sir Odin
*
*/

inherit "/std/monster.c";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>

#define TNAME ({"Sgnoh","Bahh","Musha","Blaehg"})

#define TLONG ({\
      "has dark red eyes that seem to see everything. "+\
        "It has scars on his face from all the fighting it has been in.\n",\
      "looks very powerful. It would probably wise not to mess with him. "+\
      "looks kind of stupid, just like all the trolls in this area.\n",\
      "is obviously not the one you should try to talk to. He looks "+\
        "big and powerful, the perfect troll soldier!\n",\
      "is laughing at you, a minor snaga in his eyes.\n"})

#define TWEIGHT ({300,250,360,200})
#define THEIGHT ({300,200,450,250})

#define TADJ ({ "red-eyed","balding fierce-looking",\
      "huge","fearsome"})

/* str dex con int wis dis */
#define TSTATS ({\
      ({ 140, 60, 140, 85, 50, 80 }), \
      ({ 170, 50, 170, 40, 70, 50 }), \
      ({ 180, 40, 145, 65, 57, 76 }), \
      ({ 160, 45, 150, 60, 50, 60 }) })

#define OFSKILL ({ 64, 57, 63, 58 })
#define DEFSKILL  ({ 40, 41, 55, 61 })

int time_next;
int alarm_id;

create_monster()
{
   seteuid(getuid());
   TO->create_shaw_troll(random(4));
}

int myrand(int val)
{
   return val-val/4+random(val/2)+3;
}

create_shaw_troll(int r)
{
   set_name(({TNAME[r], "soldier","troll soldier","_shaw_troll_"}));
   set_pname("soldiers");
   set_short(TADJ[r] + " troll soldier");
   set_pshort("troll soldiers");
   set_adj(TADJ[r]);
   set_race_name("troll");
   set_long(
      "This is one of the evil trolls created by Sauron, and ever since "
      +"his death they have been wandering about in this forest. They "
      +"are close relatives with the trolls in Hollin and Khazad-dum, "
      +"but because of their stupidness they still have not found their "
      +"way into Khazad-dum. This creature " + TLONG[r] + "\n");
   
   add_prop(CONT_I_WEIGHT, TWEIGHT[r] * 1000);
   add_prop(CONT_I_HEIGHT, THEIGHT[r]);
   
   set_stats(TSTATS[r]);
   
   set_skill(SS_WEP_AXE,      myrand(OFSKILL[r]));
   set_skill(SS_WEP_CLUB,   myrand(OFSKILL[r]));
   set_skill(SS_WEP_SWORD,    myrand(OFSKILL[r]));
   set_skill(SS_DEFENCE,   myrand(DEFSKILL[r]));
   set_skill(SS_PARRY,   myrand(DEFSKILL[r]));
   set_skill(SS_AWARENESS,   myrand(DEFSKILL[r]-20));
   set_pick_up(80);
   
   set_aggressive(1);
   set_attack_chance(75);
   
   set_alignment(-600 - random(200));
   
   
   set_act_time(5);
   add_act("sigh evil");
   add_act("emote rakes you with his claws.");
   add_act("emote snarls something unintelligable.");
   add_act("emote howls ferociously.");
   add_act("emote looks at you as a possible meal.");
   add_act("emote bellows.");
   add_act("emote screams at you ferociously.");
   add_act("emote swings his weapon at you, narrowly missing " +
       "your head.");
   add_act("emote prepares his weapon for battle.");
   add_act("emote sniffs the air.");
   add_act("emote puts his nose to the ground and sniffs it.");


   set_cact_time(4);
   add_cact("scream");
   add_cact("emote bellows furiously!");
   add_cact("emote charges you, knocking you over into the mud.");
   add_cact("emote howls something unintelligable at you.");
   add_cact("emote works himself into a frenzy and attacks you.");


   alarm_id = set_alarm(1.0, 0.0, "arm_me");
   
   set_m_in("lumbers in and sniffs the air");
   set_m_out("lopes off");
   
}

arm_me()
{
   string *wep = (({"trollsword","trollclub","trollaxe"}));
   clone_object(TROLLSH_DIR + "weapon/" +wep[random(3)])->move(TO);
   command("wield all");
   remove_alarm(alarm_id);
   
}


public void
do_die(object killer)
{
   
   killer->add_prop("_i_killed_trollshaw_trolls",
   TP->query_prop("_i_killed_trollshaw_trolls") + 1);
   
   return ::do_die(killer);
   
}
