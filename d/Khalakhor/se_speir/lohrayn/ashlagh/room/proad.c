// Pier Road Base Room
//
// Date    Coder       Action
// ------- ----------- ----------------------------------------
// 6/9/98  Zima        Created
//
inherit "/d/Khalakhor/std/room";
#include "defs.h"
string extra="";
 
create_proad()
{
   set_short("On a rocky winding road between the sea and a village");
   set_long("You are on a rocky road which winds its way up from the "+
            "sea to a small coastal village. A brisk cool salty wind "+
            "blows in constantly from the sea to the east where "+
            "there is a small pier for arriving ships. The little "+
            "village sits on the hills to the west overlooking the "+
            "shoreline, composed mostly of small wooden houses "+
            "surrounded by an old stone wall. "+extra+"\n");
   add_item("road",
      "It is just a rocky road, rutted by centuries of wagons and "+
      "flattened by trodding feet. It winds up the sides of the "+
      "coastal hills from the sea to the east, leading to a small "+
      "village to the west.\n");
   add_item(({"sea","white-tops","waters"}),
      "The cold choppy waters of the sea are overcast with thin "+
      "grey clouds, a brisk wind tearing white-tops across its "+
      "surface. The sea extends across the entire eastern horizon.\n");
   add_item(({"clouds","sky"}),
      "Thin gray clouds hang over the sea to the east, though they "+
      "don't look threatening now. The skies clear a bit over the "+
      "land to the west.\n");
   add_item("pier",
      "There is a small wooden pier at the east end of the road "+
      "which extends out over the surface of the sea. Ships from "+
      "distant and near lands and islands arrive there on a somewhat "+
      "regular basis, as long as the fury of the sea is relatively "+
      "quiet.\n");
   add_item("ships","You don't see any on the sea at the moment.\n");
   add_item(({"hill","hills"}),
      "The coastal hills of this area slope down to the rocky shores "+
      "of the sea from the west to the east, covered mostly in "+
      "short grass and weeds.\n");
   add_item(({"grass","weeds","weed"}),
      "The grass and weeds on the hillside are fairly short and "+
      "scrubby. They seem to struggle in the salty sea air as the "+
      "landscape becomes rocky along the shore.\n");
   add_item(({"shore","beach","rocks","boulders"}),
      "The shore of the sea is covered in sharp boulders and rocks, "+
      "nothing you would call a beach, but the place where the "+
      "crashing waters of the sea batter the edge of the land. It "+
      "runs mostly north to south, though it seems to swing out "+
      "more easterly as it runs south, and more westerly to the north.\n");
   add_item("village",
      "The village sits atop the hills at the west end of the road, "+
      "surrounded by and old stone wall. Most of the buildings and "+
      "houses of the village appear to be made of wood painted in "+
      "pastel colors with sharp red roofs.\n");
   add_item(({"houses","house","building","roofs"}),
      "The houses and buildings of the village are low one or two "+
      "level structures, most made with wood planks painted in "+
      "pastel pinks, blues and yellows. They are obviously much "+
      "newer than the old stone wall surrounding the village.\n");
   add_item("wall",
      "A wall made of large stones and boulders surrounds the "+
      "village. It is not quite as high as the roofs of the houses "+
      "of the settlement, and it looks to have been built long "+
      "before the newer houses.\n");
}
 
create_khalakhor_room()
{
   create_proad();
}
