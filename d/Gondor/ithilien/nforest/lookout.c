inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

#define HARD_TO_CLIMB  20  /* how hard is it to climb up the cedar? - x + random(x) */

string extraline;
int ladder, alarm_id;
object damrod, meneldil;

string describe();
void   reset_room();

void
create_room()
{
  set_short(BS("A branch close to the top of a giant cedar"));
  extraline =
    "You are close to the top of the tree. Someone has cut away " +
    "several branches and twigs so that you have a terrific view from here. " +
    "To the north, you can look over a heath covering gentle slopes and vales that extend to the Anduin in the west. " +
    "The foothills of the Ephel Duath are rising to the east, the dark shadow of the mountains themselves " +
    "receding eastward in a long curve. " +
    "Where the heath meets the foothills, a road can be seen, running from the north " +
    "to the south in a straight line. From here, every movement on that road can be " +
    "observed. " +
    "You might manage to climb down the tree. ";
  set_long("@@describe");
  add_item(({"river","anduin"}),BS(
    "Far away to the west, you can see a shimmering blue band. " +
    "This is the mighty river Anduin, running from the Falls of Rauros " +
    "south towards Osgiliath and finally to its mouth at the sea. " +
    "You estimate that it is about ten leagues from here to its eastern shore.\n"));
  add_item(({"cedar","cedar tree","tree"}), BS(
    "This is a giant tree with an enourmous trunk. You are close to the top, " +
    "perhaps thirty or forty metres above the ground. \n"));
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "The mountains named Ephel Duath appear to be dark grey from here. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are several kilometers away now.\n"));
  add_item("road",VBFC_ME("on_road"));
  add_item(({"branch","branches","bough","boughs"}), BS(
    "All the branches of the cedar tree are densely covered with thick green needles. " +
    "The branch you are standing on is close to the top of the cedar. " +
    "It is thicker than a man's thigh and probably could hold several people. \n"));
  add_item(({"heath","heathland","heath land"}), BS(
    "North of the forests, you can see a tumbled heathland spreading far " +
    "to the north, grown with ling and " +
    "broom and cornel, and other shrubs you do not know. Here and there " +
    "you can see knots of tall pine-trees. \n"));

  set_noshow_obvious(1);

  reset_room();
}

void
add_damrod()
{
  damrod = clone_object(ITH_DIR + "npc/damrod.c");
  damrod->arm_me();
  damrod->move(TO);
  tell_room(TO,capitalize(LANG_ADDART(damrod->query_nonmet_name())) + " arrives.\n");
}

void
add_meneldil()
{
  meneldil = clone_object(ITH_DIR + "npc/meneldil");
  meneldil->arm_me();
  meneldil->move(TO);
  tell_room(TO,capitalize(LANG_ADDART(meneldil->query_nonmet_name())) + " arrives.\n");
  if(objectp(damrod)) damrod->team_join(meneldil);
}

void
reset_room()
{
  if(!objectp(damrod)) add_damrod();
  if(!objectp(meneldil)) add_meneldil();

}

string
describe()
{
  object clock;
  string time,long_descf;
  clock = find_object(CLOCK);
  time = clock->query_time_of_day();
  long_descf = "You are standing on a branch of a giant cedar in a forest somewhere " +
    "in northern Ithilien. ";
  if (!clock->query_war()) 
  {
    if (time == "night") 
    {
      long_descf = long_descf + "Darkness rules the fields of Ithilien now in the nightime. ";
      if (clock->query_moon()==2) long_descf = long_descf + "A full moon gives some light though. ";
      else if (clock->query_moon()==1) long_descf = long_descf+"The moon gives a little light though. ";
      else long_descf = long_descf+"The sky is covered with dark clouds, and not even the moon "+
        "shines through. ";
    }
    if (time == "afternoon") {
      long_descf = long_descf+"The light of day shines across Ithilien. "+
      "It is afternoon. ";
    }
    if (time == "morning") {
      long_descf = long_descf+"The sun is on its way up on the morning sky to the east. ";
    }
    if (time == "noon") {
      long_descf = long_descf + "The sun is almost at its peak on its way across the sky. "+
        "It is the middle of the day in Middle-Earth. ";
    }
    if (time == "evening") {
      long_descf = long_descf+"The sun is setting in the west, coloring the sky golden red. ";
    }
    if (time == "early morning") {
      long_descf = long_descf + "The sun is rising in the east, casting long shadows "+
        "across Ithilien. ";
    }
  }
  else {
    if (time == "evening"||time=="night"||time=="early morning") {
      long_descf = long_descf + "Massive dark clouds cover the sky, making it "+
        "difficult to distinguish night and day. The clouds seem to be coming from "+
          "the east, where Mordor lies. You suspect it is night now, as it is as dark "+
            "as it can get. ";
    }
    if (time == "morning") {
      long_descf = long_descf + "A thick cover of clouds prevent the sun from "+
        "shining on the lands of Ithilien, and it is almost as dark as at night. "+
          "However you gather that it is probably morning, as it is getting a bit "+
            "lighter than earlier. ";
    }
    if (time == "noon") {
      long_descf = long_descf + "A dark mass of clouds seems to be rolling in from "+
        "the east, covering the sky above Ithilien. It is not much lighter now than "+
          "it usually is at night, but still you suspect it is the middle of the day. ";
    }
    if (time == "afternoon") {
      long_descf = long_descf + "A thick mass of clouds cover the sky, making it "+
        "difficult to see far. You suspect that it is afternoon, as it is getting "+
          "a bit darker than earlier. ";
    }
  }
  if(ladder) extraline = extraline + "Tied to the tree trunk there is a rope ladder. ";
  if (extraline) long_descf = long_descf + extraline + "\n";
  else long_descf = long_descf + "\n";
  return (break_string(long_descf,75));
}

void
drop_item(object ob)
{
  string down_room;

  down_room = ITH_DIR + "nforest/mbranch";
  if (ob && present(ob))
  {
    tell_room(TO, "The " + ob->query_name() + " falls down.\n");
    ob->move(down_room);
    tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from above.\n");
    down_room->drop_item(ob);
  }
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if(!living(ob))
    set_alarm(1.0, 0.0, &drop_item(ob));
}

void 
fall_down(int hit)
{
  write("You try to climb down from the branch.\n");
  write("Suddenly you slip ...\n");
  tell_room(TO,QCTNAME(TP) + " tries to climb down from the branch, but slips.\n",TP);
  TP->reduce_hit_point(hit);
  write(BS("You fall down from the branch, but you manage to stop your fall somewhere halfway down the tree.\n"));
  tell_room(TO,capitalize(TP->query_pronoun()) + " falls down from the branch.\n",TP);
  TP->move_living("M",ITH_DIR + "nforest/mbranch");
  tell_room(ENV(TO),QCTNAME(TP) + " arrives falling down from above.\n",TP);
  return;
}

void 
climb_down()
{
  if(TP->query_prop("_arrested") && damrod && present(damrod,TO)) 
  {
    if(!damrod->stop_fleeing(TP))
    {
      write(BS(process_string(QCTNAME(damrod)) +
        " tries to stop you, but you manage to climb down.\n"));
      tell_room(TO,BS(QCTNAME(damrod) + " tries to stop "+
        QTNAME(TP)+", but "+TP->query_pronoun()+" manages to climb down.\n"),TP);
      fall_down(HARD_TO_CLIMB + 2*random(HARD_TO_CLIMB) - TP->query_stat(SS_DEX)/3);
    }
  }
  else if(TP->query_prop("_arrested") && meneldil && present(meneldil,TO)) 
  {
    meneldil->command("kill " + TP->query_real_name());
    fall_down(HARD_TO_CLIMB + 2*random(HARD_TO_CLIMB) - TP->query_stat(SS_DEX)/3);
  }
  else if(TP->query_attack())
  {
    fall_down(HARD_TO_CLIMB + 2*random(HARD_TO_CLIMB) - TP->query_stat(SS_DEX)/3);
  }
  else
  {
    write(BS("You climb down.\n"));
    tell_room(TO,QCTNAME(TP) + " climbs down.\n",TP);
    TP->move_living("M",ITH_DIR + "nforest/mbranch");
    tell_room(ENV(TP),QCTNAME(TP) + " arrives climbing down from above.\n",TP);
  }
  return;
}

int
query_ladder()
{
  return ladder;
}

int
add_ladder()
{
  if(ladder) return 0;
  else
  {
    ladder = 1;
    return 1;
  }
}

int
remove_ladder()
{
  if(!ladder) return 0;
  else
  {
    ladder = 0;
    return 1;
  }
}

int
do_climb(string str)
{
  int climb_skill, dex_stat, risk, hurt, cap;

  if(!str)
  {
    write("Climb what? \n");
    return 1;
  }

  climb_skill = TP->query_skill(SS_CLIMB);
  dex_stat = TP->query_stat(SS_DEX);
  risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
  cap = climb_skill + dex_stat/2;

  if (str == "cedar" || str == "branch" || str == "bough" || str == "tree")
  {
    write(BS("Climb up or down?\n"));
    return 1;
  }

  if (str == "up")
  {
    write(BS("You cannot climb any further up, since the branches would not support you.\n"));
  }
  else if(str == "down")
  {
    risk = risk + random(HARD_TO_CLIMB);
    if(cap > risk) climb_down();
    else fall_down(5*(risk-cap));
  }
  else if(str == "ladder")
  {
    if(!ladder)
    {
      write("You cannot see any ladder here.\n");
      return 1;
    }
    else
    {
/*
      climb_ladder();
*/
    }
  }
  else write("Climb what? \n");
  return 1;
}

string
on_road()
{
  string desc;
  object road9,road10,road11;
  object *list, *lnames;
  int i,size,flag;

  desc = 
    "The long straight road runs north towards the Morannon, the Black " +
    "Gates of Mordor, while in the other direction it goes to the crossroads " +
    "where it meets the road from Osgiliath to Minas Morgul. From there, it " +
    "then continues through South Ithilien towards the land of Harad. " +
    "The road and everyone travelling on it is visible for many miles to the north. To the west, the view " +
    "is blocked by the ridge on which the cedar you are in is standing. ";
  flag = 0;

  seteuid(getuid(this_object()));

  "/d/Gondor/ithilien/road/nr9"->teledingska();
  road9 = find_object("/d/Gondor/ithilien/road/nr9");
  "/d/Gondor/ithilien/road/nr10"->teledingska();
  road10 = find_object("/d/Gondor/ithilien/road/nr10");
  "/d/Gondor/ithilien/road/nr11"->teledingska();
  road11 = find_object("/d/Gondor/ithilien/road/nr11");

  lnames = ({ });
  list = all_inventory(road9);
  for(i = 0; i < sizeof(list); i++)
  {
    if(living(list[i])) lnames += ({list[i]});
  }

  size = sizeof(lnames);
  if(size)
  {
        desc += "Where the road leaves the cleft through the ridge, you can see " + COMPOSITE_LIVE(lnames) + " on the road. ";
        flag = 1;
  }

  lnames = ({ });
  list = all_inventory(road10);
  for(i = 0; i < sizeof(list); i++)
  {
    if(living(list[i])) lnames += ({list[i]});
  }

  size = sizeof(lnames);
  if(size)
  {
        desc += "Further north, you can see " + COMPOSITE_LIVE(lnames) + " on the road. ";
        flag = 1;
  }

  lnames = ({ });
  list = all_inventory(road11);
  for(i = 0; i < sizeof(list); i++)
  {
    if(living(list[i])) lnames += ({list[i]});
  }

  size = sizeof(lnames);
  if(size)
  {
        desc += "The excellent view from the lookout makes it possible to see " + COMPOSITE_LIVE(lnames) +
          " on the road far to the north. ";
        flag = 1;
  }

  if(!flag) desc += "There is nobody on the road. ";

  return BS(desc + "\n");
}

void
alert_msg(object ob)
{
  meneldil->command("say Look out!");
  if(IS_EVIL(ob))
  {
    meneldil->command("say There are enemies on the road!");
    return;
  }
  meneldil->command("say There is something on the road.");
}

void
enter_road(object ob, object from)
{
  remove_alarm(alarm_id);
  alarm_id = 0;
  if(!present("ranger",TO)) return;
  if(!meneldil || !present(meneldil,TO)) return;
  if (!alarm_id)
    alarm_id = set_alarm(2.0, 0.0, &alert_msg(ob));
}

void
make_smoke(object fire)
{
  tell_room(TO,"Smoke from " + LANG_ADDART(fire->short()) + " is rising from below into the sky.\n");
  if(!damrod || !present(damrod,TO)) return;
  damrod->fire_alarm();
  return;
}

void
init()
{
  ::init();
  add_action("do_climb","climb");
}
