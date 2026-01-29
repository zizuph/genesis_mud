inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>

create_room()
{
  set_short("Northern Wastelands");
  set_long("This is the base of a hill among many hills scattered "+
	"throughout the wastelands of the north.  Only the patches of "+
	"white snow, green grass and brown dirt break up the seemingly "+
	"unchanging view.\n");

  set_noshow_obvious(1);
  
   add_exit(KAT_DIR+"desert/desert6","northeast");
   add_exit(KAT_DIR+"desert/desert8","northwest");

}
