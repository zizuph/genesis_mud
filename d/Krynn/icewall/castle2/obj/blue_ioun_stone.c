/* Navarre June 11th 2006: Added keep option */
/* Navarre September 4th 2014: Added set_keep(1) as default keep setting 
 *
 * 2020-12-23 - Cotillion
 * - Add item expiration and keep recovery
 *       Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 35.
*/

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

inherit "/lib/keep";
inherit "/lib/item_expiration";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_object()
{
    set_name("stone");
    set_adj("night-blue");

     set_long("The small night-blue stone seems to glimmer strangely. " +
       "It looks like one of the fabled ioun stones, but what powers " +
       "this one possesses, only a sage would know.\n");
 
    add_prop(OBJ_I_WEIGHT, 235);
    add_prop(OBJ_I_VOLUME, 79);
    add_prop(OBJ_I_VALUE, 3 * 12 * 12 * 12);
  
    add_prop(MAGIC_AM_MAGIC, ({ "enchantment", 30 }));

    add_prop(MAGIC_AM_ID_INFO, ({
	"There is something magical about the stone.\n", 1,
	"When held, the stone will grant you with the ability of " +
        "infravision.\n", 30 }) );

    add_prop(OBJ_S_WIZINFO, "This magic stone gives infravision.\n");

    // will_not_recover = (random(100) < 80);

    set_slots(W_ANYH);
    set_keep(1);
    set_item_expiration();

    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(35);          
}

public mixed
hold()
{
    write("As you grasp the night-blue ioun stone in your hand, " +
        "darkness explodes into colors.\n");
 
    /* Add 3 points of night vision to the player. */
    this_player()->add_prop(LIVE_I_SEE_DARK,
        (this_player()->query_prop(LIVE_I_SEE_DARK) + 3));

    return 0;
}

public mixed
release()
{
    /* Remove the 3 points of night vision again. */
    this_player()->add_prop(LIVE_I_SEE_DARK,
        (this_player()->query_prop(LIVE_I_SEE_DARK) - 3));

    write("As you release the night-blue ioun stone, " +
        "you lose the power of infravision.\n");

    return 0;
}


public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();

    write(item_spellpower_desc());
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_item_expiration_recover(arg);
}

public string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover() + query_keep_recover();
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
