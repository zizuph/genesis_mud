/*
 * road_base.c
 *
 * This is a baseroom for the roads throughout Port
 * Macdunn. Mainly here just for a few common add_items.
 *
 * Khail - July 22, 1997
 */
#pragma strict_types

#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/std/room";
int G_x,
    G_y;

public void
setup_local_coords()
{
    sscanf(file_name(TO),
        "/d/Khalakhor/se_speir/port/room/road_%d_%d", G_x, G_y);
}

public int *
query_local_coords()
{
    return ({G_x, G_y});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public int
is_port_macdunn_road()
{
    return 1;
}

public void
create_khalakhor_room()
{
    string temp;

    this_object()->create_road();
    setup_local_coords();

    add_item(({"town","village","port macdunn","Port Macdunn"}),
        "A fairly quiet little village, Port Macdunn is still " +
        "one of the major port villages on Ruighe Cuideal, " +
        "the southeastern peninsula of Khalakhor. Consisting " +
        "of low buildings made of grey stone, with dirt roads " +
        "twisting about the buildings and the occasional " +
        "wisp of smoke rising out of a chimney from a peat " +
        "fire, it seems to be a fairly quiet village.\n");
    add_item(({"sky"}),
        "Looking up, you see the sky is partially overcast, " +
        "with thick grey clouds drifting through an " +
        "otherwise blue sky.\n");
    add_item(({"clouds","thick clouds", "white clouds",
        "thick white clouds"}),
        "Thick clouds drift lazily across the sky high above " +
        "your head.\n");
    add_item(({"ground","earth","dirt","road"}),
        "The ground here is firmly packed earth on the roads, " +
        "with thick strips of grass filling in anything that " +
        "isn't road nor building.\n");
    add_item(({"grass"}),
        "Thick patches of green grass cover the ground in " +
        "many places which see little traffic.\n");
    add_item(({"buildings","stone buildings","low buildings"}),
        "A number of buildings occupy the village, most " +
        "look pretty much identical with stone walls and " +
        "thatched roofs.\n");
    add_item(({"wall","walls"}),
        "The walls of all the buildings are are made " +
        "in a similar fashion, of large stone blocks " +
        "which have been squared and mortared together " +
        "with clay.\n");
    add_item(({"stones","blocks"}),
        "The stones which make up the walls of most of " +
        "the buildings here are odd-sized blocks of grey " +
        "stone, though moderately well dressed and squared.\n");
    add_item(({"clay"}),
        "The chinks between the stones in the walls are " +
        "packed tightly with river clay to make a more " +
        "secure seal.\n");

    if (G_y == 9 && G_x <= 12)
    {
        add_item(({"shore","shoreline"}),
            "The road here runs atop a low rise overlooking " +
            "the sandy shoreline that marks the edge of " +
            "the harbour Port Macdunn is built on, Cala " +
            "Fasgadh. The wet, white sand stretches off " +
            "into the distance to the east and west.\n");
        add_item(({"sand","white sand"}),
            "The shoreline is covered in thick white sand.\n");
        add_item(({"harbour","water","Cala Fasgadh","cala fasgadh"}),
            "To the south, the dark waters of Cala Fasgadh " +
            "lie, broken only by the piers jutting out south" +
            "wards from the village. Beyond these waters lie " +
            "Lear Min, and beyond that the mighty ocean " +
            "Cuan Siorruidh.\n");
        if (G_x == 9)
            add_item(({"pier","piers"}),
                "Immediately south from here, the piers of " +
                "Port Macdunn jut out southwards into the " +
                "waters of Cala Fasgadh.\n");
        else if (G_x < 9)
            add_item(({"pier","piers"}),
                "The piers of Port Macdunn jut out southwards " +
                "into the waters of Cala Fasgadh further " +
                "east along the shore.\n");
        else 
            add_item(({"pier","piers"}),
                "The piers of Port Macdunn jut out southwards " +
                "into the waters of Cala Fasgadh further " +
                "west along the shore.\n");   
    }

    if (G_x == 17 && G_y < 7)
    {
        add_item(({"embankment","earthen embankment"}),
            "To the east rises the earthen embankment which " +
            "serves as a sort of defensive wall around the " +
            "village. It isn't much to look at, little more " +
            "than hard-packed soil heaped at about a forty " +
            "five degree slope.\n");
    }

    if (G_y >= 8 && G_x >= 13)
    {
            add_item(({"warehouse","warehouses"}),
                "The warehouses seem no different from any of " +
                "the other buildings, except they appear to " +
                "see much more traffic. They're used to briefly " +
                "store good arriving by ship or awaiting for " +
                "transfer to ship between overland shipping.\n");
    }

    if (G_y <= 2)
    {
        add_item(({"embankment","earthen embankment"}),
            "To the north rises the earthen embankment which " +
            "serves as a sort of defensive wall around the " +
            "village. It isn't much to look at, little more " +
            "than hard-packed soil heaped at about a forty " +
            "five degree slope.\n");
    }

    if (G_x == 3)
    {
        add_item(({"embankment","earthen embankment"}),
            "To the west rises the earthen embankment which " +
            "serves as a sort of defensive wall around the " +
            "village. It isn't much to look at, little more " +
            "than hard-packed soil heaped at about a forty " +
            "five degree slope.\n");
    }
 
}
    
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        (ROAD_MESSAGES)->start_messages();
}
