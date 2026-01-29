inherit "std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
   set_name("rose");
   add_adj("deep");
   add_adj("red");
   set_long(break_string("This delicate flower represents passion and will "+
     "unlock the door to your lust.\n", 76));
add_prop(OBJ_I_VALUE, 25);
}

void init()
{
   ::init();
   add_action("smell", "smell");
}

int
smell(string arg)
{
   notify_fail("Smell what?\n");
   if (arg != "rose" && arg != "roses")
     return 0;
   write("Your nose tingles with the sweet scent.\n");
   return 1;
}

string
query_recover()
{
    return MASTER;
}
