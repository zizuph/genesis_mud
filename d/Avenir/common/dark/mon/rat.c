// -*-C++-*-
// file name: ~Avenir/common/dark/mon/rat.c
// creator(s):  Boriska
// last update: Boriska,  Apr 24 1995, reduced logging verbosity
//      Lilith, May 2022: added restrain path
// purpose: inhabitant of Avenir tunnels, part of rat hunting quest
// note: see the doc in ~Avenir/QUESTS/rat_hunting
// bug(s):
// to-do:     

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <tasks.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/rat_trap.h"

#define H_BODY 0
#define H_TAIL 2
#define H_HEAD 4

// adjectives to pick from
static string *adjs =
({ "fat", "confused", "pathetic", "plump", "skinny", "funny"});
int adj_num = sizeof (adjs);

static string *texts = ({
  "You notice rat attracted by the smell approaching the trap...\n",
  "It is getting closer, sniffing around the bait...\n",
  "closer...\n",
  "Closer...\n",
  "CLOSER!\n",
  "\n\nBANG!!!\n\n"
});
static int text_len = sizeof(texts);

static int alarm_id;
static int step = 0;
static string adj;
static int alive;
static int tail_off_delay;

private void caught(object hunter);
private void not_caught(object hunter);
void start_trap_seq (object trap);
void stop_alarm();

void
create_creature ()
{
  if (!IS_CLONE)
    return;
  
  adj = adjs[random(adj_num)];
  set_name ("rat");
  add_name (RAT_ID);
  add_name (RAT_ALIVE_ID);
  set_short ("@@my_short@@");
  add_adj (adj);
  
  set_race_name ("rat");
  set_long ("@@my_long@@");
  
  set_gender (G_NEUTER);
  set_stats ( ({20,15,15,1,1,5}) );
  
  set_restrain_path("/d/Avenir/common/dark/l4/");
  set_monster_home("/d/Avenir/common/dark/l4/w10");
  set_random_move(5);
  
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (SS_DEFENSE, 50);
  
  set_attack_unarmed (0, 10, 10, W_IMPALE, 75,"teeth");
  set_attack_unarmed (2, 10, 10, W_SLASH, 75,"paws");
  
  set_hitloc_unarmed ( H_BODY, 10, 30, "body");
  set_hitloc_unarmed ( H_HEAD, 10, 30, "head");
  set_hitloc_unarmed ( H_TAIL, 10, 40, "tail");

  add_prop (LIVE_I_SEE_DARK, 1);
  add_prop (CONT_I_WEIGHT, 4000);
  add_prop (CONT_I_VOLUME, 4000); 
  add_prop (CONT_I_MAX_WEIGHT, 5000);
  add_prop (CONT_I_MAX_VOLUME, 5000);
  add_prop (OBJ_I_WEIGHT, 4000);
  add_prop (OBJ_I_VOLUME, 4000);
  alive = 1;
}  

void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
  ::cr_got_hit(hid, ph, att, aid, dt,dam);
  if (hid == H_TAIL && ph > 0 && !tail_off_delay)
    tail_off_delay = set_alarmv(1.0, 0.0, "tail_off", ({att, environment()}));
}

private void
tail_off(object att, object where)
{
  if (objectp(att)) {
    att->catch_msg ("You cut the rat's tail off!\n");
    tell_room (where, QCTNAME(att) + " cuts the rat's tail off!\n", att);
  }
  clone_object(OBJ + "r_tail")->move(where);
  remove_hitloc (H_TAIL);
}

string
my_short()
{
  string str = adj + " rat";
  return alive ? str : "unconscious " + str;
}

string
my_long ()
{
  string str = "Gray sneaky rat which has never seen the sunlight.\n";
  return alive ? str : str + "It is unconscious.\n";
}
  
void
init_living()
{
  ::init_living();
  add_action ("do_catch", "catch");
}

int
do_catch (string str)
{
  object tp = this_player();
  
  notify_fail ("Catch whom?\n");
  
  if (( !str || !alive || str != "rat") && str != short())
    return 0;

  tp->catch_msg (
    capitalize(short()) + " bites your finger. It hurts!\n");

  say (QCTNAME(tp) + " fails miserably in " + tp->query_possessive() +
       " clumsy attempt to catch a " + short() + ".\n");
  return 1;
}

void
enter_env (object dest, object old)
{
  object trap;
  object hunter;
  
  ::enter_env (dest,old);
    
  if (!dest->this_room())
    return;

  if (query_attack() || !alive)
    return;

  if (!(trap = present(TRAP_ID, dest)))
    return;

  start_trap_seq (trap);
}

void
start_trap_seq( object trap)
{
  step = 0;
  alarm_id = set_alarm (4.0, 8.0, "trap_seq", trap);
}

// This is a cludge to prevent the rat leaving the room while inside
// trap_seq sequence or while being inconsicious.
// It would be much better if there were a function
// disabling set_random_move() effect.
// oke_to_move originally is used to prevent from walking away from fighting

mixed
oke_to_move (string exit)
{
  string res;
  
  if (res = ::oke_to_move(exit))
    return (alarm_id || !alive) ? 0 : res;
  return 0;
}

private void
trap_seq (object trap)
{
  object hunter;
  
  // have to check it each step to avoid confusion if trap is
  // removed from the room while alarm is running.
  if (!present (TRAP_ID, environment()))
    {
      stop_alarm();
      return;
    }
  
  if (!(hunter=trap->query_set_by()))
    {
      tell_room (environment(),
       capitalize(short()) +
		 " obviously ignores the rat trap that is not set.\n");
      stop_alarm();
      return;
    }
  // person setting trap has to be here, not realistic, but avoiding
  // possibility of 'professional' hunters dragging newbies through the
  // quest.
  
  if (!present(hunter, environment()))
      {
	stop_alarm();
	return;
      }
      
  if (step < text_len )
    {
      tell_room (environment(), texts[step]);
      step++;
    }
  else
    {
      trap->disarm_trap();
      stop_alarm();
      if (hunter->resolve_task
	  (TASK_DIFFICULT, ({SS_HUNTING, SS_HUNTING, SS_FR_TRAP})) > 0)
	// about 32% chance of success for players having hunting
	// skill of 50 and no FR_TRAP skill at all.
	// 57% chance of success for player with hunting 50 and
	// FR_TRAPS of 70 (current maximum for Rangers)
	caught(hunter);
      else
	not_caught(hunter);
    }
}

private void
caught(object hunter)
{
  tell_room (environment(), "Another one bites the dust.\n");
  tell_room (environment(),
   "The " + short() + " is caught in skillfully set trap!\n" +
	     "It falls unconsicious right on the place.\n");
  add_adj ("unconsicious");
  remove_name (RAT_ALIVE_ID);
  alive = 0;
  add_stun ();
  remove_prop (OBJ_M_NO_GET);  // player may get it now
  add_prop (RAT_CAUGHT_BY, hunter->query_real_name());
//  WRITE_LOG (hunter, "caught a rat.\n");
}

private void
not_caught(object hunter)
{
  tell_room (environment(),
     "The " + short() + " easily escapes the trap set by such\n" +
         "a clumsy rat trapper as " + QCTNAME(hunter) +  " is.\n");
//  WRITE_LOG (hunter, " failed to catch a rat.\n");
}

void
stop_alarm()
{
  remove_alarm(alarm_id);
  alarm_id = 0;
  step = 0;
}







