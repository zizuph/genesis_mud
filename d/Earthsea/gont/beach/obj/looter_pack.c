/* coded by Amelia, 7/97 */

#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

public void
create_wearable_pack()
{
    set_keep();
    set_mass_storage(1);
    set_name("backpack");
    add_name("equipment");
    add_name("pack");
    add_pname("backpacks");
    add_pname("packs");
    add_adj("looter's");
    add_adj("brown");
    add_adj("leather");
    set_short("brown looter's backpack");
    set_long("A very worn backpack made from " +
        "brown leather. It is used by the local scavengers to " +
        "collect their loot in. You feel that it could hold a " +
        "large amount of items. Use <help backpack> for commands.\n");
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_WEIGHT, 125);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(CONT_I_WEIGHT, 1600);
    add_prop(CONT_I_VOLUME, 1800);
    add_prop(OBJ_I_LIGHT, 0);
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

public void
init_recover(string args)
{
    init_container_recover(args);
}

public int
help_backpack(string str)
{
    object bearer = this_player(), to = this_object();

    if(id(str))
    {
        if(present(to, bearer))
        {
            write("You can <fill backpack> " +
                "and <empty backpack>, as well as <wear backpack> and " +
                "<remove backpack>.\n");
            return 1;
        }
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(help_backpack, "help");
}
