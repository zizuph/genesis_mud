/* Food for Longbottom
 * Finwe, December 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name(({"strips"}));
    set_pname(({"strips"}));
    set_short("chicken strips");
    set_pshort("chicken strips");
    set_adj(({"deep-fried"}));
    set_long("This is a basket of chicken strips. Each strip was " +
        "dipped in breading mix and deep-fried in lard to a golden " +
        "color.\n");
    set_amount(150);
}
