inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"

#define HAS_FOUND_LETTER "_has_found_letter"

 
create_room()
 {
  set_short("Attic");
  set_long("You have reached the end of the attic.  Around you can see "
	+"numerous things lying on the floor, but what catches your eye "
	+"is a small pile of junk near a clear space on the floor.  "
	+"There seems to be no dust there and there is also the melted "
	+"remains of a candle.\n");
  add_item(({"candle","remains"}),"It looks like someone was burning "
	+"a candle here sometime fairly recently, there is not much "
	+"dust covering it.\n");
  add_item("dust","There is a lot of dust on the floor here.  It all "
	+"looks relatively undisturbed at first.  Upon careful "
	+"examination, though, you notice faint footprints in the "
	+"dust.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item(({"footprint","footprints"}),"They are footprints the size "
	+"of a young man or possibly a woman.  You can't be absolutely "
	+"sure because they are so faint.\n");
  add_item(({"dishes","accessories","things"}),"There is a large variety "
	+"of miscellaneous dishes and things on the floor or in chests.\n");
  add_item(({"chest","chests"}),"There are a number of chests lying on "
	+"the floor and are apparently used to store things.\n");
  add_item(({"junk","pile of junk"}),"This particular pile of "
   +"junk seems to be composed of mainly things that look feminine, "
   +"as if someone was trying to get information or get "
   +"to know details about them better.\n");
  add_prop(OBJ_S_SEARCH_FUN, "search_junk");
  add_prop(ROOM_I_LIGHT,0);
  INSIDE
   add_exit(TZ_MINTHOR + "mh36","north");
}

public string
search_junk(object me, string arg)
{
    if (arg != "junk")
        return "";
   if (TP->query_prop(HAS_FOUND_LETTER))
	return "";
    if (TP->query_skill(SS_AWARENESS) >29)
    clone_object("/d/Cirath/tyr/minthor/obj/letter")->move(TO);
   TP->add_prop(HAS_FOUND_LETTER,1);
    return "You search the pile of junk carefully and discover a letter!\n";
}


