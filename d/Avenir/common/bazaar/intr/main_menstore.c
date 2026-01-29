// Main Men's Store room (/d/Avenir/common/bazaar/intr/main_menstore.c)
// creator(s):   Lilith Sept 1997
// last update:  March 1998, Sirra added the leather_jacket.c 
// purpose:      
// note:   
// bug(s):
// to-do:

inherit "/std/room";
inherit "/lib/store_support.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <stdproperties.h>

void reset_room();

void
create_room() 
{
	::create_room();

   set_short("The ready-to-wear shop's store room");
   set_long("This is the store room for the Tailor.\n");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


   add_exit(INTR +"main_menshop", "up", 0, 1);
   enable_reset(200);
   reset_room();
}

enter_inv(ob, from)
{
	::enter_inv(ob, from);
	store_update(ob);
}

int
cloak_check(object ob)
{
    return (ob->id("cloak"));
}        

void
reset_room()
{
    object cloak, pants, shirt, scarf, jacket;

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);

    cloak = clone_object(WORN + "mencloaks");
    cloak->create_tailored();
    cloak->move(TO, 1);


    jacket = clone_object(WORN + "leather_jacket");
    jacket->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    pants = clone_object(WORN + "menpants");
    pants->create_tailored();
    pants->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    shirt = clone_object(WORN + "menshirts");
    shirt->create_tailored();
    shirt->move(TO, 1);

    scarf = clone_object(WORN + "menscarf");
    scarf->create_tailored();
    scarf->move(TO, 1);

    scarf = clone_object(WORN + "menscarf");
    scarf->create_tailored();
    scarf->move(TO, 1);

    scarf = clone_object(WORN + "menscarf");
    scarf->create_tailored();
    scarf->move(TO, 1);

    scarf = clone_object(WORN + "menscarf");
    scarf->create_tailored();
    scarf->move(TO, 1);

    scarf = clone_object(WORN + "menscarf");
    scarf->create_tailored();
    scarf->move(TO, 1);

}
