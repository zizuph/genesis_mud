/* Trofast 4-4-1999 */
/*
 * Revised:
 *   Jan 2021 - Lucius - Set/Unset OBJ_I_CONTAIN_WATER based on whether
 *                       the trough is full or not.
 */
inherit "/std/room";
#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <composite.h>
#define CORRAL CALATHIN_DIR+"stable_corral.c"

#define HIS(x) x->query_possessive()


int trough_full=0, is_pumping=0;
int trough_alarm=0, pump_alarm=0;
object pumper, pumproom;

/* Function Prototypes */

void   stop_pumping();
int    empty_trough();
int    do_empty_trough (string arg);
string pump_water();
int    drink_water(string arg);
int    water_animal(string arg);
string trough_desc();
string pump_desc();
string room_desc();
string exa_corral();
string climb_fence();
/*********************************************************************/
void
stop_pumping()
{
  is_pumping=0;
  tell_room (pumproom, 
	     "Gradually the stream of water coming from the pump slows to "+
	     "a trickle, then stops.\n");

  if (get_alarm(pump_alarm)) remove_alarm(pump_alarm);

}

/*********************************************************************/
int
empty_trough()
{
  if (!trough_full) return 1;
  add_prop(OBJ_I_CONTAIN_WATER,0);
  trough_full=0;
  if (is_pumping) stop_pumping();
  tell_room (pumproom, 
	     "The stable-master leads two horses from the stable and "+
	     "waters them at the trough.  Then he tilts the trough over "+
	     "and empties the remains of the water onto the ground.\n");
  return 1;

}

/*********************************************************************/
int
do_empty_trough(string arg)
{

  if (!arg)
    { return 0;}
  
  if (arg=="trough")
    {
      if (is_pumping)
	{
	  write ("Perhaps you should wait until the pump stops flowing?\n");
	  return 1;
	}

      if (trough_full)
	{
	  write ("Carefully, you tilt the trough over and pour the water "+
		 "on the ground.\n");
	  trough_full=0;
          add_prop(OBJ_I_CONTAIN_WATER,0);
	}
      else
	{
	  notify_fail("The trough is already empty!\n");
	  return 0;
	}
      return 1;
    }
}


/*********************************************************************/
string
pump_water()
{ 
  pumper=this_player();
  pumproom=ENV(pumper);

  if (!get_alarm(trough_alarm))
    trough_alarm = set_alarm(180.0,0.0, empty_trough);

  if (!get_alarm(pump_alarm))
    pump_alarm= set_alarm(20.0,0.0, stop_pumping);

  if (trough_full)
    {
      is_pumping=1;

      say("Water overflows from the already-full trough onto the ground.\n");
      return "Water overflows from the already-full trough onto the ground.\n";
    }
  else
    {
      trough_full=1;
      is_pumping=1;
      add_prop(OBJ_I_CONTAIN_WATER,-1);
      say("Slowly the trough fills with water.\n");
      return "Slowly the trough fills with water.\n";
    }
}

/*********************************************************************/
int
drink_water(string arg)
{
  
  int amount= TP->drink_max() / 20;

  notify_fail("Drink water from what?\n");
  if (!arg) return 0;
  
  if (arg=="water")
    {
      notify_fail("Drink water from the trough or from the pump?\n");
      return 0;
    }
  
  if (parse_command( arg, TO, 
		     "[the] 'water' 'from' / 'at' [the] 'trough'"))
    {
      if (!trough_full)
	{
	  write ("But the trough is empty!\n");
	  return 1;
	}
      
      if (! TP->drink_soft(amount)) 
	{
	  write ("You plunge your head into the water, but you are "+
		 "too full to drink any more!\n");
	  say (QCTNAME(TP)+" plunges his head into the water!\n");

	  //top it off anyway.
	  TP->drink_soft(TP->drink_max() - TP->query_soaked());  
	}
      else
	{
	  write ("You bend down to the trough and gulp down water "+
		 "like a dog!\n");
	  say(QCTNAME(TP)+ " bends down to the trough and gulps down "+
	      "water like a dog!\n");
	}
      return 1;
    }
  
  if (parse_command( arg, TO, 
		     "[the] 'water' 'from' / 'at' [the] 'pump'"))
    {

      if (!is_pumping)
	{
	  write ("There's no water coming from the pump.  Perhaps you "+
		 "can pump it?\n");
	  return 1;
	}

      if (! TP->drink_soft(amount)) 
	{
	  write ("You cup your hands under the water, but you are "+
		 "too full to drink any more!\n");
	    say ("Water overflows from "+QCTNAME(TP)+"'s cupped hands.\n");
	  //top it off anyway.
	  TP->drink_soft(TP->drink_max() - TP->query_soaked());  
	  }
	else
	  {
	write ("You cup your hands under the streaming pump and drink "+
	       "of the cool, fresh well water.\n");
	say(QCTNAME(TP)+ " cups "+HIS(TP)+ " hands under the streaming "+
	    "pump and drinks of the well water.\n");
	  }
	return 1;
    }
}
/*********************************************************************/
int
water_animal(string arg)
{
object animal;
int i, amount;

if (!arg) 
{return 0;
}

if (parse_command( arg, 
		   TO, 
		   "[the] %o [from] [at] [the] [trough]", 
		   animal))
  {
    /*    if (!TP->check_seen(animal)) {return 0;}

    if (!living(animal)) {return 0;}

    if (!present(TO, animal)) {return 0;}
    */
    if (trough_full)
      {
	say (QCTNAME(TP)+" leads "+HIS(TP)+" "+animal->short()+
	     " to the trough and waters "+animal->query_objective()+".\n");
	write ("You lead your " +animal->short()+
	       " to the trough and water "+animal->query_objective()+".\n");

	  amount=animal->drink_max() / 20;

	  for (i=0;i<20;i++) 
	    {
	      animal->drink_soft(amount);
	    }
	  animal->drink_soft ( animal->drink_max() - animal->query_soaked());

	  return 1;

	}
      else
	{
	  notify_fail("But the trough is empty!\n");
	  return 0;
	}
  }
else
    {
      notify_fail("Water what, where? \n");
      return 0;
    }
}


/*********************************************************************/
string
trough_desc()
{
  if (is_pumping)
    {
      return "A long wooden trough, filling with water from the pump.";
    }

  if (trough_full)
    {
      return "A long wooden trough filled with "+
	"water stands ready to water your animals.  Next to the trough is "+
	"a hand-operated pump.";
    }
  else
    {
      return "An empty wooden trough.  Next to the trough is a "+
	"hand-operated pump.";
    }
}


/*********************************************************************/
string
pump_desc()
{
  if (is_pumping)
    {
      if (TP==pumper)
	{
	  return "As you pump the handle, a steady stream of clear water "+
	    "jets into the trough.\n";
	}
      else
	{
	  return "A steady stream of clear water jets from the pump into the "+
	    "trough as "+pumper->query_art_name(TP)+ " pumps the handle.\n";
	}
    }
  else
    return "This pump can be used to fill the trough with fresh well water.";
}  


/***************************************************************************/
string
room_desc()
{
  if (is_pumping) 
    {
      return "a trough filling with water.";
    }

  if (trough_full) 
    {
      return "a trough filled with water.";
    }
  else
    {
      return "an empty water trough.";
    }
}

/***************************************************************************/
create_room()
{
  set_short("Outside the stable");
  set_long("You stand in a large yard.  The grass is beaten down "+
	   "by hoofprints.  South of here is a long, wooden, "+
	   "one-story building.  The east side of the building is "+
	   "fenced into a large corral.  Beside the large entrance is "+
	   "@@room_desc@@\n");

  add_prop(ROOM_I_ALLOW_STEED,1);
  
  add_exit(CALATHIN_DIR+"roads/road_n04.c","northwest");
  add_exit(CALATHIN_DIR+"stable.c","south");
   
  add_item( ({"stable", "building", "entrance","door"}) ,"The wide open "+
  "door of the stable tells you that it is open for business.\n");  

  add_item ( ({"trough","water"}),
	     "@@trough_desc@@\n");

  add_item ( ({"pump", "hand-operated pump"}), 
	     "@@pump_desc@@\n");

  add_cmd_item( ({"pump","handle","water","hand-operated pump"}),
		({"pump"}),
		"@@pump_water@@");

  add_item("corral", "@@exa_corral@@");
  add_item("fence",  "A high fence made of heavy wooden posts.\n");

  add_cmd_item("fence","climb","@@climb_fence@@");

  //have to load the corral, since I call it via VBFC in a desc
  (CORRAL)->long();
  
}

void 
init()
{
  ::init();
  add_action(drink_water, "drink");
  add_action(do_empty_trough, "empty");
  add_action(water_animal, "water");
}

/***********************************************************/
string
exa_corral()
{
object *horses;

horses=FIND_STR_IN_OBJECT("horses", 
			  find_object(CALATHIN_DIR+"stable_corral.c"));

if (sizeof(horses) == 0)
  {
    return "A fenced-in pasture about 2 acres in size.  The ground near the "+
      "stable shows the hoofprints of many horses.\n";
  }
else
  {
    return "A fenced-in pasture about 2 acres in size.  In the corral "+
      "you see "+COMPOSITE_LIVE(horses)+".\n";
  }

}


/***********************************************************/
string
climb_fence()
{
if (TP->query_skill(SS_CLIMB) > 35)
  {
    write( "You put one foot on the lower plank, grab the top "+
      "of the fence and heave yourself over.\n");

    TP->move_living("climbing over the fence", 
		    CALATHIN_DIR+"stable_corral.c",
		    1,
		    0);
    return "";

  }
else return "The fence is too high for you to dare climb.\n"; 
}
