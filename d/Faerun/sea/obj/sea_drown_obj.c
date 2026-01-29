/*
 * /d/Faerun/sea/obj/sea_drown_obj.c
 *
 * Nerull 2020
 */

#pragma strict_types
inherit "/std/object";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <mail.h>
#include <filter_funs.h>
#include <composite.h>
#include "defs.h"

int oxygen;
int object_flag = 0;

public void
create_object()
{
    set_name("_sea_drown_obj");
    add_adj( ({"tansparent"}) );

    set_short("transparent sea_drown_obj");
    set_long("This is the drownobject for the Faerun oceans.\n");

    add_prop(OBJ_S_WIZINFO,"This is the drownobject for the Faerun oceans.\n");
                      
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    add_prop(OBJ_I_INVIS, 100);

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    
    oxygen = 100;
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
} 


int drown_status(object playah)
{
    if (environment(environment(this_object()))->query_prop(FAERUN_UNDERWATER))
    {
        switch(oxygen)
        {
            case 91..100:
            tell_object(environment(this_object()), "Your lungs are still at full capacity.\n");
            break;
            
            case 81..90:
            tell_object(environment(this_object()), "Your lungs are still at near full capacity.\n");
            break;
            
            case 71..80:
            tell_object(environment(this_object()), "Your lungs are still at somewhat full capacity.\n");
            break;
            
            case 61..70:
            tell_object(environment(this_object()), "The level of oxygen in your blood is very fine.\n");
            break;
            
            case 51..60:
            tell_object(environment(this_object()), "The level of oxygen in your blood is fine.\n");
            break;
            
            case 41..50:
            tell_object(environment(this_object()), "The level of oxygen in your blood is ok.\n");
            break;
            
            case 31..40:
            tell_object(environment(this_object()), "Your lungs are starting to feel uneasy.\n");
            break;
            
            case 21..30:
            tell_object(environment(this_object()), "You are getting very uncomfortable with the lack of oxygen in your lungs.\n");
            break;
            
            case 11..20:
            tell_object(environment(this_object()), "Your lungs screams for air.\n");
            break;
            
            case 1..10:
            tell_object(environment(this_object()), "You are out of air very soon!\n");
            break;
        
            default:
            tell_object(environment(this_object()), "Your lung fils with water, and you drown!\n");
            break;
        }
        
        object_flag = 1;

        oxygen = oxygen - 5;
        
        if (oxygen <= 0)
        {
            tell_object(environment(this_object()), "Your lungs fills with water, and you drown!\n");
            
            environment(this_object())->set_hp(0);
            environment(this_object())->do_die(this_object());
            
            remove_object();
            
            return 1;   
        } 

        return 1;        
    }
    
    if (object_flag == 1)
    {
        tell_object(environment(this_object()), "You fill your lungs with fresh air!\n");
        
        object_flag = 0;
    }
    
    return 1;
}

/*
 * Function name: enter_env
 * Description  : Called when we enter an environment.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we are leaving.
 */
void
enter_env(object player, object from)
{
                
    ::enter_inv(player, from);
    

    /*if (present("_sea_drown_obj", player))
    {        
        // One is enough.
        remove_object();
        return;
    }*/
    
    set_alarm(20.0, 20.0, &drown_status(player));
        
    
    return;
}
