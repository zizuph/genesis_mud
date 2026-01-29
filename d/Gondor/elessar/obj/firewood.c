inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

int burn_time,orig_burn_time,burnt,burnt_down,lit,waslit,cool_ticks;

create_object()
{
  set_name("firewood");
  add_name("wood");
  add_name("campfire");
  set_short("@@short_func");
  set_long("@@long_func");
  set_burn_time(5);
  add_prop(OBJ_I_LIGHT,"@@test_light");
  add_prop(OBJ_I_NO_GET,"@@test_lit");
  add_prop(OBJ_I_WEIGHT,"@@test_weight");
  add_prop(OBJ_I_VOLUME,"@@test_volume");
  add_prop(OBJ_I_VALUE,0);
}

determine_size()
{
  if (orig_burn_time > 625) return "very large";
  if (orig_burn_time > 500) return "large";
  if (orig_burn_time > 375) return "ordinary";
  if (orig_burn_time > 250) return "small";
  if (orig_burn_time > 125) return "tiny";
  else return "pathetic";
}

init()
{
  add_action("light_fire","light");
  add_action("extinguish","extinguish");
  add_action("get_torch","get");
  add_action("get_torch","take");
  add_action("kick_fire","kick");
}

void
update_fire()
{
  object room;
  room = environment(this_object());
  while (!room->query_prop(ROOM_I_IS)) room=environment(room);
  room->update_light();
}

get_torch(string str)
{
  object torch;
  if (!str) 
    {
      notify_fail("Get what?\n");
      return 0;
    }
  if (str != "torch from campfire" && str != "branch from campfire")
    return 0;
  /* Ok, we assume the player actually wanted to get a burning branch
   * from the fire. Now let's give it to him if we can. */
  if (burn_time > 375) 
    {
      /* We declare this campfire big enough to have a real branch to take. */
      seteuid(getuid(this_object()));
      torch = clone_object("/std/torch");
      torch->set_name("branch");
      torch->set_pname("branches");
      torch->set_adj("gnarly");
      torch->set_adj("dry");
      torch->set_long("This dry branch looks like it has fallen from a tree.\n");
      torch->set_strength(1);
      torch->set_time(200);
      torch->add_prop(OBJ_I_WEIGHT,400);
      torch->add_prop(OBJ_I_VOLUME,600);
      if (test_lit()) torch->light_me();
      if (torch->move(TP))
	{
	  write("You can't carry more!\n");
	  say(QCTNAME(TP)+" tries to get a branch from the campfire, but fails.\n",TP);
	  torch->remove_object();
	}
      else 
	{
	  burn_time -= 200;
	  orig_burn_time -= 200;
	  update_fire();
	  if (test_lit()) {
	    write("You get a burning branch from the campfire.\n");
	    say(QCTNAME(TP)+" takes a burning branch from the campfire.\n");
	  }
	  else {
	    write("You get a dry branch from the campfire.\n");
	    say(QCTNAME(TP)+" takes a dry branch from the campfire.\n");
	  }
	}
      return 1;
    }
  write(break_string("There are no branches large enough; the campfire "+
     "consists of only small dry sticks, not suitable for a torch.\n",70));
  return 1;
}
      

test_lit()
{
  if (lit) return 1;
  return 0;
}

int
test_light()
{
  if(!lit) return 0;
  return (burn_time/100 + 1);
}

test_weight()
{
  return burn_time*50/3;
}

test_volume()
{
  return test_weight()*3;
}

short_func()
{
  string shortstr;
  shortstr = determine_size();
  if (burnt_down) return "pile of ashes from an old, "+determine_size()+" campfire";
  if (lit) shortstr = shortstr + ", burning campfire";
  else if (waslit) shortstr = shortstr+", half-burned, extinguished campfire";
  else shortstr = shortstr + " campfire, ready to be set fire to";
  return shortstr;
}

long_func()
{
  string longstr;
  int hrs;
if (!lit && !waslit && !burnt_down) {
  return "This "+determine_size()+" stack of firewood is ready to be lit.\n";
  }
  if (burnt_down) {
    hrs = cool_ticks/60;
    longstr = "This campfire must have been "+determine_size()+", judging by the "+
      "amount of ashes left behind. ";
    if (hrs) longstr = longstr+"By feeling the temperature of the ashes "+
      "you guess that this campfire burned down about "+hrs+" hours ago. ";
    else if (cool_ticks > 45) longstr = longstr+"By feeling the temperature of "+
        "the ashes, you estimate that this campfire burned down less than an hour ago. ";
    else if (cool_ticks > 30) longstr = longstr+"You also find a few live coals left, "+
        "glowing in the ashes. The campfire probably burned down about half an hour ago. ";
    else longstr = longstr+"The glowing pieces of live coals and firewood left amongst "+
        "the ashes makes you understand that this fire burned out quite recently. ";
    return break_string(longstr+"\n",75);
    }
  if (waslit) {
    hrs = cool_ticks/60;
    longstr = "This "+determine_size()+" campfire had burned a while when it was extinguished again. "+
      "By feeling the temperature of the ashes, you guess that ";
    if (hrs) {
      if (hrs>1)
        longstr = longstr+"the campfire was extinguished about "+hrs+" hours ago. ";
      else longstr = longstr+"the campfire was extinguished about an hour ago. ";
      }
    else if (cool_ticks > 45) longstr=longstr+"the campfire burned down less than an hour ago. ";
    else if (cool_ticks > 30) longstr=longstr+"the campfire burned down about half an hour ago. "+
        "The few live coals you find glowing amongst the ashes confirms this. ";
    else longstr = longstr+"the campfire was extinguished quite recently, since you see glowing "+
        "pieces of wood and live coals in the ashes. ";
    return break_string(longstr+"\n",75);
    }
  if (lit) {
    hrs = burn_time/60;
    longstr = "This "+determine_size()+", burning campfire gives both light "+
      "and warmth out here in the open. You guess that it will still burn for ";
    if (hrs>1) longstr=longstr+"about another "+hrs+" hours before it dies out. ";
    else if (hrs==1) longstr=longstr+"about one more hour before it dies out. ";
    else if (burn_time > 45) longstr=longstr+"less than an hour before it dies out. ";
    else if (burn_time > 30) longstr=longstr+"just about half an hour before it dies out. ";
    else longstr=longstr+"a few more minutes before going out. ";
    return break_string(longstr+"\n",75);
    }
}

set_burn_time(int i)
{
  burn_time = i;
  orig_burn_time = burn_time;
  if(lit) update_fire();
}

add_burn_time(int i)
{
  burn_time = burn_time + i;
  if (burn_time - orig_burn_time) orig_burn_time = burn_time;
  if(lit) update_fire();
}

query_burn_time()
{
  return burn_time;
}

query_lit()
{
  return lit;
}

light_fire(string str)
{
  object room;
  if (!str) return 0;
  if (str == "campfire" || str == "firewood" || str == "fire" || str == "wood") {
    if (burnt_down) return 0;
    if (!environment(this_object())->query_prop(ROOM_I_IS))
    {
      NF("You cannot light the firewood you are carrying!\n");
      return 0;
    }
    if(lit)
    {
      NF("But the campfire is already burning!\n");
      return 0;
    }
    write("You light the campfire, and feel the warmth of the fire warm you\n"+
      "and the light from the fire feels as a protection against the wild.\n");
    say(QCTNAME(this_player())+" lights the campfire.\n",this_player());
    call_out("light_tick",1);
    lit = 1;
    waslit = 0;
    add_name("fire");
/* prop _room_has_fire added to the room, Olorin, 14-apr-93 */
    room = environment(this_object());
    while (!room->query_prop(ROOM_I_IS)) room=environment(room);
    room->add_prop("_room_has_fire",1);
    room->add_prop(OBJ_I_HAS_FIRE,1);
    room->update_light();
    return 1;
    }
  return 0;
}

light_tick()
{
  burn_time--;
  if (burn_time == 45) tell_room(environment(this_object()),"The campfire flickers and the heat grows less intense.\n");
  if (burn_time == 30) tell_room(environment(this_object()),"The campfire seems to be burning out soon.\n");
  if (burn_time == 15) tell_room(environment(this_object()),"The campfire grows smaller; it's about to go out.\n");
  if (burn_time == 0) go_out(1);
  if (burn_time) call_out("light_tick",1);
  update_fire();
  return 1;
}

extinguish(string str)
{
  if (!str) return 0;
  if (str=="campfire" || str=="fire") {
    if (burnt_down || waslit) {
      NF("But the campfire is already extinguished!\n");
      return 0;
      }
    if (!lit) {
      NF("But the campfire has not even bin lit yet!\n");
      return 0;
      }
    write("You extinguish the campfire.\n");
    say(QCTNAME(this_player())+" extinguishes the campfire.\n",this_player());
    go_out();
    return 1;
    }
  return 0;
}

kick_fire(string str)
{
  object room;
  if (!str) return 0;
  if (str == "campfire" && lit)
    {
      if (orig_burn_time > 500 && burn_time > 200)
	{
	  write("The campfire is too large to just kick it out.\n"+
		"You will have to extinguish it the normal way.\n");
	  return 1;
	}
      write("You kick the burning campfire, spreading sticks and branches\n"+
	    "around, soon to go out by themselves.\n");
      say(QCTNAME(TP)+" kicks out the campfire, extinguishing it effectively.\n",TP);
      tell_room(environment(this_object()),"Only a sad pile of ashes are left.\n");
      burn_time = 0;
      orig_burn_time = orig_burn_time / 10;
      burnt_down = 1;
      room = environment(this_object());
      if (!room->query_prop(ROOM_I_IS)) room = environment(room);
      room->remove_prop("_room_has_fire");
      room->remove_prop(OBJ_I_HAS_FIRE);
      room->update_light();
      remove_name("firewood");
      remove_name("campfire");
      remove_name("wood");
      add_name("ashes");
      add_name("pile");
      add_name("pile of ashes");
      remove_call_out("light_tick");
      call_out("cool_down",1);
      return 1;
    }
  if (str == "ashes" && burnt_down)
    {
      write("You kick the ashes of the campfire, and spread them to remove the traces.\n");
      say(QCTNAME(TP)+" kicks the ashes of the campfire, spreading them\n"+
	  "to remove the traces.\n",TP);
      blow_away_ashes();
      return 1;
    }
  if ((str == "campfire" || str == "firewood") && !lit)
    {
      write("You kick at the readied campfire, and spread the firewood all around.\n");
      say(QCTNAME(TP)+" kicks at the readied campfire, spreading the firewood all around.\n");
      remove_object();
      return 1;
    }
  return 0;
}

go_out(int i)
{
  object room;
  remove_name("fire");
  if (i) tell_room(environment(this_object()),
    "The flames of the campfire flicker briefly, then goes out, leaving only\n"+
    "a smoking pile of ashes.\n");
  else tell_room(environment(this_object()),
    "The flames of the campfire silently die out, leaving a half-burnt pile\n"+
    "of smoking firewood.\n");
  set_name("old campfire");
  if (i) burnt_down = 1;
  else waslit = 1;
  lit = 0;
/* remove prop _room_has_fire from environment, Olorin, 14-apr-93 */
  room = environment(this_object());
  while (!room->query_prop(ROOM_I_IS)) room=environment(room);
  room->remove_prop("_room_has_fire");
  room->remove_prop(OBJ_I_HAS_FIRE);
  room->update_light();
  remove_name("firewood");
  remove_name("wood");
  add_name("ashes");
  add_name("pile of ashes");
  add_name("pile");
  remove_call_out("light_tick");
  call_out("cool_down",1);
  return 1;
}

cool_down()
{
  cool_ticks++;
  if (cool_ticks > orig_burn_time) blow_away_ashes();
  if (!random(35)) tell_room(environment(this_object()),
    "A sudden gust of wind blows away some of the ashes from the campfire.\n");
  return 1;
}

blow_away_ashes()
{
  tell_room(environment(this_object()),
    "The remaining ashes of the old campfire blows away with the wind.\n");
  remove_object();
  return 1;
}

query_burnt_down()
{
  return burnt_down;
}


