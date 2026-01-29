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
    set_name("comb");
    set_pname("combs");

    set_short("golden tarnished hair comb");
    add_adj(({"golden", "tarnished"}));

    set_long("This is a narrow piece of metal with a row of narrow teeth. it is used to untangle or style your hair. The comb looks like it was once nice looking, but now it tarnished. You could probably <comb hair>.\n");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init()
{
        add_action("comb_hair","comb");
}

int comb_hair(string str)
{
    if(str !="hair") return 0;

    say(QCTNAME(TP) + " rakes " + HIS_HER(TP) + short() +
        "through " +HIS_HER(TP) + " hair, tearing out a "+
		"large clump.\n");
    TP->catch_msg("You quickly run the " + short() + " through " +
        "your hair. Accidently it snags up and you tear a"+
		" clump of hair from your scalp.\n");
    return 1;
}

