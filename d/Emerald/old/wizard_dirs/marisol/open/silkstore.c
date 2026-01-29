// Bazaar Silkstore (/d/Avenir/common/bazaar/intr/silkstore.c)
// creator(s):   Grace Nov 15 1995
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

   set_short("The silk shop's store room");
   set_long("This is the store room for the Silk shop.\n");

   add_exit("/d/Avenir/common/bazaar/intr/silkshop", "up");

   IN 

   enable_reset(200);
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
      clone_object(WORN + "blouse.c")->move(this_object());
      clone_object(WORN + "blouse.c")->move(this_object());
      clone_object(WORN + "blouse.c")->move(this_object());
      clone_object(WORN + "blouse.c")->move(this_object());
      clone_object(WORN + "blouse.c")->move(this_object());

      clone_object(WORN + "trouser.c")->move(this_object());
      clone_object(WORN + "trouser.c")->move(this_object());
      clone_object(WORN + "trouser.c")->move(this_object());
      clone_object(WORN + "trouser.c")->move(this_object());
      clone_object(WORN + "trouser.c")->move(this_object());

      clone_object(WORN + "gloves.c")->move(this_object());
      clone_object(WORN + "gloves.c")->move(this_object());
      clone_object(WORN + "gloves.c")->move(this_object());
      clone_object(WORN + "gloves.c")->move(this_object());
      clone_object(WORN + "gloves.c")->move(this_object());

      clone_object(WORN + "armlet.c")->move(this_object());
      clone_object(WORN + "armlet.c")->move(this_object());
      clone_object(WORN + "armlet.c")->move(this_object());
      clone_object(WORN + "armlet.c")->move(this_object());

      clone_object(WORN + "girdle.c")->move(this_object());
      clone_object(WORN + "girdle.c")->move(this_object());
      clone_object(WORN + "girdle.c")->move(this_object());
      clone_object(WORN + "girdle.c")->move(this_object());

      clone_object(WORN + "qskirt.c")->move(this_object());
      clone_object(WORN + "qskirt.c")->move(this_object());

}
