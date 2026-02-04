/* coffin_manager.c created by Novo
 * This file takes care of the logs and a few miscellanea
 * for the vampire coffins.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild.h"
#include "../defs.h"
#include <std.h>

inherit "/d/Emerald/lib/data_manager";

#define MEMBER_FILE(who)       save_dir + who

/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    ::create_data_manager();    
    set_save_dir(DATA_DIR + "coffin/");
    set_garbage_dir(DATA_DIR + "coffin/old/");
} /* create_data_manager */


string save_dir;

string *query_all_coffins();
int remove_coffin(mixed who);

public void
set_save_dir(string dir)
{
    save_dir=dir;
    ::set_save_dir(dir);
}


string
get_name(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
  
    if (!stringp(who))
    {
        return 0;
    }
  
    return lower_case(who);
}


int
remove_coffin(mixed who)
{
    if (objectp(who))
    {
    	who = who->query_real_name();
    }
    
    return delete_data(who);
}

string member_name_from_member_file(string file)
{
    string name;

    if (!sscanf(file, "%s.o", name))
    {
        return 0;
    }

    if (!SECURITY->exist_player(name))
    {
        return 0;
    }

    return name;
}

string *query_all_coffins()
{
    string *names;

    setuid();
    seteuid(getuid());

    names = map(get_dir(save_dir), member_name_from_member_file);
    names -= ({ 0 });

    return names;
}

int set_material(mixed who,string material)
{
    return set_info(who,"material",material);
}

public string query_material(mixed who)
{
    return get_info(who,"material");
}
int set_material_cost(mixed who,int cost)
{
    return set_info(who,"material_cost",cost);
}

public int query_material_cost(mixed who)
{
    return get_info(who,"material_cost");
}


int set_lining(mixed who,string lining)
{
    return set_info(who,"lining",lining);
}

public string query_lining(mixed who)
{
    return get_info(who,"lining");
}

int set_lining_color(mixed who,string color)
{
    return set_info(who,"lining_color",color);
}

public string query_lining_color(mixed who)
{
    return get_info(who,"lining_color");
}

int set_carving(mixed who,string carving)
{
    return set_info(who,"carving",carving);
}

public string query_carving(mixed who)
{
    return get_info(who,"carving");
}

int set_location(mixed who,string location)
{
    return set_info(who,"location",location);
}

public string query_location(mixed who)
{
    return get_info(who,"location");
}

int set_destroyed(mixed who,string destroyer)
{
    return set_info(who,"destroyed",destroyer);
}

public string query_destroyed(mixed who)
{
    return get_info(who,"destroyed");
}


/* Add someone to the list of guild members, noting the time
 * and the new member's age
 */
int
add_coffin(mixed who,string material)
{
    object ob;
  
    if (objectp(who))
    {
    	who = who->query_real_name();
    }
  
    if (!stringp(who))
    {
        return 0;
    }

    set_material(who,material);
    set_material_cost(who,0);
    return 1;
}


