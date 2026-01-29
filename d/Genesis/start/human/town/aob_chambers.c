/* AoB team meeting chambers */

inherit "/std/room";

#include <macros.h>

void
create_room()
{
    set_short("AoB team meeting chambers");
    set_long("This is where the Arch of Balance and his cabinet meet " +
        "to discuss important balance issues.\n"); 

    setuid();
    seteuid(getuid());

    clone_object("/w/postmaster/private/arch_boards/aob_board")->move(this_object(), 1);
}

