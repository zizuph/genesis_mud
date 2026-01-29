/*                            <  -- 78 spaces -- >                         */

/* OBJECT:  Pumpkin that can be carved into a jack-o-lantern 
   CALIA DOMAIN  /d/Calia/valkira/objects/pumpkin.c

   Date      Coder      Action    Comment/Purpose
   ------- ----------- -----------------------------
   9/23/99   Valkira    Created   Practice & Halloween object - Thanks Bishop
                                  for the help!
   10/4/99   Valkira    Modified  Check for wielded knife (based on
                                  /d/Calia/central/bog/outer/low/base_side.c)
*/
  
 
// INCLUSIONS AND DEFINITIONS

inherit "std/object";             /* standard object file                  */
#include "/d/Calia/domain.h"      /* Default include file for Calia Domain */
#include <stdproperties.h>        
#include <macros.h>
#include <options.h>
#include <wa_types.h>

#include <ss_types.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>


//  FUNCTIONS 

/* Function : carve_pumpkin()
   Purpose : Determine whether a player has a knife with with to carve.
   Arguments : "carve"
   Returns : 1 if knife, 0 if no knife
*/

int
carve_pumpkin(string with_what)
{

    object tp = this_player();
    object *knife;

    /*  The combination of functions to generate the inventory is redundant,
        but it ensures that any wielded knife will be chosen before any
        unwielded one.  */

     

    if (strlen(with_what) && parse_command(with_what, all_inventory(tp),
        "'pumpkin' 'with' %o ", knife))

    {
        if (knife->query_wielded())
        {
			object jack;
        	object tp = this_player();
        	jack = clone_object("/d/Calia/valkira/jol.c");
        	jack->move(tp);

        	say(QCTNAME(tp) + " pauses, studying the pumpkin," +
                " before placing the " + knife->query_short() +
                " against the pumpkin and beginning to carve" +
                " a jack-o-lantern.\n");
            write("You have just carved a jack-o-lantern." +
                " You can use it as a lamp.\n");
            
 	        remove_object();
	        return 1;
		}


        else

        {
            notify_fail("You must be wielding the knife to" +
                " carve with it.\n");
            return 0;
        }
    }
    else
    {
         notify_fail("Carve what with what?\n");
         return 0;
    }
}



void
init()
{
    ::init();
    add_action(carve_pumpkin, "carve");
}



void
create_object()
{

    /*  VARIABLES  */

    string *shapes = ({"large", "square", "round", "long", "small"});
    int num = random(sizeof(shapes));
      
    set_name("pumpkin");
    set_short(shapes[num]  + " orange pumpkin");
    set_pshort("orange pumpkins");
    set_long("It's a bright orange pumpkin. It is a bit " + shapes[num] + "." +
             " However, you might be able to carve the pumpkin into" +
             " a jack-o-lantern.\n");
    set_adj(shapes[num]);

 
    add_prop(OBJ_I_WEIGHT, 200);
}
 
