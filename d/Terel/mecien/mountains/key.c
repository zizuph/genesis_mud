inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("large");
  add_adj("brass");
  set_pshort("large brass keys");

  set_long("A large brass key.\n");

  set_key(123454321);
}
