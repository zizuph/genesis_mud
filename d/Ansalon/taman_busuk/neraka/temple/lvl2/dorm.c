/* This is the start room for the PoT.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"
#include <macros.h>

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    ::create_temple_room();

    set_short("The sleeping quarters");
    set_long("This is a large chamber sub-divided into smaller sections " +
        "by thin walls but all sections are open towards the centre of " +
        "the room. In each little section stands a single bed neatly " +
        "made and to the north is an open archway.\n");

    add_item(({"bed", "beds", "single bed"}), "All the beds are identical. " +
        "They are small wooden unadorned beds with a thick wool blanket " +
        "smoothly laid out on each.\n");
    add_item(({"blanket", "blankets"}), "The blankets are made of thick " +
        "black wool.\n");
    add_item("archway", "The archway is decorated with smooth black " +
        "stone with small carvings.\n");
    add_item(({"carvings", "pattern", "vines", "thorny vines"}),
        "The carvings on the archway make up a pattern of thorny vines.\n");

    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);

    add_exit( LVLTWO + "corr4.c", "north", 0, 0, 1 );
}

int
do_start(string str)
{
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    if (!str || str != "here")
    {
        notify_fail("Start where?\n");
        return 0;
    }
    
    if (this_player()->set_default_start_location(MASTER))
        write("You will now start your journeys here.\n");
    else
        write("Problems with setting this as your start location.\n");
    
    return 1;
}

void
init()
{
    ::init();
    
    add_action(do_start, "start");
}
