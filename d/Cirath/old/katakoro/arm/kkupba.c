/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/arm/kkupba.c
* Comments: Khahan's Kupba	,edited by Luther sept 2001
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
   	set_name("kupba");
   	set_pname("kupbas");
   
   	set_adj("leather");
   	   	
   	set_short("leather kupba");
   	set_pshort("leather kupbas");
   
   	set_at(A_HEAD);
   	set_ac(3);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is a low cap with a band of thick sable on the brow. "+
	"It is of the same design as commonly worn among the members of "+
	"the camp, but this one looks to be of a finer quality.\n");   
	
	add_prop(OBJ_I_VALUE,44);	
 }