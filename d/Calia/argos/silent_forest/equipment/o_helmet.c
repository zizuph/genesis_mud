/*   o_helmet.c
 *
 *  The light obsidian helmet, a pretty
 *  good helmet, breaks slightly easier
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
    return (SFEQDIR + "c_helmet.c");
}
 
void create_armour() 
{
    set_name("helmet");
    set_adj(({"light","obsidian"}));
    set_short("light obsidian helmet");
    set_long("This helmet, made of pure obsidian is heavily "+
      "ornamented with gems and pearls, forming a magnificent pattern. "+
      "It feels very light, which probably affects its condition.\n");
    set_ac(15);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15 + random(10)));
    
    set_likely_cond(5);
    
    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
}
