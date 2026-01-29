/* 
 * Food for AA mess hall
 * Finwe, February 2019
 */

inherit "/std/food";

void
create_food()
{
    add_name("jerkey");
    set_name("venison");
    set_short("strip of venison jerkey");
    set_pshort("strips of venison jerkey");
    set_adj(({"thick", "venison"}));
    set_long("This is a thick strip of venison jerkey. It was smoked " +
        "over a hickory fire and salted to prevent spoilage.\n");
    set_amount(25);
}
