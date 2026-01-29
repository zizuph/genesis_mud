/* /d/Faerun/guilds/vampires/obj/turn_paralyze.c
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

string turner_name;

void
remove_me()
{
	remove_object();
}


int
set_turner(object turner)
{
	turner_name = turner->query_real_name();
	
	return 1;
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
        environment(this_object())->catch_tell("Finally, you feel a great "
		+"weakness, limbs going entirely numb and all the heat of your body "
		+"drained away before your fast-beating heart goes into cardiac "
		+"arrest!\nYou die!\n");
        
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" dies.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("\n\nSuddenly, you sense your heart starts "
		+"to beat again!\nYou rise from the ground.\n");
        
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" suddenly awakens and rises from the ground.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer == 2)
    {
        environment(this_object())->catch_tell("While your "
        +"heart is beating again, you are no longer alive!\nYou have risen "
        +"as a Vampire - undead, hunter of the living, and you "
        +"sense a new strange sensation of the thirst for...Blood.\n\n");
        
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" is thirsty for...Blood.\n", 
        environment(this_object()));       
        
        setuid();
		seteuid(getuid());
		
		object shadow_lay;
        object shadow_occ;
        object shadow_racial;

		shadow_lay = clone_object(VAMPIRES_GUILD_DIR 
		+ "shadows/vampires_sh_lay.c");
        
		if (shadow_lay->shadow_me(environment(this_object()), "layman", "mage", 
		LAY_VAMPIRES_GUILD_NAME) != 1)
		{
			write("You try to become vampire spawns, but nothing happens.\n");
            remove_cutscene_paralyze();
			return;
		}
               
        shadow_racial = clone_object(VAMPIRES_GUILD_DIR 
		+ "shadows/vampires_sh_racial.c");
        
        if (shadow_racial->shadow_me(environment(this_object()), "race", "race", 
		RACE_VAMPIRES_GUILD_NAME) != 1)
		{
			write("You try to become vampire spawns racial, but nothing happens.\n");
            remove_cutscene_paralyze();
			return;
		}
        
        shadow_occ = clone_object(VAMPIRES_GUILD_DIR 
        + "shadows/vampires_sh_occ.c");

        if (shadow_occ->shadow_me(environment(this_object()), "occupational", "ranger", 
        OCC_VAMPIRES_GUILD_NAME) != 1)
        {
            write("You try to become a full vampire, but nothing happens!\n");
            return;
        }

        VAMPIRES_MAPPINGS->set_vampires_gauge(environment(this_object())->query_name(), 1451);
        VAMPIRES_MASTER->add_occ_vampires(environment(this_object())->query_name());
        VAMPIRES_MASTER->add_race_vampires(environment(this_object())->query_name());
		VAMPIRES_MASTER->add_lay_vampires(environment(this_object())->query_name());
        VAMPIRES_MAPPINGS->set_vampires_rank(environment(this_object())->query_name(), 1);        
        VAMPIRES_MAPPINGS->set_vampirespawn_timer(environment(this_object())->query_name(), 1);
        VAMPIRES_MAPPINGS->set_thirst_gauge(environment(this_object())->query_name(), 16);
        SIRE_MANAGER->set_sire(environment(this_object())->query_name(), turner_name);
        
        THRALL_MANAGER->remove_thrall(environment(this_object())->query_name());
        VAMPIRES_MAPPINGS->set_thrall_pool(environment(this_object())->query_name(), 3);
        
        int special;
        special = random(3) + 1;
        
        VAMPIRES_MAPPINGS->set_vampire_main_special(environment(this_object())->query_name(), special);
        
        // No longer a vampire seeker. We reset the progress.
        VAMPIRES_MAPPINGS->clean_vampires_seeker(environment(this_object())->query_name());
		
		environment(this_object())->set_skill(SS_ANATOMY, 100);
        
        environment(this_object())->add_prop(REMAIN_STATIONARY, 1);
                
       
        // Turned full vampires are only rewarded 1 point, and not 2        
        VAMPIRES_MAPPINGS->set_vampires_resilience(environment(this_object())->query_name(), 1);

		environment(this_object())->update_hooks();

		JOIN_LOG("join_log",
		"The individual " +environment(this_object())->query_name() 
		+" was turned into a full Vampire by "+turner_name+".\n");
        
        remove_cutscene_paralyze();
        
        return;
    }
    
    if (cutscene_timer == 3)
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
        case "v":
		case "open coffin":
        case "enter coffin":
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