
/*  Magic ring coded by Arren, November 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("ring");
    set_adj("silver");
    add_adj(({ "sapphire", "yellow sapphire", "runed", "elvish" }));
    set_short("silver ring");
    set_long(BSN(
    "A beautiful ring wrought by silver, and upon it is a sparkling yellow "+
    "sapphire. Fine elvish runes are written on the inside of the ring."));

    set_af(TO);
    set_default_armour(3, A_MAGIC);

    add_prop(MAGIC_AM_MAGIC, ({ 31, "abjuration" }));
    add_prop(MAGIC_AM_ID_INFO, ({ 
    "The ring seems to be magical.\n", 1,
    "The magic ring will protect you from physical damage.\n", 17 }));
    add_prop(OBJ_S_WIZINFO, BSN(
    "This ring gives an extra AC of 3 to all armour slots. "+
    "It is worn by the /d/Gondor/common/npc/barrow_wight.c. "));
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 450 + random(100));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}

int
wear(object ob)
{
    write("You wear the " + query_short() + " on your finger.\n");
    say(QCTNAME(TP) + " wears the " + query_short() + ".\n");
    return 1;
}

int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS });
}

public string 
query_recover() { return 0; }
