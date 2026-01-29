/*
 * Miscellaneous junk found in the Trollshaws
 * Designed for no purpose other than to be sold
 * -- Finwe, September 2001
 */
inherit "/std/object";
#include "/d/Shire/common/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("standard");
    add_name("flag");
    add_name("_broken_standard");
    set_short("broken tattered standard");
    set_pshort("broken tattered standards");
    set_adj(({"broken","tattered"}));
    set_long("This is a broken, tattered battle standard. It is " +
        "red and black on a broken pole. On the " +
        "center of the standard is the face of a proud human's " +
        "face being smashed in with a terrible mace.\n");
    add_item(({"pole", "broken pole"}),
        "The pole was once a smooth piece of wood. Now it is " +
        "broken in half with a broken, tattered standard attached " +
        "to the top.\n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 50+random(100));
}
