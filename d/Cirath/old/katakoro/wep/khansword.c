/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/wep/khansword.c
* Comments: Khahan's Sword	,edited by Luther Sept 2001
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
    	set_short("fine, black steel sword");
    	set_pshort("fine, black steel swords");
    	set_long ("This long straight sword was made as a gift for the Khahan "+
		"by the smith of the encampent. It is of a fine blackened steel "+
		"and is of excellent workmanship.\n");
    	set_adj("steel");
   	set_adj("black");
   	set_adj("fine");

    	set_hit(38);
   	set_pen(27);
    	
    	set_wt(W_SWORD);
   	set_dt(W_SLASH);
   	set_hands(W_RIGHT);  
   	
   	add_prop(OBJ_I_VALUE,1350);
   	add_prop(OBJ_I_WEIGHT,2350);
    	add_prop(OBJ_I_VOLUME,400);		
}