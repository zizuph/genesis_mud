inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"

#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    if (leader) return;
bring_room_team(TZ_MINTHOR+"npc/minthor",1,2,TZ_MINTHOR+"npc/guard2",1);
   leader->set_monster_home(TZ_MINTHOR+"mh32");
}

void
create_room()
 {
  set_short("Master Suite");
  set_long("You have entered the master suite of the Minthor House. "
	+"Placed around the room are various decorations ranging from "
	+"exotic stuffed animals, to weaponry and art.  The decorations "
	+"in here must have cost a fortune, but after seeing the rest "
	+"of the house, that comes as no surprise.  You see elaborate "
	+"furniture accenting the art work and decorations.\n");
  add_item("bed","The bed is large enough to comfortably fit two adult "
	+"half-giants.\n");
  add_item("furniture","All of the common bedroom and study furniture "
	+"is present here, including a dresser, bed, divan, some chairs, "
	+"and a large number of small tables with assorted trinkets "
	+"on them.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item("dresser","The dresser looks to be made of highly polished "
	+"agafari wood with metal handles on it.\n");
  add_item("divan","This small, low couch is covered in a silken fabric "
	+"that would probably be cool on the skin.\n");
  add_item(({"chair","chairs"}),"The chairs look like very comfortable "
	+"overstuffed cushions that have been molded and placed on a "
	+"wooden frame.  They look very comfortable.\n");
  add_item(({"decoration","decorations"}),"There are a variety of "
	+"decorations here.  There are beautiful pieces of art, lifelike "
	+"stuffed animals, and many forms of exotic weapons.\n");
  add_item(({"animals","stuffed animals","animal"}),"There are various "
	+"animals native to this region that have been killed and stuffed "
	+"to be used as decorations.\n");
  add_item(({"weapon","weapons","weaponry"}),"You see many forms of "
	+"traditional Athasian weapons hanging on the wall, most of which "
	+"you don't know the name for.\n");
  add_item("art","There are many beautiful works of art decorating this "
	+"beautiful room.\n");

  INSIDE
  add_exit(TZ_MINTHOR + "mh34","south");
   add_exit(TZ_MINTHOR + "mh32","southeast");
   reset_room();
}
