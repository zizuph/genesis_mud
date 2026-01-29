inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <stdproperties.h>
 
public void
create_element()
{
}
 
public nomask void
create_ctower_room()
{
  set_short("Hall of Elements");
 
  set_long("You can hardly believe that this room is "+
      "inside.  The ground is fresh smelling earth, there is a light "+
      "breeze, it is raining and the room is lit by flickering firelight."+
      "\n");
 
  add_item(({"wall", "ceiling"}), "The walls are made "+
      "of a dark crystal that seems to absorb the light.\n");
 
  add_item(({"ground"}), "Your feet sink almost a foot into the soft, " +
      "rich soul.\n");
 
  create_element();
}
