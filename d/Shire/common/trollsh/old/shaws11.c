/* File: /d/Shire/common/trollsh/trollsh11.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom";	/*master object*/

create_shawrom()
{

    set_short("South-east in the Shaws");
    set_extraline(
	 "You are standing on a ridge of the hill, inside the shaws, far from "
        +"the road and the safety of it. The forest is dense and it is closing "
	+"your view in all directions. North you can see a narrow slope in the "
   +"forest. The ground is full of scattered pine sprigs. There is "
	+"no other way to get out of this place except the exit to the "
	+"north. The scent of evil is strong, as if something were lurking "
	+"in the area.       ");

add_item(({"eastroad","road","Eastroad","slope"}),"Down the slope to the southeast "
          +"you see the Great Eastroad. It is way to steep to climb down there though.\n");

add_item(({"sprig","sprigs","pine sprigs","ground","hill"}),
		"The ground is full of small pine sprigs.\n");

    NORTH("shaws12");
}
