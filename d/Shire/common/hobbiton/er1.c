inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"


#include "defs.h"
#include "/sys/ss_types.h"

create_room() {

   object salesman;
   set_short("Main road");
   set_long("@@my_long");

salesman = clone_object("/d/Shire/common/hobbiton/npc/cart_man");
   salesman->move(TO);
   add_exit(STAND_PARENT + "bree/bridge", "east", 0);
   add_exit(STAND_DIR + "er2", "west", 0);
}

my_long() {
   string the_long;

   the_long =  "You are on the great Eastroad, near a bridge. To the east "
             + "is a bridge";

   if (this_player()->query_skill(SS_LOC_SENSE) > 20)
      the_long += " over the river Baranduin, or Brandywine as they call "
                + "it in the Shire. ";
   else
      the_long += " over some river. ";

   the_long += "If you cross the bridge and follow the road east, you will "
         + "eventually end up in Bree. West, lies the rest of the Shire.\n";

   return break_string(the_long,70);
}
