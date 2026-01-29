#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
#include <macros.h>

inherit THARK_IN;
inherit "/d/Emerald/lib/shop_list";

#define STORE_ROOM "/d/Krynn/tharkadan/room/dwarf/store"
#define MAXLIST    30
#define TORCH      "/d/Krynn/solace/new_village/obj/torch"

object bin;

void
reset_tharkadan_room()
{
    if(!objectp(bin))
    {
        bin = clone_object("/d/Genesis/start/human/obj/trash_can");
        bin->move(TO, 1);
    }
}

void
create_tharkadan_room()
{
    config_default_trade();
    set_short("The general store");
    set_long("You are in the general store of the dwarven village. " +
         "Here you can sell and buy stuff. " +
         "You can also use value or list commands, 'list armours', " +
         "'list weapons', 'list <name>' and 'list' works too. " +
         "There is also a small sign to read with more instructions. " +
         "The exit from the shop is to the west. There is also a " +
         "locked door leading north.\n");

    add_exit(ROOM + "dwarf/village1", "southwest", 0);
    add_invis_exit(STORE_ROOM, "north", "@@wiz_check");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");

    set_store_room(STORE_ROOM);

    reset_tharkadan_room();
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the warshop */
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int
wiz_check()
{
    if (this_player()->query_wiz_level())
        return 0;

    return 1;
}


void
print_message(string str)
{
    write("The dwarven shopkeeper says: " + str + "\n");
}

object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));


    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_sell(ob[i]))
            continue;


        if (ob[i]->query_prop(OBJ_I_VALUE) == 0)
        {
            shop_hook_sell_no_value(ob[i]);
            continue;
        }

        if (check && (ob[i]->query_worn() ||
            ob[i]->query_wielded()))
        {
            shop_hook_sell_worn_or_wielded(ob[i]);
            continue;
        }

        if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
        {
            shop_hook_sell_no_sell(ob[i], tmp);
            continue;
        }

        /* Save price if ob destructed in move */
        price = query_sell_price(ob[i]);

        if (price <= 0)
        {
            shop_hook_sell_no_value(ob[i]);
            continue;
        }

        if (err = ob[i]->move(store_room))
        {
            shop_hook_sell_object_stuck(ob[i], err);
            continue;
        }

        if (price > 0)
        {
            tmp_arr = calc_change(price, null, str);
            for (k = 0; k < sizeof(value_arr); k++)
                value_arr[k] += tmp_arr[k];

            sold[j] = ob[i];
            j++;
            if (j >= 20)
                break;
            /*
            * Only let people sell 20 objects at once and hopefully we wont get
            * those too long evaluation problems.
            */
        }
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0)
    {
        change_money(null_arr + value_arr, this_player());
        shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}


int
do_sell(string str)
{
    if(::do_sell(str))
    {
        print_message("Thank you for the business!");
        return 1;
    }
    return 0;
}
