#include "defs.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "ogress"
object witch;
int op;

CONSTRUCT_ROOM {
    op = 0;
    set_short("Ogress' dwelling");
    set_long("@@my_long@@");
    add_prop(ROOM_I_LIGHT, 1);
    add_item(({"cave","room"}),
             "It is obviously the dwelling of the ogress.");
    add_item(({"fire-place","fire place"}),
             "This must be from where she fetches energy for her magic "+
             "spells.");
    add_item(({"carpets","carpet"}),
             "They are soft, but somehow, you can't remove them.");
    add_item("hole","@@hole@@");
    add_exit(THIS_DIR+"rattrap","north", "@@chk_north@@");
    reset();
}

RESET_ROOM {
    op = 0;
    if (!witch || !present(witch)) {
      witch = clone_object(MORIA_NPC+"newogress");
      witch->move(this_object());
    }
}

object
query_witch()
{
    return witch;
}

init() {
    ::init();
    add_action("my_say","say");
    add_action("my_say","'",1);
    add_action("my_say","rsay");
    add_action("my_say","shout");
    add_action("my_nod","nod");
    add_action("my_nod","agree");
    add_action("enter","enter");
    add_action("down","down");
    add_action("my_climb","climb");
}

string
my_long() {
    string desc;
    desc ="This is the dwelling of the ogress. It is a dark cave with a "+
      "crackling fire-place in a corner of the room. The walls are "+
      "covered with soft carpets, and the only exit is to the north, "+
      "where you came from. ";
    if (op)
        desc += "There is also a hole in the floor here.";
    return desc;
}

string
hole() {
    if (op)
        return "A hole in the floor.\n"+
               "You can probably go down there.\n";
    else
        return "What hole?\n";
}
  chk_north() {
  if (witch && !witch->query_allowed(this_player())) {
    write("The ogress wont let you pass.\n");
    return 1;
  }
}

int
down() {
    if (!op)
        return 0;
    this_player()->move_living("down",THIS_DIR+"deep/ringroom");
    return 1;
}

int
my_say(string what)
{
    string vrb = query_verb();
    if (vrb[0]=='\'')
        what = extract(vrb,1)+" "+what;
    if (witch && present(witch, TO))
        witch->recieve_say(TP, what);
    return 0;
}

int
my_nod(string how)
{
    if (witch && present(witch, TO) && witch)
        witch->recieve_say(TP, "yes");
    return 0;
}

int
my_climb(string str) {
  if (!op) {
    notify_fail("Climb where?\n");
    return 0;
  }
  if (str =="down" || str == "hole")
    return down();
  return 0;
}

int
enter(string str) {
  if (!op){
    notify_fail("Enter what?\n");
    return 0;
  }
  if (str == "hole")
    return down();
  return 0;
}

void
open_hole() {
    op = 1;
}

int
reward_player(object player)
{


    if(player->test_bit("Shire",EASTERN_GROUP,OGRESS_BIT))
    {
      witch->command("say How dare you come back!");
      player->force_out();
      return 1;
    }


          player->remove_prop("_ogress_code");
          player->set_bit(EASTERN_GROUP,OGRESS_BIT);
          player->add_exp(OGRESS_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
CAP(player->query_real_name()) + " rewarded with "+OGRESS_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel much more experienced!\n");
               say(QCTNAME(player) + " got a nice reward.\n");

    if(!player->query_skill(SS_WEP_AXE) > 80)
       player->set_skill_extra(SS_WEP_AXE, 20);
      return 1;

}
