/*
* Created by: Chaos
* Date: 18 April 1995
*
* File: /d/Cirath/katakoro/wep/hammer.c
* Comments: Smith's Hammer	,edited by Luther Sept 2001
*/

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Cirath/defs.h"

void
create_weapon()
{
	set_name("hammer");
    	set_pname("hammers");
    	set_short("heavy steel hammer");
    	set_pshort("heavy steel hammers");
    	set_long ("There is nothing special about this hammer other than "+
		"it's sturdy weight and fine craftsmanship. It is used by "+
		"the smith to work the heated metal into the desired "+
		"shapes.\n");
    	set_adj("steel");
   	set_adj("heavy");

    	set_hit(9);
    	set_pen(13);
    	
    	set_wt(W_CLUB);
    	set_dt(W_BLUDGEON);
    	set_hands(W_ANYH);    		
    	add_prop(OBJ_I_WEIGHT,9000);
    	add_prop(OBJ_I_VOLUME,1200);
}