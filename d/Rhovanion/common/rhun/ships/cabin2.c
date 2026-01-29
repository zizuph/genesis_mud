#pragma save_binary

inherit "/d/Rhovanion/lib/cabin";

#include "/d/Rhovanion/farlong.h"

object ship = previous_object();

void
create_cabin()
{
    set_short("A sparsely-furnished cabin");
        set_long("This cabin on the tilting ship is"
	+" sparsely furnished, with nothing of real value present."
	+" In fact, this room is quite boring.\n");
  
    add_exit(RHUN+"ships/deck2", "up", 0);
    set_cabin_sound("@@my_cabin_sound@@");
}

string 
my_cabin_sound()
{
  int location;

  if(ship)
    location = ship->query_location();

  switch(location)
  {
    case  4:
    case 18: return "The ship shakes suddenly and you have a feeling of "+
                    "flying instead of sailing.\n";
    case  5:
    case 19: return "The ship bumps softly and you feel that it is "+
                    "sailing again.\n";
    case  0:
    case 11: return "You feel the ship bump into something.\n";
    default: return "The ship sways slightly in the wind.\n";
  }
}