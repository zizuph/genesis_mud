inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
#include <stdproperties.h>
 
public void
create_fire()
{
}
 
public nomask void
create_ctower_room()
{
    set_short("Fire hall");
   
    set_long("This room is a blazing inferno.  Flames fill "+
	"the room from floor to ceiling.  The flames seem to dance,  "+
	"enticing you to embrace them and be filled by their brilliance.  "+
	"You shake your head to dispel the hypnotic effect and wonder "+
	"how much longer you can stand this heat.\n");
   
    add_item(({"flames", "flame", "fire", "inferno"}), "As "+
	"you stare deeper into the flames you think you can detect a "+
	"pattern to their dance.  And with the last vestiges of your will, "+
	"you tear your eyes away before it is too late.  You are covered "+
	"in sweat and not sure how much time has passed.\n");
   
    add_item(({"wall", "ceiling", "floor"}), "The walls are "+
	"made of a dark crystal that seems to absorb the light.\n");
   
    create_fire();
}
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
  
    if (living(ob) && !ob->id("fire_elemental"))
    {
    	setuid();
    	seteuid(getuid());
    	ELEMENTAL_DAMAGE->register(ob);
    }
}
