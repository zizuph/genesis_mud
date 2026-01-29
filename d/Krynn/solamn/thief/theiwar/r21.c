/* created by Aridor 04/19/94 */

/* ideas: make a ceramic pot in the furnace
          get fire for furnace going
	     (get coal/wood, light it, pump up the bellows)
	  clean furnace
	  forge sword
	  fill a gap or hole with the metal
	  pour molten lead over some enemies
	  if metal dumped in wrong place, let it seal off an exit (trap)
	      (or intentionally)
	  if metal cooled block a door
	  channel into a forming device to give shape to the metal as it cools
	      (a key)
*/

#include "../local.h"

inherit LIGHTDARKROOM;

#include <language.h>
#include <macros.h>
#include <cmdparse.h>
#define TUBROOM   THEIWAR + "r20"

int *furnace_content = ({ random(1000), random(5000), random(10000) });
object *things       = ({ });
mixed *color         = ({ ({"gold","platinum","mithril"}),
			  ({"silver","copper","bronze"}),
			  ({"iron","metal","steel"}) });
int *lev_st = ({ 0,0,0 }); /* which valves are open? */
int fire_alarm; /* alarm that burns down the fire ;-) */
int fuel_ready_to_light = 21;
int flow_alrm; /* alarm that controls flow */

/* prototypes */
int switch_lever(string str);
int query_time_to_burn_left();
int do_add_to_fire(object obj);

void
start_fire()
{
    tell_room(TO,"A sweaty bearded dwarf arrives.\nThe sweaty bearded dwarf " +
	      "lights the fire in the furnace.\nThe sweaty bearded dwarf " +
	      "leaves.\n");
    fire_alarm = set_alarm(itof(1500 + random(4000)),0.0,"burn_fire_out");
    LIGHT;
}

void
reset_ld_room()
{
    int i;
    if (random(2) && !fire_alarm)
      start_fire();
    i = random(1000);
    if (i > furnace_content[0])
      furnace_content[0] = i;
    i = random(5000);
    if (i > furnace_content[1])
      furnace_content[1] = i;
    i = random(10000);
    if (i > furnace_content[2])
      furnace_content[2] = i;
    
}

void
create_ld_room()
{
    set_short("In a cavern");
    set_long("This is a hot room with light coming out of the east wall, " +
	     "and several exits leading off into the other parts of the " +
	     "mountain. Towards the southwest, an ordinary hallway seems " +
	     "to lead to some living area, to the northwest another cavern " +
	     "continues, this one seems to lead into another work area, " +
	     "whereas the north and south exits seem to lead to some kind " +
	     "of shops.\n");
    
    add_item(({"light","fire","wall","furnace"}),
	     "The fire in the east wall is visible through a hole " +
	     "right at the floor. @@fire_state@@It appears to be " +
	     "some kind of furnace, " +
	     "used for melting metals. In another hole, at about " +
	     "@@which_height@@ level, you can see glowing liquid. You could " +
	     "easily throw something into that hole. " +
	     "On the same wall, near the " +
	     "south exit, you can see three levers protruding from the " +
	     "wall.\n");
    add_item(({"lever","levers"}),"@@show_lever_states@@");
    add_item(({"another hole","other hole","second hole","liquid",
		 "glowing liquid","metals"}), "@@show_liquid_states@@");
    add_item(({"hole","fuel","floor"}),
	     "The fire in the east wall is visible through a hole right at " +
	     "the floor. @@fire_state@@\n");
    
    add_exit(THEIWAR + "r22", "north");
    add_exit(THEIWAR + "r23", "northwest");
    add_exit(THEIWAR + "r19", "southwest");
    add_exit(THEIWAR + "r20", "south");
    
    set_alarm(1.0,0.0,"start_fire");
}

void
init()
{
    ::init();
    ADD("switch_lever","move");
    ADD("switch_lever","push");
    ADD("switch_lever","pull");
    ADD("switch_lever","switch");
    /*ADD("switch_lever","throw"); this is handled by throw_into_furnace, too*/
    ADD("throw_into_furnace","throw");
    ADD("throw_into_furnace","put");
    ADD("add_fuel_to_fire","add");
    ADD("light_the_fire","light");
}

string
show_liquid_states()
{
    string how;
    string str = ("You can see three small tubs inside the furnace, each " +
		  "contains some glowing liquid.");
    int i;
    for(i=0;i<sizeof(furnace_content);i++)
      {
	  if (furnace_content[i] > 20000)
	    how = "about full";
	  else if (furnace_content[i] > 19000)
	    how = "almost full";
	  else if (furnace_content[i] > 10000)
	    how = "about half full";
	  else if (furnace_content[i] > 1000)
	    how = "partly full";
	  else if (furnace_content[i] > 100)
	    how = "almost empty";
	  else
	    how = "practically empty";
	  str += " The " + LANG_WORD(i+1) + " small tub is " + how +
	    " and " + color[i][0] + " seems to be in it.";
      }
    return str + "\n";
}

string
fire_state()
{
    int f_st = query_time_to_burn_left();
    if (f_st > 3000)
      return "You are certain there is still enough fuel left for a very " +
	"long time. ";
    else if (f_st > 1000)
      return "You are sure there is still enough fuel left for quite " +
	"some time. ";
    else if (f_st > 500)
      return "You are sure there is still enough fuel left for a while. ";
    else if (f_st > 200)
      return "You think the fuel will not last for a long time any more. New fuel should be added soon. ";
    else if (f_st > 100)
      return "You assume the fire is likely to go out sometime soon. New fuel should be added soon. ";
    else if (f_st > 50)
      return "You think the fuel is practically used up now. New fuel should be added soon. ";
    else if (f_st > 0)
      return "You are certain the fire will go out any second now. New fuel should be added soon. ";
    else
      return "The fire seems to have gone out recently. New fuel needs to be added before it can be lit again. ";
}

string
which_height()
{
    int sze = TP->query_prop(CONT_I_HEIGHT);
    if (sze > 220)
      return "knee";
    if (sze > 150)
      return "waist";
    if (sze > 100)
      return "chest";
    return "head";
}

int
contains_some_metal(string *met, object what)
{
    int i,j;
    string *to_check = what->query_adjs();
    string str1, str2;
    if (what->query_names())
      if (to_check)
	to_check += what->query_names();
      else
	to_check = what->query_names();
    for(i=0;i<sizeof(to_check);i++)
      for(j=0;j<sizeof(met);j++)
	if (sscanf(L(to_check[i]),"%s" + met[j] + "%s", str1, str2) == 2)
	  return 1;
    if (met == color[2] && what->check_weapon())
      return 1;
    return 0;
}

/* we have double functionality on throw here... if the player
 * didn't want to throw the lever, maybe s/he wants to throw
 * something into the furnace?
 */
int
throw_into_furnace(string str)
{
    object *objs, obj;
    int i, done = 0;
    string what, dummy;
    NF("Throw what?\n");
    if (!str)
      if (query_verb() == "put")
	return 0;
      else
	return switch_lever(str);

    NF("Throw what where?\n");
    if (sscanf(str, "%s in%sfurnace", what, dummy) < 2)
      if (sscanf(str, "%s in%shole", what, dummy) < 2)
	if (query_verb() == "put")
	  return 0;
	else
	  return switch_lever(str);

    NF("You don't have the " + what + " to throw away.\n");
    obj = P(what, TP);
    if (!obj)
	return 0;
    
    if (obj->move("/d/Krynn/common/void"))
      return 0;

    write("You throw " + LANG_ASHORT(obj) + " into the furnace.\n");
    say(QCTNAME(TP) + " throws something into the furnace.\n");
    /* without a fire, the object won't melt. all 'things' will be melted
       once the fire is hot again. */
    if (!fire_alarm)
      things += ({ obj });
    else
      {
	  for(i=0;i<sizeof(color);i++)
	    if (!done && contains_some_metal(color[i], obj))
	      {
		  furnace_content[i] += obj->query_prop(OBJ_I_WEIGHT);
		  done = 1;
	      }
	  if (!done)
	    {
		do_add_to_fire(obj);
		write("Since it does not contain metal it just adds to the " +
		      "fire burning in there.\n");
	    }
	  else
	    write("You watch it melt slowly into a pool of metal.\n");
      }

    set_alarm(12.0,0.0,"check_if_something_flows_out");
    return 1;
}

string
show_lever_states()
{
    string *txtup = ({ }), *txtdwn = ({ });
    string txt = "You can count " + sizeof(lev_st) + " levers here. ";
    int i,j = 0;
    
    for(i=0;i<sizeof(lev_st);i++)
      {
	  j += lev_st[i];
	  if (lev_st[i])
	    txtup += ({ LANG_WORD(i+1) });
	  else
	    txtdwn += ({ LANG_WORD(i+1) });
      }
    if (j == sizeof(lev_st))
      txt += "All levers are currently pointing upwards.";
    else if (j == 0)
      txt += "All levers are currently pointing downwards.";
    else
      {
	  txt += "The " + txtup[0];
	  for(i = 1;i<sizeof(txtup)-1;i++)
	    txt += ", " + txtup[i];
	  if (sizeof(txtup) > 1)
	    txt += " and " + txtup[sizeof(txtup)-1];
	  txt += " lever is currently pointing upwards. ";
	  txt += "The " + txtdwn[0];
	  for(i = 1;i<sizeof(txtdwn)-1;i++)
	    txt += ", " + txtdwn[i];
	  if (sizeof(txtdwn) > 1)
	  txt += " and " + txtdwn[sizeof(txtdwn)-1];
	  txt += " lever is currently pointing downwards.";
      }
    return txt + "\n";
}

int
switch_lever(string str)
{
    string which, where;
    int i, num;
    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;
    if (str == "lever")
      {
	  NF("Throw which lever?\n");
	  return 0;
      }
    i = sscanf(str,"%s lever%s", which, where);
    if (i < 1)
      {
	  i = sscanf(str,"lever %d%s", num, where);
	  if (i < 1)
	    return 0;
      }
    else
      num = LANG_ORDW(which);
    if (num < 1 || num > sizeof(lev_st))
      return 0;
    num--;
    NF("The lever is already in that position.\n");
    if (i == 2)
      {
	  if (lev_st[num] && (where == " up" || where == " upwards"))
	    return 0;
	  if (!lev_st[num] && (where == " down" || where == " downwards"))
	    return 0;
      }
    lev_st[num] = !lev_st[num];
    which = LANG_WORD(num+1);
    where = (lev_st[num] ? "up" : "down");
    write("You throw the " + which + " lever " + where + "wards.\n");
    say(QCTNAME(TP) + " throws the " + which + " lever " + where + "wards.\n");
    set_alarm(5.0,0.0,"check_if_something_flows_out");
    return 1;
}


void
check_if_something_flows_out()
{
    int i,num_open = 0;
    for(i=0;i<sizeof(lev_st);i++)
      num_open += lev_st[i];
    
    if (num_open == 0)
      {
	  if (flow_alrm)
	    remove_alarm(flow_alrm);
	  flow_alrm = 0;
	  return;
      }
    else if (query_time_to_burn_left() < 400) 
      /* the fire is not hot enough anymore */
      return;
    else if (!flow_alrm)
      flow_alrm = set_alarm(1.0,5.0,"do_flow_out");
    /* don't do anything new if the alarm is already on! */
}

do_flow_out()
{
    int i, how_much, can_remove_alarm = 1;
    tell_room(TO,"You can hear something rushing and bubbling inside " +
	      "the east wall.\n");
    
    for(i=0;i<sizeof(lev_st);i++)
      {
	  if (lev_st[i])
	    {
		how_much = (furnace_content[i] > 500 ? 500 : furnace_content[i]);
		(TUBROOM)->fill_tub(how_much, color[i][0]);
		furnace_content[i] -= how_much;
		/* if there's still anything left that can flow out, do it */
		if (furnace_content[i] > 0)
		  can_remove_alarm &= 0;
	    }
      }
    if (can_remove_alarm)
      {
	  remove_alarm(flow_alrm);
	  flow_alrm = 0;
      }
}

void
do_add_to_fire(object obj)
{
    int fuel;
    if (fire_alarm)
      {
	  fuel = query_time_to_burn_left();
	  fuel += (obj->query_prop(OBJ_I_VOLUME) +
		   obj->query_prop(OBJ_I_WEIGHT));
	  remove_alarm(fire_alarm);
	  fire_alarm = set_alarm(itof(fuel),0.0,"burn_fire_out");
      }
    else
      fuel_ready_to_light += (obj->query_prop(OBJ_I_VOLUME) +
			      obj->query_prop(OBJ_I_WEIGHT));
}


int
add_fuel_to_fire(string str)
{
    object ob, *objs;
    NF(C(query_verb()) + " what?\n");
    if (!str)
      return 0;
    objs = FIND_STR_IN_OBJECT(str,TP);
    if (!objs || !sizeof(objs))
      return 0;
    ob = objs[0];
    if (ob->move(E(TP)))
      return 0;
    do_add_to_fire(ob);
    write("You add the " + ob->short() + " to the fuel for the furnace.\n");
    say(QCTNAME(TP) + " adds " + LANG_ASHORT(ob) + " to the fuel for " +
	"the furnace.\n");
    ob->remove_object();
    return 1;
}

int
light_the_fire(string str)
{
    /*only works if the fire is out.*/
    NF("Light what?\n");
    if (!str)
      return 0;
    if (str != "fire" && str != "fuel")
      return 0;
    
    LIGHT;
    write("You light the fire under the furnace.\n");
    say(QCTNAME(TP) + " lights the fire under the furnace.\n");
    fire_alarm = set_alarm(itof(fuel_ready_to_light),0.0,"burn_fire_out");
    fuel_ready_to_light = 21;
    set_alarm(20.0,0.0,"melt_things_inside");
    return 1;
}

void
burn_fire_out()
{
    tell_room(TO,"The fire under the furnace flickers, then goes out.\n");
    if (gate_closed)
      DARK;
    fire_alarm = 0;
}

int
query_time_to_burn_left()
{
    mixed *calls;
    if (!fire_alarm)
      return 0;
    calls = get_alarm(fire_alarm);
    return ftoi(calls[2]); /*time till the alarm is executed*/
}

void
melt_things_inside()
{
    int i,j, done;
    if (!fire_alarm)
      return;
    for(j=0;j<sizeof(things);j++)
      {
	  done = 0;
	  for(i=0;i<sizeof(color);i++)
	    if (!done && contains_some_metal(color[i], things[j]))
	      {
		  furnace_content[i] += things[j]->query_prop(OBJ_I_WEIGHT);
		  done = 1;
	      }
	  if (!done)
	    do_add_to_fire(things[j]);
      }
    things = ({ });
}

/* Darkness only when no fire is burning */
void
make_dark()
{
    if (query_time_to_burn_left() <= 0)
      ::make_dark();
}
