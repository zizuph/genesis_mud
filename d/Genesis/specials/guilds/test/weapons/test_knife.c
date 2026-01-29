/*
 * Standard Equipment for Test NPCs
 *
 * This is a test 30/30 knife
 * 
 * Created by Petros, May 2013
 *
 * Change hit/pen, weight and volume to something more representative
 *    - Ckrik 6/9/2021
 */
 
inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon ()
{
    set_name("knife");
    set_short("typical knife");
    add_adj( ({"typical" }) );
    set_long("This is a standard 30/30 knife for testing.\n");
    set_hit(30);
    set_pen(30);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(40);

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 2000);
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
