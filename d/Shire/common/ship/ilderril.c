#pragma save_binary

inherit "/d/Genesis/ship/captain";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Shire/common/defs.h"
#define TICKET "/d/Shire/common/ship/har_ticket"
#define PRICE  720

//    Prototypes
void introduce_me();

int alarm_id;
object	ship;

void
do_die(object killer)
{
  if(query_hp() > 0) 
      return;
  if (ship)
      ship->stop_ship("The ship stops; someone killed the captain!\n");
  ::do_die(killer);
}

void
set_ship(object s)
{
    ship=s;
}

void
create_captain()
{
    if(!IS_CLONE) return;
    set_name("ilderril");
    add_name( ({ "man", }) );
    set_living_name("ilderril");
    set_race_name("human");
    set_adj(({"strong", "barrel-chested"}));
    set_title("the Sea Mariner");

    set_stats(({ 60, 60, 60, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_UNARM_COMBAT,85);
    set_skill(SS_DEFENCE,50);
    refresh_mobile();
    set_alignment(700);
    set_chat_time(12);
    set_chat_time(12);
    add_chat("The Elves are leaving, never to return.");
    add_chat("Minas Tirith is still bustling with activity. Trade is good.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("You'll arrive safely when you travel with me.");
    add_chat("Those Corsairs are dangerous, but they've never caught me.");
    add_chat("My ship is one of the fastest on the open seas.");
    add_chat("Fair wind today. We should be able to stay on schedule.");
    add_chat("I think there will be a good wind to sail up coast.");
    add_chat("The open ocean is a dangerous place, but I've sailed it many times.");

    set_cchat_time(11);
    add_cchat("Hey! Are you one of the pirates of Umbar??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Corsairs of Umbar!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_ticket(TICKET);
    set_price(PRICE);

    trig_new("%w 'introduces' %s", "react_introduce");
}


/*
int
buy(string str)
{
    if (TP->query_average_stat() < 15)
    {
        command("say You don't need to buy any ticket.");
        command("smile "+TP->query_real_name());
        command("say Young travel for free.");
        return 1;
    }

    return ::buy(str);
}
*/
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
        
