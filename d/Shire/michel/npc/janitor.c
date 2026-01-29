inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/prestige.h"

//    Prototypes
void introduce_me();
void re_intro();
void arm_me();
int not_intro, intro_id, re_intro_id;

void
create_monster()
{
   set_name("alva");
   set_title("Baggins, Curator of the Michel Delving Mathom House");
   set_living_name("_alva_");
   add_name(({"doorman","curator","guide"}));
   set_race_name("hobbit");
   set_adj(({"ancient","talkative"}));
   set_gender(0);

   set_long("This hobbit seems to be the maintainer of the Mathom "+
   "house.  He busies about with his broom and carefully stacks "+
   "the mathoms in their proper heaps.\n");

   set_stats(({40,57,38,17,20,39}));
   trig_new("%w 'introduces' %s", "react_introduce");

   MAKE_MONEY;
   set_skill(SS_DEFENSE, 29 + random(50));
   set_skill(SS_UNARM_COMBAT, 30 + random(12));
   set_skill(SS_AWARENESS, 30 + random(19));

   set_chat_time(6);
   add_chat("Welcome to the mathom house!");
   add_chat("I should be getting back to my rocking chair.");
   add_chat("I hate it when it rains.");
   add_chat("Another leak in the roof!");
   add_chat("Old Mr Bilbo has reclaimed his mail-shirt.");
   add_chat("Now where is that... I saw it yesterday.");
   add_chat("Have you spoken with my wife, Rosa?");
   add_chat("Just because you've seen it already doesn't mean you can't see it again!");
   add_chat("I love my job.");
   add_chat("Why don't you ask my wife? She knows where everything is.");
   set_act_time(10);
   add_act("whistle play");
   add_act("dance");
   add_act("sigh depressedly");

   set_restrain_path(({"/d/Shire/michel/mathom"}));
   set_random_move(5);

}

void
arm_me()
{
   object tunic;

   tunic = clone_object(BREE_DIR + "arm/ltunic");
   tunic->move(TO);
   command("wear all");
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
   command("introduce myself");
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

