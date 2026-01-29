/*
 * Matron's room for Drow Guild
 * By Finwe, May 2006
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <mail.h>
#include <const.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";


void
create_drow_room()
{
    add_prop(ROOM_S_MAP_FILE, "drow_guild_map.txt");
    set_short("Matron's Judgement Cave");
    set_long(short() + ". It is larger than most and serves as a meeting " +
        "place for the Matrons of the Drow. The walls are decorated " +
        "with the deities of the drow. On the floor is carved a large " +
        "spider. It looks alive and its eyes seem to follow your every " +
        "move. A large sign hangs on a wall. To the west is a doorway.\n");

    add_item("sign", "It is large and made of a bone-white material. " +
        "Flowing letters are written on it, which seem to dance with " +
        "an inner flame.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_exit("admin", "west");

}


string read_sign()
{

    if(this_player()->query_wiz_level() || check_drow(TI, HOUSE_MATRON))
    return "\n\n" +
"+---------------------------------------------------------------+\n" +
"| * *                                                       * * |\n" +
"|  *                                                         *  |\n" +
"|                                                               |\n" +
"|         M A T R O N   M O T H E R   C O M M A N D S           |\n" +
"|                                                               |\n" +
"|    These are the different commands available to rule your    |\n" +
"|    house:                                                     |\n" +
"|                                                               |\n" +
"|    accept  - Allow a commoner to your house.                  |\n" +
"|    annex   - Annex leadership of a house.                     |\n" +
"|    appoint - Appoint or demote drow in your house.            |\n" +
"|              To demote, appoint the rank again to remove the  |\n" +
"|              drow from that rank.                             |\n" +   
"|    deny    - Deny an application to your house                |\n" +
"|    dismiss - Remove a drow from your house                    |\n" +
"|                                                               |\n" +
"|  *                                                         *  |\n" +
"| * *                                                       * * |\n" +
"+---------------------------------------------------------------+\n\n";


    return "Only Matron Mothers may read this sign.\n";
}

string read_plaque()
{

    return "\n\n" +
"+----------------------------------------------------+\n" +
"|                                                    |\n" +
"|         D R O W   G U I L D   C O M M A N D S      |\n" +
"|                                                    |\n" +
"|    Below are the commands available to you as a    |\n" +
"|    drow:                                           |\n" +
"|                                                    |\n" +
"|    apply   - Apply to join a house.                |\n" +
"|    claim   - Claim a house and become head of it.  |\n" +
"|              (Only for female drow).               |\n" +
"|    desert  - Leave a house and become a commoner.  |\n" +
"|    list    - List drow who are awake.              |\n" +
"|                                                    |\n" +
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}


/*
 * Routines for the Matrons
 */
 /* Accepts or denies a house applicant. */
public int
f_accept(string str)
{
    string house;
    object player;

    if (!check_drow(TI, HOUSE_MATRON))
	return notify_fail("Only Matron Mothers may do this.\n", 0);

    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" who as a member of thy House?\n");
	return 0;
    }
    else
    {
	str = lower_case(str);
    }

    if (!check_drow(str, GUILD_MEMBER))
    {
	write("There does not seem to be any drow with that name.\n");
	return 1;
    }

    house = GSERVER->query_member_house(TI);
    if (member_array(str, GSERVER->query_house_members(house, 1)) == -1)
    {
	write("But "+ CAP(str) +" has not applied to your House.\n");
	return 1;
    }

    if (query_verb() == "accept")
    {
	GSERVER->set_member_house(str, house, 0);
	write("You have accepted "+ CAP(str) +" into House "+ house +".\n");

	if (objectp(player = find_player(str)))
	{
	    player->update_member_info_race();
	    player->catch_tell("\nYou have been accepted into "+
		"the Drow House "+ house +"!\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(), str, "",
		"You have been accepted into the Drow House "+ house +"!\n");
	}
    }
    else
    { // query_verb() == "deny"
	GSERVER->set_member_house(str, "", 1);
	write("You have denied "+ CAP(str) +" entrance into House "+
	    house +".\n");

	if (objectp(player = find_player(str)))
	{
	    player->catch_tell("\nYou have been denied entrance into "+
		"the Drow House "+ house +"!\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(), str, "",
		"You have been denied entrance into the Drow "+
		"House "+ house +"!\n");
	}
    }

    return 1;
}

/* Annex leadership of a house. */
public int
f_annex(string str)
{
    if (!check_drow(TI, HOUSE_NOBLE) || (TI->query_gender() != G_FEMALE))
	return notify_fail("Only Female Noble may do this.\n", 0);

    if (!strlen(str))
    {
	notify_fail("State your House name for the record.\n");
	return 0;
    }

    if (str != GSERVER->query_member_house(TI))
    {
	write("But you are not a member of that House!\n");
	return 1;
    }

    switch(GSERVER->reorganize_house(str, TI))
    {
    case -2:
	write("The First Daughter is still active, "+
	    "therefore your request is denied.\n");
	break;
    case -1:
	write("The Matron Mother is still active, "+
	    "therefore your request is denied.\n");
	break;
    case 1:
	/* Fallthru */
    case 2:
	TI->update_member_info_race();
	write("Congratulations!  You are now the Matron Mother "+
	    "over House "+ str +"!\n");
	break;
    default:
	write("An unforseen error has occured, please contact "+
	    "the Guildmaster.\n");
	break;
    }

    return 1;
}

/* Promote/demote members of a house. */
public int
f_appoint(string str)
{
    mixed rank;
    mapping dranks;
    string *arr, house;

    if (!check_drow(TI, HOUSE_MATRON) || this_player()->query_wiz_level())
	return notify_fail("Only Matron Mothers may do this.\n", 0);

    if (!strlen(str))
	return notify_fail("Appoint whom to what position?\n");

    if (sizeof(arr = explode(lower_case(str), " ")) != 2)
	return notify_fail("Appoint whom to what position?\n");

    if (arr[0] == TI->query_real_name())
    {
	write("You are the Matron Mother, you may not demote yourself.\n"+
	    "If you wish to leave, you must 'desert' thine House.\n");
	return 1;
    }

    if (!check_drow(arr[0], HOUSE_MEMBER))
    {
	write("But "+ CAP(arr[0]) +" does not even belong to a House!\n");
	return 1;
    }

    house = GSERVER->query_member_house(TI);
    if (GSERVER->query_member_house(arr[0]) != house)
    {
	write("You may only alter appointments within thy own House.\n");
	return 1;
    }

    dranks = DROW_RANKS;
    if (!dranks[arr[1]])
    {
	write("That is not even a valid rank to appoint!\n");
	return 1;
    }

    rank = GSERVER->query_house_rank(house, "", arr[0]);
    if (strlen(rank))
    {
	if (rank != arr[1])
	{
	    write(CAP(arr[0]) +" already holds a rank within "+
		"House "+ house +"!\nYou must unappoint it by "+
		"giving their current rank first.\n");
	}
	else
	{
	    object player = find_player(arr[0]);

	    GSERVER->remove_house_rank(house, rank, arr[0]);
	    write(CAP(arr[0]) +" will no longer hold the rank "+
		"of "+ dranks[rank][DR_TITLE] +" within House "+
		house +".\n");

	    if (objectp(player))
	    {
		player->update_member_info_race();
		player->catch_tell("You no longer hold the rank "+
		    "of "+ dranks[rank][DR_TITLE] +" within House "+
		    house +".\n");
	    }
	    else
	    {
		CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		    arr[0], "", "You no longer hold the rank"+
		    "of "+ dranks[rank][DR_TITLE] +" within House "+
		    house +".\n");
	    }
	}
    }
    else
    {
	int limit, gender;
	object player = find_player(arr[0]);

	if (objectp(player))
	{
	    gender = player->query_gender();
	}
	else
	{
	    player = ("/secure/master")->finger_player(arr[0]);
	    gender = player->query_gender();
	    player->remove_object();
	    player = 0;
	}

	rank = GSERVER->query_house_rank(house, arr[1]);
	limit = dranks[arr[1]][DR_LIMIT][gender];

	if (limit == 0)
	{
	    write("The position of "+ dranks[arr[1]][DR_TITLE] +
		" is unsuitable for "+ CAP(arr[0]) +".\n");
	    return 1;
	}
	else if ((limit == 1) && strlen(rank))
	{
	    write("The rank of "+ dranks[arr[1]][DR_TITLE] +
		" has already been filled.\n");
	    return 1;
	}
	else if (sizeof(rank) >= limit)
	{
	    write("There is a limit of "+ limit +" "+
		dranks[arr[1]][DR_TITLE] +"s and they "+
		"are all filled.\n");
	    return 1;
	}

	GSERVER->set_house_rank(house, arr[1], arr[0]);
	write("You grant "+ CAP(arr[0]) +" the rank of "+
	    dranks[arr[1]][DR_TITLE] +"!\n");

	if (objectp(player))
	{
	    player->update_member_info_race();
	    player->catch_tell("You have been granted "+
		"the rank of "+ dranks[arr[1]][DR_TITLE] +
		" within House "+ house +"!\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		arr[0], "", "You have been granted "+
		"the rank of "+ dranks[arr[1]][DR_TITLE] +
		" within House "+ house +"!\n");
	}
    }

    return 1;
}

/* To kick a player from a House. */
public int
f_dismiss(string str)
{
    string house, rank;
    object player;

    if (!check_drow(TI, HOUSE_MATRON))
	return notify_fail("Only Matron Mothers may do this.\n", 0);

    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" who as a member of thy House?\n");
	return 0;
    }
    else
    {
	str = lower_case(str);
    }

    if (!check_drow(str, GUILD_MEMBER))
    {
	write("There does not seem to be any drow with that name.\n");
	return 1;
    }

    house = GSERVER->query_member_house(TI);
    if (GSERVER->query_member_house(str) != house)
    {
	write("You may only alter appointments within thy own House.\n");
	return 1;
    }

    rank = GSERVER->query_house_rank(house, "", str);
    if (strlen(rank))
    {
	write("You must demote "+ CAP(str) +" before you remove "+
	    "them from thine House.\n");
	return 1;
    }

    write("You dismiss "+ CAP(str) +" from House "+ house +".\n");
    GSERVER->set_member_house(str, "", 0);

    if (objectp(player = find_player(str)))
    {
	player->update_member_info_race();
	player->catch_tell("\nYou have been dismissed from House "+
	    house +"!\n\n");
    }
    else
    {
	CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
	    str, "", "You have been dismissed "+
	    "from House "+ house +"!\n");
    }

    return 1;
}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();
    add_action(  f_accept, "accept"  );
    add_action(   f_annex, "annex"   );
    add_action( f_appoint, "appoint" );
    add_action(  f_accept, "deny"    );
    add_action( f_dismiss, "dismiss" );
    add_action(    f_list, "list"    );

}
