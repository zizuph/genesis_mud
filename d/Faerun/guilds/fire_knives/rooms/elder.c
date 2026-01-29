/* /d/Faerun/guilds/fire_knives/rooms/elder.c
 *
 * Room for the Elder/Master of Assassins
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

    set_short("The Elder's Chamber");  
     set_long("A lavishly decorated chamber is now found where the once "
    +"bare hole into the keep was carved. Its floor is covered in a white "
    +"bearskin rug that muffles all sound. Stone replicas of enemies' heads "
    +"serve as sconces for the torches shedding off light and warmth to the "
    +"otherwise cold room. In the center of the room, right below the high "
    +"candelabra hanging from its ceiling is a sturdy mahogany "
    +"desk in front of a comfortable tall chair.\n");

    add_item(({"chamber", "room"}),
    "You are within it.\n");
    
    add_item(({"floor"}),
    "The otherwise cold, stone floor is decorated with a "
    +"lavish white bearskin "
    +"rug that muffles all sound.\n");
    
    add_item(({"rug", "bearskin rug","carpet"}),
    "A comfortable white bearskin rug covers the "
    +"otherwise cold, stone floor "
    +"and muffles all sound from it.\n");
    
    add_item(({"heads", "replicas"}),
    "The sconces of the wall are made of stone and formed into replicas of "
    +"what can only be interpreted as enemies. Their "
    +"expressions are sculpted "
    +"into those of torment and anguish. Upon and within their skulls are "
    +"torches which shed light and warmth to the chamber.\n");
    
    add_item(({"torches","torch"}),
    "The torches resting within the sconces are currently lit.\n");
    
    add_item(({"candelabra"}),
    "The candelabra rests by thick chains from a ceiling hidden beneath "
    +"dancing shadows.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is hidden beneath dancing shadows. Its existence only "
    +"explained by the chains dropping from it and from which the candelabra "
    +"hangs.\n");
    
    add_item(({"chains","chain"}),
    "Thick iron chains come down from the ceiling, holding "
    +"the candelabra in place.\n");
    
    add_item(({"shadow", "shadows"}),
    "Shadows dance above you in the high ceiling, caused "
    +"by the darkness swayed by "
    +"the flickering light coming from the torches.\n");
    
    add_item(({"desk"}),
    "A sturdy mahogany desk rests in the chamber's "
    +"center in front of a tall chair.\n");
    
    add_item(({"chair", "comfortable chair", "comfortable tall chair"}),
    "This is a comfortable tall chair upon which the "
    +"Inquisitor can sit by the desk.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "conference.c", "south");

    reset_faerun_room();
}


/*
 * Function that allows the player to sit 
 */
int action_sit(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
    {
        if(this_player()->query_prop("_sitting_at_elder_chair"))
        {
            write("But you are already sitting at the decorated throne!\n");
            return 1;
        }   
        
        if(str == "on the chair" | str == "on chair" 
        | str == "chair")
        {
            this_player()->catch_msg("You sit down at the "
            +"high-armed antique chair.\n");
            
            say(QCTNAME(this_player()) + " sits down at the "
            +"high-armed antique chair.\n");
            
            this_player()->add_prop("_sitting_at_elder_chair", 1);
            
            this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
            +" at the high-armed antique chair");
            return 1;
        }

        else
        {
            this_player()->catch_msg("Please 'sit on chair'.\n");
            return 1;
        }

        return 1;
    }
    
    write("This is the personal chair of the Fist! You would rather "
    +"stand.\n");
    
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
        if(this_player()->query_prop("_sitting_at_elder_chair"))
        {
            this_player()->catch_msg("You stand up and leave the "
            +"high-armed antique chair.\n");
            
            say(QCTNAME(this_player())+" stands up from the "
            +"high-armed antique chair.\n");
            
            this_player()->remove_prop("_sitting_at_elder_chair");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
        
        return 1;
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
                
    if(ob->query_prop("_sitting_at_elder_chair"))
    {
        ob->catch_msg("You stand up and leave the "
        +"high-armed antique chair before leaving the room.\n");
        
        say(QCTNAME(ob)+" stands up from the "
        +"high-armed antique chair before leaving the room.\n");
        
        ob->remove_prop("_sitting_at_elder_chair");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
    }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_ELDER_LOG("wizard_entry_elder_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives Elder room.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
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

    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}

