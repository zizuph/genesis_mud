/*
 * /d/Faerun/guilds/vampires/obj/expel_obj.c
 *
 *
 * Coded by Nerull, 2020
 *
 */
inherit "std/object";
#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>

#define COFFIN_MANAGER   "/d/Faerun/guilds/vampires/master/coffin_manager.c"



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
expelme_vampire(string str)
{
    seteuid(getuid());
    
    object token;

    if (str == "vampirevampie")
    {
        write("You feel you are too weak to "
		+"keep existing in this undead form, and therefore "
		+"you slip into the void!\nYou are Destroyed!\n");
        
        VAMPIRES_MAPPINGS->clean_vampires_rank(this_player()->query_name());
		VAMPIRES_MAPPINGS->clean_weaponskill_selection(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampires_gauge(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_thirst_gauge(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampires_resilience(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampirespawn_timer(this_player()->query_name());
        
        VAMPIRES_MAPPINGS->clean_vamp_pathprogression(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vamp_agent(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vamp_title(this_player()->query_name());
 
		SIRE_MANAGER->remove_sire(this_player()->query_name());
	    THRALL_MANAGER->remove_thrall(this_player()->query_name());
		
        VAMPIRES_MAPPINGS->clean_vampire_main_special(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_ability_occ_1(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_ability_occ_2(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_ability_occ_3(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_ability_occ_4(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_ability_occ_5(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_ability_occ_progenitor(this_player()->query_name());
		VAMPIRES_MAPPINGS->clean_vampires_seeker(this_player()->query_name());
        VAMPIRES_MAPPINGS->clean_vampire_reputation(this_player()->query_name());
		
        VAMPIRES_MASTER->remove_lay_vampires(this_player()->query_name());
        VAMPIRES_MASTER->remove_nonxp_vampire(this_player()->query_name());
		VAMPIRES_MASTER->remove_race_vampires(this_player()->query_name());
        VAMPIRES_MASTER->remove_failed_vampire(this_player()->query_name());
        
        VAMPIRES_MASTER->remove_aging_check(this_player()->query_name());
               
        VAMPIRES_MASTER->remove_coven1_member(this_player()->query_name());
        VAMPIRES_MASTER->remove_coven2_member(this_player()->query_name());
        VAMPIRES_MASTER->remove_coven3_member(this_player()->query_name());
        
        VAMPIRES_MASTER->remove_coven1_master(this_player()->query_name());
        VAMPIRES_MASTER->remove_coven2_master(this_player()->query_name());
        VAMPIRES_MASTER->remove_coven3_master(this_player()->query_name());
        
        VAMPIRES_MASTER->remove_vamp_progenitor(this_player()->query_name());
        VAMPIRES_MASTER->remove_vamp_antediluvian(this_player()->query_name());
        VAMPIRES_MASTER->remove_vamp_methuselah(this_player()->query_name());
        VAMPIRES_MASTER->remove_vamp_elder(this_player()->query_name());
         
        this_player()->remove_skill(SS_ANATOMY);
       
	    // If the vampire is OCC
	    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()))
	    {
            this_player()->remove_cmdsoul("/d/Faerun/guilds/vampires/souls/vampires_guild_soul_occ");
			this_player()->remove_guild_occ();
		    this_player()->clear_guild_stat(SS_OCCUP);
		    VAMPIRES_MASTER->remove_occ_vampires(this_player()->query_name());
		}

        this_player()->remove_guild_lay();
		this_player()->remove_guild_race();
       
        this_player()->clear_guild_stat(SS_LAYMAN);
		this_player()->clear_guild_stat(SS_RACE);
       
        this_player()->remove_cmdsoul("/d/Faerun/guilds/vampires/souls/vampires_guild_soul_lay");
		this_player()->remove_cmdsoul("/d/Faerun/guilds/vampires/souls/vampires_guild_soul_race");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        COFFIN_MANAGER->remove_coffin(this_player()->query_real_name());
               
        this_player()->update_hooks();
        
        this_player()->set_hp(-1000);
        this_player()->do_die();
		
		LEAVE_LOG("leave_log",
        "The Vampire (Spawn) " +this_player()->query_name() 
        +" was permanently removed from the guild.\n");
        
        // We let the player stick at level 6 in case of later returns.
        VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), 6);
        
        if (!present("_seekercleanse_countdown_ob2", this_player()))
        {
            clone_object(VAMPIRES_GUILD_DIR +"obj/seekercleanse_countdown2_ob")->move(this_player(), 1);
        }
    
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

    add_action(expelme_vampire, "destroymevampire");
}
