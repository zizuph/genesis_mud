/*
 * cell_2_key.c
 *
 * Key to prison cell 2.
 *
 * Khail - June 15/97
 */

inherit "/std/key";

public void
create_key()
{
    add_name("_cell_2_key");
    set_adj("heavy");
    add_adj("iron");
    set_short("heavy iron key");
    set_long("The key is quite heavy, and made of iron. " +
        "The number 2 is stamped on its head.\n");
    set_key(524523552);
}