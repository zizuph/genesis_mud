/* goblin caves */
inherit "/d/Rhovanion/common/misty/gcaves/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

#define PLAYER_HAS_SEARCHED "_player_has_searched"
#define PLAYER_HAS_FOUND    "_player_has_found"

void create_cave()
{
  set_long(VBFC_ME("my_long")+VBFC_ME("hidden_door"));

  add_item("door","@@door_desc");

  add_exit(CAVE_DIR + "t26", "west",      "@@cleare_search");
  add_exit(CAVE_DIR + "t24", "northeast", "@@cleare_search");
}

string door_desc()
{
  if(TP->query_prop(PLAYER_HAS_FOUND))
    return "You can just barely see a well hidden door in the southern wall.\n";
  return "You find no door.\n";
}

string hidden_door()
{
  if(TP->query_prop(PLAYER_HAS_FOUND)){
    return "You can also see a hidden door in the southern wall.\n";
  }
  return "";
}

void init()
{
    ::init();
    add_action("show_door", "show");
}

int show_door(string arg)
{
  string door, who;
  object *in_room;
  int i;

  NF("Show what to whom?\n");
  if(TP->query_prop(PLAYER_HAS_FOUND))
   {
    if((sscanf(arg, "%s to %s", door, who)<1) || (door != "door"))
     {
       return 0;
     }
    if((who != "all") && (!present(who, TO)))
     {
       return 0;
     }
    if(who == "all")
     {
       in_room=FILTER_LIVE(all_inventory(TO));
       if(sizeof(in_room) == 1)
        {
          TP->catch_msg("But you are alone here!\n");
          return 1;
        }
       for (i = 0; i < sizeof(in_room); i++)
           in_room[i]->add_prop(PLAYER_HAS_FOUND,1);
       TP->catch_msg("You show the hidden door to everybody in the room.\n");
       say(QCTNAME(TP)+" shows you a hidden door.\n");
       return 1;
     }
    if(present(who, TO))
     {
       if(present(who, TO) == TP)
        {
          TP->catch_msg("It is pretty stupid showing it to yourself.\n");
          return 1;
        }
       present(who, TO)->add_prop(PLAYER_HAS_FOUND,1);
       TP->catch_msg("You show the hidden door to "+QCTNAME(present(who, TO))+".\n");
       present(who, TO)->catch_msg(QCTNAME(TP)+" shows you a hidden door.\n");
       return 1;
     }
   }
  NF("Show what?\n");
  return 0;
}


int push_something(string str)
{
  if(str=="door" && TP->query_prop(PLAYER_HAS_FOUND))
  {
    if(CAN_SEE_IN_ROOM(TP))
    {
      TP->catch_msg("You wait while nobody looks at you, then you quickly "+
                    "push the door and...\nNothing happens.\n");
      return 1;
    }
    TP->catch_msg("You can't find it in this dark...\n");
  }
  return ::push_something(str);
}

int pull_something(string str)
{
  if(str=="door" && TP->query_prop(PLAYER_HAS_FOUND))
  {
    if(CAN_SEE_IN_ROOM(TP))
    {
//      TP->catch_msg("You cannot go there now! Ged is working there!\n");
//      return 1;
      TP->catch_msg("You wait while nobody looks at you, then you quickly "+
                    "pull the door, enter it and close it behind.\n");
      say("Ooops!!! Suddenly you realize that "+QCTNAME(TP)+" isn't here!\n");
      tell_room(CAVE_DIR+"d10",QCTNAME(TP)+" enters room through "+
                                           "secret door.\n");
      TP->move_living("M",CAVE_DIR+"d10");
      return 1;
    }
    TP->catch_msg("You can't find it in this dark...\n");
  }
  return ::pull_something(str);
}


int cleare_search()
{
  TP->remove_prop(PLAYER_HAS_SEARCHED);
  TP->remove_prop(PLAYER_HAS_FOUND);
  return 0;
}

string search_wall(object who, string str)
{
  int sum_skills = who->query_skill(SS_AWARENESS)+
                   who->query_skill(SS_LOC_SENSE);

  if(((str == "wall") || (str == "walls")) &&
     CAN_SEE_IN_ROOM(who))
  {
    if(who->query_prop(PLAYER_HAS_SEARCHED) && (sum_skills > 70) &&
         (random(sum_skills) > 40))
    {
      who->add_prop(PLAYER_HAS_FOUND, 1);
      return "Yes!!! Finally you discovered a secret door in the southern "+
             "wall. It was hidden really well. Even now you can hardly "+
             "see it. If someone doesn't know where to look... "+
             "Easy to miss it once you walk away.\n";
    }
    else
    {
      if(who->query_prop(PLAYER_HAS_SEARCHED))
        return "Your search reveals nothing more.\n";
      who->add_prop(PLAYER_HAS_SEARCHED, 1);
      return "Your search reveals nothing.\n";
    }
  }
}
