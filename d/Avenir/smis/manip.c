// file name:        /d/Avenir/smis/manip.c
// creator(s):       Denis, Jul'96
// purpose:          Provides functions for module manipulation.
#pragma strict_types

#include "sys.h"

public object
find_smis_module(string ref)
{
    string *ref_parts;

    if(!ref)
	return 0;

    ref_parts = explode(ref, ":");

    if(sizeof(ref_parts) < 2 ||
       !find_object(SMIS_MANAGER_DOM(ref_parts[0])) ||
	catch(SMIS_MANAGER_DOM(ref_parts[0])->telelednignsanka()))
	return 0;

    return SMIS_MANAGER_DOM(ref_parts[0])->query_module_object(ref_parts[1]);
}

public object
find_smis_module_available(string ref)
{
    string *ref_parts;

    if(!ref)
	return 0;

    ref_parts = explode(ref, ":");

    if(sizeof(ref_parts) < 2 ||
       !find_object(SMIS_MANAGER_DOM(ref_parts[0])) ||
	catch(SMIS_MANAGER_DOM(ref_parts[0])->telelednignsanka()))
	return 0;

    return SMIS_MANAGER_DOM(ref_parts[0])->query_module_available(ref_parts[1]);
}

public int
find_exit_of_type(object where, string type)
{
    int i;
    string *exits = where->query_exit_cmds();
    string *exit_rooms = where->query_exit_rooms();

    while (++i < sizeof(exit_rooms))
    {
	if (exit_rooms[i]->query_location_type() == type)
	    return i;
    }
    return 0;
}
