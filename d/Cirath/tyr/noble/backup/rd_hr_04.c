/* rd_hr_04: High road section 4: Serpine, 04-07-95 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
    set_short("central high road");
    set_long("Within the heart of the rich section of the city, nothing "+
             "is outside of the realm of affordability for the residents. "+
             "Small fountains, gardens, structures of wood, and even "+
             "doors with metal reinforcements dot the area. Strange "+
             "spirals of wire top most walls. Just to "+
             "the east a gate leaves the residential area, while some "+
             "mansions can be accessed to the north and northeast.\n");

    add_item(({"garden", "gardens"}), "Most are enclosed in the walls of "+
             "the mansions.\n");

    add_item(({"fountain", "fountains", "small fountains"}), "Sneaking "+
             "past the guards, you discover that they are all just long "+
             "standing illusions. Even the rich of Tyr aren't rich "+
             "enough to waste that much water.\n");

    add_item(({"spiral", "spirals", "wire", "wires", "strange spirals"}), 
             "It isn't wire at all! Someone has gone to the dangerous "+
             "trouble of carefully trimming fast growing, razor-sharp "+
             "bramblevine to form a deadly barrier.\n");

    add_item(({"structure", "structure", "mansions", "mansion"}), "Huge "+
             "and heavily decorated with carvings and art from all over "+
             "Athas and beyond, only the richest citizens could possibly "+
             "afford such luxury.\n");

    add_item("gate", "Its relatively large but wide open.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_NOBLE+"house3.c", "north", 0, 1);
    add_exit(TYR_NOBLE+"house5.c", "northeast", 0, 1);
    add_exit(TYR_NOBLE+"rd_ds_01.c", "east", "@@gate_message", 1);
    add_exit(TYR_NOBLE+"rd_hr_05.c", "southeast", 0, 1);
    add_exit(TYR_NOBLE+"rd_pr_02.c", "west", "@@roof_message", 1);
}

public int
gate_message()
{
    TP->catch_msg("You feel you are being watched as you pass "+
                  "under the large gate.\n");
    return 0;
}
 
public int
roof_message()
{
    TP->catch_msg("The temperature increases as you "
                 +"enter the shade of the Great Roof.\n");
    return 0;
}
