/* This is the objects that can be cloned into the crates in the 
 * dunlending crates.
 *
 * Raymundo, Spring 2020
 */

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"
#include "defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

/* Function Name:   include_objects()
 * Arguments:       None 
 * Description:     Controls which items get loaded into the 
 *                  crates in the Dunlending tents.
 */
string
include_objects()
{
    setuid();
	seteuid(getuid());
    
    
    int x = random(100);
    switch(x)
    {
        case 0..9:
        return(CAMP_OBJ_DIR + "pinecone");
               
        case 10..19:
        return(CAMP_ARM_DIR + "tunic");
              
        case 20..29:
        return(CAMP_ARM_DIR + "trousers");
               
        case 30..39:
        return(CAMP_ARM_DIR + "dress");
         
        case 40..44:
        return(CAMP_FOOD_DIR + "nuts");
        
        case 45..49:
        return(GEM_DIR + "garnet");        
        
        case 50..54:
        return(CAMP_FOOD_DIR + "dried_meat");
        
        case 55..59:
        return(GEM_DIR + "diamond_black");
        
        case 60..69:
        return(CAMP_FOOD_DIR + "cured_sausage");
        
        case 70..79:
        return(GEM_DIR + "opal");        
        
        case 80..89:
        return(CAMP_FOOD_DIR + "camp_biscut");
        
        case 90..96:
        return(GEM_DIR + "beryl");       
        
        case 97:
        return(CAMP_FOOD_DIR + "magic_suranie");
        
        case 98:
        return(CAMP_FOOD_DIR + "magic_chicory");
        
        case 99:
        return(CAMP_WEP_DIR + JSWORD);
        
    }
}