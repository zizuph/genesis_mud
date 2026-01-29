/* /d/Emerald/lib/shop_room.c
 *
 * Inherit this into a shop room.
 *
 * Example:
 *
 * inherit "/d/Emerald/std/room";
 * inherit "/d/Emerald/lib/shop_room";
 *
 * void
 * create_emerald_room()
 * {
 *     set_short("shop");
 *     set_long("A nice shop.\n");
 *     add_default_store_sign();
 * }
 *
 * void
 * init()
 * {
 *     ::init();
 *     init_shop_room();
 * }
 */

void
add_default_store_sign()
{
    string str = "/lib/shop"->query_default_sign_text();
    this_object()->add_item("sign", str);
    this_object()->add_cmd_item("sign", "read", str);
}

int
shop_fail(string str)
{
    notify_fail("There is no one here to help you.\n");
    return 0;
}

void
init_shop_room()
{
    add_action(shop_fail, "buy");
    add_action(shop_fail, "sell");
    add_action(shop_fail, "value");
    add_action(shop_fail, "show");
    add_action(shop_fail, "list");
    add_action(shop_fail, "store");
}
