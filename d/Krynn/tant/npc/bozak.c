#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <wa_types.h>

inherit BOZAK;
inherit "/lib/unique";

#define WEP1 "/d/Krynn/common/weapons/flame_glaive"
#define WEP2 "/d/Krynn/common/weapons/light_halberd"
#define WEP3 "/d/Ansalon/common/wep/pole/roncone"
#define ARM1 ARMOUR + "barmour1"
#define ARM2 ARMOUR + "bleggings"
#define ARM3 ARMOUR + "bheavyboots"
#define ARM4 ARMOUR + "brobe"
#define ARM5 ARMOUR + "bhelmet"

void arm_me(object me);

void
create_bozak()
{
    if (!IS_CLONE)
        return;

    arm_draconian_called = 1;
    /* Necessary so that Gakhan does not automatically wield
    standard draconian equipment */
    set_alarm(1.0, 0.0, &arm_me(this_object()));
}

void
arm_me(object me)
{
    seteuid(getuid(me));
    object weapon;

    weapon = clone_unique(WEP1, 5, WEP2);

    if(!weapon->id("glaive"))
    {
        weapon->remove_object();
        weapon = clone_unique(WEP3, 7, WEP2);
    }
    weapon->move(me, 1);
    command("wield all");

    clone_object(ARM1)->move(me,1);
    clone_object(ARM2)->move(me,1);
    clone_object(ARM3)->move(me,1);
    clone_object(ARM4)->move(me,1);
    clone_object(ARM5)->move(me,1);
    command("wear all");
}
