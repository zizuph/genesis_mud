
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Cramped corridor");
  set_long("A narrow corridor with a low ceiling. Broken items are "+
     "strewn across the ground. Dark stains line the wall and "+
     "criss-cross the floor. The corridor runs off to the "+
     "northwest and southeast.\n");

  add_item("ceiling",
     "It is arched in the form of a semi-circle.\n");
  add_item(({ "stain", "stains", "blood" }),
     "Although long dried these stains remind you of what can happen "+
     "to an ill prepared party exploring the depths of Khazad-dum.\n");
  add_item(({ "wall", "walls" }),
     "Besides the old blood smeared and splatterd about these "+
     "grey stone walls are rather unremarkable.\n");
  add_item("corridor",
     "It heads off to the northwest and southeast.\n");
  add_item(({ "broken weapones", "broken armours", "weapons", "armours" }),
     "Useless weapons and armours litter the floor.\n");
  add_item(({ "floor", "ground" }),
     "Useless weapons and armours are scattered about. A large "+
     "amount of blood has spilled here leaving dark stains "+
     "behind.\n");

  add_exit("/d/Shire/khazad/west/wd5","northwest",0,1);
  add_exit("/d/Shire/khazad/west/wd9","southeast",-1,1);
}

