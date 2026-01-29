/*
* Created by: Chaos
* Date: 9 March 1995
*
* File: /d/Cirath/katakoro/arm/kalat2.c
* Comments: Camp Guard Hide Armour	,edited by Luther sept 2001
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
   
   	set_adj("wool");
   	set_adj("heavy");
   	set_adj("foul-smelling");
   	
   	set_short("foul-smelling, heavy wool kalat");
   	set_pshort("foul-smelling, heavy wool kalats");
   
   	set_at(A_ROBE);
   	set_ac(9);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is the normal form of armour worn by soldiers "+
		"in the Khahan's army.\n");   
		
 }
