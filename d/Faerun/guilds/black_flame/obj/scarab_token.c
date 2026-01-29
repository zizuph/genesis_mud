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


inherit "/std/object";
//inherit "/std/combat/unarmed";

object PLAYER;
string p_name;

string target_string;

string node_name;


public int 
check_seen(object for_obj)
{
    // Wizards can always see us.
    if (for_obj->query_wiz_level())
    {
        return 1;
    }
    
    if (for_obj->query_name() == p_name)
	{
		return 1;
	}

    return 0;
}


void
destruct_scarab()
{
	int nodenumberss;
	
	nodenumberss = BF_MAPPINGS->query_bf_nodes(p_name);
	
	nodenumberss = nodenumberss - 1;
	
	BF_MAPPINGS->set_bf_nodes(p_name, nodenumberss);
	
	tell_room(environment(), "The " + this_object()->short() + " bursts info black flames and is gone!\n");

	remove_object();
}


void
ping_owner()
{
	if (p_name == 0)
	{
		return;
	}
	
	int nodenumbers = BF_MAPPINGS->query_bf_nodes(p_name);
	
	if (nodenumbers > MAXNODES)
    {
		this_object()->destruct_scarab();
		
		return;
	}
		
	return;
}


void
create_object()
{
	set_name("scarab");
    add_name("_bf_scarab");
	//add_name("scarab");
	
	set_adj("tiny");
	add_adj("black");

	set_short("tiny black scarab");

	set_long("A tiny black scarab.\n");

	add_prop(LIVE_I_SEE_DARK, 10);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(OBJ_I_WEIGHT, 350);
	
	add_prop(OBJ_I_VOLUME, 350);
	
	node_name = this_object()->query_name();

	setuid();
	seteuid(getuid());
	
	set_alarm(10.0, 10.0, &ping_owner());
}


int
do_node_name(string str)
{
	if (this_player()->query_name() != p_name)
	{
		return 0;
	}

	if (!str)
	{
		return 0;
	}

	write("You change your scarab's name "
    +"to: <"+str+">.\n");

    this_object()->set_name(str);
	
	
	node_name = this_object()->query_name();

	return 1;
}


int
do_node_remove(string str)
{

	if (this_player()->query_name() != p_name)
	{
		return 0;
	}

	if (str != "scarab")
	{
		return 0;
	}

	destruct_scarab();

	return 1;

}


int
watch_exit_se()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling southeast ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_e()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling east ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_ne()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling northeast t";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_n()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling north ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_nw()
{
    object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling northwes ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_w()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling west ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_sw()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling southwest ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_s()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling south ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_up()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling up ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_down()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling down ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_in()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling in  ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}

int
watch_exit_out()
{
	object targe;
	string direction;	
	string node_name;
	
	
	targe = this_player();
	direction = ", seen travelling out ";
	node_name = this_object()->query_name();
	
	BF_MAPPINGS->register_living(targe, direction, node_name);

    return 0;
}


void
set_owner(string str)
{
	p_name = str;
	//p_name = PLAYER->query_real_name();
    
    return;
}


string
query_owner()
{
	return p_name;
}


void
init()
{
		::init();
	
	add_action(do_node_remove, "destruct");

	
	add_action(do_node_name, "scarabname");
	
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

