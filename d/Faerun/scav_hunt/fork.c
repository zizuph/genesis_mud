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
inherit "/lib/keep";

create_object()
{
    seteuid(getuid());
    set_name("fork");
    set_pname("forks");

    set_short("bent fork");
    add_adj(({"bent", "large"}));

    set_long("The large bent fork has seen better days. The tines are bent in all directions and looks unusable. You can probably <play with fork>.\n");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init()
{
        add_action("chew_fork","play");
}

int chew_fork(string str)
{
    if(str !="with fork") return 0;

    say(QCTNAME(TP) + " attempts to put " + HIS_HER(TP) + short() +
        "into " + HIS_HER(TP) + " mouth, but alas, "+
		"even " + HIS_HER(TP) + " mouth isn't that BIG!\n");
    TP->catch_msg("You attempt to use the " + short() + ", but " +
        "even your mouth can't possibly be that BIG!\n");
    return 1;
}

