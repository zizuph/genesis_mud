/*
* Created by: Chaos
* Date: 15 March 1995
*
* File: /d/Cirath/katakoro/wep/ksword.c
* Comments: Kashik Sword	,edited by Luther Sept 2001
*/

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Cirath/defs.h"

void
create_weapon()
{
	set_name("sword");
    	set_pname("swords");
    	set_short("fine sword");
    	set_pshort("fine swords");
    	set_long ("This is a long straight sword issued only to the "+
		"elite warriors of the Khahan, the Kashik.\n");
    	set_adj("fine");

    	set_hit(31);
   	set_pen(29);
    	
    	set_wt(W_SWORD);
   	set_dt(W_SLASH);
   	set_hands(W_ANYH);  
   	
   	add_prop(OBJ_I_VALUE,139);
   	add_prop(OBJ_I_WEIGHT,2350);
    	add_prop(OBJ_I_VOLUME,400);	
}