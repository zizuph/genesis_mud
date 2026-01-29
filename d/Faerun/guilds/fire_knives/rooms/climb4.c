/* /d/Faerun/guilds/fire_knives/rooms/climb4.c
 *
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
    int req_fatigue;
    
    req_fatigue = 110;
    
    if (str == "up")
    {
        if (this_player()->query_fatigue() < req_fatigue)
        {
            write("\nYou suddenly fall off the cliffside!\n\nYou plunge "
            +"into the ground with alarming speed!\n\n");

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " suddenly fall off the cliffside and plunges down!\n", 
            this_player());
            
            this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
            + "rooms/mountain_ft", 1);
            
            tell_room(FIREKNIVES_GUILD_DIR 
            + "rooms/mountain_ft", QCTNAME(this_player())
            + " crashes in from above, plunging into the ground with an "
            +"alarming speed!\n", this_player()); 

            this_player()->heal_hp(-4000);
            this_player()->set_fatigue(this_player()->query_fatigue() - 110);

            if (this_player()->query_hp() <= 0)
            {
                this_player()->do_die(this_object());
            }
            
            return 1; 
        }
        
        write("\nYou continue to climb the cliffside upwards.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " continues to climb upwards.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        + "rooms/climb5", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb5", QCTNAME(this_player())
        + " arrives climbing up from below.\n", this_player());
        
        this_player()->set_fatigue(this_player()->query_fatigue() - 40);
        
        return 1;
    }
    
    if (str == "down")
    {
        if (this_player()->query_fatigue() < req_fatigue)
        {
            write("\nYou suddenly fall off the cliffside!\n\nYou plunge "
            +"into the ground with alarming speed!\n\n");

            tell_room(environment(this_object()), QCTNAME(this_player())
            +" suddenly fall off the cliffside and plunges down!\n", 
            this_player());
            
            this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
            +"rooms/mountain_ft", 1);
            
            tell_room(FIREKNIVES_GUILD_DIR 
            +"rooms/mountain_ft", QCTNAME(this_player())
            +" crashes in from above, plunging into the ground with an "
            +"alarming speed!\n", this_player()); 

            this_player()->heal_hp(-4000);
            this_player()->set_fatigue(this_player()->query_fatigue() - 110);

            if (this_player()->query_hp() <= 0)
            {
                this_player()->do_die(this_player());
            }
            
            return 1; 
        }
        
        write("\nYou continue to climb the cliffside downwards.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        +" continues to climb downwards.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        +"rooms/climb3", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb3", QCTNAME(this_player())
        +" arrives climbing down from above.\n", this_player());
        
        this_player()->set_fatigue(this_player()->query_fatigue() - 40);
        
        return 1;
    }
    
    write("Climb up or down, perhaps?\n");
    
    return 1;
}


void
create_fireknives_outdoor()
{
    set_short("Below the thick blanket of fog");
    
    set_extraline("Winds buffeting your body attempt to sweep you off the "
    +"face of the mountain as you try to hold on "
    +"with all your might. The stones "
    +"that jut outward from the mountain feel softer "
    +"at this height, but you are "
    +"unsure if it is your hands going numb or "
    +"the stone being smoothened out "
    +"by the dry winds. Downwards you see nothing "
    +"but a thin whirlwind of snow "
    +"revolving around the mountain, while directly "
    +"upwards begins a cloud of "
    +"fog which obfuscates anything within it past its outline.");

    add_item(({"snow", "snowdrift","snowflakes", "flakes",
    "flake","layer","layers",
    "patch","patches"}),
    "Layers of snow cover everything around you, "
    +"disguising strong stones from simple "
    +"patches of snow. It drifts in the air around "
    +"you in a whirlwind and falls down "
    +"away from you just as a new wave hits you from the west.\n");

    add_item(({"ground","floor"}),
    "The ground is not visible from here. \n");

    add_item(({"base"}), 
    "The base of the mountain is no longer visible from "
    +"here, and you can only see "
    +"a thin whirlind of snow revolving around the mountain. \n");

    add_item(({"mountain","mountains"}),
    "The mountain is wide and high, reaching an apparent "
    +"end at the dense fog right "
    +"above you.\n");

    add_item(({"fog","blanket", "blanket of fog"}),
    "The fog obscures the view of the mountain and "
    +"anything around it directly up "
    +"from your current position, rendering details "
    +"imperceptible from here.\n");

    add_item(({"sky"}),
    "The view of the sky is lost here due to thefog "
    +"between it, but you remember "
    +"its colors vividly as if in a dream. \n");
    
    add_item(({"winds","wind"}),
    "The winds buffet mightily against you as try "
    +"and hold on to the stones jutting "
    +"outwards of the mountain, throwing snow "
    +"all throughout the air around you and "
    +"forming a whirlwind. It takes all your strength "
    +"to hold on to your current "
    +"position, finding brief moments of respite "
    +"between each wind-wave.\n");

    add_item(({"stone","stones","jagged stones","jagged stone"}),
    "Jagged stones protrude slightly from the mountain, "
    +"sheltering patches of "
    +"dryness amidst the snow-covered "
    +"prominence before you. They look as if they "
    +"would pierce through the layers of snow. You "
    +"are hanging on to them at "
    +"the moment, and looking down you find "
    +"similar ones within reach, while upwards "
    +"only the shadow of something similar can be seen.\n");

    add_item(({"whirlwind"}),
    "The western winds buffet mightly against the "
    +"mountain, reverberating around "
    +"the area and boncing off with revolved "
    +"snow which twirl around you before "
    +"they fall downwards, only to be once again "
    +"swept away by the next wind-wave.\n");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();

    add_action(do_climb, "climb");
}
