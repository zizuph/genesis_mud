inherit "/std/room";
inherit "/lib/store_support.c";
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>

create_room() 
{
	::create_room();
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit("/d/Avenir/common/bazaar/intr/shop", "down");

   IN 

     clone_object(BAZAAR+"Obj/misc/ptorch.c")->move(this_object());
     clone_object(BAZAAR+"Obj/misc/ptorch.c")->move(this_object());
}

enter_inv(ob, from)
{
	::enter_inv(ob, from);
	store_update(ob);
}
