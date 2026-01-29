/* The watchdog to avoid in the Reveal Spy quest.
 * Must be given drugged food, or else it will attack.
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD  0
#define H_BODY  1
#define TO this_object()
#define TP this_player()

int awake, suspicious;
object player;

void
create_creature()
{
  if (!IS_CLONE) return;
  set_living_name("dog");
  set_name("watch-dog");
  add_name("dog");
  add_name("awake_dog");
  set_race_name("dog");
  set_short("dangerous watch-dog");
  set_pshort("dangerous watch-dogs");
  set_adj("dangerous");
  set_long("This watch-dog looks frightening, as it is obviously trained to attack\n"+
    "and kill intruders. Its gleaming eyes stare hungrily at you.\n");
  set_stats(({ 9,30,30,7,7,90}));
  set_hp(625);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_UNARM_COMBAT, 55);
  set_skill(SS_PARRY, 15);
  set_attack_unarmed(A_BITE, 35, 30, W_SLASH,  70, "bite");
  set_attack_unarmed(A_LCLAW,30, 18, W_SLASH,  15, "left claws");
  set_attack_unarmed(A_RCLAW,30, 18, W_SLASH,  15, "right claws");
  set_hitloc_unarmed(H_HEAD, ({ 5, 5, 5, 5 }), 20, "head");
  set_hitloc_unarmed(H_BODY, ({ 10,10,10,10}), 80, "body");
  set_cact_time(7);
  add_cact("do_bark");
  add_cact("growl");
  awake = 1;
}

int
check_att()
{
  string time;
  if (TP->query_invis()) return 0;
  if (TO->query_attack()) return 0;
  if (TP->query_skill(SS_ANI_HANDL) < 15) {
    call_out("do_fight",4,TP);
    return 1;
  }
  time = find_object("/d/Gondor/elessar/lib/clock")->query_time_of_day();
  if (time == "night" || time == "early morning") {
    if (TP->query_skill(SS_ANI_HANDL) < 40) {
      call_out("do_fight",4,TP);
      return 1;
    }
  }
  call_out("accepted",4,TP);
  return 1;
}

void
init_living()
{
  if (awake) check_att();
  add_action("do_pat","pat");
}

int
do_fight(object player)
{
  if (!player) return 0;
  write("The watch-dog doesn't like you! It attacks!\n");
  say("The watch-dog growls ferociously as it eyes "+QTNAME(player)+", and attacks!\n",player);
  command("kill "+player->query_real_name());
  return 1;
}

int
suspicious(object player)
{
  if (!player) return 0;
  write("The watch-dog looks suspiciously at you, and silently awaits\n"+
	"your next move.\n");
  say("The watch-dog stares suspiciously at "+QTNAME(player)+",\n"+
      "but stays quiet, awaiting "+player->query_possessive()+" next move.\n",player);
  suspicious = 1;
  return 1;
}

int
accepted(object player)
{
  if (!player) return 0;
  write("The watch-dog looks at you with large eyes, enjoying your attention.\n");
  say("The watch-dog looks at "+QTNAME(player)+", and seems to like "+
    player->query_objective()+"!\n",player);
  command("lick "+player->query_real_name());
  suspicious = 0;
  return 1;
}

int
do_pat(string str)
{
  if (!str) return 0;
  if (str == "dog" || str =="watch-dog" || str=="watchdog" || str=="watch dog") {
    write("You charmantly pat the large watch-dog on the head to befriend it.\n");
    say(QCTNAME(TP)+" charmantly pats the dog on its head, trying to befriend it.\n",TP);
    if (!awake) {
      write("The dog is sleeping heavily, as it has been drugged.\n");
      return 1;
    }
    if (TO->query_attack()) {
      write("The dog, which was fighting, notices you, and attacks you instead!\n");
      command("kill "+TP->query_real_name());
      return 1;
    }
    if (suspicious) {
      if (TP->query_skill(SS_ANI_HANDL) > 50) accepted(TP);
      else do_fight(TP);
      return 1;
    }
    write("The dog licks your hand.\n");
    return 1;
  }
}

int
do_bark()
{
  say("The watch-dog barks noisily!\n");
  if (random(100) > 20) call_out("summon_guards",10);
  return 1;
}

int
summon_guards()
{
  object guard;
  seteuid(getuid(TO));
  guard = clone_object("/d/Gondor/minas/npc/cguard");
  guard->move_living("X",environment(TO));
  say("Two cityguards arrive to check out the commotion.\n");
  guard->init_command("kill "+TO->query_attack()->query_real_name());
  guard = clone_object("/d/Gondor/minas/npc/cguard");
  guard->move_living("X",environment(TO));
  guard->command("kill "+TO->query_attack()->query_real_name());
  return 1;
}

int
is_food(object obj)
{
  if (!obj) return 0;
  if (function_exists("create_object",obj) == "/std/food")
    return 1;
  return 0;
}

void
enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);
  if (is_food(obj)) {
    if (awake) {
      if (present("drugged food",TO)==obj) call_out("get_sleepy",15);
      command("eat "+obj->query_name());
      command("lick "+from->query_real_name());
    }
  }
}

int
get_sleepy()
{
  set_aggressive(0);
  tell_room(environment(TO),"The watch-dog looks rather sleepy, and sits down to rest.\n");
  call_out("get_drugged",15);
  return 1;
}

int
get_drugged()
{
  tell_room(environment(TO),"The watch-dog trips over and falls asleep.\n");
  TO->query_attack()->stop_fight();
  TO->stop_fight();
  awake = 0;
  set_aggressive(0);
  call_out("wake_up",300);
  return 1;
}

int
wake_up()
{
  tell_room(environment(TO),"The watch-dog wakes up from its drugged sleep.\n");
  awake = 1;
  set_aggressive(1);
  return 1;
}

int
query_awake()
{
  return awake;
}

void
set_awake(int i)
{
  if (i) awake = 1;
  else awake = 0;
}
