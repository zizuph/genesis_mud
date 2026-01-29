inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
public void
create_water()
{
}
 
public nomask void
create_ctower_room()
{
    set_short("Water hall");
   
    set_long("You seem to be completely submerged in "+
	"cool water.  There is a slight current, more of a swirling of "+
	"the water than any real current.  You do seem to be able to "+
	"walk, even if it is slow going.\n");
   
    add_item(({"wall", "ceiling", "floor"}), "The walls are "+
	"made of a dark crystal that seems to absorb the light.\n");
   
    add_item(({"water"}), "It is normal water although you "+
	"are not sure how it stays in the room.  It is cool but not "+
	"cold.\n");
   
    create_water();
}
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (living(ob) && !ob->id("water_elemental"))
    {
    	setuid();
    	seteuid(getuid());
    	ELEMENTAL_DAMAGE->register(ob);
    }
}
