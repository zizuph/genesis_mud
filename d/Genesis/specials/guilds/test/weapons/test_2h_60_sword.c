/*
 * Standard Equipment for Test NPCs
 *
 * This is a test 60/60 2-handed sword.
 * 
 * Created by Petros, February 2009
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
    set_short("typical 60/60 sword");
    add_adj( ({"typical" }) );
    set_long("This is a standard 60/60 2-handed sword for testing.\n");
    set_hit(60);
    set_pen(60);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(60);

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
