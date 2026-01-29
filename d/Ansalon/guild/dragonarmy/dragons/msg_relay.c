/* message relay from dragon back to the dragon environment
 * based on stone.c from arena stuff
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Ansalon/guild/dragonarmy/dragons/relay";

#include "../guild.h"

void catch_msg(mixed str, object obj)
{
    object dragon = E(TO)->query_dragon();

    if (objectp(dragon) && file_name(E(dragon)) != TEMP_DRAGON_ROOM)
    {
	tell_room(E(dragon), str, dragon->query_msg_relay());
    }
}
