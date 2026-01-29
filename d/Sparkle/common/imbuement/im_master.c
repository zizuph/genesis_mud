/* Imbuement master room for automatic imbuements. 
 *
 *
 * Nerull 14/3-09
 */

//inherit "/std/room"; 

#include <stdproperties.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../defs.h"
#include "imbuements.h"
#include "imb_list_wep.h"
//#include "imb_list_arm.h"

#define LOG_DIR  "/d/Sparkle/common/imbuement/log/"

#define LOG(x,y)       write_file(LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )    

int potency = 1;   
int attempts = 0;                         


void
random_imbuement_wep()
{
  
    seteuid(getuid());
    

    // The first imbuement, random(100).
    if (random(2) == 1)
    {  
    	
    	  
    	  // The second imbuement, random(10).
    	  if (random(3) == 1)
    	  {
    	  		object shadow2;
    	  		
    	  		
            shadow2 = clone_object(S_DOMAIN_COMMON_DIR + 
            "imbuement/wep_shadows/"+
            imb_wep[random(sizeof(imb_wep))]);
        
            shadow2->shadow_me(this_object());                                 
            set_alarm(1.0,0.0, &shadow2->init_imb_shadow());
    	  		potency++;
    	  		
    	  		
    	  		// The third imbuement, random(10).
    	  		if (random(5) == 1)
    	      {
    	  				object shadow3;
    	  		
    	  				
            		shadow3 = clone_object(S_DOMAIN_COMMON_DIR + 
            		"imbuement/wep_shadows/"+
            		imb_wep[random(sizeof(imb_wep))]);
        
            		shadow3->shadow_me(this_object());                                 
            		set_alarm(1.0,0.0, &shadow3->init_imb_shadow());
    	  				potency++;
    	  		}
    	  }
    	  
    	     	  
    	  // We cap the potency at 3.
    	  if (potency >= 3)
    	  {
    	  		potency = 3;
    	  }
    	      	  
      	object shadow;
  	  	                
        shadow = clone_object(S_DOMAIN_COMMON_DIR + "imbuement/wep_shadows/"+
        imb_wep[random(sizeof(imb_wep))]);
        
        shadow->shadow_me(this_object());                                 
        set_alarm(1.0,0.0, &shadow->init_imb_shadow());
        
         if (potency == 1)
        {
        		this_object()->set_short("unusual "+this_object()->query_short());
        		return;
        }
        
        if (potency == 2)
        {
        		this_object()->set_short("bizarre "+this_object()->query_short());
        		return;
        }
        
        if (potency == 3)
        {
        		this_object()->set_short("exotic "+this_object()->query_short());
        		return;
        }
        
       
                        
    }
    
    LOG("weapon_imb", capitalize(this_player()->query_real_name())+
    " dropped a imbued weapon in " + 
    file_name(environment(this_player())) + " at " + 
    ctime(time()) + ".\n");
}


