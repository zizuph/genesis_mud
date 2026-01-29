/* bat guano      /d/Avenir/common/obj/guano.c 
 * Created by: Lilith, Dec 2021   
 *   Bat guano from the bat cave in the Utterdark
 *   Burns brightly (2x) for a short period of time (30s).
 *   Cannot be extinguished once it is lighted. 
 *   Can be smeared on burnt-out torches to make them re-useable for 5 mins
 *    one time only.
 * Note: Cherek approved the above feature on Dec 6 2021 
 *
 */
inherit "/std/torch";
inherit "/lib/keep";
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
int Decay_Alarm, Time_Left, Burn_Alarm;

void 
create_torch()
{
    set_name("guano");
    add_name(({"_avenir_bat_guano", "lump"}));
    set_pname("guano");
    set_short("lump of guano");
    set_pshort("lumps of guano");
    add_adj(({"lump", "bat"}));
    set_long("It is a clay-like lump of bat guano. It is highly flamable. "
        +"When ignited it will burn very brightly for a short period of time. "
        +"Bat guano can also be smeared on burnt out torches to extend their "
        +"usefulness a little longer. @@lit_desc@@\n");
  set_keep(1);
  set_time(30); // 30 seconds
  set_strength(2);
  set_value(10 + random(25));
  add_prop(OBJ_I_VOLUME, 100);
  add_prop(OBJ_I_WEIGHT, 100);
  add_prop(OBJ_M_NO_SELL, "@@dont_sell@@");
}

mixed dont_sell()
{
  if(query_prop(OBJ_I_HAS_FIRE))
   return "It cannot be sold when it is lighted.\n";
  else
   return 0;
}

string lit_desc()
{
  if(!query_time())
     return " It doesn't look like there is much left to burn.";
  else if(!query_prop(OBJ_I_HAS_FIRE))
     return " It is reddish in color.";
  else
     return " It burns brightly, with an alternating yellow and lilac flame.";
}

void torch_tell()
{
  string  str;
  object  where;

  if(!query_lit(0))
    return;

  switch(random(3))
  {
    case 0:
     str = "emits a faint acrid scent.";
     break;
    case 1:
     str = "flickers with a bright yellow light.";
     break;
    case 2:
     str = "flares with a lilac-colored flame.";
     break;
    default:
     str = "burns brightly.";
   }

   where = environment(this_object());
   if(!living(where))
    tell_room(where, "The " + QSHORT(this_object()) 
     + " " + str + "\n");
   else
   {
    where->catch_msg("Your " + QSHORT(this_object()) + " " + str + "\n");
    tell_room(environment(where), QCTNAME(where) + "'s "
      + QSHORT(this_object()) + " " + str + "\n", ({ where }));
   }

  set_alarm(itof(random(5) + 6), 0.0, torch_tell);
}

public 
int light_me_after_delay()
{
  ::light_me_after_delay();
  set_alarm(itof(random(5) + 2), 0.0, torch_tell);
  return 1;
}


/*
 * Function name: command_extinguish
 * Description:   Extinguish this torch.
 * Returns:       string - an error message (failure)
 *                1 - torch successfully extinguished
 *
 *  Masking this to prevent player from extinguishing it. Its only good
 *  for 30 seconds and some fires burn to intensely to be easily extinguished.
 */
public mixed
command_extinguish()
{
    if (!Burn_Alarm)
    {
        return "The " + short() + " isn't lit.\n";
    }

    return "The "+ short() +" is burning too intensely for you to "
        +"extinguish it so easily!\n";
}

/*
 * Function name: burned_out
 * Description:   If this function is called when the torch has burned out.
 *
 *                 Masking this to cause it to decay immediately.
 */
public void
burned_out()
{
    object env = environment();
    string tmp = ::short();

    Time_Left = 0;
    Burn_Alarm = 0;

    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);

    set_adj("out");
    set_adj("burnt");
    remove_adj("lit");
    remove_adj("burning");

    if (!objectp(env))
    {
        return;
    }

    if (living(env))
    {
        tell_object(env, "The " + tmp + " goes out.\n");
        tell_room(environment(env), "The " + tmp + " that " +
            QTNAME(env) + " is holding goes out.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The " + tmp + " goes out.\n");


    }
    /* Call this in the environment to let it trigger on the event. */
    env->hook_torch_burned_out(this_object());
    Decay_Alarm = set_alarm(2.0, 0.0, decay_torch);
 
}

public int
do_smear(string str)
{
	object *obj;
    object torch;
	
    if (!strlen(str))
	return notify_fail("Smear what on what?\n");
    if (!parse_command(str, this_player(),
	    "[the] [bat] [guano] 'on' / 'onto' [the] %i", obj) || 
        (!sizeof(obj = NORMAL_ACCESS(obj, 0, 0))))
	return 0;

    if (sizeof(obj) != 1)
    {
        notify_fail("You can only smear it on one at a time.\n");
        return 0;
    }
    else
    {
        torch = obj[0];
    }
	
    notify_fail("You can only smear the guano on a burnt out torch.\n");
    if (!function_exists("create_torch", torch) ||
	torch->query_adj() != "burnt")
	return 0;	

    // This keeps the torch from being re-used over and over.		
	if (torch->query_prop("_av_guano_smeared"))
    {
        write("It has had guano smeared on it before. It makes no sense "+
            "to do it again.\n");
	    return 1;
	}	

	write("You smear the bat guano on the "+ torch->short() +".\n");
	say(QCTNAME(this_player()) +" smears bat guano onto "+ torch->short() +"\n");
    
	torch->set_time(300); 
	torch->remove_adj("out");
    torch->remove_adj("burnt");
	torch->add_adj("guano");
	torch->add_prop("_av_guano_smeared", 1);
	Decay_Alarm = set_alarm(1.5, 0.0, decay_torch);
    return 1;
}



public void
init(void)
{
    ::init();

    if (environment() != this_player())
	return;

	add_action(do_smear, "smear");
}


string
query_recover()
{
   return MASTER + ":" + query_torch_recover();
}

void
init_recover(string arg)
{
   init_torch_recover(arg);
} 
