// name: /d/Avenir/common/ships/dead/ship.c
// creator(s): Ilyian, Sept 23
// last update: 
//              Lilith, Sept 2021 Added check for DMASK_PROP
//                 to allow passage for death mask wearers.
//              Lilith 27 MAY 2014 Made ship go faster. 
//              Once Every 20 mins is too slow.
// purpose: Ship between bazaar and Isle of the Dead
// note: I had to redefine a bunch of the functions
//       in /d/Genesis/ship/ship.c here, mostly because
//       the inherited ship does not seem to allow for
//       the ship to move based on anything except a
//       basic timer.

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>
#include "deadship.h"
#include "/sys/stdproperties.h"
#include "/d/Avenir/include/relation.h"

#define DEADPORT    "/d/Avenir/common/dead/path/landing"
#define BAZPORT     "/d/Avenir/common/bazaar/intr/d_landing"

object gobbo, cap;
int which_port;
int myevent;
string query_port();

void
create_ship()
{
    if (!IS_CLONE)
      return;

    set_name("barge");
    add_name(({"boat", "ship"}));
    add_name(({"bark", "barque"}));
    add_adj("long");
    LONG("This is a long and eerie cargo barge. Both the "
        +"bow and the stern are raised up in a slow "
        +"arc, and the long slats of wood that run along "
        +"the sides are made of a weathered brown wood. At "
        +"the base of the boat, the wood is stained with "
        +"a murky black substance.\n");

    set_deck(DEAD_DIR + "deck");
      myevent=1;

    seteuid(getuid());
     cap = clone_object(DEAD_DIR + "npc/captain");
       cap->arm_me();
       set_captain(cap);

     gobbo = clone_object(DEAD_DIR + "npc/horowitz");
       gobbo->move(query_deck()[0]);
       gobbo->arm_me();
       gobbo->set_ship(TO);
       gobbo->bazaar_routine();

    set_callout_fq(3);

    set_places_to_go(({
     BAZAAR + "intr/d_landing",  /* Pier in Bazaar */
      SEA + "darksea1",
      SEA + "darksea2",
      SEA + "darksea3",
      SEA + "darksea4",
      SEA + "darksea5",
      SEA + "darksea6",
     DEAD + "path/landing",   /* Isle of the Dead */
      SEA + "darksea6",
      SEA + "darksea5",
      SEA + "darksea4",
      SEA + "darksea3",
      SEA + "darksea2",
      SEA + "darksea1", }));

    set_time_between_stops(3);
    enable_reset();
  }

void
reset_ship()
{
  object cap;
  if(!objectp(query_captain()))
    {
      cap=clone_object(DEAD_DIR + "npc/captain");
      cap->equip_me();
      set_captain(cap);
      cap->move(query_deck()[0]);
      sail_away_out_on_the_open_sea();
    }
}

string query_port()
{
   string where = file_name(ENV(TO));

   if(where == DEADPORT)
    return "dead";
   else
   if(where == BAZPORT)
    return "bazaar";
   else
    return "nowhere";
}

/*
 * Function name: start_ship
 * Description  : Make the ship do it's thing
 * Arguments    : where - the location number to start in
 * Returns      : 0 - failed to start the ship
 *                1 - ship started
 */
public varargs int
start_ship(int where)
{
    int time;
    object pier, captain;

    if (!places_to_go || !time_between_stops || !query_deck() ||
        sizeof(places_to_go) > sizeof(time_between_stops) ||
        !(captain = query_captain()) || !query_callout_fq())
        return 0;
    captain->set_ship(this_object());
    if (where)
    {
        if (where < 0 || where >= sizeof(places_to_go))
            return 0;
        location = where;
        move(places_to_go[where]);
    }
    else
        move(places_to_go[0]);
    call_arrive(environment());
    call_no = time_between_stops[where];
    if (environment()->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
        set_board_enabled(1);
        if (captain)
        {
            captain->move_living("the ship", environment());
            captain->command("grumble");
        }
    }
    else if (query_captain())
    {
        pier = environment(captain);
        captain->move_living("boarding the ship", query_deck()[0]);
        captain->command("say And we're off!");
        tell_room(pier, "The ship leaves at once.\n");
    }
}

/*
 * This function enables the boat to make the
 * trip when the goblin bearer is ready to
 * go. Todo: What if captain is dead?
 */
void lets_get_going()
{
    captain->command("sigh .");
    captain->command("board");
     myevent=0;
    sail_away_out_on_the_open_sea();
}


/*
 * Function name: board
 * Description  : Allow a player to board the ship if he have got a ticket, or
 *                if the fare is free of charge
 * Arguments    : what - what we want to enter
 * Returns      : 1 - success
 *                0 - wrong parameters
 */
int
board(mixed what)
{
  object ticket, *tmp;

  if (!board_enabled)
      return 0;
  if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what,
      environment(this_player()))) || this_object() != tmp[0]))
      return 0;

  environment(this_player())->set_dircmd(what);

  if (this_player()->query_wiz_level() ) 
  {	  
      this_player()->move_living("boarding the ship", query_deck()[0]);
	  write("Wizards can go where mortals fear to tread.\n");
	  return 1;
  }

  if (IS_INFIDEL(this_player()))
  {
      if (query_captain())
      {
          query_captain()->command("say I will not risk Plalgus' wrath.");
      }
      else
      {
          write("Something stops you from boarding the "+
              short() + ".\n");
          tell_room(environment(), QCNAME(this_player()) + " tries to "+
              "board the " + short() + ", but is prevented.\n",
              this_player());
      }
      return 1;
  }

  // This is an npc working on this boat, wearing a death mask, 
  // or an undead player
  if (!this_player()->query_prop(DEAD_ENABLE) &&
      !this_player()->query_prop(DMASK_PROP) &&
	  !this_player()->query_prop(LIVE_I_UNDEAD))
    {
      if (query_captain())
       {
         query_captain()->command("say You'll need to be dead to get " +
             "aboard this ship, "+
             this_player()->query_race() + ".");
       }
      else
       {
         write("Something stops you from boarding the "+
             short() + ".\n");
         tell_room(environment(), QCNAME(this_player()) + " tries to "+
             "board the " + short() + ", but is prevented.\n",
             this_player());
       }
      return 1;
    }

   tell_room(environment(), QCTNAME(this_player()) + " boards the "+
            short() + ".\n", this_player());
   write("You board the " + short() + ".\n");
   this_player()->move_living("boarding the ship", query_deck()[0]);

  return 1;
}

/*
 * Function name: sail_away_out_on_the_open_sea
 * Description  : The core of the ship; this is called every callout_fq
 *                seconds and will move the ship around at appropiate
 *                intervals
 * Update: Looks like I have to redefine the whole damn
 *         thing because it doesn't look like the code
 *         allows for a stop that is based on anything
 *         except a timer.
 */
void
sail_away_out_on_the_open_sea()
{
    int time;
    object pier, captain;

     if(myevent)
                  {return; }
     else
    if (call_no < 1)
    {
        board_enabled = 0;
        location++;
        if (location >= sizeof(places_to_go))
            location = 0;
        call_no = time_between_stops[location];

        if (captain = query_captain())
            if (file_name(pier =
                environment(query_captain())) != query_deck()[0])
            {
             captain->move_living("boarding the ship", query_deck()[0]);
             tell_room(pier,
             capitalize(LANG_ADDART(short())) + " starts moving away.\n");
            }

        call_left(environment(), places_to_go[location]);
        call_arrive(places_to_go[location]);
        move(places_to_go[location]);

        if (places_to_go[location]->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
        {
            tell_room(places_to_go[location],
            capitalize(LANG_ADDART(short())) + " just came in.\n");
            myevent = 1;
            if (captain)
            {
                captain->move_living("the ship", places_to_go[location]);
                captain->command("sigh");
            }
            set_board_enabled(1);
           if(query_port() == "dead")
              gobbo->dead_routine();
           else
              gobbo->bazaar_routine();
        }
        else
            tell_room(places_to_go[location], capitalize(LANG_ADDART(short()))+
                      " passes by.\n");
    }
    else
        call_no--;

           set_alarm(itof(query_callout_fq()), 0.0, sail_away_out_on_the_open_sea);
}
