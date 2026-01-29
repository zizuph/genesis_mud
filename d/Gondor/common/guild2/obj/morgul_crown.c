/*
 * /d/Gondor/common/guild2/obj/nazgul_crown.c
 *
 * The crown of the Lord of Morgul, Lord of the Nazgul
 *
 * Olorin, August 1994
 *
 * 
 * Modifications:
 *
 *   Toby, 2008-02-13: Changed weight from 7200 to 1200
 */
#pragma save_binary

inherit "/std/armour";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

int query_value() { return 0; }

void
create_armour()
{
    set_name("crown of steel");
    add_name(({"crown", "nazgul crown", "crown of morgul", }));
    add_name(MORGUL_MORGUL_CROWN);
    set_adj(({"steel", "morgul", "nazgul", "black", }));
    set_short("crown of steel");
    set_long("A ring of black steel with three points, the Crown of Morgul.\n");

    set_ac(5);
    set_af(TO);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_NO_DROP, 1);

    FIX_EUID
}

mixed
wear(object ob)
{
    object  tp = TP;

    if (ob != TO)
        return -1;

    if ((tp->query_guild_name_occ() == GUILD_NAME) && (tp->query_nazgul() > 1))
    {
        write("You wear the "+query_short()+" on your head.\n"+
              "You feel the dark power of Black Sorcery flowing through you.\n");
        say(QCTNAME(tp)+" wears "+LANG_ASHORT(TO)+".\n");
        return 1;
    }
    tp->heal_hp(-(tp->query_max_hp()/10));
    set_alarm(0.0, 0.0, remove_object);
    return "When you try to wear the "+query_short()+", it glows red hot and disappears.\n";
}

string
query_recover()
{
    return 0;
}
