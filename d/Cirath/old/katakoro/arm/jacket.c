/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/arm/jacket.c
* Comments: Khahan's Jacket	,edited by Luther sept 2001
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
   	set_name("jacket");
   	set_pname("jackets");
   
   	set_adj("silk");
   	set_adj("blue");
   
   	set_short("blue silk jacket");
   	set_pshort("silk blue jackets");
   
   	set_at(A_BODY);
   	set_ac(0);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This blue silk jacket is of the finest quality. The back is "+
		"embroidered with golden dragons which reach around and down the "+
		"arms. It doesn't look like it would be effective armour but it "+
		"does look valuable.\n");   
		
	add_prop(OBJ_I_VALUE,250);	
 }
