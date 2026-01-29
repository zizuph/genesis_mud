/* A crude, yet effective weapon in the hands of a troll. 
   Code (c) 1999 to Damian Horton.
*/

#pragma strict_types 
#pragma save_binary

inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <formulas.h>		

void create_weapon()
{
    set_name("branch");
    add_name("club");
    set_short("thick tree branch");
    set_long("This crude club appears to have been, quite literally "+
	"ripped off of a good sized tree. Similiar force would be "+
	"required to wield it as an effective weapon, but, given its "+
	"size and weight, the results are quite impressive when it "+
	"is so employed.\n");	
    set_adj("thick");
    add_adj("tree");

    set_hit(30);
    set_pen(28);

    likely_dull=0;
    likely_corr=0;
    likely_break=18;

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 28000 + random(6000));
    add_prop(OBJ_I_VOLUME, 28000 + random(6000));
    add_prop(OBJ_I_VALUE, random(20));
    add_prop(OBJ_M_NO_BUY,"I can go grab my own tree branches if "+
	"I wanted!\n");

    set_wf(this_object());
}

mixed
wield(object to)
{
    to = this_object();
    if(this_player()->query_stat(SS_STR)<80)
    {
	return("You lack the strength necessary to employ the branch as "+
		"a weapon.\n");
    }
    else
    {
	return 0;
    }
}



