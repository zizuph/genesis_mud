/*
* Created by: Chaos
* Date: 9 March 1995
*
* File: /d/Cirath/katakoro/wep/saber.c
* Comments: Camp Guards Saber	,edited by Luther Sept 2001
*/

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Cirath/defs.h"

void
create_weapon()
{
	set_name("saber");
    	set_pname("sabers");
    	set_short("iron saber");
    	set_pshort("iron sabers");
    	set_long ("This is a standard saber, issued to most soldiers "+
		"in the Khahan's army.\n");
    	set_adj("iron");
   	set_adj("standard");

    	set_hit(19);
   	set_pen(13);
    	
    	set_wt(W_SWORD);
   	set_dt(W_SLASH);
   	set_hands(W_ANYH);  
   	
   	add_prop(OBJ_I_VALUE,95);
   	add_prop(OBJ_I_WEIGHT,600);
    	add_prop(OBJ_I_VOLUME,200);	
}