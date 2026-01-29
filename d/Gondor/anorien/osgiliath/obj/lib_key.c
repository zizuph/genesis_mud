inherit "/std/key";

create_key()
{
  ::create_key();
  set_adj("new");
  add_adj("iron");
  set_pshort("iron keys");
  set_long("This key looks quite new and unused - yet you sense it is not.\n"+
    "The handle is shaped like a star.\n");
  set_key("Key_To_The_Osg_Lib_Vault");
}
