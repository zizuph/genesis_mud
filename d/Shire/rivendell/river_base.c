/*
 * Base file for river Bruinen as it floods
 * By Finwe
 * July 1998
 */
 
#include "/d/Shire/sys/defs.h"
inherit AREA_ROOM;
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_river_room() {}
 
 
public void
create_area_room()
{
    set_areaname("the river");
    add_item(({"river", "bruinen", "river bruinen", "water"}),
        "The river crashes about you, pulling you under and " +
        "blinding you as you get swept away. Debris washes past " + 
        "you, some hitting you and other stuff dangerously " +
        "missing you.\n");
    add_item("debris",
        "You see rotting logs, downed trees, large branches, " +
        "large boulders, and silt spilling past you in the " +
        "river.\n");
    add_item(({"rotting logs", "logs"}),
        "The logs are various sizes and condition. Some are " +
        "falling apart in the water while others look like " +
        "they were recently felled.\n");
    add_item(({"downed trees", "trees", "trunks", "tree trunks"}),
        "Many of the trees look like they were ripped up from " +
        "the ground. Their roots are exposed and many of their " +
        "branches are broken from the wrath of the the river.\n");
    add_item(({"large branches", "broken branches"}),
        "You see broken branches of all sizes swirling about " +
        "in the river. Some go flying past you while others " +
        "swirl about in the water. Their ends are shattered " +
        "from being ripped from trees by sheer force of the " +
        "river.\n");
    add_item(({"large rocks", "large boulders", "boulders"}),
        "Many large boulders are being hurled about the river. " +
        "They are creating white water and are making the river " +
        "treacherous. Some have been ripped up from the riverbed " +
        "and are being tossed about by the force of the water.\n");
    add_item(({"silt", "dirt"}),
        "The silt is a reddish color. It floats about making it " +
        "difficult to see.\n");

    create_river_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}
 
string
river_desc()
{
    switch(random(4))
    {
        case 0:
            return "You feel the force of the river as it " +
            "throws you about. It tosses you about dangerously, " +
            "almost as if it is trying to drown you. Large " +
            "boulders, tree trunks, and other debris hurl " +
            "past you. ";
            break;
        case 1:
            return "The river tosses you about with all its " +
            "might. Silt and dirt blind you while trees and " +
            "boulders are thrown past you. The force of " +
            "the river pulls you under, almost drowning you, as " +
            "you breathe in water and dirt.";
            break;
        case 2:
            return "You get pulled under. As you struggle " +
            "to the surface, the silt in the water makes it " +
            "difficult to see what is in the water. You are tossed " +
            "out of the water and crash back into it, narrowly " +
            "missing a jutting rock. ";
            break;
        case 3:
            return "The river furiously churns about you, " +
            "dredging up rocks, boulders, silt, and other debris " +
            "from its bed. The force of the river is unreal " +
            "as it violently throws you about. Trees and branches " +
            "hurt you as you get slammed into boulders. ";
            break;
 
        default:
            return "This river is deadly in its fury. You " +
            "are tossed about by it and get dragged under. " +
            "Boulders slam into you, breaking bones while branches " +
            "caught in the river hurt you. ";
            break;
     }
}
