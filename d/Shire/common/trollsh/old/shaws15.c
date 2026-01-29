/* File: /d/Shire/common/trollsh/shaws15.c */

inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"
#include <ss_types.h>

create_shawrom()
{
    set_short("Deep in the TrollShaw on a ridge");
    set_extraline(
	 "You find yourself on a ridge deep in the Trollshaws. "
	+"Here the bushes are as dense as everywhere else in the "
	+"Trollshaws. Somehow, though, you feel rather safe here. "
	+"To the south there is a path going through a depression to "
	+"another ridge in the south. Going north or west would take "
	+"you to another place on this ridge. There a is narrow "
	+"path leading down to the east. ");
   
    add_exit(TROLLSH_DIR +  "shaws18", "east", 0, 1);
    add_exit(TROLLSH_DIR + "shaws14", "south", 0, 1);
    add_exit(TROLLSH_DIR +  "shaws13", "west", 0, 1);
    add_exit(TROLLSH_DIR + "shaws16", "north",0, 1);	
}
 
