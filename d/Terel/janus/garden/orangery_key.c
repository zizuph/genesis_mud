/*
    A black iron key. Mortricia 920722
 */
inherit "/std/key";

create_key()
{
    ::create_key();

    set_short("iron key");
    set_pshort("iron keys");
    set_adj(({"black"}));

    set_long("It's a black iron key.\n");
}
