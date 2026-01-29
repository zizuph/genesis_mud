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

    reset();
}

enter_inv(ob, from)
{
	::enter_inv(ob, from);
	store_update(ob);
}
reset_room()
{
   if(!present("waterskin",TO))
   {
      clone_object(BAZAAR+"Obj/misc/waterskin.c")->move(this_object());
      clone_object(BAZAAR+"Obj/misc/waterskin.c")->move(this_object());
      clone_object(BAZAAR+"Obj/misc/waterskin.c")->move(this_object());
      clone_object(BAZAAR+"Obj/misc/waterskin.c")->move(this_object());
   }
   if(!present("torch",TO))
   {
      clone_object(BAZAAR+"Obj/misc/ptorch.c")->move(this_object());
      clone_object(BAZAAR+"Obj/misc/ptorch.c")->move(this_object());
   }
   if(!present("sword", TO))
   {
      clone_object(BAZAAR+"Obj/wield/gsword")->move(this_object());
      clone_object(BAZAAR+"Obj/wield/bsword")->move(this_object());
   }
   if(!present("knife", TO))
   { 
      clone_object("/d/Avenir/common/obj/knife")->move(this_object());
      clone_object("/d/Avenir/common/obj/knife")->move(this_object());
      clone_object("/d/Avenir/common/obj/knife")->move(this_object());
   }


}
