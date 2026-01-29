// This file is whobbit.c, used as a master hobbit file for the weaker bunch
// of hobbits.
// This file borrows from /d/Shire/michel/npc/militia.c
// Dunstable, Jan 31 1995
// N.B. When cloning this monster- call arm_me() before moving the object
// to the room.

/* Copied over & modified from whobbit.c to become the 
 * Storyteller in Gamwich 
 * on 26 February 1995 
 * by Farlong
 */

inherit "/std/monster";
 
#include <macros.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/sys/language.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"
#include "/d/Shire/eastroad/npc/names.h"
#include "../defs.h"
 
#define RNDARM ({"h_shirt","h_robe","h_tunic","h_cloak",\
     "coat","hat","leggings","lshirt","pants","scloak"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({35,44,30,31,29})
#define SKILLDEF ({24,25,33,35,36})

//  Prototypes
void re_intro();
void introduce_me();

int intro_id, re_intro_id;
int not_intro, alarm_id;

void 
create_monster()
{
    int ran,ran3,ranname,ranfam;
 
   if (!IS_CLONE)
      return;
 
    ran=random(8);
    ran3=random(5);
   ranname = random(77);
   ranfam = random(30);

   set_name(MALENAME[ranname]);
   add_name("villager");
   set_title(FAMILYNAME[ranfam]);

   set_pname("hobbits");
   set_race_name("hobbit");
    set_adj("old");
    add_adj("boisterous");
   set_alignment(140 + ran);
    set_long("This fellow is the local storyteller at the "+
        "Golden Wheelbarrow Pub at Gamwich.  He's rather "+
        "drunk, but still a friendly and well-meaning "+
        "hobbit.\n");
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
 
    set_stats(({20,30,20,40,60,30}));
 
   set_skill(SS_WEP_SWORD, SKILLCOM[ran3]);
   set_skill(SS_WEP_KNIFE, SKILLCOM[ran3]);
   set_skill(SS_WEP_POLEARM, SKILLCOM[ran3]);
   set_skill(SS_WEP_CLUB, SKILLCOM[ran3]);
   set_skill(SS_DEFENCE, SKILLDEF[ran3]);
   set_skill(SS_PARRY, SKILLDEF[ran3]);

   clone_tobacco();
 
   set_chat_time(16+ran);
   add_chat("Strange things go on in the East Farthing.");
   add_chat("How are you today?");
   add_chat("Sometimes I think I should be doing real work.");
   add_chat("I love my beer!");
   add_chat("Have you been to Michel Delving?");
    add_chat("The Wheelbarrow special is excellent.  It'll knock "+
        "your socks off!");
    add_chat("Have you heard the one about the donkey?");
    add_chat("Why, when I was your age...");

   set_act_time(16 - ran);
   add_act("yawn");
   add_act("stretch");
   add_act("emote drinks a Wheelbarrow special.");
    add_act("emote smiles drunkenly.");

   set_cact_time(5);
   add_cact("scream");
    add_cact("shout HELP!!!");
    add_cact("say You Bully!");

   MAKE_MONEY;
    trig_new("%w 'introduces' %s", "react_introduce");

}

void
arm_me()
{ 
   object weap;
   object armo;
    object dinero;

        weap=clone_object(GAMWICH_DIR+"wep/st_club");
      weap->move(TO,1);
        armo=clone_object(GAMWICH_DIR+"arm/st_armour");
      armo->move(TO,1);
      armo = clone_object(ER_DIR +"arm/" +"hat");
      armo->move(TO,1);
      TO->command("wear all");

    dinero=clone_object("/std/coins");
    dinero->set_coin_type("gold");
    dinero->move(TO);

    dinero=clone_object("/std/coins");
    dinero->set_coin_type("gold");
    dinero->move(TO);

    command("buy beer");
}

void 
stop_killers(object player)
{
    string race;

       race = player->query_race();

       if (player->query_prop("_i_kill_hobbits_"))
       {
       command("glare at " + race);
       command("shout I knew this "+ race +" was up to no good!");
       command("kill " + race);
       command("wield all");
       return;
       }
}
 
void
init_living()
{
   ::init_living();
   set_alarm(1.0,0.0,"stop_killers",TP);
}
 
public void
attacked_by(object ob)
{ 

    if (!ob->query_prop("_i_kill_hobbits_"))
      ob->add_prop("_i_kill_hobbits_",1);
      command("shout Help! This " + ob->query_race() + " wants to kill me!");
      command("wield all");
      ::attacked_by(ob);
      alarm_id = set_alarm(10.0,20.0,"before_attack");
     return;
}

void
before_attack()
{
    if(TO->query_attack())
    {
        return;
    }
    command("unwield all");
    command("grin maniac");
    remove_alarm(alarm_id);
}

void
react_introduce(string person,string who)
{
   if (not_intro)
      return;
   if (intro_id)   
      {
      if (ftoi(get_alarm(intro_id)[2]) != 0)   
         {
         intro_id = set_alarm(4.0,0.0,&introduce_me());
      } 
   }
}

void
introduce_me()
{
   command("introduce me");
   not_intro = 1;
   if (re_intro_id)
      {
      if (ftoi(get_alarm(re_intro_id)[2]) != 0)
         {
         re_intro_id = set_alarm(15.0,0.0,&re_intro());
       }
   }
}

void
re_intro()
{
    not_intro = 0;
}
