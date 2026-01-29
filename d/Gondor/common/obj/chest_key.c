/*
 * Key to unlock the chest on the dead mumak.c 
 * set_key() is set and the key cloned into a haradrim when the animals 
 * dies.
 * -- Finwe, August 2005
 */

inherit "/std/key";

create_key()
{
    ::create_key();
    set_adj("long");
    set_adj("iron");
    set_pshort("long iron keys");
    set_long("This long iron key is valuable looking. It appears to open " +
        "chests or doors.\n");
}
