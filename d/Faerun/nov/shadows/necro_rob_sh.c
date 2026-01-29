#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <state_desc.h>
#include <wa_types.h>
#include "../nov.h";

inherit "/std/shadow";

public void
init_robe_shadow()
{
    setuid();
    seteuid(getuid());
        
}


#ifndef OBJ_ADJS
#define OBJ_ADJS ({"black-robed", "high-collared"})
#endif

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
        return 0;

    if (!arg && sizeof(list))
        return list[0];
    else
        return list + ({});
}

varargs public mixed
query_adj(int arg) 
{
    return query_list(OBJ_ADJS, arg);
}

public string *
query_adjs() 
{ 
    return query_list(OBJ_ADJS, 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, OBJ_ADJS) >= 0);
}

public string *
parse_command_adjectiv_id_list()
{
    return OBJ_ADJS + ({ query_shadow_who()->query_gender_string() });
}


int
query_necro_robed()
{
    return 1;
}


public void 
remove_shadow()
{
 
    ::remove_shadow();
}









