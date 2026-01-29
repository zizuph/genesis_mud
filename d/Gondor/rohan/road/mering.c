#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

static object  Guard1,
               Guard2;

public void
add_guard()
{
    if (!objectp(Guard1))
    {
        Guard1 = clone_object(ROH_DIR + "npc/borderguard");
        Guard1->arm_me();
        Guard1->move_living("down", TO);
        if (objectp(Guard2))
            Guard1->team_join(Guard2);
    }
    if (!objectp(Guard2))
    {
        Guard2 = clone_object(ROH_DIR + "npc/borderguard");
        Guard2->arm_me();
        Guard2->move_living("down", TO);
        Guard1->team_join(Guard2);
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, add_guard);
}

void
create_roads() 
{
    set_street("wooden bridge");
    set_where("southeast");
    set_county("Fenmark");
    set_land("Rohan");
    set_mountain("Ered Nimrais");
    set_vegetation("juicy, spicy, long grass");
    set_forest("Firienwood");
    set_extraline("This is the center of the Firienwood Forest. The bridge "
      + "stands on a foundation made out of stone, crossing a mountain "
      + "stream that runs down the White Mountains through this forest to the "
      + "marshes fed by the mouths of the Entwash in the north. In the middle "
      + "of the bridge, sitting on top of one of the stone piers that carry "
      + "the bridge, there is a large obelisk.");

    add_exit(ROH_DIR + "road/er7",  "west", 0, 4);
    add_exit(ANO_DIR + "road/wr14", "east", 0, 4);
 
    (ROH_DIR + "plains/e14")->teledingska();
    (ROH_DIR + "plains/l10")->teledingska();

    add_item( ({"road", "west road", }), BSN(
        "The road is running through the Firienwood, crossing the bridge "
      + "here. To the east, it continues through a clearing that is just "
      + "barely visible through the trees, while disappearing quickly "
      + "to the west under the shadows of the giant oaks that make up the "
      + "forest."));
    add_item("bridge", BSN("It is a wooden bridge standing on a foundation "
      + "of expertly hewn big stone. The bridge looks to be quite old, but "
      + "it is in very good repair. Evidently the Lord of Rohan puts an "
      + "effort into the upkeep of the roads in his realm."));
    add_item(({"forest","firienwood", "firien wood", }), BSN(
        "This is the great oak wood that covers the flanks of the hill "
      + "Halifirien. On top of the Halifirien, you can see the last of the "
      + "seven beacon towers between Minas Tirith and Edoras."));
    add_item(({"mountain stream","stream","mering","mering stream","river"}),
        BSN("This is the Mering Stream which forms the border between Rohan "
      + "and Gondor. Its sources are high up in the White Mountains, and it "
      + "flows through the Firienwood and the green fields of the East Emnet "
      + "before it joins the River Entwash somewhere in the soggy marshes of "
      + "the Vale of Entwash."));
    add_item(({"obelisk","stone","stone marker"}), BSN(
        "The obelisk sits on top of the middle pier. Imbedded in the stone of "
      + "the obelisk you can see a metal marker. It reads:")
      + "\n   I, Cirion, Lord Steward of Gondor \n"
      + "   In the Two Thousand Five Hundred and Tenth Year\n"
      + "   Of The Third Age\n"
      + "   Hereby Declare\n"
      + "   With the authority of the Stewards of the Kings\n"
      + "   To Offer to Eorl, Son of Leod, Lord of the Eotheod\n"
      + "   In Recognition of the Valour of His People\n"
      + "   And of the Help Beyond Hope that He brought\n"
      + "   To Gondor in Time of Dire Need\n"
      + "   In the Battle of The Field of Celebrant:\n"
      + "   To Eorl I will Give in free Gift\n"
      + "   All the Great Land of Calenardhon from Anduin to Angren.\n"
      + "   There He Shall Be King, and His Heirs After Him,\n"
      + "   And the Eotheod shall Live in Freedom\n"
      + "   While the Authority of the Stewards Endures,\n"
      + "   Until the Great King Returns.\n\n");
   reset_room();
}

