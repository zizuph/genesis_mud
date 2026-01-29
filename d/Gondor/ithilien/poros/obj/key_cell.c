inherit "/std/key";

void
create_key()
{
    ::create_key();
    set_long("This is a heavy, worn steel key.\n");
    set_adj( ({ "heavy", "worn", "steel" }) );
    set_short("steel key");
    set_pshort("steel keys");
    set_key("Corsairs_Cell_Key");

}
