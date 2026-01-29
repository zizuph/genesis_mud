/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>

inherit "/std/object";

create_object()
{
    seteuid(getuid());
    set_name("bell");
    add_name("cowbell");
    set_pname("bells");
    add_pname("cowbells");

    set_short("copper cowbell");
    add_adj(({"copper"}));

    set_long("This is a "+short()+". It is worn by cows so their " +
        " owner can locate the animal. It rectangular shaped and " +
        "flares out at the bottom. On top is a ring that a piece of " +
        "leather or rope can be strung through to tie around the " +
        "cow's neck. You can probably ring the cowbell\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE,  125);
    add_prop(OBJ_I_VOLUME, 100);

}
void init()
{
    ::init();
    add_action("ring_bell","ring");
}

int ring_bell(string str)
{
    object   target;

    if((str !="the bell") && (str !="the cowbell")
        && (str !="bell") && (str !="cowbell")) return 0;


    say(QCTNAME(TP) + " shakes " + HIS_HER(TP) + " "+short() +
        "wildly, making the bell ring raucously and yells: We need more cowbell !!!'\n");
    TP->catch_msg("You shake your " + short() + ", making it ring raucously and yell: We need more cowbell !!!.\n");
    return 1;
}

