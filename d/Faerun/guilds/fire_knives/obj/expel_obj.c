/*
 * /d/Faerun/guilds/fire_knives/obj/expel_obj.c
 *
 *
 * Coded by Nerull, 2018
 *
 */

#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "std/object";

void
remove_me()
{
    remove_object();
    
    return;
}

/*
 * Function name: create_monster()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("expel_obj");
    
    add_prop(OBJ_I_INVIS, 100);
    
    set_no_show();

    set_short("expel_obj");
    set_long("expel_obj.\n");

    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_HEIGHT, 1);
    
    set_alarm(10.0, 0.0, &remove_me());
}


int
expelme_fireknife(string str)
{
    seteuid(getuid());
    
    object token;
    object bleed_to_death_obj;

    if (str == "the fire knives outfit")
    {
		
		// Npcs dont die.
		if (this_player()->query_npc() == 1)
		{
			return 1;
		}
		
        tell_room(environment(this_player()), "You see a bald muscular male "
        +"human walk up to "
        +this_player()->query_name()+", placing a hand on "
        +this_player()->query_possessive()+" shoulder. There is a flash "
        +"of steel between "+this_player()->query_name()+" legs and a pool " 
        +"of blood starts forming quickly. The bald muscular human leans in "
        +"and whispers something to "+this_player()->query_name()
        +" before turning "
        +"around and walking away.\n", this_player());
        
        write("You feel a hand on your shoulder followed by a sharp "
        +"pain on the inside of your thigh. Warm liquid starts to pour "
        +"down your thigh as you hear the gravelly voice of "
        +"Richard D. Ruddock whispering in your "
        +"ear 'Goodnight, princess.' and you turn around to face him "
        +"as he backs "
        +"off and walks away. Your arms start to feel heavy and "
        +"your vision starts "
        +"to blur as you fall to your knees from the loss of "
        +"blood.\nYou are no longer "
        +"a member of the Fire Knives.\n");

        this_player()->remove_skill(SS_ART);
     
        this_player()->remove_guild_occ();
       
        this_player()->clear_guild_stat(SS_OCCUP);
       
        this_player()->remove_cmdsoul(FIREKNIVES_GUILD_DIR 
        +"souls/fireknives_guild_soul");

        FIREKNIVES_MAPPINGS->clean_assassin_rank(this_player()->query_name());
        FIREKNIVES_MAPPINGS->clean_assassin_gauge(this_player()->query_name());
        
        FIREKNIVES_MASTER->remove_occ_fireknife(this_player()->query_name());
        FIREKNIVES_MASTER->remove_occ_mentor_fireknife(this_player()->query_name());
        FIREKNIVES_MASTER->remove_occ_thefist_fireknife(this_player()->query_name());
        FIREKNIVES_MASTER->remove_occ_boss_fireknife(this_player()->query_name());
		FIREKNIVES_MASTER->remove_guild_fullmember(this_player()->query_name());
	    FIREKNIVES_MASTER->remove_guild_trainee(this_player()->query_name());
        
        this_player()->set_default_start_location(this_player()->query_def_start());
        
        this_player()->update_hooks();

        if (objectp(token = present("_fireknife_token", this_player())))
        {
            write("Your "+token->query_short()+" crumbles to dust.\n");
            tell_room(environment(this_player()), "The "+
            token->query_short()+" of "+
            QTNAME(this_player())+" crumbles to dust.\n", this_player());
            token->remove_object();
        }
        
        bleed_to_death_obj = clone_object(FIREKNIVES_GUILD_DIR 
        + "obj/bleed_to_death_obj");
        bleed_to_death_obj->move(this_player(), 1);
		
		EXPELLED_LOG("expelled_log",
        "The member "+this_player()->query_name()
        +" was expelled from the brotherhood!\n");

        remove_object();

        return 1;
    }
    
    return 0;
}


/*
 * Function name: init_living()
 * Description  : Enables commands for the player when encountering
 *                this npc.
 */
void init()
{
    ::init();

    add_action(expelme_fireknife, "betray");
}
