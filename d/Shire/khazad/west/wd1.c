
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("In a cleft");
  set_long("The cleft widens to its eastern end. The rough, natural walls "+
     "of the cleft nearly run together a few feet above your head. "+
     "You hear the sound of running water coming from an openning in "+
     "the southern wall. A narrow path runs through rocky terrain "+
     "here leading eastwards deeper into the cleft. To the west "+
     "you see a large blanket of moss blocking most of the "+
     "path in that direction.\n");

  add_item("cleft",
     "You stand in a small crack in the cavern wall.\n");
  add_item(({ "southern wall", "south wall", "opening" }),
     "You see a small creavice you might be able to squeeze "+
     "through.\n");
  add_item(({ "moss", "blanket", "blanket of moss" }),
     "It has a translucent greenish appearance and glistens "+
     "in the light.\n");
  add_item("path",
     "The cleft is large enough for someone to have "+
     "established a rocky path here.\n");
  add_item(({ "walls", "wall" }),
     "The uneven rock walls of the cleft are rough and jagged.\n");

  add_exit("/d/Shire/khazad/west/cp6","west",0,1);
  add_exit("/d/Shire/khazad/west/wd2","east",0,1);
  add_exit("/d/Shire/khazad/west/pool1","south");
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
 
  if (!living(ob))
    return;
 
  if (file_name(from) == "/d/Shire/khazad/west/cp6")
    ob->catch_msg("Moving the wet moss aside you enter the dark "+
      "cleft.\n");
}
