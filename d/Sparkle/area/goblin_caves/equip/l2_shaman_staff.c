/*
 * Shaman staff on level 2
 * - Boreaulam, Aug 2014
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

/*
 * Function name:        create_weapon
 * Description  :        constructor for the object
 */
void
create_weapon()
{

    set_name("staff");
    set_adj("wooden");
    add_adj("black");
    set_short("black wooden staff");
    set_long("Crafted from a heavy black wood, this long staff is slightly " +
        "curved with a deadly looking spike affixed to the tip. The smooth " +
        "wooden shaft is quite solid and study enough to almost feel as " +
        "if the staff was made from metal.\n");

	int wc = 30 + random (10); 
    set_hit(wc);
    set_pen(wc);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(wc, wc) + random(200));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(wc, W_POLEARM));

    set_hands(W_BOTH);
    
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(25);    
} /* create_weapon */

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
