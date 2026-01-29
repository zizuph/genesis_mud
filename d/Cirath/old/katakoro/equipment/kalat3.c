/* Empress' Guard Leather Kalat
 * Created 30 March 1995
 * by Chaos
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour()
{
   set_name("kalat");
   set_adj("leather");
   set_adj("white");
   set_adj("heavy");
   set_short("heavy, white leather kalat");
   set_long("This is the armour worn only by the Empress' guard.\n");
   set_at(A_ROBE);
   set_ac(15);
   
 }


