/*Created by Stevenson*/
/* Cave Entrance to leave the caverns */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

static int rope_present = 0;


void
enter_inv(object ob, object old)
{
    rope_present = (ICE_OUT + "back_waterfall")->query_rope();
    ::enter_inv(ob, old);
}


void 
reset_icewall_room() 
{
    (ICE_OUT+"back_waterfall")->reset_room();
    LIGHT
}

void
init() 
{
    ADD("do_climb","climb");
    ADD("fall","jump");
    ::init();
}

void
create_icewall_room() 
{
    set_short("Noisy Cave");
    set_long(
	     "You find yourself in a small cave. Directly in front of you is "
	     + "the backside of a mighty waterfall. Its roaring drowns out "
	     + "all other noises. The mist in the air will have you drenched "
	     + "very soon if you don't do something. @@show_rope@@"
	     + "\n");
    
    add_cmd_item("rope","test","It doesn't look very strong.\n");
    add_cmd_item("waterfall","enter","Perhaps you should jump into it?\n");
    add_item("rope","@@item_rope");
    add_item("waterfall","It is thundering in intensity and fills the room "
	     + "with a slight mist. You can see light through the other side.\n");
    add_item("light","You look at the light very closely and get your nose wet.\n");
    add_item(({"rock","outcropping"}),"@@item_rock");
   add_exit(QUEST+"path3","east");
    set_alarm(1.0,0.0,"roar");
    
    LIGHT;
    reset_icewall_room();
}

int
fall() 
{
    write("Mustering up your courage, you run out and jump through "
	  + "the mighty, raging waterfall.\n");
    say(QCTNAME(TP) + " runs and jumps through the waterfall.\n");
    set_alarm(1.0,0.0,"splash");
    return 1;
}

void
splash() 
{
    write("\nAs you fall, you narrowly miss the rocks and land "
	  + "safely in the water with a loud splash."
	  + "\n");
    tell_room(ICE_OUT+"back_waterfall", "You see " + QCTNAME(TP) + " "
	      + "fall down from above and land in the water.\n");
    this_object()->move_player();
}

string 
show_rope() 
{
    if (rope_present) 
      return "\nThere is a rope here. ";
    return "";
}

string 
item_rope() 
{
    if (rope_present) 
      return "The rope is old and very frayed. It "
	+ "is tied off to a rocky outcropping and leads out through "
	+ "the waterfall.\n";
    return "What rope?\n";
}

string 
item_rock() 
{
   if (rope_present) 
     return "There is a rope tied to it.\n";
   return "It is a rocky outcropping.\n";
}

int 
do_climb(string str) 
{
    if ((str == "rope" || str == "down rope") && rope_present) 
    {
	write("You grasp the rope firmly in both hands and begin to "
	      + "climb down through the waterfall.\n");
	if ((TP->weight() / TP->max_weight())*100 > 70) 
	{
	    say(QCTNAME(TP)+" grabs the rope and begins to climb out "
		+ "through the waterfall.\n");
	    tell_room(ICE_OUT+"back_waterfall","You see "+QTNAME(TP)
		      + " fall down from above and land with a loud crunch.\n");
	    set_alarm(1.0,0.0,"do_fall_down");
	    return 1;
	}
	say(QCTNAME(TP)+" grabs the rope and climbs out backwards "
	    + "through the waterfall.\n");
	tell_room(ICE_OUT+"back_waterfall",QCTNAME(TP)+" arrives "
		  + "sliding down the rope.\n");
	set_alarm(1.0,0.0,"move_player");
	return 1;
    }
    if (rope_present) 
    {
	write("Climb what?  The rope maybe?\n");
	return 1;
    }
    NF("Climb what?\n");
    return 0;
}

void
move_player() 
{
    TP->move_living("M",ICE_OUT+"back_waterfall",1,0);
}

void
do_fall_down() 
{
    write("Suddenly, you hear a snapping sound and you begin to fall.\n"
	  + "\n . . . . . . . O U C H ! ! ! ! !\n");
    TP->reduce_hit_point(500);
    if (TP->query_hp() <= 0) TP->do_die(TO);
    (ICE_OUT + "back_waterfall")->break_rope();
    move_player();
    tell_room(QUEST+"cave","You hear a shriek and a loud thump "
	      + "from the other side of the waterfall.\n");
}

void
break_rope() 
{
    rope_present = 0; 
}

void
make_rope() 
{
    rope_present = 1; 
}

