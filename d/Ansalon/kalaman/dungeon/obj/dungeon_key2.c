inherit "/std/key";

void
create_key()
{
  set_short("well-used steel key");
  set_adj("well-used");
  add_adj("steel");
  set_long("This is a "+short()+" commonly used for doors. It seems to be " +
   "a bit more advanced the normal keys though. The key has the letters " +
   "D Key, Area 2, etched into the side.\n");

  set_key("_kalaman_cell_key2_");
}
