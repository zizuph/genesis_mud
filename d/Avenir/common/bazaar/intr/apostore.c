// Apothecary storeroom (/d/Avenir/common/bazaar/intr/apostore.c)
// creator(s):   Lilith, March 20 1997
// last update:  
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

    set_short("The apothecary store room");
    set_long("This is the store room for the apothecary shop.\n");

    add_exit("/d/Avenir/common/bazaar/intr/apoth1", "up");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.



    reset_room();
}

enter_inv(ob, from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
reset_room()
{
    if (!present("ash",TO))
    {
        clone_object("/d/Avenir/common/obj/ashpinch")->move(this_object());
        clone_object("/d/Avenir/common/obj/ashpinch")->move(this_object());
        clone_object("/d/Avenir/common/obj/ashpinch")->move(this_object());
    }
    if (!present("mummy",TO))
    {
        clone_object("/d/Avenir/common/obj/e_corpse")->move(this_object());
        clone_object("/d/Avenir/common/obj/e_corpse")->move(this_object());
    }
    if (!present("feather",TO))
    {
        clone_object("/d/Avenir/common/obj/feather")->move(this_object());
        clone_object("/d/Avenir/common/obj/feather")->move(this_object());
    }
    if (!present("charcoal",TO))
    {
       clone_object("/d/Avenir/common/obj/charcoal")->move(this_object());
       clone_object("/d/Avenir/common/obj/charcoal")->move(this_object());
       clone_object("/d/Avenir/common/obj/charcoal")->move(this_object());
    }
    if (!present("pelt",TO))
    {
        clone_object("/d/Avenir/common/obj/pelt")->move(this_object());
        clone_object("/d/Avenir/common/obj/pelt")->move(this_object());
    }
    if (!present("qarraba",TO))
    {
        clone_object("/d/Avenir/common/bazaar/Obj/misc/qarraba")->move(this_object());
        clone_object("/d/Avenir/common/bazaar/Obj/misc/qarraba")->move(this_object());
        clone_object("/d/Avenir/common/bazaar/Obj/misc/qarraba")->move(this_object());
        clone_object("/d/Avenir/common/bazaar/Obj/misc/qarraba")->move(this_object());
        clone_object("/d/Avenir/common/bazaar/Obj/misc/qarraba")->move(this_object());
    }    
    if (!present("eye",TO))
    {
        clone_object("/d/Avenir/common/bazaar/Obj/misc/eye")->move(this_object());
        clone_object("/d/Avenir/common/bazaar/Obj/misc/eye")->move(this_object());           
    }  
    if (!present("toe",TO))
    {
        clone_object("/d/Avenir/common/bazaar/Obj/misc/toe")->move(this_object());
        clone_object("/d/Avenir/common/bazaar/Obj/misc/toe")->move(this_object());           
    }  

}
