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
     "A flickering light from the east casts dancing shadows about. "+
     "The tunnel continues off to the west while to the east the tunnel"+
     " widens.\n");
  add_item("tunnel",
     "It's a cramped humid tunnel continuing to the east and west.\n");
  add_item(({ "ceiling", "roof" }),
     "It's low and roughly cut from the hard stone. Some places are "+
     "moist due to the strange humidity in this place.\n");
  add_item(({ "walls", "wall", "western wall", "west wall" }),
     "These rough stone walls are about five feet apart and damp from "+
     "the strange humidity in this small tunnel.\n");
  add_item(({ "ground", "floor" }),
     "The uneven stone floor is covered in some areas by moss and an "+
     "occasional puddle.\n");
  add_item("moss",
     "It has a translucent greenish color and appears to be common "+
     "around these parts.\n");
  add_item(({ "water", "puddle", "streak", "streaks" }),
     "The water is clear but rather warm. Occasionally it runs down "+
     "from the ceiling and either forms tiny puddles or is drained "+
     "away through a hole at the base of the western wall.\n");
  add_item(({ "light", "flickering light" }),
     "It's hard to tell what causes it from here but you guess it's "+
     "from a torch.\n");
  add_item(({ "shadow", "shadows" }),
     "Cast by the flickering light to the east they dance off the "+
     "ceiling and walls as if possessed by a joyful spirit.\n");
  
  add_prop(ROOM_I_LIGHT,1);
 
  add_exit("/d/Shire/khazad/wcamp/camp_tunnel1","west",0,1);
  add_exit("/d/Shire/khazad/wcamp/camp_tunnel3","east",0,1);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  switch (random(14))
  {
    case 0..1:
        tell_room(TO, "Shadows dance along the walls.\n");
        break;
    case 2..3:
        tell_room(TO, "A warm light flickers to the east.\n");
        break;
    case 4..5:
        tell_room(TO, "Shadows dance upon the ceiling.\n");
        break;
    case 6:
        tell_room(TO, "You nearly slip on the slick ground!\n");
        break;
    case 7:
        tell_room(TO, "You step in a small puddle.\n");
        break;
  }
}            
