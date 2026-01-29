/*
 * Guild manager, master
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "../guild.h";


void create();

private string *lay_theorder_melee_list = ({ });
private string *lay_theorder_cleric_list = ({ });


int
is_lay_theorder_melee(string name)
{
    name = capitalize(name);

    if (member_array(name, lay_theorder_melee_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_lay_theorder_melee(string name)
{  
    name = capitalize(name);

    if (is_lay_theorder_melee(name) == 1)
    {
        return;
    }

    lay_theorder_melee_list += ({ name });

    sort_array(lay_theorder_melee_list);
    
    save_object(THEORDER_SAVE_FILE);

    return;
}


void
remove_lay_theorder_melee(string name)
{
    name = capitalize(name);

    if (is_lay_theorder_melee(name) != 1)
    {
        return;
    }

    lay_theorder_melee_list -= ({ name });
    
    sort_array(lay_theorder_melee_list);

    save_object(THEORDER_SAVE_FILE);

    return;
}


int
is_lay_theorder_cleric(string name)
{
    name = capitalize(name);

    if (member_array(name, lay_theorder_cleric_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_lay_theorder_cleric(string name)
{  
    name = capitalize(name);

    if (is_lay_theorder_cleric(name) == 1)
    {
        return;
    }

    lay_theorder_melee_list += ({ name });

    sort_array(lay_theorder_melee_list);
    
    save_object(THEORDER_SAVE_FILE);

    return;
}


void
remove_lay_theorder_cleric(string name)
{
    name = capitalize(name);

    if (is_lay_theorder_cleric(name) != 1)
    {
        return;
    }

    lay_theorder_cleric_list -= ({ name });
    
    sort_array(lay_theorder_cleric_list);

    save_object(THEORDER_SAVE_FILE);

    return;
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    if (!restore_object(THEORDER_SAVE_FILE))
    {
        lay_theorder_melee_list = ({});
        lay_theorder_cleric_list = ({});
    }
}