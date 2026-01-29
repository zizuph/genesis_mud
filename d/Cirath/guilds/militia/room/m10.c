inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Staircase");
  set_long("You are at the top of the staricase that leads to the "
  	+"first floor of the guildhall for the Tyrian Militia.  A "
  	+"small ladder leads up through the trapdoor above you, "
  	+"while passageways lead off to the west and south.  The "
  	+"accomadations here are sparse to say the least, with "
  	+"no decorations, and basically no amenities.  Then again "
  	+"being sponsored by a noble doesn't mean you get to enjoy "
  	+"their benefit.\n");
  add_item("staircase","Large and regal, it stretches high above your "
  	+"head to another floor.  The large marble steps look to be "
  	+"rooted into the walls for added strength and look to be able "
  	+"support an enormous weight.\n");
  add_item("steps","They are long and broad, at least a cubit deep as "
  	+"well.  They can fit a big foot.\n");
  add_item("trapdoor","It is far above your head, but looks as if it "
  	+"leads out onto a roof of sorts.\n");
  add_item("ladder","Constructed from thick pieces of an agafari tree, "
  	+"this ladder stretches up the 10 feet between floor and ceiling "
  	+"and can give you access to the roof.\n");
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
  	
  add_exit(MILITIA_ROOM + "store","south");
  add_exit(MILITIA_ROOM + "m11","west");
  add_exit(MILITIA_ROOM + "m9","down");
  add_exit(MILITIA_ROOM + "m12","up");
}

