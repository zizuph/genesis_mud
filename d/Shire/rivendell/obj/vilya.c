/*
 * Vilya, the elven rings.
 *
 * It is worn by Elrond in Imladris.
 * This ring is generated once per reboot and 
 * only obtained by killing Elrond.
 *
 * Based on the herald prayerbook.
 *
 * Finwe June 1998
 */
#pragma strict_types
#pragma save_binary
 
inherit "/d/Genesis/magic/spellcasting";
inherit "/std/armour";
inherit "/lib/keep";
 
 
// Spells 
 
// inherit SPELLS_DIR + "palantir"      /* scry */
 
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
//#include SPELLS_DIR + "spells.h" 
 
void
create_armour()
{
    set_name("ring");
    add_name("_vilya_elf_ring_");
    set_adj(({"simple", "golden"}));
    set_long("This ring is made of white gold with a large " +
        "emerald set into it. It is Vilya, Ring of Air, and " +
        "mightiest of the Three Rings of the Elves. Originally " +
        "worn by Gil-galad, the ring was then given to Elrond " +
        "by him.\n");
    
    add_item(({"vilya", "Vilya", "Ring of Air", 
            "ring of air","elven ring", "elvish ring"}),
        "The ring is made of white gold. It is smooth to the " +
        "touch and has a large emerald set into it. Across the " +
        "surface, both inside and outside the ring, flowing " +
        "elvish script can be seen\n");
    add_item(({"flowing elvish script", "elvish script", "script"}),
        "@@read_script@@");
    add_item(({"emerald", "large emerald"}),
        "The emerald is set into the ring in a solitare style. " +      
        "The jewel is deep green and sparkles as if it holds " +
        "the light of countless stars.\n");
 
    set_at(A_L_FINGER);
    set_ac(0);
    set_am(({0, 0, 0}));
    set_keep(1);
     
    add_prop(OBJ_M_NO_SELL,     1);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_I_WEIGHT, 7);
    add_prop(OBJ_I_VOLUME, 32);
    remove_prop(OBJ_I_VALUE);
 
 
}
 
string read_script()
{
  return "nice ring.\n";
}
