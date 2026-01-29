/* /d/Gondor/guilds/defenders/rooms/join.c
 *
 * Defenders of the Westlands, guildhall.
 *
 * Nerull, 2016
 *
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "defs.h";
#include "../guild.h";

inherit DEF_STD_ROOM;


public int
block_nonmembers()
{
	if (DEF_MASTER->is_defender(this_player()->query_name()))
	{
		
		write("Welcome home, Defender of the Westlands!\n");

		return 0;
	}

	if (this_player()->query_wiz_level())
	{
		write("Welcome, wizard!\n");
		return 0;
	}

	write("Only members of the Defenders of the Westlands can "
	+"proceed any further!\n");

	return 1;
}

/*
 * Function name: create_demon_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_def_room()
{
    set_short("joiningroom");
    set_long("This is the joiningroom.\n");

    add_exit(DEF_GUILDDIR + "rooms/h1_1",   "south", block_nonmembers);

	add_item(({"stuff"}), "stuff.\n");

    reset_room();
}



void
reset_room()
{
    
}


int
do_rsign(string str)
{
	if (str == "sign")
    {
	    write("    0----------------------------------0 \n");
	    write("    |                                  |\n");
	    write("    |                                  |\n");
	    write("    | Demonologists, joining procedure.|\n");
	    write("    | ================================ |\n");
	    write("    |                                  |\n");
	    write("    | Hopefuls may, if they dare, to   |\n");
	    write("    | 'join defenders' if they         |\n");
	    write("    | wish to join.                    |\n");
	    write("    |                                  |\n");
	    write("    | 'leave defenders' is what        |\n");
	    write("    | you must do if you wish to leave.|\n");
	    write("    |                                  |\n");
        write("    |                                  | \n");
        write("    0----------------------------------0 \n");
	    write("\n");
        write("\n");

	    return 1;

    }

     if (!str)
     {
         return 0;
     }

     return 0;
}


/*
 * Function name: do_guildjoin()
 * Description  : This functions starts the joiningprocedure of the guild
 *
 */
int
do_guildjoin(string str)
{
    object shadow_occ;
    object tokena;

    if (str != "defenders")
    {
        write("join defenders, perhaps?\n");
        return 1;
    }


    if (this_player()->query_guild_name_lay() == GUILDNAME_OCC)
    {
        write("You are already a member of the Defenders of the Westlands!\n");
        return 1;
    }


    if (this_player()->query_guild_name_occ())
    {
        write("You are already a member of an occupational guild.\n");
        return 1;
    }


    shadow_occ = clone_object(DEF_GUILDDIR +"shadows/guild_sh_occ.c");

    if (shadow_occ->shadow_me(this_player(), "layman", "mage",
    "defenders of the westlands") != 1)
    {
        write("For some reason, you cannot join the Defenders of the Westlands!\n");
        return 1;
    }

    DEF_MASTER->add_defender(this_player()->query_name());

    write("You join the Defenders of the Westlands!\n");

    tell_room(environment(this_player()), this_player()->query_name()
    +" joins the Defenders of the Westlands.\n", this_player());

    //tokena = clone_object(DEF_GUILDDIR +"obj/ldemtoken")->move(this_player());

    //write("A "+tokena->query_short()+" materializes in your hands.\n");

    //tell_room(environment(this_player()), "A "
    //+tokena->query_short()+" materializes into "+
    //QTNAME(this_player())+"'s hands.\n", this_player());

    this_player()->update_hooks();

    return 1;
}


/*
 * Function name: do_guildleave()
 * Description  : The function that removes a member of the guild.
 *
 */
int
do_guildleave(string str)
{
	object token;

	if (str != "defenders")
	{
		write("leave defenders, perhaps?\n");
		return 1;
	}

    if (this_player()->query_guild_name_occ() != GUILDNAME_OCC)
    {
        write("You are not a member of the Defenders of the Westlands.\n");
        return 1;
    }

    write("You leave the Defenders of the Westlands!\n");

    tell_room(environment(this_player()), this_player()->query_name()
    +" leaves the " +
    "Defenders of the Westlands.\n", this_player());

    //this_player()->remove_skill(SS_LYCAN_RAVAGE);
    //this_player()->remove_skill(SS_LYCAN_REGEN);
	//this_player()->remove_skill(LYCAN_HUNGER);

    this_player()->remove_guild_occ();

    this_player()->clear_guild_stat(SS_OCCUP);

    this_player()->remove_cmdsoul(DEF_GUILDDIR +"souls/guild_soul");

	DEF_MASTER->remove_defender(this_player()->query_name());

    this_player()->set_default_start_location(this_player()->query_def_start());

    this_player()->update_hooks();


    /*if (objectp(token = present("_deftoken", this_player())))
    {
        write("Your "+token->query_short()+" crumbles to dust.\n");

        tell_room(environment(this_player()), "The "+
        token->query_short()+" of "+
        QTNAME(this_player())+" crumbles to dust.\n", this_player());

        token->remove_object();
    }*/

    return 1;
}


void
init()
{
    ::init();

    add_action(do_guildjoin, "join");
    add_action(do_guildleave, "leave");

    add_action(do_rsign, "read");
}

