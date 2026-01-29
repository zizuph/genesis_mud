/*   c_mantle.c
 *
 *  The elegant airy mantle, a pretty
 *  good mantle, breaks slightly easier
 *  then regular armours, Covers both
 *  the standard robe slot and the neck.
 *
 * Baldacin@Genesis, Sep 2003
 * Fixed typo - Jaacar, May 2016
 */
inherit "/std/armour";
#include "../ldefs.h"
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() 
{
    set_name("mantle");
    set_adj(({"elegant","airy"}));
    set_short("elegant airy mantle");
    set_long("This mantle is crafted from an elegant and airy material. It is "+
      "heavily ornamented with gems and pearls which have been sewn onto the "+
      "material. It feels very light, which probably affects its condition. "+
	  "It has been reinforced with some sort of thick cloth around the neck, "+
	  "giving it some protection there too.\n");
    set_ac(15);
    set_at(A_ROBE | A_NECK);
	set_looseness(2);
    
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15 + random(10)));
    
    set_likely_cond(5);
    
    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
}
