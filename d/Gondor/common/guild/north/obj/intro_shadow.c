/*
 * The shadow that modifies add_introduced
 *
 * 960117 by Rastlin
 * Modified by Elessar, 1998
 */

#include "camo.h"

inherit "/std/shadow";

public void
add_introduced(string name)
{
    shadow_who->add_prop(CAMO_I_GOT_INTRO, 1);

    shadow_who->add_introduced(name);
}

