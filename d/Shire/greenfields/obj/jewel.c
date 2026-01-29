/*
 * Modification Log:
 * Finwe May 2020 - Updated the description, changed the domain defs file
 * from /common/def to current defs.h, and gave it a name
 */

inherit "/std/object";
#include "/d/Shire/sys/defs.h" 
#include <stdproperties.h>
#include <ss_types.h>

create_object()
{
    set_name("jewel");
    add_name("_leech_jewel_");
    add_name("heart of hollin");
    set_short("dark red jewel");
    add_name("gem");
    set_adj("dark");
    add_adj("red");
    add_adj("dull");
    set_long("The dark red jewel seems to pulse and shift in your hand. " +
        "The jewel is polished and a deep fire seems to burn within. However, " +
        "it gives no illumination whatsover. It is cut perfectly and " +
        "appears to be extremely valuable, although the edges on one side " +
        "of the jewel are slightly worn.\n");

    add_prop(OBJ_I_WEIGHT,3500-random(501));
    add_prop(OBJ_I_VOLUME,1500-random(251));
    add_prop(OBJ_I_VALUE,500+random(93));
}
