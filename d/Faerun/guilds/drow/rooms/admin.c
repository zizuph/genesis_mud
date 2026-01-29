/*
 * Administration room for the Drow Guild
 * By Finwe, July 2006
 */

 /*
 Lucius wizard-speaks: when you 'list <house>' it pulls the data manually, you'll just want to update it slightly.
You wizard-speak: ok. I'll look into that.
> 
Lucius wizard-speaks: oh me too.. I had just kinda planned to flush it out a tiny bit to have more rp-fleshiness to it I guess.
Lucius wizard-speaks: but however you prefer to do things is fine by me.
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
    set_short("Membership Cave");
    set_long(short() + ". This a a small antechamber. It is where Drow " +
        "come to manage their membership in the guild. The walls are " +
        "smooth and polished and streaked with veins of dark ore. A " +
        "sign hangs on a wall. Six stone pillars encircle the cave.\n");


    add_item("sign", "It is large and made of a bone-white material. Flowing " +
        "letters are written on it, which seem to dance with an inner flame.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_item(({"pillars", "stone pillars", "pillar", "stone pillars"}),
        "They are square shaped with the top forming a point. There is " +
        "writing on each stone pillar, which is dedicated to a particular " +
        "deity of the Drow and can be read.\n");

    add_cmd_item(({"1st pillar", "first pillar", "eilistraee pillar", "eilistraee"}), 
        "read", "@@read_pillar1@@");
    add_cmd_item(({"2nd pillar", "second pillar", "ghaunadaur pillar", "ghaunadaur"}), 
        "read", "@@read_pillar2@@");  
    add_cmd_item(({"3rd pillar", "third pillar", "kiaransalee pillar", "kiaransalee"}), 
        "read", "@@read_pillar3@@");
    add_cmd_item(({"4th pillar", "fourth pillar", "lolth pillar", "lolth"}),
        "read", "@@read_pillar4@@");
    add_cmd_item(({"5th pillar", "fifth pillar", "selvetarm pillar", "selvetarm"}), 
        "read", "@@read_pillar5@@");
    add_cmd_item(({"6th pillar", "sixth pillar", "vhaeraun pillar", "vhaeraun"}),
        "read", "@@read_pillar6@@");

    add_exit("matron_rm", "east", "@@check_matron@@");
    add_exit("board_pri", "southwest");


}


string read_sign()
{

    return "\n\n" +
    "+----------------------------------------------------+\n" +
    "| * *                                            * * |\n" +
    "|  *                                              *  |\n" +
    "|                                                    |\n" +
    "|         D R O W   G U I L D   C O M M A N D S      |\n" +
    "|                                                    |\n" +
    "|    Below are the commands available to you as a    |\n" +
    "|    Drow:                                           |\n" +
    "|                                                    |\n" +
    "|    apply   - Adds or removes request to join a     |\n" +
    "|              house.                                |\n" +  
    "|    claim   - Claim a house and become head of it.  |\n" +
    "|              (Only for female drow).               |\n" +
    "|    desert  - Leave a house and become a commoner.  |\n" +
    "|    list    - List house information.               |\n" +
    "|                                                    |\n" +
    "|  *                                              *  |\n" +
    "| * *                                            * * |\n" +
    "+----------------------------------------------------+\n\n";
}


/* Annex leadership of a house. */
public int
f_annex(string str)
{
    //if (!check_drow(TI, HOUSE_NOBLE) || (TI->query_gender() != G_FEMALE))
	//return notify_fail("Only Female Noble may do this.\n", 0);

    if (TI->query_gender() != G_FEMALE)
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


/*
 * Admin Routines 
 */

/* Apply to join a house. */
public int
f_apply(string str)
{
    string tmp;

    if (check_drow(TI, HOUSE_MEMBER))
	return notify_fail("You already belong to a House.\n", 0);

    if (!strlen(str))
    {
	notify_fail("To which House are you applying?.\n");
	return 0;
    }

    if (strlen(tmp = GSERVER->query_member_house(TI)))
    {
	if (tmp != str)
	{
	    write("You already have an application pending with "+
		"House "+ tmp +".  Apply to it again to remove it.\n");
	}
	else
	{
	    write("You withdraw your application to House "+ tmp +".\n");
	    GSERVER->set_member_house(TI, "", 1);
	}
	return 1;
    }

    if (!strlen(tmp = GSERVER->query_house_rank(str, HR_MATRON)))
    {
	write("There is no House "+ str +" for you to apply to.\n");
    }
    else
    {
	object matron = find_player(tmp);

	GSERVER->set_member_house(TI, str, 1);
	write("You have applied to join the House "+ str +".\n");

	if (objectp(matron))
	{
	    tell_object(matron, "\nThe Drow "+ TI->query_name() +
		" has applied to join House "+ str +".\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Application", TI->query_real_name(),
		tmp, "", "The drow, "+ TI->query_name() +
		", has applied to join House "+ str +".\n");
	}
    }

    return 1;
}

/* Claim a house. */
public int
f_claim(string str)
{
    string tmp;

    if (check_drow(TI, HOUSE_MEMBER))
	return notify_fail("You already belong to a House.\n", 0);

    if (!strlen(str))
    {
	notify_fail("Please name the House you are wanting to claim.\n");
	return 0;
    }

    if (TI->query_gender() != G_FEMALE)
    {
	write("Only Drow females may claim and rule a House.\n");
	return 1;
    }

    tmp = GSERVER->query_member_city(TI);
    if (member_array(str, DROW_CITIES[tmp][0]) == -1)
    {
	write("There is no such House from the City "+ tmp +".\n");
	return 1;
    }

    if (GSERVER->query_house_rank(str, HR_MATRON))
    {
	write("That House is already in possession of a Matron.\n");
	return 1;
    }

    if (GSERVER->claim_house(TI, str, tmp))
    {
	TI->update_member_info_race();
	write("Congratulations!  From this day forth you shall "+
	    "be known as the Matron Mother of House "+ str +"!\n");
    }
    else
    {
	write("There seems to be a problem claiming that House.\n"+
	    "Please contact a wizard.\n");
    }

    return 1;
}

/* 
 * Leave a House
 */
public int
f_desert(string str)
{
    string tmp;

    if (!check_drow(TI, HOUSE_MEMBER))
    {
	write("How can you desert a House when you don't belong to one?\n");
	return 1;
    }

    if (!strlen(str))
	return notify_fail("Name your House for the records.\n");

    if (str != GSERVER->query_member_house(TI))
    {
	write("You do not belong to House "+ str +".\n");
	return 1;
    }

    if (!check_drow(TI, HOUSE_MATRON))
    {
	object matron;

	GSERVER->set_member_house(TI, "", 0);
	TI->update_member_info_race();
	tmp = GSERVER->query_house_rank(str, HR_MATRON);

	write("You have deserted House "+ str +"!\n");

	if (objectp(matron = find_player(tmp)))
	{
	    matron->catch_tell("\n"+ TI->query_name() +" has deserted "+
		"House "+ str +"!\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		tmp, "", "The Drow "+ TI->query_name() +
		" has deserted House "+ str +"!\n");
	}
    }
    else
    { // Matrons require special handling.
	GSERVER->remove_house_rank(str, HR_MATRON, TI);
	GSERVER->set_member_house(TI, "");
	GSERVER->reorganize_house(str, 0);
	TI->update_member_info_race();
	write("You have deserted House "+ str +"!\n");
    }

    return 1;
}



/*
 * Stone pillars of Deities
 */

string read_pillar1()
{
    return "\n" +
"                   /\\\n" +
"                 /    \\\n" +
"               /        \\\n" +
"             /            \\\n" +
"           /                \\\n" +
"         /                    \\\n" +
"       /                        \\\n" +
"     /                            \\\n" +
"   /                                \\\n" +
" /                                    \\\n" +
"+ ------------------------------------ +\n" +
"  |                                  |\n" +
"  |            Ghaunaduar            |\n" +
"  |                                  |\n" +
"  |                ***               |\n" +
"  |                                  |\n" +
"  |          That Which Lurks        |\n" +
"  |           The Elder Eye          |\n" +
"  |                                  |\n" +
"  |                ***               |\n" +
"  |                                  |\n" +
"  |     A Purplish Eye On Purple,    |\n" +
"  |     Violet And Black Circles     |\n" +
"  |                                  |\n" +
"  ------------------------------------\n\n";
}

string read_pillar2()
{
    return "\n" +
"                   /\\\n" +
"                 /    \\\n" +
"               /        \\\n" +
"             /            \\\n" +
"           /                \\\n" +
"         /                    \\\n" +
"       /                        \\\n" +
"     /                            \\\n" +
"   /                                \\\n" +
" /                                    \\\n" +
"+ ------------------------------------ +\n" +
"  |                                   |\n" +
"  |                                   |\n" +
"  |            Kiaransalee            |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |      Overlord of the Undead       |\n" +
"  |       The Lady of the Dead        |\n" +
"  |          The Revenancer           |\n" +
"  |       The Vengeful Banshee        |\n" +
"  |                                   |\n" +
"  |               ***                 |\n" +
"  |                                   |\n" +
"  |        A Female Drow Hand         |\n" +
"  |       Wearing Silver Rings        |\n" +
"  |                                   |\n" +
"  -------------------------------------\n\n";
}

string read_pillar3()
{
    return "\n" +
"                   /\\\n" +
"                 /    \\\n" +
"               /        \\\n" +
"             /            \\\n" +
"           /                \\\n" +
"         /                    \\\n" +
"       /                        \\\n" +
"     /                            \\\n" +
"   /                                \\\n" +
" /                                    \\\n" +
"+ ------------------------------------ +\n" +
"  |                                   |\n" +
"  |               Lolth               |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |         The Spider Queen          |\n" +
"  |         Queen of Spiders          |\n" +
"  |    Queen of the Demonweb Pits     |\n" +
"  |      Demon Queen of Spiders       |\n" +
"  |     Demon Queen of the Abyss      |\n" +
"  |         Weaver of Chaos           |\n" +
"  |         Lady of Spiders           |\n" +
"  |      Dark Mother of All Drow      |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |         A Black Spider With a     |\n" +
"  |       Female Drow Head Hanging    |\n" +
"  |           From a Spider Web       |\n" +
"  |                                   |\n" +
"  -------------------------------------\n\n";
}

string read_pillar4()
{
    return "\n" +
"                   /\\\n" +
"                 /    \\\n" +
"               /        \\\n" +
"             /            \\\n" +
"           /                \\\n" +
"         /                    \\\n" +
"       /                        \\\n" +
"     /                            \\\n" +
"   /                                \\\n" +
" /                                    \\\n" +
"+ ------------------------------------ +\n" +
"  |                                   |\n" +
"  |            Selvetarm              |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |        Champion of Lolth          |\n" +
"  |      The Spider that Waits        |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |      A Spider On a Crossed        |\n" +
"  |         Sword and Mace            |\n" +
"  |                                   |\n" +
"  -------------------------------------\n\n";
}

string read_pillar5()
{
    return "\n" +
"                   /\\\n" +
"                 /    \\\n" +
"               /        \\\n" +
"             /            \\\n" +
"           /                \\\n" +
"         /                    \\\n" +
"       /                        \\\n" +
"     /                            \\\n" +
"   /                                \\\n" +
" /                                    \\\n" +
"+ ------------------------------------ +\n" +
"  |                                   |\n" +
"  |             Vhaeraun              |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |            Masked Lord            |\n" +
"  |        Masked God of Night        |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |   A Pair of Black Glass Lenses    |\n" +
"  |   That Peer From Behind a Mask    |\n" +
"  |                                   |\n" +
"  -------------------------------------\n\n";
}

string read_pillar6()
{
    return "\n" +
"                   /\\\n" +
"                 /    \\\n" +
"               /        \\\n" +
"             /            \\\n" +
"           /                \\\n" +
"         /                    \\\n" +
"       /                        \\\n" +
"     /                            \\\n" +
"   /                                \\\n" +
" /                                    \\\n" +
"+ ------------------------------------ +\n" +
"  |                                   |\n" +
"  |            Eilistraee             |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |            Dark Maiden            |\n" +
"  |         Lady of the Dance         |\n" +
"  |                                   |\n" +
"  |                ***                |\n" +
"  |                                   |\n" +
"  |        A Nude, Long-Haired        |\n" +
"  |    Female Drow Dancing With a     |\n" +
"  |      Silver Bastard Sword In      |\n" +
"  |       Front of a Full Moon        |\n" +
"  |                                   |\n" +
"  -------------------------------------\n\n";
}


/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();
    add_action(   f_apply, "apply"   );
    add_action(   f_claim, "claim"   );
    add_action(  f_desert, "desert"  );
    add_action(    f_list, "list"    );
    //add_action(   f_annex, "annex"   );


}


int
check_matron()
{
   
   object tp = this_player();
   
   if((tp->query_wiz_level()) || (check_drow(TI, HOUSE_MATRON))) return 0;
      
    write("Only Matron Mothers may go there.\n");
      return 1;

}

