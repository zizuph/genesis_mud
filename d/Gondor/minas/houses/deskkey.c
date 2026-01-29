inherit "/std/key";

create_key()
{
  ::create_key();
  set_adj("rusty");
  set_pshort("rusty keys");
  set_long("This is a rusty key, quite little.\n");
  add_adj("little");
  set_key("Key_To_PeDesk");
  add_name("Key_To_PeDesk");
}
