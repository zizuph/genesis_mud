/*
    A large gold key. Mortricia 920909
 */
inherit "/std/key";

create_key()
{
    ::create_key();

    set_short("gold key");
    set_adj(({"gold"}));

    set_long("It's a 18 carat gold key.\n");
}
