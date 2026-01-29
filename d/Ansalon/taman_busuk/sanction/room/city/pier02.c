#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>

inherit SANCTION_OUT;


void
create_sanction_room()
{
    set_short("Northern pier in the harbour of Sanction");
    set_extra_long("Huge clouds of steam obscure the view of the " +
        "northern shores. This pier stretches north and south. A " +
        "very large open gate leads east into an old warehouse.");

    add_harbour_items();
    add_item(({"warehouse","large warehouse"}),
        "It is a large stone building situated on the edge of the pier.\n");
    add_item(({"gate","large gate","open gate"}),
        "The open gate leads into the large warehouse.\n");

    add_exit(SCITY + "pier01", "north");
    add_exit(SCITY + "pier03", "south");
    add_exit(SCITY + "warehouse03", "east");
}
