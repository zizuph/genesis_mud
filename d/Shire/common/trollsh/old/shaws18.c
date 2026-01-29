/* File: /d/Shire/common/trollsh/trollsh18.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"



create_shawrom()
{
    set_short("East in the Trollshaw");
    set_extraline(	 
	"The bushes have grown totally out of proportion and the pines are "
	+"very thick and sturdy. As you move about in this place you smell "
	+"a foul reek or you might call it a stench, but you are not quite "
	+"sure where to place it. It makes your nose wrinkle a bit though. "
	+"There is a ridge building up to the south and and a narrow path "
	+"going up to another ridge to the west. To the north there is another "
	+"path leading someplace. ");
        

add_item(({"reek","foul reek","stench","smell"}),
		 "You imperil your nose and smell the stench. "
		+"It seems this is some trolls favourite spot.\n");


    add_exit(TROLLSH_DIR + "shaws15", "west", 0, 2);
    add_exit(TROLLSH_DIR + "shaws17", "south", 0, 2);
    add_exit(TROLLSH_DIR + "shaws19", "north", 0, 2);
}
