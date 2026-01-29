/*
 * glowinghelmet.c
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

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

int hitsleft;
#define MAXNRHITS 20

void
to_coal()
{
    remove_prop(OBJ_I_LIGHT);
    remove_prop(MAGIC_I_RES_COLD);

    set_ac(-3);
    set_short("coal helmet");
    set_adj("coal");
    set_long("If you call this poor excuse for a helmet an armour you are crazy.\n");

    if (wearer)
        wearer->update_armour(this_object());
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "#ggg#" + hitsleft + "#";
}

void
init_recover(string arg)
{
    string foobar;
    init_arm_recover(arg);
    sscanf(arg, "%s#ggg#%d#%s", foobar, hitsleft, foobar);
    if (hitsleft)
        return;
    to_coal();
}

void
create_armour()
{
    set_short("glowing helmet");
    set_long("This helmet is obviously some kind of magic item.\n");
    set_name("helmet");
    set_adj("glowing");

    set_ac(18);
    set_am(({-1, 1, 0}));

    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(MAGIC_I_RES_COLD, ({50, 1}));

    hitsleft = MAXNRHITS;
}

void
got_hit(int hid, int ph, object att, int dt, int dam)
{
    ::got_hit(hid, ph, att, dt, dam);

    if (hitsleft <= 0)
        return;

    att->hit_me(random(dam) / 2, 0, wearer, 0);
    att->catch_msg("You burn yourself on the glowing helmet!\n");
    wearer->catch_msg(QCTNAME(att) +
                      " is hurt by the glowing helmet's fire\n");
    hitsleft--;
    if (hitsleft == 0)
    {
        wearer->catch_msg("The fire of the glowing helmet goes out.\n" +
                          "On your head remains only a coal layer.\n");

        to_coal();
    }
}
