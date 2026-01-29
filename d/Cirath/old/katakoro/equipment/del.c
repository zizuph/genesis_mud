/* Leather Del
 * 18 April 1995, Chaos
 */

#include "/d/Cirath/defs.h"
inherit "/std/armour";
#include <wa_types.h>

create_armour()
{
   set_name("del");
   set_adj("leather");
   set_adj("sturdy");
   set_long("This is a sturdy leather kalat, known as a del among the "+
	"people of the steppes.  It is worn by smiths as protection "+
	"against some of the hazards in thier work.\n");
   set_at(A_BODY);
   set_ac(2);
   
 }


