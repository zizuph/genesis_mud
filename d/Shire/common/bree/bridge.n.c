#include "/d/Shire/common/defs.h"
#include "defs.h"
#include "/sys/ss_types.h"

inherit "/d/Shire/room";

create_room() {
    set_short("Brandywine bridge");
    set_long("@@my_long");

    add_item("bridge", break_string(
	  "The bridge looks old but solid, it has been "
	+ "maintained by the Hobbits of the Shire since the old days, "
	+ "when this was part of the duties towards the King at "
	+ "Fornost.\n",70));

    add_item(({"stream","river"}), "@@river_long");

    add_exit(BREE_DIR + "gatekeeper", "east");
    add_exit(STAND_PARENT + "hobbiton/er1", "west");
}

my_long() {
   string the_long;

   the_long = "You are standing on a bridge over ";

   if (this_player()->query_skill(SS_LOC_SENSE) > 20)
      the_long += "the river Baranduin, or Brandywine as the people "
                + "of the Shire call it. ";
   else
      the_long += "some big river. ";

   the_long +=  "Beneath you can see the cold, but clear stream, "
	      + "making its way south.\n";
   return break_string(the_long,70);
}

river_long() {
   string the_long;

   the_long = "The river ";

   if (this_player()->query_skill(SS_LOC_SENSE) > 20)
      the_long += "Brandywine ";

   the_long += "is a clear stream, "
	+ "running southwards from the now lost kingdom, "
	+ "maybe keeping some secrets...\n";

   return break_string(the_long,70);
}
