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
inherit "/d/Terel/mountains/elderwood/include/cold_fatigue.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define DEFAULT    MOUNTAIN_DIR + "elderwood/forest/"
#define MONSTER_DIR      "/d/Terel/mountains/elderwood/monster/"


string *birds   = ({"bird","falcon"}),
       *small   = ({"rodent","squirrel","rabbit","pfox","hare","ferret"}),
       *large   = ({"deer","caribou","moose","mbear"});

object pebble;
int long, short, exits;

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
    set_long("The snow covered forest is populated by several " +
       "varieties of trees. Rays of sunlight shine down through " +
       "the canopy of tree limbs overhead casting dabbled shadows " +
       "upon the forest floor. " +
       "@@long_desc@@");


    add_prop("_room_m_da_dragonsteed_no_land","The forest " +
       "is to thick for your dragon to land here.");

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
    add_item(({"forest","elderwood"}),
        "The forest is large and stretches in all directions. " +
        "Tall trees are everywhere, some have fallen over and block " +
        "paths in the forest while others grow tall and block the " +
        "sky above. Fallen branches, leaves, pine needles, and other " +
        "debris cover the forest's floor.\n");
    add_item(({"ravine"}),"The ravine is covered in undergrowth.\n");
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow under the trees, making travel " +
        "through the forest difficult and obscuring your way.\n");
    add_item(({"outcroppings", "rock outcroppings", 
            "rock outcropping", "outcropping"}),
        "These bits of rock protrude from the ground. They are " +
        "weather beaten with a few trees clinging to them, " +
        "trying to grow in the dense forest.\n");
    add_item(({"rays","rays of light","light","ray"}),
               "Rays of light rain down from the canopy of tree " +
               "limbs above.\n");

    set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                  }),
                  ({"trees","bushes","undergrowth",
                    "plants","shrub","tree","shrubs"}) , 3 );


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
  
    add_cmd_item(({"tree"}),({"climb"}),"The tree limbs are too " +
                   "high for you to grab making climbing them " +
                   "impossible.\n");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
    reset_room();

}


int
exits()
{
   if ((TP->query_skill(SS_LOC_SENSE) > 60))
   {
       return 0;
   }
       return 1;
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
    write("You sift through the snow finding a pebble, then pick it up.\n");
       say(QCTNAME(TP) + " reaches into the snow and picks up a pebble.\n");
    return 1;
}


// Clone forest critters.
public string*     
query_moving_object_list()
{
    seteuid(getuid(this_object()));     
  
       switch(random(15))
       {
         case 0 :  
              return ({MONSTER_DIR + birds[random(sizeof(birds))]});
              break;
         case 1 :  
              return ({MONSTER_DIR + small[random(sizeof(small))]});
              break;
         case 2 :  
              return ({MONSTER_DIR + large[random(sizeof(large))]});
              break;
         case 3 :
              return 0;
              break;
       }
}


string short_desc()
{
    switch(short)
        {
                case "middle":
                        return "Deep within the snow-covered forest of Elderwood";
                        break;

                case "east":
                        return "Eastern section of the Elderwood forest";
                        break;

                case "south":
                        return "Southern reaches of the Elderwood forest";
                        break;

                case "north":
                        return "Northern reaches of the Elderwood forest";
                        break;

                case "west":
                        return "Western area of the Elderwood forest";
                        break;

                default:
                        return "Somewhere within the Elderwood forest";
                        break;
        }
}


string long_desc()
{
    switch(long)
        {
                case 0:
                     return "Snow crunches beneath your feet as you " +
                     "continue onwards through the dense " +
                     "forest. The forest floor climbs steadily " +
                     "in the northern direction.\n";
                     break;

                case 1:
                    return "You make your way through the dense undergrowth " +
                    "covering the forest floor. The tall evergreens loom above you " +
                    "like giant wooden sentinels.\n ";
                    break;

                case 2:
                    return "You decend into a small ravine covered in dense undergrowth. " +
                    "The ravine appears to have been created over time by water erosion. " +
                    "The undergrowth within the ravine looks like an excellent refuge " +
                    "for small animals.\n";
                     break;

                case 3:
                    return "The forest continues to climb in an northerly  " +
                    "direction. The various species of plantlife impede " +
                    "you, as you continue onward.\n";
                        break;

                case 4:
                    return "The forest around you seems harsh and unyielding. " +
                    "The ground beneath you is frozen covered in patches of snow. Large " +
                    "drifts of snow have collected along the tree basin. You begin " +
                    "to shiver at the thought of remaining here indefinitely.\n";
                        break;

             case 5:
                    return "The dense undergrowth claws at your clothing as " +
                    "you continue your trek onwards through the drifts of " +
                    "snow covering the frozen ground.\n";
                    break;
             
             case 6:
                    return "The bitter cold and the isolation of the forest " +
                    "gives you a sense of loneliness.\n";
                    break;

             case 7:
                    return "The forest floor levels off into a field of " +
                    "frozen yellow grass.\n";
                    break;

             case 8: 
                    return "The trees are spaced wider apart here. The ground " +
                    "is layered in soft snow. Drifts of snow built up over time " +
                    "can be seen along the tree basin and scrub brush.\n";
                    break;

             case 9: 
                    return "The trees are spaced apart more here. The ground " +
                    "is layered in snow. Drifts of snow built up over time " +
                    "can be seen along the tree basin.\n";
                    break;
 
                default:
                    return "The snow covered forest is populated by several " +
                    "varieties of trees. Rays of sunlight shine down through " +
                    "the canopy of tree limbs overhead casting dabbled shadows " +
                    "upon the forest floor.\n";
                    break;
        }
}
