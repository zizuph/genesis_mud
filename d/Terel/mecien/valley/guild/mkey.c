/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/key";

create_key() {
  ::create_key();

   set_adj("white");
  add_adj("stone");

  set_long("A large stone key. It has been carved from a\n" +
          "white marble and looks like a serpent. The head\n" +
         "of the serpent forms the teeth of the keys, the\n" +
         "tail loops around a four-pointed star.\n");

   set_key(7777777);
}
