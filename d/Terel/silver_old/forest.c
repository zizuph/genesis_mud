/* This comment tells emacs to use c++-mode -*- C++ -*- */
// Southern Forest surrounding the road leading to 
// the Stonehold
// Tomas  -- Jan 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

string long_desc();


object pebble;
int long, short;


int set_long_desc(int i)
{
    long = i;
}

int set_short_desc(int i)
{
    short = i;
}

init()
{
    ::init();
    start_room_tells();
}


public void
create_room()
{
    ::create_room();
    set_short("@@short_desc@@");
    set_long("You are standing in the "+long_desc()+". Everything in the forest "+
                   "is covered in snow. Trees rise up to the sky all around "+
                   "blocking your view above. Here and there you see various "+
                   "animals skitter behind fallen logs or other plants. The "+
                   "snow crunches below your feet with every step. ");


    add_prop("_room_m_da_dragonsteed_no_land","The forest " +
       "is too thick for your dragon to land in it.");

    add_item(({"rocks", "pebbles"}),
        "Various sized rocks and pebbles litter the forest " +
        "floor.\n");
    add_item(({"plants", "woodland plants"}),
        "Besides trees, a diverse number of plants grow in the " +
        "forest. Bushes grow everywhere, somewhat " +
        "impeding your travel and blocking your view.\n");
    add_item("bushes",
        "Bushes of different color and sizes grow everywhere. " +
        "Some are thick and block your view while others are " +
        "thin and spindly.\n");
    add_item(({"snow", "drift","snowdrift","snow drifts","snowsdrift",
               "patches of snow"}),
        "The forest, plants, shrubs and ground are covered in " +
        "a thick blanket of snow.\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them " +
        "are partially buried in the snow.\n");
    add_item(({"tree","trees"}),
        "Evergreens, the dominant tree in this part of the " +
        "forest, grow thick here.\n");
    add_item(({"evergreen trees", "conifer trees", "evergreen", 
        "evergreens", "conifers", "conifer"}),
        "The dominate evergreen trees here are tall pines. Also " +
        "growing here are hemlocks and some cedars. The trees reach " +
        "to the sky and block out much of the light.\n");
    add_item(({"pine trees", "pine tree", "hemlock", "hemlocks",
        "cedar", "cedars", "pines", "hemlock trees", "hemlock tree",
        "cedar trees", "cedar tree"}),
        "These evergreens dominate the forest. Some grow along the rocks " +
        "showing exposed roots.\n");
    add_item(({"ground", "path", "forest debris", "debris", 
        "forest's floor", "floor", "down"}),
        "The ground is mostly covered in deep snow with the exception of various " +
        "dry spots around rock outcroppings, underneath " +
        "bushes and along the edges of fallen trees. Twigs, branches " +
        "and other various forest debris can be seen mixed with " +
        "snow.\n");
    add_item(({"leaves", "leaf"}),
        "You see a mat of both fresh and dead leaves covering the " +
        "ground. Poking out of them are dead branches, some " +
        "plants, stones, and other signs of a living forest.\n");
    add_item(({"fallen branches", "dead branches", "dead branch", 
            "branches", "branch"}),
        "Broken branches can be seen scattered about the snow drifts. " +
        "Some look like they just fell from the trees, " +
        "splintered and twisted. They lay on the ground in " +
        "various stages of decomposition.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the " +
        "forest's floor.\n");
    add_item(({"needles", "pine needles"}),
        "Some fresh and dead pine needles litter the ground.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
        "dead tree"}),
        "Some fallen trees lay rotting under a blanket of fallen " +
        "pine needles and forest debris.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs are in various forms of decomposition. " +
        "Some are hollowed out and look to be homes for " +
        "woodland animals.\n");
    add_item(({"peaks", "mountain peaks"}),
        "They are hard to see with the trees moving about. " +
        "Nonetheless, some snow-capped tops can be seen as well " +
        "as some buried in the clouds.\n");
    add_item(({"mountains", "dragon tooth mountains", "mountain"}),
        "The Dragon Tooth Mountains rise up above the treeline " +
        "to the north. You note the tall spire peaks covered " +
        "in snow.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "Tall trees are everywhere, some have fallen over and block " +
        "paths in the forest while others grow tall and block the " +
        "sky above. Fallen branches, leaves, pine needles, and other " +
        "debris cover the forest's floor.\n");
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow under the trees, making travel " +
        "through the forest difficult and obscuring your way.\n");
    add_item(({"outcroppings", "rock outcroppings", 
            "rock outcropping", "outcropping"}),
        "These bits of rock protrude from the ground. They are " +
        "weather beaten with a few trees clinging to them, " +
        "trying to grow in the dense forest.\n");

    set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                  }),
                  ({"trees","bushes","undergrowth",
                    "plants","shrub","tree"}) , 3 );


    set_tell_time(300 + random(200));
    add_tell("You hear birds chirping off in the distance.\n");
    add_tell("The wind whips through the trees, creating " +
       "an erie howling sound.\n");
    add_tell("Something scurrys past in the brush next to you.\n");
    add_tell("The leaves from the trees sway in the icy cold " +
             "breeze.\n");
    add_tell("You catch something furry run from one bush " +
             "to another in the corner of your eye.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");

    add_cmd_item(({"air","forest","trees","plants"}),
                   "smell","@@smell_air");    

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
    reset_room();

}



// Smell the air, forest, plants
public string
smell_desc()
{
    return "The air smells of fresh evergreens.\n";
}

public int
do_smell(string str)
{
    write(smell_desc());
    return 1;
}



//Forest Objects
get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}



string short_desc()
{
    switch(short)
        {
                case 0:
                        return "In the central parts of the Silver Forest";
                        break;

                case 1:
                        return "In the northern parts of the Silver Forest";
                        break;

                case 2:
                        return "In the northwest parts of the Silver Forest";
                        break;

                case 3:
                        return "In the northeast parts of the Silver Forest";
                        break;

                case 4:
                        return "In the eastern parts of the Silver Forest";
                        break;

                case 5:
                        return "In the southeast parts of the Silver Forest";
                        break;

                case 6:
                        return "In the southern parts of the Silver Forest";
                        break;

                case 7:
                        return "In the southwest parts of the Silver Forest";
                        break;

                case 8:
                        return "In the western parts of the Silver Forest";
                        break;


                default:
                        return "In the Silver Forest";
                        break;
        }
}


string long_desc()
{
    switch(long)
        {
                case 0:
                        return "central part of the Silver Forest";
                        break;

                case 1:
                    return "northern part of the Silver Forest";
                    break;

                case 2:
                    return "northwest part of the Silver Forest";
                     break;

                case 3:
                    return "northeast part of the Silver Forest";
                        break;

                case 4:
                    return "eastern part of the Silver Forest";
                        break;

                case 5:
                    return "southeast part of the Silver Forest";
                    break;
             
                case 6:
                    return "southern part of the Silver Forest";
                    break;

                case 7:
                    return "southwest part of the Silver Forest";
                    break;

                case 8:
                    return "western part of the Silver Forest";
                    break;

                default:
                    return "in the Silver Forest";
                    break;
        }
}
