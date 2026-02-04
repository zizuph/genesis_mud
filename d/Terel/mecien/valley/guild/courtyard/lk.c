/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/key";

create_key() {
  ::create_key();

   set_adj("ornate");
  add_adj("silver");
   add_name("lattice_key");

set_long("It is an ornate silver key with lattice work.\n");

   set_key(50999);
}
