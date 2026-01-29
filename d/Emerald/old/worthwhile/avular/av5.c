/*
 * AV5.c
 * A street in Avular
 * Also contains a door leading into the forge.
 * - Alaron JAN 2000
 */

#include "defs.h"

inherit AVULAR_ROOM;

void
create_avular_room()
{
    set_short("A dark cobblestoned street");
    set_em_long("The narrow street here rounds a corner, winding between "+
                "the dense cluster of buildings. Each building is unique, some "+
                "of them are tall, some short, and none of them plain-looking. Some "+
                "have slanted rooves, others have rounded rooves that appear bent "+
                "or warped somehow. The street disappears into the darkness to the "+
                "west and south. A large, dome-shaped building with a huge stone "+
                "chimney in the center dominates the northeast corner of the street.\n");

    add_item( ({"road", "street", "cobblestoned road", "cobblestoned street",
             "cobblestone road", "cobblestone street"}),
             "The road here is made up of thousands of small to medium-sized, "+
             "finely carved dark stones. Each one has its own unique shape, yet "+
             "when combined with the others, forms a very straight and neat "+
             "path.\n");

    add_item( ({"stones", "cobblestone", "cobblestones"}),
             "The cobblestones are made of a strange, dark rock that seems to "+
             "absorb light from around it, not reflecting anything. The stones "+
             "appear to have all been deliberately and uniquely carved to form "+
             "a straight and neat path.\n");

    add_item( ({"building", "forge", "dome", "dome-shaped building"}),
             "The dome-shaped building is quite large, and made of extremely smooth "+
             "gray stone. The stone is so smooth, that you can't even feel the slightest "+
             "bump or imperfection running your hand along it. Climbing out of the top "+
             "of the center of the dome is a huge stone cylinder that is constantly "+
             "belching out clouds of black and gray smoke.\n");

    add_item( "chimney" ,
             "A large, smooth, cylinder climbs out of the center of the top of the "+
             "dome-shaped building, constantly belching out clouds of black and gray "+
             "smoke.\n");

    add_item( ({"buildings", "rooves", "roof", "warped rooves", "other buildings"}),
             "The buildings surrounding this area of the street are very "+
             "unique and interesting. The ones that you can see through the darkness "+
             "are made of a dull, lifeless-looking, smooth gray stone. Some of them "+
             "have wooden rooves, others have stone rooves of strange shapes and sizes.\n");

    add_door_exit(AV_OBJ+"forge_door1", AVINSIDE+"forge1", "northeast",0,0,1);
    add_exit(AVMAIN+"av4", "west");
    add_exit(AVMAIN+"av6", "south");
}
