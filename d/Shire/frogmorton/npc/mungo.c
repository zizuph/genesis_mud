/*
 * The innkeeper for the Floating Log in Frogmorton
 * Based on the innkeeper at Stonebows.
 * Finwe, September 1998
 */
/* 
inherit "/std/monster.c";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"
*/
#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

//   Prototypes
/*
void re_intro();
void introduce_me();
 
int intro_id, re_intro_id;
int not_intro;
*/ 
void
//create_monster()
create_hobbit()
{
    set_family_name("Bunce");
    set_type(CITIZEN);
    set_name("mungo");
    set_title("Brandybuck, Innkeeper of the Floating Log");
    add_adj(({"tired","slim"}));
    set_long("This hobbit is the proprietor of the Floating Log. " +
         "He's just as famous as his inn and runs around all the " +
         "time as he takes care of his customers.\n");
//    set_race_name("hobbit");
    set_gender(0);
    add_act("smile");
    add_chat ("Welcome to the Floating Log! How are you? Sit a " +
         "spell and have some of our famous beer.\n");
    add_chat("Try our meat pies. Very delicious and just baked today.");
    add_chat("Strange things are afoot in the Shire, or so they say.");
 
    add_act(" throws out a ruffian and shouts: ...and stay out!");
    add_act(" spit shines some mugs.");
    add_act(" runs around and fills some mugs.");
    add_act(" pours some beer for a hobbit.");
   
    set_act_time(10);
    set_chat_time(5);
   
//    set_skill(SS_UNARM_COMBAT,100);
//    set_skill(SS_DEFENCE, 100);
   
//   set_alignment(170);
   
   
    MAKE_MONEY;
    trig_new("%w 'introduces' %s", "react_introduce");
}
 
/* 
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
*/