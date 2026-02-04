

inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("small");
  add_adj("bone");
  set_pshort("small bone keys");

  set_long("A small bone key.\n");

  set_key(621621);
}
