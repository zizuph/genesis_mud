/*
 *  An example shop coded by Nick, some Ideas and part of code taken from
 *  Tricky's shop in Hobbitown.
 */
/* Revision history:
 * ---------------------
 * April 2000 by Boron added support for warfare tax
 *
 */

/**
 * Added check on ::do_sell, to make the shopkeeper not say
 * thank you for the business unless you actually sold something
 *
 * -- Navarre, February 3rd 2007.
 */


#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/local.h"
#include <macros.h>
#include DELIVERY

inherit SOLINROOM;
inherit DELIVERY_OFFICE;
//inherit "/w/boron/open/lib/shop";
//inherit WARSHOP;
inherit "/d/Emerald/lib/shop_list";

#define STORE_ROOM TDIR + "store"
#define MAXLIST    30
#define TORCH      OBJ + "torch"

object bin;

void
reset_solace_room()
{
    if(!objectp(bin))
    {
        bin = clone_object("/d/Genesis/start/human/obj/trash_can");
        bin->move(TO, 1);
    }
}


/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_solace_room()
{
    config_default_trade();
    set_short("The local shop");
    set_long("You are in the local shop. Here you can sell and buy stuff. " +
         "You can also use value or list commands, 'list armours', " +
         "'list weapons', 'list <name>' and 'list' works too. " +
         "There is also a small sign to read with more instructions. " +
         "A new poster has been hung onto one of the walls. The exit " +
         "from the shop is to the west. There is also a locked door " +
         "leading north.\n");

    add_exit(TDIR + "bridge_walk12", "west", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    add_item("bridge",
        "It's made out of wood and look safe to travel, in fact, most\n" +
        "people does here in solace.\n");
    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");
    add_item("poster","It's readable.\n");
    add_cmd_item("poster","read",
         "Delivery Office Solace\n" +
         "'Ask for a delivery tour' if you wish to help out and earn " +
         "a few coins.\n All you need to do with the packet you " +
         "receive then is to bring it to\n its destination where you " +
         "will also receive the payment. Use 'deliver\n packet' to " +
         "deliver your packet at its destination. 'Return packet' " +
         "is\n for packets which are not destined for this office " +
         "and which do not\n have this office set as origin.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    set_store_room(STORE_ROOM);
    set_office("the Shop in Solace",15);
    add_content(TORCH);

    // Added for warfare support
    //TO->create_warshop();
    //set_shop_war_area(WAR_AREA_SOLACE);
    //set_tax(15);

    reset_solace_room();
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
    init_shop();//init_shop;// /* Get the commands from the warshop */
    init_office(); /* Get the commands from the delivery office */
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
    write("Some magic force keeps you from going north.\n");
    say(QCTNAME(this_player()) + " tries to go north but fails.\n");
    return 1;
}


void
print_message(string str)
{
    write("The shopkeeper says: " + str + "\n");
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
