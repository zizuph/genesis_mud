/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_mail.c
 *
 * Mergula's ringmail.
 *
 *
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
inherit "/lib/keep";

#define EVIL_LIM -100

public void
create_terel_armour()
{
    set_name("ringmail");
    set_short("blackened steel ringmail");
    set_long("It is a shirt of mail made with rings of blackened "+
        "steel. The quality is quite good, though the armour "+
        "itself is rather heavy. While the craftsmanship is "+
        "undeniably dwarven, it appears to have been made "+
        "for someone three or four times the size of a dwarf.\n");
    set_adj("steel");
    add_adj(({"blackened", "ring"}));

    set_default_armour(29, A_TORSO, 0, 0);

    set_af(this_object());
}
