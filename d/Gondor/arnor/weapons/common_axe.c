/*
 *  /d/Gondor/arnor/weapons/common_axe.c
 *  wielded by /d/Gondor/arnor/npc/massive_troll.c
 *  common axe wielded by the troll.
 */ 

inherit "/std/weapon";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("axe");
    set_short("dull stone axe");
    set_pshort("dull stone axes");
    set_adj(({"dull", "stone"}));
    set_long("This axe is made from a very large stone, sharpened clumsily, and strapped to a long wooden handle with strips of leather.\n");
    add_prop(OBJ_I_WEIGHT, 8500);
    set_default_weapon(35, 35, W_AXE, W_BLUDGEON | W_SLASH, W_ANYH, 0);
}
