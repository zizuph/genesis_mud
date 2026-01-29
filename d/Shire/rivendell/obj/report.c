/*
 * Report of Elladan for Elrond's quest
 * Finwe, June 1999
 */

inherit "/std/object";
#include <stdproperties.h>      /* Properties */

create_object()
{

    set_name(({"parchment", "report"}));
    add_name("_elladan_report_");
    set_short("faded parchment");
    set_long("This parchment is faded and yellow. Nonetheless, " +
        "it still looks strong. Upon it is fine, flowing " +
        "penmanship. Perhaps it was written by an elf.\n");
    add_item(({"writing", "penmanship"}),
        "The flowing letters are beautiful, obviously written " +
        "by a skilled hand familiar with the elven language. " +
        "However, they are undecipherable to your eyes. Perhaps " +
        "it is a secret message designed for certain people or " +
        "elves.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_VOLUME, 5);
}

