/*
 * glowingshield.c
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

void hackspett();

int hitsleft;

#define MAXNRHITS 20

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

    remove_prop(OBJ_I_LIGHT);
    remove_prop(MAGIC_I_RES_COLD);
    remove_prop(MAGIC_I_RES_FIRE);

    hackspett();
}

void
create_armour()
{
    set_am(({0, 0, 0}));
    set_name("shield");
    set_adj("glowing");
    set_short("glowing shield");
    set_long("Ancient magic has created this shield of fire.\n");
    set_ac(15);
    set_at(A_SHIELD);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(MAGIC_I_RES_COLD, ({25, 1}));

    hitsleft = MAXNRHITS;
}

void
hackspett()
{
    if (wearer)
    {
        wearer->catch_msg("Remaining is only a tiny coal plate.\n");
        wearer->update_armour(this_object());
    }
    set_short("tiny coal plate");
    set_name("plate");
    set_adj(({"tiny", "coal"}));
    set_long("This is the most ridiculous excuse for an armour ever seen!\n");
    set_ac(-2);
}

void
got_hit(int hid, int ph, object att, int dt, int dam)
{
    ::got_hit(hid, ph, att, dt, dam);

    if (hitsleft <= 0)
        return;

    att->hit_me(random(dam), 0, wearer, 0);
    att->catch_msg("You burn yourself on the glowing shield!\n");
    wearer->catch_msg(QCTNAME(att) +
                      " is hurt by the glowing shield's fire\n");
    hitsleft--;
    if (hitsleft == 0)
    {
        wearer->catch_msg("The fire of the glowing shield goes out...\n");
        remove_prop(OBJ_I_LIGHT);
        remove_prop(MAGIC_I_RES_COLD);
        hackspett();
    }
}
