inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"
#include "dirdefs.h".

#define DOWN_ROOM    "chimney4"

void reset_room();

int     jump_alarm = 0;
object  jumper;
string  down_room;

void
create_room()
{
  set_long(BSN("You are on a small plateau high in the White Mountains in Gondor. " +
    "It is rather cold and windy here. South of where you are standing " +
    "there rises a sheer cliff high into the sky. To the west, the plateau ends " +
    "with the walls falling down far too steep to climb. The plateau extends a bit " +
    "further to the northwest. " +
    "To the east, you can see a broad chasm that ends in a chimney further north. " +
    "Across the chimney, a smooth wall is rising vertically to a projecting rock. " +
    "Looking across the chasm, on the other side you see a smaller plateau from " +
    "which you might be able to climb up to the projecting rock. You would have " +
    "to jump across the chasm first, however."));
  set_short("On a small plateau high up in the White Mountains");
  add_item(({ "wall", "rock wall" }),
      BSN("The wall on the other side of the chimney is rather steep, "
      + "and since the chimney is too broad, you cannot climb it."));
  add_item(({ "rock", "projecting rock" }), "You cannot see what's on it " +
      "from here.\n");
  add_item(({"cleft","chasm","broad cleft"}), BS(
    "The chasm divides the plateau you are on into two parts. The large one " +
    "is where you are standing, the smaller one is on the other side of the " +
    "cleft. To the south, the cleft disappears between large sheer cliffs " +
    "rising on either side of it, both bounding the small plateaus southward. " +
    "To the north, the cleft ends in a narrow chimney. It would be much easier " +
    "to cross the narrow chimney than jumping across the broad cleft, but " +
    "across the chimney, there is a sheer rock wall rising up to the " +
    "projecting rock. Where you are standing, " +
    "the cleft is about fifteen feet broad, so you should be able to jump " +
    "across, provided you rested a bit after the climb up to the plateau.\n"));
  add_item(({"plateau","plateaus","small plateau"}), BSN(
    "The plateau is divided into two parts by the cleft. From where you are " +
    "standing, you can make out that the smaller part of the plateau across the " +
    "cleft is surrounded on three sides by rock walls. One of these walls leads " +
    "up to the projecting rock and you might be able to climb it. Close to " +
    "walls, you can see some plants growing in a few protected spots."));
  add_item("chimney", BSN(
    "This is a narrow chimney, going straight down between the rock walls."));
  add_exit(THIS_DIR + "plateau1", "northwest", 0, 2);

  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_prop(OBJ_I_SEARCH_TIME,8);
  set_search_places(({"ground","plateau", "slope", "rock"}));
  add_herb_file(HERB_DIR+"frostheal");
  add_herb_file(HERB_DIR+"madwort");

  seteuid(getuid());
  down_room = (THIS_DIR + DOWN_ROOM);
  if(down_room)
      down_room->load_me();
}

void
init()
{
  ::init();
  add_action("climb", "climb");
  add_action("jump", "jump");
  add_action("do_enter","enter");
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
  if (str == "down")
  {
    write("You cannot climb down here.\n");
    return 1;
  }
  if (str == "up")
  {
    write("You cannot climb up here.\n");
    return 1;
  }
  return 0;
}

do_fall(object player, int height)
{
  if(!height)
    write("AAARRRRGGGHHH!!! You fall.\n\n");
  else
    write("\nYou continue to fall down.\n\n");

  height = height + 1;

  tell_room(down_room, "You hear a terrible scream as someone falls down from above.\n");
  player->move_living("M", down_room, 1);
  down_room->do_fall(player, height);
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
    return 1;
  }

  TP->add_fatigue(-25);

  TP->add_prop("_is_jumping",1);
    jumper = TP;
  jump_alarm = set_alarm(2.0,1.0,"jump_message", jumper, cap);
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
              tp->move_living("M",THIS_DIR + "plateau3",1);
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
              tell_room(THIS_DIR + "plateau3", "You hear a terrible scream from the chasm.\n");
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
          }
          else
          {
              write(BS("With your last strength, you manage to pull yourself up " +
                  "to the small plateau on this side of the cleft.") + "\n\n" +
                  "You made it!\n\n");
              say("With " + tp->query_possessive() + " last strength, " + QCTNAME(tp) +
                  " manages to pull " + tp->query_objective() + "self up.\n");
              end_jump(tp);
              tp->move_living("M",THIS_DIR + "plateau3",1);
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

int do_enter(string str)
{
  if(!str || (str != "chimney"))
  {
    NF("Enter what?\n");
    return 0;
  }
  write("There is no way to enter the chimney from here.\n"+
        "If you did try, you would fall down the chasm to your death!\n");
  return 1;
}

void
reset_room()
{
    set_searched(0);
}
