#pragma strict_types
inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string  long_func();

public void
create_gondor()
{
    set_short("hallway in the Shades hideout");
    set_long("@@long_func");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_item(({"marks","footprint","dust","floor"}),"@@exa_footprint");
    add_item(({"panels","walls","wall","panel"}),"@@exa_panels");
    add_item(({"east panel","east wall"}),"@@exa_east_panel");
    add_item(({"arch","archway"}),BSN("The archway is made of stone nothing " +
               "really special. It seems to lead into some sort of sleeping " +
               "chamber."));
    add_exit(SHADES_DIR +"sleep2","south",0);
    add_exit(SHADES_DIR + "hall1", "north", 0, 1);
}

string 
long_func()
{
    string longstr =
        "You are in a narrow hall in the Shades hideout. Oil-lamps are " +
        "suspended from the ceiling just like in the livingroom to the north. " +
        "To the south is an archway leading into another room. Light from " +
        "more lamps can be seen through the archway. The walls here are " +
        "covered with wooden panels.";
    if(TP->query_skill(SS_TRACKING)>49)
        longstr +=" Your keen sight focuses in on a light footprint going into the east wall.";
    else if (TP->query_skill(SS_TRACKING)>39)
        longstr +=" The dust on the ground here seems to have been disturbed.";
    else
        longstr +=" You see no signs that anything is down here.";
    return BSN(longstr);
}

int 
push_panel(string str)
{
  string vb  =query_verb(),
       vbs;

  vbs = " " + vb + ((vb=="kick")?"s":"es");

  if(!str)
      return 0;
  if (str == "panel" || str== "wall")
  {
      write("You "+vb+" at the "+str+"s, but nothing happens.\n");
      say(QCTNAME(TP)+vbs+" on the "+str+"s, but nothing happens\n.");
      return 1;
  }
  if (str == "east panel" || str == "east wall")
  {
      write(BSN("As you "+vb+" on the panel in the east wall, a part of the panel " +
                "opens and you stumble inside!"));
      say("As "+QCTNAME(TP)+" "+vb+" on the east wall, a part of the panel opens, "+
          "and "+TP->query_pronoun()+" stumbles inside!\n");
      TP->move(SHADES_DIR + "loot2");
      TP->command("l");
      say("Suddenly the west door opens, and "+QCTNAME(TP)+" comes stumbling in!\n",TP);
      tell_room(TO,"The panel closes behind "+TP->query_objective()+".\n");
      say("The west door closes again automatically.\n");
      return 1;
  }
  NF(CAP(vb)+" what?\n");
  return 0;
}

int 
tap_panel(string str)
{
    if(!str)
        return 0;

    if(str == "panel" || str == "wall")
    {
        write("You tap on the "+str+", but nothing happens.\n");
        say(QCTNAME(TP) + " taps on the "+str+", but nothing happens.\n");
        return 1;
    }
    if(str == "east panel" || str == "east wall")
    {
        write(BSN("As you tap on the panel on the east wall, the sound " +
                  "tells you that there is some empty space behind the panel."));
        say(QCTNAME(TP) + " taps on the panel on the east wall. It sounds rather strange.\n");
        return 1;
    }
    NF("Tap what?\n");
    return 0;
}

int 
pull_wall(string str)
{
    if(!str ||(str !="panel" && str !="wall" && str !="east wall" && str !="east panel"))
        return 0;
    write("You try to pull on the " + str + ", but you are unable to do so.\n");
    say(QCTNAME(TP) + " tries to pull on the " + str + ".\n");
    return 0;
}

string 
exa_footprint()
{
    if(TP->query_skill(SS_TRACKING)>49)
        return BSN("You study the footprint and see that there must be a room " +
                   "beyond the east wall.");
    else if(TP->query_skill(SS_TRACKING)>39)
        return BSN("You study the dust and see that it might just have been " +
                   "yourself disturbing the dust.");
    else
        return BSN("You study the area but find nothing of interest.");
}

string 
exa_east_panel()
{
    if(TP->query_skill(SS_AWARENESS)>49)
        return BSN("Studying the east wall closely, your keen ears " +
                   "make you aware that there must be another room " +
                   "behind the panel on the wall!");
    else
        return "You examine the north wall but cannot discern anything " +
                   "from your inspection.\n";
}

string 
exa_panels()
{
    if (TP->query_skill(SS_AWARENESS)>39)
       return BSN("Studying the walls closely, your keen ears make you " +
                  "aware that there must be another room behind the east " +
                  "wall!");
    else
        return "You examine the walls and panels, but do not discover anything.\n";
}

 
        
void 
init()
{
    ::init();
    add_action(push_panel, "push");
    add_action(push_panel, "press");
    add_action(push_panel, "kick");
    add_action(tap_panel,  "tap");
    add_action(pull_wall,  "pull");
}

