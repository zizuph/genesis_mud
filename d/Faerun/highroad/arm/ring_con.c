/*
 * Magic ring
 * -- Finwe, November 2008
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("ring");
    set_pname("rings");
    set_adj(({"decorated","silver"}));
    set_short("decorated silver ring");
    set_pshort("decorated silver rings");
    set_long("The ring is small and forged of silver. The band is wide and decorated with a motif of entwined vines. It feels cold and is polished smooth.\n");

    add_item(({"vines", "entwined vines"}),
        "They are engraved on the band and look very alive.\n");

    set_ac(5);
    set_at(A_ANY_FINGER);
    set_af(TO);

    add_prop(OBJ_I_VALUE, 1500);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 100);

    add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,({"This gives the wearer increased constitution\n",20}));
    add_prop(OBJ_S_WIZINFO,"This add 15 points of con to whoever wears "+
    "it.\n");
}
int
wear(object ob)
{
    int stat;
    stat = ENV(ob)->query_stat_extra(SS_CON);
    ENV(ob)->set_stat_extra(SS_CON,stat + 15);
    write("The ring warms on your finger and the vines pulsate with life.\n");
    return 0;
}

int
remove(object ob)
{
    int stat,stat2;
    set_this_player(query_worn());
    write("The ring suddenly grows cold and the life drains from the vines.\n");
    stat = TP->query_stat_extra(SS_CON);
    TP->set_stat_extra(SS_CON,stat - 15);
    return 0;
}

