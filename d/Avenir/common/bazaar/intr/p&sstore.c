// Alchemist's storeroom (/d/Avenir/common/bazaar/intr/p&sstore.c)
// creator(s):   Lilith, March 20 1997
// last update:  Lilith, 4/7/97
// purpose:      
// note:   
// bug(s):
// to-do:

inherit "/std/room";
inherit "/lib/store_support.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <files.h>
#include <stdproperties.h>

void reset_room();

void
create_room() 
{
    ::create_room();

    set_short("The alchemist's store room");
    set_long("This is the store room for the alchemist's shop.\n");

    add_exit("/d/Avenir/common/bazaar/intr/p&s_shop", "up");

    IN 

//   enable_reset(200);
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
    if (!present("anarex", TO))
    {
        clone_object("/d/Avenir/common/obj/potions/anarex")->move(this_object());
        clone_object("/d/Avenir/common/obj/potions/anarex")->move(this_object());
    }
    if (!present("somnan",TO))
    {
        clone_object("/d/Avenir/common/obj/potions/somnan")->move(this_object());
        clone_object("/d/Avenir/common/obj/potions/somnan")->move(this_object());
    }
    if (!present("lanthan",TO))
    {
        clone_object("/d/Avenir/common/obj/potions/lanthan")->move(this_object());
        clone_object("/d/Avenir/common/obj/potions/lanthan")->move(this_object());
    }
    if (!present("mortar",TO))
    {
        clone_object("/d/Genesis/std/potions/mortar")->move(this_object());
        clone_object("/d/Genesis/std/potions/mortar")->move(this_object());
    }
    if (!present("vial",TO))
    {
        clone_object(POTION_VIAL_OBJECT)->move(this_object());
        clone_object(POTION_VIAL_OBJECT)->move(this_object());
    }
}
