/* river.c - to inherit if you want to make a river with a current. 
 * Elessar, Jan'94.
 */

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/time.h"
#define LIVE_I_SWIM_HERE "_live_i_swim_here"
#define LOG_FILE LOG_DIR+"drown"
string rivertype, landname, cur_dir, up_dir, *shore, rivername,extraline;
int cur_str;

string roomobj(string cdir);
int downstream(object obj, int fat, int swim);
int upstream(object obj, int fat);
int decr_hp(object pl, int fati);

string convert_dir(string dir)
{
  switch(dir) {
  case "n":
    return "north"; break;
  case "ne":
    return "northeast"; break;
  case "e":
    return "east"; break;
  case "se":
    return "southeast"; break;
  case "s":
    return "south"; break;
  case "sw":
    return "southwest"; break;
  case "w":
    return "west"; break;
  case "nw":
    return "northwest"; break;
  case "u":
    return "up"; break;
  case "d":
    return "down"; break;
  default:
    return dir; break;
  }
}

int query_exit_fatigue(string dir)
{
  int i;
  mixed *exit_arr;
  exit_arr = query_exit();
  while (i<sizeof(exit_arr)/3) {
    if (dir == exit_arr[i*3+1]) return exit_arr[i*3+2];
    i++;
    }
  return 0;
}

int exist_dir(string dir)
{
  mixed *exit_arr;
  int i;
  exit_arr = query_exit();
  while (i<sizeof(exit_arr)/3) {
    if (dir == exit_arr[i*3+1]) return 1;
    i++;
    }
  return 0;
}

int do_drown(object pl)
{
  pl->catch_msg("You drowned!\n"); /* To be implemented */
  write_file(LOG_FILE,pl->query_name()+" ("+pl->query_avg_stat()+
    ") drowned in the river "+rivername+", on "+ctime(time())+".\n");
  write_file(LOG_FILE,"   Swim skill: "+pl->query_skill(SS_SWIM)+", "+
    " and the current was "+cur_str+" strong.\n");
  return 1;
}

int can_swim(string dir, object pl)
{
  int cs, ss, fl;
  ss = pl->query_skill(SS_SWIM);
  if (dir == cur_dir) { fl = cur_str/10 - ss/10; cs = cur_str-10; }
  else if (dir == up_dir) { fl = cur_str/4 - ss/6; cs = cur_str+10; }
  else { cs = cur_str; fl = cur_str/4 - ss/5; }
  if (fl < 5) fl = 5;
  if (cs > ss) return 0;
  else if (fl > pl->query_fatigue()) { decr_hp(pl,fl); return -1; }
  pl->add_fatigue(-fl);
  return 1;
}

int try_swim(object pl, string dir)
{
  string txt;
  string room;
  int i;
  i = can_swim(dir,pl);
  if (i > 0) {
    room = roomobj(dir);
    if (member_array(dir,shore)>0) {
      write("You swim "+dir+", and manage to climb ashore.\n");
      tell_room(room,QCNAME(pl)+" comes swimming, and climbs out of the water,\n"+
        "dripping wet.\n",pl);
    }
    else {
      write("You swim further "+dir+".\n");
      tell_room(room,QCNAME(pl)+" comes swimming.\n",pl);
    }
    pl->move(room);
    return 1;
  }
  else if (i == 0) txt ="The current proves too strong for you,";
  else txt = "You are too tired to resist the pull of the current,";
  write(BS(txt+" and you are washed away downstream.\n"));
  downstream(pl,query_exit_fatigue(dir),0);
  return 1;
}

int query_float(object obj)
{
  if (obj->query_prop(OBJ_I_WEIGHT) < obj->query_prop(OBJ_I_VOLUME)) return 1;
  return 0;
}

string roomobj(string cdir)
{
  int n;
  string *exit_arr;
  exit_arr = TO->query_exit();
  while (n<sizeof(exit_arr)/3) {
    if (exit_arr[n*3+1]==cdir)
    return exit_arr[n*3];
    n +=1;
  }
}

string cur_adj(int cs)
{
  cs = cs/10;
  switch(cs)
  {
    case 0:
      return "stagnant"; break;
    case 1:
      return "quiet"; break;
    case 2:
      return "calm"; break;
    case 3:
      return "gentle"; break;
    case 4:
      return "meandering"; break;
    case 5:
      return "swift"; break;
    case 6:
      return "rough"; break;
    case 7:
      return "rushing"; break;
    case 8:
      return "rapid"; break;
    case 9:
      return "wild"; break;
    case 10:
      return "torrential"; break;
    default:
      return "ferocious"; break;
  }
}

int do_swim(string dir)
{
  if (!dir && query_verb()!= "swim") dir = query_verb();
  if (!dir || dir == "here") {
    TP->add_prop(LIVE_I_SWIM_HERE,1);
    write("You start swimming in attempt to stay against the "+cur_adj(cur_str)+" current.\n");
    say(QCTNAME(TP)+" starts swimming not to get washed away by the current.\n",TP);
    return 1;
    }
  dir = convert_dir(dir);
  if (!exist_dir(dir)) { write("It is impossible to swim in that direction!|n"); return 1; }
  if (dir == cur_dir) downstream(TP,query_exit_fatigue(dir),1);
  if (dir == up_dir) upstream(TP,query_exit_fatigue(dir));
  else try_swim(TP,dir);
  return 1;
}

string short_func()
{
  return "In a "+cur_adj(cur_str)+" part of the "+rivertype+" "+rivername;
}

string describe()
{
  string txt;
  int i;
  txt = "The current in the "+rivertype+" is "+cur_adj(cur_str)+" here, continuing "+
    cur_dir+" through "+landname+". ";
  if (sizeof(shore)>0) {
    txt = txt + "To the ";
    if (sizeof(shore)==1) txt = txt+shore[0]+" is the shore. ";
    else {
      while (i<sizeof(shore)-1) { txt = txt+shore[i]+" and "; i++; }
      txt = txt+" is the shore. ";
      }
    }
  if (extraline) return BS(txt+extraline+"\n");
  else return BS(txt+"\n");
}

void make_the_room()
{
  set_short("@@short_func@@");
  set_long("@@describe@@");
  set_noshow_obvious(1);
  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
}

void init()
{
  ::init();
  add_action("do_swim","swim");
}

void enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
    if (living(obj)) call_out("current",110-cur_str,obj);
    else if (obj->query_boat()) call_out("boat_current",110-cur_str,obj);
    else if (query_float(obj)) call_out("object_current",110-cur_str,obj);
}

int current(object obj)
{
  int fat,swimskill;
  if (ENV(obj) != TO) return 1;
  swimskill = obj->query_skill(SS_SWIM);
  fat = cur_str/5 - swimskill/5;
  if (fat < cur_str/10) fat = cur_str/10; 
  if (obj->query_prop(LIVE_I_SWIM_HERE))
    {
      if (obj->query_fatigue() < fat)
	{
        obj->catch_msg("You are too fatigued to keep swimming against the current.\n");
	  downstream(obj,fat,0);
	  return 1;
	}
      obj->add_fatigue(-fat);
      obj->catch_msg("You continue swimming to keep up with the current.\n");
      tell_room(TO,QCTNAME(obj)+" swims to keep up with the current.\n",obj);
      return 1;
    }
  downstream(obj,fat,0);
  return 1;
}

int decr_hp(object pl, int fati)
{
  pl->set_hp(-(fati*2));
  pl->catch_msg("You swallow some water and feel that you are drowning!\n");
  tell_room(TO,QCTNAME(pl)+" is coughing and sputtering water!\n",pl);
  if (pl->query_hp() < 0) { do_drown(pl); return 1; }
  return 0;
}

int downstream(object pl, int fati, int swim)
{
  int dead;
  if (pl->query_fatigue() < fati)
    dead = decr_hp(pl, fati);
  else pl->add_fatigue(-fati);
  if (dead) return 1; /* If player drowned, stop further swimming :) */
  if (!swim) pl->catch_msg("You are drawn with the current "+cur_dir+".\n");
  else pl->catch_msg("You swim with the current "+cur_dir+".\n");
  tell_room(roomobj(cur_dir),QCTNAME(pl)+" comes floating down the "+rivertype
	    +".\n");
  pl->move(roomobj(cur_dir));
  return 1;
}

int upstream(object pl, int fati)
{
  pl->add_fatigue(-fati);
  pl->catch_msg("You swim up the "+rivertype+" against the "+cur_adj(cur_str)+
    " current, "+up_dir+"wards.\n");
  say(QCTNAME(pl)+" swims away "+up_dir+" against the "+cur_adj(cur_str)+
    " current.\n");
  tell_room(roomobj(up_dir),QCNAME(pl)+" comes swimming against the current.\n");
  pl->move(roomobj(up_dir));
  return 1;
}

int query_cur_str()
{ return cur_str; }

string query_cur_dir()
{ return cur_dir; }

string query_up_dir()
{ return up_dir; }

