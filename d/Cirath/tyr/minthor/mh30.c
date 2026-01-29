inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("human", TZ_MINTHOR +"/npc/marisol",1,1);
}

void
create_room()
 {
  set_short("Bedroom");
  set_long("A large bed dominates this room.  Draped with a shimmering "
	+"silken fabric, it shrouds the shape of the bed a little.  You "
	+"also see other standard bedroom accoutrements, a dresser, "
	+"a mirror, things you would find in any bedroom.  The room itself "
	+"is enormous, there is more room here than in most of the houses "
	+"in Tyr.\n");
  add_item(({"wall","walls"}),"The walls stretch around you.\n");
  add_item(({"bed","large bed"}),"The bed is large enough for four or five "
	+"people easily.  It has a diaphanous material resembling silk "
	+"draped over it and around the room, which diffuses the light in "
	+"here, making it seem almost solid.  The bed has intricate carvings "
	+"on it as well, sweeping desert designs and cloudy skies.\n");
  add_item(({"door","doors","southeast door","southwest door"})," The doors "
	+"look to be made of beautiful carved agafari wood, which is known "
	+"for its strength and durability.  It would be a mistake to try and "
	+"break it down.\n");
  add_item("dresser","It is a large wooden dresser with some thin garments "
	+"on it.\n");
  add_item("mirror","This is a large mirror with gold leaf along the edges. "
	+"It was probably very expensive.\n");
  add_item("garments","They look like lady's lingerie.\n");
   add_item("material","It looks to be some form of silk "
	+"or other related fabric.  It is draped all around "
	+"the room and helps to diffuse the light from "
	+"Athas's red-hot sun.  You notice a piece of the "
	+"fabric seems to be stuck to the wall near the back "
	+"of the room.\n");
  add_item("piece","This piece of cloth is near the head of "
	+"the bed and looks to be closed in a crack of some "
	+"sort.\n");
   add_item("fabric","It is draped over the bed, keeping the light"
	+"from penetrating too deeply into it while someone is "
	+"sleeping.  You notice a small piece of it seems to be "
	+"caught in something near the head of the bed.\n");
  add_item("crack","You examine the crack closely, and finally "
	+"reach out and pusk that portion of the wall.  There is "
	+"a quiet click and a small door swings out towards you. "
	+"You think you could probably squeeze into the door "
	+"easily.\n");
   add_cmd_item("into door","squeeze","@@enter");
   add_cmd_item("door","enter","@@enter");
  

  ADD_SUN_ITEM
  
  INSIDE

   add_exit(TZ_MINTHOR + "mh29","northwest");
  set_alarm(1.1,0.0,"reset_room");
}

enter()
{
   write("You squeeze through the small door.\n");
  say(QCTNAME(TP)+" steps through the a small hidden door concealed "
        +"behind the bed.\n");
    set_dircmd("secret room");
  TP->move_living("squeezes through the small door.",TYR+"minthor/sroom");
    return 1;
}

