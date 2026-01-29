inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

void
create_container()
{
   set_name("chest");
   set_adj("large");
   add_adj("steel");
   set_short("@@short_descr");
   set_long("@@long_descr");
    add_prop(CONT_I_WEIGHT, 2500);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_M_NO_GET, "You don't want to take your chest, it's fine "+
         "where it is now.\n");
    add_prop(OBJ_I_VALUE, 120);
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
   return "large steel chest";
}

string
long_descr()
{
   return "It is a small chest made from light brown oak and reinforced with steel bars. "+
          "It is standing with its lid closed. Perhaps you can open it?\n";
}