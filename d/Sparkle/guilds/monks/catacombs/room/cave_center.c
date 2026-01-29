/*******************************************************************\
| CAVE_CENTER.C                                                     |
\*******************************************************************/

/*
 * 03/07/23 Arandir     Created
 * 03/08/09 Arandir     Added precepts to the walkways
 * 04/03/07 Arandir     Added columns and dragons
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit CC_ROOM_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("central podium");
  set_long ("The podium you stand on is situated in the very center " +
            "of the large cave, surrounded on all sides by stone " +
            "columns. From here, the intricate weave of the narrow " +
            "stone walkways looks truly beautiful, but even more " +
            "catching to the eye is the silvery glow coming from " +
            "the dragons you have passed on your way here. " +
            "The podium itself is bare, its floor covered with " +
            "sand that softens your steps.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("perch_4_0", "south");
  add_exit ("perch_4_1", "southwest");
  add_exit ("perch_4_2", "northwest");
  add_exit ("perch_4_3", "northeast");
  add_exit ("perch_4_4", "southeast");

  add_item (({ "podium" }),
            "You stand on a bare podium in a center of a large cave.\n");
  add_item (({ "floor", "sand" }),
            "On the edges of the podium, the floor is covered with a " +
            "mixture of multicolored sand that glistens in the silvery " +
            "light. Towards the center, the colors become increasingly " +
            "more regular, forming a complex pattern of a great mandala.\n");
  add_item (({ "grain", "grains", "mandala" }),
            "You study the mandala carefully, admiring the expression of " +
            "balance instilled into its pattern. Noting a few damaged " +
            "spots, you still marvel how it could have remained intact, " +
            "only to have your unspoken question answered a moment later. " +
            "The grains of sand appear to be shifting on their own to " +
            "repair the damage, adding yet another level of symbolism " +
            "to the expression of balance in the infinite cycle of " +
            "creation and destruction.\n" +
            dg_embed_action ("gasps in wonder and awe of the great mandala."));

  add_item (({ "pattern", "weave", "structure", "structures" }),
            "Looking at how the intricate weave of the narrow stone " +
            "walkways seems to complement the mandala in its center, " +
            "you get a hunch that there must be a deeper meaning in " +
            "the entire arrangement. And even if you are not sure " +
            "you grasp it, you are enjoying the view.\n");

  add_item (({ "column", "columns", "pillar", "pillars", "dragon", "dragons" }),
            "The massive stone columns of smooth stone form a gradually " +
            "descending slope, with the top of each column directly " +
            "visible. The dragons that you passed on your way here " +
            "glow with a silvery light, their gazes fixed upon you " +
            "in a frozen expression of intense scrutiny. The walkways " +
            "between the columns add to the grandeur of the entire setup.\n");

  add_item (({ "walkway", "walkways", "ribbon", "ribbons" }),
            "Five stone walkways lead from the podium, spiraling away to " +
            "join the complex pattern of the other walkways and columns " +
            "that fill the cave. The lack of railing makes the stone " +
            "structures look like giant ribbons suspended in space, " +
            "their slant making the shades cast by the uneven " +
            "surface look like strange symbols.\n");
  add_item (({ "shades", "slant", "surface",
               "symbols", "strange symbols",
               "runes", "strange runes" }),
            "The angle of the light falling on the stone walkways is " +
            "such that their uneven surface casts long shadows that " +
            "appear to form symbols. Taking a closer look at each " +
            "of the walkways might reveal more.\n");
  add_item (({ "first walkway", "south walkway", "southern walkway" }),
            "As you focus on the surface of the south walkway, you " +
            "realize that the shades form a sentence. It reads: " +
            "Perfect Thy Soul.\n");
  add_item (({ "second walkway", "southwest walkway", "southwestern walkway" }),
            "As you focus on the surface of the southwest walkway, you " +
            "realize that the shades form a sentence. It reads: " +
            "Keep Thy Ways Honest.\n");
  add_item (({ "third walkway", "northwest walkway", "northwestern walkway" }),
            "As you focus on the surface of the northwest walkway, you " +
            "realize that the shades form a sentence. It reads: " +
            "Cultivate Spirit Of Effort.\n");
  add_item (({ "fourth walkway", "northeast walkway", "northeastern walkway" }),
            "As you focus on the surface of the northeast walkway, you " +
            "realize that the shades form a sentence. It reads: " +
            "Develop Respectful Attitude.\n");
  add_item (({ "fifth walkway", "southeast walkway", "southeastern walkway" }),
            "As you focus on the surface of the southeast walkway, you " +
            "realize that the shades form a sentence. It reads: " +
            "Shun Unenlightened Violence.\n");

  cc_item_cave_inside ();

  // Clone the opponent avatar that occupies the podium.

  dg_clone_here (CC_PATH_NPC + "/avatar");
}

//-------------------------------------------------------------------

