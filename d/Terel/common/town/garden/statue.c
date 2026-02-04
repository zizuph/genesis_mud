inherit "std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
   
   set_name("statue");
   set_short("statue");
   set_long("This tall iron statue takes the shape of an\n" +
      "imposing ancient human, garbed in a robe and draped\n" +
      "with a long mantle. The face of the man is hidden\n" +
      "in the cowl of the mantle.\n");
   
   add_prop(OBJ_I_NO_GET, 1);
   
   
}

void
init()
{
	
   add_action("bow_statue", "bow");
   
   ::init();
}

int
bow_statue(string str)
{
   if(str!="statue") return 0;
   write("You bow before the statue.\n");
   say(QCTNAME(this_player()) + " bows before the statue.\n");
   return 1;
}
