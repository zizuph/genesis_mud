/*
* Created by: Chaos
* Date: 30 March 1995
*
* File: /d/Cirath/katakoro/arm/kalat3.c
* Comments: Empress' Guard Leather Kalat	,edited by Luther sept 2001
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
   	set_adj("white");
   	set_adj("heavy");
   	
   	set_short("heavy, white leather kalat");
   	set_pshort("heavy, white leather kalats");
   
   	set_at(A_ROBE);
   	set_ac(15);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is the armour worn only by the Empress' guard.\n");   
		
 }
