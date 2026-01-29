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
#include <composite.h>
#include <macros.h>
#include <std.h>
#include <mail.h>
#include "../guild.h";

void create();


// LAY vampires list
private string *race_ho_list = ({ });


int
is_race_ho(string name)
{
    name = capitalize(name);

    if (member_array(name, race_ho_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_race_ho(string name)
{  
    name = capitalize(name);

    if (is_race_ho(name) == 1)
    {
        return;
    }
    
    if (name == 0)
    {
        return;
    }

    race_ho_list += ({ name });

    sort_array(race_ho_list);
    
    save_object(HO_SAVE_FILE);

    return;
}


void
remove_race_ho(string name)
{
    name = capitalize(name);

    if (is_race_ho(name) != 1)
    {
        return;
    }

    race_ho_list -= ({ name });
    
    sort_array(race_ho_list);

    save_object(HO_SAVE_FILE);

    return;
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    if (!restore_object(HO_SAVE_FILE))
    {
        race_ho_list = ({});
    }
}