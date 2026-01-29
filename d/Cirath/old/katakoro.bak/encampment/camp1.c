inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"

create_room()
{
  set_short("Outside Encampment");
   set_long("Streched out below this hill is a huge encampment.  "+
	"Black and white domelike tents, known as Yurts among "+
	"the barbarian natives of this land, are scattered about "+
	"in dense clumps.  Cluttering the space between these "+
	"clumps are heavy wooden wheeled carts, ox yokes, racks of "+
	"drying meat and hobbled horses.  Also scattered about the valley "+
	"are wicker corrals containing horses and sheep.  All over the "+
	"encampment thin trails of smoke drift up from the cooking fires "+
	"between the yurts.  There is a muddy trail here leading down "+
	"into the valley.\n");

  add_item(({"yurts","tents"}),"For the most part the yurts are dirty "+
	"looking felt mounds.  The white ones are more grayish from the "+
	"mixing of dirt and chalk that occurs over time.  It is "+
	"also noticable that all of the entryways into the yurts "+
	"are facing southeast.\n");
   add_item("clumps","Thousands of yurts are clumped together in "+
	"various size groups.  They seem to cover the valley floor for a "+
	"mile in each direction.  The number of people in this valley "+
	"appears to be vast.\n");
  add_item("smoke","A gray smudge of smoke hangs over the encampement, "+
	"residue from hundreds of cooking fires.  It fills the air with "+
	"the acrid tang of burning dung, the only fuel avaliable to these "+
	"people.\n");
  add_item("trail","The churned mud of the trail suggests that there is "+
	"steady horse traffic through this area.\n");

  add_exit(PATH + "desert/desert1","south");  
  add_exit(PATH + "encampment/camp2","north");

}
