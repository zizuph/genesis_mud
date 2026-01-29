inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("small");
  add_adj("steel");
  set_pshort("small steel keys");

  set_long("It's a small key made out of steel.\n");
}
