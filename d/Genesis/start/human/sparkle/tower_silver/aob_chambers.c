/* AoB team meeting chambers */

inherit "/std/room";

#include <macros.h>

void
create_room()
{
    set_short("AoB team meeting chambers");
    set_long("This is where the Arch of Balance and her cabinet meet " +
        "to discuss important balance issues.\n"); 

    setuid();
    seteuid(getuid());

    clone_object("/d/Genesis/postmaster/private/arch_boards/aob_board")->move(this_object(), 1);
}

