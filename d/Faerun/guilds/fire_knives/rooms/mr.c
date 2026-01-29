/* /d/Faerun/guilds/fire_knives/rooms/mr.c
 *
 * Meeting Room for Assassins
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

    set_short("A lounge within the keep");
    
    set_long("Within the luxuriously spacious "
    +"room reigns a sense of comfort "
    +"unparallel. Massive wall high windows "
    +"crown the easthern wall of the area "
    +"surrounded by purple curtains embroided "
    +"in a golden hue in front of which "
    +"is a comfortable looking couch. To the "
    +"north are two murals, to the right "
    +"and left of an imposing board, each one "
    +"towering up to the arching ceiling "
    +"sealed off and sustained by curving wooden "
    +"planks. The cold stone floor "
    +"is covered in thick reddish carpets, "
    +"muffling any sounds of steps or "
    +"conversations that may be had in one of "
    +"the circular tables placed in "
    +"the room around which there are five chairs each.\n");
    
    add_item(({"room","spacious room"}),
    "The room is spacious and luxuriously decorated, "
    +"providing a sense of calm "
    +"comfort ideal for relaxation.\n");

    add_item(({"windows","window","high window","high windows"}),
    "High windows dominate the room from the "
    +"eastern wall of the room, decorated "
    +"with thick purple curtains. The glass "
    +"is reinforced to maintain the warmth "
    +"of the room while allowing you to look out from it.\n");

    add_item(({"northern wall","wall", "walls"}),
    "The northern wall bears a single board in the "
    +"middle of two rich murals at "
    +"each one of its sides, one to the right and "
    +"the other to the left of it.\n");
    
    add_item(({"curtains","curtain","purple curtains","purple curtain"}),
    "Thick purple curtains droop down from the top "
    +"of the window and are held in "
    +"place by each side of it, leaving the "
    +"window uncovered for a dim light to "
    +"come through and allow you to look out from it.\n");
    
    add_item(({"couch"}),
    "A comfortable looking purple couch is placed "
    +"underneath the window on the "
    +"eastern wall of the room. With space enough "
    +"for three persons to sit down "
    +"or one to lay, it fits perfectly beneath the frame.\n");

    add_item(({"murals", "mural"}),
    "There are two murals you can examine. One to the "
    +"left and one to the right "
    +"of the board.\n");
    
    add_item(({"plate"}),
    "The small hot plate is full of minuscule burning coals, "
    +"providing warmth to those sitting at the table.\n");
    
    add_item(({"eastern wall"}),
    "The eastern wall is crowned by a massive wall-high "
    +"window, which is un turn surrounded by purple curtains "
    +"embroided in a golden hue in front of which is a "
    +"comfortable looking couch.\n");
    
    add_item(({"left mural"}),
    "The left mural bears a full body image of a "
    +"female body clad in white shredded "
    +"robes. Four arms extend from its sides, two "
    +"pointing upwards and two downwards "
    +"while her lustruous black hair seems to "
    +"fly upwards as if she was falling.\n ");
    
    add_item(({"right mural"}),
    "The right mural depicts two bodies standing "
    +"back to back with their arms across "
    +"their chests, wearing similar yet oppositely "
    +"coloured gold and black clothing. "
    +"Both have long golden hair and are similar "
    +"in height, yet one is laughing in the "
    +"way a maniac would whilst the other, saddened, "
    +"looks downwards.\n");
    
    add_item(({"carpet","carpets","floor"}),
    "Thick reddish carpets cover the entirety of the "
    +"floor, muffling sounds of steps "
    +"and conversations.\n");
    
    add_item(({"table","tables"}),
    "The tables are circular, with four legs bending "
    +"outwards to keep their balance. "
    +"In the center of it is a small hot plate "
    +"with minuscule burning coals, providing "
    +"warmth to those sitting around it.\n");
    
    add_item(({"chair","chairs"}),
    "The chairs are wooden, cushioned in the back, "
    +"arms and bottom with a fluffy puple "
    +"material.\n");

    add_item(({"ceiling"}),
    "The ceiling has been sealed off low and is "
    +"supported by arching wooden planks to "
    +"maintain the room's warmth intact rather "
    +"than have it drift upwards to the stone "
    +"ceiling.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "h3", "west");
    
    room_add_object(FIREKNIVES_BOARDS_DIR + "full_board");
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_at_couch"))
    {
        write("But you are already sitting in a couch!\n");
        return 1;
    }

    if(str == "on the couch" | str == "on couch" | str == "couch")
    {
        this_player()->catch_msg("You sit down on one of the "
        +"couches.\n");
        say(QCTNAME(this_player()) + " sits down on a couch.\n");
        this_player()->add_prop("_sitting_at_couch", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
        +"on a couch");
        return 1;
    }
    
    if(str == "on the chair" | str == "on chair" | str == "chair")
    {
        this_player()->catch_msg("The chairs are better suited for "
        +"a bigger party. Why not take your place by the couch instead?\n");
        
        return 1;
    }

    else
    {
        this_player()->catch_msg("Where would you like to sit? "
        +"On the couch?\n");
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
        if(this_player()->query_prop("_sitting_at_couch"))
        {
            this_player()->catch_msg("You stand up and leave the couch.\n");
            say(QCTNAME(this_player())+" stands up from the couch.\n");
            this_player()->remove_prop("_sitting_at_couch");
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
                
    if(ob->query_prop("_sitting_at_couch"))
    {
        ob->catch_msg("You stand up from the couch before leaving.\n");
        say(QCTNAME(ob) + " stands up from the couch before "
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_couch");
    }
}


void init()
{
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}
