#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the Armoury.");
    set_em_long("This bright room contains a few low tables in the " +
        "middle of the room flanked to the north and the south by " +
        "racks of armours and weapons. A large lamp suspended from " +
        "the ceiling casts shadows through the room as the flame " +
        "within dances and jumps. Doors lead out of this room to " +
        "the east and the west.\n");


    add_item( ({"lamp", "large lamp"}),
        "A large, iron lamp hangs suspended from the ceiling. Fueled " +
        "by oil and domed by glass, it is functional, but not extravagant.\n");

    add_item( ({"table", "low table", "tables", "low tables"}),
        "The surface of the tables are marked by rings of oil, nicks, " +
        "and scratches. Strewn across their tops are chain links, " +
        "scraps of leather, and other byproducts of armour and weapon " +
        "repair.\n");

    add_item( ({"racks", "rack"}),
        "Long racks filled with armours and weapons line the northern " +
        "and southern walls.\n");

    add_item( ({"armours", "armour"}),
        "The armours which fill the racks are made from a wide variety of " +
        "metals and fabrics. Helms, breastplates, and greaves lie stacked " +
        "neatly side by side. As you look through them, you notice " +
        "many flaws and imperfections upon the pieces lying here and you " + 
        "are unable to find a single piece of usable armour.\n");

    add_item( ({"weapons", "weapon"}),
        "A number of different weapons fill the racks in this room. " +
        "Swords, knives, halberds and bows, all with at least one " +
        "obvious defect, stand one next to another. Some swords do " +
        "not have handles, some knives have broken or badly chipped " +
        "blades, and tens of bows are without strings.\n");
        

    add_exit("yard_08","west");
    add_exit("yard_09","east");

}
