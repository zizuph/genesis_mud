/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/wep/knife.c
* Comments: Khahan's knife	,edited by Luther Sept 2001
*/

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Cirath/defs.h"

void
create_weapon()
{
	set_name("knife");
    	set_pname("knives");
    	set_short("fine, black steel knife");
    	set_pshort("fine, black steel knives");
    	set_long ("This long straight knife was made as a gift for the Khahan "+
		"by the smith of the encampent. It is of a fine blackened steel "+
		"identical to his sword and is of excellent workmanship.\n");
    	set_adj("steel");
   	set_adj("fine");
   	set_adj("black");

    	set_hit(13);
    	set_pen(14);
    	
    	set_wt(W_KNIFE);
    	set_dt(W_SLASH);
    	set_hands(W_LEFT);    
    	
    	add_prop(OBJ_I_VALUE,590);		
}