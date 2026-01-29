#pragma strict_types
inherit "/std/object";

#include <cmdparse.h>
#include <composite.h>

#include "../defs.h"

public mapping ceremonies = ([ ]);


public void
create_object()
{
    reset_euid();
    set_name("cer");
    set_short("ceremony tester");

    seteuid(getuid());
    restore_object(CEREMONY + "ceremonies");
}

public int
add_ceremony(string name, string file)
{
    if (!strlen(name) || !strlen(file))
       return 0;

    if (ceremonies[name])
       return 0;

    if (file_size(CEREMONY + file + ".c") <= 0)
       return 0;

    ceremonies += ([ name : file ]);
    save_object(CEREMONY + "ceremonies");

    return 1;
}

public int
remove_ceremony(string name)
{
    if (!strlen(name))
       return 0;

    if (!ceremonies[name])
       return 0;

    m_delkey(ceremonies, name);
    save_object(CEREMONY + "ceremonies");
    return 1;
}

public int
list_ceremonies(string str)
{
    if (!strlen(str) || str != "ceremonies")
        return 0;

    write("Possile ceremonies: " +
	COMPOSITE_WORDS(m_indices(ceremonies)) + ".\n");

    return 1;
}

public int
ceremony(string str)
{
    object cer, *things;
    string who, what, *arr;

    notify_fail("Ceremony <which> for <whom>\n");

    if (!strlen(str))
	return 0;

    parse_command(str, ({}), "%s 'for' %s", what, who);
    if (!strlen(who) || !strlen(what))
	return 0;

    if (present("_union_ceremony_object", ENV(TP)))
    {
	notify_fail("There is already a ceremony in progress.\n"+
	    "You must wait for it to finish.\n");
	return 0;
    }

    things = FIND_STR_IN_OBJECT(who, ENV(TP));
    if (!sizeof(things))
    {
	notify_fail("'" + who + "' not found.\n");
	return 0;
    }

    arr = m_indices(ceremonies);
    if (member_array(what, arr) == -1)
    {
	notify_fail("Possible ceremonies are: " +
	    COMPOSITE_WORDS(arr) + ".\n");
	return 0;
    }

   cer = clone_object(CEREMONY + ceremonies[what]);

   if (!cer->set_ceremony_master(TP))
   {
       cer->remove_object();
       return 0;
   }

   if (!cer->set_ceremony_target(things[0]))
   {
       cer->remove_object();
       return 0;
   }

   if (!cer->valid_ceremony())
   {
       cer->remove_object();
       return 0;
   }

   cer->move(ENV(TP));
   write("Done.\n");
   return 1;
}

public void
init()
{
    ::init();
    add_action(ceremony, "ceremony");
    add_action(list_ceremonies, "list");
}
