/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/wep/eknife.c
* Comments: Empress' knife	,edited by Luther Sept 2001
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
    	set_short("fine steel knife");
    	set_pshort("fine steel knives");
    	set_long ("This long straight knife was made as a gift by the "+
		"Khahan's smith. It is of a fine steel, probably stolen "+
		"during one of the many raids made by the Khahan's army. "+
		"It is beautifully detailed and of excellent workmanship.\n");
    	set_adj("steel");
   	set_adj("fine");

    	set_hit(12);
    	set_pen(13);
    	
    	set_wt(W_KNIFE);
    	set_dt(W_SLASH);
    	set_hands(W_ANYH);    		
}