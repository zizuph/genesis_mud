/*
* Created by: Chaos
* Date: 18 April 1995
*
* File: /d/Cirath/katakoro/arm/avgkalat.c
* Comments: Average Kalat	,edited by Luther sept 2001
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
   	set_adj("average");
   
   	set_short("average wool kalat");
   	set_pshort("average wool kalats");
   
   	set_at(A_BODY);
   	set_ac(1);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is a simple wool kalat worn by most of the "+
		"residents of the steppes. It is a wool tunic that reaches "+
   		"to the knees and provides some protection from the cold.\n");   
 }


