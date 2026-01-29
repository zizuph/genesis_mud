/*
 * An elven brooch
 * Used in Imladris brooch quest
 * Finwe June 1998
 */
 
inherit "/std/object";
 
#include <stdproperties.h>      /* Properties */
 
void
create_object()
{
    set_name("brooch");
    set_adj("silver");
    set_long("This silver brooch is diamond shaped. It is made " +
        "of mithril and quite ancient looking. It has a star " +
        "with eight points engraved on its surface with many " +
        "rays radiating from the star. On the back of the " +
        "brooch you find a broken clasp.\n");
 
    add_item(({"clasp", "broken clasp"}),
        "The clasp is broken, but it appears that the top of " +
        "the clasp is a downturned pin used to secure the item " +
        "to clothing. The bottom part of the clasp is missing.\n");
    add_item(({"star", "star with eight points"}),
        "The star is delicately engraved into the brooch. It " +
        "has eight points and represents an ancient elven house.\n");
    add_item(({"rays", "rays radiating from the star", "star rays"}),
        "The rays are finely etched into the brooch. They emanate " +
        "from the star in all directions.\n");
    add_item(({"surface"}),
        "The surface of the brooch is smooth and decorated with " +
        "an eight pointed star that has rays radiating from it.\n");
 
    add_name("_brooch_quest_");
    add_prop(OBJ_I_VALUE, 1500+random(500));
    add_prop(OBJ_I_WEIGHT, 7);
    add_prop(OBJ_I_VOLUME, 32);
    add_prop(OBJ_I_HIDE, 20+random(15));
 
}
