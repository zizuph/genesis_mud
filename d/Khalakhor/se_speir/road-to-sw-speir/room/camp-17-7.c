/*
 * Camp room on the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_CAMP;
string banner_file = OBJS_DIR + "banner";
object banner;

string
setup_long ()
{
  string my_desc = ::setup_long();
  my_desc += "You are at the southern edge of the camp, at the very shore "+
    "of Cala Fasdagh. The waves are pounding the rocks to your south, west "+
    "and east. Next to you is the largest tent of the camp with a black, "+
    "blue and green pendant flying on its top.\n";
  add_item(({"pendant"}),
           "The pendant indicates both that it's the tent of the force's "+
           "commanding officer there, and that it represents colors of "+
           "clans Macdunn and Maccrimmon.\n");
  return my_desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("camp-16-6", "northwest");
  add_exit("camp-17-6", "north");
}
