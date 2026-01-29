/*   o_chainmail.c
 *
 *  The etheral obsidian chainmail, a pretty
 *  good body armour, breaks slightly easier
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
    return (SFEQDIR + "c_chainmail.c");
}

void create_armour() 
{
    set_name("chainmail");
    set_adj(({"ethereal","obsidian"}));
    set_short("ethereal obsidian chainmail");
    set_long("This chainmail, made of pure obsidian is heavily ornamented with "+
      "gems and pearls, forming a magnificent pattern. The translucent obsidian "+
      "material makes the armourpiece seem ethereal and insubstantial. It feels "+
      "very light, which probably affects its condition.\n");
    set_ac(35);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35 + random(15)));
    
    set_likely_cond(5);
    
    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
}
