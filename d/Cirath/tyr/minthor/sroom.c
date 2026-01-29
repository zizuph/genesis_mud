inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"
 
#define HAS_FOUND_BRACELET "_has_found_bracelet"
 
create_room()
 {
  set_short("Secret Room");
  set_long("You have entered a small hidden room behind "
	+"Marisol Minthor's room.  You see a desk and a chest "
	+"in here, but nothing else of interest.\n");
  add_item(({"chest","chests"}),"You see an open chest filled "
	+"with a variety of things.  You would have to search "
	+"it further to find anything.\n");
  add_item("desk","The desk is covered in some papers, most of "
	+"them blank, but a you notice one page with some "
	+"writing on it.\n");
  add_item(({"page","writing"}),"In excellent handwriting, you "
	+"read:\n"
	+"I have done my part in your plan, the old bitch is "
	+"dead.  You need to fulfill your end of the bargain "
	+"now.  Please leave me a note in the regular place.\n"
	+"MM\n");
  add_prop(OBJ_S_SEARCH_FUN, "search_chest");
  add_prop(ROOM_I_LIGHT,0);
  INSIDE
  add_exit(TZ_MINTHOR + "mh30","north");
}

 
public string
search_chest(object me, string arg)
{
    if (arg != "chest")
        return "";
   if (TP->query_prop(HAS_FOUND_BRACELET))
	return "";
    if (TP->query_skill(SS_AWARENESS) >29)
    clone_object("/d/Cirath/tyr/minthor/obj/bracelet")->move(TO);
    TP->add_prop(HAS_FOUND_BRACELET,1);
    return "You search the chest thoroughly and uncover a "
	+"beautiful bracelet!\n";
}
 

