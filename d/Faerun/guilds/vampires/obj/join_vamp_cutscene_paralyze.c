/* /d/Faerun/guilds/vampires/obj/join_vamp_cutscene_paralyze.c
 * 
 * Nerull 2020
 */

inherit "/std/paralyze.c";

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



void remove_cutscene_paralyze();

int cutscene_timer = 0;
object ruddock;

void
remove_me()
{
	remove_object();
}

/*
 * Function name: remove_cutscene_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_cutscene_paralyze()
{
	setuid();
    seteuid(getuid());
	
    write("You feel you can move again.\n");

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
        environment(this_object())->catch_tell("\nExcruciating pain "
        +"is paired with a sudden and acute lack of blood "
        +"flowing to your brain, placing you in a strange and "
        +"unhinged paralysis!\n\n");
    }
    
    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("You hear a voice "
        +"behind you, saying: So what have we here? A lost mortal "
        +"who accidentally walked into my grasp, or a mortal who was "
        +"clever enough to solve my riddles?\nYou hear the voice "
        +"behind you snickering ever so slightly.\n");
    }
    
    if (cutscene_timer == 2)
    {
        environment(this_object())->catch_tell("You hear a voice behind "
        +"you, saying: One thing is certain, mortal...your death "
        +"is now before you!\nYou hear a cackling laughter "
        +"behind you.\n");
    }
    
    if (cutscene_timer == 3)
    {
        environment(this_object())->catch_tell("You hear a voice behind "
        +"you, saying: You will serve me in the darkness, forever at my "
        +"beck and call, doing as I command! I do very much hope that "
        +"you have granted your friends and family a tearful farewell, "
        +"for they, now, have become your enemies!\n");
    }
    
    if (cutscene_timer == 4)
    {
        environment(this_object())->catch_tell("You hear a voice behind "
        +"you, saying: To the darkness I will bind you! You shall "
        +"not see the light of the sun again without extreme pain and "
        +"personal suffering; all manifestations of egotistical, "
        +"self-aggrandizing forces shall badger you until the end "
        +"of time. Others of your kind will seek you out and destroy "
        +"you, and nowhere exists for you to find solace or rest "
        +"in your coffin!\n");
    }
    
    if (cutscene_timer == 5)
    {
        environment(this_object())->catch_tell("You hear a voice behind "
        +"you, saying: Now...the time is here!\nYou hear a cackling "
        +"laughter behind you.\n");
    }
    
    if (cutscene_timer == 6)
    {
        environment(this_object())->catch_tell("Suddenly, piercingly, you feel "
        +"a pair of powerful fangs penetrate the skin of your neck! "
        +"Your delirium and hysteria increase as you feel your blood, "
        +"the very essence of your life-force, being rapidly siphoned "
        +"from your body! Your heart starts to pound harder and "
        +"faster in your chest in an attempt to compensate for "
        +"the overwhelming loss of blood in your body!\n");
    }
    
    if (cutscene_timer == 7)
    {
        environment(this_object())->catch_tell("At long last a great "
        +"weakness befalls you, leaving your limbs and extremities " 
        +"entirely numb and cold. An agonizing spasm grips your "
        +"chest as your heart convulses into cardiac arrest!\n");
    }
    
    if (cutscene_timer == 8)
    {
        environment(this_object())->catch_tell("Your heart gifts you "
        +"one final flutter before becoming motionless and still "
        +"allowing you to feel your consciousness beginning to drift "
        +"away into eternal slumber. As you slip away, an "
        +"indiscernible voice mumbles something incoherent and "
        +"you taste something coppery on your tongue, causing "
        +"a distant memory of the taste of blood.\n");
    }
    
    if (cutscene_timer == 9)
    {
        environment(this_object())->catch_tell("\n\nYou die!\n\nTime passes...\n\n");
    }
    
    if (cutscene_timer == 10)
    {
        environment(this_object())->catch_tell("\n\nSuddenly, a pounding echo "
        +"reverberates in your ears as your heart begins to beat!\n");
    }
    
    if (cutscene_timer == 11)
    {
        environment(this_object())->catch_tell("In startled shock, you "
        +"open your eyes, as if to awaken from a nightmare! You are " 
        +"filled with life renewed! All around you can be seen dirt "
        +"and fragments of gravel and stone, as though you have been "
        +"buried without a coffin... buried alive!\n");
    }
    
    if (cutscene_timer == 12)
    {
        environment(this_object())->catch_tell("Shock and horror consume "
        +"you as you realize that while your heart is beating again, you "
        +"are no longer among the living. You have become a Vampire "
        +"Spawn, one of undead, dead but not dead; a hunter of the "
        +"living. You are overcome with a strange new "
        +"sensation, an undeniable thirst... for blood.\n\n");
        
        setuid();
		seteuid(getuid());
		
		object shadow_lay;
        object shadow_racial;

		shadow_lay = clone_object(VAMPIRES_GUILD_DIR 
		+ "shadows/vampires_sh_lay.c");

		if (shadow_lay->shadow_me(environment(this_object()), "layman", "mage", "Vampires of Faerun") != 1)
		{
			write("You try to join the vampire spawns (layman), but nothing happens.\n");
            remove_cutscene_paralyze();
			return;
		}
        
        shadow_racial = clone_object(VAMPIRES_GUILD_DIR 
		+ "shadows/vampires_sh_racial.c");
        
        if (shadow_racial->shadow_me(environment(this_object()), "race", "race", "Vampires of Faerun") != 1)
		{
			write("You try to join the vampire spawns (race), but nothing happens.\n");
            remove_cutscene_paralyze();
			return;
		}

        VAMPIRES_MASTER->add_race_vampires(environment(this_object())->query_name());
		VAMPIRES_MASTER->add_lay_vampires(environment(this_object())->query_name());
		VAMPIRES_MAPPINGS->set_vampires_rank(environment(this_object())->query_name(), 1);
		VAMPIRES_MAPPINGS->set_vampires_gauge(environment(this_object())->query_name(), 10);
        VAMPIRES_MAPPINGS->set_vampirespawn_timer(environment(this_object())->query_name(), 1);      
		VAMPIRES_MAPPINGS->set_thirst_gauge(environment(this_object())->query_name(), 16);
		SIRE_MANAGER->set_sire(environment(this_object())->query_name(), "vorador");
        
        THRALL_MANAGER->remove_thrall(environment(this_object())->query_name());
        VAMPIRES_MAPPINGS->set_thrall_pool(environment(this_object())->query_name(), 3);
        
        int special;
        special = random(3) + 1;
        
        VAMPIRES_MAPPINGS->set_vampire_main_special(environment(this_object())->query_name(), special);
        
        // No longer a vampire seeker. We reset the progress.
        VAMPIRES_MAPPINGS->clean_vampires_seeker(this_player()->query_name());
		
		environment(this_object())->set_skill(SS_ANATOMY, 50);

		environment(this_object())->update_hooks();
        
        environment(this_object())->move_vampire();

		JOIN_LOG("join_log",
		"The individual " +environment(this_object())->query_name() 
		+" joined the Vampire Spawns.\n");
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
    set_fail_message("You are paralyzed, and can't move!\n");
    
    set_name(({"join_vamp_cutscene_paralyze"}));
    
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