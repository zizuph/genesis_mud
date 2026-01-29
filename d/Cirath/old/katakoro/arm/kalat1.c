/*
* Created by: Chaos
* Date: 15 March 1995
*
* File: /d/Cirath/katakoro/arm/kalat1.c
* Comments: Kashik Leather Kalat	,edited by Luther sept 2001
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
   	set_name("kalat");
   	set_pname("kalats");
   
   	set_adj("leather");
   	set_adj("black");
   	set_adj("heavy");
   
   	set_short("heavy, black leather kalat");
   	set_pshort("heavy, black leather kalats");
   
   	set_at(A_ROBE);
   	set_ac(15);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is the armour worn only by the elites Kashik guard.\n");   
		
 }

