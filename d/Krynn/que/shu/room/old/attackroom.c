/* created by Aridor 06/28/94 */

#include "../local.h"

inherit BASE_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include RND_MEET

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
 */

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


static object monster;


/*prototypes*/
void start_change_this_room();
void hurt_everyone_in_the_room();
void hurt_it(object livin);


public void
create_attack_room() { }

public nomask void
create_room() 
{ 
    create_attack_room();
    ATTACKMASTER->add_room(TO); /* add all rooms to change list */
}

public nomask void
set_change_msg(int which, string str) { change_msg[which] = str; }

public nomask void
set_change_short(int which, string str) { short_desc[which] = str; }

public nomask void
set_change_long(int which, string str) { room_desc[which] = str; }

public varargs string
short(object for_obj)
{
    int state = QUERY_STATE;
    if (state == 0)
      return ::short(for_obj);
    else
      return check_call(short_desc[state], for_obj);
}

public varargs string
long(string str)
{
    int i, state = QUERY_STATE;
    mixed lg;

    if (state == 0 || str)
      return ::long(str);

    lg = room_desc[state];
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

/* hook which can be redefined in case the changing can depend
 * on something in the room itself.
 * Return: 1 if ok to change state
 *         0 if no change now.
 */
public int
hook_change_room(int which) 
{ 
    if (which == 1)
      if (monster || present("draconian",TO))
	return 0;
    return 1;
}

public nomask void
start_change_this_room()
{
  string *exitrooms = query_exit_rooms();
  int i,j,state = QUERY_STATE;
  if (state != 0)
    return;

  tell_room(this_object(),change_msg[state]);
  monster = RANDOM_MEET(TABLE);
  monster->set_aggressive(1);
  monster->move_living("xx",TO);
  if (random(100) < FIRE_CHANCE)
    add_prop(OBJ_I_HAS_FIRE, 1);
  hurt_everyone_in_the_room();
}

public nomask void
change_state_of_room()
{
    int state = QUERY_STATE;
    tell_room(this_object(),change_msg[state]);
    remove_prop(OBJ_I_HAS_FIRE);
}

static void
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
    set_alarm(itof(random(40)+5),0.0,"hurt_everyone_in_the_room");
}

static void
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

