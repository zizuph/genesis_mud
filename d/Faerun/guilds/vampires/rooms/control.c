/* /d/Faerun/guilds/vampires/rooms/control.c
 *
 * Nerull 2019
 *
 * THIS ROOM IS ONLY FOR TESTING!
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <mail.h>
#include "../guild.h";


int fixme = 0;
int immfixme = 1;

#define COFFIN_MANAGER   "/d/Faerun/guilds/vampires/master/coffin_manager.c"

/*
 * Function name: do_join()
 * Description  : The function that adds a member of the guild.
 *
 */
int do_join(string str)
{
    object shadow_occ;
    object shadow_lay;
    object shadow_racial;
    
    object tokena;
	
	string *coffins;
    
    setuid();
    seteuid(getuid());
        
    if (str == "vampires")
    {   
        setuid();
		seteuid(getuid());

        if (VAMPIRES_MASTER->is_lay_vampires(this_player()->query_name()))
        {
            write("You are already a member of the vampires lay.\n");
            return 1;
        }
        
        /*if (this_player()->query_average() < REQ_AVG_LAY)
        {
            write("You feel you are not quite yet to join the "
            +"vampire spawns. Return later when you have grown some more.\n");
            
            return 1;        
        }*/
        
        if (this_player()->query_guild_name_lay())
        {
            write("Return when you have a vacant layman slot.\n");
                
            return 1;
        }
        
        if (this_player()->query_guild_name_race())
        {
            write("Return when you have a vacant racial slot.\n");
                
            return 1;
        }

        shadow_racial = clone_object(VAMPIRES_GUILD_DIR 
		+ "shadows/vampires_sh_racial.c");
        
        shadow_lay = clone_object(VAMPIRES_GUILD_DIR 
        + "shadows/vampires_sh_lay.c");
        
        /*if (shadow_racial->shadow_me(this_player(), "race", "race", 
		RACE_VAMPIRES_GUILD_NAME) != 1)
		{
			write("You try to join the vampire spawns (race), but nothing happens.\n");
			return 1;
		}*/

        if (shadow_lay->shadow_me(this_player(), "layman", "mage", 
        LAY_VAMPIRES_GUILD_NAME) != 1)
        {
            write("You try to join the vampire spawns (layman), but nothing happens.\n");
            return 1;
        }
        
        write("Joining check, OK.\n");
        return 1;

        this_player()->add_prop(REMAIN_STATIONARY, 1);

        VAMPIRES_MASTER->add_race_vampires(this_player()->query_name());
        VAMPIRES_MASTER->add_lay_vampires(this_player()->query_name());
        VAMPIRES_MAPPINGS->set_vampires_rank(this_player()->query_name(), 1);
		VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), 10);
        VAMPIRES_MAPPINGS->set_vampirespawn_timer(this_player()->query_name(), 1);        
		VAMPIRES_MAPPINGS->set_thirst_gauge(this_player()->query_name(), 16);
        SIRE_MANAGER->set_sire(this_player()->query_name(), "vorador");
        
        int special = random(3) + 1;
        
        VAMPIRES_MAPPINGS->set_vampire_main_special(this_player()->query_name(), special);
        
		this_player()->set_skill(SS_ANATOMY, 30);
		
		this_player()->update_hooks();
      
        JOIN_LOG("join_log",
        "The individual " +this_player()->query_name() 
        +" joined the Vampire Spawns.\n");
		
		write("You joined the Vampire Spawns.\n");
		
        return 1;
    }
    
    write("Join what? the vampires?\n");
            
    return 1;
}


/*int do_join_race(string str)
{
    object shadow;
    
    setuid();
    seteuid(getuid());
        
    if (str == "vampiresrace")
    {   
        setuid();
		seteuid(getuid());

        if (this_player()->query_guild_name_race())
        {
            write("Return when you have a vacant racial slot.\n");
                
            return 1;
        }

        shadow = clone_object(VAMPIRES_GUILD_DIR 
		+ "shadows/vampires_sh_racial.c");
        
        if (shadow->shadow_me(this_player()), "race", "fighter", 
		RACE_VAMPIRES_GUILD_NAME) != 1)
		{
			write("You try to join the vampire spawns, but nothing happens..\n");
			return 1;
		}

		this_player()->update_hooks();
      
        JOIN_LOG("join_log",
        "The individual " +this_player()->query_name() 
        +" joined the Vampire Spawns (RACE).\n");
		
		write("You joined the Vampire Spawns (RACE).\n");
		
        return 1;
    }
    
    write("Join what? the vampiresrace?\n");
            
    return 1;
}*/


/*
 * Function name: do_leave()
 * Description  : The function that removes a member of the guild.
 *
 */
int
do_leave(string str)
{
    object emblem;

    if (str != "vampires")
    {
        write("Do 'leave vampires' if you want to "
        +"flee from the Vampires!\n");
        return 1;
    }
	
	/*if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
	{
		if (VAMPIRES_MASTER->is_lay_vampires(this_player()->query_name()) == 0)
		{
			write("You are neither a vampire spawn nor a vampire!\n");
            return 1;
		}
	}*/

	VAMPIRES_MAPPINGS->clean_vampires_rank(this_player()->query_name());
    VAMPIRES_MAPPINGS->clean_weaponskill_selection(this_player()->query_name());
    VAMPIRES_MAPPINGS->clean_vampires_gauge(this_player()->query_name());
    VAMPIRES_MAPPINGS->clean_thirst_gauge(this_player()->query_name());
    VAMPIRES_MAPPINGS->clean_vampires_resilience(this_player()->query_name());
    VAMPIRES_MAPPINGS->clean_vampirespawn_timer(this_player()->query_name());
    
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
    
    //this_player()->set_hp(-1000);
    //this_player()->do_die();
    
     CREATE_MAIL("Destruction", "Vampires", this_player()->query_name(), "",
                "Vorador has removed you from his pool of vampire "
                +"spawns due to lack of satisfactory activity.\n");
	
	return 1;
}


int occ_ready(string str)
{
	if (str == "ready")
	{
		VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), 1450);
	
	    write("Set lay vampire gauge to occ ready (1450).\n");
	
	    return 1;
	}
	
	return 0;
}


int reduce_gauge(string str)
{
	if (str == "age")
	{      
        int downi = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
        
        if (downi <= 1)
        {
            write("Age is at level 1 already.\n");
            
            return 1;
        }
        
        downi = downi - 1;
               
		VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), downi);
        
        write("Decrease age -1.\n");
	
	    return 1;
	}
	
	return 0;
}


int increase_gauge(string str)
{
	if (str == "age")
	{      
        int downia = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
        
        /*if (downia > 300)
        {
            write("Age is at level 300 already.\n");
            
            return 1;
        }*/
        
        downia = downia + 1;
               
		VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), downia);
        
        write("Increase age 1.\n");
	
	    return 1;
	}
	
	return 0;
}



int decrease_seeker_gauge(string str)
{
	if (str == "seeker gauge")
	{
		int down = VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name());
        
        if (down <= 1)
        {
            write("Seeker is at level 1 already.\n");
            
            return 1;
        }
        
        down = down - 1;
               
		VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), down);
        
        write("Decrease seeker gauge -1.\n");
	
	    return 1;
	}
	
	return 0;
}


int increase_seeker_gauge(string str)
{
	if (str == "seeker gauge")
	{
        int up = VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name());
        
        if (up >= 7)
        {
            write("Seeker is at level 7 already.\n");
            
            return 1;
        }
        
        up = up + 1;
        
		VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), up);
	
	    write("Increase seeker gauge +1.\n");
	
	    return 1;
	}
	
	return 0;
}


int fill_thirst(string str)
{
	if (str == "thirst")
	{
		VAMPIRES_MAPPINGS->set_thirst_gauge(this_player()->query_name(), 1000);
	
	    write("Set 1000 in thirst.\n");
	
	    return 1;
	}
	
	return 0;
}


int fill_immpoints(string str)
{
	if (str == "immortality")
	{
		VAMPIRES_MAPPINGS->set_vampires_resilience("Silon", 2);
	
	    write("Set 1immportalitypoint.\n");
	
	    return 1;
	}
	
	return 0;
}


int increase_vampage(string str)
{
	if (str == "age")
	{
		
	
	    write("Increase age with 100 hours.\n");
        
        int member_gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
        
        int increase_100;
        
        increase_100 = member_gauge + 100;
        
        VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), increase_100);
	
	    return 1;
	}
	
	return 0;
}


int drain_thirst(string str)
{
	if (str == "thirst")
	{
		VAMPIRES_MAPPINGS->set_thirst_gauge(this_player()->query_name(), 2);
	
	    write("Set 2 in thirst.\n");
	
	    return 1;
	}
	
	return 0;
}


int do_nullifykick(string str)
{
	if (str == "kick")
	{
        VAMPIRES_MASTER->remove_failed_vampire(this_player()->query_name());
            
        write("You remove yourself from kicking.\n");
            
        return 1;
    }
	
	return 0;
}


int set_correction(int i)
{
    fixme = i;
}


int query_correction()
{
    return fixme;
}


int query_blaph()
{
    if (present("_vamppresence2_53263", this_object()))
    {
        write("It's here.\n");
        return 1;
    }
    
    write("Nothing here.\n");
    return 1;
}


int do_flagme()
{
    VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), 7);
        
    write("You flag yourself for Vampire testing.\n");
        
    return 1;
}


int do_fixme()
{
    if (fixme > 0)
    {        
        int q_gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
        
        int increase_100;
        
        q_gauge = q_gauge + fixme;
        
        VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), q_gauge);
        
        write("Correction in age performed.\n");
        
        fixme = 0;
                    
        return 1;
    }
    
    write("Correction in points not set\n");
	
	return 0;
}


int do_fixme_immpoint()
{
    if (immfixme > 0)
    {        
        int imm_gauge = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name());
        
        int imm_increase;
        
        imm_increase = 2;
        
        imm_gauge = imm_gauge + imm_increase;
        
        VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), imm_gauge);
        
        write("Correction in immpoints fixed.\n");
        
        immfixme = 0;
                    
        return 1;
    }
    
    write("Correction in immpoints not set\n");
	
	return 0;
}


int check_paintings_status(string str)
{
	if (str == "paintings status")
	{
        int p1 = VAMPIRES_MASTER->query_box1_active();
        int p2 = VAMPIRES_MASTER->query_box2_active();
        int p3 = VAMPIRES_MASTER->query_box3_active();
        int p4 = VAMPIRES_MASTER->query_box4_active();
        int p5 = VAMPIRES_MASTER->query_box5_active();
        int p6 = VAMPIRES_MASTER->query_box6_active();
        
        write("Painting 1: "+p1+".\n");
        write("Painting 2: "+p2+".\n");
        write("Painting 3: "+p3+".\n");
        write("Painting 4: "+p4+".\n");
        write("Painting 5: "+p5+".\n");
        write("Painting 6: "+p6+".\n");
	
	    return 1;
	}
	
	return 0;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Vampire Control room");
    
    set_long("Vampire Control room.\nFUNCTIONS:\n---------\n");
    //+" - join vampires\n"
    //+" - leave vampires\n"
    //+" - occ ready\n"
    //+" - add immortality (add 200 points)\n"
    //+" - boost age (add 100 hours in age)\n"
    //+" - fill thirst\n"
    //+" - drain thirst\n"
    //+" - increase seeker gauge\n"
    //+" - decrease seeker gauge\n"
   // +" - flag me (set to level 8 seeker)\n");
    //+" - 1. flagme\n"
    //+" - 2. fixme\n");
    //+" - check paintings status\n");
    
    /*clone_object("/d/Faerun/guilds/vampires/obj/vamp_painting_test1.c")->move(this_object(), 1);
    clone_object("/d/Faerun/guilds/vampires/obj/vamp_painting_test2.c")->move(this_object(), 1);
    clone_object("/d/Faerun/guilds/vampires/obj/vamp_painting_test3.c")->move(this_object(), 1);
    clone_object("/d/Faerun/guilds/vampires/obj/vamp_painting_test4.c")->move(this_object(), 1);
    clone_object("/d/Faerun/guilds/vampires/obj/vamp_painting_test5.c")->move(this_object(), 1);
    clone_object("/d/Faerun/guilds/vampires/obj/vamp_painting_test6.c")->move(this_object(), 1);*/
    
    add_exit("/w/nerull/workroom", "east");

    
    
    reset_faerun_room();
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

    add_action(do_join, "join");
	add_action(do_leave, "leave");
    
   
    add_action(do_nullifykick, "nullify");
	
	add_action(occ_ready, "occ");
	add_action(fill_thirst, "fill");
	add_action(drain_thirst, "drain");
    
    add_action(fill_immpoints, "add");
    add_action(increase_vampage, "increase");
    add_action(reduce_gauge, "reduce");
    add_action(increase_gauge, "grow");
    
    add_action(do_flagme, "flagme");
    add_action(do_fixme, "fixme");
    
    add_action(do_fixme_immpoint, "immpointfix");
	
    add_action(increase_seeker_gauge, "increase");
	add_action(decrease_seeker_gauge, "decrease");
    
    add_action(check_paintings_status, "check");
}

