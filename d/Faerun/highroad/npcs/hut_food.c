/*
 * Food npc on mountaintop
 * by Finwe, November 2007
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/lib/unique";

void greet(object ob);

nomask void create_monster()
{
    add_adj("withered");
    add_adj("old");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name("human");

    set_gender(G_FEMALE);

    add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
    add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
    add_prop(LIVE_I_ALWAYSKNOWN, 0);

    default_config_npc(55);

    set_short("withered old human");
    set_long("This is a " + short() + ". She has weathered skin and her " +
        "black hair is tied back. Her face is wrinkled from age and she " +
        "has sparking blue eyes, but she appears younger than she looks. " +
        "If you are hungry or thirsty, she can serve you, but why she is " +
        "up on this mountain is a mystery.\n");

    set_act_time(5);
    add_act("emote washes some pots and pans.");
    add_act("emote takes down a dead animal from the ceiling and begins dressing it for food.");
    add_act("emote stirs a pot on the stove.");
    add_act("emote watches you carefully.");
    add_act("emote sweeps the floor clean.");
    
    set_chat_time(5);
    add_chat("Can I get you something to eat?");
    add_chat("Are you thirsty?");
    add_chat("I gets cold up here.");
    add_chat("I have the freshest meat around.");
    add_chat("The cold mountain air is so refreshing.");

}

init_living() 
{
   ::init_living();
   if (interactive(this_player()))
      {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Hi there " + ob->query_nonmet_name() + ". What can I serve " +
      "you?");
}
