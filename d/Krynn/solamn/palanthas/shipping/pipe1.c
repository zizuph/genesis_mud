/* created by Aridor 12/14/93 */
/* Navarre Feb 2007, changed "The wall give off" to
 * "The wall gives off".
 * Milan 13.12.2007, added check and changed alarm to function call
 */

#include "windpipe.h"

inherit SHIP_ROOMBASE;


void
create_palan_room()
{
    set_short("Inside a vertical shaft");
    set_long("You are inside a vertical shaft. There are two small gems " +
	     "on the wall. Better not touch them, you'll never know what " +
	     "will happen. There is a ladder leading further down from the " +
	     "small platform you are standing on, but you can also climb " +
	     "up on the ladder. The walls of the shaft seem to glow a " +
	     "little.\n");
    
    add_exit(IN_WALL, "up",0,5);
    add_exit(SHIP + "pipeud1","down",0,1);
    
    LIGHT;
    
    add_item(({"shaft"}),
	     "The shaft is a round shaft and it is very wide, you can " +
	     "hardly see the wall on the other side. You wonder what the " +
	     "purpose of the shaft is.\n");
    add_item(({"wall","walls"}),
	     "The wall close to you is made from some unkown material. It " +
	     "is very smooth and the ladder you are standing on is bolted " +
	     "to the wall. You can hardly make out the wall on the other " +
	     "side of the shaft though. The wall gives off a strange glow, " +
	     "illuminating the shaft.\n");
    add_item("ladder",
	     "It's a very long ladder going up and down made from iron. You " +
	     "cannot see the bottom of it.\n");
    add_item(({"gems","small gems"}),
	     "These are two small gems set into the wall here. Maybe you " +
	     "shouldn't touch them, but then again, maybe you should.\n");
    add_item("gem",
	     "There are two gems there.\n");
}

void
init()
{
    ::init();
    if (TP->query_prop(PLAYER_S_BLOWN_DIR))
      write("The winds lessen and you gently float down to a platform in " +
	    "the pipe. The journey has reached its end.\n");
    TP->remove_prop(PLAYER_S_BLOWN_DIR);
    ADA("touch");
}

void
blow_me_away(object who)
{ 
	if (!objectp(who)) return; //Milan
    if (E(who) != TO)
    {
	  who->remove_prop(PLAYER_S_BLOWN_DIR);
	  return;
    }
    who->catch_msg("The wind suddenly turns in on itself and you are sucked " +
		   "into the shaft.\n");
    who->move_living("down, blown by the wind",SHIP + "pipe2",0,1);
}

string
wait_blow_me_away()
{
    TP->add_prop(PLAYER_S_BLOWN_DIR, "south");
    write("You can feel winds starting to rise up from the pipe.\n");
    set_alarm(itof(random(10) + 3), 0.0, &blow_me_away(TP)); //Milan
    return "";
}

int
touch(string str)
{
    NF("Touch what?\n");
    if (!str)
      return 0;
    NF("Nothing happens.\n");
    if (str == "gem" || str == "small gem")
      return 0;
    NF("Touch what?\n");
    if (str != "gems" && str != "small gems")
      return 0;
    TP->add_prop("_player_i_has_touched_gems",time());
    wait_blow_me_away();
    return 1;
}
