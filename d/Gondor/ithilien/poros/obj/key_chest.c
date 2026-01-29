inherit "/std/key";

void
create_key()
{
    ::create_key();
    set_long("This is a large steel key. Engraved on its handle is the form "
      + "of a great winged drake.\n");
    set_adj( ({ "large", "steel" }) );
    set_pshort("large steel keys");
    set_key("Corsairs_Chest_Key");

}
