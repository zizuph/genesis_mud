/*
 *  The post office of Pelargir
 *
 *  Olorin, January 1995
 */

inherit "/d/Gondor/common/lib/post";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
   set_short("the post office of Pelargir");

   set_long(BSN(
      "This is the post office in Pelargir, where the citizens and "
    + "travellers deliver letters and mail to be sent to friends, "
    + "relatives and people in other parts of the world. There is "
    + "a regular mail-transport to Minas Tirith, Edoras, Hobbiton "
    + "and Sparkle, among other towns in the world. You may also "
    + "read and write mail here, it will be distributed so that the "
    + "recipient can read it in any other post-office. On one wall "
    + "is a big poster with the picture of a pigeon above it."));

   add_exit(PELAR_DIR + "streets/plaza","northeast", 0, 1);

   set_poster_name("big poster");
   create_post();
}

