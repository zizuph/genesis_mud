/* message relay from dragon environment to the dragon back
 * based on stone.c from arena stuff
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Ansalon/guild/dragonarmy/dragons/relay";

#include "../guild.h"

object dragon;

void
set_dragon(object ob)
{
    dragon = ob;
}

void catch_msg(mixed str, object obj)
{
    object back = dragon->query_back();

    if (objectp(back))
    {
	tell_room(back, str, back->query_msg_relay());
    }
}
