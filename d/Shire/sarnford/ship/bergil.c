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
      ship->stop_ship("With the captain dead, this ship is going nowhere!\n");
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
    set_name("bergil");
    add_name( ({ "man", }) );
    set_living_name("bergil");
    set_race_name("human");
    set_adj(({"slender", "silver-haired"}));
    set_title("Bridgewater, Captain of the Osprey");

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
    add_chat("Have you been to the Sleeping Fisherman? Tell Haestur I sent you!");
    add_chat("Running a ship is hard work.");
    add_chat("I love the sea, she is my true mistress.");
    add_chat("I could really go for a nice bowl of fish stew right now.");
    add_chat("There is nothing quite like the air on the open sea.");
    add_chat("Have you ever considered living the life of a sailor?");
    add_chat("We have a schedule to meet, lets keep it moving lads.");
    add_chat("I have spent my whole life on the water, and I don't regret a single minute.");
    add_chat("The Osprey might not be the largest ship, but she's the fastest!");
    add_chat("Whenever I stop near Sarn Ford, I visit the Sleeping Fisherman");

    set_cchat_time(11);
    add_cchat("What do you think you are doing!");
    add_cchat("Get lost before you really make me angry!");
    add_cchat("I'll show you!");
    add_cchat("That's it, I'm done playing with you!");
    add_cchat("Now you've done it!");
    add_cchat("You're ugly and your mother dresses you funny!");
    add_cchat("What's your problem anyways?");
    add_cchat("Throw this lubber overboard lads!");

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
        
