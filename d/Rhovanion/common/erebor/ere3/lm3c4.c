inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include "door.h"
#define CAVE_DIR ERE_DIR + "ere3/"

int candle_out;
int light_room();

object west_door, guard, key, sarcophagus;

void reset_room();
int test();
 
 

void
create_cave()
{

  reset_room();

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(2);
  set_long("This is the gravechamber of Thorin Oakenshield. Its "
         + "sparsely furnished. In the centre of the room is a "
         + "sarcophagus standing on a red thick carpet. Above "
         + "the sarcophagus is hanging a big painting on "
         + "the wall.\n");

  add_item("painting","The painting is strong and bright in colors. "
         + "On it, you can see a young and powerful dwarf standing "
         + "on a battlefield. The Battle of Azanulbizar for sure.\n"
         + "In his right hand he holds a waraxe, but what "
         + "strikes you most is the thick oakbranch he is wearing "
         + "as a shield on his left arm. Around him lay many dead "
         + "orcs and dwarves, slayed during the cruel battle. Below the "
         + "frame you can see a plaque.\n"); 

  add_item("carpet","The bloodred carpet is very think. When you "
         + "set your foot on it, you sink down a bit, as it was a "
         + "well looked-after grass lawn. The carpet has no traces "
         + "of ever beeing used.\n");

  add_item("frame","The frame is relatively simple. Just an oak frame "
         + "with a few ornaments and carvings.\n");

  add_item(({"ornaments","carvings"}),"The ornaments and carvings are not "
         + "particullarly fine or soft. The carpenter must have tried "
         + "make them robust and solid to add to the atmosphere of the "
         + "painting.\n");

  add_item("plaque","The plaque reads:\n\n\n\n"
         + "                  Thorin Oakenshield 2746-2941\n\n\n");

  add_item("base","The base of rock is a huge piece of "
         + "rock, carved out like a big pillar from the floor, "
         + "when they dug out this chamber in the mountain.\n");

  add_item("candle","The wax candle is about 3 feet "
         + "long, but you guess it was longer when someone light it. "
         + "It will probably burn for a very long time.\n");

  west_door = clone_object(CAVE_DIR + "door_lm3c4");
  west_door->move(TO);
  west_door->set_key(GOLD);
 
  /* This is what is needed for the east door */
  key = clone_object(CAVE_DIR + "gold_key");
  key -> set_key(GOLD); /* Setting id number of the key. */
 
}

void
reset_room()
{
 if(sizeof(FILTER_LIVE(all_inventory(TO))))
    {
      return;
    }
    sarcophagus->remove_object();
    sarcophagus = clone_object(CAVE_DIR+"sarcophagus");
    sarcophagus->move(TO);
}
 
void
sunset()
{
    if (objectp(guard))
        guard->close_tomb();
}
int
ext_candle(string arg) 
{
    if(candle_out)
    {
    TP->catch_msg("But the candle is already blown out!\n");
    return 1;
    }
    if(arg != "candle") 
    {
    TP->catch_msg("Blow out what?\n");
    return 1;
    }
    TP->catch_msg("You inhale some air and blow out the candle.\n");
    say(QCTNAME(TP)+" takes a deep breath and blows out the candle.\n");
    candle_out = 1;
    add_prop(ROOM_I_LIGHT,0);
    set_alarm(15.0,0.0,light_room);
    return 1;
}
 
int
test()
{
  if(present("thain",TO))
  {
     guard->command("say present!");
    return 1;
  }
  return 0;
}
 
int
light_room()
{
  if(present("thain",TO))
  {
    guard->command("emote lights the candle again!");
    add_prop(ROOM_I_LIGHT,1);
    guard->command("shout Dont do that again. Im warning you!");
    return 1;
  }
  return 0;
}
 
int
hide_sarc(string arg) 
{
 
  if(arg != "behind sarcophagus") 
  {
    TP->catch_msg("Hide behind what?\n");
    return 1;
  }
  if((present("thain",TO)))
  {
    guard->command("Shout Stop that at once!");
    TP->catch_msg("Thain pokes you in the ribs!\n");
    return 1;
  }
    TP->catch_msg("Quickly before someone can see you, you take "
                  + "a step forward and hide behind the "
                  + "sarcophagus.\n");
    return 1;
}

init()
{
    ::init();
    add_action("ext_candle", "blow");
    add_action("hide_sarc", "hide");
}
