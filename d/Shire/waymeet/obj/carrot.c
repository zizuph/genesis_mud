/* Vegetable for Waymeet field
 * Finwe, March 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name("carrot");
    set_pname("carrots");
    set_short("large carrot");
    set_pshort("large carrots");
    set_adj("large");

    set_long("This is a large, orange carrot. The plant has several long " +
        "featherly leaves with a large, long orange root.\n");
   set_amount(85);
}
