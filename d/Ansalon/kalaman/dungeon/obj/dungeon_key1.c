inherit "/std/key";

void
create_key()
{
  set_short("rusty iron key");
  set_adj("rusty");
  add_adj("iron");
  set_long("This is a "+short()+" commonly used for doors and and trunks " +
   "or similar items that has a lock. The iron seems to have been exposed " +
   "to the forces of weather and has started to rust.\n");

  set_key("_kalaman_cell_key1_");
}
