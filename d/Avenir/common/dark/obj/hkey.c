/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/key";

public void
create_key(void)
{
    set_adj("large");
    add_adj("iron");
    set_short("large iron key");
    set_pshort("large iron keys");
    set_long("A large iron key.\n");

    set_key(6056);
}
