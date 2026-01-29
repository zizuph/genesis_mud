
/* 	Grove of Diabrecho in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Calia/sys/water.h"
#include "defs.h"
#include "/d/Krynn/common/herbsearch.h"

#define KRYNN_HERBS "/d/Krynn/common/herbs/"
#define KALAD_HERBS "/d/Kalad/common/herbs/"

void reset_herb_room()
{
    set_searched(random(6));    /* Lots of plant life here */
}

void
create_water_room()
{
    set_short("Grove of Diabrecho");
    set_long("You have entered into the sacred Grove of "+
        "Diabrecho. This multitude of plants, trees and "+
        "flowers are all a tribute to the Lord of the Seas "+
        "himself. The grove continues to the northwest and "+
        "the southwest along a small pathway. The road "+
        "continues west to another bridge. The Lesser Zone "+
        "lies around you in all other directions.\n");
    add_item(({"bridge","tower","guard tower"}),"The bridge leads off to "+
        "the west into the Citadel of the city. On the top "+
        "of the bridge sits the three storey guard tower.\n");
    add_item(({"grove","sacred grove","Grove of Diabrecho",
        "sacred Grove of Diabrecho"}),"The Sacred Grove of "+
        "Diabrecho is a tribute from the citizens of this "+
        "city to the life-saving Lord of the Seas, Lord "+
        "Diabrecho. It is because of his powers that these "+
        "citizens are alive and well and living in this "+
        "underwater paradise. It is made up from various "+
        "plants, trees and flowers of every colour imaginable. "+
        "It continues off to the northwest and southwest along a "+
        "small pathway.\n");
    add_item(({"path","pathway","small path","small pathway"}),
        "This small pathway is made from hundreds of intricately "+
        "placed gold covered stones that form a path to follow "+
        "through the Grove. It leads off to the northwest and "+
        "southwest. Above you, you notice the underside of the "+
        "racetrack that the racers follow from the grandstand.\n");
    add_item(({"racetrack","track","race track"}),"The racetrack seems "+
        "to follow the entire Grove around in a large circle.\n");
    add_item(({"stone","stones","gold covered stone","gold covered stones",
        "gold stone","gold stones","pathway stone","pathway stones"}),
        "These stones seem to be cut just perfect so that they would "+
        "fit together just perfectly to form this pathway. They are "+
        "covered in gold.\n");
    add_item(({"plant","plants"}),"There are several types of "+
        "plants growing in this place including trees and "+
        "flowers.\n");
    add_item(({"flowers","flower"}),"You recognize two flowers "+
        "here, the orchid and the iris.\n");
    add_item(({"tree","trees"}),"There are two types of trees "+
        "growing here in the Grove. The bonsai trees and the "+
        "gardenia trees.\n");
    add_item(({"orchid","orchids"}),"These orchids, known also as snowfrost "+
        "phalaenopsis, have the typical orchid long, broad, waxy "+
        "leaves at the base and a tall spindly stem that offers "+
        "the heavy blossoms at the top of it, all in a row. They "+
        "are light pink with a dark pink stamen and frosted outer "+
        "rims, hence the name.\n");
    add_item("iris","There are irises of both blue and purple in "+
        "colour, all of them with a yellow centre, long pointed "+
        "leaves, and blooms that appear to have burst from the stem.\n");
    add_item(({"gardenia tree","gardenia trees","gardenia"}),"This small "+
        "flowering tree has large white blooms and large, oval "+
        "waxy leaves. These trees are very delicate and appear "+
        "as though someone has taken a bunch of fallen flower "+
        "petals and spread them out in a flat circle and called "+
        "it a plant. They vary in size from a hands height tall "+
        "to almost two hands height.\n");
    add_item(({"bonsai tree","bonsai trees","bonsai"}),"These diminutive "+
        "trees have a small twisting leaning trunk and branches "+
        "and tiny leaves. Each diminutive tree represents nature "+
        "in concentrated form, and no two trees are alike. They "+
        "appear to have been shaped by the currents. They are "+
        "about one and a half hands high, and have a wide, triangular "+
        "head of foliage and exaggerated width to heighth proportion. "+
        "They are surrounded by mossy stones.\n");
    add_item(({"mossy stones","mossy stone"}),"These small stones "+
        "are covered in some strange moss and surround the bonsai "+
        "trees.\n");
    add_item(({"strange moss","moss"}),"The moss is brownish-red in "+
        "colour and very strange to the touch.\n");

    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");

    seteuid(getuid(TO));

    if (random(100) > 30) add_herb_file(KRYNN_HERBS+"bull_kelp");
    if (random(100) > 50) add_herb_file(KRYNN_HERBS+"sargassum");
    add_herb_file(KRYNN_HERBS+"sea_bubble");
    if (random(100) > 70) add_herb_file(KALAD_HERBS+"glowshroom");
    if (random(100) > 40) add_herb_file(KRYNN_HERBS+"elkhorn_kelp");
    if (random(100) > 60) add_herb_file(KRYNN_HERBS+"sea_lettuce");


    add_swim_exit(THALL+"lesser27","north",0,1);
    add_swim_exit(THALC+"brguard_e_1_1","west",0,1);
    add_swim_exit(THALL+"lesser28","east",0,1);
    add_swim_exit(THALL+"lesser30","south",0,1);
    add_swim_exit(GROVE+"grove12","northwest",0,1);
    add_swim_exit(THALL+"lesser26","northeast",0,1);
    add_swim_exit(GROVE+"grove14","southwest",0,1);
    add_swim_exit(THALL+"lesser29","southeast",0,1);
}

void
reset_room()
{
    reset_herb_room();
}
