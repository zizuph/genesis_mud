/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/arm/robe.c
* Comments: Khahan's Robe	,edited by Luther sept 2001
*/

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include "/d/Cirath/defs.h"
#include "/sys/formulas.h"
#include <ss_types.h>
#include <stdproperties.h>

void
create_armour()
{
   	set_name("robe");
   	set_pname("robes");
   
   	 set_adj("fur");
   	set_adj("thick");
   	   	
   	set_short("thick fur robe");
   	set_pshort("thick fur robes");
   
   	set_at(A_ROBE);
   	set_ac(3);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This broad cuffed robe is lined with the finest, whitest "+
	"ermine that could be found on the steppes. It's leather is strong "+
	"and it looks to be very warm as well.\n");   
	
	add_prop(OBJ_I_VALUE,100);	
 }
