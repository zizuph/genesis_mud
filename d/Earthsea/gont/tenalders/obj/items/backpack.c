/*  coded by Amelia, 7/97 */

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
    add_name("_amelias_backpack");
    add_name("pack");
    add_pname("backpacks");
    add_pname("packs");
    add_adj("goatskin");
    add_adj("brown");
    set_short("goatskin backpack");
    set_pshort("goatskin backpacks");
    set_long("This is a backpack made from brown goatskin, " +
        "which has two straps that allow you to wear it on your " +
        "back. You feel that it could hold a large amount of " +
        "items. Use <help backpack> for commands.\n");
    add_item((({ "straps", "two straps" })),
        "The straps on the backpack allow you to wear it on " +
        "your back.\n");
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_WEIGHT, 125);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(CONT_I_WEIGHT, 1600);
    add_prop(CONT_I_VOLUME, 1800);
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
    if(id(str))
    {
        if(present(this_object(), this_player()))
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
