/*
 *      /d/Gondor/ithilien/nforest/fpath/fpath4.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 *      April 16, 2004: Tigerlily, modified for ranger
 *          recode
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

public int     go_north();
private int    check_track(object player);
public string  exa_bushes();
public string  exa_ground();
public string  exa_forest();

static object *Rabbit = allocate(2 + random(4));

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("green-shadowed woodlands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("You are walking under old trees in ever-green woods. " +
        "The woodlands seem to extend forever in every direction, but " +
        "they are growing thinner here. The land falls more steeply " +
        "than further to the east. To the north you can see a few " +
        "bushes. An ever-present sweet and pungent smell of herbs and " +
        "flowers dominates in Ithilien, the garden of Gondor.");

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "ginger",
                     HERB_DIR + "thyme",   HERB_DIR + "hemlock", }),
                  ({ "ground", "field", "flowers", "forest", }), 3);
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");

    add_item( ({ "forest", "wood", "woodlands", "herbs", }), &exa_forest());
    add_item( ({ "ground", "path", "tracks"}), &exa_ground());
    add_item( ({ "bush", "bushes", "thicket"}), &exa_bushes());

    add_exit(ITH_DIR + "nforest/fpath/bushes1", "north",     &go_north(), 2, 1);
    add_exit(ITH_DIR + "nforest/fpath/fpath3",  "northeast", 0, 4);
    add_exit(ITH_DIR + "nforest/fpath/fpath41", "south",     0, 4);
    add_exit(ITH_DIR + "nforest/fpath/fpath5",  "west",      0, 4);

    reset_room();
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Rabbit, NPC_DIR + "rabbit", 15.0 + rnd() * 30.0, 
        ITH_DIR + "nforest/fpath");
}
 
public string
exa_forest()
{
    string  desc =
        "Many great trees are growing here, cedars and giant oaks and " +
             "hoary ash trees.";
    if (check_track(TP))
        desc += " Looking carefully, you can make out a few tracks on " +
            "the ground.";
    desc += " Many herbs of different forms and scents fill the air with " +
        "sweet and pungent smells.";

    return BSN(desc);
}

public string
exa_ground()
{
    string  desc;
    int     ic;
    
    if (ic = check_track(TP))
    {
        desc = "Looking carefully, you can make out several tracks among " +
            "the dry leaves and twigs on the floor. Following the tracks, " +
            "you find a hidden path leading north through the bushes.";
    if (ic == 4)
        desc += " You know that this is the path to the Henneth Annun, " +
            "the secret hideout of the Rangers of Ithilien.";
    }
    else
        desc = "There are mostly dry leaves and moss on the forest floor.";
    
    return BSN(desc);
}

public string
exa_bushes()
{
    string  desc =
        "Between the trees to the north, a few bushes are growing. " +
            "They are green and fair, with a delicate fragrance.";
  
    switch (check_track(TP))
    {
    case 4: 
        desc += " Hidden by these bushes is the path to the Henneth " +
           "Annun, the secret hideout of the rangers of Ithilien."; 
        break;
    case 3: 
    case 2: 
        desc += " Behind the bushes, you see a path."; 
        break;
    case 1: 
        desc += " Behind the bushes, you discover a well hidden path.";
        break;
    default:
        break;
    }
    
    return BSN(desc);
}

public int
go_north()
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
        write("You discover a path leading north and follow it.\n");
        break;
    default:
        write("There is no obvious exit north.\n");
        return 1;
        break;
    }
    return 0;
}

private int
check_track(object player)
{

    int     track = player->query_skill(SS_TRACKING),
            aware = player->query_skill(SS_AWARENESS);

#ifndef  NEW_RANGERS_OPEN 
//old ranger Ithilien designation
    if ((player->query_company() == "Ithilien") || 
        player->query_prop("ranger_ithilien_visitor") ||
        IS_GONDOR_WIZARD(player))
        return 4;
    if (player->query_company()) 
        return 3;
#endif
//else
#ifdef  NEW_RANGERS_OPEN 
    if ((ITHILIEN_MEMBER(player)) || 
        MANAGER->query_voted_in(player->query_real_name(), "ithilien") ||
        IS_GONDOR_WIZARD(player))
        return 4;
    if (RANGERS_MEMBER(player))
        return 3;
#endif


    if (strlen(player->query_company()))
        return 3;
    if (player->query_prop("ranger_ithilien_found")) 
        return 2;
    if ((track+aware)/2 >= 50) 
    {
        player->add_prop("ranger_ithilien_found", 1);
        return 1;
    }
    return 0;
}
