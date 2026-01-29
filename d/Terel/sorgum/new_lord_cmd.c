/*
 * wiz_cmd_lord.c
 *
 * This object holds the lord wizards commands. (WIZ_LORD)
 * Made by Sorgum
 */

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <log.h>
#include <stdproperties.h>
#include "/secure/std.h"

string convtime(int i);

#define TP this_player()

mapping info;

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "New lord commands";
}

int
query_tool_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()
{
    return ([
	     "checkpoint":"checkpoint",
	     "dcheck":"dcheck",
	     "delta":"delta",	     
	     "ll":"ll",
	     "lle":"ll",	     	     
	     ]);
}

nomask int
is_a_lord(object ob)
{
    return (SECURITY->query_wiz_level(ob->query_real_name()) > WIZLEV_MAGE);
}


mapping
query_info()
{
    return info;
}

object
player_obj(string who)
{
    object player;

    player = find_player(who);
    if (!objectp(player))
	player = SECURITY->finger_player(who);

    return player;
}

string *
wiz_seconds(string *wizzes)
{
    int i;
    string *seconds = allocate(sizeof(wizzes));
    string *seconds_list;
    object player;

    for (i = 0; i < sizeof(wizzes); i++) {
	player = player_obj(wizzes[i]);
	seconds_list = player->query_seconds();
	if (sizeof(seconds_list)) 
	    seconds[i] = seconds_list[0];
	else seconds[i] = "";
    }

    return seconds;
}
	
string
login_info(string player_name, mixed player)
{
    int log_time;
    string line;

    if (!objectp(player))
	line = sprintf("%lls has no player file!", capitalize(player_name));
    else
    {
	log_time = time() - player->query_login_time();

	line = sprintf("%11s %17s", capitalize(player_name),
		       convtime(log_time));
    }

    return line;
}

int
checkpoint(string str)
{
    string domain_name;
    object player;
    object second;
    int i;
    mixed * range; 
    string *wizzes;
    string *seconds;
    string path;

    domain_name = SECURITY->query_wiz_dom(TP->query_name());
    info = ([ ]);
    wizzes = SECURITY->query_domain_members(domain_name);
    seconds = wiz_seconds(wizzes);
    
    for (i = 0; i < sizeof(wizzes); i++) {
	player = player_obj(wizzes[i]);
	if (!objectp(player)) {
	    info[wizzes[i]] = ({0, 0, 0});
	    continue;
	}
	range = allocate(3);	
	range[0] = (player->query_age() * 2);
	if (strlen(seconds[i])) {
	    range[1] = seconds[i];
	    second = player_obj(seconds[i]);
	    range[2] = (second->query_age() * 2);
	}
	else {
	        range[1] = 0;
		range[2] = 0;
	    }
	info[wizzes[i]] = range;
    }
    path = (string)(SECURITY->query_wiz_path(TP->query_real_name()) +
		    "/dcheck_data");
    /*TP->catch_msg("path is " + path + "\n");*/
    save_object(path);
    TP->catch_msg("Checkpoint updated.\n");
    return 1;
}

int
delta(string str)
{
    object wizard;
    object second;
    int age;
    int i;
    string sec_str;
    string sec_name;
    int sec_age;
    int wiz_age;
    string path;
    string fname;
    string *wizzes;
    string *seconds;
    string msg;

    path = (string)(SECURITY->query_wiz_path(TP->query_real_name()) +
		    "/dcheck_data");
    fname = path + ".o";
    restore_object(path);

    wizzes = m_indexes(info);
    seconds = wiz_seconds(wizzes);

    TP->catch_msg("Delta since " + ctime(file_time(fname)) + "\n");
    TP->catch_msg("Delta is a period of " + convtime(time() - file_time(fname))
		  + "\n");
    for (i = 0; i < sizeof(wizzes); i++) {

	wizard = player_obj(wizzes[i]);
	if (!objectp(wizard)) {
	    notify_fail(str + ": has no playerfile.\n");
	    return 0;
	}

	msg = sprintf("%11s", wizzes[i]);
	wiz_age = (wizard->query_age() * 2) - info[wizzes[i]][0];
	if (wiz_age)
	    msg +=  ": " + sprintf("%18s",convtime(wiz_age));
	else msg += ":                     ";
				   
					
				      
	if ((sec_name = info[wizard->query_real_name()][1])) {
	    second = player_obj(sec_name);
	    sec_age = (second->query_age() * 2) - info[wizard->query_real_name()][2];
	    if (sec_age > 0)
		msg += "      " + sec_name + ": " + convtime(sec_age);
	    else msg += "      " + sec_name + ":";
	}

	TP->catch_msg(msg + "\n");
    }
    return 1;
}

int
dcheck(string dom)
{
    string *wizzes;
    string *seconds;
    string rest;
    object player;
    object second;
    int i;
    string what;
    string line;

    
    if (!strlen(dom))
	what = SECURITY->query_wiz_dom(this_player()->query_name());
    else
	what = capitalize(dom);

    if (member_array(what, SECURITY->query_domain_list()) == -1) {
	notify_fail(what + ": Bad domain name.\n");
	return 0;
    }

    this_player()->catch_msg(capitalize(what) + " last logins:\n");
    wizzes = SECURITY->query_domain_members(what);
    seconds = wiz_seconds(wizzes);

    for (i = 0; i < sizeof(wizzes); i++) {
	
	player = player_obj(wizzes[i]);
	line = login_info(wizzes[i], player);
	
	if (strlen(seconds[i])) {
	    second = player_obj(seconds[i]);
	    line += login_info(seconds[i], second);
	}
	else
	    line += "         (No second)";
	this_player()->catch_msg(line + "\n");
    }

    return 1;
}


/*
 * Time in secs to  nn days xx hours yy minutes ss seconds
 */
string
convtime(int time)
{
    string res;
    int n;
    
    res = "";

    n = time / 86400;
    if (n > 0)
    {
	res = sprintf("%3d", n) + " d";
	time -= n * 86400;
    }
    else res = "     ";

    n = time / 3600;
    if (n > 0)
    {
	if (strlen(res) != 0)
	    res += " ";

	res += sprintf("%2d", n) + " h";
	time -= n * 3600;
    }
    else res += "     ";

    n = time / 60;
    if (n > 0)
    {
	if (strlen(res) != 0)
	    res += " ";

	res += sprintf("%2d", n) + " m";
	time -= n * 60;
    }
    else res += "     ";

    if (time)
    {
	if (strlen(res) != 0)
	    res += " ";

	res += sprintf("%2d", time) + " s";
    }

    return res;
}


/* **************************************************************************
 * liege - send a message on the liege-line
 * Now featuring emotes -- Sorgum (who noticed we all used them anyway *wink*)
 */
int
ll(string str)
{
    object *list;
    int    i;
    string name;


    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    name = capitalize(this_interactive()->query_real_name());
    list = filter(users() - ({ 0, this_interactive() }), "is_a_lord",
        this_object());
    str = "@Liege@ " + name + ((query_verb() == "ll") ? ": " : " ") +
			    str + "\n";
    for (i = 0; i < sizeof(list); i++)
    {
	if (!(list[i]->query_prop(WIZARD_I_BUSY_LEVEL) & 1024))
	{
            list[i]->catch_msg(str);
	}
    }

    if ((this_interactive()->query_get_echo()) &&
	(!(this_interactive()->query_prop(WIZARD_I_BUSY_LEVEL) &
	    (1024 + 128 + 16))))
        this_interactive()->catch_msg(str);
    else
        write("Ok.\n");

    return 1;
}
