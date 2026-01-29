inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "dirdefs.h".
#include "/d/Gondor/common/lib/herbsearch.h"

#define UP_ROOM    "wall3"
#define DOWN_ROOM    "chimney4"

void reset_room();

int     jump_alarm = 0;
object  jumper;
string  up_room,
        down_room;

void
create_room()
{
  set_long(BSN("You are on a small plateau high in the White Mountains in " +
      "Gondor. The plateau is bounded on three sides by rock walls, and " +
      "only the one to the north seems climbable. " +
      "On the fourth side of the plateau there is a broad cleft. " +
      "You might be able to climb up."));
  set_short("On a plateau high up in the White Mountains");
  add_item(({ "walls", "wall", "rock walls" }), BSN(
      "The walls are rather steep, but an experienced climber might be able " +
      "to climb the wall to the north."));
  add_item(({"chimney", "cleft", "chasm"}), BSN(
      "The cleft is about fifteen feet broad here. If you are rested, you are " +
      "probably able to jump across. The walls of the cleft are much too steep " +
      "to climb down."));
  add_item(({"plateau","plateaus","small plateau"}), BSN(
      "The plateau is divided into two parts by the cleft. From where you are " +
      "standing, you can make out the larger part of the plateau across the " +
      "cleft. Close to walls, you can see some plants growing in a few " +
      "protected spots."));

  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_prop(OBJ_I_SEARCH_TIME,8);
  set_search_places(({"ground","plateau", "slope", "rock"}));
  add_herb_file(HERB_DIR+"frostheal");
  add_herb_file(HERB_DIR+"madwort");

  seteuid(getuid());
  up_room = (THIS_DIR + UP_ROOM);
  down_room = (THIS_DIR + DOWN_ROOM);
  if(up_room)
    up_room->load_me();
  if(down_room)
    down_room->load_me();
}

init()
{
  ::init();
  add_action("jump","jump");
  add_action("climb", "climb");
  add_action("catch_all","",1);
}

void
end_jump(object player)
{
    remove_alarm(jump_alarm);
    jump_alarm = 0;
    jumper = 0;
    player->remove_prop("_is_jumping");
}

int
catch_all(string str)
{
    int     stage = TP->query_prop("_is_jumping");

    if (TP->query_wiz_level())
        return 0;

    if (stage > 3)
    {
        write("You are jumping across the chasm, it's too late to stop now!\n");
        return 1;
    }
    else if (stage > 0)
    {
        write("You stop in your tracks when you suddenly start doing something else.\n");
        end_jump(TP);
        return 0;
    }
    return 0;
}

climb(string str)
{
  NF("Climb what?\n");
  if (str == "up")
  {
    if(up_room)
      return climb_up();
    else
    {
      write("You cannot climb up here.\n");
      return 1;
    }
  }
  if (str == "down")
  {
    write("You cannot climb down here.\n");
    return 1;
  }
  return 0;
}

int
climb_up()
{
  int skillvalue, rnd;
skillvalue = ((TP->query_skill(SS_CLIMB) - 5) * 2);
  if (skillvalue < 15)
  {
    write(BS("You examine the wall closely and realize that you are not sufficiently " +
      "skilled in climbing, so you dare not to try it.\n"));
      return 1;
  }
  rnd = random(20);
  if (skillvalue + rnd > 40)
  {
    write("You skillfully climb up the wall.\n");
    say(QCTNAME(TP) + " climbs up.\n", TP);
    TP->move_living("M", up_room, 1);
    TP->add_fatigue((rnd+skillvalue)/6 - 25);
    say(QCTNAME(TP) + " arrives climbing up from below.\n", TP);
    return 1;
  }
  write("You try to climb higher, but you lose your grip!\n");
  say(QCTNAME(TP) + " begins to climb higher, but "+
    TP->query_pronoun() + " loses " +
    TP->query_possessive() + " grip and falls down again!\n", TP);
  return 1;
}

void
do_fall(object player, int height)
{
  int acrobat, dex, hurt;
  if(!height)
  {
    write("AAARRRRGGGHHH!!! You fall.\n\n");
    height = height + 1;
    tell_room(down_room, "You hear a terrible scream as someone falls down from above.\n");
    player->move_living("M", down_room, 1);
    down_room->do_fall(player, height);
  }
  else
  {
    acrobat = TP->query_skill(SS_ACROBAT);
    if(acrobat > 25) acrobat = 25;
    dex = TP->query_stat(SS_DEX);
    if(dex > 100) dex = 100;
    hurt = height*height*20 - acrobat*2 - dex/2;
    if(hurt < height*height*10) hurt = height*height*10;
    hurt = hurt*3 + random(hurt*4);
    write("You crash to the ground on the small plateau next to the chasm.\n");
    say(QCTNAME(TP) + " falls down from the rock wall.\n");
    TP->heal_hp(-hurt);
    if (TP->query_hp() <= 0)
    {
      TP->do_die(TO);
      write_file("/d/Gondor/log/climb", TP->query_name() + " died climbing in the White Mountains on the plateau. " +
        "Avg_stat = " + TP->query_average_stat() + ", climbing = " + TP->query_skill(SS_CLIMB) + ", " +
        ctime(time())+".\n");
    }
  }
  return;
}

jump(string str)
{
  string s1, s2;
  NF("Jump what?");
  if(!str) return 0;

  if(sscanf(str,"%s %s",s1,s2) == 2)
    if((s1 == "across" || s1 == "over") && (s2 == "chasm" || s2 == "cleft"))
    {
      return do_jump();
    }
  if(str == "chasm" || str == "cleft")
  {
    return do_jump();
  }
  return 0;
}

int
do_jump()
{
  int cap;
  int str, dex, fat;

    if (objectp(jumper))
    {
        write(process_string(QCTNAME(jumper)) + " is already trying to jump across the chasm!\n"+
            "You will have to wait until "+jumper->query_pronoun()+" makes room for you to jump.\n");
         return 1;
    }

  str = TP->query_stat(SS_STR);
  dex = TP->query_stat(SS_DEX);
  fat = TP->query_fatigue();

  cap = str + dex + fat;

  write(BS("You recede from the cleft as far as the small open space " +
    "up here allows to take a run before trying to jump across.\n"));
  say(QCTNAME(TP) + " prepares to take a run.\n");
  say("It looks as if " + TP->query_pronoun() + " plans to jump the chasm.\n");
  if(TP->query_stat(SS_DIS)  < 55)
  {
    write("But then your courage leaves you. You just do not dare to risk the jump.\n");
    say("But then, " + TP->query_possessive() + " courage leaves " + TP->query_objective() + ".\n");
    return 0;
  }

  TP->add_fatigue(-25);

    jumper = TP;
  jump_alarm = set_alarm(2.0,1.0,"jump_message", jumper, cap);
  TP->add_prop("_is_jumping",1);
  return 1;
}

void
jump_message(object tp, int cap)
{
  int     stage = tp->query_prop("_is_jumping");

  switch (stage)
  {
      case 1:
          say(QCTNAME(tp) + " runs towards the cleft, and tries to jump across.\n");
          write("And then you start to run towards the cleft ... \n\n");
          break;
      case 2:
          write(" ... it seems to fly up to you ... \n\n");
          break;
      case 3:
          write(" ... and then, at the last possible moment ... \n\n");
          break;
      case 4:
          write(" ... you jump ....... \n\n\n");
          break;
      case 5:
          write(" ... you fly across the cleft ... \n\n");
          break;
      case 6:
          if(cap > 200)
          {
              write(" ... and land safely on the other side of the cleft.\n\n" +
                  "You did it!\n");
              say(CAP(tp->query_pronoun()) + " seems to have landed safely on the other side.\n");
              write("The jump made you rather breathless.\n");
              end_jump(tp);
              tp->move_living("M",THIS_DIR + "plateau2",1);
              tell_room(ENV(tp), QCTNAME(tp) + " arrives jumping across the chasm.\n", tp);
          }
          else 
              write(" ... and then, you realize that your jump will be too short ... \n\n");
          break;
      case 7:
          if (cap > 200)
              end_jump(tp);
          else
              write(" ... desperately, you throw your arms ahead ... \n\n");
          break;
      case 8:
          if (cap > 200)
              end_jump(tp);
          else
          {
              write(" ... trying to reach the other side of the cleft at least with your hands ... \n\n");
              say("But " + tp->query_possessive() + " jump goes too short.\n");
          }
          break;
      case 9:
          if(cap > 150)
          {
              write("You hit hard against the rocky edge, hurting your arms \n" +
                  "and chest rather badly. But you manage to get a hold.\n\n");
              tp->heal_hp((200-cap)*20);
              tp->add_fatigue(-25);
              say(QCTNAME(tp) + " hits hard against the rocky edge on the other side of the cleft.\n");
              say(CAP(tp->query_pronoun()) + " barely manages to get a hold.\n");
          }
          else
          {
              write(" ... but you cannot reach it ....... \n\n\n");
              say(CAP(tp->query_pronoun()) + " falls down with a loud scream.\n");
              end_jump(tp);
              do_fall(tp,0);
          }
          break;
      case 10:
          if((cap > 150) && (tp->query_hp() <= 0))
          {
              write("But then your strength is gone ... \n\n" +
                  " ... and you let go ..... \n\n");
              say("But then " + tp->query_possessive() + " strength is gone.\n");
              say(QCTNAME(tp) + " falls down with a terrible scream.\n");
              end_jump(tp);
              do_fall(tp,0);
              tell_room(THIS_DIR + "plateau2", "You hear a terrible scream from the chasm.\n");
          }
          else
          {
              write(BS("With your last strength, you manage to pull yourself up " +
                  "to the small plateau on this side of the cleft.") + "\n\n" +
                  "You made it!\n\n");
              say("With " + tp->query_possessive() + " last strength, " + QCTNAME(tp) +
                  " manages to pull " + tp->query_objective() + "self up.\n");
              end_jump(tp);
              tp->move_living("M",THIS_DIR + "plateau2",1);
              tell_room(ENV(tp), QCTNAME(tp) + " arrives jumping across the chasm.\n", tp);
              write("The jump has taxed you quite a lot.\n");
          }
          break;
      default:
          write("An error occured - please make a bug report! Thanks!\n");
          end_jump(tp);
          break;
    }
    if (tp->query_prop("_is_jumping"))
        tp->add_prop("_is_jumping",++stage);
}

void
reset_room()
{
    set_searched(0);
}
