/*
 * Standard Equipment for Test NPCs
 *
 * This is a test 40/40 polearm
 * 
 * Created by Petros, March 2009
 */
 
inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon ()
{
    set_name("polearm");
    set_short("typical polearm");
    add_adj( ({"typical" }) );
    set_long("This is a standard 40/40 2-handed polearm for testing.\n");
    set_hit(40);
    set_pen(40);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hands(W_BOTH);

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(40);

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
