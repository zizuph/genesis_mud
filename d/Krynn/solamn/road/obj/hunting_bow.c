/* Based on Blizzard's ash_bow.c in Qualinesti
 * 
 *
 * Arman 14 December 2003
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <formulas.h>

inherit "/std/bow";


public void
create_bow()
{
    set_adj(({"hunting", "short"}));
    add_name("shortbow");
    set_short("hunting shortbow");
    set_long("This is a well-used hunting shortbow, often used by peasants and farmers " +
      "in catching food for the table as well as protecting their flocks from predators. " +
      "While not as powerful as a longbow, these bows are quite accurate.\n"); 

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 2250);
    add_prop(OBJ_I_VALUE, 600);
    set_wf(TO);

    set_hit(35);
    set_pen(20);
    
    seteuid(getuid(TO));
}