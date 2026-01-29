#pragma save_binary

inherit "/d/Shire/lib/kill_logger";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDCAPTAIN;

//    Prototypes
void introduce_me();
int alarm_id;

void
create_captain()
{
  ::create_captain();
    if(!IS_CLONE) return;
    set_name("riondir");
    add_name("captain");
    set_title("Captain of the Flying Swan");
    set_living_name("_riondir_");
    set_race_name("elf");
    add_adj("smiling");
    add_adj("thoughtful");
    set_stats(({ 60, 60, 60, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_UNARM_COMBAT,85);
    set_skill(SS_DEFENCE,50);
    refresh_mobile();
    //set_alignment(700); - Sorry, no alignment in GSL
    set_chat_time(12);
    add_chat("I see darkness rising again in the East.");
    add_chat("Have you been to Michel Delving?");
    add_chat("Gil-galad is lost and will never return to the Havens.");
    add_chat("Cirdan still makes ships that sail west.");
    add_chat("The Prancing Pony in Bree has agreeable company.");

    trig_new("%w 'introduces' %s", "react_introduce");

    set_kill_log_name("riondir");
}

void
react_introduce(string person,string who)
{
    alarm_id = set_alarm(4.0,0.0,&introduce_me());
}

void
introduce_me()
{
    command("introduce myself");
}

/* solemnian knights prestige */
query_knight_prestige() {return -15;}
        
