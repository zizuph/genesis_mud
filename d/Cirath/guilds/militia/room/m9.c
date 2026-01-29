inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Staircase");
  set_long("The dull light of the twin suns of Athas shines dully "
  	+"through what looks like a trapdoor high above your head, "
  	+"casting long gray shadows through out the room.  It is "
  	+"still easily bright enough to see by though, and by this "
  	+"diffused light you see the only thing in this room, a "
  	+"staircase.  Large marble steps spiral upward to another "
  	+"floor above you.  The stairs actually seem to be set into "
  	+"the walls of the room for reinforcement, and it looks to "
  	+"be very strong and capable.\n");
  add_item("staircase","Large and regal, it stretches high above your "
  	+"head to another floor.  The large marble steps look to be "
  	+"rooted into the walls for added strength and look to be able "
  	+"support an enormous weight.\n");
  add_item("steps","They are long and broad, at least a cubit deep as "
  	+"well.  They can fit a big foot.\n");
  add_item("trapdoor","It is far above your head, but looks as if it "
  	+"leads out onto a roof of sorts.\n");
  add_item("guard","He stands sheltered in a recess in the wall, his "
  	+"watchful eyes never leaving your face.\n");
  add_item("recess","It is a small indention in the wall for a guard "
  	+"to stand inobstrusively.\n");
  add_item(({"block","sandstone","blocks","blocks of sandstone"}),
  	"These enormous blocks were most likely hauled here and "
  	+"assembled into this tower by half-giant slaves, no other "
  	+"creature could have carried such mass alone.\n");
    add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  	
   add_exit(MILITIA_ROOM + "board","south");
  add_exit(MILITIA_ROOM + "m8","west");
  add_exit(MILITIA_ROOM + "m10","up");

}

