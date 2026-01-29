/*
 * seeker2.c
 * A seeker, in the town of haven
 * Uses the SEEKERBASE file.
 * This one accepts items for the Chalice quest here in Haven.
 * Created by Tibbit, 11 March 1998
 *
 *
 */

#include "../local.h"
#include <stdproperties.h>

inherit SEEKERBASE;

int getting_ready;

void
enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);

    if(getting_ready)
        return;

    if(!(ob->id("_seeker_quest_chalice_")))
    {
        set_alarm(1.0,0.0,"return_it", ob, from);
        return;
    }

    set_alarm(1.0,0.0,"accept_it",ob,from);

}

void
create_seeker()
{
    set_level(6);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_ask(({"chalice","silver chalice"}), "say A silver chalice " +
      "from our temple went missing a few days ago. If you happen " +
      "to find and return it, we would be most appreciative.", 1);

    add_chat("A silver chalice has disappeared from the temple.");
    add_chat("One of our chalices has mysteriously disappeared.");
    add_chat("We've not been able to find the missing silver chalice "+
        "for days.");
    add_chat("A silver chalice from the temple has disappeared.");

    getting_ready=1;

    set_alarm(3.0,0.0,"finish_getting_ready");
    
}

void
finish_getting_ready()
{
    getting_ready = 0;
}


void
return_it(object ob,object from)
{
    command("say I don't want this, sorry.");
    command("emote returns it.");
    ob->move(from);
}

void
accept_it(object ob,object from)
{
    ob->remove_object();

    if(from->test_bit("Krynn", SEEKER_CHALICE_QUEST_GROUP,
		      SEEKER_CHALICE_QUEST_BIT))
    {
        command("say Thanks, but I have no further reward for you.");
    }
    else
    {
        command("say Ah, the missing chalice.  Thank you!");
        from->catch_msg("You feel more experienced.\n");
        from->add_exp(SEEKER_CHALICE_QUEST_EXP);
        from->set_bit(SEEKER_CHALICE_QUEST_GROUP, SEEKER_CHALICE_QUEST_BIT);
	STD_QUEST_LOG("Haven Seeker Chalice", from, SEEKER_CHALICE_QUEST_EXP);
    }

    command("smile");

}


