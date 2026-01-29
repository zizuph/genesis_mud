/*
 *  A brochure that enables the player to read files with info on the pets.
 *                          Tricky, 13-6-92
 */
inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define PAGEPOS  STAND_DIR + "brochure/"

void
create_object()
{
   set_name("brochure");
   set_name("brochures");
   set_adj("pet");
   set_short("pet brochure");
   set_pshort("pet brochures");
   set_long(break_string(
      "This colourful brochure is filled with pictures of all kinds "
    + "of dogs. It also contains a lot of information about pets. "
    + "Read side 1 to learn more about the contents.\n",70));
}

void
init()
{
   add_action("do_read","read");
}

do_read(str)
{
   string var1;

   if (!str)
      return 0;

   str = lower_case(str);
   if (!sscanf(str,"side %s",var1))
      return 0;

   seteuid(getuid());
   notify_fail("You see nothing of interest on that side.\n");
   if (file_size(PAGEPOS + "side_" + var1 + ".txt") == -1)
      return 0;

   write("You open the brochure on side " + var1 + ".\n");
   say(QCTNAME(this_player()) + " reads a bit in "
     + this_player()->query_possessive() + " brochure.\n");

   write("\n");
   cat(PAGEPOS + "side_" + var1 + ".txt");
   write("\n");
   return 1;
}
