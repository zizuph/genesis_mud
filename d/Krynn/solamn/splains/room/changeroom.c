/* created by Aridor 10/27/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

#define DIS(xx)   (xx->query_base_stat(SS_DIS) > 10 ? xx->query_base_stat(SS_DIS) : 10)
#define SPARK       "/d/Krynn/solamn/splains/obj/spark"
#define CHANCE      75 /* 0%-100% chance for the room to burst into flames*/
#define CHANGEROOM  (ROOM + "changeroom")

/* This is support for a changing room. By redefining the enter_inv() function
 * it is possible to trigger the changing of a room, ie. its descriptions.
 * There are 4 arrays containing the short and long descriptions, the
 * changeover messages and the duration of each state (*short_desc, *room_desc,
 * *change_msg, *state_time, respectively). 
 *
 * room_desc contains an "" (empty string) in pos 0, at its place, the
 * normal long() desc. is used.
 *
 * change_msg contains the message displayed whenever the state of the 
 * room changes. Pos 0 contains the message to change from state 0 to 
 * state 1, etc.
 *
 * state_time contains the time for a state to exist, after that time
 * the room changes over to a new state, Pos 0 is ignored as this is 
 * the default state and constantly the current state unless triggered
 * with enter_inv().
 */

int *state_time = ({0, 300, 300, 300, 500}),
    state_of_room = 0;

string *short_desc = ({"",/*just a dummy, the short() is used here instead.*/
		       "A Fire",
		       "On the plains",
		       "On the plains",
		       "On the plains"});
string *room_desc = ({"",/*just a dummy, the long() is used here instead.*/
		      "This is a blazing inferno! Flames are all around you and you feel very hot!\n",
		      "You stand on a charred black landscape, no living things are left.\n",
		      "The flat land is all black and sooty. Despite that you can see green grass growing anew.\n",
		      "Green grass is all around you. These plains are really plain, but everything looks healthy and vivid.\n"});

string *change_msg = ({"The grass catches fire!\n",
		       "The flames slowly burn out.\n",
		       "The first little green spots appear in the charred black landscape.\n",
		       "The grass has grown back to normal.\n",
		       "The grass starts to dry out. It just hasn't rained in a very long time. "
			 + "Everywhere, you see less green and more brown around you.\n"});



/*prototypes*/
void change_state_of_room();
void hurt_everyone_in_the_room();
void hurt_it(object livin);

varargs string
plains_describe(string dir1, string dir2)
{
    if (dir1==0)
      {
	  if (random(2) != 1)
	    return "You are standing knee-deep in brownish grass " +
	      "which seems to stretch out to the horizon in all " +
	      "directions. It is possible to go in all directions.\n";
	  else
	    return "These are the Plains of Solamnia. Brownish grass " +
	      "stretches out in all directions. These plains are really " +
	      "plain! Despite that you can make out some mountains very " +
	      "far to the west.\n";
      }
    else
      {
	  if (dir2 == 0)
	    return "You are on the Plains of Solamnia. There is " +
	      "brownish grass stretching out in all directions. " +
	      "To the " + dir1 + " you can see an " +
	      "irregularity in the grass.\n";
	  else
	    return "You are on the Plains of Solamnia. There is " +
	      "brownish grass stretching out in all directions. " +
	      "To the " + dir1 + " and to the " + dir2 + " you " +
	      "can see an irregularity in the grass.\n";
         }
}


void
create_change_room()
{
    set_long("On the plains, the grass seems dry like cinder.\n");
}

nomask void
create_splains_room()
{
    create_change_room();
    
    // Added to stop spawning Warfare NPCs in this room.
    if (MASTER == CHANGEROOM)
        set_num_npc(0);
}
    
void 
set_change_msg(int which, string str)
{
    change_msg[which] = str; 
}

void
set_change_short(int which, string str) 
{
    short_desc[which] = str; 
}

void
set_change_long(int which, string str) 
{
    room_desc[which] = str; 
}

void
set_state_duration(int which, int time) 
{
    state_time[which] = time; 
}

void
init()
{
  ::init();
/*    ADA("pour","pour");
    ADD("pour","pour out");
    ADD("pour","empty");*/
}

mixed
short()
{
    if (state_of_room == 0)
      return query_short();
    else
      return short_desc[state_of_room];
}

varargs mixed
long(string str)
{
    if (str)
      return ::long(str);

    if (state_of_room == 0)
      return long_desc(query_long());
    else
      return long_desc(room_desc[state_of_room]);
}

int
pour(string str)
{
  object *what;
  if (!str)
    return 0;
  what = FIND_STR_IN_OBJECT(str, TP);
  if (!what)
    return 0;
  if (what->query_prop(OBJ_I_CONTAIN_WATER))
    {
      what->remove_prop(OBJ_I_CONTAIN_WATER);
      write("You empty the " + (what->short()) + " onto the ground.\n");
      tell_room(QCTNAME(TP) + " empties " + LANG_ADDART(what) + " onto the ground.\n", TP);
      if ((random(5000)+1000) < (what->query_prop(OBJ_I_VOLUME)))
	set_alarm(itof(random(5) + 3),0.0,"change_state_of_room");
      else
	tell_room("It doesn't have any effect, though.\n");
      return 1;
    }
  NF("Hmmm, this doesn't seem to work.\n");
  return 0;
}

void
enter_inv(object new, object from)
{
    ::enter_inv(new, from);
    if ((random(100) < CHANCE) &&
	(new->query_prop(OBJ_I_HAS_FIRE) && (state_of_room == 0)))
      set_alarm(itof(random(10) + 3),0.0,"start_change_this_room");
    if ((state_of_room == 1) && (new->query_prop(OBJ_I_CONTAIN_WATER)))
      set_alarm(itof(random(5) + 3),0.0,"change_state_of_room");
}

void
extinguish_fire_in_room()
{
  mixed* calls;
  int i;

  if (state_of_room != 1)
    return;

  calls = get_all_alarms();
  for(i=0;i<sizeof(calls);i++)
  {
      if (calls[i][1] == "fly_spark")
	remove_alarm(calls[i][0]);
      else if (calls[i][1] == "change_state_of_room")
      {
	  remove_alarm(calls[i][0]);
	  change_state_of_room();
      }
  }
}

void
start_change_this_room()
{
  string *exitrooms = query_exit_rooms();
  int i,j;
  if (state_of_room != 0)
    return;
  tell_room(this_object(),change_msg[state_of_room]);
  state_of_room++;
  add_prop(OBJ_I_HAS_FIRE, 1);

  /*write_file("/d/Krynn/solamn/splains/log/firelog", extract(ctime(time()), 4, 15)
   *           + " " + capitalize(TP->query_real_name()) + "\n");
   */
  set_alarm(itof(state_time[state_of_room]),0.0,"change_state_of_room");
  for (i = 0; i < sizeof(exitrooms); i++)
    for (j = 0; j < 10; j++)
      if (!random(3))
	set_alarm(itof(random(state_time[state_of_room])),0.0,"fly_spark",exitrooms[i]);
  hurt_everyone_in_the_room();
}

void
change_state_of_room()
{
  tell_room(this_object(),change_msg[state_of_room]);
  state_of_room++;
  remove_prop(OBJ_I_HAS_FIRE);
  if (state_of_room >= sizeof(room_desc))
    state_of_room = 0;
  else
    set_alarm(itof(state_time[state_of_room]),0.0,"change_state_of_room");
}


void
fly_spark(string to_room)
{
    object spark = clone_object(SPARK);
    to_room->load_me();
    spark->move(to_room);
    spark->come_flying();
}

int
query_state() 
{
    return state_of_room; 
}

void
hurt_everyone_in_the_room()
{
    int i;
    object *things;
    if (state_of_room != 1)
      return;
    seteuid(getuid(this_object()));
    things = all_inventory(this_object());
    for (i = 0; i < sizeof(things); i++)
      {
	if (interactive(things[i]) || things[i]->query_prop(LIVE_I_IS))
	  hurt_it(things[i]);
	else
	  if (!random(4) && things[i]->short() != "spark"
	      && (things[i]->query_prop(OBJ_I_RES_FIRE) < random(100))
	      /*&& things[i]->query_prop(OBJ_I_VOLUME) <= 5000
                && things[i]->query_prop(OBJ_I_WEIGHT) <= 5000 */
	      && !things[i]->query_prop(MAGIC_AM_MAGIC))
	    {
	      tell_room(environment(things[i]),"The " + (things[i]->short()) + " is destroyed by the fire.\n");
	      things[i]->move_all_to(environment(things[i]));
	      things[i]->remove_object();
	    }
      }
    set_alarm(itof(random(40) + 5),0.0,"hurt_everyone_in_the_room");
}

void
hurt_it(object livin)
{
    object co;
    int hitp;
    string str;
    hitp = livin->query_hp();
    co = livin->query_combat_object();
    if (hitp < 21)
      hitp = -random(hitp + 3);
    else
      hitp = -hitp / 4 - 10;
    /*hitpoint modifier on RES_FIRE:*/
    hitp -= hitp * (livin->query_prop(OBJ_I_RES_FIRE) + livin->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
    if (hitp > 0)
      hitp = 0;
    else
      {
	if (hitp > -20)
	  str = "slightly ";
	else if (hitp > -50)
	  str = "somewhat ";
	else if (hitp > -100)
	  str = "";
	else
	  str = "badly ";
	tell_object(livin,"You are " + str + "burnt from the flames.\n");
      }
    tell_room(environment(livin), QCTNAME(livin) + " is engulfed in the flames.\n", livin);    
    livin->heal_hp(hitp);
    hitp = -(hitp * 50 / DIS(livin));
    hitp = (hitp > 80 ? 80 : hitp);
    co->cb_add_panic(hitp);
    co->cb_may_panic("north");
    livin->do_die(this_object());
}

