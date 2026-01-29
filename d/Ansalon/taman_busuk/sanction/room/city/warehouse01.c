#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_IN;


void
create_sanction_room()
{
    set_short("A storage building in the harbour area of Sanction");
    set_long("This warehouse is filled with various items, covering the " +
        "floor and stacked along the walls. The opening to the north " +
        "leads out into the harbour.\n");

    add_item("floor","The floor is covered with various items.\n");
    add_item("walls","Lots of crates are stacked along the walls.\n");
    add_item("crates","Lots of them are stacked along the walls.\n");
    add_item("opening","To the north is the harbour.\n");
    add_item("harbour","The harbour is to the north.\n");
    
    add_exit(SCITY + "pier06", "north");
}


