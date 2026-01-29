inherit "/std/food";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>


object thrown_by, thrown_at, thrown_in;
string *colors = ({"red","orange","yellow","green","blue","violet",
	"white","pink","grey","black","purple"});
string *tastes = ({"rum","cherries","apples","oranges","caviar",
	"salmon","cheese (buerk!)","dust","chocolate","vanilla"});

string color,taste;
string wishes;
string sender;

create_food()
{
    color = colors[random(sizeof(colors))];
    taste = tastes[random(sizeof(tastes))];
    wishes = "Happy New Year!";
    set_name("pig");
    set_adj(({"marzipan",color}));
    set_long(break_string("This is a little, " + color + " pig made of sweet " +
	"marzipan, a gift from the wizards of Dville and Terel to " +
	"all players of Genesis with the best wishes for " +
	"1993! You can eat it, or throw it at anybody you like. " +
	"Before throwing, you can stick a message to the pig with " +
	"the 'pigwish Happy New Year' command (or whatever text " +
	"you like after pigwish ;--)\n",70));
    set_amount(300);
}


eat_it(string str)
{
    int result;

    notify_fail("Eat what?\n");
    if (str != "pig" && str != "all") return 0;
    write("As you slay the poor little pig it screams.... SQUEAK!\n");
    say("As " + QCTNAME(this_player()) + 
	" slays the poor little pig it screams.... SQUEAK!\n");
    result = ::eat_it(str);
    if (result)
    {
	write("It tastes like " + taste + ". Hmmm... delicious!\n");
    }
    return(result);
}



pigwish(string str)
{
    wishes = str;
    return 1;
}


init()
{
  ::init();
  if (find_call_out("hit_victim") == -1)
  {
    add_action("do_throw", "throw");
  }
  else add_action("do_duck", "duck");
  add_action("pigwish","pigwish");
}

do_duck(str)
{
  object victim;
  string body_part_hit, msg;

  if (str) return 0;
  if (!random(4))
  {
    write("You try to evade the " + color + " marzipan pig but fail miserably...\n");
    say(QCTNAME(this_player()) + " tries in vain to evade the " + color + 
	" marzipan pig.\n");
    return 1;
  }
  remove_call_out("hit_victim");
  msg = "The " + color + " marzipan pig hits ";
  victim = get_new_victim();
  if (victim)
  {
    body_part_hit = get_body_part_hit();
    msg += QTNAME(victim) + " " + body_part_hit;
    this_player()->catch_msg("You duck.\n" + msg + "!\n");
    say(QCTNAME(this_player()) + " ducks.\n" + msg + "!\n", ({this_player(),
      victim}));
    victim->catch_msg(QCTNAME(this_player()) + " ducks and you are hit by "
     +"the " + color + " marzipan pig.\n" +
	"It tastes like " + taste + ". Mmmm... it is delicious.\n");
  }
  else
  {
    msg += "the wall";
    this_player()->catch_msg("You duck.\n" + msg + ".\n");
    say(QCTNAME(this_player()) + " ducks.\n" + msg + ".\n");
  }
  remove_object();
  return 1;
}

do_throw(string str)
{
  object *obs;
  string cake, victim;
  int i;

  sender = this_player()->query_name();
  notify_fail("Throw what at who?\n");
  if (!str) return 0;
  if (sscanf(str, "%s at %s", cake, victim) != 2) return 0;
  obs = FIND_STR_IN_OBJECT(cake, this_player());
  if (!obs || !sizeof(obs) || obs[0] != this_object()) return 0;
  notify_fail("Throw " + cake + " at who?\n");
  obs = FIND_STR_IN_OBJECT(victim, environment(this_player()));
  if (!obs || !sizeof(obs)) return 0;
  if (sizeof(obs) > 1)
  {
    notify_fail("Throw just one " + cake + " at several players???\n");
    return 0;
  }
  if (obs[0] == this_player())
  {
    notify_fail("You must be kidding.\n");
    return 0;
  }
  this_player()->catch_msg("You throw your " + color + " marzipan pig at " + QTNAME(obs[0]) + ".\n");
  say(QCTNAME(this_player()) + " throws a " + color + " marzipan pig at " + QTNAME(obs[0]) + "!\n",
    ({ this_player(), obs[0]}));
  obs[0]->catch_msg("A " + color + " marzipan pig comes flying towards you!!!\n");
  thrown_by = this_player();
  thrown_at = obs[0];
  thrown_in = environment(thrown_by);
  call_out("hit_victim", random(8) + 2);
  move(obs[0]);
  return 1;
}

get_new_victim()
{
  object *obs;

  obs = all_inventory(environment(this_player()));
  obs = filter(obs, "get_new_victim_filter", this_object());
  if (!obs || !sizeof(obs)) return 0;
  return obs[random(sizeof(obs))];
}

get_new_victim_filter(obj)
{
  if (obj != thrown_at && obj != thrown_by && living(obj)) return 1;
  return 0;
}

get_body_part_hit()
{
  switch (random(6))
  {
    case 0: return "right in the face";
    case 1: return "on the head";
    case 2: return "on the cheeks";
    case 3: return "on the arms";
    case 4: return "in the stomach";
    case 5: return "on the side";
  }
}

hit_victim()
{
  string body_part_hit;

  if (!thrown_in) return;
  if (!thrown_at || !present(thrown_at, thrown_in))
  {
    tell_room(thrown_in, "The " + color + " marzipan pig hits the wall.\n");
    return;
  }
  body_part_hit = get_body_part_hit();
  set_this_player(thrown_at);
  write("The " + color + " marzipan pig hits you " + body_part_hit + 
	"!\nIt tastes like " + taste + ". Mmmm... it is delicious.\n" +
	break_string("A message from " + sender + 
		" sticking on the pig says : '" + 
		wishes + "'\n",70));
  say(QCTNAME(thrown_at) + " is hit " + body_part_hit + " by the " 
	+ color + " marzipan pig!\n");
  remove_object();
  return 1;
}
