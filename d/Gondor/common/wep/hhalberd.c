/* Increased hit/pen, Eowul, 2009 */

inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("halberd");
    set_pname("halberds");
    set_short("heavy halberd");
    set_long("This heavy weapon is the standard weapon for Gondor soldiers.\n");
    set_adj(({"heavy", }));  // add adjectives used in the short or the long!
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_default_weapon(32,39,W_POLEARM,W_IMPALE | W_SLASH,W_BOTH, 0);
   
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 1750);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(32,39) + random(200) - 100);
   
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
