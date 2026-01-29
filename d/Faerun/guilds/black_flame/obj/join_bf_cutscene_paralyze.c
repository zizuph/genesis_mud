/* /d/Faerun/guilds/dr/obj/join_bf_cutscene_paralyze.c
 * 
 * Nerull 2022
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
        environment(this_object())->catch_tell("\nYou feel something "
		+"stirring within yourself.\nYou are paralyzed!\n");
    }
		
	if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("\nA searing power "
		+"courses through your very being.\n");
    }
	
	if (cutscene_timer == 2)
    {
        environment(this_object())->catch_tell("\nSuddenly the power "
		+"manifests. From the very pores of the skin on your forearms, "
		+"small black flames start to flicker.\n");
    }
	
	
	if (cutscene_timer == 3)
    {
        environment(this_object())->catch_tell("\nThe flames "
		+"intensify. Black flames now writhe around your forearms, "
		+"like living beings with a will of their own. Strangely, "
		+"you feel no pain, but a connection with them.\n");
    }
	
	
	if (cutscene_timer == 4)
    {
        environment(this_object())->catch_tell("\nAs you stand "
		+"looking at the flames of your arm, a dark-clad male "
		+"human approaches and hands you a bandolier. 'You are "
		+"going to need this', he says and then walks away.\nThe flames "
		+"dies out.\n");
		
		setuid();
		seteuid(getuid());
		
		object shadow_lay;

		shadow_lay = clone_object(BF_GUILD_DIR 
		+ "shadows/bf_sh_lay.c");

		if (shadow_lay->shadow_me(environment(this_object()), "layman", "ranger", LAY_BF_GUILD_NAME) != 1)
		{
			write("You try to join, but nothing happens.\n");
            remove_cutscene_paralyze();
			return;
		}		
        		
		BF_MASTER->add_lay_bf(environment(this_object())->query_name());
		
		write("You join the Order of the Black Flame.\n");

        tell_room(environment(environment(this_object())), environment(this_object())->query_name()
        + " joined the Order of the Black Flame!\n", environment(this_object()));
		
		object guilditem;
        
        guilditem = clone_object(BF_GUILD_DIR + "obj/bandolier");
        guilditem->move(environment(this_object()), 1);  
    }
	
	
    if (cutscene_timer == 5)
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
    
    set_name(({"join_bf_cutscene_paralyze"}));
    
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