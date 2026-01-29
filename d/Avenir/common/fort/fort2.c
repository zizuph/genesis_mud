// file name: d/Avenir/common/outpost/fort2.c
// creator(s):  Kazz    Feb '95
// purpose:     first fort room entered via the gate (from cave2)
// note:	
// last update: Cirion, Feb 1996
//                Added Kilnar to this area, see 
//               ~Avenir/private/QUESTS/outpost_water.doc
//          Lilith Apr 2022:  Fort makeover.
# pragma strict_types

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include <macros.h>
#include <stdproperties.h>

inherit OUTPOST +"fort_base";

#define OTHER_SIDE "/d/Avenir/common/outpost/cave2.c"
#define LIST       ("/d/Avenir/union/list")
#define ENEMY(x)   (LIST->query_enemy(x))
#define FRIEND(x)  (LIST->query_friend(x))
#define SEE_EAST   ({ OUTPOST + "fort5", OUTPOST + "fort3" })
#define SEE_WEST   ({ OUTPOST + "cave2", OUTPOST + "cave1", OUTPOST + "cave3"})

object kilnar;

int door_closed;
int do_open(string str);
int enemy_test(object ob);

string 
east_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_EAST); i++)
    if((room = find_object(SEE_EAST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " where you can see " + COMPOSITE_LIVE(live);
  }
  return "";
}

string 
west_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_WEST); i++)
    if((room = find_object(SEE_WEST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "You can see "+ COMPOSITE_LIVE(live) +
       " on the other side.\n";
  }
  return "The window looks out into the cave beyond.\n";
}

void
init()
{
    ::init();
    add_action(do_open, "open" );
}

void
reset_fort_room()
{
    if (!objectp(kilnar))
    {
	kilnar = clone_object(MON+"kilnar");
	kilnar->move(TO);
    }
    kilnar->reset_wangle();
    kilnar->reset_quest();
}

int
enemy_test(object ob)
{
    if (IS_INFIDEL(ob) || ENEMY(ob))
        return 1;
    else
        return 0;
}

void
create_fort_room()
{
	// add_exit_views() uses the short, so using lower case and articles.
    set_short("the forecourt of Fort Sybarus");
    set_long("You stand inside the gate of Fort Sybarus, "+ 
        "in the forecourt between the north and south towers. "+
	    "The entire fortress appears to be built from "+
	    "and into the black stone native to this place. "+
		"Pale limestone cobbles gleam underfoot, providing "+
        "a stark contrast. "+
        "The center courtyard of the fort lies east"+
        "@@east_view@@, and beyond it, to the northeast, "+
        "you catch a glimpse of a dark sea. "+
        "A wide wooden door stands at the base of the black "+
        "tower built into the south wall of cavern. "+
        "West is the black stone gate which controls access to "+
        "and from this place.\n");
    
	add_npc(MON + "food_merch", 1);
	add_npc(MON + "dw_guard", 1);
	
    add_exit("cave2","west", "@@try_west");
    add_exit("fort3","east",0);
    add_exit("tower_floor", "south", "@@try_south");
  
    // from fort_base.c
    add_exit_views(); 
    add_towers_out(); 
    add_gate_items();
	add_basic_fort();
    
	add_item(({"door"}),
       "There is door is at the base of the south tower.\n");
    add_item(({"north"}),
       "North is the exterior wall of the north tower.\n");
    add_item(({"tower door", "south door", "wood door", "wooden door"}),
       "The wooden tower door is closed. You don't hear any noise "+
       "coming from behind it.\n" );
    add_item(({"tower window", "big window", "high window"}),
       "There are some slit-like windows and one big window a few "+
       "levels up. It looks out over the courtyard of the fort, "+
	   "commanding a great view.\n" );
    add_item(({"metal window", "window"}), "@@west_view@@");
    add_cmd_item(({"gate", "gates", "black gate",
       "on gate" }), 
       ({"knock", "bang", "hit", "pound"}), "@@knock_gate");
    add_item(({"forecourt", "fore court"}), "This is the "+
       "forecourt, the small, open space between the two "+
       "towers. It is where the gate opens into.\n");
				
    reset_fort_room();

} // create_room()

int
knock_gate()
{

    if(!OTHER_SIDE->query_closed())
    {
        notify_fail("The black stone door is already open.\n");
        return 0;
    }

    write("You knock on the black stone door.\n");
    say(QCTNAME(TP)+ " knocks on the black stone door.\n");

    if (TP->query_prop(OBJ_I_INVIS) || TP->query_prop(OBJ_I_HIDE))
    {
        write("The dwarven guards look around as though getting ready to "+
            "open the door but don't see who knocked.\n");
        return 1;
    }

    if (TP->query_hooded())
    {
	write("The dwarven guards look at you quizzically.\n");
	say("The dwards guards look at "+ QTNAME(TP) +" quizzically.\n");
	return 1;
    }

    if (enemy_test(TP))
    {
        write("The dwarven guards make a hand-signal to someone "+
            "on the other side of the door.\n");
        write("A booming dwarven voice shouts: I'd sooner eat "+
            "phynos meat than let you pass, you filth! Begone.\n");
        say("The dwarven guards look "+QCTNAME(TP)+" up and down, "+
            "then make a hand-signal towards someone on the "+
            "other side of the door.\n");
        say("A booming dwarven voice shouts: I'd sooner eat "+
            "phynos meat than let you pass, you filth! Begone.\n");
        return 1;
    }

    write("The dwarven guards on both sides of the gate peer at you.\n");
    say("The dwarven guards on both sides of the gate peer at "+ QCTNAME(TP) +".\n");

    (OTHER_SIDE)->open_door();
    set_alarm(8.0, -1.0, "close_door");
    return 1;
}

void
close_door()
{
    (OTHER_SIDE)->close_door();
    return;
}

int
try_west()
{
    if (!interactive(TP))
        return 0;

    if((OTHER_SIDE)->query_closed())
    {
        write("The black stone door is closed.\n");
        return 1;
    }

    if(enemy_test(TP))
    {
        close_door();
        return 1;
    }
    write("You walk past the open door and into the fortress.\n");
    return 0;
}

int 
do_open(string str)
{
    object tower_room;
    object tp = this_player();

    if ((str == "door") || (str == "the door") || (str == "tower door") ||
         (str == "wooden door") ||  (str == "wide wooden door"))
    {
      tp->catch_msg("You open the tower door and enter.\n");
	  say(QCTNAME(tp) +" opens the tower door and enters it.\n"+
        "The door closes.\n", tp);
      tp->move_living("M", OUTPOST + "tower_floor", 1 );
	  tp->catch_msg("The wide wooden door closes behind you.\n" );
	  tower_room = find_object(OUTPOST + "tower_floor");
	  tell_room(tower_room, QCTNAME(tp) +
		  " enters through the tower door.\n", tp);
        return 1;
    }
	
    notify_fail("The black stone door can only be opened by the guards.\n");
    return 0;

} // do_open()

  
int
try_south()
{
    write("You walk right into the door! Ouch!  "+
        "Perhaps you should try opening it?\n");
	return 1;
}

