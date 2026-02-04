inherit "/std/key";

create_key()
{
  ::create_key();
  set_adj("iron");
  set_adj("sturdy");
  set_pshort("sturdy iron keys");
  set_long("This sturdy iron key looks to be in very good condition.\n");
  set_key("half_chest");
}
