/* A generic wagon to be inherited. */
/* By Elessar, March '92 */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
inherit "/d/Gondor/common/lib/friend_or_foe";

int horses,max_horses,livings,max_livings,speed,tour_loop,leavable;
object tour_file,wagon_inside;
string *tour, *retour, goal;
string tourgoal,retourgoal;

make_wagon()
{
  seteuid(getuid(this_object()));
  set_short("@@carriage_short");
  set_pshort("carriages pulled by horses");
  set_long("@@carriage_long");
  add_item(({"horse","horses"}),"@@exa_horses");
  add_prop(OBJ_I_WEIGHT,400000);  /* Well, a wagon is heavy - 400 kg...*/
  add_prop(OBJ_I_VOLUME,400000);  /* Large volume too :) */
  wagon_inside->set_wagonob(this_object());
}

start(int i) 
{
  arrange_tours();
  tell_room(environment(this_object()),"A horse-carriage comes rolling out of the stables.\n");
  call_out("prepare_tour",i);
  return 1;
}

arrange_tours() {
  tour = tour_file->query_tour();
  tourgoal = tour_file->query_tourgoal();
  retour = tour_file->query_retour();
  retourgoal = tour_file->query_retourgoal();
}

init() {
  add_action("enter_wagon","enter");
  add_action("enter_wagon","board");
}

set_tour_file(object obj)
{
  tour_file = obj;
}

set_wagon_inside(object obj)
{
  wagon_inside = obj;
  seteuid(getuid(this_object()));
}

remove_living() {
  livings--;
}

query_horses()
{
  return horses;
}

set_max_horses(int i)
{
  max_horses = i;
}

set_horses(int i)
{
  if (i>max_horses) return 0;
  horses = i;
  adjust_speed();
}

adjust_speed()
{
  speed = max_horses - horses + 1;
}

set_max_livings(int i)
{
  max_livings = i;
}

prepare_tour() {
  goal = tourgoal;
  tell_room(environment(this_object()),
    "The wagon-driver yells: All passengers aboard! The transport to "+goal+" leaves soon!\n");
  tell_room(wagon_inside,"The wagon-driver yells: All passengers aboard! The transport to "+goal+" leaves soon!\n");
  set_leavable(0);
  call_out("tour_move",15,0);
  return 1;
}

turn_back() {
  goal = retourgoal;
  tell_room(environment(this_object()),
    "The wagon-driver yells: All passengers aboard! The transport is returning to "+goal+"!\n");
  tell_room(wagon_inside,"The wagon-driver yells: All passengers aboard! The transport is returning to "+goal+"!\n");
  set_leavable(0);
  call_out("retour_move",15,0);
  return 1;
}

tour_move(int turn)
{
  int maxn,n;
  string *exit_arr;
  exit_arr = environment(this_object())->query_exit();
  maxn = sizeof(exit_arr)/3;
  my_noise(tour[turn]);
  while (n<maxn)
    {
      if (tour[turn] == exit_arr[n*3+1]) {
	this_object()->move(exit_arr[n*3]);
	tell_room(exit_arr[n*3],"A wooden carriage pulled by horses comes rambling in.\n");
      }
      n++;
    }
  if (sizeof(tour)>turn+1) 
    {
      call_out("tour_move",speed,turn+1);
      return 1;
    }
  set_leavable(1);
  tell_room(environment(this_object()),break_string("The wagon-driver yells: The carriage will return to "+retourgoal+" in 1 hour!\n",70));
  tell_room(wagon_inside,break_string("The wagon-driver yells: All right, we have arrived in "+tourgoal+"! The carriage will return to "+retourgoal+" in 1 hour!\n",70));
  call_out("turn_back",120);
  return 1;
}

retour_move(int turn)
{
  int maxn,n,i;
  string *exit_arr;
  my_noise(retour[turn]);
  exit_arr = environment(this_object())->query_exit();
  maxn = sizeof(exit_arr)/3;
  while (n<maxn)
    {
      if (retour[turn] == exit_arr[n*3+1]) {
	this_object()->move(exit_arr[n*3]);
	tell_room(exit_arr[n*3],"A wooden carriage pulled by horses comes rambling in.\n");
      }
      n++;
    }
  if (sizeof(retour)>turn+1)
    {
      call_out("retour_move",speed,turn+1);
      return 1;
    }
  set_leavable(1);
  tell_room(wagon_inside,"The wagon-driver yells: We have arrived in "+retourgoal+"! Everybody out!\n");
  tell_room(environment(this_object()),"The wagon-driver yells: We have arrived in "+retourgoal+"! Everybody out!\n");
  if (tour_loop) call_out("prepare_tour",120);
  else call_out("disassemble",40);
  return 1;
}

set_tour_loop(int i) {
  tour_loop = i;
}

query_tour_loop() {
  return tour_loop;
}

disassemble() 
{
  int n,maxn;
  object *liv_arr;
  tell_room(wagon_inside,"The wagon-driver kicks you out of the wagon, as he is preparing for a new tour.\n");
  maxn = sizeof(all_inventory(wagon_inside));
  liv_arr = all_inventory(wagon_inside);
  while (n<maxn) {
    liv_arr[n]->move_living("out of the wagon",environment(this_object()));
    n++;
  }
  return 1;
}

my_noise(string dir)
{
  tell_room(environment(this_object()),"The wagon whirls up some dust as it passes you on its way "+dir+"wards.\n");
  tell_room(wagon_inside,"The wagon rambles on "+dir+"wards along the road to "+goal+".\n");
  return 1;
}

enter_wagon(str) {
  if (!str) {
    write("Enter what?\n");
    return 1;
    }
  if (str!="wagon" && str!="carriage" && str!="horse carriage") {
    return 0;
    }
if (!horses) {
    write("You should make sure the wagon is started first.\n"+
     "Do 'start' inside the stables, to get the wagon prepared.\n");
    return 1;
    }
  if (query_friend_or_foe(TP)==-1) {
    write("As you try to enter the wagon, the horses pulling it start to\n"+
      "whinny and kick, so eventually give up the attempt.\n");
    say("As "+QCTNAME(TP)+" tries to climb into the wagon, the horses pulling\n"+
      "it start to whinny and kick wildly, until "+TP->query_pronoun()+" gives it up.\n",TP);
    return 1;
    }
  if (M_TIRITH_MASTER->query_enemy(TP->query_real_name(),
      TP->query_race_name())) {
    write("The wagon-driver yells at you: Go away! I won't help enemies of Gondor to enter the White City!\n");
    say("The wagon-driver refuses to help "+QTNAME(TP)+".\n",TP);
    return 1;
  }
  if (livings == max_livings) {
    write("The carriage is full already, there are "+livings+" persons in it!\n");
    say(QCTNAME(this_player())+" tries to enter the horse carriage, but it is full.\n",this_player());
    return 1;
    }
  write("You enter the horse carriage.\n");
  say(QCTNAME(this_player())+" enters the horse carriage.\n",this_player());
  tell_room(wagon_inside,QCTNAME(this_player())+" enters the horse carriage.\n");
  wagon_inside->set_wagonob(this_object());
  this_player()->move_living("into the wagon",wagon_inside);
  livings++;
  return 1;
}

carriage_short()
{
  string short_descf;
  if (horses>1) short_descf = "carriage pulled by "+horses+" horses";
  else if (horses==1) short_descf="carriage pulled by one horse";
  else short_descf = "horse carriage with no horses";
  return short_descf;
}

carriage_long()
{
  string long_descf;
  if (horses>1) long_descf = "This is a wooden horse carriage, currently pulled by "+horses+" horses. ";
  else if (horses==1) long_descf="This is a wooden horse carriage, currently pulled by one horse. ";
  else long_descf = "This is a wooden horse carriage, currently not pulled by any horses. ";
  if (livings) long_descf = long_descf + "Someone is riding in the carriage, but you can't see who. ";
  else long_descf = long_descf + "There's no one in the wagon right now, except the driver. ";
  long_descf = "From a little sign on the side of the carriage, you understand that it runs between Minas Tirith and Edoras.\n";
  return (break_string(long_descf,70));
}

exa_horses()
{
  if (!horses) return "There are no horses pulling the horse-carriage.\n";
  if (horses == 1) return "Before the horse-carriage one strong cart-horse has been put.\n"+
    "It looks to be able to pull the wagon without problem.\n";
  else return "Before the horse-carriage "+horses+" cart-horses have been put.\n"+
    "They look strong and fresh, quite able to pull the wagon, and at\n"+
    "a decent pace too.\n";
}


add_horse()
{
  if (horses+1 <= max_horses) {
    horses++;
    adjust_speed();
    return 1;
  }
  else write("The carriage is already pulled by the maximal number of horses.\n");
  return 1;
}

remove_horse()
{
  if (horses)
    {
      horses--;
      adjust_speed();
      return 1;
    }
  write("There are no horses pulling the carriage!\n");
  return 1;
}

query_leavable()
{
  return leavable;
}

set_leavable(int i)
{
  leavable = i;
}


