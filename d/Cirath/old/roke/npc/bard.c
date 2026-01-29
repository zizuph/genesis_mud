/*
 * bard.c
 *
 * Used in nyreese/cadu_out.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* A bard, givin roses to ladies
Joshua 950128                 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>

void
create_monster()
{
    add_name("bard");
    set_adj("smiling");
    add_adj("dreaming");
    set_race_name("human");
   
    set_long("He seems detached from the troubles" +
             " in this world, dreamingly playing "+
             "his songs. \n");
   
    default_config_npc(30);
   
    set_act_time(10);
    add_act("sing");
    add_act("say Is this the best of all worlds?");
    add_act("say Sometimes I feel like I am "+
            "nothing more than an object...");
    add_act("smile dreamily");
}

void
return_smile(object who)
{
   object obj;
   
   if (obj = present(who, environment())) 
   {
       if ((obj->query_gender() == 1) && (!objectp(present("rose", obj))))
       {
           command("smile at " + OB_NAME(obj));
           command("say You have a beautiful " +
                   "smile " + obj->query_nonmet_name() + ".");
           obj->catch_msg("The bard gives you a rose.\n");
           clone_object(ROKEDIR + "obj/rose")->move(obj);
       }   
   }
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote != "smile") return;

    set_alarm(2.0, 0.0, &return_smile(actor));
}

void
offer_female()
{
   command("say What wouldn't I give to see you smile?");
}

void
init_living()
{
    ::init_living();
    if (TP->query_gender() == 1)
        set_alarm(2.0, 0.0, offer_female);
}
