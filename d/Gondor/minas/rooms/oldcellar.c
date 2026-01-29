/*
 *    /d/Gondor/minas/rooms/oldcellar.c
 *
 *    Coded by Elessar.
 *
 *    Modification log:
 *    21-aug-1997, Olorin: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string  exa_panels();
public string  exa_north_panel();
public string  exa_stairs();
public string  exa_traces();
public string  long_desc();

public void 
create_gondor()
{
    set_short("in a dark, dusty basement");
    set_long(long_desc);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_item( ({ "marks", "traces", "trace", "dust", "floor"}),
	      exa_traces); 
    add_item( ({ "panels", "walls", "panel", "wall", }), exa_panels);
    add_item( ({ "north panel", "north wall", }), exa_north_panel);
    add_item( ({ "stairs", "stair" }), exa_stairs);
    add_item( ({ "cobwebs" }), BSN("There are cobwebs almost " +
	"everywhere under the ceiling of the room. All of them are " +
	"too high to reach them.")); 

    add_exit(MINAS_DIR + "rooms/oldhouse", "up", 0, 1);
}

public string 
long_desc()
{
   string  longstr = "You are in a dark and dusty cellar. The room " +
       "is empty, except a set of stone stairs leading up to the " +
       "room above. This room could have been used as a living " +
       "room earlier, as the walls are covered with wooden panels. ";
   if (TP->query_skill(SS_TRACKING) > 15) 
       longstr += "Your trained eyes quickly notice some traces in the dust on the floor. ";
   else if (TP->query_skill(SS_TRACKING) > 10) 
       longstr += "In the dim lighting of the room, you think you see some traces in the dust on the floor. ";
   longstr += "Cobwebs and dust gives you the impression that this room has been unused for a long time.";
   return BSN(longstr);
}

public int 
push_panel(string str)
{
    string  vb       = query_verb(),
	    vbs;

    vbs = " " + vb + ((vb=="kick" || vb=="knock") ? "s" : "es");

    if (!strlen(str))
	return 0;
    if ( (str == "panel") || (str == "wall") )
    {
	write("You "+vb+" at the "+str+"s, but nothing happens.\n");
	say(QCTNAME(TP)+vbs+" on the "+str+"s, but nothing happens.\n");
	return 1;
    }
    if ( (str == "north panel") || (str == "north wall") )
    {
	write(BSN("As you "+vb+" on the panel in the north wall, a part of the panel "+
          "opens, and you stumble inside!"));
	say("As "+QTNAME(TP)+vbs+" on the north wall, a part "+
	  "of the panel opens, and "+TP->query_pronoun()+" stumbles inside!\n", TP);
	TP->move_living("M",MINAS_DIR + "shades/shadeentr", 1);
	say("Suddenly the south door opens, and "+QNAME(TP)+" comes stumbling in!\n",TP);
	tell_room(TO,"The panel closes behind " +
		  TP->query_objective() + ".\n");
	say("The south door closes again automatically.\n");
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
    if(str=="north panel" || str=="north wall")
    {
        write(BSN("As you tap on the panel on the north wall, the sound " +
            "tells you that there is some empty space behind the panel."));
        say(QCTNAME(TP) + " taps on the panel on the north wall. It sounds rather strange.\n");
        return 1;
    }
    NF("Tap what?\n");
    return 0;
}

int pull_wall(string str)
{
    if(!str || (str != "panel" && str != "wall" && str != "north wall" && str != "north panel"))
        return 0;

    write("You try to pull on the " + str + ", but you are unable to do so.\n");
    say(QCTNAME(TP) + " tries to pull on the " + str + ".\n");
    return 1;
}

string exa_traces()
{
  if (TP->query_skill(SS_TRACKING)>17)
      return BSN("Studying the marks in the dust on the floor, your skilled eyes " +
          "tell you the traces lead towards the north wall of the room.");
  else if (TP->query_skill(SS_TRACKING)>12)
      return BSN("You study the dust closely, but it could be your imagination that " +
          "tricked you, since you're not able to make anything out of the traces.");
  else 
      return "You study the dusty floor carefully, but you can't see anything interesting.\n";
}

string exa_north_panel()
{
    if (TP->query_skill(SS_AWARENESS)>12)
        return BSN("Studying the north walls close, your keen ears "+
            "make you aware that there must be another room "+
            "behind the panel on the wall!");
    else 
        return "You examine the north wall and panel, but you don't discover anything.\n";
}

string exa_panels()
{
  if (TP->query_skill(SS_AWARENESS)>15)
      return BSN("Studying the walls closely, your keen ears "+
          "make you aware of that there must be another room "+
          "behind the panel on the north wall!");
  else 
      return "You examine the walls and panels, but you don't discover anything.\n";
}

string exa_stairs()
{
  if (TP->query_skill(SS_TRACKING)>10)
      return BSN("Studying the stairs closely, your trained eyes soon discover some " +
          "marks that indicate a very recent use of these stairs.");
  else 
      return "They are cold stone stairs, nothing special about them.\n";
}

public void 
init()
{
  ::init();

  add_action(push_panel, "push");
  add_action(push_panel, "press");
  add_action(push_panel, "knock");
  add_action(push_panel, "kick");
  add_action(tap_panel,  "tap");
  add_action(pull_wall,  "pull");
}    
