/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/key";

create_key() {
  ::create_key();

   set_adj("small");
  add_adj("black");
   add_name("winery_key");

set_long("It is a black iron key. Its handle is sculpted\n"
+"with vines and grape leaves.\n");

   set_key(31313);
}
