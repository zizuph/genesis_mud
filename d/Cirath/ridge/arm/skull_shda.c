/*
* Created by: Luther
* Date: Sept 2001, update Feb 2002
*
* File: /d/Cirath/ridge/arm/skull_shda.c
* Comments: Replacement for skull shield in the ruins of the valley in athas
*/

inherit "/lib/keep";
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    	set_name("shield");
    	set_short("rusted steel shield");
    	set_long("An old rusted shield, worn down by time and use. "
    		+"Many dents cover the face of it with just as many patches. "
    		+"Most would think twice before using such a piece of junk. "
    		+"However in these lands you would used anything you can get "
    		+"your hands on.\n");
 
    	set_adj("rusted");
    	add_adj("steel");   
    	
	add_prop(OBJ_I_WEIGHT,5000);
        add_prop(OBJ_I_VOLUME,2200);
	add_prop(OBJ_I_VALUE, 300);
	
	add_prop(OBJ_S_WIZINFO, "The secondary shield to the skull shield.\n");
	set_ac(28);
    	set_at(A_SHIELD);
    	set_wf(TO);	    	
}

public int *
query_shield_slots()
{
return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}