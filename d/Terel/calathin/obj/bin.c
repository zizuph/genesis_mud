inherit "/std/container";
#include "/d/Khalakhor/sys/defs.h"
#include <tasks.h>        
#include <formulas.h> 
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>

int dest_alarm = 0; 


void
create_container()
{
 
    seteuid(getuid(TO));
    
        set_name("bin");
        add_name("can");
        set_short("garbage bin");
        add_adj("garbage");
        set_long("Garbage bin. Looks like you can throw things away in it.\n");
  
   
        add_prop(CONT_I_CLOSED,0);
        add_prop(CONT_I_MAX_WEIGHT, 500000);
        add_prop(CONT_I_MAX_VOLUME, 500000);
        add_prop(CONT_I_WEIGHT, 100000);
        add_prop(CONT_I_VOLUME, 100000);
        add_prop(OBJ_I_VALUE, 8549);
        add_prop(CONT_I_RIGID, 1);
        add_prop(OBJ_M_NO_GET, "It is attatched to the wall by thick "
           +"metal and stone brackets.\n");
        
}

void
dest_objs()
{
    dest_alarm = 0; 

    write("Intense flames rise from the " + TO->short() + " engulfing " +
          "the " + COMPOSITE_DEAD(all_inventory(TO)) + ".\n");
    all_inventory()->remove_object();
    return;
}


public void
enter_inv(object ob, object from)
{

   if (!dest_alarm) 
   { 

     dest_alarm = set_alarm(1.5, 0.0, dest_objs); 
   }

  ::enter_inv(ob, from);
}

