#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("The crossing of roads in northern Solamnia");

    set_long("Here, the main road leads east and west, and a small " +
      "track branches off to the south. The remains of a signpost " +
      "stands sadly on the side of the road. A bit further north, you " +
      "can see a mighty river beyond the bushes, the occasional " +
      "lonely tree and the plains, which spread out in all " +
      "directions. On the southeast horizon, you can make out " +
      "a high, eerie looking mountain range.\n");

    add_item(({"crossroads", "crossroad", "road", "track", "path", "fork"}),
      "You stand at the fork of three ways. The main road leads " +
      "to the east and west. As well, a small track leads south.\n");
    add_item(({"signpost", "sign", "signs", "post"}),
      "This signpost has seen better years. Unfortunately, you " +
      "can only just make out the words that used to be there. " +
      "The signs point in three directions, north, east and "+
      "south.\n");
    add_cmd_item(({"signpost", "sign", "signs", "post"}), "read",
      "Cleaning of a bit of the road dust from the sign, you " +
      "can see a bit more clearly.\n" + 
      "The north sign reads: Kal ma .\n" +
      "The east sign reads:  a a rd  eep.\n" +
      "The south sign reads: V ng ard K p, S anlhus.\n");
    add_cmd_item(({"signpost", "sign", "signs", "post"}),
      ({"correct", "fix", "rotate", "turn"}),
      "The signpost is just too old to fix. Before breaking " +
      "it altogether, you decide not to touch it.\n");
    add_search(({"signpost", "sign", "signs", "post"}), 3,
      "After a detailed inspection of the remains of the signpost, " +
      "you come to the conclusion that the sign should be " +
      "rotated 90 degrees to point to the correct directions " +
      "again.\n");
    add_item(({"mountains", "range", "horizon"}),
      "A high mountain range looms in the southeast. One end " +
      "is directly to the east, and appears to continue " +
      "southwards out of your sight.\n");
    add_item(({"plains"}), "It is possible to leave the road, striking " +
      "out onto the desolate plains, but travelling will be more " +
      "strenuous off the beaten path.\n");
    add_item(({"bushes", "trees", "bush", "tree"}),
      "The plains are dotted with bushes and trees. Many appear " +
      "to be bending towards the ground from the heavy winds " +
      "that sweep the flat plains.\n");
    add_item(({"river", "mighty river", "water"}),
      "You cannot see much from this distance, but the occasional " +
      "reflection indicates that water must flow to " +
      "your north.\n");

    add_std_exits();
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 1;
}
