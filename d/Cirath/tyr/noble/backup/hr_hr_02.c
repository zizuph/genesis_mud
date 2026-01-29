/* rd_hr_02: High road section 2. */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("southwestern high road");
    set_long("Free of any trace of nearby districts, the Noble's Quarter "+
             "serves as home to merchant princes and landless nobles. "+
             "In this section the poorest of the elite live in small, "+
             "well decorated flats. While nothing like the sprawling "+
             "mansions deeper in, they are still incredibly luxurious "+
             "compared to the cramped and filthy conditions most dwellers "+
             "of the city face: The air even seems better here, helping "+
             "lessen the oppressive effects of the Athasian sun.\n");

    add_item(({"flat", "flats"}), "Most have huge walls or heavy guards, "+
             "but one lies somewhat open to the east. In addition, a "
            +"small building of white marble is north.\n");

    OUTSIDE
    ADD_SUN_ITEM;
    object archives_sign = clone_here("/d/Raumdor/cities/drakmere/ag_sign");
    archives_sign->set_name("banner");
    archives_sign->set_adj("flapping");
    archives_sign->set_short("flapping banner");
    add_exit(TYR_NOBLE+"rd_hr_03.c", "northeast", 0, 1);
    add_exit(TYR_NOBLE+"house1.c", "east", 0, 1);
    add_exit(TYR_NOBLE+"bank.c", "north", 0, 1);
    add_exit(TYR_NOBLE+"rd_hr_01.c", "southwest", 0, 1);
    add_exit("/d/Cirath/notary/archive", "west");


}
