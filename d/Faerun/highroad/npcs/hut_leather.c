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
    add_adj("dark-skinned");
    add_adj("gray-haired");
    add_prop(LIVE_I_NEVERKNOWN, 1);


    set_race_name("human");
    add_name("human");

    set_gender(G_MALE);

    add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
    add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
    add_prop(LIVE_I_ALWAYSKNOWN, 0);

    default_config_npc(55);

    set_short("dark-skinned gray-haired human");
    set_long("This is a " + short() + ". He has weathered skin and his hair is dark and streaked with gray. black hair is tied back. His hands are stained and wrinkled from many years handling leather. His face is has a few wrinkles around his dark eyes eyes.\n");

    set_act_time(5);
    add_act("emote begins working on a piece of leather.");
    add_act("emote looks up from his work.");
    add_act("emote cuts some leather into pieces and begins sewing them together.");
    add_act("emote watches you carefully.");
    add_act("emote sweeps the floor clean.");
    
    set_chat_time(5);
    add_chat("Can I get you something?");
    add_chat("Working leather is hard work.");
    add_chat("It gets cold up here.");
    add_chat("You won't find any leather goods as good as mine.");
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
   command("say Hi there " + ob->query_nonmet_name() + ". What can I sell " +
      "you?");
}
