/*
 * A torch
 *
 * Made by Nick
 */

inherit "/std/torch";

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
void
create_torch()
{
    set_name("torch");
    set_pname("torches");	   /* The plural name. */
    set_adj("small");
    set_long("A small torch but yet a light source better than a stick.\n");
    set_strength(2);
    set_short("small torch");
    set_pshort("small torches");
}
