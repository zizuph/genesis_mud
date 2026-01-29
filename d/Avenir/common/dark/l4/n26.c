// file name: ~Avenir/common/dark/l4/n26
// creator(s):  Farlong, Boriska
// last update: Jan 1995
// purpose: Entrance to worm lair 
// note:
// bug(s):
// to-do:     

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/worm.h"
// for logging

#define POLE_ID "worm_lair_entrance_pole"

// part of max fatigue to extract when holding the slab here
#define FAT_PENALTY 3

// minimal strength needed to lift the slab
#define STR_MIN 80
#define PARALYZE (OBJ+"hold_paralyze")
#define PARALYZE_PROP "_avenir_o_hold_paralyze"

#define LAIR_ENTRANCE ("/d/Avenir/common/dark/lair/entrance")


static int slab_lifted = 0;
static int slab_held = 0;
static int wait_alarm_id = 0;

void
create_room()
{
  set_short("Dirty chamber");
  set_long(
       "The tiny cobwebbed tunnel ends here in a rough-hewn stone chamber.\n"+
       "The choking dirt and dust hangs heavily in the air. There is a\n"+
        "slab of black rock on the floor.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

  AI("dust", "It is thick on the floor. Your footsteps stir " +
   "it up and cloud the air.\n");

  AI("dirt", "It is thick on the floor. Your footsteps stir " +
   "it up and cloud the air.\n");

  AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
   "face, tickling your skin.\n");

  add_item ("slab",
      "It is heavy and seems unmovable. Touching it does not help.\n");
  
  add_cmd_item ("slab",
    ({ "touch" }),
    ({"The slab is strangely hot as if something heats it up from beneath.\n",
      }) );
  
  AE(L4+"n25","southeast",0,DIRT);
  add_prop(ROOM_I_LIGHT,0);
  IN;
}

void
init()
{
  ::init();
  add_action ("do_move", "move");
  add_action ("do_move", "lift");
  add_action ("do_move", "push");
  add_action ("do_hold", "hold");
  add_action ("do_drop", "drop");
  add_action ("do_enter", "enter");
}    

int
do_move(string str)
{
  object tp = this_player();
  int fatigue_penalty;

  notify_fail ("Lift what?\n");
  
  if (str != "slab" && str != "slab with pole")
      return 0;
  
  notify_fail ("It is too heavy to lift without tools.\n");
  if (str != "slab with pole" || !present(POLE_ID, tp))
    return 0;
  
  notify_fail ("The slab is already lifted.\n");
  if (slab_lifted || slab_held)
      return 0;
  
  notify_fail ("You are not strong enough.\n");
  if (tp->query_base_stat(SS_STR) < STR_MIN)
    return 0;
  
  notify_fail ("You are too tired to lift the slab.\n");
  if (tp->query_fatigue() < tp->query_max_fatigue()/FAT_PENALTY)
    return 0;
  
  tp->catch_tell (
"Using the pole as a lever you slowly lift the slab over the rocky floor.\n" +
 "You can see the source of the heat now - the space under the slab\n" +
 "appears to be a hole filled with liquid fire.\nHold the slab!!!\n");

  say ("As " + QTNAME(tp) + " lifts the slab over the floor you can see\n" +
       "the source of the heat - the space under the slab appears to be\n" +
       "a hole filled with liquid fire!\n");
  
  tell_room (LAIR_ENTRANCE,
	     "You hear somebody lifting the slab revealing the passage!\n");
  
  add_item ("hole", "It appears to be a passage between hot red rocks!\n");
  slab_lifted = 1;
  wait_alarm_id = set_alarm (10.0, 0.0, "wait_for_free", tp);
  return 1;
}

//secures the slab when 'hold' command is issued within some time interval
// after 'lift slab'

int
do_hold(string str)
{
  object tp = this_player();
  int fatigue_penalty;
  float hold_time;
  object paralyze;
  
  if (!slab_lifted)
    return 0;
  
  notify_fail ("Hold what with what? Decide quickly!\n");
  
  if (str != "slab with pole" || !present(POLE_ID, tp))
    return 0;

  fatigue_penalty = tp->query_max_fatigue()/FAT_PENALTY;

  if (tp->query_fatigue() < fatigue_penalty)
    {
      tp->catch_msg ("You are too tired to hold the slab.\n");
      return 1;
    }
  
  tp->catch_tell (
  "Inserting the pole deep between the stone and rocky wall and applying\n" +
  "all your strength you hold the slab securely lifted above the passage.\n" +
  "You start sweating from the effort.\n");
  
  say (QCTNAME(tp) +
  " inserts the pole deep between the stone and rocky wall and applying"
       + " all " + tp->query_possessive() +
       " strength holds the slab securely lifted above the passage.\n" +
       QCTPNAME(tp) +
       " forehead covers with drops of sweat from the effort.\n");

  tell_room (LAIR_ENTRANCE,
    "Somebody secures the rock above allowing you to enter the passage.\n");
  
  slab_held = 1;
  remove_alarm (wait_alarm_id);
  hold_time = itof (random(tp->query_base_stat(SS_STR) - STR_MIN ));
  (paralyze = clone_object(PARALYZE))->move(tp);
  tp->add_prop(PARALYZE_PROP, paralyze); // stores objectpointer
  
  wait_alarm_id = set_alarm (hold_time, 0.0, "wait_for_free", tp);
  return 1;
}

void
wait_for_free(object tp)
{
  int fatigue_penalty = tp->query_max_fatigue()/FAT_PENALTY;
  object paralyze;
  
  // wait for free can be called not only by alarm, but when dropping
  // the slab of when stopping the paralyze.
  if (wait_alarm_id)
    {
      remove_alarm (wait_alarm_id);
      wait_alarm_id = 0;
    }
  
  tp->catch_tell (
    "You drop the slab.\n" +
    "With deafening sound the slab falls down, covering the hole again,\n" +
     "like a sarcophagus lid...\n");
  
  set_this_player(tp);
  say (
  "With deafening sound the slab falls down, covering the hole again,\n" +
       "like a sarcophagus lid...\n");

  tell_room (LAIR_ENTRANCE,
 "With deafening sound the slab falls down, covering the passage again,\n" +
  "like a sarcophagus lid...\n");
  
  slab_lifted = 0;
  slab_held = 0;
  tp->add_fatigue (-fatigue_penalty);
  remove_item ("hole");
  // remove paralyze from player.
  if (objectp(paralyze = tp->query_prop(PARALYZE_PROP)))
    paralyze->remove_object();
  tp->remove_prop(PARALYZE_PROP);
}

int
do_drop(string str)
{
  object tp = this_player();
  
  if (!slab_held && !slab_lifted)
    return 0;
  
  if (!str || str != "slab")
    return 0;
  wait_for_free(tp);
  return 1;
}

int
do_enter(string str)
{
  object tp = this_player();

  if (!slab_lifted)
    return 0;
  
  notify_fail ("It is too dangerous to enter now!\n");
  if (!slab_held)
    return 0;
  
  notify_fail ("Enter what?\n");
  if (!str || str != "hole")
    return 0;
  tp->move_living ("through hole", LAIR + "entrance", 1);
  tp->catch_tell ("You step into the blazing inferno!\n");
  WRITE_LOG(capitalize(tp->query_real_name()) + " entered the lair.\n");
  return 1;
}
  
public int
query_slab_lifted() { return slab_lifted;}

public int
query_slab_held() { return slab_held;}

