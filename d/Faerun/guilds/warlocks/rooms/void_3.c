/* /d/Faerun/guilds/warlocks/rooms/void_3.c
 *
 * Warlock-related room.
 *
 * Nerull, 2017
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

void
removeme()
{
    remove_object();
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("In the void outside the fabric of reality");
    
    set_long("You are floating in a black empty void, trapped "
    +"outside the fabric of reality. You sense that you are "
    +"falling downwards into nothingness...\n");

    add_item(({"void", "black void", "black empty void", 
    "nothingness"}),
    "This is a completely black environment, but yet, "
    +"somehow you are illuminated, glowing in the "
    +"darkness of the void. Nothing, no features, "
    +"distance or anything can be seen...\n");
    
    set_alarm(300.0, 0.0, &removeme());
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        object void_paralyze = clone_object(WARLOCK_GUILDDIR
        +"obj/void_3_paralyze.c")->move(this_player(), 1);
    }
}
