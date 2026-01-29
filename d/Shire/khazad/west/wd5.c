
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("A small intersection");
  set_long("A square shaped room with a low ceiling. Yellowed bones "+
     "are scattered across the cold stone floor partially "+
     "covering abundent dark crusty stains. Broken remains of "+
     "items lost in battle are also strewn about. A rectangular "+
     "opening in the northern wall leads down a dark stairway. "+
     "Another such opening lies to the west where an ascending "+
     "stairway begins. Beyond an arched opening to the southeast "+
     "lies a narrow corridor.\n");
 
  add_item("ceiling",
     "The flat stone ceiling is rather unremarkable.\n");
  add_item(({ "bones", "yellowed bones" }),
     "From the looks of it these have been here a while. They "+
     "appear to be from some type of humaniod.\n");
  add_item(({ "broken weapons", "broken armours", "weapons", "armours" }),
     "Useless weapons and armours litter the floor.\n");
  add_item(({ "item", "items" }),
     "You see weapons and armours mostly.\n");
  add_item(({ "wall", "walls" }),
     "These dark stone walls are fairly smooth. A few cracks "+
     "can be seen marring its surface.\n");
  add_item(({ "floor", "ground" }),
     "Useless weapons and armours are scattered about. A large "+
     "amount of blood has spilled here leaving dark stains "+
     "behind.\n");
  add_item(({ "stain", "stains", "blood" }),
     "Although long dried these stains remind you what can happen "+
     "to an ill prepared party exploring the depths of Khazad-dum.\n");
  add_item(({ "stairway", "staircase", "stairs", "steps" }),
     "One staircase decends to the north while another ascends to "+
     "the east. Both have high, shallow steps making for a very "+
     "steep and difficult journey.\n");
  add_item(({ "wall", "walls" }),
     "Besides for a few smears and splatters of blood these "+
     "grey stone walls are rather unremarkable.\n");
  add_item("corridor",
     "It heads in a southeasterly direction away from here. "+
     "You will have to journey down it to make out details.\n");

  add_exit("/d/Shire/khazad/west/wd4","up",0,5);
  add_exit("/d/Shire/khazad/west/wd6","down",0,5);
  add_exit("/d/Shire/khazad/west/wd7","southeast",0,1);
}
 
public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/wd4")
  {
    ob->catch_msg("You laboriously make your way down the "+
      "treacherous stairs.\n");
  }
 
  else if (file_name(from) == "/d/Shire/khazad/west/wd6")
    ob->catch_msg("You laboriously climb the treacherous stairs.\n");
}
