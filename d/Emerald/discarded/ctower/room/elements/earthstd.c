inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
public void
create_earth()
{
}
 
public nomask void
create_ctower_room()
{
    set_short("Earth hall");
   
    set_long("The ground of this passage is constantly changing."+
	"  Stalagmites and stalactites are constantly forming and unforming "+
	"making this room extremely dangerous.  There is constant rumbling "+
	"and grinding noises accompanying the formations that makes "+
	"conversation difficult.\n");
   
    add_item(({"wall", "ceiling"}), "The walls are"+
	" made of a dark crystal that seems to absorb the light.\n");
   
    add_item(({"stalactite", "stalagmite"}), "The formations "+
	"are made of the same material as the walls and appear to be rather "+
	"sharp.\n");
   
    add_item(({"ground", "floor", "earth", "soil"}),"The ground " +
	"is made of rich soil that is about a foot deep.\n");
   
    create_earth();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
  
    if (living(ob) && !ob->id("earth_elemental"))
    {
    	setuid();
    	seteuid(getuid());
    
    	ELEMENTAL_DAMAGE->register(ob);
    }
}
