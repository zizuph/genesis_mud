/* /d/Faerun/guilds/fire_knives/obj/fullmember_cutscene_paralyze.c
 * 
 * Nerull 2019
 */

#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

inherit "/std/paralyze.c";

void remove_cutscene_paralyze();

int cutscene_timer = 0;
object kyri;

/*
 * Function name: remove_cutscene_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_cutscene_paralyze()
{
	environment(this_object())->catch_tell("Kyri says: "
	+"Congratulations and welcome to "
    +"the Brotherhood as a full member.\nKyri walks away to "
	+"the south.\n");
        
    tell_room(environment(environment(this_object())), "Kyri says: "
    +"Congratulations, and welcome to the Brotherhood as a full "
	+"member.\nKyri walks "
    +"away to the south.\n", environment(this_object()));
	
    kyri->remove_object();
	
	FIREKNIVES_MASTER->add_guild_fullmember(environment(this_object())->query_name());
	FIREKNIVES_MASTER->remove_guild_trainee(environment(this_object())->query_name());
        
    remove_object();
}
 
 
 /*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
cutscene_effect()
{
    setuid();
    seteuid(getuid());

    if (cutscene_timer == 0)
    {
        environment(this_object())->catch_tell("A slim stern-eyed female human "
        +"approaches from the shadows and presents herself as: Kyri, Deadly "
        +"Assassin.\nShe walks around you and stand in front of your feet.\n");
    
        tell_room(environment(environment(this_object())), "A slim stern-eyed "
        +"female human approaches from the shadows and presents herself "
        +"as: Kyri, Deadly Assassin.\nShe walks around the "
        +environment(this_object())->query_name()+" and stand in front of "
        +environment(this_object())->query_objective()+".\n", 
        environment(this_object()));      

        if (!kyri)
        {
            kyri = clone_object(FIREKNIVES_GUILD_DIR + "npc/trainee_trainer");
            kyri->move(environment(environment(this_object())), 1);  
        }        
    }
    
    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("You are desperately gasping for "
        +"air while rolling around on the ground in pain.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" is desperately gasping "
        +"for air while rolling around on the ground in pain.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 2)
    {
        environment(this_object())->catch_tell("Kyri says: The fight is over. Do "
        +"you remember your Oath, trainee?\n");
    
        tell_room(environment(environment(this_object())), "Kyri says: The "
        +"fight is over. Do "
        +"you remember your Oath, trainee?\n", 
        environment(this_object()));       
    }
    
     if (cutscene_timer == 3)
    {
        environment(this_object())->catch_tell("You stutter desperately with "
        +"interruptions: I.. Will stay m.. my blade from.. The flesh of an "
        +"in..nocent, biting.. only that of a marked individual either by "
        +"deed, decree or bounty.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" stutters desperately with "
        +"interruptions::  I.. Will stay m.. my blade from.. The flesh of an "
        +"in..nocent, biting.. only that of a marked individual either by "
        +"deed, decree or bounty.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 4)
    {
        environment(this_object())->catch_tell("Kyri nods in response.\n");
    
        tell_room(environment(environment(this_object())), "Kyri nods in "
        +"response.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 5)
    {
        environment(this_object())->catch_tell("Kyri reaches out a hand and "
        +"helps you back to your feet and says: You have now completed your "
        +"final trial, following orders even in the face of certain death.\n");
    
        tell_room(environment(environment(this_object())), "Kyri reaches out "
        +"a hand and "
        +"helps "+environment(this_object())->query_name()+" back to "
        +environment(this_object())->query_possessive()
        +" feet and says: You have now completed your "
        +"final trial, following orders even in the "
        +"face of certain death.\n", environment(this_object())); 
    }
    
    
     if (cutscene_timer == 6)
    {
        environment(this_object())->catch_tell("Kyri says: You were "
        +"expected to fail but you didn't. You showed us that you have "
        +"what it takes and that you are worthy to become our equal. "
        +"From this day you will have access to our advanced training "
        +"and you have proven yourself enough to be called an equal. "
        +"You now stand here amongst equals. Take a good look at your "
        +"brothers and sisters in arms because they are the ones who "
        +"will have your back, just as you will have theirs.\n");
    
        tell_room(environment(environment(this_object())), "Kyri "
        +"says: You were "
        +"expected to fail but you didn't. You showed us that you have "
        +"what it takes and that you are worthy to become our equal. "
        +"From this day you will have access to our advanced training "
        +"and you have proven yourself enough to be called an equal. "
        +"You now stand here amongst equals. Take a good look at your "
        +"brothers and sisters in arms because they are the ones who "
        +"will have your back, just as you will have theirs.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 7)
    {
        remove_cutscene_paralyze();
        
        return;
    }
     
    cutscene_timer = cutscene_timer + 1;
    
    return;
}
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("The severity of this situation "
    +"has rendered you unable to move a muscle.\n");
    
    set_name(({"fullmember_cutscene_paralyze"}));
    
    set_alarm(1.0, 10.0, &cutscene_effect());
}


/*
 * Function name: stop
 * Description:   Here all commands the player gives comes.
 * Argument:      str - The extra string the player sent.
 */
varargs int
stop(string str)
{
    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())    
    return 0;

    if (wildmatch("'*", query_verb()))
    return 0;

    switch (query_verb())
    {
        // Eyes:
        case "l":
        case "look":
        case "exa":
        case "who":
        case "list":
        case "v":
        case "vitals":
        case "examine":
        // meta-commands
        case "bug":
        return 0;
        break;
        default:
            if (fail_message)
                this_player()->catch_msg(fail_message);
            
            if (!this_player()->query_wiz_level())
                return 1;
            break;
    }
    
    write("Since you are a wizard this paralyze won't affect you.\n");
    return 0;
}


void init()
{
    ::init();
}