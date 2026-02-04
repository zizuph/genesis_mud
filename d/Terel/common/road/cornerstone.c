#define PATH "/d/Terel/common/road"
#define MSGPATH "/d/Terel/common/road/cornerstone/" 
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>


void msg_text(int n)
{
     switch (n) {
     case 1:
	  cat(MSGPATH + "b710731177", 2);
	  break;
     case 2:
	  cat(MSGPATH + "b710733749", 2);
	  break;
     case 3:
	  cat(MSGPATH + "b715511800", 2);
	  break;
     case 4:
	  cat(MSGPATH + "b716262658", 2);
	  break;
     case 5:
	  cat(MSGPATH + "b717269203", 2);
	  break;
     case 6:
	  cat(MSGPATH + "b720913777", 2);
	  break;
     case 7:
	  cat(MSGPATH + "b720915258", 2);
	  break;
     case 8:
	  cat(MSGPATH + "b720915835", 2);
	  break;
     case 9:
	  cat(MSGPATH + "b722820679", 2);
	  break;
     case 10:
	  cat(MSGPATH + "b727422267", 2);
	  break;
     case 11:
	  cat(MSGPATH + "b742229809", 2);
	  break;
     case 12:
	  cat(MSGPATH + "b742627340", 2);
	  break;
     case 13:
	  cat(MSGPATH + "b760985981", 2);
	  break;
     default:
	  cat(MSGPATH + "b710731177", 2);
	  break;
     }
}

init()
{
     ::init();
     add_action("do_read", "read");
}

int 
do_read(string str)
{
     int msgnum;
	  
     notify_fail("Read what?\n");
     if (!str)
	  return 0;

     msgnum = atoi(str);
     
     if ((msgnum <= 0) || (msgnum > 13)) {
	  notify_fail("inscription number out of range.\n");
	  return 0;
     }

     msg_text(msgnum);
     return 1;
}

create_room()
{
  object stone;

  set_short("Cornerstone");
  set_long("Great stone pillars stand here, monuments of ancient days. " +
	   "They are placed all about here, creating an ominous feeling.  " +
	   "Various other stones and markers have been set into the " +
	   "ground, almost as if this were a tomb.  A road leads west " +
	   "towards the mountains, east across the moors, north into the " +
	   "hills. South of here is a great silvery pine forest.\n");

  add_exit(PATH + "/road5","east",0);
  add_exit(PATH + "/road6","west",0);
  add_exit(PATH + "/forest_edge","south",0);
  add_exit(PATH + "/road9","north",0);
  add_item(({"stone pillars","pillars"}),
	   "These grand pillars seem to have some kind of astrological " +
	   "meaning when studied.  They have been inscribed with runes " +
	   "and icons. They are so worn and covered with moss and " +
	   "lichen to make then unreadable.\n");
  
  add_item(({"stones","markers"}),
	   "They seem to have ceremonial signifigance and have also been worn\n" +
	   "down so any writings they had are gone.\n");
add_item(({"lichen","moss"}),
"This place seems to be a haven for strange moss and lichen.\n"
+"There are many different kinds, covering the stones, pillars,\n"
+"markers and ground. Their colors range from purple to orange.\n");


/*
 * WE'll have to fix this later!
 *
 * -- Sorgum
 */

/*stone = clone_object(PATH + "/cornerstone_obj"); */

stone = clone_object(PATH + "/broken_cobj"); 
stone->move(this_object());

}
