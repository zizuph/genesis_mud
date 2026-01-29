#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_IN;


void
create_sanction_room()
{
    set_short("You are in the Krynn/Ansalon discussion room");
    set_long("This is a room in which you should be quiet!\nYou " +
             "can come here to share your ideas on the board, " +
             "which others from all over Krynn and Ansalon can " +
             "debate with you.\n");
    add_exit(SCITY + "yard", "out");
    clone_object("/d/Krynn/common/obj/disc_board")->move(this_object(), 1);
}


