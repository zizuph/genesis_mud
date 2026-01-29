inherit "/std/object";
 
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#include "/sys/macros.h"
 
int filled;
 
create_object()
{
  set_name(({"bottle", "zima", "bottle of zima"}));
  set_pname(({"bottlez", "zima", "bottlez of zima"}));
  set_short("@@my_short_desc");
  set_pshort("@@my_pshort_desc");
  set_long("@@my_long_desc");
  add_prop(OBJ_I_WEIGHT, "@@my_weight");
  add_prop(OBJ_I_VOLUME, 1500);
  add_prop(OBJ_I_VALUE, "@@my_value");
  filled = 2;
}
 
my_short_desc()
{
  switch (filled)
  {
    case 2: return "full bottle of zima";
    case 1: return "half-full bottle of zima";
    case 0: return "empty bottle of zima";
  }
}
 
my_pshort_desc()
{
  switch (filled)
  {
    case 2: return "full bottlez of zima";
    case 1: return "half-full bottlez of zima";
    case 0: return "empty bottlez of zima";
  }
}
 
my_long_desc()
{
  switch (filled)
  {
    case 2:
      return break_string("A clear malt drink, it has a light citruz "
       +"taste...zomething different!.\n", 70);
    case 1:
      return break_string("A clear malt drink, it has a light citruz "
       +"tast..zomething different! Unfortunately, only half is left :( "
       +".\n", 70);
    case 0:
     return break_string("It is an empty clear zima bottle.  It is worthlezz."
       +"You better give it to the butler.\n", 70);
  }
}
 
my_weight()
{
  switch (filled)
  {    case 2: return 1000;
    case 1: return 600;
    case 0: return 200;
  }
}
 
my_value()
{
  switch (filled)
  {
    case 2: return 12;
    case 1: return 5;
    case 0: return 0;
  }
}
 
init()
{
  ::init();
  add_action("do_drink", "drink");
  add_action("do_cheer", "cheer");
  add_action("do_cheer", "cheerz");
}
 
do_drink(str, nocheck)
{
  object *obs;
 
  if (!nocheck)
  {
    notify_fail("Drink what?\n");
    if (!str) return 0;
    obs = FIND_STR_IN_OBJECT(str, this_player());
    if (!obs || !sizeof(obs) || obs[0] != this_object()) return 0;
  }
  switch (filled)
  {
    case 2:
      filled = 1;
      write("You drink zome zima from the bottle.  It tastez very good " 
       +"and luckily there is still zome left.\n");
      say(QCTNAME(this_player()) + " drinks some zima and smilez "
       +"happily.\n");
      return 1;
    case 1:
      filled = 0;
      write("You zwing the rest of the bottle. It was very good this "
       +"zima.\n");
      say(QCTNAME(this_player()) + " finishez "
       +this_player()->query_possessive() + " bottle of zima and givez "
       +"you a drunk look.\n");
      return 1;
    case 0:
      notify_fail("The bottle is empty.\n");
      return 0;
  }
}
 
do_cheer(str)
{
  object *obs;
  string adj, qp;
 
  switch (filled)
  {
    case 2: adj = "filled"; break;
    case 1: adj = "semi-filled"; break;
    case 0: notify_fail("You cannot cheer with an empty bottle.\n"); return
0;
  }
  qp = this_player()->query_possessive();
  if (!str || str == "to everyone" || str == "everyone" || str == "to all"
||
    str == "all")
  {
    write("You raise your " + adj + " bottle of zima high in the air "
     +"and cheer to everyone. ");
    say(QCTNAME(this_player()) + " raises " + qp + " " + adj +" bottle of "
     +"zima and yells: 'Cheerz to you all'. ");
    do_drink(0, 1);
    return 1;
  }
  obs = FIND_STR_IN_OBJECT(str, environment(this_player()));
  if (!obs || !sizeof(obs) || !living(obs[0]))
  {
    notify_fail("Cheer who?\n");
    return 0;
  }
  if (present("bottle of zima", obs[0]))
  {
    this_player()->catch_mst("You hold up your " + adj + " bottle of zima " 
     +"and cling it with the one " + QTNAME(obs[0]) + " is carrying: "
     +"Cheerz!\n");
    obs[0]->catch_msg(QCTNAME(this_player()) + " holds up " + qp + " " + adj
     +" bottle of zima and clings it with yours: Cheerz!\n");
    say(QCTNAME(this_player()) + " and " + QTNAME(obs[0]) + " cling their "
     +"bottles of zima together.\n", ({ this_player(), obs[0] }));
  }
  else
  {   this_player()->catch_mst("You hold your " + adj + " bottle of zima in " 
     +" front of " + QTNAME(obs[0]) + " and yell: CHEERZ!\n");
    obs[0]->catch_msg(QCTNAME(this_player()) + " holds " + qp + " " + adj
     +" bottle of zima in front of you and yells: CHEERZ!\n");
    say(QCTNAME(this_player()) + " holds " + qp + " " + adj + " bottle of "
     +"zima in front of " + QTNAME(obs[0]) + " and yells: CHEERZ!\n",
     ({ this_player(), obs[0]}));
  }
  return 1;
}
