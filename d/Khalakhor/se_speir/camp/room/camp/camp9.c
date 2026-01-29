inherit "/std/room";
inherit "/w/stark/celtcamp/rooms/camp/campbase";
#include "/w/stark/defs.h"

void
 create_room()
 {
  ::create_room();
  set_short("In a heavily guarded celtic camp");
  set_long("You have entered the suspicious-looking encampment. "
	  +"Now the pungent odor is very strong. This is the first row of tents, "
	  +"and before you stands a tent, which you can enter.\n");
  add_item(({"Odor","encampment","base","base of operations"}),
      "You stand in a hastily established encampment of celtic barbarians! "
	 +"Row after row of red and black striped tents create the campground, and "
     +"you begin to realize the true scope of military power that stands "
	 +"to threaten Port Macunn! The pungent odor is almost unbearable, but "
	 +"you manage to keep yourself awake and alert.\n");
  add_item(({"tent", "tents", "rows"}),
      "These rows of tents arrange a block format. each row holding five "
	 +"tents each, set up extremely well, even though it is evident that "
	 +"the tents have been set up very recently. Each tent holds a red "
     +"and black striped pattern, as they are the colours of the clan Baran!\n");
  add_item(({"forest","wild",}),
	  "The forest surrounds the barbaric camp. No longer emitting "
	 +"natural sounds and a general relaxing atmosphere, but rather "
	 +"dominated by the sounds of swordplay and grunting from the warriors.\n");
  add_item(({"odor"}),
	  "These barbarians don't seem to be too keen on "
	 +"Around you, are colourful birds on branches and squirrels "
	 +"darting through the underbrush.\n");
  add_exit(CAMP_DIR2+"camp10","east",0,0);
  add_exit(CAMP_DIR2+"camp12","west",0,0);
  add_exit(CAMP_DIR2+"camp9","north",0,0);
  add_exit(CAMP_DIR2+"tent9","in",0,0);
  add_exit(CAMP_DIR2+"camp2","south",0,0);
  
  summon_kguard();
  summon_kguard();
  summon_kguard();
}