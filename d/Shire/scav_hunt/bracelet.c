/*
 * plain silver bracelet
 */


inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
 
public void
create_object()
{
    seteuid(getuid());

    set_name("bracelet");
    add_name("_shire_bracelet_");
    add_adj(({"plain", "silver"}));
    set_short("plain silver bracelet");
    set_long("This is a " + short() + ". It was hammered from a strip " +
        "of silver until it was smooth. It is oval shaped and large " +
        "enough to be worn on the hand. The bracelet is plain looking.\n");

    set_slots(A_R_HAND);
    set_layers(0);
    set_looseness(0);

}
 
