/*
 * Common Board Room for the Vampyrs of Terel 
 *
 * This is a room that is accessible from their study. It allows access
 * for Vampyrs to read the common board.
 * 
 * Created by Petros, April 2009
 */
 
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

public void    load_board();

public void
create_vamp_room()
{
    set_short("Small Alcove");
    set_long("You find yourself in a rather small alcove with not much "
        + "except for a bulletin board. Your only option appears to be "
        + "to go <back> from where you came from.\n");

    add_exit("study", "back");
    
    load_board();
}

void
load_board()
{
    seteuid(getuid(TO));

    clone_object("/d/Genesis/obj/board")->move(TO);
}
