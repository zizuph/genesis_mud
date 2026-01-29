// -*-C++-*-
// file name: ~Avenir/common/port/mon/sailor.c
// creator(s): Boriska, Aug 1995
// last update:
// purpose:    NPC for port area, carries brass knuckles for right hand.
// note:
// bug(s):
// to-do:

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include "/d/Avenir/common/common.h"

inherit "/std/monster";

private int alarm_id;

void equip_me();

void
create_monster()
{
    set_name("sailor");
    set_adj("weathered");
    add_adj("sad");
    add_name("sailor2");
    set_race_name("human");
    set_stats(({80, 90, 90, 70, 70, 70}));
    set_default_answer("@@default_answer", 1);
    set_chat_time(3);
    add_chat("I have seen it, I have seen it!");
    add_chat("Beware of the evil down there....");
    add_chat("It is still down there.....");
    add_ask("octopus","@@tell_octo");
    set_act_time(20);
    add_act("sigh");
    add_act("stare");

    set_skill( SS_DEFENSE, 100 );
    set_skill( SS_UNARM_COMBAT, 100 );
    set_skill( SS_AWARENESS, 40 );
    equip_me();
}

void
equip_me()
{

  int i;

  seteuid(getuid());

  MONEY_MAKE_SC(random(25))->move(this_object(), 1);
  clone_object(PORT + "obj/jacket")->move(this_object(),1);
  clone_object(PORT + "obj/oilskin_cloak")->move(this_object(),1);
  command("wear all");

  for (i = 0; i < 5; i++)
    clone_object(PORT + "obj/rum")->move(this_object(),1);
}

string
default_answer()
{
    int i;

    this_player()->catch_msg("The poor man stares at you with " +
        "wild open eyes.\n");
    set_alarm(5.0, 0.0, &command("shiver"));


    i = random(5);

    switch(i)
    {
        case 0:
        {
            return "emote falls down on his knees with " +
                "wild staring eyes in a silent prayor";
        }
        case 1:
        {
            return "say Do not go down there. It will take you if you " +
                "do not beware....";
        }
        case 2:
        {
            return "emote looks at the water with the frightened " +
                "look of a man who knows he is about to die";
        }
        case 3:
        {
            return "say It took the whole crew. ......\n"+
                "It took them all....";
        }
        case 4:
        {
            set_alarm(2.0, 0.0, &command("say Dont go down there"));
            return "emote falls down on his knees and starts " +
                "to cry";
        }
    }
}

int
warn_player(object player)
{
    player->catch_msg("The sailor steps in your way.\n");
    TO->command("shout Dont go down there. It will get you!\n");
    player->add_prop("warned_by_sailor", 1);
    player->set_alarm(25.0, 0.0, remove_prop("warned"));
}

string
tell_octo()
{
    TO->command("say Its down there. Only I managed to escape. " +
        "It took them all...\n");
    return "";
}
