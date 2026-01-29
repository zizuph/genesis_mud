#pragma strict_types

inherit "/d/Ansalon/taman_busuk/sanction/std/i_room_base";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

void
create_sanction_room()
{
    set_short("meeting room for the Dragonarmy in Sanction");
    set_long("This small room below the post office is for "+
        "members of the Dragonarmy and/or the Priesthood to "+
        "meet in solitude.\n");

    add_item(({"wall","walls","stone","stones"}),
        "The walls are made of stone.\n");

    add_exit(SCITY + "po","up",0);

    clone_object(SOBJ + "rack_meet")->move(TO,1);
}
