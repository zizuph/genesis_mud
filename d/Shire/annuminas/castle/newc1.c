inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_room()
{

  set_short("A ruined entryway");
  set_long("The entryway to the castle is almost impassible. Blackened "
	+"white marble comprises the walls and floor, and huge brazen "
	+"doors lie on the floor, bent and mangled by the fury of the "
	+"Witchking's armies. Although there are large quantities of "
	+"rubble here, there is no dust. That alone is evidence of "
	+"inhabitance by the remnants of the so called Army of Angmar. "
	+"The vaulted ceiling above you is scarred by cracks and chips, "
	+"as well as by the huge black streaks caused by flames. Empty "
	+"torch brackets line the walls, giving some company to the "
	+"once beautiful cracked marble. To the east, a massive pile "
	+"of rubble blocks what was once a passage.\n");

  add_exit(ANNUM_DIR + "am19", "south", 0);
  add_exit(ANNUM_DIR + "ac2", "west", 0);
  add_prop(ROOM_I_INSIDE,1);

}
