/* Vegetable for Waymeet field
 * Finwe, March 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name("beet");
    set_pname("beets");
    set_short("large beet");
    set_pshort("large beets");
    set_adj("large");
    set_adj("red");
    set_long("This is a large, red beet. The plant has several large " +
        "leaves with a large round red root.\n");
   set_amount(100);
}
