/* 07 Sept 2003 Palmer
 Caught raise and lower errors when no object specified */

inherit "/std/armour.c";
inherit "/lib/keep";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

int visor_up = 1;

void
create_armour() {
  set_name("helm");
  add_name("helm");
  set_adj(({"great","lacquered","steel"}));
  set_short("lacquered steel helm");
  set_long("This "+short()+", the work of a master craftsman, "+
    "seems to have been created from a single piece of metal. "+
    "Starting from a flared guard of metal that protects the neck, "+
    "the "+short()+" extends upwards to protect the head with "+
    "a swept-back conical shape. The great helm widens from a narrow, "+
    "angular parody of a face to encase the rest of the head as it "+
    "rises to a point behind the head, giving the head the appearance "+
    "of an extremely long, sloping forehead that tapers to a point "+
    "in the back. Narrow vertical slits where the mouth would be "+
    "allow for breathing and speech, while a long, horizontal "+
    "slit carves the visor almost in half to allow for vision. "+
    "@@do_long@@"+" Dark blue ribbons of lacquer "+
    "edged in gold and silver flow down from the peak of the helm "+
    "until they are abruptly cut off as they reach the neck guard.\n");
  set_default_armour(30,A_HEAD|A_NECK,({1,1,-2}),TO);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(30,A_HEAD)+random(151));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(101));
  set_keep();
}


string do_long()
{
  if(visor_up)
    return "The visor is raised, allowing the padded leather interior "+
    "to peek out of the helm.";
  else
    return "The visor is lowered, blocking the view into the helm.";
}


init()
{
  add_action("do_raise","raise");
  add_action("do_lower","lower");
  ::init();
}


int do_raise(string what)
{
  if (!what)
  {
    NFN0("Raise what?");
  }


  if(!parse_command(what,TP, " [the] 'visor' "))
  {
    NFN0("Raise what?");
  }

  if(visor_up)
  {
    WRITEN("The visor on the "+short()+" is already up.");
    return 1;
  }

  WRITEN("You raise the visor on the "+short()+".");
  SAY(" raises the visor of the "+short()+".");
  TO->set_ac(30);
  TO->add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(32)+random(101));
  visor_up = 1;
  return 1;
}


int do_lower(string what)
{
  if(!what)
  {
    NFN0("Lower what?");
  }

  if(!parse_command(what,TP, " [the] 'visor' "))
  {
    NFN0("Lower what?");
  }

  if(!visor_up)
  {
    WRITEN("The visor on the "+short()+" is already down.");
    return 1;
  }

  WRITEN("You lower the visor on the "+short()+".");
  SAY(" lowers the visor of the "+short()+".");
  TO->set_ac(32);
  TO->add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(32)+85+random(16));
  visor_up = 0;
  return 1;
}

public mixed
wear(object arm)
{
  if(!visor_up)
  {
    SAY(" tries to wear the "+short()+" but fails.");
    return "You can't put the "+short()+" on when the visor is down!\n";
  }
  return 0;
}

public int remove()
{
  object wearer=query_worn();
  if(!visor_up)
  {
    wearer->catch_msg("You can't remove the "+short()+" with the "+
      "visor down!\n");
    return -1;
  }
  return 0;
}
