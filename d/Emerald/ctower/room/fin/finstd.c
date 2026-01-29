inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <stdproperties.h>
 
public void
create_fin()
{
}
 
public nomask void
create_ctower_room()
{
    set_short("Shimmering hall");
   
    set_long("You are in a multicolored, crystal hallway "+
	"that shimmers throughout the rainbow.  You never realized that "+
	"such colors were possible.  The beauty of these halls is "+
	"breathtaking.\n");
   
    add_item(({"wall", "floor", "ceiling"}), "The walls are "+
	"made of a shimmering crystal that change color throughout the "+
	"spectrum continuously, giving off a rainbow light that makes "+
	"everything sparkle.\n");
   
    create_fin();
}
