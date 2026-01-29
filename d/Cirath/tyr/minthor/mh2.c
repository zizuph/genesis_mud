inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
  bring_room_team(TYR_NPC+"hgiant",1,1,TYR_NPC+"hgiant",1);
}
void
create_room()
 {
  set_short("Path");
   set_long("Here, a gate opens into a courtyard. Sometimes it is "
   +"guarded by fiercely loyal half-giants, sometimes not. "
	+"A sign rests on the wall, and it looks moderately important. "
	+"The path heads south back towards the Caravan way. A stone "	
	+"wall lies to your east and west, an additional measure against "
	+"intruders. From within the walls, a strange smell emanates, "
	+"a smell not frequently found in homes in Tyr. Over the wall "
	+"you can see a glimpse of a towering building that looks like "
	+"a private home. High above you, the red Athasian sun beats "
	+"down upon you like a slavemasters whip.\n");
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item(({"path"}),"This is a large path, about half as large as "
        +"Caravan Way, and this appears to be the frontal entrance "
        +"to a house. This must be the house of some noble.\n");
  add_item(({"wall"}),"The wall is about 9 feet tall, and is made of "
        +"a dark grey granite. It would seem to protect decently well "
        +"against thugs and the like, as well as keep slaves in.\n");
  add_item(({"building"}),"The building is somewhere around four "
        +"stories tall(about 50 feet), and is covered in statues and "
        +"other decorative items.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  add_item(({"sun"}),"The crimson sun shimmers in the olive-tinged sky "
	+"like a pool of fiery blood.\n");
  add_item(({"guards"}),"They are two REALLY big half-giants.\n");
  add_item(({"gate"}),"The gate leads north into the courtyard of the "
	+"house.\n");
  add_cmd_item("sign","read","It says: House Minthor, Trespassers are "
	+"not welcome.\n");
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh3", "north", 0);
  add_exit(TZ_MINTHOR + "mh1","south", 0);
   set_alarm(1.1,0.0,"reset_room");
}
