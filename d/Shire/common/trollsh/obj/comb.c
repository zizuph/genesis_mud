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
    set_name("comb");
    add_name("ivory comb");
    add_name("_comb");
    set_short("ivory comb");
    set_adj(({"ivory"}));
    set_long("The comb is made of ivory. It has some broken teeth and looks to be in pretty bad shape. Undoubtedly, it belonged to a wealthy woman, but now it's pretty worthless.\n");

    add_prop(OBJ_I_WEIGHT,75);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 75+random(100));
}
