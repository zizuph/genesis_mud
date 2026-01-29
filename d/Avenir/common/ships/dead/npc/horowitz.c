
// file name: horowitz.c
// creator: Cirion, Feb 14, 1996
// last update:
//          Lilith, Jan 2022 -- Added see_dark, as players carrying 
//              darkness is interfering with his ability to get coffins. 
//          Gorboth, Oct. 2016 - Increased str in set_stat extra so
//                                   he can carry ogres too.
//          Lilith, May 2014 - Faster dragging so the boat
//			  trips aren't so very long between.
//          Cirion, October 9 1996, worked on seperating the
//          coffins from the goblin, so that each
//          could be used as an example for future
//          objects of these types.
//          Thanks to Olorin for help on the alarms.
// purpose: Goblin bearer who carries coffins to the
//           Dead Isle ship.
// note:    Many thanks to Quetzl for help with this.
// bug(s):
// to_do:

#pragma strict_types

inherit "/std/monster.c";
#include "/d/Avenir/common/ships/dead/deadship.h"
#include <math.h>

int alarm_id, counter;
object ship;
string *ship_warehouse = (({ "disembark" , "south" ,
                           "east" , "south" , "east" }));
string *warehouse_ship = (({ "west" , "north" , "west" ,
                               "north" , "board" }));
string *ship_dead = (({ "disembark" , "north" , "north" ,
                        "east" , "northeast" , "north" ,
                        "northeast" , "north" , "north" }));
string *dead_ship = (({ "south" , "south" , "southwest" ,
                        "south" , "southwest" , "west" ,
                        "south" , "south" , "board" }));
mixed *actions = (({ "smile" }));

/*            Prototypes           */
int      check_location(string where);
void     verify_ship();
void     verify_ware();
void     verify_dead();
int      bazaar_routine();
int      dead_routine();
int      make_trip();
void     pickup(int num = 0);
void     departure();

void create_monster()
{
   set_name(({"horowitz","bearer"}));
   add_name("deadislandcoffin_bearer");

   set_long("This large goblin has a grim "
           +"expression on his face. He appears "
           +"to be very old, and resigned to "
           +"some terrible task.\n");
   set_race_name("goblin");
   set_adj(({"grim","sturdy"}));
   set_stats(({80, 80, 70, 40, 40, 95}));
   set_stat_extra(0, 700);  // Make him very strong
   add_prop(OBJ_S_WIZINFO, "Don't be disturbed by his "
      +"disproportionate strength ... I used set_stat_extra, "
      +"so his xp reward won't be unbalanced..He needs to be "
      +"able to move Ogres. See the doc in the ships/dead/* dir "
      +"for instructions on how to 'fix' any coffin-related "
      +"problems that arise.\n");

   add_prop(DEAD_ENABLE, 1); // So he can board the ship
   add_prop(LIVE_I_SEE_DARK, 1); // So he can get coffins in the dark.

   set_alignment(0);

   set_skill(SS_DEFENCE, 45);
   set_skill(SS_WEP_KNIFE, 40);

   set_skill(SS_AWARENESS, 55);
   set_skill(SS_PARRY, 10);

   seteuid(getuid());
}

void arm_me()
{
// Nothing for now...
   return;
}

void set_ship(object what)
{
    ship = what;
}

int check_location(string where)
{
  if(file_name(ENV(TO)) == where)
    return 1;
  else
    command("peer");
    command("emote mumbles something about making a "
           +"wrong turn somewhere.");
    move_living("away", where);
    return 0;
}

void verify_ship()    { check_location(SHIPLOC); }
void verify_ware()    { check_location(WAREHOUSE); }
void verify_dead()    { check_location(DEADLOC); }
   
int bazaar_routine()
{
   actions = ({verify_ship, pickup}) + 
                     ship_warehouse + 
                     ({verify_ware, "drop coffins", pickup}) +
                     warehouse_ship + 
                     ({verify_ship, "drop coffins", pickup}) +
                     ship_warehouse +
                     ({verify_ware, "drop coffins", pickup}) +
                     warehouse_ship +
                     ({verify_ship, "drop coffins", pickup}) +
                     ship_warehouse +
                     ({verify_ware, "drop coffins", pickup}) +
                     warehouse_ship +
                     ({verify_ship, "drop coffins", departure});

    if(get_alarm(alarm_id)) return 0;
    counter = 0;
    alarm_id = set_alarm(1.5, 0.5, make_trip);
    return 1;
}

int dead_routine()
{
   actions = ({verify_ship, pickup}) + 
                     ship_dead + 
                     ({verify_dead, "drop coffins", pickup}) +
                     dead_ship + 
                     ({verify_ship, "drop coffins", pickup}) +                     
                     ship_dead + 
                     ({verify_dead, "drop coffins", pickup}) +
                     dead_ship + 
                     ({verify_ship, "drop coffins", pickup}) +    
                     ship_dead + 
                     ({verify_dead, "drop coffins", pickup}) +
                     dead_ship +
                     ({verify_ship, "drop coffins", departure});

    if(get_alarm(alarm_id)) return 0;
    counter = 0;
    alarm_id = set_alarm(1.5, 0.5, make_trip);
    return 1;
}

int make_trip()
{
    mixed f; 

    f = actions[counter]; 
   
    if (functionp(f)) 
       f();
    else
       command(f);

    counter++;

    if(counter >= sizeof(actions) || !actions[counter])
      {
        remove_alarm(alarm_id);
        alarm_id = 0;
        counter = 0;
        return 0;
       }

    return 1;
} 
      
void pickup(int num = 0)
{
    object which = ENV(TO)->query_coffins(num);

    if (which)
    {
	command("close "+which->id_name());
	command("emote grunts.");
	if (!command("get "+which->id_name()))
	{
	    command("emote murmurs a curse.");
	    which->too_heavy();
	    pickup(++num);
	}
    }
}

void departure()
{
   if(ship)
    ship->lets_get_going();
}

string query_m_out()
{
  object   cof;

  if(!(cof = present("coffin", TO)))
   return ::query_m_out();

  if(function_exists("create_deck", ENV(TO)))
   return "drags "+LANG_ASHORT(cof)+" off";
  else
   return "drags "+LANG_ASHORT(cof);
}

string query_m_in()
{
  object   cof;

  if(!(cof = present("coffin", TO)))
   return ::query_m_in();

  if(function_exists("create_deck", ENV(TO)))
   return "drags "+LANG_ASHORT(cof)+" off the ship";
  else
   return "arrives dragging "+LANG_ASHORT(cof)+"";
}

void get_rid_of_coffins()
{
  object   cof;

  while(cof = present("coffin", TO))
   cof->move(ENV(TO), 1);
}

void do_die(object killer)
{
    command("drop coffins");
/*
    get_rid_of_coffins();
 */
    command("sigh sadly");
    ::do_die(killer);
}

/*
void remove_object()
{
  command("$drop coffins");
  remove_object();
}
*/
