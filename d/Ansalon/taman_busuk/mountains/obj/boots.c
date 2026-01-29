/* Stralle @ Genesis 030824
 */

/**
 * Navarre January 31st 2007
 * - Added Prop OBJ_I_IS_MAGIC_ARMOUR
 */

#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_pname("boots");

    set_adj(({"knee-high", "brown"}));

    set_short("pair of knee-high brown boots");
    set_pshort("pairs of knee-high brown boots");
    set_long("These boots are made of thick brown leather that " +
        "protects both the feet as well as the lower legs. " +
        "They are crafted in the fashion of the plains " +
        "warriors of Nordmaar, offering both finesse and style.\n");
    
    set_af(this_object());
    set_at(A_FEET | A_LEGS);
    set_ac(30);

    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "Originating from Nordmaar, this was the footwear of higher " +
        "ranking plains warriors that craved for garment that " +
        "aided them in their hunts and battles.\n", 10,
        "Wearing these boots one is allowed swifter movement.\n", 20,
        "While walking feet in these boots one will not tire as " +
        "quickly.\n", 30 }));
    add_prop(OBJ_S_WIZINFO, "Hobbits are not allowed to wear these " +
        "boots (they don't fit them). By wearing them the player " +
        "is given a shadow that will raise LIVE_I_QUICKNESS and " +
        "increase the rate fatigue heals.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_M_NO_BUY, 1);
}

mixed
wear()
{
    string basename, *arr;
    object sh;

    if (this_player()->query_race_name() == "hobbit")
        return "Try as you might, these boots could not possibly fit you.\n";

    setuid();
    seteuid(getuid());
    
    arr = explode(explode(file_name(this_object()), "#")[0], "/");
    basename = implode(arr[0 .. sizeof(arr) - 2], "/");
    /* Shadow will take care of fatigue
     */
    sh = clone_object(basename + "/boots_sh");
    sh->shadow_me(this_player());

    this_player()->add_prop(LIVE_I_QUICKNESS,
        this_player()->query_prop(LIVE_I_QUICKNESS) + 20);
    (this_player()->query_combat_object())->cb_update_speed();


    write("You slip into the " + short() + ", feeling very comfortable.\n");
    say(QCTNAME(this_player()) + " slips into the " + short() + ".\n");
    return 1;
}

mixed
remove()
{
    query_worn()->remove_boots_shadow();
    query_worn()->add_prop(LIVE_I_QUICKNESS,
        query_worn()->query_prop(LIVE_I_QUICKNESS) - 20);
    (query_worn()->query_combat_object())->cb_update_speed();

    return 0;
}
