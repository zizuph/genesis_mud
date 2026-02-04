

inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("dark");
  add_adj("iron");
  set_pshort("iron keys");

  set_long("The top of this iron key is in the shape of a hound.\n");

  set_key(55555);
}
