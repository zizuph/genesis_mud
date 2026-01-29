/*   upper6.c
 *
 * Upper levels of the Shipwreck.
 *
 * Baldacin@Genesis, July 2003
 * Patched the wheel for resetting - Tapakah, June 2011
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Calia/sys/water.h"
#include "/d/Calia/sea/sea_quests.h"
#include "defs.h"
inherit "/d/Calia/std/water_room";

int room_searched, wheel;

void
create_water_room()
{
    set_short("Quarter-deck of a wrecked ship");
    set_long("You are floating underwater at the quarter-deck of a "+
        "wrecked ship. This is where the captain used to stand when "+
        "he called out orders for his ship-crew. @@wheel_desc@@ and "+
        "a few barrels are scattered around. The only way back is "+
        "down to the main deck, using the stairs.\n");

/* Room tells borrowed from the sea rooms, created by Maniac & Khail. */
    set_tell_time(45);
    add_tell("A great, dark shape cuts through the water off to one " +
        "side, but it's gone again before you can see any details.\n");
    add_tell("A school of small, brightly coloured fish appear directly " +
        "in front of you, and accelerate around you on their way past. " +
        "Tickles a bit, doesn't it?\n");
    add_tell("The deep water darkens slightly as the sun is blocked by " +
        "a cloud high above.\n");
    add_tell("Something bumps you playfully from behind, at least you hope " +
        "it was playful, because it was gone when you looked around.\n");
        
    add_item(({"railwork","rails","railing"}),"They are etched "+   
        "with what was once, obviously, detailed engravings but have "+ 
        "now rotted beyond recognition.\n");
    add_item(({"wreck","shipwreck"}),"It used to be a pretty small ship, "+
        "about 25 meters, some sort of transportation ship. The ship is "+
        "decayed and rotting, it must have been down here for quite some "+
        "time. The salty water probably did its share of corroding too.\n");
    add_item(({"short stick","stick"}),"@@exa_stick@@");
    add_item(({"barrel","barrels", "rotting barrel", "rotting barrels"}),""+
        "They are all decayed and rotting, you can't really see anything "+
        "special about them.\n");
    add_item("deck", "It is the floorlike covering of the ship's surface. "+
        "It is made of wood, you can't see anything special about it.\n");
    
    add_item(({"steering wheel", "wheel"}),"@@exa_steeringwheel@@");
    
    add_prop(OBJ_S_SEARCH_FUN,"search_func");
    room_searched = 0;
    wheel = 0;

    add_swim_exit(WRECKU + "upper4","stairs");
    
}

void
reset_room()
{
  ::reset_room();
  wheel = 0;
}

string
exa_stick()
{
    if (wheel)
        return "A steering wheel is attached to the short stick.\n";
    return "This is most likely where the steering wheel used to "+
        "be attached. Perhaps you can find it and put it back!?\n";
}

string
exa_steeringwheel()
{
    if (wheel)
        return "A wheel that controls the steering of the ship.\n";
    return "Steering wheel? I don't see any, only a stick where one "+
      "most likely used to be attached.\n";
}

string
wheel_desc()
{
    if (wheel)
        return "A steering wheel is secured on a stick at "+
          "the deck floor";
    return "A short stick is secured to the deck floor";
}

string
search_func(object me, string arg)
{
   string *allowed_args = ({"barrel", "barrels", "rotting barrel", "rotting barrels"});
   string item = one_of_list(({ OBJ+"comb.c", OBJ+"drum.c", OBJ+"harp.c", OBJ+"mocha.c", OBJ+"rope.c" }));
   
   if (member_array(arg, allowed_args) != -1)
   {     
       if(room_searched || me->query_skill(SS_AWARENESS) < (15 + random(5)))
           return "";
       
       clone_object(item)->move(me, 1);
       room_searched = 1;
       return "You find "+LANG_ASHORT(item)+"!\n";
   }
   
   return "";
}

int
attach_wheel(string str)
{   
    object steering_wheel = present("shipwreck_wheel_", TP); 
    
    notify_fail("Attach what? A steering wheel.\n");
    if (!str || !parse_command(str, ({ }), "[the] [steering] 'wheel' "+
           "[to] [short] [stick]"))
        return 0;
           
    notify_fail("There is already a steering wheel in place!\n");
    if (wheel)
        return 0;

    notify_fail("But, you need a steering wheel for that!.\n");
    if (!steering_wheel)
        return 0;
     
    if(!TP->test_bit(SW_WHEEL_DOMAIN, SW_WHEEL_GROUP, SW_WHEEL_BIT))
    {
        write("You attach the steering wheel to the short stick.\n");
        write("Oh, How thoughtful of you!\n");
        TP->add_exp_quest(SW_WHEEL_EXP);
        TP->set_bit(SW_WHEEL_GROUP, SW_WHEEL_BIT);
        set_alarm(1.0, 0.0,&write("You feel slightly more experienced.\n"));
        log_file("shipwreck_steering_wheel", extract(ctime(time()), 4, 15) + " " +
          capitalize(TP->query_real_name()) + " solved the quest.\n");
        steering_wheel->remove_object();
        wheel = 1;
	return 1;  
    }
    
    write("You attach the steering wheel to the short stick.\n");
    write("Oh, How thoughtful of you!\n");
    steering_wheel->remove_object();
    wheel = 1;
    return 1;    
}

void
init()
{
    ::init();
    if (present("shipwreck_wheel_", TP))
        add_action(attach_wheel, "attach");
}
