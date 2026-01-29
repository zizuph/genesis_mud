/* /d/Faerun/guilds/fire_knives/rooms/mountain_ft.c
 *
 * Base of the mountain
 *
 * Nerull 2019
 *
 */
 
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_OUTDOOR;


int
do_climb(string str)
{
    if (str == "up")
    {   
        if (this_player()->query_average() < REQ_AVG)
        {
            write("You doubt you should try this climb as you would not "
            +"even survive the easiest fall! Perhaps you should grow abit more.\n");
            
            return 1;        
        }

        write("\nYou climb the cliffside upwards.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        +" climbs upwards along the cliffside.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        +"rooms/climb1", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        +"rooms/climb1", QCTNAME(this_player())
        +" arrives climbing up from below.\n", this_player());
        
        CLIMB_LOG("climb_log",
        "The player "+this_player()->query_name()
        +" started 'The Climb'.\n");
        
        return 1;
    }
    
    write("Climb where?\n");
    
    return 1;
}


void
create_fireknives_outdoor()
{
    set_short("At the feet of an enormous mountain");

    set_extraline("Ankle deep in snow you stand at "
    +"the base of an enormous mountain "
    +"reaching up to the clouds that fog the "
    +"sky. Flakes and layers of snow blow "
    +"off the mountain as the furious western "
    +"winds meet it full force, covering "
    +"the recently obvious tracks which revealed "
    +"a path to the west back to the "
    +"trail. Here and there from the base "
    +"upwards jut out jagged stones that seem "
    +"to pierce through the layers of snowdrift.");

    add_item(({"snow", "snowdrift","snowflakes", 
    "flakes","flake","layer","layers",
    "patch","patches"}),
    "Layers of snow cover the ground upon which you "
    +"stand, rising up to your ankles "
    +"and maintaining a steady height between the "
    +"new that accumulates and the old "
    +"which is blown away by the winds. Everything "
    +"around you is covered in it, "
    +"from the bottom of the mountain to its "
    +"highest point, the only exception patches "
    +"of stone underneath the ones jutting out from the base.\n");

    add_item(({"ground","floor"}),
    "Layers of snow cover the ground underneath you, "
    +"crunching under your weight "
    +"with every step you take and leaving a "
    +"temporary footprint that swiftly "
    +"disappears by will of the winds.\n");
    
    add_item(({"base","mountain","mountains"}),
    "The base of the mountain is wide and "
    +"extends towards the east and south of you, "
    +"leaving a trail open to the west back "
    +"whence you came from. From this perspective "
    +"it seems almost vertical even if there is "
    +"a slight incline towards the top. The "
    +"mountain extends up to high heavens, its "
    +"peaks lost between clouds and fog. You think "
    +"it's possible to climb up here, even if it's "
    +"steep and very dangerous.\n");

    add_item(({"fog"}),
    "The fog obscures the view of the mountain "
    +"past some meters upwards, about twice "
    +"your height, rendering details imperceptible "
    +"from here.\n");

    add_item(({"sky"}),
    "The sky is seen through the thick veil of "
    +"fog that obfuscates it, its colors "
    +"dimming through it and appearing softer "
    +"than they should. It seems both far "
    +"and near at the same time, as if it would "
    +"call you upwards. \n");

    add_item(({"winds","wind"}),
    "The winds buffet mightily against the mountain, "
    +"throwing snow all throughout "
    +"the area and making your stance all the harder "
    +"to maintain. The otherwise "
    +"tolerable cold becomes bitter and stern as it "
    +"is slammed into everything with "
    +"full force.\n");

    add_item(({"track","tracks","prints","footprints","footprint","print"}),
    "The tracks made by your feet are soon "
    +"thereafter covered by the winds "
    +"which buffet the mountain, throwing "
    +"fresh layers of snow upon everything.\n");

    add_item(({"path"}),
    "The path whence you came from leads back "
    +"to the west to a trail in the snow.\n");

    add_item(({"stone","stones","jagged stones","jagged stone"}),
    "Jagged stones protrude slightly from the "
    +"mountain, sheltering patches of "
    +"dryness amidst the snow-covered prominence "
    +"before you. They look as if they "
    +"would pierce through the layers of snow.");
    
    reset_faerun_room();

    add_exit("/d/Faerun/highroad/rooms/htr10", "west",0,0,1);
}


void
init()
{
    ::init();

    add_action(do_climb, "climb");
}


void
reset_faerun_room()
{
}
