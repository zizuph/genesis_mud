inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/gcamp/defs.h"
#include "/d/Cirath/common/teamer.h"
#define PORTCULLIS_DOWN "_portcullis_down_"

void
create_room()
 {
  set_short("Gith Fortress");
  set_long("You are standing just inside the wall of a large, stone-"
  	+"walled fortress.  To the north is the exit to the camp, "
  	+"which is framed by a short corridor through the walls.  "
  	+"Against the inside of the corridor you see a portcullis "
  	+"locked in place that looks as if it can be dropped to prevent "
  	+"attackers from entering the fortress.  Stretching out inside "
  	+"the encampment before you are a large number of semipermanent "
  	+"shelters and tents as well as many of the fearsome creatures "
  	+"known in Athas as gith.\n");
  add_item("portcullis","Composed of a number of interlocked stone "
  	+"tipped spears, this portcullis looks to be extremely heavy.\n");
  add_item("shelters","They are scattered through out the fortress, mainly "
  	+"against the inside of the stone walls of the fortress.  It looks "
  	+"as if they could house a large number of gith.\n");
  add_item(({"corridor","short corridor"}),"It leads into the camp from the "
  	+"wastes outside.\n");
  add_prop(ROOM_I_HIDE,-1);
   add_exit(CAMP + "campent","north");
  add_exit(CAMP + "c2","southwest");
  add_exit(CAMP + "c3","south");
  add_exit(CAMP + "c4","southeast");
}

void
bring_guard()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith1",1,2,GITH_NPC+"gith1",1);
}

public int
block()
{
   write("As you try to go go back to the north, you bump into "
	+"an invisible wall of force.  It seems as if you've "
	+"fallen into a trap.\n");
   return 1;
   return 0;
}

