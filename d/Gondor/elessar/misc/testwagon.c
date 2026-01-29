/* A wagon to run between Edoras and Minas Tirith */
/* By Elessar, March '92 */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#define WAGON_INSIDE "/d/Gondor/elessar/misc/transport/inwagon"
#define TOUR_FILE "/d/Gondor/elessar/lib/tour_file"

int horses,max_horses,livings,max_livings,speed,leavable;
string *tour, *retour;
string goal;

create_object()
{
  set_name("wagon");
  add_name("carriage");
  add_name("tour_wagon");
  add_name("horse carriage");
  reset_carriage();
  set_short("@@carriage_short");
  set_long("@@carriage_long");
  add_prop(OBJ_I_WEIGHT,400000);  /* Well, a wagon is heavy - 400 kg...*/
  add_prop(OBJ_I_VOLUME,400000);  /* Large volume too :) */
  add_item(({"horse","horses"}),"@@exa_horses");
}

reset_carriage() 
{
  WAGON_INSIDE->short();
  set_horses(2);
  set_max_horses(4);
  set_max_livings(4);
  arrange_tours();
  this_object()->move("/d/Gondor/minas/e3crc1");
  tell_room(environment(this_object()),"A horse-carriage comes rolling out of the stables.\n");
  call_out("prepare_tour",60);
  return 1;
}

arrange_tours() {
  tour = TOUR_FILE->query_tour();
  retour = TOUR_FILE->query_tour();
}

init() {
  add_action("enter_wagon","enter");
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
  tell_room(environment(this_object()),"The wagon-driver yells: All passengers aboard! The transport to Edoras leaves soon!\n");
  tell_room(WAGON_INSIDE,"The wagon-driver yells: All passenger aboard! The transport to Edoras leaves soon!\n");
  goal = "Edoras";
  set_leavable(0);
  call_out("tour_move",15,0);
  return 1;
}

turn_back() {
  tell_room(environment(this_object()),"The wagon-driver yells: All passengers aboard! The transport is returning to Minas Tirith!\n");
  tell_room(WAGON_INSIDE,"The wagon-driver yells: All passenger aboard! The transport is returning to Minas Tirith!\n");
  goal = "Minas Tirith";
  set_leavable(0);
  call_out("retour_move",15,0);
  return 1;
}

tour_move(int turn)
{
  int maxn,n;
  string *exit_arr;
  exit_arr = environment(this_object())->query_exit();
  maxn = sizeof(exit_arr);
  my_noise(tour[turn]);
  while (n<maxn)
    {
      tell_room(environment(this_object()),"WAGONTEST: N is "+n+", and exit_arr[n] is "+exit_arr[n]+".\n");
      n++;
    }
  if (sizeof(tour)>turn+1) 
    {
      call_out("tour_move",speed,turn+1);
      return 1;
    }
  set_leavable(1);
  call_out("turn_back",120);
  return 1;
}

retour_move(int turn)
{
  int maxn,n,i;
  string *exit_arr;
  my_noise(retour[turn]);
  exit_arr = environment(this_object())->query_exit();
  maxn = sizeof(exit_arr);
  while (n<maxn)
    {
      if (retour[turn] == exit_arr[n][1]) this_object()->move(exit_arr[n][0]);
      n++;
    }
  if (sizeof(retour)>turn+1)
    {
      call_out("retour_move",speed,turn+1);
      return 1;
    }
  set_leavable(1);
  call_out("prepare_tour",120);
  return 1;
}

my_noise(string dir)
{
  tell_room(environment(this_object()),"The wagon whirls up some dust as it passes you on its way "+dir+"wards.\n");
  tell_room(WAGON_INSIDE,"The wagon rambles on "+dir+"wards along the road to "+goal+".\n");
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
  if (livings == max_livings) {
    write("The carriage is full already, there are "+livings+" persons in it!\n");
    say(QCTNAME(this_player())+" tries to enter the horse carriage, but it is full.\n",this_player());
    return 1;
    }
  write("You enter the horse carriage.\n");
  say(QCTNAME(this_player())+" enters the horse carriage.\n",this_player());
  tell_room(WAGON_INSIDE,QCTNAME(this_player())+" enters the horse carriage.\n");
  this_player()->move(WAGON_INSIDE);
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
  long_descf = "From a little sign on the side of the carriage, you understand that it runs between Minas Tirith and Edoras.";
  return (break_string(long_descf,70));
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

exa_horses() {
  if (horses==1) {
    return "There is only one horse pulling the carriage.\n";
    }
  if (horses>1) {
    return "There are "+horses+" horses pulling the carriage. They seem in good shape.\n";
  }
}

query_leavable()
{
  return leavable;
}

set_leavable(int i)
{
  leavable = i;
}


