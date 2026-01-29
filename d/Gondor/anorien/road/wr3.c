/*
 *	/d/Gondor/anorien/road/wr3.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define LOG		"/d/Gondor/log/amon-din"
#define DIN_I_SAW_PATH	"_din_i_saw_path"
#define MIN_AWARE	24

public string  exa_hill();
public string  exa_path();
public int     follow_path();

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("soft, light green grass");
    set_treetype("oak");
    set_extraline("Along each side of the road, tall oaks have been " +
        "planted to shade the travellers, and to beautify the way. "+
        "The road continues southeast along the eastern edges "+
        "of the Druadan Forest. Beyond the forest to the southwest " +
        "the White Mountains dominate the view, but a tall hilltop " +
        "looms out of the forest itself, southwest of here. The " +
        "plains of Anorien stretch out north and east.");
    add_item( ({"path","paths"}), exa_path);
    add_item( ({"oak", "oaks", "tree", "trees"}), BSN(
        "These tall oaks have been planted along both sides of the " +
        "road to shade travellers. Slender trunks are topped by wide " +
        "crowns with thick foliage."));
    add_item(({"hilltop", "hill", "amon din"}), exa_hill);
    add_item(({"forest","druadan forest"}), BSN(
        "Just beyond the roadside trees on the southwest side of " +
        "the road, is the Druedain Forest. Tall trees with dense " +
        "foliage make up the forest. The shadows below the trees are " +
        "filled with dark underbrush that makes passage impossible."));
    add_item(({"mountains","white mountains"}), BSN(
        "Beyond the forest to the southwest, you can see the Ered Nimrais, " +
        "the White Mountains. Some of the higher foothills of the mountains " +
        "loom up in the forest, and upon some of these hilltops, towers have " +
        "been built. These towers are used for beacon fires, by which Gondor and " +
        "Rohan call for eachother's help in times of war. "));
    add_item(({"thicket", "bushes", "trees", "dense thicket"}),
        "Large clusters of bushes gather all along the west side of " +
        "the road, but they are far too thick for you to enter.\n");
    set_no_exit_msg(({"south","west"}),
        "The bushes are too thick to enter from here.\n");

    add_exit(ANO_DIR + "road/wr4", "northwest",           0, 3, 0);
    add_exit(ANO_DIR + "road/wr2", "southeast",           0, 3, 0);
    add_exit(AMON_DIR + "ad1",     "southwest", follow_path, 2, 1);
    add_exit(ANO_DIR + "plains/an13w8n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an12w8n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an13w9n","east",0,5,1);

}

public string
exa_hill()
{
    int     min = MIN_AWARE;
    string  txt = "This is the hilltop of Amon Din, known in the land"
      + " to be the first in a series of hills to house beacon towers"
      + " which the Steward's Armies can set aflame to alert the"
      + " allies in Rohan that need is at hand.";
 
    min += random(min / 4) + 1;
    if (TP->query_skill(SS_AWARENESS) > min)
    {
        TP->add_prop(DIN_I_SAW_PATH, 1);
        txt += " You notice a concealed path running"
	    +  " southwest in the direction of the hilltop.";
    }
    return BSN(txt);
}
 
public int
follow_path()
{
    write("You leave the road and carefully follow the path.\n");
    return 0;
}
 
public string
exa_path()
{
    if (!TP->query_prop(DIN_I_SAW_PATH))
    {
        return BSN("You have not located any path to examine.");
    }

    return BSN("There seems to be a path of some kind running towards"
      + " the hilltop to the southwest. It seems as if someone has"
      + " attempted to conceal it from view.");
}

/*
 This was used while the plains were under construction. Now open
 Varian - August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}

*/