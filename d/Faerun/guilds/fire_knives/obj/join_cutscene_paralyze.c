/* /d/Faerun/guilds/fire_knives/obj/join_cutscene_paralyze.c
 * 
 * Nerull 2018
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
object ruddock;

/*
 * Function name: remove_cutscene_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_cutscene_paralyze()
{
    environment(this_object())->catch_tell("Ruddock sizes you up and down, "
    +"scoffs, and begins to walk away, saying: And try not to get yourself "
    +"killed too fast... \nYou have joined the Fire Knives as an "
    +"Postulant!\nYou dare to move again.\n");
    
    
    tell_room(environment(environment(this_object())), "Ruddock sizes the "
    +"new Postulant "
    +environment(this_object())->query_name()+" up and down, scoffs, and "
    +"begins to walk away, saying: And try not to get yourself killed too "
    +"fast...\n", environment(this_object()));
    
    //environment(this_object())->add_prop(I_CAN_JOIN_FIREKNIVES2, 1);
    
    //environment(this_object())->command("pledge to brotherhood");
    
    ruddock->remove_object();
        
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
        environment(this_object())->catch_tell("You say: I pledge my "
        +"life to the Brotherhood, knowing it is no longer mine. I "
        +"am not free to dispose of it, and any shortcomings of mine "
        +"may require it as payment.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" says: I pledge my "
        +"life to the Brotherhood, knowing it is no longer mine. I "
        +"am not free to dispose of it, and any shortcomings of mine "
        +"may require it as payment.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("You say: I will stay "
        +"my blade from the flesh of an innocent, biting only that of "
        +"a marked individual either by deed, decree, or bounty.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" says: I will stay "
        +"my blade from the flesh of an innocent, biting only that of "
        +"a marked individual either by deed, decree, or bounty.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 2)
    {
        environment(this_object())->catch_tell("You say: I understand "
        +"that I bring upon myself the hate of both dead and living, woman "
        +"and child, man and beast, good and evil, and must be prepared "
        +"at all times to survive any attempt on my life.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" says: I understand that "
        +"I bring upon myself the hate of both dead and living, woman and "
        +"child, man and beast, good and evil, and must be prepared at all "
        +"times to survive any attempt on my life.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 3)
    {
        environment(this_object())->catch_tell("You say: Same as the "
        +"Brotherhood's weakness is its weakest assassin, so are any of my "
        +"relations a weakness of mine that could, and most likely will, "
        +"be exploited. Whoever associates with us associates with death.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" says: Same as the "
        +"Brotherhood's weakness is its weakest assassin, so are any of "
        +"my relations a weakness of mine that could, and most likely will, "
        +"be exploited. Whoever associates with us associates with death.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 4)
    {
        environment(this_object())->catch_tell("You say: What we learn, "
        +"experience, hear, speak, taste, feel, or see is for us alone. "
        +"Any disclosure of what is ours to any who isn't is under penalty "
        +"of permanent dispatch from life and discharge from service.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" says: What we learn, "
        +"experience, hear, speak, taste, feel, or see is for us alone. "
        +"Any disclosure of what is ours to any who isn't is under penalty "
        +"of permanent dispatch from life and discharge from service.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 5)
    {
        environment(this_object())->catch_tell("You say: We live to serve "
        +"the Brotherhood and each other, with the end goal of fulfilling "
        +"our duty to the contract always in sight. Whatsoever we invest "
        +"it - a single acquired item, knowledge or information gathered "
        +"and shared among us, improvement of our physical and mental "
        +"stature, words spoken and heard, and the fulfillment of our "
        +"missions - serves the Brotherhood which we all are a part of. "
        +"If any of us is found of an unlike mind, a permanent dispatch "
        +"from life and discharge from service will follow.\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" says: We live to serve "
        +"the Brotherhood and each other, with the end goal of fulfilling "
        +"our duty to the contract always in sight. Whatsoever we invest "
        +"it - a single acquired item, knowledge or information gathered "
        +"and shared among us, improvement of our physical and mental "
        +"stature, words spoken and heard, and the fulfillment of our "
        +"missions - serves the Brotherhood which we all are a part of. "
        +"If any of us is found of an unlike mind, a permanent dispatch "
        +"from life and discharge from service will follow.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 6)
    {
        if (!ruddock)
        {
            ruddock = clone_object(FIREKNIVES_GUILD_DIR + "npc/ruddock_join");
            ruddock->move(environment(environment(this_object())), 1);  
        }
        
        environment(this_object())->catch_tell("A bald muscular male human "
        +"arrives from the south and comes to a halt before you, "
        +"letting out a heavy sigh.\nThe bald muscular male human introduces "
        +"himself as Richard D. Ruddock, Master Assassin.\n");
    
        tell_room(environment(environment(this_object())), "A bald muscular "
        +"male human arrives "
        +"from the south and comes to a halt "
        +"before the postulant, letting out a heavy sigh.\nThe bald "
        +"muscular male human introduces "
        +"himself as Richard D. Ruddock, Master Assassin.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 7)
    {
        environment(this_object())->catch_tell("Ruddock looks up and "
        +"down at you, assessing you.\n");
    
        tell_room(environment(environment(this_object())), "Ruddock examines "
        +environment(this_object())->query_name()+" closely.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 8)
    {
        environment(this_object())->catch_tell("Ruddock mumbles: Best "
        +"we could find, I suppose...\n");
    
        tell_room(environment(environment(this_object())), "Ruddock "
        +"mumbles: Best we could find, I suppose...\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 9)
    {
        environment(this_object())->catch_tell("Ruddock looks at "
        +"you directly in the eyes "
        +"and says: So you are to become a trainee...\n");
    
        tell_room(environment(environment(this_object())), "Ruddock looks "
        +"at "+environment(this_object())->query_name()
        +" directly in the eyes, "
        +"saying: So you are to become a trainee...\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 10)
    {
        object guilditem;
        
        guilditem = clone_object(FIREKNIVES_GUILD_DIR + "obj/dark_suit");
        guilditem->move(environment(this_object()), 1);  
        
        environment(this_object())->catch_tell("Ruddock tosses "
        +"a "+guilditem->short()+" to you, saying: You're now on the bottom of "
        +"the totem pole around here. Your job is to train "
        +"and do as we say.\n");
    
        tell_room(environment(environment(this_object())), "Ruddock tosses "
        +"a "+guilditem->short()+" to "
        +environment(this_object())->query_name()
        +", saying: You're now on the bottom "
        +"of the totem pole around here. Your job is to train and "
        +"do as we say..\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 11)
    {
        environment(this_object())->catch_tell("Ruddock continues: You "
        +"took an oath, and you vouched for that with your life. I "
        +"don't think "
        +"I need to tell you what the price is if you fail...\n");
    
        tell_room(environment(environment(this_object())), "Ruddock says "
        +"to "+environment(this_object())->query_name()+": You took an oath, "
        +"and you vouched for that with "
        +"your life. I don't think I need to tell you what the price is "
        +"if you fail...\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 12)
    {
        environment(this_object())->catch_tell("Ruddock crosses his arms "
        +"on his chest and says: Some ground rules around here. First, as I "
        +"said, do as you're told. Second, respect your elders. Third, own "
        +"up to your mistakes. You will make them, I assure "
        +"you, and it would "
        +"be best if you faced the consequences willingly rather than making "
        +"us push your face onto them.\n");
    
        tell_room(environment(environment(this_object())), "Ruddock "
        +"crosses his "
        +"arms on his chest and says: Some ground rules around "
        +"here. First, as I "
        +"said, do as you're told. Second, respect your "
        +"elders. Third, own up "
        +"to your mistakes. You will make them, I assure you, and "
        +"it would be "
        +"best if you faced the consequences willingly rather than making us "
        +"push your face onto them.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 13)
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
    +"has rendered you unable to move a muscle while you do the pledge.\n");
    
    set_name(({"join_cutscene_paralyze"}));
    
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