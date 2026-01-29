/* File: /d/Shire/common/trollsh/trollsh14.c */
#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/

create_shawrom()
{

    set_short("Deep in the Trollshaw on a ridge");
    set_extraline(
	 "You are south of a large depression in the Trollshaw. "
   +"It's almost like a small valley to the north and a narrow "
   +"path leads through the depression. It seems it leads up to another "
	+"bushy ridge to the north. To the east the ridge continues. ");

add_item(({"depression"}),
		 "The depression bends down between the two ridges. "
		+"It is full of bushes making it imposible to move down "
		+"there, exept for the path going through it.\n");


    add_exit(TROLLSH_DIR +  "shaws12", "west", 0, 1);
    add_exit(TROLLSH_DIR + "shaws15", "north", 0, 1);
    add_exit(TROLLSH_DIR +  "shaws17", "east", 0, 1);
}
