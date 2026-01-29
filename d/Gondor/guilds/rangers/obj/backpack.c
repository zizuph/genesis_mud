/*
 * /d/Gondor/common/guild/obj/backpack.c
 *
 * A backpack to carry stuff in. It has sell-protection.
 *
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Composed by the best parts from Mercade's rucksack and
 * Maniac's backpack.   For the Rangers, by Elessar, May 1994.
 *
 * Modified the backpack so it can be inherited for other
 * backpacks, sacks, etc with different descriptions.
 * Olorin, 30-may-1995
 *
 * Inherit /d/Genesis/std/pack, conform to domain.rules
 * Gnadnar, 19-Mar-1998
 */
inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define NO_SELL_VBFC &no_sell_vbfc()

static string fill_verb = "fillpack", empty_verb = "emptypack", backpack_long;

/* Prototypes */
public void     create_backpack();
nomask void     create_wearable_pack();
public void     set_backpack_long(string s);
public string   query_backpack_long();
public void     set_fill_verb(string s);
public void     set_empty_verb(string s);
public string   long_description();
public mixed    no_sell_vbfc();
public void     init();
public void     set_keep(int keep);
public int      query_keep();
public string   query_recover();
public void     init_recover(string arg);
public void     tmp_add_prop(mixed setting, object tp);
public string   query_auto_load();
public int      myfillpack();
public int      myemptypack();


/*
 * Function name: create_backpack
 * Description  : Backpack configuration
 */
public void
create_backpack()
{
    set_name(({ "backpack", "pack", "rucksack", "knapsack" }));
    add_pname(({ "backpacks", "packs", "rucksacks", "knapsacks" }));
    add_adj(({ "large", "green", "mottled-green", "green-coloured" }));
    set_short("large mottled-green backpack");
    set_pshort("backpacks");
    set_backpack_long("The backpack is rather large and "
        + "made of a very light, yet strong material. Its colours are "
        + "various shades of green so that it offers the best possible "
        + "camouflage for the travelling Rangers.");
}

/*
 * Function name: create_wearable_pack
 * Description  : Basic pack configuration
 */
nomask void
create_wearable_pack()
{
    add_prop(OBJ_I_VALUE,             200);
    add_prop(CONT_I_CLOSED,             1);
    add_prop(CONT_I_WEIGHT,          2000);
    add_prop(CONT_I_VOLUME,          2500);
    add_prop(CONT_I_MAX_WEIGHT,    150000);
    add_prop(CONT_I_MAX_VOLUME,    150000);
    add_prop(CONT_I_REDUCE_VOLUME,    125);
    remove_prop(CONT_I_RIGID);

    /* call this after props so inheriting packs may change value, size */
    create_backpack();

    set_long(long_description);

    set_keep(1);
    set_mass_storage(1); 

}

public void
set_backpack_long(string s)
{
    backpack_long = s;
}

public string
query_backpack_long()
{
    return backpack_long;
}

public void
set_fill_verb(string s)
{
    fill_verb = s;
}

public void
set_empty_verb(string s)
{
    empty_verb = s;
}

/*
 * Function name: long_description
 * Description  : append instructions for use to the normal description
 * Returns      : string -- the complete description
 */
public string
long_description()
{
    string long_desc = query_backpack_long();

    long_desc += " If you type '" + fill_verb + "' you can put all "
        + "unequipped items, except money and containers into the "
        + query_name()+". And if you type '" + empty_verb + "' you fetch "
        + "all the items from the " + query_name() + " again. ";

    if (query_keep())
    {
        long_desc += "At present, the " + query_name() + " is protected "
            + "so you will not sell it when selling equipment. Do <unkeep "
            + query_name() + "> to remove the protection.";
    }
    else
    {
        long_desc += "Whenever you sell equipment, you might sell the " 
            + query_name() + ". To prevent yourself from selling it you "
            + "may <keep " + query_name() + "> to protect it.";
    }

    return (long_desc + "\n");
}

/*
 * Function name: no_sell_vbfc
 * Description  : VBFC for OBJ_M_NO_SELL
 * Returns      : int -- 0 if may be sold or
 *                string -- msg if may not be sold
 */
public mixed
no_sell_vbfc()
{
    if (sizeof(all_inventory(TO)))
    {
        return ("The " + query_name() + " is not empty at the "
          + "moment. Please empty it before you sell it, to "
          + "prevent loss of property.\n");
    }
    return 0;
}

/*
 * Function name: init
 * Description  : continue to accept fill_verb and empty_verb,
 *                as well as "fill" and "empty"
 */
public void
init()
{
    ::init();
    add_action(myfillpack, fill_verb);
    add_action(myemptypack, empty_verb); 
}

/*
 * Function name: set_keep
 * Description  : mask parent to prevent selling non-empty pack
 * Arguments    : int keep -- whether or not to keep
 */
public void
set_keep(int keep = 1)
{
    if (keep)
    {
        ::set_keep(keep);
        return;
    }

    add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
}

/*
 * Function name: query_keep
 * Description  : query current 'keep' status
 * Returns      : int -- 1 if keep protected, 0 if not
 */
public int
query_keep()
{
    return (query_prop_setting(OBJ_M_NO_SELL) != NO_SELL_VBFC);
}

/*
 * Function name: query_recover
 * Description  : check whether pack is recoverable (it is)
 * Returns      : string -- the recovery string
 */
public string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

/*
 * Function name: init_recover
 * Description  : set the recovery vars
 * Arguments    : string arg -- the arguments to parse
 */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_container_recover(arg);
}

/*
 * Function name: tmp_add_prop
 * Description  : add OBJ_M_NO_DROP prop again
 * Arguments    : mixed setting -- value of OBJ_M_NO_DROP
 *                object tp -- this_player
 */
public void
tmp_add_prop(mixed setting, object tp)
{
    /* Add prop only if backpack is still in player's inventory */
    if (objectp(tp) && objectp(ENV(TO)) && (tp == ENV(TO)))
    {
        add_prop(OBJ_M_NO_DROP, setting);
    }
}

/*
 * Function name: query_auto_load
 * Description  : remove the OBJ_M_NO_DROP property if it is set so the
 *                backpack and its contents are not lost when player quits.
 * Returns      : 0 -- doesn't autoload
 */
public string
query_auto_load()
{
    mixed setting;

    if (setting = query_prop_setting(OBJ_M_NO_DROP))
    {
        remove_prop(OBJ_M_NO_DROP);
        set_alarm(0.1, 0.0, &tmp_add_prop(setting, ENV(TO)));
    }
    return 0;
}

/*
 * Function name: myfillpack
 * Description  : handle fill_verb
 * Returns      : 1 on success, 0 on failure
 */
public int
myfillpack()
{
    return fill_pack(query_name());
}


/*
 * Function name: myemptypack
 * Description  : handle empty_verb
 * Returns      : 1 on success, 0 on failure
 */
public int
myemptypack()
{
    return empty_pack(query_name());
}

