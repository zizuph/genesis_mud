/* /d/Gondor/guilds/defenders/master/def_master.c
 *
 * Guild manager
 *
 * Nerull 2016
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

void create();

private string *def_list = ({ });


int
is_defender(string name)
{
    name = capitalize(name);

    if (member_array(name, def_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_defender(string name)
{
    if (member_array(name, def_list) != -1)
    {
        return;
    }

    def_list += ({ name });

    seteuid(getuid(this_object()));

    save_object(SAVE_FILE);

    sort_array(def_list);

    return;
}


void
remove_defender(string name)
{
    name = capitalize(name);

    if (member_array(name, def_list) == -1)
    {
        return;
    }

    def_list -= ({ name });

    seteuid(getuid(this_object()));

    save_object(SAVE_FILE);

    return;
}


void
create()
{
	int i;

	seteuid(getuid(this_object()));

	if (!restore_object(SAVE_FILE))
	{
		def_list = ({});
	}
}












