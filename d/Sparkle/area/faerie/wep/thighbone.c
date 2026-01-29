/*
 * Thighbone fasioned into a club-like weapon by the orcs of Faerie
 * by Finwe, 2007
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 48,
    pen = 48;
void
create_weapon()
{

    seteuid(getuid());

    set_name("club");
    add_name("thighbone");
    add_name("bone");
    add_name("thigh");
    add_name("_orc_thighbone_");
    set_adj("heavy");
    set_short("heavy sturdy thighbone"); 
    set_long("This is a " + short() + ". It is from a tall elf and an enemy of the orc lord. It is encased in iron to make it stronger and used as a club. Dark runes decorate the bone.\n");
    
    set_hit(hit);
    set_pen(pen);
    set_wt(W_CLUB);
    set_dt(W_IMPALE | W_BLUDGEON);
    
    add_prop(OBJ_I_WEIGHT,2700);
    add_prop(OBJ_I_VOLUME,2500);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    add_prop(MAGIC_AM_MAGIC,({ 15, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"This thighbone seems to be magical.\n",1,
    "It was cursed by the shamans of the orcs and is a prized possession of theirs.\n",25,
    "The enchanted thighbone can do more damage than most weapons.\n",30 }));

    add_item(({"runes", "dark runes"}),
        "The dark runes decorate the weapon and look twisted and undecipherable. They seem to glow and radiate pure evil.\n");
    add_item(({"iron"}),
        "It is knicked from constant use. The iron is rough and covered with dried blood of the orc lord's enemies. Runes cover it.\n");

    set_hands(W_LEFT); 
    set_keep(1);

}

