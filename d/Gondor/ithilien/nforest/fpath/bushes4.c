/*
 *      /d/Gondor/ithilien/nforest/fpath/bushes4.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 *      April 16, 2004: Tweaked slightly by Tigerlily
 *          for ranger recode
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define MIN_SKILL               (70 + random(21))
#define RANGER_ITHILIEN_FOUND   "ranger_ithilien_found"
#define RANGER_ITHILIEN_VISITOR "ranger_ithilien_visitor"

public int     go_northwest();
public string  exa_forest();
public string  exa_ground();
public string  exa_bushes();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("in a bushy thicket");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("rowan");
    set_extraline("You are walking through a bushy thicket under old " +
        "trees in ever-green woods. To the northeast, you can hear a " +
        "small river rushing down a narrow gorge, blocking your progress " +
        "in that direction. The land is falling steeply towards the " +
        "west. Looking over the top of the bushes there, you can see " +
        "lowlands and broad meads, and glinting far off the wide waters " +
        "of the Anduin.");

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "mint", 
             HERB_DIR + "ungolestel",  }), 
         ({ "ground", "field", "flowers", "forest", "bushes", }), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"gorge","river","stream"}), BSN(
        "To the northeast, hidden by some bushes, you can hear a small " +
        "river rushing over a stony bed."));
    add_item( ({"rock", "cliff", }), BSN(
        "The giant rock to the north rises like a dark shadow out of " +
        "the forest to the north. The sheer cliff face is completely " +
        "free of vegetation and without any features that might make " +
        "it possible to climb it."));
    add_item(({"vale","anduin"}), BSN(
        "Looking west over the top of the bushes, you can see far " +
        "below you green lowlands and broad meads on both sides of the " +
        "wide waters of the Anduin. You guess that there are still " +
        "many miles between you and the mighty river."));

    add_item(({"forest","wood","woodlands","herbs"}), &exa_forest());
    add_item(({"ground","path","tracks"}), &exa_ground());
    add_item(({"bush","bushes","thicket"}), &exa_bushes());

    add_exit(ITH_DIR + "nforest/fpath/bushes2", "east",      0, 3);
    add_exit(ITH_DIR + "nforest/fpath/bushes3", "southeast", 0, 3);
    add_exit(ITH_DIR + "nforest/fpath/bushes5", "northwest", &go_northwest(), 3, 1);
}

public string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

private int
check_track(object player)
{
    int     track  = player->query_skill(SS_TRACKING), 
            aware  = player->query_skill(SS_AWARENESS);

#ifdef  NEW_RANGERS_OPEN 
    if ((ITHILIEN_MEMBER(player)) || 
        player->query_prop(RANGER_ITHILIEN_VISITOR) ||
        MANAGER->query_voted_in(player->query_real_name(), "ithilien") ||
        IS_GONDOR_WIZARD(player))
        return 4;
    if (RANGERS_MEMBER(player))
        return 3;
#endif

//else

#ifndef  NEW_RANGERS_OPEN 
//old ranger Ithilien designation
    if ((player->query_company() == "Ithilien") || 
        player->query_prop(RANGER_ITHILIEN_VISITOR) ||
        IS_GONDOR_WIZARD(player))
        return 4;
    if (player->query_company()) 
        return 3;
#endif

    if (player->query_prop(RANGER_ITHILIEN_FOUND) >= 5) 
        return 2;
    if ((track+aware)/2 >= MIN_SKILL) 
    {
        player->add_prop(RANGER_ITHILIEN_FOUND, 5);
        return 1;
    }
    return 0;
}

public string 
exa_forest()
{
    string  desc = "Many great trees are growing here, rowan trees and " +
        "hoary ash trees mostly. ";

    if (check_track(TP))
        desc += " Looking carefully, you can make out a few tracks on the ground.";
    desc += " Many herbs of different forms and scents fill the air " +
        "with sweet and pungent smells.";
    
    return BSN(desc);
}

public string
exa_ground()
{
    string  desc;
    int     ic;

    if (ic = check_track(TP))
    {
        desc = "Looking carefully, you can make out several tracks " +
            "among the dry leaves and twigs on the floor. Following " +
            "the tracks, you find that the hidden path continues " +
            "northwest through the bushes.";
        if (ic == 4)
            desc += " You know that this is the path to the Henneth " +
                "Annun, the secret hideout of the Rangers of Ithilien.";
    }
    else
        desc = "There are mostly dry leaves and moss on the forest " +
            "floor, and a few tracks leading southeast.";

    return BSN(desc);
}

public int
go_northwest()
{
    switch (check_track(TP))
    {
    case 4: 
        write("You follow the path to the Henneth Annun.\n"); 
        break;
    case 3:
    case 2: 
        write("You follow a path.\n"); 
        break;
    case 1: 
        write("You discover a path leading northwest and follow it.\n");
        break;
    default:
        write("There is no obvious exit northwest.\n");
        return 1;
        break;
    }
    return 0;
}

public string
exa_bushes()
{
    string desc = "Bushes are growing all around you. They are green " +
        "and fair, with a delicate fragrance.";
  
    switch (check_track(TP))
    {
    case 4: 
        desc += " Hidden by the bushes to the northwest is the path " +
            "to the Henneth Annun, the secret hideout of the " +
            "rangers of Ithilien."; 
        break;
    case 3: 
    case 2: 
        desc += " Behind the bushes to the northwest, you see a path."; 
        break;
    case 1: 
        desc += " Behind the bushes to the northwest, you discover " +
            "a well hidden path.";
        break;
    default:
        break;
    }

    return BSN(desc);
}
