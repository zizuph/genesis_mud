inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h";
#include "/sys/ss_types.h";

create_room() {
    set_short("Slope");
    set_long("@@my_long");

    add_exit(DOWNS_DIR + "slope", "south");
    add_exit(DOWNS_DIR + "slope3", "north");
}

my_long() {
   string str;

   str =  "The grass is green and stands tall, "
	+ "hidden from the moist wind by the steep hill south. "
	+ "The aura that emanates from the south does not feel so good. "
	+ "Far away to the west you spot a river flowing.";

   if (this_player()->query_skill(SS_LOC_SENSE) > 20)
   {
	str += " It is the Baranduin, the biggest river that flows through the Shire.";
   }

   str += "\n";

   return break_string(str,70);
}
