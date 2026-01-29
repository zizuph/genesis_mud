inherit "/std/room";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"


void
create_room()
 {
  set_short("Dusty Path");
  set_long("You are standing on a narrow path outside of a massive "
  	+"fortress.  To your west a large rent in the thick stone "
  	+"wall probably would give you access back into the "
  	+"encampment of gith if you want.  Chunks of rubble are "
  	+"piled up against the wall in a haphazard attempt to "
  	+"block the hole, but instead it just creates a slope that "
  	+"is easy for you to traverse.\n");
  add_item(({"mountainside","mountain"}),"The mountain looms to the south, "
  	+"its flat face stretching up above the towers situated against "
  	+"it, before becoming covered in small rocky outcroppings.\n");
  add_item("wall","It is a large sandstone wall circling the gith "
  	+"camp.  There is a hole in it here that leads into the gith "
  	+"fortress.\n");
  add_item(({"hole","rent"}),"It looks to have been created a long "
  	+"time ago, "
  	+"probably during some forgotten conflict.  It leads into "
  	+"the fortress.\n");  
  add_item(({"rubble","chunks","chunks of rubble"}),"These chunks "
  	+"appear to have come from the hole in the wall before you.  "
  	+"They form a gentle slope back into the gith encampment.\n");
  add_exit(CAMP + "c19","east");
  add_exit(CAMP + "p2","northwest");
}

