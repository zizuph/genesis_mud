/* Lucius made shadow
 * For me
 * Created by Destiny 11/Y2K
 * Updated to be used in Genesis 
 * By Damaris 11/Y2K
 */
inherit "/std/shadow";
#include "guild.h"
public int
add_hat_shadow(object who)
{
    return shadow_me(who);
}

public void
remove_hat_shadow()
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

