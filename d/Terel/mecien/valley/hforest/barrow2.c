inherit "/std/workroom";

create_workroom()
{
  set_short("Barrow");
  set_long("The walls of this chamber are covered with mosaics,\n"
    + "which depict the life of a great knight.\n");
   add_item("walls", "They are covered with mosaics.\n");
   add_item("mosaics", "They seem to depict the life of a great knight.\n");
  add_item("knight", "Some warrior of the ancient world.\n");
  add_exit("/d/Terel/mecien/valley/hforest/barrow1", "south", 0);
  add_exit("/d/Terel/mecien/valley/hforest/barrow3", "north", 0); 
}
