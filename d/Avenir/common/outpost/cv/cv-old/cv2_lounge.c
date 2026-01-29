/* /d/Faerun/guilds/vampires/rooms/cv1_lounge.c
 *
 * Nerull 2021
 *
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/vampires/guild.h";
#include <stdproperties.h>

inherit VAMPIRES_STD_ROOM;

/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Lounge");
    
    set_long("The relatively large room opens up into a vast "
    +"gathering chamber dripping with exponentially more affluence "
    +"and lavishness than in any other parts of the lair. There are "
    +"various couches and throw-rugs lazily "
    +"placed about the room as though to foster an atmosphere "
    +"of relaxation and ease; a place to forget about things like "
    +"hunger, mortals or the sun. The room us suffused with "
    +"goblets, baubles and numerous other treasures gathered "
    +"throughout the ages. The walls are covered in "
    +"decorations befitting a king's court, yet the ceiling "
    +"is veiled in complete darkness.\n");
    
    add_item(({"treasures" }),
        "Goblets, gemstones, baubles and other trinkets of "
        +"value are spread out throughout the room in a "
        +"careless manner.\n");

    add_item(({"goblets" }),
        "Cups of all sizes and shapes, bejeweled and smooth. Many "
        +"of the treasures thrown carelessly throughout the room.\n");
        
    add_item(({"baubles" }),
        "Numerous trinkets and trifles strewn throughout, "
        +"carelessly. A testament to the effluence of the room.\n");
        
    add_item(({"wall", "walls" }),
        "The walls are made from a polished, dark, mahogany "
        +"wood and covered in decoration befitting a regal palace.\n");
        
    add_item(({"wood" }),
        "The wood of the walls is a polished mahogany with a "
        +"deep dark richness.\n");

    add_item(({"rug", "rugs"}),
        "Finely woven, thread-bare and multi-colored floor "
        +"coverings collected through the ages.\n");
           
    add_item(({"decoration", "decorations"}),
        "Copious wall coverings of varying color enshrouding the "
        +"walls, giving the sense of a regal setting.\n");
                      
     add_item(({"ceiling", "roof" }),
       "Strange as it may be, the ceiling is covered by something "
       +"resembling magical darkness that even your eyes can't pierce "
       +"through.\n");
                      

    add_exit(VAMPIRES_GUILD_DIR + "rooms/cv1_entryway", "south");
    
    reset_faerun_room();
}


/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_in_couch"))
    {
        write("But you are already sitting in one of the couches!\n");
        return 1;
    }
    if(str == "couch" | str == "in couch"
    | str == "in one of the couches")
    {
        this_player()->catch_msg("You sit down in one of the couches.\n");
        
        say(QCTNAME(this_player()) + " sits down in one of the couches.\n");
        
        this_player()->add_prop("_sitting_in_couch", 1);
        
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting in one of "
        +"the couches");
        return 1;
    }
    else
    {
        this_player()->catch_msg("Where would you like to sit? "
        +"In one of the couches?\n");

        return 1;
    }
    return 1;
}


/*
 * Function that allows the player to stand from a table or the bar
 */
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_in_couch"))
        {
            this_player()->catch_msg("You rise up from the couch.\n");
            
            say(QCTNAME(this_player())+" rises from one of the couches.\n");
            
            this_player()->remove_prop("_sitting_in_couch");

            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
    }
    else
    {
        this_player()->catch_msg("Stand? Stand up?\n");
        return 1;
    }
    return 1;
}


/*
 * Function to cleanup props if a player leaves before standing
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_in_couch"))
    {
        ob->catch_msg("You rise from the couch before leaving.\n");
        
        say(QCTNAME(ob) + " rises up from one of the couches before "
        +"leaving the room.\n");
        
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        
        ob->remove_prop("_sitting_in_couch");
    }
}


void
init()
{
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}
