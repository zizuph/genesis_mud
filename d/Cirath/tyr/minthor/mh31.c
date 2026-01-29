inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("human", TZ_MINTHOR+"/npc/bacchus",1,1);
}

 
create_room()
 {
  set_short("Bedroom");
  set_long("A large bed dominates this room.  There is also a large hide "
	+"covered couch and chair with a table and ottoman in front of them. "
	+"The walls have exotic weapons mounted on them, as well as the "
	+"stuffed heads of a variety of athasian beasts.  This room is "
	+"obviously a man's room.  There is a large open armoire filled "
	+"with richly embroidered clothing and sturdy shoes. There looks "
	+"to be a shape on the bed as well.  The curtains are all drawn, "
	+"and the room is very dim.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item(({"bed","large bed"}),"This is a massive canopy bed.  It has a thin "
	+"white fabric surrounding it to keep bugs out, but the fabric still "
	+"can be seen through.  There seems to be a shape lying on the bed.\n");
  add_item(({"door","doors","southeast door","southwest door"})," The doors "
	+"look to be made of beautiful carved agafari wood, which is known "
	+"for its strength and durability.  It would be a mistake to try and "
	+"break it down.\n");
  add_item("weapons","There is a large variety of bladed weapons on the wall.\n");
  add_item("heads","Most of these heads you do not recognize, but they all appear "
	+"vicious and quite stuffed.\n");
  add_item("shape","Upon closer examination it looks to be a heavily sedated "
	+"woman.  As you look you notice that she has the markings of a slave "
	+"on her exposed right shoulder.  You also notice that she is extremely "
	+"beautiful.  Apparently all slaves have to perform some form of labor.\n");
  add_item(({"couch","couches"}),"They are made of some of the "
        +"finest fabrics in the Tyr region. They look very comfortable "
        +"to sit on.\n");
  add_item(({"chair","chairs"}),"They are made of fine hardwoods, lined "
        +"with soft plush materials to make them comfortable.\n");
  add_item("armoire","It is a large piece of hardwood intricately carved and used "
	+"for storing clothing.\n");
  add_item(({"clothing","shoes"}),"They look to be very nice and most likely "
	+"extraordinarily expensive.\n");
  add_item("curtains","They cover the windows and are keeping the sun out.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_cmd_item("in chair","sit","@@chair");
  add_cmd_item("on couch","sit","@@couch");
  add_cmd_item("up","stand","@@stand");
  ADD_SUN_ITEM  
  INSIDE

   add_exit(TZ_MINTHOR+"mh29","northeast");
  set_alarm(1.1,0.0,"reset_room");
}

