/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/key";

create_key() {
   ::create_key();
   
   set_name("key");
   add_name("maus_key");
   add_name("sacred_key");
   set_adj("heavy");
   add_adj("gold");
   set_long("It is a plain gold key, very heavy.\n");
   
   set_key(01710);
}
