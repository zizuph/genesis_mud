#include "defs.h"

inherit PAV_ROOM;

public int
po_closed()
{
    write("The post office is currently closed.\n");
    return 1;
}

public int
pub_closed()
{
    write("The pub is currently closed.\n");
    return 1;
}

public string
desc_pav_areas()
{
    return "Toward the edge of the pavilion, just to the left of the " +
        "nearest entrance, an area is set aside for postal services, while " +
        "just across from it, at the other side of the entrance, a few " +
        "tables are set out for travellers who wish to order drinks.  At " +
        "the center of the pavilion lies the information and ticketing " +
        "counter.";
}

void
create_pav_room()
{
    add_exit("pav2", "north");
    add_exit("pav5", "southwest");
    add_exit("pav7", "southeast");
    add_exit("post", "northwest", PO_OPEN ? 0 : po_closed);
    add_exit("pub",  "northeast", PUB_OPEN ? 0 : pub_closed);
    add_information_desk();

    // Override some of the default descriptions
    add_item(({ "pub", "small pub" }), (PUB_OPEN ? 
        "The tiny pub is barely more than a collection of a few tables " +
        "just off to the side of the nearest entrance to the pavilion.\n" :
        "The tiny pub is barely more than a collection of a few tables " +
        "just off to the side of the nearest entrance to the pavilion.  " +
        "It appears to be closed at the moment.\n"));

    add_item(({ "table", "tables", "small tables", "collection of tables" }),
        (PUB_OPEN ? "A few small tables are set out just to the side of the " +
        "nearest entrance, where travellers can rest and order drinks or a " +
        "quick meal.\n" :
        "A few small tables are set out just to the side of the nearest " +
        "entrance where travellers can rest and order drinks or a quick " +
        "meal.  Currently, though, there doesn't appear to be any service, " +
        "and the chairs have been removed from the tables.\n"));       

    add_item(({ "post", "office", "post office", "postal area" }),
        "A small area is set aside to the left of the nearest entrance, " +
        " where travellers can use the postal services.\n");
}
