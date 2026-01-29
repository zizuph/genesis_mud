#pragma save_binary

inherit "/d/Rhovanion/lib/deck";
#include "/d/Rhovanion/farlong.h"

#include <stdproperties.h>

object ship = previous_object();
object captain;

void by_sea_rhun()
{
  captain->command("say We are landing by the sea of Rhun.");
}

void mid_to_esgaroth()
{
  captain->command("say We are landing at the joining of rivers Celduin and "+
                   "Carnen.");
  captain->command("say In a moment we will continue to Esgaroth.");
  set_alarm(1.0, 0.0, "to_esgaroth", 0);
}

void
to_esgaroth(int i)
{
  if(ENV(captain) != TO)
  {
    if(i < 1)
    {
      captain->command("say We are going to the Esgaroth now.");
      set_alarm(4.0, 0.0, "to_esgaroth", 5);
      return;
    }
    i--;
    set_alarm(4.0, 0.0, "to_esgaroth", i);
  }
}

void by_esgaroth()
{
  captain->command("say We are landing at the lake town Esgaroth.");
}

void mid_to_rhun()
{
  captain->command("say We are landing at the joining of rivers Celduin and "+
                   "Carnen.");
  captain->command("say In a moment we will continue to the sea of Rhun.");
  set_alarm(1.0, 0.0, "to_rhun", 0);
}

void
to_rhun(int i)
{
  if(ENV(captain) != TO)
  {
    if(i < 1)
    {
      captain->command("say We are going towards the sea of Rhun now.");
      set_alarm(4.0, 0.0, "to_rhun", 5);
      return;
    }
    i--;
    set_alarm(4.0, 0.0, "to_rhun", i);
  }
}

string
my_bump_sound()
{
  int location;

  if(ship)
  {
    location = ship->query_location();
    if(!captain)
      captain = ship->query_captain();
  }
  if(captain)
  {
    switch(location)
    {
      case 0: TO->by_sea_rhun(); break;
      case 5: TO->mid_to_esgaroth(); break;
      case 11: TO->by_esgaroth(); break;
      case 17: TO->mid_to_rhun(); break;
      default: break;
    }
  }

  return "The ship lands softly by the pier.\n"+
         "The crew throws the anchor - splash!\n";
}

void
create_deck()
{
    set_short("On a wooden ship");
    set_long(break_string("You stand on the deck of a wooden ship."
	+"  This craft makes its run up and down the long lengths of"
	+" the River Carnen, as it nears the Sea of Rhun, and the"
	+" River Celduin, often called the River Running, as it heads"
	+" off to the northwest and approaches the lake town of"
	+" Esgaroth, near the mountain of Erebor, at the northeastern"
	+" edge of the vastness of Mirkwood.  Oarsmen stand ready to"
	+" propel the craft on its way, while a pair of well-worn sails"
	+" flap overhead.  The ship's cabin lies downward from here."
	+"\n",75));

    add_exit(RHUN+"ships/cabin1", "down", 0);

    set_bump_sound("@@my_bump_sound@@");
}
