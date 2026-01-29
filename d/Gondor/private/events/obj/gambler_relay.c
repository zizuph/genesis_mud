/*
 * October 1, 2000
 * Mercade and Stern
 */

/*
 * /d/Gondor/private/events/obj/gamber_relay.c
 *
 * This is the tool for the gambler npc to carry to be able to use
 * npcspeak when possessing him.
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("set of cards");
    add_name("gambler_relay");
    
    add_prop(OBJ_M_NO_STEAL, 1);
}

int
npcspeak(string str)
{
    return environment()->npcspeak(str);
}

int
npcsilence(string str)
{
    return environment()->npcsilence(str);
}

int
npcunsilence(string str)
{
    return environment()->npcunsilence(str);
}

int
npcbusy(string str)
{
    return environment()->npcbusy(str);
}

int
npcunbusy(string str)
{
    return environment()->npcunbusy(str);
}

int
npclog(string str)
{
    return environment()->npclog(str);
}

void
init()
{
    ::init();
    add_action(npcspeak, "npcspeak");
    add_action(npcspeak, "ns");
    add_action(npcsilence, "npcsilence");
    add_action(npcunsilence, "npcunsilence");
    add_action(npcbusy, "npcbusy");
    add_action(npcunbusy, "npcunbusy");
    add_action(npclog, "npclog");
}
