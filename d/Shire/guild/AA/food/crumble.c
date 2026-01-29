/* 
 * Food for AA mess hall
 * Finwe, February 2019
 */

inherit "/std/food";

void
create_food()
{
    add_name("rhubarb crumble");
    set_name("crumble");
    set_short("rhubarb crumble");
    set_pshort("rhubarb crumbles");
    set_adj(({"rhubarb", "crumbles"}));
    set_long("This is a very sticky and sickly-looking plate of rich " +
        " rhubard crumble. It looks like it will keep you going for a " +
        "while....\n");
    set_amount(500);
}
