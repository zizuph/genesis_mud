inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "../guild.h"


void
create_room()
 {
  set_short("Tower Base");
  set_long("You step out of the heat into the cool interior of the "
  	+"headquarters for the Tyrian Militia.  Thick blocks of "
  	+"sandstone have been mortared together to provide a thick "
  	+"protective wall that also keeps the inside quite cool and "
  	+"comfortable.  This is the main greeting hall of the guild, "
  	+"no strangers are allowed past this point.\n");
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
  add_item("plants","They are small leafless vines that are growing in "
  	+"a tangle near the wall.\n");
  add_item("footprints","They look to be deliberately left footprints "
  	+"used for people to hone their tracking skill.\n");
  	
   add_exit(MILITIA_ROOM + "m_train","south","@@block");
  add_exit(MILITIA_ROOM + "m9","east","@@block");
   add_exit(MILITIA_ROOM + "joinroom","west");

}
   
int
block()
{
   
   if((!IS_TYR_MILITIA(TP)))
    {
	TP->catch_msg("A guard steps out and blocks your path.  "
		+"He then says 'This is a private group.  If you "
		+"want to explore, go join up.'\n");
      return 1;
    }
    TP->catch_msg("You nod your head to the door guard in greeting as "
    	+"you pass.\n");
    return 0;
}

