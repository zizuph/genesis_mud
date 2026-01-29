inherit "/std/room";

#pragma strict_types
#pragma save_binary
#include <stdproperties.h>

public void
create_room()
{
   set_short("Underwater Eclipsia");
   set_long("An unmodified cave room.\n");
   add_item(({"floor", "ground"}), "The floor has been worn down " +
      "so much that it has become very smooth and slippery.\n");
   add_item("ceiling", "The ceilings are very high and rounded; they " +
      "give the feeling of open spaces. The brilliant colours of  " +
      "the coral are more vibrant than any rainbow you've ever seen.\n");
   add_item("walls", "The walls are a mixture of smooth, slippery stone " +
      "along the bottom; then coral has grown above the stone, " +
      "creating the feelings of large, airy caves.\n");
   add_item(({"crack", "cracks"}), "Close to the bottom of the walls " +
      "you notice cracks of various depths in the stone.\n");
   add_item("seaweed", "Long leaves of seaweed float and sway out " +
      "of the cracks and crevices in the walls and coral all around.\n");
   add_item("coral", "A rainbow of colour meets your eyes each time you " +
      "look at the coral. It appears different with each glance.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 1);
}


