
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Cramped corridor");
  set_long("A narrow corridor with a low ceiling. Broken items are "+
     "strewn across the floor. Dark stains line the wall and "+
     "criss-cross the floor. The corridor runs off to the "+
     "northwest, east and down a flight of stairs to the south.\n");

  add_item("ceiling",
     "It is arched in the form of a semi-circle.\n");
  add_item(({ "stain", "stains", "blood" }),
     "Although long dried these stains remind you of what can happen "+
     "to an ill prepared party exploring the depths of Khazad-dum.\n");
  add_item(({ "wall", "walls" }),
     "Besides for a few smears and spl atters of blood these "+
     "grey stone walls are rather unremarkable.\n");
  add_item("corridor",
     "It heads off to the northwest and southeast.\n");
  add_item(({"broken weapons", "broken armours", "weapons", "armours"}),
     "Useless weapons and armours litter the floor.\n");
  add_item(({ "floor", "ground" }),
     "Useless weapons and armours are scattered about. A large "+
     "amount of blood has spilled here leaving dark stains "+
     "behind.\n");

  add_exit("/d/Shire/khazad/west/wd7","northwest",-1,1);
  add_exit("/d/Shire/khazad/west/wd10","down",0,5);
  add_exit("/d/Shire/khazad/west/wd11","east",0,1);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
 
  if (file_name(from) == "/d/Shire/khazad/west/wd10")
  {
    write("Ascending northward you come to the top of the "+
          "staircase.\n");
  }
}
