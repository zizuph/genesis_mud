/* /d/Faerun/guilds/fire_knives/rooms/climb5.c
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
            
            tell_room(FIREKNIVES_GUILD_DIR + "rooms/mountain_ft", 
            QCTNAME(this_player())
            + " crashes in from above, plunging into the ground with an "
            +"alarming speed!\n", this_player()); 

            this_player()->heal_hp(-6000);
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
        + "rooms/climb6", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb6", QCTNAME(this_player())
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
            + " suddenly fall off the cliffside and plunges down!\n", 
            this_player());
            
            this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
            + "rooms/mountain_ft", 1);
            
            tell_room(FIREKNIVES_GUILD_DIR 
            + "rooms/mountain_ft", QCTNAME(this_player())
            + " crashes in from above, plunging into the ground with an "
            +"alarming speed!\n", this_player()); 

            this_player()->heal_hp(-6000);
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
        + "rooms/climb4", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb4", QCTNAME(this_player())
        + " arrives climbing down from above.\n", this_player());
        
        this_player()->set_fatigue(this_player()->query_fatigue() - 40);
        
        return 1;
    }
    
    write("Climb up or down, perhaps?\n");
    
    return 1;
}


void
create_fireknives_outdoor()
{
    set_short("Engulfed in the fog");
    
    set_extraline("The fog embraces you and hinders "
    +"your sight of anything not up "
    +"close to your face here. The chilled air "
    +"serves as a sort of protection "
    +"from the winds below, surrounding you in "
    +"an eerie and calming silence."
    +"The cold turns your hands to claws that "
    +"hang on to the stones protruding "
    +"from the mountain, nails biting deep into "
    +"the surface grasping for strength."
    +"Blinking to try and clear your sight, "
    +"you notice a slight clarity below "
    +"you which reveals similar stones you could "
    +"use to climb down, while "
    +"upwards only the faintest shadow of something similar can be seen.");

    add_item(({"snow", "snowdrift","snowflakes", "flakes",
    "flake","layer","layers",
    "patch","patches"}),
    "Layers of snow cover everything around you, barely "
    +"visible yet perceptible.\n");

    add_item(({"ground","floor", "base"}),
    "The ground is not visible from here. \n");

    add_item(({"mountain","mountains"}),
    "The mountain is wide and high, extending downwards "
    +"as far as the eye can see "
    +"but it isn't clear where it ends. The "
    +"only visible thing are more of the same "
    +"stones jutting outwards from it as the ones you now hold on to.\n");

    add_item(({"fog","blanket", "blanket of fog", "air"}),
    "You are within the fog, engulfed by it and unable "
    +"to see much from here past it.\n");

    add_item(({"sky"}),
    "The fog that surrounds you obfuscates the sky "
    +"above you, rendering it invisible.\n");
       
    add_item(({"winds","wind"}),
    "The winds seem to have calmed here, the chilled "
    +"air which surrounds you acting "
    +"as a protector from it. You can still hear the "
    +"whispers from its gusts below.\n");

    add_item(({"stone","stones","jagged stones","jagged stone"}),
    "Jagged stones protrude slightly from the mountain, "
    +"sheltering patches of "
    +"dryness amidst the snow-covered prominence "
    +"before you. They look as if they "
    +"would pierce through the layers of snow. "
    +"You are hanging on to them at "
    +"the moment, and looking down you find "
    +"similar ones within reach, while upwards "
    +"only the shadow of something similar can be seen.\n");

    add_item(({"shadow", "shadows"}),
    "The shadowy outline of what appears to be stones "
    +"similar to the ones you now "
    +"hold on to are discernible upwards, though "
    +"it is uncertain if that is the case. "
    +"Nevertheless it is your only chance to continue the climb upwards.\n");

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
