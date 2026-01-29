/* Imbuement masterroom for automatic imbuements. 
 *
 *
 * Nerull 14/3-09
 */

inherit "/std/room"; 

#include <stdproperties.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../defs.h"
#include "imbuement_list.h"



void
create_room()
{  
    add_prop(ROOM_I_INSIDE, 1);   
    add_prop(ROOM_I_LIGHT, 1);

    seteuid(getuid(this_object()));
}



// This function adds a spesific imbuement to a weapon.
void
spes_imbue_me(int i)
{
	  seteuid(getuid());
	
		object shadow;
		
		if (this_object()->query_prop(MAGIC_AM_MAGIC))
    {                      
        return;
    }
	
		switch(i)
    { 
            
        case 0:
        shadow = clone_object(IMB_SH_DIR + "imb0_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb0_shadow());
        break;
                        
        case 1:     
        shadow = clone_object(IMB_SH_DIR + "imb1_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb1_shadow());   
        break;
              
        case 2:
        shadow = clone_object(IMB_SH_DIR + "imb2_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb2_shadow());
        break;
        
        case 3:
        shadow = clone_object(IMB_SH_DIR + "imb3_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb3_shadow());
              
        default:
        break;	 
        
		}
		
}
	 

// This function adds a random imbuement to a weapon.
void
random_imbue_me()
{
	  seteuid(getuid());

		object shadow;
		int imbuement;
		
		imbuement = random(sizeof(imbuement_list));
		
		if (this_object()->query_prop(MAGIC_AM_MAGIC))
    {                      
        return;
    }
	
		switch(imbuement)
    { 
            
        case 0:
        shadow = clone_object(IMB_SH_DIR + "imb0_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb0_shadow());
        break;
                        
        case 1:     
        shadow = clone_object(IMB_SH_DIR + "imb1_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb1_shadow());   
        break;
              
        case 2:
        shadow = clone_object(IMB_SH_DIR + "imb2_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb2_shadow());
        break;
        
        case 3:
        shadow = clone_object(IMB_SH_DIR + "imb3_sh");
        shadow->shadow_me(this_object());                                 
        set_alarm(2.0,0.0, &shadow->init_imb3_shadow());
              
        default:
        break;	 
        
		}
		
}
