#pragma strict_types

inherit "/d/Genesis/ship/captain";
inherit "/d/Earthsea/lib/width_height";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/sys/filter_funs.h"
#include "defs.h"
inherit REMEMBER;

#define NUM sizeof(MONEY_TYPES)
#define ENV(xx) environment(xx)
#define TICKET AVENIR_LINE + "ticket"


object ship;

void
set_ship(object s)
{
    ship=s;
}

public void
arm_me()
{
    clone_object(AVENIR_LINE + "bodice")->move(this_object(), 1);
    clone_object(AVENIR_LINE + "harem_pants")->move(this_object(), 1);
    clone_object("/d/Avenir/common/clubs/dance/veil")->move(this_object(), 1);
    command("wear all");
}

void
create_captain()
{
    set_name("cerra");
    add_name("captain");
    add_name("witch");
    set_race_name("human");
    set_height("tall");
    set_width("normal");
    set_adj(({"voluptuous", "long-legged"}));
    set_gender(G_FEMALE);
    add_prop(OBJ_M_NO_ATTACK, "You feel this woman "+
      "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
      "harmlessly on thin air.\n");
    set_chat_time(45);
    set_act_time(45);
    set_living_name("_GONT_AVENIR_CAPTAIN_");
    default_config_npc(60);
    set_skill(SS_SWIM,100);
    set_skill(SS_UNARM_COMBAT,45);
    set_skill(SS_DEFENCE,34);

    heal_hp(10000);
    set_hp(50000);
/*
    add_equipment(({ "/d/Avenir/common/clubs/dance/veil",
        AVENIR_LINE + "bodice", AVENIR_LINE + "harem_pants" }));
*/

    add_act("dperf");
    add_act("dansm");
    add_chat("I want to see that travellers on my ship enjoy "+
      "every comfort.");

    add_act("dsmooth");
    add_act("dbored");
    set_alignment(200);

    config_default_trade();

    setuid();
    seteuid(getuid());


    set_hp(50000);

    set_ticket(TICKET);
    set_price(24);
    set_newbie_stats(25);

    set_alarm(0.0, 0.0, &arm_me());
}


void
intro_hook(string str)
{
    command("introduce myself");
    command("dbo");
    return;
}
void
add_introduced(string str)
{

    ::add_introduced(str);
    return;
}

void
init_living()
{
    ::init_living();
    TO->command("dstrut on");
}

string
query_ticket()
{
    return TICKET;
}
