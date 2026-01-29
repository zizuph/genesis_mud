/* /d/Faerun/guilds/fire_knives/rooms/climb2.c
 *
 * Second room climbing up to the ledge
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
    int climbskill, climbreduce;
    
    climbskill = this_player()->query_skill(SS_CLIMB);
    climbreduce = climbskill / 2;
    
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

            this_player()->heal_hp(-1000);
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
        + "rooms/climb3", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb3", QCTNAME(this_player())
        + " arrives climbing up from below.\n", this_player());
        
        this_player()->set_fatigue((this_player()->query_fatigue() - 50) + climbreduce);
        
        return 1;
    }
    
    if (str == "down")
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

            this_player()->heal_hp(-1000);
            this_player()->set_fatigue(this_player()->query_fatigue() - 110);

            if (this_player()->query_hp() <= 0)
            {
                this_player()->do_die(this_player());
            }
            
            return 1; 
        }
                
        write("\nYou continue to climb the cliffside downwards.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " continues to climb downwards.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        + "rooms/climb1", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb1", QCTNAME(this_player())
        + " arrives climbing down from above.\n", this_player());
        
       this_player()->set_fatigue((this_player()->query_fatigue() - 50) + climbreduce);
        
        return 1;
    }
    
    write("Climb up or down, perhaps?\n");
    
    return 1;
}


void
create_fireknives_outdoor()
{
    set_short("Clinging to protruding rocks on a mountain");
    
    set_extraline("Winds buffeting your body attempt to sweep you off the "
    +"face of the mountain as the snow that drifts in a whirlwind around "
    +"you. You are tightly holding onto the stones that protrude from the "
    +"mountain, using all your strength to maintain your position. Downwards "
    +"you can still see the ground, while upwards the only thing visible are "
    +"more of the jagged stones from which you are hanging. Beneath you, the "
    +"once welcoming ground seems far and barely visible now, lost underneath "
    +"waves of snow twirling in a circle, while above you is nothing but more "
    +"of the same stones you are now holding onto and an ever-nearing thick "
    +"blanket of fog.");

    add_item(({"snow", "snowdrift","snowflakes", 
    "flakes","flake","layer","layers",
    "patch","patches"}),
    "Layers of snow cover everything around you, "
    +"disguising strong stones from simple "
    +"patches of snow. It drifts in the air around "
    +"you in a whirlwind and falls down "
    +"away from you just as a new wave hits you from the west.\n");

    add_item(({"ground","floor"}),
    "The ground is becoming barely visible from this "
    +"point underneath waves of snow "
    +"twirling in a circle.\n");

    add_item(({"base"}), 
    "The base of the mountain is no longer visible from here.\n");

    add_item(({"mountain","mountains"}),
    "The mountain is wide and high, extending upwards as "
    +"far as the eye can see "
    +"only to lose itself into a dense fog. From your "
    +"current perspective it seems "
    +"as if it would go on forever, while downwards "
    +"he ground is becoming barely "
    +"visible from this point underneath waves of snow "
    +"twirling in a circle.\n");

    add_item(({"fog","blanket", "blanket of fog"}),
    "The fog obscures the view of the mountain past "
    +"some meters upwards, about twice "
    +"your height, rendering details imperceptible from here.\n");

    add_item(({"sky"}),
    "The sky is seen through the thick veil of "
    +"fog that obfuscates it, its colors "
    +"dimming through it and appearing softer "
    +"than they should. It seems both far "
    +"and near at the same time, as if it would call you upwards. \n");
    
    add_item(({"winds","wind"}),
    "The winds buffet mightily against you as try "
    +"and hold on to the stones jutting "
    +"outwards of the mountain, throwing snow "
    +"all throughout the air around you and "
    +"forming a whirlwind. It takes all your "
    +"strength to hold on to your current "
    +"position, finding brief moments of respite "
    +"between each wind-wave.\n");

    add_item(({"stone","stones","jagged stones","jagged stone"}),
    "Jagged stones protrude slightly from the mountain, "
    +"sheltering patches of "
    +"dryness amidst the snow-covered prominence "
    +"before you. They look as if they "
    +"would pierce through the layers of snow. You "
    +"are hanging on to them at "
    +"the moment, and looking up or down you "
    +"find similar ones within reach.\n");

    add_item(({"whirlwind"}),
    "The western winds buffet mightly against the "
    +"mountain, reverberating around "
    +"the area and boncing off with revolved snow "
    +"which twirl around you before "
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
