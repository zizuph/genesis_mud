inherit "/std/key";

create_key() {
  ::create_key();

  set_adj("ornate");
  add_adj("silver");
  set_pshort("ornate silver keys");

  set_long("A large ornate silver key, perhaps to a gate.\n");

  set_key(191);
}
