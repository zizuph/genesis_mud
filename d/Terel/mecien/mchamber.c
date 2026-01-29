inherit "/std/workroom";

create_workroom()
{
  set_short("Mecien's Chamber");
  set_long("This darkened vault whispers tales of ancient days,\n"
    + "carved from living rock, supported by ivory pillars.\n");
  add_exit("/d/Genesis/start/human/town/church", "church", 0);
  add_exit("/d/Terel/mecien/dhall", "stair", 0);
}
