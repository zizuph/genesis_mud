inherit "/std/room.c";

#include "/sys/stdproperties.h"

void
create_room()
{
   set_short("Bright Forest");
   set_long("This is probably the most vivid forest you've ever " +
      "seen!  Its hues range from blackest black, through brightest orange, " +
      "to vivid green and deepest indigo. The trees here are deciduous, and " +
      "are apparently competing to see who can have the most beautiful fall " +
      "foliage.  Even the path beneath you is not merely dirt-brown, but " +
      "a rich shade of burnt sienna, and bushes edge it on both sides.\n");
   
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);
   
   add_item(({"tree", "trees"}),
      "These trees are mostly oak and sugar maple, with the occasional "
      + "elm thrown in for variety.  They seem to be murmuring to each "
      + "other, so quietly that you cannot make out the words.\n");
   
   add_item(({"path", "road", "ground"}),
      "The path is a deep orange-brown, and there is the occasional stone "
      + "embedded in it.\n");
   
   add_item(({"stone", "stones"}),
      "The stones in the path are a charcoal-grey slate, and "
      + "although large, they don't seem rough enough to trip over.\n");
   
   add_item(({"bush","bushes"}),
      "These bushes are vibrantly colored, showing every color of green "
      + "imaginable, since they can't be as colorful as their larger "
      + "brethren.\n");
   
   add_exit("/d/Calia/alisande/workroom", "out", 0, 1);
}
