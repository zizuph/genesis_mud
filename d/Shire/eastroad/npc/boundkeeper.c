inherit "/std/monster.c";
 
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

int not_intro;
int intro_alarm, reintro_alarm;

void introduce_me();
void re_intro();

void
create_monster()
{

   set_name("fredregar");
   set_title("Whitfoot, Inn-keeper of the Bounds");
   add_adj(({"sluggish","lazy"}));
   set_long("This hobbit seems mostly asleep.\n");
    set_race_name("hobbit");
    set_gender(0);
   add_act(({"bow","tap","yawn","giggle","sigh slee"}));
     add_act("get worm");
    add_chat("Welcome!");
    add_chat("How are you?");
    add_chat("Have you tried the wine?");

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
    if (!intro_alarm)
        intro_alarm = set_alarm(4.0, 0.0, &introduce_me());
}

void
introduce_me()
{
    command("introduce myself");
    not_intro = 1;
    if (!reintro_alarm)
        reintro_alarm = set_alarm(15.0, 0.0, &re_intro());
}

void
re_intro()
{
    not_intro = 0;
}
