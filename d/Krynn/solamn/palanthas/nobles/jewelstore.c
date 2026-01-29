// Gem storeroom borrowed from Avenir
// Arman 9/11/2003

#include "../local.h"
#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>
 
inherit NOBLE_ROOMBASE;
inherit "/lib/store_support.c";

void 
reset_palan_room()
{
    object gem;

    gem = RANDOM_GEM(GEM_RARE);
    gem->move(this_object());
    gem = RANDOM_GEM(-1);
    gem->move(this_object());
    gem = RANDOM_GEM(-1);
    gem->move(this_object());
    gem = RANDOM_GEM(-1);
    gem->move(this_object());
    gem = RANDOM_GEM(-1);
    gem->move(this_object());
}

void
create_palan_room()
{

    set_short("The jewelry shop display case and store room");
    set_long("This is the store room and display case for the "+
        "jewelry shop.\n");

    add_exit(NOBLE + "jeweler", "up");
    enable_reset(200);
    reset_palan_room();

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
