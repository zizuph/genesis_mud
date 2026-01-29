inherit "/d/Shire/khazad/moria_room_drip";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("Within a dark tunnel");
  set_long("You are crouched within a roughly hewn, dark tunnel. "+
     "The tunnel's ceiling is low and its walls are not more than five "+
     "feet apart. The bare stone ground is rather slick due to moss "+
     "that thrives here in this humid environment. Faint trickles of "+
     "water occasionally streak down the walls beside you. A small hole "+
     "at the base of the western wall seems to drain excess water away. "+
     "To the south you see an open doorway while to the east the dark "+
     "tunnel continues.\n");

  add_item("tunnel",
     "It's a cramped humid tunnel continuing to the east and south.\n");
  add_item(({ "ceiling", "roof" }),
     "It's low and roughly cut from the hard stone. Some places are "+
     "moist due to the strange humidity in this place.\n");
  add_item(({ "walls", "wall", "western wall", "west wall" }),
     "These rough stone walls are about five feet apart and damp from "+
     "the strange humidity in this small tunnel.\n");
  add_item(({ "ground", "floor" }),
     "The uneven stone floor is covered in some areas by moss and an "+
     "occasional puddle. A small hole can be seen in the floor at the "+
     "base of the western wall.\n");
  add_item("moss",
     "It has a translucent greenish color and appears to be common "+
     "around these parts.\n");
  add_item(({ "water", "puddle", "streak", "streaks" }),
     "The water is clear but rather warm. Occasionally it runs down "+
     "from the ceiling and either forms tiny puddles or is drained "+
     "away through a hole at the base of the western wall.\n");
  add_item(({ "hole", "drain" }),
     "A small hole no more than a few inches wide and the base of "+
     "the western wall.\n");
  add_item(({ "door", "doorway" }),
     "The stone door to the south is swung back open against "+
     "the western wall.\n");

  add_exit("/d/Shire/khazad/wcamp/camp_tunnel2","east",0,1);
  add_exit("/d/Shire/khazad/wcamp/westcamp8","south",0,1);
}
 
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/westcamp8")
    write("A rush of damp humid air engulfs you.\n");
}
