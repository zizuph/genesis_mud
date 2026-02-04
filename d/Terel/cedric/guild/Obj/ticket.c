#pragma save_binary

inherit "/std/object";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * A claim ticket for the weapon check-in at Minstrels Guild.
 * Functions: set_whose(string name) and query_whose()
 * Cedric 1/93
 */

/*
 * Prototypes:
 */
int do_endorse(string str);

/*
 * Globals:
 */
string whose; 
int endorsed = 0;


init()
{
    ::init();
    add_action(do_endorse, "endorse");
}

int do_endorse(string str)
{
    object ob;

    NF("Endorse what? The ticket, perhaps?\n");
    if (!stringp(str) || parse_command(str, all_inventory(TP()), "%o", ob) != 1)
    {
	return 0;
    }

    if (ob != TO())
    {
	return 0;
    }
    if (TP()->query_real_name() != whose)
    {
	NF("Only the owner of the ticket may endorse it!\n");
	return 0;
    }
    if (endorsed)
    {
	NF("But you have already endorsed the ticket!\n");
    }
    TP()->CM("You endorse the ticket. Now anybody may present it at the "
	     + "August Order of Minstrels for your weapons.\n");
    say(QCTNAME(TP())+" scribbles something on a tiny ticket.\n");
    endorsed = 1;
    return 1;
}

void set_whose(string name)
{
    whose = name;
}

string query_whose()
{
    return whose;
}

int query_endorsed()
{
    return endorsed;
}

string query_capital_whose()
{
    string ret = capitalize(whose)+". ";
    if (endorsed)
    {
	ret = ret + "It has been endorsed by "+capitalize(whose)+".";
    }
    return ret;
}

void create_object()
{
    set_name("minstrel_claim_ticket");
    add_name("ticket");
    add_adj("claim");
    set_short("claim ticket");
    set_long("This small ticket is labeled: "+"@@query_capital_whose@@"+"\n"
    + "There is some fine print on the back.\n");
    add_cmd_item(({"ticket", "print", "fine print"}), "read", "This "
    + "ticket entitles you to receive your weapons at the check-in desk "
    + "near the entrance of the Order. Don't lose it as we will not be "
    + "responsible. You may endorse the ticket, enabling anybody to present "
    + "it for your weapons.\n");
    add_item(({"print", "fine print"}), "This "
    + "ticket entitles you to receive your weapons at the check-in desk "
    + "near the entrance of the Order. Don't lose it as we will not be "
    + "responsible. You may endorse the ticket, enabling anybody to present "
    + "it for your weapons.\n");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_STEAL, 1);
}

string query_recover()
{
    string sTime;
    
    sTime = sprintf("%d", time());
    return MASTER + ":" + whose + ":" + sTime;
}

/*
 * We want the ticket to self-destruct if there has been a reboot since
 * the player quit. Otherwise he'll have a ticket that points to a bin
 * that doesn't exist.
 */
void init_recover(string str)
{
    string *args;
    int time_stamp;
    
    args = explode(str, ":");
    set_whose(args[0]);
    sscanf(args[1], "%d", time_stamp);
    if (time_stamp < "/secure/master"->query_start_time())
	remove_object();
}

/*
 * Called by office.c when a baddie kills a minstrel
 */
void self_destruct()
{
    if (interactive(environment()))
	environment()->catch_msg("The claim ticket disintegrates with a puff "
				 + "of flame! Whoops....\n");

    remove_object();
}
