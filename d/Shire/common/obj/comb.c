/*
 * Miscellaneous junk found in the Trollshaws
 * Designed for no purpose other than to be sold
 * -- Finwe, September 2001
 */
inherit "/std/object";
#include "/d/Shire/sys/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("comb");
    add_name("ivory comb");
    add_name("_comb");
    set_short("ivory comb");
    set_adj(({"ivory"}));
    set_long("The comb is made of ivory with several large teeth. It " +
        "looks like it once belonged to a wealthy person for it is too " +
        "beautiful for a common individual.\n");
    add_item(({"large teeth", "teeth", "several large teeth"}),
	    "The large teeth of the comb are smooth. They are about a " +
        "finger's length and rounded at each end.\n");

    add_prop(OBJ_I_WEIGHT,75);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE, 75+random(100));
}

void init() 
{
        add_action("comb_hair","comb");
}

int comb_hair(string str)
{
    if(str !="hair")
    {
        write("Comb what?\n");
        return 1;
    }

    say(QCTNAME(TP) + " runs " + HIS_HER(TP) + " " + short() + 
        " through " + HIS_HER(TP) +" hair several times.\n"); 
    TP->catch_msg("You run your " + short() + " through your hair " +
        "several times.\n");
    return 1;
}                 
