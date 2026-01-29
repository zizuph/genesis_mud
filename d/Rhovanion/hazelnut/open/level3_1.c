inherit "/std/room";

#include "default.h"
#include "tower_defs.h"

#define MIN_AWARENESS_NEEDED 20
#define MIN_AWARENESS_FOR_CLUE 10

static int is_disarmed;

void
create_room()
{
   set_short("Third floor");
   set_long(break_string("You are hanging on for dear life at the top of the "+
        "Tower of Puzzles. The floor below doesn't look all that inviting "+
        "from this angle. The wall you are hanging to, is made of packed "+
        "stones, arranged in a neat way interlocking with each other.\n", 76));
   
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(OBJ_S_SEARCH_FUN, "search_fun");
   add_prop(OBJ_I_SEARCH_TIME, 5);

   add_item("floor","The floor is far below, and you would certainly "+
        "die if you fell from this\ndistance.\n");
   add_item(({"wall","stone","stones"}),"The wall is made of closely "+
        "packed stones, quite large in character.\n");
   
   is_disarmed = 0;
}

int query_is_disarmed() { return is_disarmed; }

void set_is_disarmed(int i) { is_disarmed = i; }

void
reset_room()
{
   ::reset_room();
   is_disarmed = 0;
}

string
search_fun(object player, string what)
{
   int awareness;
   
   if(what != "wall" && what != "stones")
   {
      return 0;
   }
   awareness = player->query_skill(SS_AWARENESS);
   awareness += random(awareness + 1);
   
   if((awareness >= MIN_AWARENESS_NEEDED) && (!query_is_disarmed()))
   {
      remove_item("crack");
      add_item("crack","The crack holds some sort of serpent, you need some"+
        "thing to lure it out with.\n");
      return break_string("You search the wall carefully, as you are very "+
        "high up here, and discover in a small crack, some sort of serpent.\n"
, 76);
   }
   
   if((awareness >= MIN_AWARENESS_FOR_CLUE) && (!query_is_disarmed()))
   {
      return break_string("You search the wall very carefully, and think "+
        "that one of the cracks has something secreted away in it.\n", 76);
   }
   
   if(query_is_disarmed())
      return break_string("You search the wall, but realize that it is "+
      "safe to climb up.\n", 76);
}

void
init()
{
   ::init();
   add_action("do_climb","climb");
}

int
do_climb(string str)
{
   int ran;
   
   NF("Climb where?\n");
   if(!str)
      return 0;
   if(str == "up")
   {
      if(query_is_disarmed())
      {
         if(this_player()->resolve_task(TASK_ROUTINE, 
                  ({ TS_STR, SS_CLIMB }) ) >0 ) 
         {
                write("You climb through the trapdoor.\n");
                tell_room(ENV(TP), QCTNAME(TP)+" climbs up through the "+
                "trapdoor.\n", TP);
                TP->move_living("M","/d/Emerald/room/puzzle/top", 0);
                tell_room(ENV(TP), QCTNAME(TP)+" arrives from below.\n", TP);
                return 1;
         }
         notify_fail("You try but can't find the handholds to climb up.\n");
         return 0;
      }
      write(break_string("As you climb the wall, a serpent strikes out, and "+
        "latches it's fangs onto your hand. You feel heavier, and fall "+
        "backwards into nothingness.\n", 76));
      tell_room(ENV(TP), QCTNAME(this_player())+" is attacked by a serpent.\n"+
        CAP(POS(TP))+" falls backwards to the ground below.\n", TP);
      TP->move_living("M","/d/Emerald/room/puzzle/ground",0);
      tell_room("/d/Emerald/room/puzzle/ground",QCTNAME(this_player())+
	" comes plummeting down from above, to hit the ground hard.\n", TP);
      write("\nYou hit the ground hard.\n");
      TP->reduce_hit_point(9*(TP->query_max_hp())/10);
      if(TP->query_hp() <= 0)
         TP->do_die();
      return 1;
   }
   if(str == "down")
   {
      if(TP->query_prop(PUZZLE_LEVEL_TWO_ONE))
         {
         TP->move_living("M","/d/Emerald/room/puzzle/level2_1", 0);
         return 1;
      }
      if(TP->query_prop(PUZZLE_LEVEL_TWO_TWO))
         {
         TP->move_living("M","/d/Emerald/room/puzzle/level2_2",0);
         return 1;
      }
      if(TP->query_prop(PUZZLE_LEVEL_TWO_THREE))
         {
         TP->move_living("M","/d/Emerald/room/puzzle/level2_3", 0);
         return 1;
      }
      if(TP->query_prop(PUZZLE_LEVEL_TWO_FOUR))
         {
         TP->move_living("M","/d/Emerald/room/puzzle/level2_4", 0);
         return 1;
      }
      tell_room(ENV(TP), QCTNAME(this_player())+" climbs down from "+
         "above.\n", TP);
      write("You climb down the wall, to the ground.\n");
      return 1;
   }
   notify_fail("Climb where?\n");
   return 0;
}
