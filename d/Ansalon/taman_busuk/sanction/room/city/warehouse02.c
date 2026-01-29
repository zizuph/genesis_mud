#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_IN;


void
create_sanction_room()
{
    set_short("A storage building in the harbour area of Sanction");
    set_long("This warehouse is filled with various items, covering the " +
        "floor and stacked along the walls. There are two openings leading " +
        "back out into the harbour of Sanction.\n");

    add_item("floor","The floor is covered with various items.\n");
    add_item("walls","Lots of crates are stacked along the walls.\n");
    add_item("crates","Lots of them are stacked along the walls.\n");
    add_item("openings","They lead out into the harbour.\n");
    
    add_exit(SCITY + "pier05", "north");
    add_exit(SCITY + "pier06", "west");
}


