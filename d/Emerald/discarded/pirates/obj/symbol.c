inherit "/std/object";

#include "defs.h"

void
create_object()
{
   set_short("symbol drawn in blood");
   set_name("symbol");
   set_long(
      "This symbol is written in blood, it looks "+
      "like this...\n"+
      "                             \n"+
      "                             \n"+
      "           *     *           \n"+
      "         *         *         \n"+
      "        **         **        \n"+
      "        **    *    **        \n"+
      "        *  *     *  *        \n"+
      "         *         *         \n"+
      "          *       *          \n"+
      "           *     *           \n"+
      "            *   *            \n"+
      "             * *             \n"+
      "              *              \n"+
      "\n"
   );
   add_prop(OBJ_M_NO_GET,1);
   set_alarm(600.0,0.0,"dest_symbol");
   seteuid(getuid());
}

void
dest_symbol()
{
   tell_room(ENV(TO),"The symbol fades away.\n");
   TO->remove_object();
   return;
}

