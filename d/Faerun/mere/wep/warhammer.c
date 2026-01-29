/*
 * Warhammer for the Shaman
 * Magical
 * by Finwe, July 2007
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define ADJ1 "runed"
#define WEAPON  "warhammer"

int hit = 45,
    pen = 47;
void
create_faerun_weapon()
{

    set_name("club");
    add_name("hammer");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_short(ADJ1 + " " + WEAPON); 
    set_long("This heavy warhammer has a broad striking head that can easily beat down your enemies. It is made of a strange, blood-red metal, which gleams with a strange light. Dark runes decorate the head.\n");
    
    add_item(({"head"}),
        "It is made of a strange, blood-red metal. The head is beak shaped and looks powerful enough to punch through armours. Dark runes are enscribed on it.\n");
    add_item(({"runes", "dark runes"}),
        "They are cryptic and in an unknown language. They glow with a pale orange light.\n");
    add_item(({"metal", "blood-red metal", "strange metal", 
            "strange blood-red metal"}),
        "It looks like steel, but is a blood-red color.\n");
    

    set_hit(hit);
    set_pen(pen);
    set_wt(W_CLUB); 
    set_dt(W_BLUDGEON | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, 
	     "This is a large warhammer that is enchanted with magic. It is wielded by the shaman in the Mere of Dead Men in Faerun\n");
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This weapon is magically enchanted.\n", 10,
		 "The weapon is enchanted to enable " +
		 "extra damage.\n", 45}));
    add_prop(MAGIC_AM_MAGIC, ({ 45, "enchantment" }));

    set_hands(W_LEFT); 
}

