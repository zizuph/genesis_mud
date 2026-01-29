/*
 *  /d/Gondor/arnor/weapons/common_club.c
 *  wielded by /d/Gondor/arnor/npc/massive_troll.c
 *  common club wielded by the troll.
 */ 

inherit "/std/weapon";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("club");
    set_short("massive splintered club");
    set_pshort("massive splintered clubs");
    set_adj(({"massive", "splintered"}));
    set_long("This club is enormous and heavy, made simply from a long piece of wood. It looks old and splintered.\n");
    add_prop(OBJ_I_WEIGHT, 7500);
    set_default_weapon(35, 35, W_CLUB, W_BLUDGEON, W_ANYH, 0);
}
