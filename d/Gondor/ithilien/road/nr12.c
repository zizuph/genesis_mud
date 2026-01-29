/*
 *      /d/Gondor/ithilien/road/nr12.c
 *
 *      Coded by Olorin, 1993
 *
 *      Modification log:
 *       1-Feb-1997, Olorin:    Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public int    test_npc();

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("heathland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs northeast towards Morannon, south to the crossroads " +
        "where this road meets the road from Osgiliath to Minas Morgul. It has been " +
        "made in a long lost time, but here it has been newly repaired. The " +
        "handiwork of the Men of old can still be seen in its straight sure flight " +
        "and level course. East of the road, the dark shadows of the Ephel Duath " +
        "are rising, covered with sombre trees like dark clouds. To the west "+
        "lies a tumbled heathland, grown with ling and broom and cornel. "+
        "Here and there knots of tall pine-trees can be seen.\n");
    add_mountains(1, "less than a league",
        "The roots of the hills are rising next to the road " +
        "and are covered with sombre trees like dark clouds. " +
        "North of here the mountains are receding eastward.");
    add_road(6);
    add_item( ({"forest","wood","woods","trees","knots"}), 
        "On the heathland west of the road one can see knots of pine-trees " +
        "rising out from among the shrubs and bushes dominating the heath.\n");
    add_item(({"heath","heathland","heath land"}), 
        "All about you lies a tumbled heathland, grown with ling and " +
        "broom and cornel, and other shrubs you do not know. Here and there " +
        "you can see knots of tall pine-trees. The air is fresh and fragant.\n");
    add_exit(ITH_DIR + "poros/ford_north",  "northeast", test_npc);
    add_exit(ITH_DIR + "road/nr11",         "south",     test_exit, 3);

    set_patrol_dir("northeast");
}

public int
test_npc()
{
    if (TP->query_wiz_level())
    {
        write("The road northeast is still closed for mortals.\n" +
              "Since you are a wizard, you can go on.\n");
        return 0;
    }

    /* Removed by Gwyneth. I see no reason to allow npcs through
       this exit if it is closed to mortals. Keeping the code in
       case there is a reason for it that is not obviously apparent.
    */
    if (TP->query_npc() == 1)
    {    
    
    return 0;
    }

    else
    {
        write("The road is closed by order of Lord Denethor, Steward " +
            "of Gondor.\n");
        return 1;
    }
}
