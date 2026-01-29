/* File:          /d/Khalakhor/se_speir/forest/std/forest_base.c
 * Creator:       Teth
 * Date:          February 12, 1998
 * Modifications:
 * Purpose:       This is the base room for the non-special forest
 *                rooms in the forest north of Port Macdunn. It is
 *                inherited by those rooms.
 * Related Files: /d/Khalakhor/se_speir/forest/
 * Comments:      set_logged() should be set from 0 to 3.
 * TODO:          Add doable things.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <macros.h> 
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
#include "../forest.h"

inherit HERBSEARCH;

void query_logged();
void set_up_forest();
int block_forest();
int block_river();
int cross_path();
int enter_bush();
int enter_path();
int enter_riverbank();
int enter_stream();
int enter_village();
int set_logged(int i);
int Logged;
string *herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD,}));
string str1, str2, str3, str4, str5, str6, str7, str8, str9;

public void
reset_forest_room()
{
}

public void
create_forest_room()
{
}

public void
reset_room()
{
    set_searched(0);
    reset_forest_room();
}

public void
create_khalakhor_room()
{
    set_short("in the mixed woods forest known as Coille Cagairean");
    set_long("This is the base room.\n");

    add_item(({"sky","crystal-clear blue sky","blue sky",
        "crystal-clear sky"}),"The sky above is crystal-clear blue, " +
      "with nary a cloud in the sky.\n");
    add_item("cloud","There are no clouds in the sky.\n");
    add_item(({"Khalakhor","khalakhor"}),"It is the continent you " +
      "stand on.\n");
    add_item(({"speir","southeast speir"}),"It is the particular region " +
      "of Khalakhor in which you are currently located.\n");
    add_item(({"Whispering Forest","whispering forest","coille",
        "Coille Cagairean","coille cagairean"}),"@@know_forest");
    add_item(({"forest","mixed woods","mixed woods forest",
        "mixed-woods","mixed-woods forest","surroundings"}),
      "@@long");
    add_item(({"other species","other trees"}),"The other trees " +
      "in this area are a mixture of hardwood and coniferous " +
      "types.\n");
    add_item(({"hardwood trees","hardwood types", "hardwoods"}),
      "The hardwood trees found in this forest include oak, yew, " +
      "willow, birch, and maple. Some types are not present in this " +
      "local area, though.\n");
    add_item(({"coniferous trees","coniferous types","conifers"}),
      "The coniferous trees found in this forest include pine, " +
      "spruce, fir, and larch. Some types are not present in this " +
      "local area, though.\n");
    add_item("leaves","There are leaves all over.\n");
    add_item("bark","Every tree is covered with bark.\n");
    add_item("branches","Each tree has some branches, but one is " +
      "much like the other.\n");
    add_item("broken branches","Broken branches exist here and there, " +
      "but all they seem to do is produce twigs.\n");
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_MIXEDWOOD);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}),({"forest","here","ground","woods",
        "underbrush"}),4);

    seteuid(getuid(this_object()));

    create_forest_room();
    reset_room();
}

public int
cross_path()
{
    write("You cross the path, entering another section of forest.\n");
    return 0;
}

public int
enter_bush()
{
    write("You start to walk down a slope, in the direction of " +
          "the edge forest which provides a transition between " +
          "the forest and the plains.\n");
    return 0;
}

public int
enter_path()
{
    write("You begin to walk out of the forest onto a path.\n");
    return 0;
}

public int
enter_riverbank()
{
    write("You start to walk down a gradual slope, " +
          "headed toward the lower land of the riverbank forest " +
          "which lines the river.\n");
    return 0;
}

public int
enter_stream()
{
    write("You begin to wade into the stream from the forest.\n");
    return 0;
}

public int
enter_village()
{
    write("You approach the village, but find that it does not yet " +
          "accept visitors.\n");
    return 1;
}

public int
block_forest()
{
    write("The forest beyond remains cloaked in mystery. Passage " +
          "is not allowed until efforts are made to reveal its " +
          "secrets.\n");
    return 1;
}

public int
block_river()
{
    write("The riverbank below cannot be reached from this route. " +
          "A steep slope prevents movement in this direction.\n");
    return 1;
}

public int
cross_stream()
{
    write("You attempt to cross the stream, but find that the forest " +
          "beyond remains cloaked in mystery. Passage is prevented " +
          "in that direction.\n");
    return 1;
}

public string
know_forest()
{
    string lore;
    int loreskill = this_player()->query_skill(SS_KHALAKHOR_LORE);

    switch(loreskill)
    {
    case 0..16:
        lore = "You know too little lore of Khalakhor, and therefore " +
        "can not recall anything of Coille Cagairean.\n";
        break;

    case 17..42:
        lore = "Drawing upon your lore of Khalakhor, you recall that " +
        "Coille Cagairean means Whispering Forest. You are unable " +
        "to remember any legends, however.\n";
        break;

    case 43..69:
        lore = "With your knowledge of the lore of Khalakhor, you recall " +
        "that Coille Cagairean translates to Whispering Forest. " +
        "You are able to recall tales of a band of warriors who " +
        "are entombed here.\n";
        break;

    default:
        lore = "Drawing upon your lore of Khalakhor, you recall that " +
        "Coille Cagairean translates to Whispering Forest. " +
        "You recall tales of an entombed band of warriors " +
        "buried in the forest, protecting their graves and a " +
        "valuable treasure.\n";
        break;
    }
    return lore;
}

public string
my_long()
{
    return "This is the mixed woods forest known as Coille " +
    "Cagairean. Here, the forest is " + str1 + ", perhaps " +
    "because it is " + str2 + " forest, and has " +
    str3 + ". The trees are mainly a mix of " + str4 + " and " + 
    str5 + ", although other species are present. This causes " +
    "the area to be " + str6 + ". The sky above is a " +
    "crystal-clear blue, and the ground below is " + str7 +
    ". The underbrush is " + str8 + ", a result of " +
    "the " + str9 + ". ";
}

public int
query_logged()
{
    return Logged;
}

public void
set_logged(int i)
{
    Logged = i;
}

public void
set_up_forest()
{
    switch(Logged)
    {
    case 1:
        str1 = "dense";
        str2 = "wild";
        str3 = "been lightly logged";
        str4 = "ancient oak";
        str5 = "pine";
        str6 = "shaded";
        str7 = "covered with duff";
        str8 = "sparse";
        str9 = "light logging";
        add_item(({"dense forest","wild forest","lightly logged forest",
            "logged forest","local forest"}),"The forest surrounding " +
          "you is dense, and has not seen much logging, so it is in " +
          "a near-natural state.\n");
        add_item("logging","The logging in this area of the forest " +
          "is light, leaving much more left to be cut. There are a " +
          "few stumps about.\n");
        add_item("trees","The main trees here are ancient oak trees " +
          "and pine trees.\n");
        add_item(({"ancient oak trees","oak trees","oaks","ancient oaks"}),
          "The ancient oak trees stand tall and gnarled, and their " +
          "leafy crowns create much shade.\n");
        add_item(({"leafy crowns","crowns","crowns of oak trees",
            "leafy crowns of oak trees"}),"The leafy crowns of the oak " +
          "trees create much shade on the forest floor.\n");
        add_item(({"floor","forest floor","ground"}),"The shaded forest " +
          "floor is covered with duff, which is leaf litter.\n");
        add_item(({"pine trees","pines"}),"Straight and true, the pine " +
          "trees are the main coniferous species in the area. The " +
          "trees are heavily needled, a sign of health.\n");
        add_item(({"pine needles","needles"}),"The needles hang long " +
          "and drooping from the pine trees.\n");
        add_item("shade","The shade makes this area cool, and an easy " +
          "place to camouflage one's self.\n");
        add_item(({"duff","litter","leaf litter"}),"The duff is a " +
          "mixture of old leaves, dried needles, and small twigs.\n");
        add_item("old leaves","The old leaves are dry, crisp, and " +
          "brittle.\n");
        add_item("dried needles","The dried needles are brown in " +
          "colour, and have pointed tips.\n");
        add_item(({"small twigs","twigs"}),"The twigs are small pieces " +
          "of broken branches, of little use.\n");
        add_item(({"underbrush","brush"}),"The underbrush is light, " +
          "allowing easy passage.\n");
        add_item("stumps","The stumps are wide in diameter, and old. " +
          "They are from larger trees which previously grew here.\n");
        add_prop(ROOM_I_HIDE, 5 + (random(10)));
        break;

    case 2:
        str1 = "somewhat dense";
        str2 = "relatively wild";
        str3 = "been logged";
        str4 = "oak";
        str5 = "old spruce";
        str6 = "somewhat shaded";
        str7 = "splotchily covered with duff";
        str8 = "relatively dense";
        str9 = "logging";
        add_item(({"somewhat dense forest","relatively wild forest",
            "dense forest","wild forest","logged forest","local forest"}),
          "The forest surrounding you is somewhat dense, and has seen " +
          "some logging, but it is still relatively wild.\n");
        add_item("logging","Logging has occurred here to some extent, " +
          "although there is still some left to cut. There are quite " +
          "a few stumps remaining.\n");
        add_item("trees","The main trees here are oak trees " +
          "and old spruce trees.\n");
        add_item(({"oak trees","oaks"}),"The oak trees stand tall and " +
          "somewhat gnarled, and their thin leafy crowns create some " +
          "shade.\n");
        add_item(({"leafy crowns","crowns","crowns of oak trees",
            "leafy crowns of oak trees", "thin crowns", "thin leafy crowns"}),
          "The thin leafy crowns of the oak trees create some shade on " +
          "the forest floor.\n");
        add_item(({"floor","forest floor","ground"}),"The lightly shaded " +
          "forest floor is splotchily covered with duff.\n");
        add_item(({"spruce trees","spruces","old spruce trees"}),
          "The spruce trees mostly grow straight, although the occasional " +
          "one angles or is bent. The spruce trees are the main " +
          "coniferous species in the area. The trees are heavily needled, " +
          "a sign of health.\n");
        add_item(({"spruce needles","needles"}),"The needles stick out " +
          "short and stiff from the spruce trees.\n");
        add_item("shade","The shade makes this area bearable, and a " +
          "relatively easy place to hide.\n");
        add_item(({"duff","litter","leaf litter"}),"The duff is a " +
          "mixture of old leaves, dried needles, and small twigs.\n");
        add_item("old leaves","The old leaves are dry, crisp, and " +
          "brittle.\n");
        add_item("dried needles","The dried needles are brown in " +
          "colour, and have pointed tips.\n");
        add_item(({"small twigs","twigs"}),"The twigs are small pieces " +
          "of broken branches, of little use.\n");
        add_item(({"underbrush","brush"}),"The underbrush is quite " +
          "dense, making passage somewhat difficult.\n");
        add_item("stumps","The stumps are wide in diameter, and old. " +
          "They are from larger trees which previously grew here.\n");
        add_prop(ROOM_I_HIDE, 10 + (random(10)));
        break;

    case 3:
        str1 = "sparse";
        str2 = "tame";
        str3 = "been heavily logged";
        str4 = "willow";
        str5 = "young spruce";
        str6 = "lightly shaded";
        str7 = "quite bare";
        str8 = "dense";
        str9 = "heavy logging";
        add_item(({"sparse forest","tame forest","heavily logged forest",
            "logged forest","local forest"}),"The forest surrounding " +
          "you is sparse, and has been heavily logged, so it is in " +
          "a rather tame state.\n");
        add_item("logging","The logging in this area of the forest " +
          "is heavy, leaving little left to be cut. There are " +
          "many stumps about.\n");
        add_item("trees","The dominating trees here are willow trees " +
          "and young spruce trees.\n");
        add_item(({"willow trees","willows"}),"The willow trees are " +
          "short, twisted, and gnarled. Their thin leaves give little " +
          "shade.\n");
        add_item(({"floor","forest floor","ground"}),"The lightly shaded " +
          "forest floor has little duff, and is mostly bare.\n");
        add_item(({"spruce trees","spruces","young spruce trees",
            "young spruces"}),"The young spruce trees are short, but " +
          "healthy. They are the main coniferous species in the area. " +
          "The trees are heavily needled, a sign of health.\n");
        add_item(({"spruce needles","needles"}),"The needles stick out " +
          "straight from the branches, yet are still somewhat pliable.\n");
        add_item("shade","Little shade can be found here, but what exists, " +
          "cools this area. It does not provide much in the way of cover.\n");
        add_item(({"duff","litter","leaf litter"}),"The small amount of " +
          "duff is a mixture of old leaves, dried needles, and small " +
          "twigs.\n");
        add_item("old leaves","The old leaves are dry, crisp, and " +
          "brittle.\n");
        add_item("dried needles","The dried needles are brown in " +
          "colour, and have pointed tips.\n");
        add_item(({"small twigs","twigs"}),"The twigs are small pieces " +
          "of broken branches, of little use.\n");
        add_item("bare ground","The bare ground reveals a black soil.\n");
        add_item(({"soil","black soil"}),"The black soil contains " +
          "some organic material, but it is not very rich soil.\n");
        add_item(({"material","organic material"}),"The organic " +
          "material is mostly decayed remnants of plant matter.\n");
        add_item(({"underbrush","brush"}),"The underbrush is dense, " +
          "making passage extremely difficult.\n");
        add_item("stumps","The stumps are wide in diameter, and old. " +
          "They are from larger trees which previously grew here.\n");
        add_prop(ROOM_I_HIDE, 15 + (random(10)));
        break;

    default:
        str1 = "extremely dense";
        str2 = "virgin";
        str3 = "never been logged";
        str4 = "yew";
        str5 = "fir";
        str6 = "darkly shaded";
        str7 = "densely covered with duff";
        str8 = "very sparse";
        str9 = "old-growth forest";
        add_item(({"virgin forest","pure forest","local forest"}),"The " +
          "forest surrounding you is extremely dense, with wide and tall " +
          "trees, as the forest is in a natural state.\n");
        add_item("trees","The main trees here are yew trees and fir " +
          "trees.\n");
        add_item(({"yew trees","yews"}),"The yew trees stand tall and " +
          "thick, their trunks reaching high into the air before " +
          "branching out.\n");
        add_item("trunks","The trunks of the trees are all that you can " +
          "see at eye-level.\n");
        add_item(({"floor","forest floor","ground"}),"The darkly shaded " +
          "forest floor is densely covered with duff, which only slowly " +
          "decays.\n");
        add_item(({"fir trees","firs"}),"The fir trees are the main " +
          "coniferous species in the area. High above, the trees are " +
          "generously needled, a sign of lack of disturbance.\n");
        add_item(({"fir needles","needles"}),"The needles are too " +
          "high above you to see clearly.\n");
        add_item("shade","The shade makes this area cold, and an extremely " +
          "easy place to hide one's self.\n");
        add_item(({"duff","litter","leaf litter"}),"The duff is a " +
          "mixture of old leaves, dried needles, and small twigs.\n");
        add_item("old leaves","The old leaves are dry, crisp, and " +
          "brittle.\n");
        add_item("dried needles","The dried needles are brown in " +
          "colour, and have pointed tips.\n");
        add_item(({"small twigs","twigs"}),"The twigs are small pieces " +
          "of broken branches, of little use.\n");
        add_item(({"underbrush","brush"}),"The underbrush is very sparse, " +
          "most young trees and shrubs dying from lack of light.\n");
        add_item("stumps","There are no stumps here.\n");
        add_prop(ROOM_I_HIDE, 1 + (random(10)));
        break;
    }
}


