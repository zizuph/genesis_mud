/*
* Created by: Chaos
* Date: 18 April 1995
*
* File: /d/Cirath/katakoro/arm/del.c
* Comments: Leather Del		,edited by Luther sept 2001
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
   	set_name("del");
   	set_pname("dels");
   
   	set_adj("leather");
   	set_adj("sturdy");
   
   	set_short("sturdy leather del");
   	set_pshort("sturdy leather dels");
   
   	set_at(A_BODY);
   	set_ac(2);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is a sturdy leather kalat, known as a del among the "+
		"people of the steppes. It is worn by smiths as protection "+
		"against some of the hazards in thier work.\n");  
}		


