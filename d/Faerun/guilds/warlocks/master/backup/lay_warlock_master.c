/*
 * Guild manager, master
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#pragma no_inherit
#pragma strict_types

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "../guild.h";


/* Patrons :  1 = Fiend
              2 = Great Old One
              3 = Archfey
*/            

void create();

// Warlock list
private string *lay_warlock_list = ({ });

// Patrons
private string *patron_1_list = ({ });
private string *patron_2_list = ({ });
private string *patron_3_list = ({ });


int
is_lay_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, lay_warlock_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_lay_warlock(string name)
{
    if (member_array(name, lay_warlock_list) != -1)
    {
        return;
    }

    lay_warlock_list += ({ name });

    save_object(WARLOCK_SAVE_FILE);

    sort_array(lay_warlock_list);

    return;
}


void
remove_lay_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, lay_warlock_list) == -1)
    {
        return;
    }

    lay_warlock_list -= ({ name });

    save_object(WARLOCK_SAVE_FILE);

    return;
}


int
is_patr1_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, patron_1_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_patr1_warlock(string name)
{
    if (member_array(name, patron_1_list) != -1)
    {
        return;
    }

    patron_1_list += ({ name });

    save_object(WARLOCK_SAVE_FILE);

    sort_array(patron_1_list);

    return;
}


void
remove_patr1_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, patron_1_list) == -1)
    {
        return;
    }

    patron_1_list -= ({ name });

    save_object(WARLOCK_SAVE_FILE);

    return;
}


int
is_patr2_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, patron_2_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_patr2_warlock(string name)
{
    if (member_array(name, patron_2_list) != -1)
    {
        return;
    }

    patron_2_list += ({ name });

    save_object(WARLOCK_SAVE_FILE);

    sort_array(patron_2_list);

    return;
}


void
remove_patr2_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, patron_2_list) == -1)
    {
        return;
    }

    patron_2_list -= ({ name });

    save_object(WARLOCK_SAVE_FILE);

    return;
}


int
is_patr3_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, patron_3_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_patr3_warlock(string name)
{
    if (member_array(name, patron_3_list) != -1)
    {
        return;
    }

    patron_3_list += ({ name });

    save_object(WARLOCK_SAVE_FILE);

    sort_array(patron_3_list);

    return;
}


void
remove_patr3_warlock(string name)
{
    name = capitalize(name);

    if (member_array(name, patron_3_list) == -1)
    {
        return;
    }

    patron_3_list -= ({ name });

    save_object(WARLOCK_SAVE_FILE);

    return;
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    if (!restore_object(WARLOCK_SAVE_FILE))
    {
        lay_warlock_list = ({});
        patron_1_list = ({});
        patron_2_list = ({});
        patron_3_list = ({});
    }
}