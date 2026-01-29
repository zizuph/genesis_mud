#pragma strict_types

inherit "/d/Genesis/ship/captain.c";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
inherit REMEMBER;

#define TICKET ANSALON_LINE + "ticket"


object ship;

void
set_ship(object s)
{
    ship=s;
}

void
create_captain()
{
    set_name("mizzen");
    add_name("captain");
    add_name("seaman");
    set_adj(({"old", "grizzled"}));
    set_long("This sea captain is close to retirement age. "+
      "He is old and bent, and his face is like wrinkled leather "+
      "from many years of exposure to the elements.\n");
    set_ticket(TICKET);
    add_prop(OBJ_M_NO_ATTACK, "You feel this man is "+
      "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
      "harmlessly on thin air.\n");
    set_chat_time(45);



    set_living_name("_GONT_ANSALON_CAPTAIN");
    set_race_name("human");
    default_config_npc(60);
    set_skill(SS_SWIM,100);
    set_skill(SS_UNARM_COMBAT,45);
    set_skill(SS_DEFENCE,34);

    heal_hp(10000);
    set_hp(50000);


    set_alignment(200);

    config_default_trade();

    setuid();
    seteuid(getuid());

    trig_new("%w 'introduces' %s", "react_introduce");

    set_hp(50000);

    set_m_in("limps in");
    add_act("emote groans as he rubs his aching back.");


    set_ticket(TICKET);
    set_price(24);
    set_newbie_stats(25);
}


void
intro_hook(string str)
{
    command("introduce myself");
    command("bow");
}
void
add_introduced(string str)
{

    ::add_introduced(str);
    return;
}
