/* A room on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";


void
load_board()
{
    seteuid(getuid(TO));

    clone_object("/d/Genesis/obj/board")->move(TO);
}

create_room()
{
    set_short("Tower Common Board");

    set_long("You have arrived at the common board in the Marble Tower." +
        " Here students can keep abreast of major changes across the Realms. "+
        basic_desc + " To the east a corridor stretches.\n");

    add_exit(TOWER + "tower_corr_2_2.c", "east", 0, 1);
    
    load_board();

    make_college_room();
}