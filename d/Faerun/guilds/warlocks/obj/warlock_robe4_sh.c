/*
*  /d/Faerun/guilds/warlocks/obj/warlock_robe4_sh.c
*
*  2018, Nerull
*
*/

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
#include "../guild.h";

inherit "/std/shadow";

#ifndef OBJ_ADJS
#define OBJ_ADJS ({"ebony-robed", "hooded"})
#endif


public void 
remove_warrobe_shadow()
{
    remove_shadow();
}


public void
init_warrobe_shadow()
{
    setuid();
    seteuid(getuid());
        
}


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
query_war_robed()
{
    return 1;
}
