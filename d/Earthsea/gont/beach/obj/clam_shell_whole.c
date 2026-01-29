/* Coded by Ckrik February 1998
 * The leftover for the clams.
 */

#pragma strict_types

inherit "/std/food";

public void
create_food()
{
    set_name("shell");
    set_adj("clam");
    set_pname("shells");
    set_short("clam shell");
    set_long("The remains of an unfortunate clam that " +
        "was without water for a prolonged period of time.\n");
    set_amount(45);
}
