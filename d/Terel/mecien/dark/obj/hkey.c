inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("large");
  add_adj("iron");

  set_long("A large iron key.\n");

  set_key(6056);
}
