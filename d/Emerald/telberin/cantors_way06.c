#include "defs.h"

inherit TELBERIN_CANTORS_WAY;

public void
create_cantors_way()
{
    set_em_long("Cantors Way extends to the east and west here, curving"
      + " very gradually from the point at which you stand and heading"
      + " very slightly southward in its narrow eliptical form. To the"
      + " south, a bright green lawn runs east and west, bordering the"
      + " long pool which runs the length of the street as it travels"
      + " in both directions. Just to the north, a sign hangs"
      + " prominently above the entrance to a well-framed yet elegant"
      + " building, setting it apart from the others.\n");

    add_item( ({ "sign", "alabaster sign", "white sign" }),
        "The sign is large, and appears to be made of alabaster or some"
      + " other white material. The words 'Post Office' have been carved"
      + " in elegant strokes from its center.\n");
    add_item( ({ "post", "post office", "office", "elegant building",
                 "well-framed building", "well framed building",
                 "well-framed elegant building", "building" }),
        "Just to the north, a well-framed building looks onto the"
      + " street. Every so often, people carrying packages and"
      + " parcels enter or leave. A sign hangs prominently above"
      + " its entrance.\n");
    add_item( ({ "door", "doors", "entrance", "steel door",
                 "steel doors", "strong door", "strong doors",
                 "strong steel door", "strong steel doors" }),
        "Strong steel doors frame the entrance to the building."
      + " There is obviously some matter of security about the"
      + " place.\n");
    add_item( ({ "alabaster", "white material" }),
        "The sign appears to have been carved from alabaster. It is"
      + " very elegant and has been beveled along its edges.\n");

    add_cmd_item( ({ "sign", "alabaster sign", "white sign" }),
                  ({ "read" }),
        "The sign reads, 'Post Office.'\n");

    add_building("/d/Emerald/telberin/arts/post.c");

    add_exit("/d/Emerald/telberin/arts/post.c", "north", 0, 1, 1);
    add_exit("cantors_way07", "west");
    add_exit("cantors_way05", "east");
}
