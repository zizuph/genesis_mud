// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
// This is part of an unimplemented quest.
// Lilith Jan 2022:
// This is the treasure in the safe once it has been "cracked"
//  by gathering all the incredients to make thermite and then
//  mixing and igniting it.

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Genesis/gems/gem.h"


void
do_decay()
{
	tell_room(environment(this_object()), "The "+ short() +" falls "+
    "apart.\n");
    set_alarm(1.0, 0.0, &remove_object());
}

void
create_receptacle()
{
	 object gem;
	
     set_name("chest");
     add_name(({"box", "strongbox", "safe", "trunk", "_cracked_safe"}));
	 set_short("steel chest");
	 set_long("It is a large steel chest. Something has melted a hole " +
		  "through the lid and down into the locking mechanism, "+
          "disintigrating it. It looks like it could fall apart "+
		  "any moment now.\n");
	 set_adj(({"large", "steel"}));
	 
	 add_prop(CONT_I_WEIGHT, 100000);
	 add_prop(CONT_I_MAX_WEIGHT, 120000);
	 add_prop(CONT_I_VOLUME, 20000);
	 add_prop(CONT_I_MAX_VOLUME, 40000);
	 add_prop(CONT_I_TRANSP, 1);
	 add_prop(CONT_I_RIGID, 1);
	 add_prop(CONT_I_LOCK, 0);
	 add_prop(OBJ_I_BROKEN, 1);
     add_prop(OBJ_M_NO_GET, "It is far too large and heavy.\n");
	 
	 seteuid(getuid(this_object()));
	 
	 // Ring of the Ancients, offers protection against Wasp
	 // and will have some functionality involving Terel dragons.
	 add_object("/d/Terel/common/moor/obj/safe_ring", 1);
	 
	 // Just a pretty vessel you can fill with water and drink from.
	 add_object("/d/Terel/common/moor/obj/goblet", 1);

     // Since this will be repeatable, don't want too much $ in here.
	 MONEY_MAKE_GC(20 + random(12))->move(this_object(), 1);

	 gem = RANDOM_GEM(GEM_EXTREMELY_RARE);	 
	 gem->set_heap_size(3 + random(5));
	 gem->move(this_object(), 1);

	 gem = RANDOM_GEM(GEM_RARE);	 	 
	 gem->set_heap_size(3 + random(5));
	 gem->move(this_object(), 1);
	 
	 add_prop(CONT_I_CLOSED, 0);
	 add_prop("_melted", 1);	 
	 
	 add_item("lid", "The lid of the trunk has a hole melted "+
         "through it.\n");
     add_item(({"lock", "locking mechanism"}), "The lock "+
         "looks like it was turned to slag. It has melted "+
         "away.\n");
		 
	 // This will remove the cracked safe after 10 minutes
	 // so it won't be there when the room resets and the 
	 // locked safe is re-cloned.
     set_alarm(600.0, 0.0, &do_decay());	
}

/* We don't want the two safes in the room so when this one is 
 *  moved to the room it will remove the previous version.
 */  
void
enter_env(object dest, object old)
{
    object safe;
	safe = present("_cottage_safe", environment(this_object()));
    if (safe)
        safe->remove_object();			
}	
