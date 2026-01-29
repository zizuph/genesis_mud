// Dummy guild token for special attack for worm_tail
// Made by Boriska  July 1994
// Dedicated to wizards of Genesis. They've created 99% of this_object.

inherit "/std/object";

#include <stdproperties.h>

string *names = ({
  "medallion", "necklace", "breath", "insignia", "fork",
  "skull", "ringfinger", "brooch", "medal","staff","robe"
});

string *shorts = ({
  "medallion of Calia", "necklace of the Kaheda Order",
  "gladiator's heavy breath", "stick", "silver tuning fork",
  "tattoed skull wrapped in torn cloak", "wildrunner's ringfinger",
  "diamond star-shaped brooch", "medal of Paladine",
  "mysterious ancient runed staff","dark hooded robe",
  });
  
  string *longs = ({
  "This medallion bears an insignia of someone thinking very hard.\n" +
  "Apparently not hard enough though to save its former owner\n" +
  "from worm's stomach.\n",
    
  "This is a necklace of some poor monk who did not\n" +
  "pray to her Gods enough.\n",

  "This is the last breath of some gladiator. It is very heavy and stinks\n"+
  "of Roke beer, the worst smell ever, it makes you vomit.\n",

  "This is the walking stick of a Traveller whose last travel brought\n" +
  "her too far from home.\n",

  "This silver tuning fork was a hallmark of a Minstrel.\n" +
  "Probably it is the single artifact remained that can be placed\n" +
  "on unlucky showman's tomb.\n",

  "Tattoed skull of some Bloodguard wrapped in remnants\n"+
  "of his former master's vampyre cloak. Both are enjoying\n" +
  "their unlife now... in worm's stomach.\n",

  "Elven finger with a golden Wildrunners' ring worn on it.\n" +
  "Its former bearer did not run fast enough when need arised.\n",

  "This diamond star-shaped brooch belonged once to Master Ranger.\n" +
  "Once he went on a raid, mistook his own tracks for Sauron's and\n" +
  "was lost... Worm enjoyed Ranger Stew without salt and spices...\n",

  "This is Paladine medal, worn by all Solamnian Knights.\n" +
  "Its former owner of had forgotten to consult with Paladine\n" +
  "before attacking the worm. The brave Solamnian had his leg broken\n" +
  "while trying to kick scaled worm's body.\n",

  "It is hard to figure out much about this staff, it is too mysterious\n"+
  "for you to comprehend. The only thing you know is that somehow its bearer\n" +
  "got separated from the staff... and from life too.\n",

"This dark hooded robe is torn apart and soaked with all kinds of strange\n" +
"liquids and potions. Worm bile is between them, which explains where\n" +
"the former owner of the robe went.\n",
  
});

create_object ()
{
  add_prop (OBJ_I_WEIGHT, 1);
  add_prop (OBJ_I_VOLUME, 1);
  add_prop (OBJ_I_VALUE, 1);
  set_alarm (600.0, 0.0, "remove", this_object() );
}

// called by whoever needs that object in order to get real thing
void
configure (int att)
{
  if ( att < 0 || att > sizeof(names) - 1)
    att = 0; 
  set_name (names[att]);
  set_short (shorts[att]);
  set_long (longs[att]);
}
     
void
remove (object obj) { obj->remove_object(); }









