/*
 *  /d/Shire/rooms/town/stable/npc/dark_minion.c
 *
 * The dark minion the black horse must be delivered to
 * By Palmer
 * Date January 2003
 */

inherit "/d/Shire/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>

#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"

#define QUEST_NAME "horse"

/* Function prototypes */
public void take_horse();
public void destruct_me();

void
create_shire_monster()
{
    ::create_shire_monster();

    set_name(({"glacken", "minion"}));
    set_adj("tall");
    set_living_name("glacken");
    set_race_name("human");
    set_title("Dark minion");
    set_long("This skeletal human stands tall, swaying slightly. Dressed in a black cloak " +
             "with the hood pulled down over his face, it is difficult to make out any features.\n");
    set_short("skeletal human");
    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 99);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_INT, 75);
    set_base_stat(SS_WIS, 70);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 200);
    set_skill(SS_RIDING, 300);
    set_alignment(-500);
    set_m_in("steps out of the shadows");

    setuid();
    seteuid(getuid());
}


public void
take_horse()
{
    // object steed;
    // object player;


    //steed = present("steed", environment(this_object()));


    command("say What took you so long? Let me have the horse.");
    command("say Take this scroll back to Ferny and get your reward.");

    command("emote takes the reigns of the horse and leads it east.");
    set_alarm(1.0, 0.0, destruct_me);
}

public void
destruct_me()
{
    TO->remove_object();
}

/*
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
}

void
failed_give(object obj,object from)
{
    command("scowl");
    write(TO->query_The_name(from)+" gives it back to you.\n");
    obj->move(from);
}


void
init_living()
{
    ::init_living();
}

*/