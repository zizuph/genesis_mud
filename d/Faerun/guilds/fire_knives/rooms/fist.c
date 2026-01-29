/* /d/Faerun/guilds/fire_knives/rooms/fist.c
 *
 * The Fist's Chamber
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

    set_short("The Fist's Chamber");
    
    set_long("Within the chamber there is barely a thing to be seen "
    +"that isn't meant to cause discomfort and pain. Unlike the rest "
    +"of the keep, the floor isn't covered in any sort of soft "
    +"fabric. In the otherwise "
    +"empty room there is only few steps to the end of the room to the "
    +"north leading up to a dais with a worn and "
    +"notched heavy desk with a high backed "
    +"chair. Mirrors reflect "
    +"the scarce light coming in through a minuscule skylight, covering "
    +"the area in twisted and contorted reflections of yourself.\n"); 

    add_item(({"floor"}),
    "Unlike the rest of the keep, the floor here is bare and cold. " 
    +"It seems to whisper from underneath you, chilling your feet and the "
    +"rest of your body by extension.\n");
    
    add_item(({"chair", "backed chair", "high backed chair"}),
    "This is a high backed chair made out of black wood, the backpiece "
    +"extends 2 meters from the seat and has a clenched fist with the "
    +"symbol of the Fire Knives engraved on what would be the wrist.\n");

    add_item(({"desk", "notched heavy desk", "notched desk", "heavy desk"}),
    "This is a heavy, darkened and severely work desk. The black "
    +"color is the only remarkable thing about it other than "
    +"the notches from various knives and other tools on the "
    +"surface, a few bloodstains adorn a corner.\n");
    
    add_item(({"notches"}),
    "The notches in this desk where made from the fist's "
    +"impulsive anger and are quite deep.\n");
    
    add_item(({"blood", "stain", "stains of blood", "blood stain"}),
    "The stains of blood are old and dried, likely left "
    +"there on the corner of the desk to make a point to "
    +"those that enter.\n");
    
    add_item(({"dais"}),
    "The dais is found atop the steps to the northern side of the room. "
    +"Upon it is a notched heavy desk and a high backed chair.\n");
    
    add_item(({"mirror", "mirrors"}),
    "The mirrors are positioned to capture the little light coming from "
    +"the skylight, sending it bouncing around them, "
    +"confusing your eyesight. "
    +"As you look into them, you catch only perverted reflections of your "
    +"factions, distorted in pain and anguish, rendering you unable to "
    +"find any comfort within this room. \n");
    
    add_item(({"skylight"}),
    "The skylight is located at the northern part of the ceiling, from which "
    +"the outside world sends its signals.\n");
 
    add_exit(FIREKNIVES_ROOMS_DIR + "b2", "east");

    reset_faerun_room();
}


/*
 * Function that allows the player to sit 
 */
int action_sit(string str)
{
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()))
    {
        if(this_player()->query_prop("_sitting_at_thefist_chair"))
        {
            write("But you are already sitting in your chair!\n");
            return 1;
        }   
        
        if(str == "in the chair" | str == "chair" | str == "in chair")
        {
            this_player()->catch_msg("You sit down in the high "
            +"backed chair with the symbol of a fist carved on it.\n");
            
            say(QCTNAME(this_player()) + " sits down in the high "
            +"backed chair with the symbol of a fist carved on it.\n");
            
            this_player()->add_prop("_sitting_at_thefist_chair", 1);
            
            this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
            +" in the high backed chair with the symbol of a fist carved on it");
            return 1;
        }

        else
        {
            this_player()->catch_msg("Please 'sit in chair'.\n");
            return 1;
        }
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
        if(this_player()->query_prop("_sitting_at_thefist_chair"))
        {
            this_player()->catch_msg("You stand up and leave the "
            +"high backed chair with the symbol of a fist carved on it.\n");
            
            say(QCTNAME(this_player())+" stands up from the high "
            +"backed chair with the symbol of a fist carved on it.\n");
            
            this_player()->remove_prop("_sitting_at_thefist_chair");
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
    
    if(ob->query_prop("_sitting_at_thefist_chair"))
    {
        ob->catch_msg("You stand up and leave the high "
        +"backed chair with the symbol of a fist carved on "
        +"it before leaving the room.\n");
        
        say(QCTNAME(ob)+" stands up from the high "
        +"backed chair with the symbol of a fist "
        +"carved on it before leaving the room.\n");
        
        ob->remove_prop("_sitting_at_thefist_chair");
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
            WIZARD_ENTRY_FIST_LOG("wizard_entry_fist_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives Fist room.\n");
            
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
