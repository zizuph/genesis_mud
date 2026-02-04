#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

#define BBOARD          CEDRICDIR+"guild/board.c"

/*
 * The Minstrel Guild Headquarters: Entrance Arch
 * Here the players must check their weapons before entering the guild.
 * Cedric 1/93
 */
 
#define TICKET		GUILDOBJ+"ticket"
#define BIN		GUILDOBJ+"bin"

object		storeroom;
int		i;

void
init()
{
    ::init();
    add_action("do_check", "check");
    add_action("do_give", "give");
    add_action("do_temp", "test");
    add_action("do_cheat", "reindeer");
}

int
do_cheat(string str)
{
    if (MEMBER(TP()))
    {
	TP()->move_living("X", GUILD+"hall");
	return 1;
    }
    return 0;
}

void
reset_room()
{
    object  board;
    
    if (!present("board", TO()))
    {
	board = clone_object(BBOARD);
	board->move(TO());
    }
}

void
create_room()
{
    set_short("The Entrance to the Minstrels Guild");
    set_long(BS("You are standing in a large open foyer. To the north a road "
    + "stretches away from the palace; to the south is an ornate archway, carved "
    + "with images of musical instruments. Near the arch is a small window with "
    + "a sign reading: PLEASE CHECK YOUR WEAPONS BEFORE ENTERING. Behind the "
    + "window sits an eager novice, waiting to check your weapons.\n"));
    add_item(({"archway", "arch", "images", "instruments"}), BS("This "
    + "beautifully carved arch is covered "
    + "with ornate images depicting various musical instruments. Some of the "
    + "instruments are being played by minstrels; others, obviously magical, "
    + "appear to be playing themselves. You recognize among them a lyre, a harp, "
    + "a recorder, and a viol.\n"));
    add_item("sign", BS("In smaller print it explains that weapons are by ancient "
    + "custom forbidden in the house of music, and that yours will be returned "
    + "to you upon request.\n"));
    add_cmd_item("sign", "read", BS("In smaller print it explains that "
    + "weapons are by ancient "
    + "custom forbidden in the house of music, and that yours will be returned "
    + "to you upon request.\n"));
    add_item("window", BS("You can check your weapons here. The young novice will "
    + "store them until you return.\n"));
    add_item("novice", BS("This young one aspires to be a Minstrel. In the meantime "
    + "he works at the front gate, checking weapons for those who would enter the "
    + "august home of that exalted guild.\n"));
    add_exit("/d/Terel/guilds/minstrels/room/hall", "south", "@@arch_exit");
    add_exit("/d/Terel/enchanted/road_s12","northeast",0);
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

int
arch_exit()
{
    if (sizeof(filter(deep_inventory(TP()), "weap_filter", TO())))
    {
	TP()->catch_msg(BS("As you try to enter the palace proper through the "
	+ "arch, a magical force presses you back and a female voice rings in your "
	+ "mind: You shall not need your weapons in this place. Leave them behind "
	+ "and let the song of peace fill your heart.\n"));
	return 1;
    }
    else
	return 0;
}

/*
 * Function: bin_filter(object ob, string name)
 * Description: Tests for a particular bin.
 * Returns: 1 if ob is a bin labeled 'name'.
 */
int
bin_filter(object ob, string name)
{
    if (explode(file_name(ob), "#")[0]==BIN)
	if (ob->query_label()==name)
	    return 1;
    return 0;
}

/*
 * Function: weap_filter(object ob)
 * Description: Tests for weapons using ob->function_exists("wield_me").
 * Returns: 1 if ob is a weapon.
 */
int
weap_filter(object ob)
{
    if (!function_exists("wield_me", ob))
    {
	return 0;
    }
    /* An autoloadable / non-droppable item is excused.
     * Otherwise members would be blocked from entry by a quest item or so.
     * Mercade, 9 February 2004.
     */
    if (ob->query_auto_load() && ob->query_prop(OBJ_M_NO_DROP))
    {
        return 0;
    }
    return 1;
}

int
do_temp()
{   object *ob_list;

    write(sizeof(filter(deep_inventory(TP()), "weap_filter", TO())));
    write(filter(deep_inventory(TP()), "weap_filter", TO()));
    write("\n");
    for (i=0;i<sizeof(ob_list=deep_inventory(TP()));i++)
    {
	write(ob_list[i]);
	write(weap_filter(ob_list[i]));
	write("\n");
    }
}


int
do_check(string str)
{
    mixed *list;
    object *weap_list;
    object bin, ticket;
    
    notify_fail("Check what? Weapons, perhaps?\n");
    if (!str)
	return 0;
    notify_fail("Just type 'check weapons' and we'll do the rest.\n");
    if (str!="weapons" && parse_command(str, TP(), "%i", list) != 1)
	return 0;
    if (list)
    {
	list -= ({list[0]});
	weap_list = filter(list, "weap_filter", TO());
    }
    else
	weap_list = filter(deep_inventory(TP()), "weap_filter", TO());

    NF("The novice says: Um..you aren't carrying any weapons.\n");
    if (sizeof(weap_list)==0)
	return 0;
 
    seteuid(getuid());    

    bin = clone_object(BIN);
    bin->set_label(TP()->query_real_name());
    storeroom = STOREROOM->this_room();

    notify_fail("The novice says: Odd..I couldn't get all your weapons. "
		+ "Better drop them or something.\n");
    for (i=0;i<sizeof(weap_list);i++)
    {
	weap_list[i]->unwield_me();
        if  (weap_list[i]->query_prop(OBJ_M_NO_DROP) !=
	     "Paladine has given this item into your safekeeping!\n" &&
	     weap_list[i]->move(bin))
	{
	    bin->move(TO());
	    return 0;
	}
	if (weap_list[i]->query_prop(OBJ_M_NO_DROP) ==
	    "Paladine has given this item into your safekeeping!\n") 
	    weap_list[i]->move(bin,1);
	TP()->catch_msg(BS("The novice takes your "+weap_list[i]->short()
	+ " and places it carefully in a labeled bin.\n"));
    }
    TP()->catch_msg("The novice takes the bin back to the storeroom "
		    + "and returns.\n");
    say(QCTNAME(TP())+" checks "+TP()->query_possessive()+" weapons with "
	+ "the novice.\n");
    say("The novice loads "+TP()->query_possessive()+" weapons into a bin "
	+ "and carries it away. He returns and hands something to "
	+ QTNAME(TP())+".\n");
    bin->move(storeroom);
    ticket = clone_object(TICKET);
    ticket->set_whose(TP()->query_real_name());
    if (!ticket->move(TP()))	
	TP()->CM("The novice hands you a claim ticket.\n"
		 + "The novice says: Just give this back to me when "
		 + "you want your weaponry back.\n"
		 + "The novice smiles happily.\n");
    else
    {
	TP()->catch_msg(BS("The novice tried to hand you a claim ticket, but "
			   + "failed. The ticket falls to the floor.\n"));
	ticket->move(TO());
    }
    return 1;
}

/*
 * Function: do_fetch(string name)
 * Description: Gets the bin labeled 'name' and gives its contents to TP().
 * Arguments: name: the name of the player, as returned by query_real_name().
 * Returns: 1 if successfull, 0 if a problem was encountered.
 */
int
do_fetch(string name)
{
    object  *weap_list, the_bin;
    
    storeroom = STOREROOM->this_room();
    notify_fail("The novice says: Uh-oh. The storeroom is empty! Better "
    + "notify the guildmaster!\n");
    if (!objectp(storeroom))
    {
	return 0;
    }
    if (!present("bin", storeroom))
	return 0;
    notify_fail("The novice says: Strange. I can't find your bin! Better notify "
    + "the guildmaster.\n");
    /* Pick the first (probably only) bin labeled 'name': */
    the_bin = filter(all_inventory(storeroom), "bin_filter", TO(), name)[0];
    /* Give them the weapons: */
    weap_list = all_inventory(the_bin);
    for (i=0;i<sizeof(weap_list);i++)
    {	
	TP()->catch_msg(BS("The novice hands you the "+weap_list[i]->short()+".\n"));
	if (weap_list[i]->move(TP()))
	{
	    TP()->catch_msg(BS("The "+weap_list[i]->query_short()+" is too heavy and you drop it.\n"));
	    weap_list[i]->move(TO());
	}
    }
    the_bin->remove_object();
    return 1;
}

int
do_give(string str)
{
    object ticket;
    string whose;
    
    notify_fail("If you would like to check your weapons, type 'check weapons'.\n");
    if (parse_command(str, TP(), "%o 'to' 'novice'", ticket))
    {
	if (explode(file_name(ticket), "#")[0]==TICKET)
	{
	    whose = ticket->query_whose();
	    if (whose==TP()->query_real_name())
	    {
		TP()->catch_msg(BS("You hand the ticket to the novice. He runs "
		+ "back into the storeroom and fetches your weapons.\n"));
		say(QCTNAME(TP())+" hands the novice a ticket.\nThe "
		+ "novice runs back into the storeroom to fetch "
		+ TP()->query_possessive()+" weapons.\n");
		ticket->remove_object();
		return do_fetch(TP()->query_real_name());
	    }
	    else
	    {
		if (ticket->query_endorsed())
		{
		    TP()->catch_msg("You hand the ticket to the novice. He runs "
				    + "back into the storeroom and fetches "
				    + "the weapons of "
				    + capitalize(whose)+".\n");
		    say(QCTNAME(TP())+" hands the novice a ticket.\nThe "
			+ "novice runs back into the storeroom to fetch "
			+ "some weapons.\n");
		    ticket->remove_object();
		    return do_fetch(whose);
		}
		
		TP()->catch_msg(BS("The novice glances at the ticket and gasps "
		+ "in astonishment! He then hands the ticket back to you, with "
		+ "a suspicious look.\n"));
		say(BS(QCTNAME(TP())+" hands the novice a ticket. "
		+ "The novice glances at the ticket and gasps "
		+ "in astonishment! He then hands the ticket back, with "
		+ "a suspicious look.\n"));
		return 1;
	    }
	}
	notify_fail("The novice looks confused and says: Err, I just take tickets.\n");
	return 0;
    }
    return 0;
}
