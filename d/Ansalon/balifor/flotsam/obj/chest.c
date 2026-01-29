inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

object webnet;

void
create_container()
{
   set_name("chest");
   set_adj("heavy");
   add_adj("battered");
   set_short("@@short_descr");
   set_pshort("heavy battered chests");
   set_long("@@long_descr");
   set_key(CHEST_KEY);
   set_no_pick();
   add_prop(OBJ_I_VALUE,120);
   add_prop(CONT_I_IN,1);
   add_prop(CONT_I_RIGID,0);
   add_prop(CONT_I_TRANSP,0);
   add_prop(CONT_I_WEIGHT, 2500000);
   add_prop(CONT_I_VOLUME,7500);
   add_prop(CONT_I_MAX_WEIGHT, 22500);
   add_prop(CONT_I_MAX_VOLUME,20300);
   add_prop(CONT_I_CLOSED, 1);
   add_prop(CONT_I_LOCK, 1);
}


void
enter_inv(object obj, object from)
{
   if (living(obj))
      {
      write("You cannot put that into the chest.\n");
      return;
   }
   ::enter_inv(obj,from);
}


void
leave_inv(object obj, object to)
{
   ::leave_inv(obj,to);
}


string
short_descr()
{
   return "heavy battered chest";
}

string
long_descr()
{
   return "This is a heavy battered chest made of iron. " +
   "Once it may have been considered a work of art, now " +
   "its sides are badly dented and has been taken over by " +
   "rust.\n";
}
