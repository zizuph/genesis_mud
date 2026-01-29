/*
 * sailor.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>

void equip_myself();

void
create_monster()
{
    set_name("sailor");
    set_short("drunken sailor");
    set_long("He is obviously very stoned.\n");
    set_adj("drunken");

    seteuid(getuid());

    default_config_npc(20);
  
    set_act_time(5);
    add_act("burp");
    add_act("say Gimme an ale, stranger!");
    add_act("puke");
    add_act("say Fiishingg ona shundayafthnoohn is nihece...");
    add_act("emote sings: whaat schall we do with 'he druunkn schailor...");

    set_alarm(1.0, 0.0, equip_myself);
}

void
equip_myself()
{
    if (!present("fishing_rod", TO))
        clone_object(ROKEDIR + "wep/fishing_rod")->move(TO);
    set_alarm(6.0, 0.0, &command("wield all"));
}

void
thank(object from)
{
    object rod;

    if (!objectp(from) || !present(from, environment()))
    {
        command("smile");
        set_alarm(5.0, 0.0, &command("drink all"));
        return;
    }
    
    if (!(rod = present("fishing_rod", TO)))
    {
        command("smile " + OB_NAME(from));
        command("say Thanks! I wish there was something I could give " +
            "you in return.");
        return;
    }
  
    command("smile " + OB_NAME(from));
    command("give rod to " + OB_NAME(from));
    
    set_alarm(600.0, 0.0, equip_myself);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from))
        return;

    if (!ob->id("ale"))
        return;

    set_alarm(1.0, 0.0, &thank(from));
}
