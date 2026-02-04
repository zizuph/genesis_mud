inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("large");
  add_adj("iron");
  set_pshort("large iron keys");

  set_long("A rusted black iron key.\n");

  set_key(0006000);
}
