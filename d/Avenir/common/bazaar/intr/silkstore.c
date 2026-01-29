// Bazaar Silkstore (/d/Avenir/common/bazaar/intr/silkstore.c)
// creator(s):   Grace Nov 15 1995
// last update:  Added Belly Chains - Hannah 2005
// purpose:      
// note:   
// bug(s):
// to-do:


inherit "/std/room";
inherit "/lib/store_support.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <stdproperties.h>

#define MAX_ITEMS     30
#define MAX_IDENTICAL 3
#define MAX_DEFAULT   30

void
reset_room()
{
    reset_store();
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
 
    store_update(obj);
}

void
create_room() 
{
   set_short("The silk shop's store room");
   set_long("This is the store room for the Silk shop.\n");

   add_exit("/d/Avenir/common/bazaar/intr/silkshop", "up");

   IN 

   set_default_stock(
    ({ "/d/Avenir/common/bazaar/Obj/worn/blouse.c", 5,
       "/d/Avenir/common/bazaar/Obj/worn/trouser.c", 5,
       "/d/Avenir/common/bazaar/Obj/worn/gloves.c", 3,
       "/d/Avenir/common/bazaar/Obj/worn/armlet.c", 5,
       "/d/Avenir/common/bazaar/Obj/worn/girdle.c", 5,
       "/d/Avenir/common/bazaar/Obj/worn/qskirt.c", 3,
       "/d/Avenir/common/bazaar/Obj/worn/toe_ring.c", 1,
       "/d/Avenir/common/bazaar/Obj/worn/belly_chain.c", 3 
    }) );

   enable_reset(200);
   reset_store();
}

