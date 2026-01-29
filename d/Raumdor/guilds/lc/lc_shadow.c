/*********************************************************************
 * - lc_shadow                                                     - *
 * - this shadow which adds/masks some functions to check if a     - *
 * - player is still suitable to be member of Ladies club          - *
 * - This code is taken from the Gentleman's Club                  - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/

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
    return "arrives flawlessly poised";
}

public string
query_m_out()
{
    return "leaves with a lure of finesse";
}
