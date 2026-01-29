/*  /d/Faerun/phlan/rooms/innbed.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;


void
create_phlan_room()
{
    set_long("A private bedroom of the Cracked Crown Inn.\n"
        +"The bedroom is simple and comfortable. A large bed"
        +" and overstuffed chair sit on a thick carpeted floor."
        +" A window in the east wall catches the sun rising"
        +" over the Moonsea every morning. A large painting hangs on"
        +" the western wall while polished brass lamps in wrought"
        +" iron sconces adorn the northern and southern ones. A staircase"
        +" leads down to the inn.\n");
    
    set_short("Inn bedroom");
    
        
    add_item(({"wall","walls"}),
    "The walls are made of cedar, reddish hued with black knots.\n");

    add_item(({"carpet"}),
        "The carpet is thick-piled to keep down the noise from the inn"
        +" below. It is a uniform earth-tone.\n");

    add_item(({"floor", "ground"}),
        "The floor is covered in a deep carpet from wall to wall. This"
        +" helps mute sound to allow for a good night's sleep.\n");

    add_item(({"staircase"}),
        "The wooden staircase goes down to the inn on the main floor."
        +" You will need a key to return to the second floor.\n");

    add_item(({"window"}),
        "Looking out the window you see the harbour and the Moonsea"
        +" beyond.\n"); 

    add_item(({"harbour", "harbor"}),
        "The harbour cuts into the land in a deep calm anchorage that led"
        +" to the formation of the town.\n");

    add_item(({"sea", "moonsea"}),
        "The Moonsea stretches as far to the eastern horizon as you can see."
        +" Its deep blue depths reflect the sky above while whitecaps top"
        +" the rolling waves.\n");  

    add_item(({"ceiling"}),
        "The ceiling is the same knotty redwood as the walls.\n");

    add_item(({"bed", "quilt"}),
        "The bed has a thick goose-down mattress covered with a heavy"
        +" warm quilt. It is freshly made with fluffed pillows on top"
        +" of the quilt at the head. The quilt is a dark green and matches"
        +" the pillows. It hangs all the way to the floor off the sides of"
        +" the bed. You can <lay> on it.\n");

    add_item(({"chair"}),
        "The chair is overstuffed and big enough for the tallest"
        +" adventurer. It is covered in soft tan leather that promises"
        +" comfort. You can <sit> in it.\n");
        
    add_item(({"pillow", "pillows"}),
        "The pillows are recently fluffed in dark green cases.\n");

    add_item(({"leather"}),
        "The leather is light tan and very soft. More supple than regular"
        +" cow hide, this appears to be doe skin, probably from the game"
        +" of the Quivering Forest.\n");

    add_item(({"lamp","lamps"}),
        "Polished brass lamps bur brightly in their wrought iron"
        +" sconces. They produce no smoke.\n");

    add_item(({"sconce","sconces"}),
        "The scones are of blackened wrought iron, providing an"
        +" attractive contrast to the polished brass of the lamps./n");

    add_item(({"painting"}),
        "The painting has a gilded frame of light wood. The artwork"
        +" is that of a nautical scene. You see a trade vessel under"
        +" full sail crossing a deep blue watery expanse.\n");    

    add_item(({"frame", "gilded frame"}),
        "The frame is of a light wood with a coarse grain. Quite"
        +" probably this is dried driftwood. The gilding is paint"
        +" infused with traces of gold dust. Not worth anything in"
        +" terms of the gold content, it makes a beautiful decorative"
        +" finish.\n");       

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "inn", "down");
}

/*
 * Function that allows the player to sit in the chair or lay on the bed
 */
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_in_chair"))
    {
        write("But you are already sitting in the chair!\n");
        return 1;
    }


    if(str == "in chair" | str == "in the chair"
    | str == "on chair" | str == "on the chair")

    {
        this_player()->catch_msg("You sit down in the overstuffed"
        +" chair. You feel yourself sinking into the supple leather"
        +" and ample stuffing in a comforting embrace. You feel you"
        +" can stand at any time.\n");
        say(QCTNAME(this_player()) + " sits down in the overstuffed"
        +" chair, relaxing in its embrace.\n");
        this_player()->add_prop("_sitting_in_chair", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting in"
        +" the chair.");
        return 1;
    }


    else
    {
        this_player()->catch_msg("Would you like to sit in the chair?\n");
        return 1;
    }

    return 1;
}


/*
 * Function that allows the player to stand from the chair
 */
 
int
action_stand(string str)
{
    if(str == "stand", "up", "stand up")
    {
        if(this_player()->query_prop("_sitting_in_chair"))
        {
            this_player()->catch_msg("You stand up from the comfortable"
            +" overstuffed chair with some reluctance.\n");
            say(QCTNAME(this_player())+" reluctantly stands up from the chair.\n");
            this_player()->remove_prop("_sitting_in_chair");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

    }

    else
    {
        this_player()->catch_msg("Up? Stand up?\n");
        return 1;
    }

    return 1;
}


/*
 * Function to cleanup props if a player leaves before standing or rising
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_in_chair"))
    {
        ob->catch_msg("You stand up from the chair before leaving.\n");
        say(QCTNAME(ob) + " stands up from the chair before "
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_in_chair");
    }
    
     if(ob->query_prop("_laying_on_bed"))
    {
        ob->catch_msg("You rise from the bed before leaving.\n");
        say(QCTNAME(ob) + " risess up from the bed before "
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_laying_on_bed");
    }  
    
}

int 
action_lay(string str)
{
    
    if(this_player()->query_prop("_laying_on_bed"))
    {
        write("But you are already laying on the bed!\n");
        return 1;
    }


    if(str == "in bed" | str == "in the bed"
    | str == "on bed" | str == "on the bed")

    {
        this_player()->catch_msg("You lay down on the goose down"
        +" mattress. You stretch out on the dark green quilt"
        +" and rest your head on the freshly fluffed pillow."
        +" You feel you can rise at any time.\n");
        say(QCTNAME(this_player()) + " lays down on the goose down"
        +" mattress, resting their head on a pillow.\n");
        this_player()->add_prop("_laying_on_bed", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is laying on"
        +" the bed.");
        return 1;
    }


    else
    {
        this_player()->catch_msg("Would you like to lay on the bed?\n");
        return 1;
    }

    return 1;
}


/*
 * Function that allows the player to rise from the bed
 */
 
int
action_rise(string str)
{
    if(str == "rise", "rise up")
    {
        if(this_player()->query_prop("_laying_on_bed"))
        {
            this_player()->catch_msg("You rise slowly from the bed feeling very"
            +" relaxed.\n");
            say(QCTNAME(this_player())+" rises slowly from the bed.\n");
            this_player()->remove_prop("_laying_on_bed");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

    }

    else
    {
        this_player()->catch_msg("Rise up? Rise?\n");
        return 1;
    }

    return 1;
}


public int
start(string str)
{
    object ob;

    if (str != "here")
    {
        write("Start where?\n");

        return 1;
    }

    if (this_player()->query_temp_start_location() == ROOM_DIR + "innbed")
    {
        write("You have already checked in!\n");
        return 1;
    }


    if(!(ob=present("_crown_key_inn",this_player())))
    {
        write("You don't have the key you need!\n");
        return 1;
    }

    ob->remove_object();

    this_player()->set_temp_start_location(ROOM_DIR + "innbed");

    write("You notice that the brown metal key crumbles to dust in your "
    + "hand. Suddenly you are confident that you will start here the next "
    + "time you enter the game.\n");

    return 1;
}


void init()
{
    ::init();
    add_action("action_lay", "lay");
    add_action("action_rise", "rise");
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
    add_action(start, "start");
}


void
reset_faerun_room()
{
    set_searched(0);
}