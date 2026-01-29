/* /d/Faerun/guilds/fire_knives/rooms/ledge.c
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
    if (str == "down")
    {
        write("\nYou start to climb downwards along the cliffside.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " starts to climb downwards along the cliffside.\n", this_player()); 
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        + "rooms/climb6", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR 
        + "rooms/climb6", QCTNAME(this_player())
        + " arrives climbing down from the ledge.\n", this_player());
        
        return 1;
    }
    
    write("Climb down, perhaps?\n");
    
    return 1;
}


int
do_crawl(string str)
{
    if (str == "through rift" || str == "through fissure" 
    || str == "through hole")
    {
        write("\nYou crawl through the rift.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " crawls through the rift.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR + "rooms/g0", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR + "rooms/g0", QCTNAME(this_player())
        + " arrives crawling through the rift.\n", this_player());
        
        return 1;
    }
    
    write("Crawl through rift, perhaps?\n");
    
    return 1;
}


void
create_fireknives_outdoor()
{
    set_short("Above a thick blanket of fog");
    
    set_extraline("Standing on the stoney platform projecting "
    +"forth from the wall "
    +"of rock it seems as if the "
    +"world spread out before you, covered in snow "
    +"as far as the eye can see. From here "
    +"it is easy to forget how high up on "
    +"the mountain you are by seeing just "
    +"how much higher it goes, yet it is "
    +"as if it embraced another from the back "
    +"to protect it from view. The sloping "
    +"platform appears narrower than it is, "
    +"halfway protected from the falling "
    +"snow as it is by the jutting stone that "
    +"arches forward and continues upwards, "
    +"making it impossible to imagine climbing "
    +"anywhere but down from here where "
    +"jutting, jagged stones seem like handlebars, "
    +"while to horizontal cardinal "
    +"point there is a dead-end as the ledge meets the wall.");

    add_item(({"sloping platform","platform","stoney platform","ledge"}),
    "The platform is less slippery than it should "
    +"be with all the falling snow. "
    +"It is as if it would be periodically maintained "
    +"with tiny rocks spread out "
    +"across it to ensure firm footing upon it.\n");
    
    add_item(({"rocks","rock","tiny rock","tiny rocks","pebbles"}),
    "Tiny rocks, small as crushed gems, are spread "
    +"out across the sloping platform in "
    +"a fashion that appears more human made "
    +"than natural. It is as if someone "
    +"intentionally wanted whoever steps foot "
    +"up here to have a firm footing.\n");

    add_item(({"wall","walls","wall of rock","slope"}),
    "The wall of stone from which the ledge protrudes "
    +"continues upwards in a slope that "
    +"serves as a ceiling, and further from there "
    +"along the side of the mountain. At the "
    +"point where the slope becomes obvious is "
    +"more snow than on the edges of the ledge, "
    +"which seems unusual given the protection "
    +"from the ceiling.\n");

    add_item(({"ceiling"}),
    "The ceiling is formed by the sloping wall's "
    +"upwards travel along the side of the "
    +"mountain. It proves a bit of protection "
    +"against the falling snow.\n");

    add_item(({"mountain"}),
    "The mountain continues upwards and downwards, "
    +"and to both sides, as far as the "
    +"eye can see. It seems to do so in a "
    +"circular fashion, as if it would embrace "
    +"another structure from behind, keeping it from view.\n");

    add_item(({"snow","falling snow"}),
    "The snow falls continuously, blown about "
    +"by the wind. The ledge's ceiling provides "
    +"some protection from it, but although it "
    +"should accumulate more heavily at the edge "
    +"of the ledge, there is far more of it at "
    +"the slope on the inside of the wall, as if "
    +"someone had swept and placed most of it "
    +"there. You notice a horizontal rift behind "
    +"the pile of snow here.\n");

    add_item(({"rift","fissure","hole"}),
    "Behind the pile of snow on the wall is a "
    +"horizontal rift within the wall. It's maybe "
    +"possible to crawl through it.\n");

    add_item(({"stone", "stones", "jutting stone","handlebar","handlebars"}),
    "Stone jut out from the lower section of the "
    +"mountain wall, serving as handlebars "
    +"which you could use to climb downwards from here.\n");

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
    add_action(do_crawl, "crawl");
}
