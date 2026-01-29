/*
 * An imbuement-shadow.
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
#include "../imbuements.h"

inherit "/std/shadow";

int strenght;


// We add something additional to the regular longdesc of the item.
string
long()
{	
		if (strenght == 1)
		{
				return shadow_who->long()+"You notice that it is emitting " +
				"a low-pitched ringing sound.\n";
		}
		
		if (strenght == 2)
		{
				return shadow_who->long()+"You notice that it is emitting " +
				"a dull ringing sound.\n";
		}
		
		if (strenght == 3)
		{
				return shadow_who->long()+"You notice that it is emitting " +
				"a high-pitched ringing sound.\n";
		}
}


// Here we add the actual effect we want stowed on the item.
void
make_imb_effect()
{
	
	  shadow_who->add_prop(HITPEN_WEP_IMB, 1);
	
		if (strenght == 1)
		{
				if (shadow_who->query_hit() < 50)
				{
    				shadow_who->set_hit(50);
    		}
    		
    		if (shadow_who->query_pen() < 50)
				{
    				shadow_who->set_pen(50);
    		} 
    }
    
    if (strenght == 2)
		{
				if (shadow_who->query_hit() < 55)
				{
    				shadow_who->set_hit(55);
    		}
    		
    		if (shadow_who->query_pen() < 55)
				{
    				shadow_who->set_pen(55);
    		} 
    }
    
    if (strenght == 3)
		{
				if (shadow_who->query_hit() < 60)
				{
    				shadow_who->set_hit(60);
    		}
    		
    		if (shadow_who->query_pen() < 60)
				{
    				shadow_who->set_pen(60);
    		} 
    }

		return;
}


// Masking wield for more phat effects.
void
wield(object ob)
{
}


// Masking wield for phat effects.
void
unwield(object ob)
{
}


// Simple check to see if the shadow is present in the item.
int
query_imb_shadow_effect()
{
		return 1;
}


// Initiation of the shadow on the item.
void
init_imb_shadow()
{   
		
		if (shadow_who->query_prop(HITPEN_WEP_IMB))
		{
				remove_shadow();
				return;
		}
		
		strenght = random(3)+1;
		
    shadow_who->add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));    
    shadow_who->add_prop(MAGIC_AM_ID_INFO,({ "The "+
    this_object()->short()+" has an engravement that is magical.\n",1,
              "This weapon sharpened by magical means, doing " +
              "more damage than normal.\n",55}));
              
    make_imb_effect();
}

