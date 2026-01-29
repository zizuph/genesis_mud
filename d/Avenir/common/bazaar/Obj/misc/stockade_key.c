/*
 * An iron key. Mortricia Dec 1994
 */
inherit "/std/key";

create_key()
{
    ::create_key();

    set_short("iron key");
    set_adj(({"iron"}));

    set_long("It's a well-used iron key.\n");
}
