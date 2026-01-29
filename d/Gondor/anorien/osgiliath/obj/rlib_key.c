inherit "/std/key";

void
create_key()
{
    ::create_key();
    set_adj("rusty");
    add_adj("iron");
    set_pshort("rusty keys");
    set_long("This iron key has almost rusted away. "
      + "It will probably not work anywhere.\n");
    set_key("Rusty_Key");
}
