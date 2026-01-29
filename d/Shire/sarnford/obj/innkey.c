inherit "/std/key";

void
create_key()
{
  ::create_key();
  set_long("This long, iron key has been purchased to enjoy a night's " +
  "rest at the Sleeping Fisherman Inn. To use it, just go upstairs at " +
  "the inn and type 'start here' and enjoy a wonderful rest.\n");
  set_adj("iron");
  set_adj("long");
  set_pshort("long, iron keys");
  set_key("_sarnford_inn_key");
  add_name("_sarnford_inn_key");
}
