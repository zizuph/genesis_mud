/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

create_object()
{
    seteuid(getuid());
    set_name("feather");
    set_pname("feathers");

    set_short("peacock feather");
    add_adj(({"iridescent", "golden"}));

    set_long("This large feather glistens in the light."+
		" A large eye adorns the furthest reaches of the"+
		" feather. It appears to have been liberated from"+
		" the backside of a large male peacock.\n");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init()
{
        add_action("wave_feather","wave");
}

int wave_feather(string str)
{
    if(str !="feather") return 0;

    say(QCTNAME(TP) + " waves " + HIS_HER(TP) + short() +
        ", promising a tickling beyond all belief.\n");
    TP->catch_msg("You wave your " + short() + ", promising " +
        "a most thorough tickling.\n");
    return 1;
}

