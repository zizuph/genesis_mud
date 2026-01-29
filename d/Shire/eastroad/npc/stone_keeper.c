inherit "/std/monster.c";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

//   Prototypes
void re_intro();
void introduce_me();
 
int intro_id, re_intro_id;
int not_intro;

void
create_monster()
{
   
   set_name("rudy");
   set_title("Took, Inn-keeper of the Stonebows");
   add_adj(({"tired","slim"}));
   set_long("This hobbit seems to be busy serving beverages.\n");
   set_race_name("hobbit");
   set_gender(0);
add_act("smile");
   add_chat ("Welcome! How are you? Did you ever swim the Brandywine?");
   
   set_act_time(10);
   set_chat_time(5);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);
   
   set_alignment(170);
   
   
   MAKE_MONEY;
   trig_new("%w 'introduces' %s", "react_introduce");
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
