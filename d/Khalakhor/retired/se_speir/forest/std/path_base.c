/* File:          /d/Khalakhor/se_speir/forest/std/path_base.c
 * Creator:       Teth
 * Date:          April 13, 1998
 * Modifications:
 * Purpose:       This is the base room for the path rooms in the
 *                forest north of Port Macdunn. It is inherited
 *                by those rooms.
 * Related Files: /d/Khalakhor/se_speir/forest/
 * Comments:      
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

int continue_path();
int cross_forest();
int enter_bush();
int enter_forest();
int enter_plains();
int enter_stream();
int enter_village();
string *herbs = HERBMASTER->query_herbs(({TERRAIN_PATH,}));

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
    set_short("on a path that runs through Coille Cagairean");
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
        "mixed-woods","mixed-woods forest","trees"}),
        "The forest is composed of a mixture of trees, both hardwood " +
        "and softwood. The trees are also of various ages.\n");
    add_item(({"old trees","young trees","trees of various ages"}),
        "Indeed, some trees are old and some trees are young. " +
        "A lumberjack would identify it as a healthy forest.\n");
    add_item(({"path","surroundings"}),"@@long");
    add_item(({"timbers","cut timbers","flat cut timbers",
      "hewn timbers"}),"The lengths of wood which provide a stable " +
      "top stratum for the path are made of a moisture-resistant wood, " +
      "most likely oak. They are weathered grey, and covered with mud " +
      "and various debris. Still, they provide a stable path.\n");
    add_item(({"lengths","lengths of wood"}),"They are most likely oak, " +
      "and serve as a stable base for the path.\n");
    add_item("mud","The mud on the timbers is dry and caked.\n");
    /* allow people to get the mud? */
    add_item(({"debris","various debris"}),"Nothing of interest, " +
      "just what one would normally expect to be on the ground on a " +
      "path in a forest.\n");
    add_item(({"weeds","plants"}),"Green and leafy, the weeds struggle " +
      "to make an existence on the well-used path.\n");
    add_item(({"moist soil","soil"}),"A water-drenched loam, " +
      "it is impossible to reach through the thin cracks between the " +
      "hewn timbers.\n");
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
    add_item("tree","No tree stands out as worthy of further " +
      "investigation.\n");
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PATH);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}),({"path","here","weeds","plants",}),4);

    seteuid(getuid(this_object()));

    create_forest_room();
    reset_room();
}

public int
continue_path()
{
    write("You continue along the path, treading on the hewn timbers.\n");
    return 0;
}

public int
cross_forest()
{
    write("You begin to walk through a break in the forest toward " +
          "a stream.\n");
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
enter_forest()
{
    write("You step into the forest.\n");
    return 0;
}

public int
enter_plains()
{
    write("You travel toward the expansive plains.\n");
    return 0;
}

public int
enter_stream()
{
    write("You pass through the sliver of forest to the northwest " +
          "and find yourself wading into a stream.\n");
    return 0;
}

public int
enter_village()
{
    write("You approach the village, but find it is not yet open " +
          "to visitors.\n");
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
    if (this_player()->query_skill(SS_AWARENESS) > 39)
    {
    return "This is a path running through the mixed woods forest " +
    "known as Coille Cagairean. Flat cut timbers which are " +
    "laid side to side serve as a base for the path, instead of the " +
    "bare ground. Weeds poke through the cracks between the hewn " +
    "timbers. Between the cracks, a moist soil can be seen, indicating " +
    "water nearby. The sky above is a crystal-clear blue. ";
    }
    return "This is a path running through the mixed woods forest " +
    "known as Coille Cagairean. Flat cut timbers which are " +
    "laid side to side serve as a base for the path, instead of the " +
    "bare ground. Weeds poke through the cracks between the hewn " +
    "timbers. Between the cracks, a moist soil can be seen. The sky " +
    "above is a crystal-clear blue. ";
}

