/* branch of mistletoe for Holidays
 * -- Finwe, November 2001
 */
#pragma strict_types

inherit "/std/object";
inherit "/cmd/std/command_driver";
inherit "/lib/keep";


#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>
#include <std.h>
#include <ss_types.h>
#include <filter_funs.h>


void
create_object()
{
    setuid(); seteuid(getuid());

    set_short("mistletoe branch");
    set_name("_shire_mistletoe_branch");
    set_name("mistletoe");
    add_name("branch");
     set_adj( ({"festive"}) );
    set_long("This is a "+short()+". Its leaves are pointed, " +
        "green and leathery. Between some of the leaves are small, " +
        "waxy red berries. You can try and get kisses from others " +
        "by doing <mikiss [player]>.\n");
   
    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,   25);

    set_keep(1);
}



void
init()
{
    ::init();
    add_action("raise", "mikiss");
    add_action("raise", "mik");
}


int
raise(string str)
{
    object *oblist;

   
    if(!strlen(str)) // no string supplied
    {
    	write("You smile hopefully, and raise your "+short()+
            " above everyone, hoping they will kiss you.\n");
	    all(" smiles hopefully for a kiss from you, as "+HE_SHE(TP)+
            "raises a "+short()+" above yours and "+HIS_HER(TP)+
            " heads.");
	    return 1;
    }

    oblist = parse_this(str, "[above] %l");


    actor("You raise a "+short()+" above", oblist," and your " +
        "heads, hoping for a kiss.");
    target(" raises a "+short()+" above your head and "+
        HIS_HER(TP)+", hoping for a kiss from you.", oblist);
    all2act(" raises a "+short()+" above",oblist," and "+
        HIS_HER(TP)+" head, hoping for a kiss.");
    return 1;
}
