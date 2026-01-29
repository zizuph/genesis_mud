/*
 * A bloody nice robe, that is the reward of the White Towers quest.
 * Cloned by /d/Shire/common/obj/tower_chest.c if I'm not mistaking. :-)
 *                      Another fine Tricky product, march 1993.
 */

inherit "/std/armour";

#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    /* Set the name, short description and long description */
    set_name("robe");
    set_adj(({"heavy","kingly"}));
    set_short("heavy and kingly robe");
    set_pshort("heavy and kingly robes");
    set_long("The robe looks fit for a king to wear, and looks quite "
           + "protective. It is a bit heavy, but that is because it "
           + "has iron thread woven on the inside.\n");
    /* The armour is found after doing a quest. */
    set_ac(30);

    /*        impale, slash, bludgeon */
    set_am(({   2,     -4,      2 }));

    /* We also need to set what type of armour this is */
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT, 10000); /* 10 Kg? ;-) */
    add_prop(OBJ_I_VOLUME, 4000); /* 4 Ltr */
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void
init_recover(string arg)
{
    init_arm_recover(arg);
}
