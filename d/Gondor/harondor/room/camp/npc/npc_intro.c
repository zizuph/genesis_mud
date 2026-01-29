/* Name      : /d/Gondor/harondor/room/camp/npc/npc_intro.c
 * Purpose   : Will handle behaviour towards different guilds
 *             in one handy file.
 * Created by: Sir Toby, Gondor Domain, 2006-03-01
 *
 *   Modified:
 * Eowul, Oktober 12th, 2008 - Added the response on a delay, rather than immediately
 */

#include <macros.h>

void respond_introduced(object player) 
{
    int i;

    if(!objectp(player) || !CAN_SEE(this_object(), player) 
       || !CAN_SEE_IN_ROOM(this_object())) {
        command("say Who's there? I can't see you!");
        return;
    }
   
    if(player->query_wiz_level())
    {
        command("introduce me to " + OB_NAME(player));
        command("say You honour me with your presence, wizard of Genesis!");
        command("bow deep " + OB_NAME(player));
    }
    else if(player->query_guild_name_occ() == "Morgul Mages")
    {
        command("introduce me to " + OB_NAME(player));
        command("say Greetings to you honoured member of the Society!");
        command("bow deep " + OB_NAME(player));
    }
    else if(player->query_guild_name_occ() == "Rangers of the Westlands")
    {
        command("laugh wickedly " + OB_NAME(player));
        command("say Greetings to you filthy scum! Interesting to find you here skulking about.");
        command("say You should not have come here though...");
        command("peer thoughtfully " + OB_NAME(player));

        if(this_object()->id("_stopping_npc"))
        {
            command("say Your last misstake ranger scum!");
            command("kill " + OB_NAME(player));
        }
    }
    else
    {
        command("introduce me to " + OB_NAME(player));
        command("say Greetings to you maggot!");
        command("grin " + OB_NAME(player));
    }
}

void
add_introduced(string name)
{
    set_alarm(2.0, 0.0, &respond_introduced(find_player(name)));
}


