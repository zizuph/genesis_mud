inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/mobber.h"

create_room()
{
   set_short("Barbarian camp");
   set_long("This area is surrounded by yurts of various shapes and "+
	"sizes.  For the most part these are homes to the members of "+
	"the Khahan's tribe.  To the west is the residence of an "+
	"obvious outsider.  It is a large wagon with a yurt attached "+
	"to it.  There is a sign hanging from the wagon suggests that "+
	"this is the residence of a smith.\n");
	
   add_item("wagon","This large wagon looks like it carries a forge, "+
	"possibly for when the Khahan's army is on the move.  Thin "+
	"trails of smoke drift up from the forge now, suggesting "+
	"that it is constantly in use.\n");

  add_exit(PATH + "encampment/camp16","south");  
   add_exit(PATH + "encampment/yurts/forge","enter");
  add_exit(PATH + "encampment/camp14","north");

}


