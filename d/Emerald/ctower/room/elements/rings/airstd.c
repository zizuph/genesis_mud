inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
public void
create_air()
{
}
 
public nomask void
create_ctower_room()
{
    set_short("Air hall");
   
    set_long("The only remarkable feature of this room "+
	"is the incredibly fierce winds which howl through the passages, "+
	"buffeting you mercilessly.\n");
   
    add_item(({"wall", "ceiling", "floor"}), "The walls are "+
	"made of a dark crystal that seems to absorb the light.\n");
   
    add_item(({"air", "wind", "winds"}), "The wind is incredibly fierce.\n");
   
    create_air();
}

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
  
    if (living(ob) && !ob->id("air_elemental"))
    {
    	setuid();
    	seteuid(getuid());
    	ELEMENTAL_DAMAGE->register(ob);
    }
}
