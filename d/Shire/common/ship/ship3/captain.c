#pragma save_binary

inherit "/d/Genesis/ship/captain";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Shire/common/defs.h"

#define TICKET (SHIP_DIR + "ticket")
#define PRICE  28

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
    set_name("osse");
     set_title("Captain of the Ossiriand");
    add_name("captain");
    set_living_name("osse");
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
    set_alignment(700);
    set_chat_time(12);
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("I see darkness rising again in the East.");
    add_chat("I was once seduced by the darkness but never again.");
    add_chat("Have you been to Michel Delving?");
    add_chat("Gil-galad is lost and will never return to the Havens.");
    add_chat("Cirdan still makes ships that sail west.");
    add_chat("The Prancing Pony in Bree has agreeable company.");
    add_chat("Sybarus is a queer place indeed.");
    add_chat("The caverns were formed by a great rifting of the earth.");

    set_ticket(TICKET);
    set_price(PRICE);

    trig_new("%w 'introduces' %s", "react_introduce");
}



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
        
