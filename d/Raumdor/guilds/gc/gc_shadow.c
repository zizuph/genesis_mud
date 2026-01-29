/*
 * shadow which adds/masks some functions to check if a player is still
 * suitable to be member of gentleman's club
 */

inherit "/std/shadow";

#include "guild.h"

public int
add_gc_shadow(object who)
{
    return shadow_me(who);
}

public void
remove_gc_shadow()
{
    remove_shadow();
}

public string
query_m_in()
{
    return "arrives gallantly";
}

public string
query_m_out()
{
    return "leaves gallantly";
}
