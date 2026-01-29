//               Standard room for Bazaar Center
// creator(s):   Tepisch Aug 1994
// last update:  
// purpose:     Inheritable room for gravel streets on Bazaar Island
//              
// note:
// bug(s):
// to-do:        

inherit "/std/room";

#include "/d/Avenir/common/bazaar/bazaar.h"

#define HILL ({  \
      BAZAAR + "hill", \
})

/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = "\n"; }

    set_name("Bazaar");

    LONG("You stand in a crowded market area.  People of many races" +
       "bustle around in a rush.  Here and there in the teeming crowd " +
       "you see merchants hawking wares and wretched-looking children " +
       "scampering out of the reach of sinister-looking guardsmen." +
       "@@hill_desc@@" +  extra_long);

    AI(({"market","bazaar"}), "This is the kind of place where "+
      "You can buy anything...for a price.\n");
    AI("children", "They are all ragged-looking, underfed, and "+
      "bruised. Some appear to be offered for sale, while others " +
      "sit apathetically in the dust or run around picking pockets.\n");
    AI(({"crowd","people"}),
        "These people seem to be afraid for some reason. You can see "+
        "apprehension on their faces and tension in the set of their "+
        "shoulders, as if expecting that someone will lash out and " +
        "hit them.\n");
    AI(({"merchants", "wares"}), "The merchants seem to be offering "+
        "everything imaginable for sale. Their wares range from "+
        "torches to food to children!\n");
    AI(({"guardsmen","protectors"}),
        "The guardsmen are strong, well-muscled dwarves. Called the "+
        "Protectors of Sybarus, their purpose is ostensibly to " +
        "protect the peace. However, it looks like the people "+
        "here in the bazaar need protection from them.\n");
    AI(({"street","stones","cobbles","cobblestone", "courtyard"}),
        "You see that the ground beneath your feet "+
        "is paved with small rounded stones that have been " +
        "pounded into the dirt.\n");
    AI(({"gravel", "gravel walk", "gravel path", "path", "walk"}),
        "The path is wide enough for 6 men to stand abreast. It "+
        "is made of a thick layer of fine gravel that appears "+
        "to be well-maintained.\n");

    IN
    LIGHT
}

string hill_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = HILL;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
  if (sizeof(live) > 0)
      return ("  Up on the hill in the center of the bazaar you " +
        "think you see " + COMPOSITE_LIVE(live) + ".\n");
    }
    return ("  The hill at the center of the bazaar seems to be empty.\n");
}
