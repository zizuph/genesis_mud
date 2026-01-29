/* Coded by Ckrik February 1998
 * The leftover for the clams.
 */

#pragma strict_types

inherit "/std/food";

public void
create_food()
{
    set_name("shell");
    set_adj("crushed");
    add_adj("clam");
    set_pname("shells");
    set_short("crushed clam shell");
    set_long("The crushed remains of an unfortunate clam.\n");
    set_amount(45);
}
