/*   o_greaves.c
 *
 *  The obsidian greaves, a pretty good pair 
 *  of greaves, breaks slightly easier
 *  then regular armours.
 *
 * Baldacin@Genesis, Sep 2003
 * Fixed typo - Jaacar, May 2016
 */
inherit "/std/armour";
#include "../ldefs.h"
#include <formulas.h>
#include <stdproperties.h>

string
query_inverted()
{
    return (SFEQDIR + "c_greaves.c");
}

void
create_armour()
{
    set_name("greaves");
    set_adj("obsidian");
    set_short("pair of obsidian greaves"); 
    set_pshort("pairs of obsidian greaves"); 
    set_long("This pair of greaves, made of pure obsidian is heavily "+
      "ornamented with gems and pearls, forming a magnificent pattern. "+
      "It feels very light, which probably affects its condition.\n");
    set_ac(15);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15 + random(10)));
    
    set_likely_cond(5);
    
    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
}

