/*
 * /d/Gondor/common/guild/obj/hood_shadow.c
 *
 * A shadow to change the adjectives of a player wearing a hood.
 *
 * Olorin, December 1996
 *
 * Copyright (c) 1996 by Christian Markus
 */
#pragma save_binary
#pragma strict_types

inherit "/std/shadow.c";

/*
 * There are (at least) four functions in /std/object.c to check
 * the adjectives set in an object. In this shadow, I shadow them all.
 * parse_command_adjectiv_id_list() is necessary so that parse_command()
 * works with the new adjectives.
 */

// Global variables:
static string *Hood_Adjs = ({ "green-cloaked", "hooded" });

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
    return query_list(Hood_Adjs, arg);
}

public string *
query_adjs() 
{ 
    return query_list(Hood_Adjs, 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, Hood_Adjs) >= 0);
}

public string *
parse_command_adjectiv_id_list()
{
    return Hood_Adjs + ({ query_shadow_who()->query_gender_string() });
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
 * Function name: set_hood_adjs
 * Description:   Set the adjectives used for hooded players.
 * Argument:      *adjs - the two adjectives
 * Returns:       1 / 0 - success / failure
 */
public int
set_hood_adjs(string *adjs)
{
    if (!pointerp(adjs) || (sizeof(adjs) != 2))
        return 0;

    Hood_Adjs = adjs;
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

