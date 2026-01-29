/* 
 *      /d/Gondor/anorien/cairandros/wford.c
 *
 *      Varian 2016
 */
#pragma strict_types
inherit "/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"

public void

create_room() 
{
    set_short("A ford across the Anduin River at Cair Andros");
    set_long("You are in the middle of the Anduin river, wading across " +
        "the ford between Cair Andros and Anorien. The island of Cair " +
        "Andros lies immediately to the east, and is heavily forested " +
        "with a tall stone fort guarding the ford at the southern end " +
        "of the island. To the west, you can see the rolling plains of " +
        "Anorien, covered in a blanket of tall green grass and " +
        "colourful wildflowers stretching out endlessly.\n");
    
    add_item(({"river","anduin","anduin river","water","great river"}),
        "This is the Anduin, the great river that flows down from the " +
        "north before emptying out into the sea. In the middle of the " +
        "river here, you see the island of Cair Andros guarding the " +
        "ford you are crossing.\n");
    add_item(({"ford","fords","shallows"}),
        "This ford connects Anorien to the island of Cair Andros in the " +
        "shallows of the Anduin. A second ford connects Cair Andros to " +
        "the plains of Ithilien farther to the east.\n");
    add_item(({"forest","forests","trees","tree","wood","woods"}),
        "There are many trees growing across the land that surrounds you, " +
        "from the dense woods that populate the northern reaches of " +
        "Cair Andros to the dark forests that hide amongst the hills of " +
        "Ithilien.\n");
    add_item(({"forest of ithilien","forests of ithilien","shadow","shadows",
            "trees of ithilien","woods of ithilien","dark forests"}),
        "Scattered across the hills of Ithilien, there are large pockets " +
        "of dark forests, including the densely packed trees that line " +
        "riverbank in shadows just east of here.\n");
    add_item(({"bank","riverbank","banks","rivernbanks"}),
        "On the banks of the Anduin River, you have Ithilien to the east " +
        "and Anorien to the west.\n");
    add_item(({"hill","hills","mountain","mountains","mountains of shadow",
            "forested hills"}),
        "The land of Ithilien is filled with countless hills that march " +
        "up the jagged slopes of the ominous Mountains of Shadow.\n");
    add_item(({"forest of cair andros","forests of cair andros","dense woods",
            "woods of cair andros","woods on island","trees of cair andros",
            "trees on island"}),
        "The northern end of the island of Cair Andros seems to be filled " +
        "with hundreds of trees that collect into dense woods.\n");
    add_item(({"gondor"}),
        "You are in the lands of Gondor, an ancient kingdom of men who " +
        "live in the southern reaches of Middle-Earth.\n");
    add_item(({"mordor"}),
        "On the other side of the mountains, lies the land of Mordor.\n");
    add_item(({"ithilien"}),
        "The lands of Ithilien are on the far eastern bank of the river, " +
        "filled with shadowy forests hiding in the hills and huddled beneath " +
        "the ominous gaze of the Mountains of Shadow that dominate the " +
        "eastern horizon.\n");
    add_item(({"anorien","plains","grass","grassy plains"}),
        "The grassy plains of Anorien roll across gentle hills just west " +
        "of here, their green fields and brightly coloured wildflowers " +
        "stretching out endlessly.\n");
    add_item(({"fields","green fields","flowers","wildflowers","grass",
            "colourful wildflowers","colourful flowers","tall grass",
            "brightly coloured flowers","brightly coloured wildflowers",
            "green grass","tall green grass"}),
        "The rolling plains of Anorien are covered is a beautiful blanket " +
        "of brightly coloured wildflowers that decorate endless fields " +
        "of tall green grass.\n");
    add_item(({"sea","ocean"}),
        "Somewhere far to the south, the Anduin River empties out into " +
        "the sea.\n");
    add_item(({"middle earth","middle-earth"}),
        "You are in the lands of Middle-Earth, and more specifically, " +
        "currently inside the kingdom of Gondor.\n");
    add_item(({"west", "western horizon"}),
        "The rolling plains of Anorien stretch out endlessly to the " +
        "west.\n");
    add_item(({"southwest", "southwestern horizon"}),
        "The rolling plains of Anorien stretch out endlessly to the " +
        "southwest.\n");
    add_item(({"northwest", "northwestern horizon"}),
        "The rolling plains of Anorien stretch out to the northwest, " +
        "ending where the mouths of the Entwash empty out into the " +
        "Anduin.\n");
    add_item(({"north", "northern horizon"}),
        "To the north, you can see the rushing waters splitting around the " +
        "island of Cair Andros as they flow south towards the sea.\n");
    add_item(({"east", "eastern horizon"}),
        "The eastern horizon is filled mostly with the island of Cair " +
        "Andros, although you can see the forested hills of Ithilien and " +
        "the Mountains of Shadow beyond.\n");
    add_item(({"southeast", "southeastern horizon"}),
        "The southeastern horizon is filled mostly with the island of Cair " +
        "Andros, although you can see the forested hills of Ithilien and " +
        "the Mountains of Shadow beyond.\n");
    add_item(({"northeast", "northeastern horizon"}),
        "The northeastern horizon is filled mostly with the island of Cair " +
        "Andros, although you can see the forested hills of Ithilien and " +
        "the Mountains of Shadow beyond.\n");
    add_item(({"south", "southern horizon"}),
        "The tumbling waters of the Anduin river stretch out in the " +
        "distance as they run towards the sea.\n");
    add_item(({"horizon", "horizons"}),
        "There is a lot of land around you out here, which horizon did " +
        "you want to examine?\n");
    add_item(({"up", "sky", "sun", "moon", "stars"}),
        "Looking up, you can see the " + VBFC("day_desc") + " " + 
        VBFC("sun_moon") + " high in the sky above you.\n");
    add_item(({"down", "ground"}),
        "You can barely see your feet through the water as it runs " +
        "through the shallows of the Anduin here.\n");

    add_exit(CAIRANDROS_DIR + "fort1","east","@@cairandros@@");
    add_exit(PLAINS_DIR + "an16w3n","west","@@anorien@@");

    set_drink_from(({"river","anduin","anduin river"}));

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}

int
cairandros()
{
    int ran, skill;
    ran = random(31);
    skill = TP->query_skill(SS_SWIM);
    if(ran > skill)
    {
    write("You try to wade through the water, but a strong current in the " +
        "river knocks you off balance. You will have to try again.\n");
    say(QCTNAME(TP)+" tries to wade east across the ford, but is " +
        "knocked off balance by the river current.\n");
    TP->add_fatigue(-10);
    return 1;
    }
    write("You cross over the Anduin and enter the fortress on the island " +
        "of Cair Andros.\n");
    return 0;
}
int
anorien()
{
    int ran, skill;
    ran = random(31);
    skill = TP->query_skill(SS_SWIM);
    if(ran > skill)
    {
    write("You try to wade through the water, but a strong current in the " +
        "river knocks you off balance. You will have to try again.\n");
    say(QCTNAME(TP)+" tries to wade west across the ford, but is " +
        "knocked off balance by the river current.\n");
    TP->add_fatigue(-10);
    return 1;
    }
    write("You cross over the Anduin and enter the land of Anorien.\n");
    return 0;
}
/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */
public void
drink_message(string from)
{
    write("You cup your hands in the river and take a drink of water.\n");
    say(QCTNAME(TP) + " cups their hands and bends down in the river to " +
        "take drink of water.\n");
}
/* drink_message */
void
init()
{
    ::init();
    init_drink();
}