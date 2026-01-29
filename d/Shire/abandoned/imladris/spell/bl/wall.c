/*
 * wall.c
 *
 * Base object for elemental walls beetween rooms.
 *
 */

#include "defs.h"

#define MAY_PASS "_temp_checked_may_pass"

inherit EFFECT_OBJECT;

create_object()
{
    TO->create_wall();
}

object this_room;
object other_room;

mixed
init_effect(object spell, object caster, int power)
{
    object targets = spell->query_targets();
    object this_room;
    object other_room;
    int pos;

    pos = member_array(TO, targets);
    this_room = targets[pos];
    other_room = targets[(pos+1)%2];

    wall_exit = spell->query_direction(pos);
    add_adj(exit_dir);

    TO->init_wall_effect();

/*********************************************************
    set_element(ELEMENT_FIRE);
    set_duration(spell->query_spell_class()*5*60);
    set_power(1 + res / 10);
    set_reducible(1);
 *********************************************************/
    return 1;
}

init_wall(object troom, string dir, object oroom, int mast)
{
    spell = previous_object();
    init_effect(spell, spell->query_caster(), spell->query_spell_power());
    this_room = troom;
    wall_dir  = dir;
    other_room = oroom;

.
.
.

}


#define ABBREV_MAP ([ \
    "north" : "n",    \
    "east"  : "e",    \
    "south" : "s",    \
    "west"  : "w",    \
    "northwest" : "nw", \
    "northeast" : "ne", \
    "southeast" : "se", \
    "southwest" : "sw", \
    "up"    : "u",    \
    "down"  : "d"     \
])

string
short_of_direction(string what)
{
    return ABBREV_MAP[what];
}

init()
{
    string short_of;

    ::init();

    if (wall_exit)
	add_action("do_block", wall_exit);

    if (short_of = short_of_dir(wall_exit))
	add_action("do_block", wall_exit);

    if (query_element() == ELEM_EARTH)
	return;

    add_action("do_pass", "go");
    add_action("do_pass", "pass");
    add_action("do_pass", "enter");
    add_action("do_pass", "run");
}

int
do_block(string str)
{
    int dis;

    if (wall_always_try_pass)
	return do_effect(str);

    if (TP->query_prop(ALLOW_PASSING))
    {
	TP->remove_prop(ALLOW_PASSING);
	return 0;
    }

    if (TP->query_npc())
    {
	dis = TP->query_stat(SS_DIS);
	if(random(dis) > 40)
	{
	   do_effect(str);
	   return 0;
	}
	tellem(TP, 0, "(You) would like to pass the "+short()+", but [you] hesitate[s].\n", 1);
	return 1;
    }

    tellem(TP, 0, "(You) would like to pass the "+short()+", but [you] hesitate[s].\n", 1);
    write("If you do dare to pass it, just write: pass <which direction> wall\n");
    return 1;
}

int
do_pass(string str) 
{
    object what;

    notify_fail("Syntax: "+query_verb()+" <which direction> wall\n");

    if (!parse_command(str, ENV(TP), "[through] [in] [into] [the] %o", what))
	return 0;

    if (what != TO)
	return 0;

    do_effect(str);

    TP->add_prop(ALLOW_PASSING, what);
    TP->command(s1);

    return 1;
}


int dispel_magic(int strength) 
{
    if (random(strength) > query_power())
    {
	call_out("dispel_effect",0);
	return 1;
    }
    return 0;
}

void
enter_env(object dest, object old)
{
    tell_room(dest, "Suddenly there appears to be a "+short()+"!\n");
}

void
remove_me()
{
    if (ENV(TO))
	tell_room(ENV(TO), "The "+short()+" fades away and disappears.\n");
}

void
do_call_remove_object()
{
    call_out("remove_object",0);
}

void
leave_env(object old, object dest)
{
    object other;
    if (other = query_wall_other())
    {
	other->set_wall_other(0);
	other->do_call_remove_object();
    }
    remove_me();	
}

string 
stat_object() {
	return ::stat_object() +
		"Wall exit dir........:"+query_wall_exit()+"\n"+
		"Wall effect..........:"+query_wall_effect()+"\n"+
		"Wall other...........:"+
		(query_wall_other() ? file_name(query_wall_other()) : "<nil>")+"\n"+
		"Wall resistance prop.:"+query_wall_res_prop()+"\n"+
		"Wall resistance value:"+query_wall_resistance()+"\n"+
		"Time left............:"+query_time_left()+"\n";
}


















































void   set_wall_exit(string exit)     { wall_exit = exit;   }
string query_wall_exit()              { return wall_exit;   }
void   set_wall_effect(int val)       { wall_effect = val;  }
int    query_wall_effect()            { return wall_effect; }
void   set_wall_other(object oth)     { wall_other = oth;   }
object query_wall_other()             { return wall_other;  }

void   set_wall_resistance(int val)   { wall_resistance = val;  }
int    query_wall_resistance()        { return wall_resistance; }
void   set_wall_res_prop(string val)  { wall_res_prop = val;  }
string query_wall_res_prop()          { return wall_res_prop; }
void   set_wall_type(string type)     { wall_type = type;     }
string query_wall_type()              { return wall_type;     }

void   set_duration(int dur) { call_out("remove_object", dur); }
int    query_time_left() 
{
	return find_call_out("remove_object");
}

mixed
init_wall(object this_room, string exit_dir) 
{
    object other_room;
    int    pos;

    if(!this_room) 
	return "Fatal: Couldn't find environment.\n";

    wall_exit  = exit_dir;

	add_adj(exit_dir);
	add_name("wall to the "+exit_dir);
    move(this_room);

    add_prop(WALL_S_PRESENT, exit_dir);

    pos        = member_array(wall_exit, this_room->query_exit_cmds());
    if(pos==-1)
		return "Fatal: Couldn't find direction.\n";

    other_room = this_room->load_room(pos*3);
    
    pos=member_array(file_name(this_room), other_room->query_exit_rooms());
    if(pos==-1) return; 

    wall_other = CLONE_COPY;
    wall_other -> set_wall_exit(other_room->query_exit_cmds()[pos]);
    wall_other -> set_wall_other(this_object());
    wall_other -> set_wall_effect(query_wall_effect());
    wall_other -> set_wall_res_prop(query_wall_res_prop());
    wall_other -> set_wall_resistance(query_wall_resistance());
    wall_other -> set_wall_type(query_wall_type());

    wall_other -> move(other_room);
}
    
init() {
    ::init();
    if(wall_exit) 
	add_action("do_hesitate",wall_exit);
    if(member_array(wall_exit,
		    ({"north","east","west","south","up","down"}))>=0) 
	add_action("do_hesitate",wall_exit[0..0]);
    add_action("do_pass", "enter");
    add_action("do_pass", "pass");
}

int
do_hesitate(string str)
{
  int dis;

  if(wall_always_try_pass)
    return do_effect(str);

  if(TP->query_prop("_wall_pass")) {
    TP->remove_prop("_wall_pass");
    return 0;
  }

  if(TP->query_npc()) 
    {
      dis = TP->query_stat(SS_DIS);
      if(random(dis) > 40) {
	do_effect(str);
	return 0;
      }
      tellem(TP, 0, "[You] would like to pass the "+short()+", but [you] hesitate[*s].\n", 1);
      return 1;
    }
  tellem(TP, 0, "[You] would like to pass the "+short()+", but [you] hesitate[*s].\n", 1);
  write("If you do dare to pass it, just write: pass <which direction> wall\n");
  return 1;
}

int
do_pass(string str) 
{
  string s1,s2;

  notify_fail("Syntax: "+query_verb()+" <which direction> wall\n");
  if(sscanf(str, "%s %s", s1, s2)!=2)
    return 0;
  if(s2!="wall") 
    return 0;
  if(wall_exit != s1)
    return 0;
  do_effect(str);
  this_player()->add_prop("_wall_pass", s1);
  this_player()->command(s1);
  return 1;
}


int dispel_magic(int strength) 
{
    if(random(strength) > query_wall_resistance()) {
		call_out("remove_object",0);
		return 1;
    }
    return 0;
}

void
enter_env(object dest, object old)
{
    tell_room(dest, "Suddenly there appears to be a "+short()+"!\n");
}

void
remove_me() {
	if(EO) tell_room(EO, "The "+short()+" fades away and disappears.\n");
}

void
do_call_remove_object() {
	call_out("remove_object",0);
}

void
leave_env(object old, object dest)
{
	object other;
	if(other = query_wall_other()) {
		other->set_wall_other(0);
		other->do_call_remove_object();
	}
    remove_me();	
}

string 
stat_object() {
	return ::stat_object() +
		"Wall exit dir........:"+query_wall_exit()+"\n"+
		"Wall effect..........:"+query_wall_effect()+"\n"+
		"Wall other...........:"+
		(query_wall_other() ? file_name(query_wall_other()) : "<nil>")+"\n"+
		"Wall resistance prop.:"+query_wall_res_prop()+"\n"+
		"Wall resistance value:"+query_wall_resistance()+"\n"+
		"Time left............:"+query_time_left()+"\n";
}
