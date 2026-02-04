/*
    A black iron key. Mortricia 920722

    Modified: 3 May 2003, by Bleys
        - added the "iron" adj, and added the set_name()

 */
inherit "/std/key";

create_key()
{
    ::create_key();

    set_short("black iron key");
    set_pshort("black iron keys");
    set_name("key");
    set_adj(({"black", "iron"}));

    set_long("It's a black iron key.\n");
}
