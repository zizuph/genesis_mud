/* Food for Longbottom
 * Finwe, December 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name(({"soup", "chowder"}));
    set_pname(({"soups", "chowders"}));
    set_short("fish chowder");
    set_pshort("fish chowders");
    set_adj(({"fresh", "creamy"}));
    set_long("This is a bowl of fresh creamy fish chowder. It is made " +
        "of small chunks of fish, cubed potatoes and onions, floating in " +
        "a rich creamy broth.\n");
    set_amount(150);
}
