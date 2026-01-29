#include "local.h"
#include <macros.h>
#include <stdproperties.h>

#define LIVE_I_BEING_SEARCHED  "_clachdun_live_i_being_searched"
#define LIVE_I_WAS_WARNED      "_clachdun_live_i_was_warned"

void
do_arrest(object player, int infraction)
{
    this_object()->command("say Finish up the arrest code Igneous!!");
}

void
do_fine(object player, int infraction)
{
    this_object()->command("say Finish up the fine code Igneous!!");
}

void
do_lawenforcement(object player, int infraction)
{
    this_object()->command("shout Halt!!");
    this_object()->command("say You are guiltly of the following crimes:");
    // Block off an exit 
    if (infraction & LAW_HIDDEN)
    {
	this_object()->command("reveal "+OB_NAME(player));
	this_object()->command("say to "+OB_NAME(player)+
	  " Walking in the shadows of Clach Dun.");
    }
    if (infraction & LAW_WIELDED)
    {
	this_object()->command("say to "+OB_NAME(player)+
	  " Wielding an offensive weapon within the walls of Clach Dun.");
    }
    if (infraction & LAW_DISGUISED)
    {
	this_object()->command("say to "+OB_NAME(player)+ 
	  " Hiding ones face from the populace of Clach Dun.");
    }
    if (infraction & LAW_ATTACKED)
    {
	this_object()->command("say to "+OB_NAME(player)+ 
	  " Attacking the citizens of Clach Dun.");
    }

    if (infraction & LAW_MURDERED)
    {
	this_object()->command("say to "+OB_NAME(player)+ 
	  " Killing citizens of Clach Dun.");
    }
    if (infraction < LAW_ATTACKED)
    {
	if (!player->query_prop(LIVE_I_WAS_WARNED))
	{
	    this_object()->command("say to "+OB_NAME(player)+
	      " I shall give you a warning to cease these activities, this time.");
	    this_object()->command("say to "+OB_NAME(player)+
	      " Next time you will not be so lucky.");
	    player->add_prop(LIVE_I_WAS_WARNED, 1);
	}
	else if (player->query_prop(LIVE_I_WAS_WARNED) <= 3)
	{
	    do_fine(player, infraction);
	    player->add_prop(LIVE_I_WAS_WARNED, 
	      player->query_prop(LIVE_I_WAS_WARNED) + 1);
	}
	else
	{
	    // Been fined enough, arrest him
	    do_arrest(player, infraction);
	}
    }
    else
    {
	// Been attacking or killing guards try and arrest him.
	do_arrest(player, infraction);
    }
}

void
search_player(object player)
{
    int infraction;

    if (!CAN_SEE(this_object(), player))
	return;
    if (!CAN_SEE_IN_ROOM(this_object()))
	return;
    if (player->query_prop(OBJ_I_HIDE))
	infraction ^= LAW_HIDDEN;

    if (sizeof(player->query_weapon(-1)))
	infraction ^= LAW_WIELDED;

    if (player->query_disguised())
	infraction ^= LAW_DISGUISED;

    if (player->query_prop(LIVE_I_ATTACKED_CITIZEN) >= 10)
	infraction ^= LAW_ATTACKED;

    if (player->query_bloodstained())
	infraction ^= LAW_MURDERED;

    if (infraction)
	do_lawenforcement(player, infraction);
    player->remove_prop(LIVE_I_BEING_SEARCHED);
}

void
init_search()
{
    if (!interactive(this_player()))
	return;
    if (this_player()->query_prop(LIVE_I_BEING_SEARCHED))
	return;
    this_player()->add_prop(LIVE_I_BEING_SEARCHED, 1);
    set_alarm(0.0, 0.0, &search_player(this_player()));
}
