/* /d/Faerun/guilds/fire_knives/rooms/climb6.c
 *
 * Sixth and last room climbing up to the ledge
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

            this_player()->heal_hp(-10000);
            this_player()->set_fatigue(this_player()->query_fatigue() - 110);

            if (this_player()->query_hp() <= 0)
            {
                this_player()->do_die(this_object());
            }
            
            return 1; 
        }
        
        write("\nYou continue to climb the cliffside upwards and "
        +"finally reach a ledge!\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " continues to climb upwards.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        + "rooms/ledge", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR + "rooms/ledge", QCTNAME(this_player())
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

            this_player()->heal_hp(-10000);
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
        + "rooms/climb5", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb5", QCTNAME(this_player())
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
    set_short("Above a thick blanket of fog");
    
    set_extraline("Holding on to firm stone protrusions from the "
    +"mountain you stand "
    +"above a thick blanket of fog that covers the area below you where the "
    +"shadow of similar stones can be discerned by their outline. From here, "
    +"directly to your northeast above you is a ledge on the mountain. While "
    +"it is unclear if anything lies beyond it, the opportunity for respite "
    +"seems tempting. The cold is intense up here, and a thin layer of ice "
    +"covers most of the areas safe from the stone by the stones jutting out "
    +"from the mountain.");

    add_item(({"ledge"}),
    "A ledge is clearly discernible from here above you, offering some "
    +"respite from the position you currently find yourself "
    +"in.\n");

    add_item(({"ice"}),
    "A thin layer of ice covers most of the areas on the "
    +"mountain which aren't "
    +"protected by the stone jutting out.\n");

    add_item(({"snow", "snowdrift","snowflakes", "flakes",
    "flake","layer","layers",
    "patch","patches"}),
    "Layers of snow cover everything around you, barely "
    +"visible yet perceptible.\n");

    add_item(({"ground","floor", "base"}),
    "The ground is not visible from here. \n");

    add_item(({"mountain","mountains"}),
    "The mountain is wide and high, extending downwards as "
    +"far as the eye can see "
    +"but it isn't clear where it ends. From here to "
    +"the northeast you can see "
    +"a ledge to your northeast, while the mountain "
    +"continues upwards without "
    +"any visible stones such as the one you're holding on to.\n");

    add_item(({"fog","blanket", "blanket of fog"}),
    "The fog obscures the view of the mountain past some "
    +"meters downwards, about twice "
    +"your height, rendering details imperceptible from here.\n");
       
    add_item(({"winds","wind"}),
    "The winds buffet mightily against you as try "
    +"and hold on to the stones jutting "
    +"outwards of the mountain, throwing snow "
    +"all throughout the air around you and "
    +"forming a whirlwind. It takes all your "
    +"strength to hold on to your current "
    +"position, finding brief moments of "
    +"respite between each wind-wave.\n");

    add_item(({"stone","stones","jagged stones",
    "jagged stone","protrusions"}),
    "Jagged stones protrude slightly from the "
    +"mountain, sheltering patches of "
    +"dryness amidst the snow-covered prominence "
    +"before you. They look as if they "
    +"would pierce through the layers of snow. "
    +"You are hanging on to them at "
    +"the moment, and looking down you find an "
    +"outline of similar ones within reach "
    +"inside the fog while upwards they seem to have disappeared.\n");

    add_item(({"shadow", "shadows"}),
    "The shadowy outline of what appears to be stones "
    +"similar to the ones you now "
    +"hold on to are discernible downwards, though "
    +"it is uncertain if that is the case. "
    +"Nevertheless it is your only chance to continue "
    +"the climb in that direction.\n");

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
