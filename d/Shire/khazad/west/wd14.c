inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
create_room()
{
  set_short("In a narrow corridor");
  set_long("You stand within a long narrow corridor. Its high "+
     "arched ceiling is barely visible in the dim light. Like "+
     "the ribs of a giant creature stone arches line the corridor "+
     "every ten feet. Upon these arches many things have been "+
     "carved. A thick wooden door that once stood at the "+
     "beginning of this passage lies before you on the cold stone "+
     "floor, battered and smashed. The narrow corridor continues "+
     "to the northeast and southwest.\n");
 
  add_item(({ "ceiling", "roof" }),
     "The ceiling arches high above you at the edge of "+
     "the light. More than that cannot be made out from here.\n");
  add_item(({ "floor", "ground" }),
     "The floor appears relatively free of debris except for "+
     "a thick wooden door laying before you.\n");
  add_item(({ "wall", "walls" }),
     "They are made up of the same cold grey stone found "+
     "throughout Khazad-dum.\n");
  add_item(({ "corridor", "passage" }),
     "It runs off to the northeast and southwest under "+
     "an arched ceiling.\n");
  add_item(({ "ribs", "arch", "arches" }),
     "Lending structural support to the ceiling of this "+
     "narrow corridor these arches constrict passage even "+
     "further allowing only one person to pass through them "+
     "at a time. Various runes and pictures have been etched onto "+
     "the underside of some of these arches.\n");
  add_item(({ "rune", "runes" }),
     "They are ancient and mean nothing to you.\n");
  add_item(({ "picture", "pictures" }),
     "On the nearest arch you see a few frames of stout "+
     "dwarves carrying hefty axes. By their posture "+
     "they seem to be protecting something.\n");
  add_item(({ "door", "wooden door", "thick door" }),
     "Battered off its hinges this door shows signs of "+
     "being repeatedly assaulted. It would seem its "+
     "hardy strength finally gave out.\n");
 
  add_exit("/d/Shire/khazad/west/wd12","northeast",0,1);
  add_exit("/d/Shire/khazad/quarters/entrance","southwest",0,1);
}
