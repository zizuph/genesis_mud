inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("At the tower's entrance");
  set_long("A tall grey tower of stone rises immediately to the south. "+
     "At is base are a set of stone double doors. Stalagmites surround "+
     "the tower like a jagged fence except on the north side where a "+
     "trench runs up to the tower doors. No windows or openings are "+
     "noticable on the tower.\n");
 
  add_item(({ "wall", "walls" }),
     "Made of dull grey rock they look fairly strong.\n");
  add_item(({ "doors", "double doors" }),
     "Flat rectangular doors that are both six feet high and four feet "+
     "across. Made of the same material as the walls they appear to "+
     "be very strong and heavy. A thick iron ring hangs from its mounting "+
     "near the center of the doors.\n");
  add_item("ring",
     "You think you might be able to pull the door open with it.\n");
  add_item("tower",
     "Silent and forboding this featureless tower rises amid the "+
     "stalagmites nearly reaching the cavern ceiling.\n");
  add_item("trench",
     "It lies immediately to the north and runs slightly uphill towards "+
     "the back of this cavern.\n");
 
  clone_object("/d/Shire/khazad/obj/tower_door_a")->move(TO);
 
  add_exit("/d/Shire/khazad/wcamp/westcamp6","north",0,1);
}
 
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/wcamp/tower2")
    tell_room(TO, "You leave through the doorway and enter a trench.\n");
  
  else if (file_name(from) == "/d/Shire/khazad/wcamp/westcamp6")
    tell_room(TO, "You make your way south through the trench.\n");  
}            
