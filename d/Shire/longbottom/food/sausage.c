/* Food for Longbottom
 * Finwe, December 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name(({"sausage"}));
    set_pname(({"sausages"}));
    set_short("grilled sausage");
    set_pshort("grilled sausages");
    set_adj(({"hot"}));
    set_long("This is a plate of grilled sausage chunks. They have " +
        "been cooked in butter. On the plate is a slice of toasted " +
        "bread and a  helping of leeks and artichokes.\n");
    set_amount(350);
}
