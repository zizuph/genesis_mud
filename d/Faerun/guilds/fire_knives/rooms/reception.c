/* /d/Faerun/guilds/fire_knives/rooms/reception.c
 *
 * Reception Room
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A Reception Room");
    
    set_long("A room bare of any comforts beyond the carpeted floor  "
    +"covering the cold stone of the keep. Sconces hold torches on "
    +"the walls the uncover the passageways opening in four different "
    +"directions from here. Stairs wind downwards next to a long "
    +"bench in which you can sit and wait. To the north, an "
    +"archway leads into the unknown.\n");
    
    add_item(({"room"}),
    " You are within it.\n");
        
    add_item(({"floor"}),
    "The room is covered in a simple black carpet the muffles all sound "
    +" and provides protection against the coldness of "
    +"the stone underneath it.\n");
    
    add_item(({"stone","stones"}),
    "The stone of the floor of the old keep is covered in carpets.\n");
    
    add_item(({"torches","torch"}),
    "The torches hang on the sconces. They are currently lit.\n");  
    
    add_item(({"stairs","stairway","stair"}),
    "The stairs lead downwards back to the second floor of the keep.\n");
    
    add_item(({"bench", "long bench"}),
    "It is a long wooden bench that can fit several people.\n");
    
    add_item(({"archway"}),
    "The archway is simple and made of stone. On its center "
    +"is a symbol of a "
    +"dagger wrapped in flames.\n");
    
    add_item(({"walls","wall"}),
    "The walls of the chamber are simple and bare, devoid of "
    +"decorations. Its dank stones emanating an uncomfortable "
    +"coldness. The lack of distractions makes any time spent here "
    +"gnaw at your very soul.\n");
       
    add_item(({"sconces","sconce"}),
    "the sconces hang on each and every one of the walls at an "
    +"almost unreachable height. Each one of them holds a lit, burning "
    +"torch that sheds light in the otherwise dark, featureless room.\n");
    
    add_item(({"carpet", "carpets"}),
    "The carpet covering the cold stone floor is simple and "
    +"black, thick enough to muffle the sound of footsteps while "
    +"also providing protection against coldness of the stone underneath it.\n");
    
    add_exit(FIREKNIVES_ROOMS_DIR + "b2.c", "west");
    add_exit(FIREKNIVES_ROOMS_DIR + "conference.c", "north");
    add_exit(FIREKNIVES_ROOMS_DIR + "post", "northeast");
    add_exit(FIREKNIVES_ROOMS_DIR + "b1.c", "east");
    add_exit(FIREKNIVES_ROOMS_DIR + "h1.c", "down");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


/*
 * Function that allows the player to sit
 */
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_at_bench"))
    {
        write("But you are already sitting at the bench!\n");
        return 1;
    }

    if(str == "on the bench" | str == "on bench" | str == "bench")
    {
        this_player()->catch_msg("You sit down on the bench.\n");
        say(QCTNAME(this_player()) + " sits down on the bench.\n");
        this_player()->add_prop("_sitting_at_bench", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
        +"on the bench");
        return 1;
    }

    else
    {
        this_player()->catch_msg("Where would you like to sit? "
        +"On the bench?\n");
        return 1;
    }

    return 1;
}


/*
 * Function that allows the player to stand 
 */
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_at_bench"))
        {
            this_player()->catch_msg("You stand up and leave the bench.\n");
            say(QCTNAME(this_player())+" stands up from the bench.\n");
            this_player()->remove_prop("_sitting_at_bench");
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
                
    if(ob->query_prop("_sitting_at_bench"))
    {
        ob->catch_msg("You stand up from the bench before leaving.\n");
        say(QCTNAME(ob) + " stands up from the bench before "
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_bench");
    }
}


void init()
{
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}

