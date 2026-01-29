inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Foot of Staircase");
  set_long("You are now standing at the foot of a wonderful staircase "
        +"made from a mix of stones and metals. They curve upward to the "
        +"next floor, while standing apart from the wall. This also looks "
	+"to be the central intersection of the house, with a hallway "
	+"leading in all cardinal directions.  To the east you here the "
	+"telltale sound of pots clanging together, while to the west "
	+"it is quiet.  North of you the hall continues towards the back "
	+"of the house.\n");
  add_item("wall","The wall is off to your side.\n");
  add_item("hallway","It leads in all directions.\n");
  add_item(({"stone","stones"}),"The stairs are made of some precious "
        +"ones. There are obsidian steps, with other glittering jewels "
        +"set in.\n");
  add_item(({"metal","metals"}),"There is a large variety of metals in "
        +"the stairs and staircase..\n");
  add_item("ceiling","It is above you.\n");
  add_item("staircase","You are standing at the foot of a staircase made of "
        +"obsidian, lined with gold, and braced with steel bars "
        +"This must have cost the owners a fortune.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh28","up", 0);
  add_exit(TZ_MINTHOR + "mh12","south", 0);
  add_exit(TZ_MINTHOR + "mh27","north",0);
  add_exit(TZ_MINTHOR + "mh23","west",0);
  add_exit(TZ_MINTHOR + "mh17","east",0);
}


