#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

static string next_port_control;
mapping sayings = ([
  "Pelargir" : ({
    "We are now sailing towards the city of Pelargir in the lands of Gondor.",
    "Pelargir is one of the two gateways into vast expanses of Middle Earth. "+
      "The other gateway is the Grey Havens, which we won't pass through, though.",
    "From here you can also reach any area of Middle Earth on foot."
  }),
  "Gelan": ({
    "We are now sailing north towards Gelan, the capital city of Calia.",
    "It is home of the famous Cadets' Guild and features many useful facilities."
  }),
  "Telberin": ({ 
    "We have now turned west towards Telberin, the main city of Emerald.",
    "This land, home of the Army of Darkness, is a bit more hostile than others."
  }),
  "Last": ({
    "We continue to the northwest towards Last, the gateway to Terel.",
    "By many Terel is considered one of the most enchanting areas of the Donut.",
    "If you want to easily reach the main city of Terel, Calathin, you should "+
      "take a boat from Last to Enchanted Garden."
  }),
  "Port Macdunn": ({
    "We are turning to the southwest towards Khalakhor's southeast speir "+
      "and its chief town of Port Macdunn.",
    "The plains and the forests beyond it offer excellent herbing "+
      "or so I heard.",
    "Other lands of Khalakhor are reachable via Cadu, which we are going to "+
      "arrive at later."
  }),
  "Raumdor" : ({
    "Our route continues in southwestern direction to the land of Raumdor.",
    "This is a dangerous place, for the road to the only city, Drakmere, "+
      "crosses a forest full of undeads. Be wary when disembarking here.",
  }),
  "Kabal" : ({
    "Turning to the south, we are now sailing to Kalad and its capital, Kabal.",
    "Kabal is one of the largest cities on the Donut, definitely worth a visit.",
    "A land connection and a wagon service to Tyr are also available from here."
  }),
  "Gont" : ({
    "Our journey south continues to the biggest city of Earthsea, Gont.",
    "Gont is one of the most popular locations of the Donut, both for "+
      "smaller and larger travellers.",
    "From here you can also take a boat to the small town of Thwil."
  }),
  "Cadu" : ({
    "We are sailing on to the south towards Cadu in the lands of Nyreese "+
      "which is one of the oldest places on the Donut.",
    "It is one of the and most popular destination of smaller travellers.",
    "It also serves as a hub for all other lands of Khalakhor, including "+
      "Sa Morgan, Eil Galaith and Port Macdunn.",
  }),
  "Sybarus" : ({
    "We are turning eastwards on our journey, and sail to the Port of "+
      "Sybarus in the lands of Avenir.",
    "This place is one of the most original and fascinating upon the Donut",
    "However, it is far from being safe, and I would recommend taking a "+
      "torch for your travels there too."
  }),
  "Palanthas" : ({
    "Our trip east continues to Palanthas, the city of the huge land of "+
      "Krynn.",
    "This land is so big, that you must take more ships to reach some parts "+
      "of it.",
    "Palanthas itself, however is a peaceful and popular destination."
  }),
  "Faerun" : ({
    "The longest part of our voyage, going eastwards, we are now heading "+
      "for Faerun.",
    "Little is known to me about this newest land to arise from depths of "+
      "Pensea."
  }),
  "Faerie" : ({
    "We have now turned sharply to northwest and go to Faerie on the "+
      "continent of Sparkle.",
    "This land, with the capital at Green Oaks, has been a favorite "+
      "of the young players for quite a while.",
    "From there you can reach, by boat or on foot, the Sparkle City itself "+
      "however I do not sail there anymore, for the city changes too much "+
      "for me."
    
  })
]);
static string *ports = m_indices(sayings);

varargs void
talk_domain (object captain, string port, int talk_index = 0)
{
  string saying;
  if (IN_ARRAY(port, ports)) {
    if (sizeof(sayings[port]) == talk_index) {
      return;
    }
    else {
      saying = sayings[port][talk_index];
    }
    if (saying) {
      captain->command(
                       "say " + saying
                       );
      set_alarm(3.5, 0.0, &talk_domain(captain, port, talk_index + 1));
    }
  }
  else
    captain->command("say I think we got off the route somehow...");
}

void
create_room()
{
  ::create_shiproom();

  set_short("On the galleon");
  set_long("You're standing on the deck of a well-built " +
           "galleon. The wind is in your hair and you can smell the sea. " +
           "A small cabin is at the aft. From here you get a splendid " +
           "view of your surroundings.\n");
  
  add_exit(CABIN, "aft", 0);
  add_exit(CABIN, "cabin", 0, 1, 1);
  add_exit(CABIN, "in", 0, 1, 1);
	set_is_deck(1);
  set_deck_sound("@@sounds");
}

string
sounds()
{
  object captain;
  string next_port;

  captain = query_ship()->query_captain();
  next_port = captain->query_destination();
  if (! next_port || next_port == next_port_control) {
    if (random(2))
      return "The ship sways slightly in the wind.\n";
    return "The ship is rocking gently with the waves.\n";
  }
  next_port_control = next_port;
  talk_domain(captain, next_port);
  return "";
}
