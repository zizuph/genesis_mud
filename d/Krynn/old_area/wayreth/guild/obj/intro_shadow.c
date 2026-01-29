/*
 * The Intro-shadow
 *
 * A shadow that temporary shadows add_introduced. Used by the hood-shadow.
 *
 * 960117 by Rastlin
 */

#include "../local.h"

inherit "/std/shadow";

public void
add_introduced(string name)
{
    shadow_who->add_prop(WOHS_I_GOT_INTRO, 1);

    shadow_who->add_introduced(name);
}

