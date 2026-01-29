/*
*
*
*
*/

#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Faerun/defs.h"
#include "../guild.h";

			
#define NODE_LOG   ("/d/Faerun/guilds/black_flame/log/node_log")

//inherit "/std/monster";
//inherit "/std/combat/unarmed";
inherit "/std/scroll";

object PLAYER;
string p_name;

string target_string;

string node_name;

// The max size of the file.
int max_size = 30000;





	
	
/*
 * Function name: read_scroll
 * Description  : This function is called when the player wants to read
 *                the scroll.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
static int
read_scroll(string str)
{
    string vb, file_name;
    object *a;
    int f_size;

    file_name = query_file();
    f_size = file_size(file_name);

    if (this_player()->query_prop(TEMP_STDREAD_CHECKED))
        return 0;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n", 0);
    if (!str)
    return 0;

    a = CMDPARSE_ONE_ITEM(str, "read_access", "read_access");
	
    if (sizeof(a) > 0)
    {
        a[0]->read_it(vb);
		
        if((f_size > max_size) && (file_name == "/d/Faerun/guilds/black_flame/log/node_log"))
        {
           // this_object()->trim_book();
        }
        return 1;
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(TEMP_STDREAD_CHECKED));
    this_player()->add_prop(TEMP_STDREAD_CHECKED, 1);
    return 0;
}


void
destruct_eye()
{
	tell_room(environment(), "The " + this_object()->short() + " bursts info flames and is gone!\n");

	remove_object();
}


void
create_scroll()
{
	set_name("eye");
	add_name("_bf_eye");

	set_short("floating eye");

	set_long("A floating eye.\n");

	add_prop(LIVE_I_SEE_DARK, 10);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(OBJ_I_WEIGHT, 350);
	
	add_prop(OBJ_I_INVIS, 5);
	
	add_prop(OBJ_I_VOLUME, 350);
	
	set_file("/d/Faerun/guilds/black_flame/log/node_log");
	
	node_name = this_object()->query_name();

	setuid();
	seteuid(getuid());

	//set_alarm(9999.0,0.0, &destruct_skeleton());
}


int
do_node_name(string str)
{

	/*if (this_player()->query_real_name() != p_name)
	{
		return 0;
	}*/

	if (!str)
	{
		return 0;
	}

	write("You change your familiar's name "
    +"to: <"+str+">.\n");

    this_object()->set_name(str);
	
	
	node_name = this_object()->query_name();

	return 1;
}


int
do_node_set_target(string str)
{

	if (this_player()->query_real_name() != p_name)
	{
		return 0;
	}

	if (!str)
	{
		return 0;
	}

	write("You order your node to watch for"
    +": <"+str+">.\n");

    target_string = str;

	return 1;
}



//----------------------------------------------------

int
do_node_remove(string str)
{

	if (this_player()->query_real_name() != p_name)
	{
		return 0;
	}

	if (str != "eye")
	{
		return 0;
	}

	destruct_eye();

	return 1;

}


int
watch_exit_se()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling eastwards.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_e()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling eastwards.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_ne()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling northeast.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_n()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling north.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_nw()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling northwest.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_w()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling west.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_sw()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling southwest.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_s()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling south.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_up()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling up.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_down()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling down.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_in()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling in.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}

int
watch_exit_out()
{
	string targ;
	string target_data;
	
    targ = capitalize(this_player()->query_name());

    target_data = capitalize(node_name)+" - "+targ
	+" recently seen travelling out.\n";	
		
	write_file(NODE_LOG, target_data);

    return 0;
}


void
init()
{
		::init();
	
	add_action(do_node_remove, "dismiss");

	
	add_action(do_node_name, "nodename");
	
	add_action(read_scroll, "read");

	//add_action(do_setpasscommand, "demsetpasscmd");

	add_action(watch_exit_w, "west");
	add_action(watch_exit_nw, "northwest");
	add_action(watch_exit_n, "north");
	add_action(watch_exit_ne, "northeast");
	add_action(watch_exit_e, "east");
	add_action(watch_exit_se, "southeast");
	add_action(watch_exit_s, "south");
	add_action(watch_exit_sw, "southwest");
	add_action(watch_exit_down, "down");
	add_action(watch_exit_up, "up");
	add_action(watch_exit_in, "in");
	add_action(watch_exit_out, "out");
}


void
init_node(object pl)
{
	PLAYER = pl;
	p_name = PLAYER->query_real_name();
}
