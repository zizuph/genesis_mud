/*
 * boy.c
 *
 * Used in nyreese/cadu_q6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

object stick;
object doggy;

void
equip_myself()
{
    tell_room(ENV(TO), "The boy drops a small yellow dog.\n");
    (doggy = clone_object(ROKEDIR + "npc/doggy"))->move(ENV(TO));
    team_join(doggy);
    doggy->team_join(TO);
    //    command("drop all"); FIXA
    // command("get all");
}

void
equip_me()
{
    seteuid(getuid());

    stick = clone_object(ROKEDIR + "obj/doggystick");
    stick->move(TO);

    set_alarm(1.0, 0.0, equip_myself);
}

string
foo()
{
    if(!doggy)
        return "say someone has killed my little dog!";
}

void
create_monster()
{
    set_name("huovar");
    add_name("boy");
    set_race_name("boy");
    set_short("boy");
    set_title("the dog-handler");
    set_long("The boy is playing with his little dog.\n");

    add_act(({"show stick to dog",
                  "throw stick west", "say fetch!", "@@foo"}));
    add_act("whistle .");
    set_act_time(1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    default_config_npc(15);

    ::create_monster();
}
