/*
 * Standard Equipment for Test NPCs
 *
 * This is a test 40/40 2-handed sword.
 * 
 * Created by Petros, September 2011
 */
 
inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon ()
{
    set_name("sword");
    set_short("typical two-handed 40/40 sword");
    add_adj( ({"typical" }) );
    set_long("This is a standard 40/40 2-handed sword for testing.\n");
    set_hit(40);
    set_pen(40);

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(40);

    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 10000);
}

public int
set_dull(int du)
{
    return 1;
}

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
