#pragma save_binary

inherit "/d/Rhovanion/lib/deck";
#include "/d/Rhovanion/farlong.h"

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>

object ship = previous_object();
object captain;

void
create_deck()
{
    set_short("On a tilting ship");
    set_long("@@my_long@@");

    add_exit(RHUN+"ships/cabin2", "down", 0);
    add_item("dragon", "@@dragon_desc@@");
    set_deck_sound("@@my_deck_sound@@");
}

string
my_long()
{
  int location = ship->query_location();

  if((location != 4) && (location != 18))
    return "This is the upper deck of a sailing ship."
	+" This craft tilts oddly to starboard as it makes its way"
	+" through the waves between the sea of Rhun and the far-off land of"
        +" Emerald.\n";
  return "This is the upper deck of a sailing ship. Now id doesn't sail "+
         "but is carried with extreme speed by a huge flying dragon.\n";
}

string
dragon_desc()
{
  int location = ship->query_location();

  if((location != 4) && (location != 18))
    return "You can't see any dragon now but you see nasty marks that "+
           "its claws have left on the sides of the ship.\n";
  return "This huge dragon is flying fast easily carrying whole ship.\n";
}

string
my_deck_sound()
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
      case  1:
      case 13: set_alarm(1.0, 0.0, "first_warning"); 
               return "The ship sways slightly in the wind.\n";
      case  2:
      case 15: set_alarm(2.0, 0.0, "second_warning"); 
               return "The ship sways slightly in the wind.\n";
      case  3:
      case 17: set_alarm(2.0, 0.0, "last_warning"); 
               return "The ship sways slightly in the wind.\n";
      case  4:
      case 18: set_alarm(0.0, 0.0, "dragon_move"); 
               return "A huge dragon comes flying and grabs the ship. "+
                     "You desperately try not to fall overboard which "+
                    "will be your death. You wonder how long can you "+
                   "hang on because  you are getting extremely exhausted.\n";
      case  5:
      case 19: set_alarm(2.0, 0.0, "after_dragon_move");
               return "To your great relief the dragon descends and drops the ship "+
                     "into some water. This time you have managed to stay "+
                    "aboard but dont try it again! Next time it may be "+
                   "your death.\n";
      default: 
               return "The ship sways slightly in the wind.\n";
    }
  }
  else
    return "The ship sways slightly in the wind.\n";
}

void
first_warning()
{
  captain->command("say I advise you to go down to the cabin and stay there.");
}
void
second_warning()
{
  captain->command("say Please, go down to the cabin.");
  captain->command("say It is really dangerous to stay here.");
}
void
last_warning()
{
  captain->command("say If you really want, you can stay here.");
  captain->command("say But it is at your own risk.");
  captain->command("say I am now going down to the cabin.");
  captain->command("down");
}

void
dragon_move()
{
  object *inv, *livings;
  int i;
  
  inv = all_inventory(TO);
  livings = FILTER_LIVE(inv);
  inv -= livings;

  for(i=0; i<sizeof(livings); i++)
    livings[i]->add_fatigue(-livings[i]->query_fatigue());
  if(sizeof(inv))
    tell_room(TO, CAP(COMPOSITE_DEAD(inv))+" fall into the sea.\n");
  for(i=0; i<sizeof(inv); i++)
    inv[i]->remove_object();
}

void
after_dragon_move()
{
  captain->command("sigh relieved");
  captain->command("say I think we are out of danger now.");
  captain->command("say You can go back to deck and enjoy the rest of "+
                   "your journey.");
  captain->command("up");
}

void 
enter_inv(object ob, object from)
{
  int location = ship->query_location();

  ::enter_inv(ob, from);
  
  if((location != 4) && (location != 18))
    return;

  if(living(ob))
  {
    ob->add_fatigue(-ob->query_fatigue());
    set_alarm(0.0, 0.0, "message_to_fool", ob);
  }
  else
  {
    tell_room(TO, "The "+ob->short()+" falls overboard.\n");
    ob->remove_object();
  }
}

void
message_to_fool(object fool)
{
  fool->catch_msg("As you foolishly walk out on the deck you are blasted "+
                 "by the strong wind. Fortunatelly you grabbed side of the "+
                "ship and saved yourself from falling overboard. You wonder "+
               "how long can you hang on because you are getting extremely "+
              "exhausted.\n");
  tell_room(TO, QCTNAME(fool)+" is blasted by strong wind as "+HE(fool)+
               " foolishly walks out on the deck. Fortunatelly on the last "+
              "moment "+HE(fool)+" saves "+HIM(fool)+"self from falling "+
             "aboard.\n", fool);
}