/*
 * glowingmail.c
 *
 * Used in npc/refnas.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#define MAXNRHITS 35            /* a VERY funny feature :) */

int goggagres;

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "#ggg#" + goggagres + "#";
}

void
init_recover(string arg)
{
    string apa;
    init_arm_recover(arg);
    sscanf(arg, "%s#ggg#%d#%s", apa, goggagres, apa);

    if (!goggagres)
        return;

    set_ac(-5);                 /* coal in the wounds :) */

    if (wearer)
        wearer->update_armour(this_object());

    goggagres = 1;

    set_short("coal mail");
    set_adj("coal");
    remove_prop(OBJ_I_LIGHT);
    remove_prop(MAGIC_I_RES_COLD);
    remove_prop(MAGIC_I_RES_FIRE);
}

void
create_armour()
{
    set_name("mail");
    add_name("platemail");

    set_short("glowing platemail");
    set_adj(({"plate", "glowing", "glowing plate"}));
    set_long("This mail has been manufactured by some wizard...\n");
    set_ac(40);
    set_am(({0, 0, 0}));                  /* impale,slash,bludgeon */

    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT, 17000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(MAGIC_I_RES_COLD, ({50, 1}));

    goggagres = 0;
}

void
got_hit(int hid, int ph, object att, int dt, int dam)
{
    ::got_hit(hid, ph, att, dt, dam);

    if (goggagres)
        return;

    att->hit_me(random(dam), 0, wearer, 0);
    att->catch_msg("You burn yourself on the glowing mail!\n");
    tell_room(E(TO), QCTNAME(att) + " is hurt by the glowing mail's fire\n");

    if (hits >= MAXNRHITS)
    {
        wearer->catch_msg("The fire of the glowing mail goes out.\n" +
                          "Remaining is only a thin layer of coal, " +
                          "offering hardly no protection at all.\n");
        att->catch_msg("The glowing mail of your enemy fades...\n");

        set_ac(-5);             /* coal in the wounds :) */

        wearer->update_armour(this_object());

        goggagres = 1;

        set_short("coal mail");
        set_adj("coal");
        remove_prop(OBJ_I_LIGHT);
        remove_prop(MAGIC_I_RES_COLD);
        remove_prop(MAGIC_I_RES_FIRE);
        wearer->command("scream");
    }
}
