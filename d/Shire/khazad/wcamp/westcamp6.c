inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
void
create_moria_room()
{
  set_short("A trench in a dim cavern");
  set_long("You stand in a trench inside a vast cavern. To your south "+
     "a high tower of stone rises like a thick grey pillar. The trench "+
     "deepens as it heads towards the tower entrance. An occasional "+
     "bat flutters overhead. Following the trench south will lead to "+
     "the tower. Just to the north are a pair of double doors leading "+
     "back into an underground tunnel.\n"); 
/*
  add_item(({ "ceiling", "roof" }),
  add_item(({ "wall", "walls" }),
  add_item(({ "ground", "floor" }),
  add_item(({ "doors", "double doors" }),
  add_item("tower",
  add_item("trench",
  add_item("entrance"
  add_item(({ "bat", "bats" }),
*/  
   
  clone_object("/d/Shire/khazad/obj/cave_door_b")->move(TO);
 
  add_exit("/d/Shire/khazad/wcamp/tower1","south",0,1);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/wcamp/camp_tunnel4")
    ob->catch_msg("You leave through the doorway and enter a trench.\n");
  
  else if (file_name(from) == "/d/Shire/khazad/wcamp/tower1")
    ob->catch_msg("You ascend northwards through the trench.\n");
}            
