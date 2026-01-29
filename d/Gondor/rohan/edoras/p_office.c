/*
 *  The Edoras post-office, a modification of the Hobbiton post-office
 *
 *  Modified to inherit /d/Genesis/lib/post.c
 *  - Olorin, October 1994
 *  Modified to inherit /d/Gondor/common/lib/post.c
 *  - Olorin, January 1995
 */

inherit "/d/Gondor/common/lib/post";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
   set_short("The post office of Edoras");
   set_long(BSN(
       "This is the post office of Edoras. Many rohirrim are working here "
     + "to deliver mail to everyone in the world, and you notice horses "
     + "riding off in all directions with todays mail. On one wall "
     + "is a big poster with the drawing of a pigeon above it.")
     + get_std_use());

   set_poster_name("big poster");
   create_post();

   add_exit(EDORAS_DIR + "stairs1","east", 0);

}

void
mail_message(string new)
{
  write("\n"+
    "There is"+new+" mail for you in the Edoras post office.\n"+
    "  (Far southwest in Rohan)\n\n");
}

