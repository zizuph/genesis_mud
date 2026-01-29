#pragma strict_types

/*
 * Redid long desc and added kick emote Ckrik March, 2004
 *
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_armour()
{
    set_name("boots");
    set_pname(({"bootses"}));
    set_adj(({"embossed", "bronze"}));
    set_short("pair of embossed bronze boots");
    set_pshort("pairs of embossed bronze boots");
    set_long("The " +query_short()+ 
        " are covered in embossed patterns swirling " +
        "along the soles to the tips of the boots. The long and thin " +
	"stiletto heels form lines rising elegantly to the " +
	"thigh high tops of the boots. They look very strong " +
        "yet feminine.\n");
    set_default_armour(35, A_FEET | A_LEGS, 0, this_object());
    
    add_prop(OBJ_I_VALUE, 950);
    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 250);
}

public int
kick(string str)
{
  object target, tp;

  tp = this_player();
  if (parse_command(str, environment(tp),
		    "%o", target))
    {
      if (living(target))
	{
	  tp->catch_msg("You kick " + QTNAME(target) + ", digging the thin " +
			"stiletto of your embossed bronze boot into " + 
			target->query_objective() + ", " +
			"and leaving " + target->query_objective() + 
			" reeling in pain.\n");
	  target->catch_msg(QCTNAME(tp) + " kicks you, " + 
			    "digging the thin stiletto of " + 
			    tp->query_possessive() +
			    " embossed bronze boot into " + 
			    "you, and leaving you reeling in pain.\n");
	  tell_room(environment(tp),
		    QCTNAME(tp) + " kicks " + QTNAME(target) + ", " +
		    "digging the thin stiletto of " + tp->query_possessive() +
		    " embossed bronze boot into " + 
		    target->query_objective() + ", and leaving " +
		    target->query_objective() + " reeling in pain.\n",
		    ({target, tp}));
	}
      else
	{
	  tp->catch_msg("You kick the " + target->short() +
			" with the tip " +
			"your embossed bronze boot.\n");
	  tell_room(environment(tp), 
		    QCTNAME(tp) + " kicks the " + target->short() + 
		    " with the tip of " + tp->query_possessive() + " " +
		    "embossed bronze boot.\n",
		    tp);
	}
      return 1;
    }
  notify_fail("Kick whom/what?\n");
  return 0;
}

public mixed 
wear(object obj)
{
  object tp = this_player();

  switch (tp->query_race())
    {
    case "half-elf":
    case "elf":
    case "human":
      write("You wear the " + query_short() + " and the rest " +
	    "of the world looks a bit shorter to you.\n");
      say(QCTNAME(tp) + " wears the " + query_short() + " and becomes " +
	  "quite a bit taller.\n");
      return 1;
    case "hobbit":
    case "kender":
    case "dwarf":
    case "gnome":
    case "goblin":
    case "hobgoblin":
    case "orc":
      return "Your legs are too short to wear the " + query_short() + ".\n";
    case "minotaur":
      return "You find your legs far to big for these tiny boots.\n";
    default:
      return "You are not able to fit into the " + query_short() +
	"properly.\n";
    }
}

public void 
init()
{
  add_action(kick, "kick");
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
