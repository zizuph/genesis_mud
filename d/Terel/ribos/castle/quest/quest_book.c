/*  A small book, coded by Vader on 05-25-93
 *
 *  questbook.c
 *
 *  This is a little treasure meant to shake up mortals who want to
 * take the easy path to enlightenment.  If they read it, they will
 * get a message informing them to send mail to me, trying to convince
 * me not to remove some of their experience.  It will tell them that
 * it logged their action (sort of like the Admin's workroom), but why
 * bother.  Ged fell for it   :)
 */
inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>

init()
{
   ::init();
   add_action("read", "read");
}

create_object()
{
   set_name("book");
   set_adj("small");
   set_short("small book");
   set_long(break_string(
   "This is a small, forbidden looking book entitled _Solutions to Major " +
   "Quests_.  It looks as if it wasn't made for the eyes of mortals.\n", 70));

   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_VALUE, 20);

}

read(str)
{
   if(str != "book")
   {
      notify_fail("What?\n");
      return 0;
   }
   write("Your wandering eyes have been noted and logged.  Send mail to " +
         "Vader\n");
   write("within two days to beg for leniency.\n");
   return 1;
}

