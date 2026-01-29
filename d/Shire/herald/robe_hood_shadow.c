/*
 * Hood shadow for Herald's robe
 * Based on Morgul hood
 * Finwe, January 2004
 */

#include "/d/Shire/sys/defs.h"
inherit "/std/shadow";


/*
 * There are (at least) four functions in /std/object.c to check
 * the adjectives set in an object. In this shadow, I shadow them all.
 * parse_command_adjectiv_id_list() is necessary so that parse_command()
 * works with the new adjectives.
 */

#ifndef OBJ_ADJS
#define OBJ_ADJS ({"white-robed", "hooded"})
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



/*
 * This is used by the robe code to allow an easy check
 * if the hood is worn.
 */
int
query_hooded()
{
    return 1;
}

/*
 * Function   : remove_hood_shadow
 * Description: Removes this shadow.
 */
public void 
remove_hood_shadow()
{
    destruct();
}

