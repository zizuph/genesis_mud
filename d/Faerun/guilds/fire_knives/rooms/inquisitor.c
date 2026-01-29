/* /d/Faerun/guilds/fire_knives/rooms/inquisitor.c
 *
 * Inquisitor's Room
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

    set_short("Inquisitor's Chamber");
   
    set_long("A spacious room serving as an office within "
    +"the keep. The once rough "
    +"stone walls have been smoothened and "
    +"evenly polished, giving it a more "
    +"official look. Arabesque carpets cover "
    +"the whole room floor, silencing "
    +"each possible step in advance, while the "
    +"high ceiling is crowned with "
    +"an ornate candelabra whose light casts "
    +"dancing shadows that fleet all "
    +"about the room. To the north wall is a wide "
    +"mahogany desk in front of "
    +"a high-armed antique chair.\n");

    add_item(({"room", "chamber"}),
    "The room is very spacious and comfortable, albeit somewhat chilly from "
    +" the cold emanating from the walls.\n");
    
    add_item(({"walls"}),
    "There are four walls, one for each cardinal point.\n"); 
    
    add_item(({"wall"}),
    "Examine which wall? The east, north, or west one?\n"); 
    
    add_item(({"north wall"}),
    "The north wall behind the desk is decorated with a full wall fresco.\n");
    
    add_item(({"fresco"}),
    "The great fresco decorates the length of the "
    +"northern wall. The images "
    +"of what appears to be howling widows leaning "
    +"over corpses of strewn bodies "
    +" appear to rise and fall with the room's "
    +"lights, making their expressions "
    +"come alive in anguish and despair.\n");
    
    add_item(({"south wall"}),
    "The south wall is where the door is. It is "
    +"almost bare save for a dart board "
    +" and a plaque.\n");
    
    add_item(({"plaque"}),
    "The plaque is of a golden tone with black "
    +"gothic letters that you can read.\n");
    
    add_item(({"dart board"}),
    "The simple dart board is empty, save for "
    +"an encrusted opal dagger encrusted in "
    +"its centre\n.");
    
    add_item(({"dagger"}),
    "The dagger is simple, with a hilt made of a reddish "
    +"opal tone and a thin blade. "
    +" It is deep within the center of the board.\n");
    
    add_item(({"east wall"}),
    "Two paintings decorate the eastern wall. One "
    +"of a simple golden circle on a black "
    +" background, and another of three interlaced "
    +"rings with a black rose across it.\n");
    
    add_item(({"painting", "paintings"}),
    "You can examine the first or the second painting.\n");
    
    add_item(({"first painting"}),
    "The first painting in a wooden frame depicts "
    +"a simple golden circle superposed "
    +"on a black background. The circle isn't "
    +"perfect, however, and breaks on the "
    +" southeastern side, symbolizing a rupture in continuity\n.");
    
    add_item(({"second painting"}),
    "The second painting is encased within a luxurious "
    +"platinum frame, depicting three "
    +" interlaced rings with a dry, withered, black "
    +"rose across all of them.\n");
    
    add_item(({"west wall"}),
    "The western wall bears various tools hanging from "
    +"hooks or attached to handles.\n");
    
    add_item(({"tools"}),
    "Various tools of assassination decorate the "
    +"length of the west walls, such as stilettos, "
    +"thin wires, and shuriken.\n");
    
    add_item(({"stiletto", "stilettos"}),
    "Stilettos of various shape and sizes hang from "
    +"different parts of the western wall.\n");
    
    add_item(({"wires", "thin wires"}),
    "Thin long copper wires attached to rubber ends. A "
    +"useful weapon for strangulation.\n");
    
    add_item(({"shuriken","shurikens"}),
    "The small and sharp shuriken along the western wall "
    +"reflect the light of the candles.\n");
    
    add_item(({"floor"}),
    "The floor is covered in lavish arabesque carpets, "
    +"absorbing the sound of steps.\n");
    
    add_item(({"carpet", "carpets"}),
    "The carpets are soft to the touch and warm "
    +"on your feet. Their surface decorations "
    +"are based on rhythmic linear patterns of "
    +"scrolling and interlacing foliage.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is high enough for shadows to assemble "
    +"on it, the light of the candelabra "
    +" casting them away to dance around the room "
    +"with each flicker from its candles.\n");
    
    add_item(({"candelabra"}),
    "The candelabra is barely visible from this low "
    +"point, its arms extending around the "
    +" spacious room as if holding its walls in place. "
    +"There is no visible hanging point "
    +" due to the shadows crowding the upper ceiling.");
    
    add_item(({"candles", "candle"}),
    "The candles are thick and long, its wick burning "
    +"with a flickering flame that sways "
    +" in the light wind.");
    
    add_item(({"shadows", "shadow"}),
    "The shadows meet at the top of the high ceiling, "
    +"from there falling like shooting "
    +" stars around the corners of the room.");
    
    add_item(({"desk"}),
    "A thick and wide mahogany desk with a single "
    +"drawer on the inside.\n");
    
    add_item(({"drawer"}),
    "The drawer is wide and deep, directly below the "
    +"top table of the desk.\n");
    
    add_item(({"chair", "chairs"}),
    "The chair is of a thick walnut wood, with high "
    +"arms, reclining slightly "
    +"backwards and seemingly more apt for "
    +"thinking than actual work.\n");
    
    add_item(({"door"}),
    "The door is of a dark brown color, thick and "
    +"study, decorated with carvings "
    + "and scrawled letters hewn into the wood in frustration.\n");
    
    
    
    
    add_exit(FIREKNIVES_ROOMS_DIR + "b1.c", "west");

    reset_faerun_room();
}


/*
 * Function that allows the player to sit 
 */
int action_sit(string str)
{
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()))
    {
        if(this_player()->query_prop("_sitting_at_mentor_chair"))
        {
            write("But you are already sitting in your chair!\n");
            return 1;
        }   
        
        if(str == "in the chair" | str == "chair" | str == "in chair")
        {
            this_player()->catch_msg("You sit down in the comfortable "
            +"tall chair with the symbol of a pen carved on it.\n");
            
            say(QCTNAME(this_player()) + " sits down in the comfortable "
            +"tall chair with the symbol of a pen carved on it.\n");
            
            this_player()->add_prop("_sitting_at_mentor_chair", 1);
            
            this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
            +" in the comfortable tall chair with the symbol of a pen carved on it");
            return 1;
        }

        else
        {
            this_player()->catch_msg("Please 'sit in chair'.\n");
            return 1;
        }

        return 1;
    }
    
    write("This is the personal chair of the Inquisitor! You would rather "
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
        if(this_player()->query_prop("_sitting_at_mentor_chair"))
        {
            this_player()->catch_msg("You stand up and leave the "
            +"comfortable tall chair with the symbol of a pen carved on it.\n");
            
            say(QCTNAME(this_player())+" stands up from the comfortable "
            +"tall chair with the symbol of a pen carved on it.\n");
            
            this_player()->remove_prop("_sitting_at_mentor_chair");
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
    
    if(ob->query_prop("_sitting_at_mentor_chair"))
    {
        ob->catch_msg("You stand up and leave the "
        +"comfortable tall chair with the symbol of a pen "
        +"carved on it before leaving the room.\n");
        
        say(QCTNAME(ob)+" stands up from the comfortable "
        +"tall chair with the symbol of a pen "
        +"carved on it before leaving the room.\n");
        
        ob->remove_prop("_sitting_at_mentor_chair");
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
            WIZARD_ENTRY_MENTOR_LOG("wizard_entry_mentor_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives Mentor room.\n");
            
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
