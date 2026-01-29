/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/wep/avgknife.c
* Comments: Average knife	,edited by Luther Sept 2001
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
    	set_short("rough iron knife");
    	set_pshort("rough iron knives");
    	set_long ("This is a knife commonly worn by everyone living in the "+
		"steppes. There is nothing remarkable about it and looks to "+
		"be quite sturdy.\n");
    	set_adj  ("bone");

    	set_hit(3);
    	set_pen(3);
    	
    	set_wt(W_KNIFE);
    	set_dt(W_SLASH);
    	set_hands(W_ANYH);    		
}
