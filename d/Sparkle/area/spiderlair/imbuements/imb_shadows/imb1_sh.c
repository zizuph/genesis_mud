/*
 * An imbuementeffect/shadow.
 *
 * Nerull 14/3/09.
 */


#include <stdproperties.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../defs.h"



inherit "/std/shadow";


// We add something additional to the regular longdesc of the item.
string
long()
{
		return shadow_who->long()+"Its enchanted by a 0 glyph rune.\n";
}


// Here we add the actual effect we want stowed on the item.
void
make_imb1_effect()
{
	
    //shadow_who->set_hit(50);
    //shadow_who->set_pen(50);
    
    //shadow_who->set_short("glowing " + shadow_who->short());

		return;
}


// Simple check to see if the shadow is present in the item.
int
query_imb1_shadow()
{
		return 1;
}


// Initiation of the shadow on the item.
void
init_imb1_shadow()
{   
		shadow_who->add_prop(I_AM_IMBUED1, 1);
    shadow_who->add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));    
    shadow_who->add_prop(MAGIC_AM_ID_INFO,({ "The "+
    this_object()->short()+" seems to be magical.\n",1,
              "Imbuement effect 0.\n",15,
              "Imbuement effect 0 + 0.\n",30}));
              
    make_imb1_effect();
    
}

