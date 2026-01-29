/*
* Created by: Chaos
* Date: 30 March 1995
*
* File: /d/Cirath/katakoro/arm/ekalat.c
* Comments: Empress' Kalat	,edited by Luther sept 2001
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
   	set_adj("white");
   
   	set_short("white wool kalat");
   	set_pshort("white wool kalats");
   
   	set_at(A_ROBE);
   	set_ac(4);
   	set_am(({ 0, -1, 1 }));
   	
   	set_long("This is a beautiful white kalat worn by the Empress.\n");   
 }


