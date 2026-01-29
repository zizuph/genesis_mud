/*
 * Listmast.c - The Spell List Master.
 *
 * This is the object which has routines which controls aspects
 * of all spell lists.
 *
 */

#include "defs.h"
#include "lists.h"

/*
 * Conversion routines.
 *
 */

int
filter_is_spell_list(mixed file_ptr)
{
    return file_ptr->is_spell_list();
}

int
filter_does_id(mixed file_ptr, string ids)
{
    if (catch(file_ptr->load_me()))
	return 0;
    return file_ptr->id(ids);
}

varargs string *
query_lists(object who = TP, string name = 0)
{
    string *list = who->query_cmdsoul_list();

    list = filter(list, "filter_is_spell_list", TO);
    if(strlen(name))
	list = filter(list, "filter_does_id", TO, name);

    return list;
}

varargs string *
query_all_lists(string name = 0)
{
    string *list = LIST_FILES;

    if(strlen(name))
	list = filter(list, "filter_does_id", TO, name);

    return list;
}
