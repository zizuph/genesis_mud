/* created by Aridor 06/28/94 */

inherit "/std/room";

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#define DIS(xx)     xx->query_base_stat(SS_DIS)
#define SAVE_FILE   ROOM + "attack_state"
#define CHANCE 40   /*chance that there is a fire in the room during attack*/
#define TRY_AGAIN   1000 /*try to change room again after this time if
                           it failed before*/

/* This is support for a changing room. 
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

static int *state_time = ({0, 3000, 3000, 3000, 5000});
int state_of_room = 0;

static string *short_desc = ({"",/*just a dummy, the short() is used here instead.*/
		       "A street under attack",
		       "A destroyed street",
		       "A destroyed street",
		       "A street under construction"});
static string *room_desc = ({"",/*just a dummy, the long() is used here instead.*/
		      "You are standing in a street, fire and smoke is all around you. " +
		      "You hear screams and rude laughter.\n",
		      "You stand in a charred black street, no living things are left.\n",
		      "People are all around you starting to sort through the rubble.\n",
		      "People are building up the buildings and tents again.\n"});

static string *change_msg = ({"Like a dark cloud you can see shapes moving closer from above!\n",
		       "The flames slowly burn out.\n",
		       "The first people arrive in this deserted village.\n",
		       "The people start to rebuild their village.\n",
		       "The people seems to have finished rebuilding the village. Peace has returned again.\n"});

/*prototypes*/
void start_change_this_room();
void hurt_everyone_in_the_room();
void hurt_it(object livin);


void
create_attack_room() { }

nomask void
create_room() 
{ 
    create_attack_room();
/*    restore_object(SAVE_FILE);*/
}

void
set_change_msg(int which, string str) { change_msg[which] = str; }

void
set_change_short(int which, string str) { short_desc[which] = str; }

void
set_change_long(int which, string str) { room_desc[which] = str; }

void
set_state_duration(int which, int time) { state_time[which] = time; }

string
short(object for_obj)
{
    if (state_of_room == 0)
      return ::short(for_obj);
    else
      return check_call(short_desc[state_of_room], for_obj);
}

string
long(string str)
{
    int i;
    mixed lg;

    if (state_of_room == 0 || str)
      return ::long(str);

    lg = room_desc[state_of_room];
    if (str)
	return lg;
    if (!lg)
	lg = "";

    while ((i = member_array(0, room_descs)) >= 0)
	room_descs = exclude_array(room_descs, i, i + 1);

    if (room_descs) 
	for (i = 1; i < sizeof(room_descs); i += 2)
	    lg = lg + check_call(room_descs[i]);

    if (room_no_obvious)
	return lg;

    return lg + this_object()->exits_description();
}

void
enter_inv(object new, object from)
{
    ::enter_inv(new, from);
    if ((new->id("dragon") || new->id("draconian")) && (state_of_room == 0))
      start_change_this_room();
}

/* hook which can be redefined in case the changing can depends
 * on something in the room itself.
 * Return: 1 if ok to change state
 *         0 if no change now.
 */
int
hook_change_room(int which) { return 1; }

void
start_change_this_room()
{
  string *exitrooms = query_exit_rooms();
  int i,j;
  if (state_of_room != 0)
    return;
  if (hook_change_room(0))
    {
	tell_room(this_object(),change_msg[state_of_room]);
	state_of_room++;
	save_object(SAVE_FILE);
	if (random(100) < CHANCE)
	  add_prop(OBJ_I_HAS_FIRE, 1);
	hurt_everyone_in_the_room();
	call_out("change_state_of_room",state_time[state_of_room]);
    }
}

void
change_state_of_room()
{
    if (hook_change_room(state_of_room))
      {
	  tell_room(this_object(),change_msg[state_of_room]);
	  state_of_room++;
	  save_object(SAVE_FILE);
	  remove_prop(OBJ_I_HAS_FIRE);
	  if (state_of_room >= sizeof(room_desc))
	    state_of_room = 0;
	  else
	    call_out("change_state_of_room",state_time[state_of_room]);
      }
    else
      call_out("change_state_of_room",TRY_AGAIN);
}


query_state() { return state_of_room; }

void
hurt_everyone_in_the_room()
{
    int i;
    object *things;
    if (!query_prop(OBJ_I_HAS_FIRE))
      return;
    seteuid(getuid(this_object()));
    things = all_inventory(this_object());
    for (i = 0; i < sizeof(things); i++)
      {
	if (things[i]->query_prop(LIVE_I_IS))
	  if (!things[i]->query_prop(OBJ_I_RES_FIRE))
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
    call_out("hurt_everyone_in_the_room", random(40) + 5);
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
      hitp = -random(hitp + 1);
    else
      hitp = - random(100) - 10;
    /*hitpoint modifier on RES_FIRE:*/
    hitp -= hitp * (livin->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
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
    hitp = -hitp * 50 / DIS(livin);
    hitp = (hitp > 100 ? 100 : hitp);
    co->cb_add_panic(hitp);
    co->cb_may_panic("north");
    livin->do_die(this_object());
}

