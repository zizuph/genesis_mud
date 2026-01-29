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
private string *lay_bf_list = ({ });

private string *test_list = ({ });


int
is_lay_bf(string name)
{
    name = capitalize(name);

    if (member_array(name, lay_bf_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_lay_bf(string name)
{  
    name = capitalize(name);

    if (is_lay_bf(name) == 1)
    {
        return;
    }
    
    if (name == 0)
    {
        return;
    }

    lay_bf_list += ({ name });

    sort_array(lay_bf_list);
    
    save_object(BF_SAVE_FILE);

    return;
}


void
remove_lay_bf(string name)
{
    name = capitalize(name);

    if (is_lay_bf(name) != 1)
    {
        return;
    }

    lay_bf_list -= ({ name });
    
    sort_array(lay_bf_list);

    save_object(BF_SAVE_FILE);

    return;
}








void
add_test_stuff(string stuff)
{  
    if (stuff == 0)
    {
        return;
    }

    test_list += ({ stuff });

    sort_array(test_list);
    
    save_object(BF_SAVE_FILE);

    return;
}


void
remove_test_stuff()
{
    //test_list -= ({ 0 });
    
    test_list -= test_list;
    
    sort_array(test_list);

    save_object(BF_SAVE_FILE);

    return;
}





















void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    if (!restore_object(BF_SAVE_FILE))
    {
        lay_bf_list = ({});
        
        test_list = ({});
    }
}