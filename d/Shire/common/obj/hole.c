inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "defs.h"

int hole_size;

void
create_object()
{
   set_name(({"hole","trench","pit","_hole_"}));
   set_adj(({"small","ordinary","big","large","average"}));
   set_short("@@my_short");
   set_long("@@my_long");
   add_prop(OBJ_I_NO_GET, 1);
   hole_size = 0;
}

string
my_short()
{
   switch (hole_size)
   {
      case 0: return "small hole";
      case 1: return "ordinary hole";
      case 2: return "big hole";
      case 3: return "ordinary trench";
      case 4: return "average trench";
      case 5: return "deep trench";
      case 6: return "small pit";
      case 7: return "ordinary pit";
      case 8: return "large pit";
   }
}

string
my_long()
{
   return break_string(
      "Someone has dug " + LANG_ADDART(my_short()) + " here. "
    + "You cannot imagine why anyone would even think of digging "
    + LANG_ADDART(my_short()) + " in this spot, since it "
    + "clearly must have cost him some sweat.\n",70);
}

void
increase_size()
{
   object to, env;

   to = this_object();
   env = environment(to);

   if (hole_size < 8)
   {
      hole_size++;
      env->remove_my_desc(to);
      env->add_my_desc("Someone has dug " + LANG_ADDART(my_short())
                     + " here.\n",to);
   }
}
