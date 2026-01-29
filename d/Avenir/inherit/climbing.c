/* Climbing.h   Cirion 031296 */

/* Example of use:
 *
 * inherit "/d/Avenir/inherit/climbing.c";
 * #include "/d/Avenir/common/common.h"
 *
 * create_room()
 * {
 *  set_short("halfway along a steep wall");
 *
 */
#pragma strict_types

inherit "/std/room";

#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>

#define DISTANCE_FELL "_Avenir_i_fallen_meters"
#define CLIMBING_ROPE "_Avenir_o_climbing_rope"
#define ROPE_I_LENGTH "_rope_i_length"
#define DANGLING      "_Avenir_rope_is_dangling"

static int     distance_down,
               distance_up,
               distance_from_top,
               distance_from_bottom,
               total_distance,
               climb_diff;

static string  jump_msg1,
               jump_msg2;

static object  toproom,
               downroom,
               uproom;

/*
 * function: rope_here()
 * returns:  the rope object if there is one in the
 *           toproom, and if it is long enough to reach
 *           down to the current room.
 * nb: redefine this to your taste
 */
object rope_here()
{
  int i;
  object *tied,
         *oblist,
         *ropes = ({});

  object rope;

  if(!toproom) return 0;

  oblist = all_inventory(toproom);

  if(!sizeof(oblist)) return 0;

  for(i=0;i<sizeof(oblist);i++)
  {
     if(function_exists("create_rope", oblist[i])   &&
       (tied[i] = oblist[i]->query_tied_to())       &&
       (oblist[i]->query_prop(DANGLING))            &&
       (oblist[i]->query_prop(ROPE_I_LENGTH) < distance_from_top) )
//      ropes += oblist[i];
     rope = oblist[i];
  }

//  if(!sizeof(ropes)) return 0;

//  add_item(({"rope"}), ropes[0]->long());
//  return ropes[0];

  add_item(({"rope"}), rope->long());
  return rope;

}

/*
 * functions: long_desc()
 * returns:   string telling whether there is a rope in the
 *            room and if the player is falling. It should be
 *            called from a VBFC in the set_long of the room.
 * nb: redefine it to your tastes.
 */
string long_desc()
{
  string str;

  return "";

  if(rope_here() && this_object() != toproom)
   str += " " + capitalize(LANG_ADDART(rope_here()->short())) + 
          " hangs down from above.";

  if(this_player()->query_prop(DISTANCE_FELL))
   str += " The wind rushes around you furiousley "+
          "as you fall faster and faster.";

  return str;
}

/*
 * Function names: long
 * Description   : The long description. We add the condition information
 *                 to it.
 * Arguments     : mixed for_obj - the object that wants to know.
 * Returns       : string - the long description.
 */
public varargs string
long(mixed for_obj)
{
  return ::long(for_obj) + long_desc();
}

/* function: calc_damage
 * argument: the player who has hit ground
 * use:      calculates the damage a player who has
 *           fallen will take, based on how far he
 *           has fallen (from the DISTANCE_FELL prop).
 *           Kills the player if necessary.
 */
void calc_damage(object who)
{
  float  force;
  int    damage, 
         distance;
  
  if(who->query_ghost() || who->query_link_dead()) return;

  distance = who->query_prop(DISTANCE_FELL);

  who->remove_prop(DISTANCE_FELL);

  if(!distance) return;

// should be SQRT(distance * 9.8)
//  force = ((9.8 * distance) * (who->weight() / 1000));
  force = 500.0;
  damage = ftoi(force);

  damage = (distance * distance);

  who->remove_hit_point(damage);
  if(who->query_hp() < 1) 
    {
     who->catch_msg("You smash into the ground, breaking "
           +"every bone in your body.\n");
     who->do_die(this_object());
     return;
    }  
  switch(damage)
  {
   case 0 .. 30:
    who->catch_msg("You land on your feet on the ground.\n");
    break;
   case 31 .. 50:
    who->catch_msg("You are bruised as you hit the ground "+
                   "hard.\n");
    break;
   case 51 .. 100:
    who->catch_msg("A shock runs through your legs as you "+
                   "crash into the ground.\n");
    break;
   case 101 .. 250:
    who->catch_msg("You slam into the ground in a painful heap.\n");
    break;
   case 251 .. 800:
    who->catch_msg("You feel crushed as you smash into the "+
                   "ground.\n");
    break;
   default:
    who->catch_msg("You hear bones break as you slam into "+
                   "the solid ground.\n");
    // Put in broken bones here
    break;
  }
}

/*
 * function: set_climb_diff
 * arguments: How difficult it is to climb up or down in
 *            the room
 */
void set_climb_diff(int difficulty)
{
  climb_diff = difficulty;
}

/*
 * function: query_climb_diff
 * returns: How difficult it is to climb up or down in
 *          the room.
 */
int query_climb_diff()
{
  return climb_diff;
}

/*
 * function: set_toproom
 * argument: The file name of the top room where the rope
 *           is tied.
 */
void set_toproom(string where)
{
  toproom = find_object(where);
}

/*
 * function: query_toproom
 * returns: The top room where the
 *          rope is tied.
 */
object query_toproom()
{
  return toproom;
}

/*
 * function: set_downroom
 * description: sets the room that you will be able to climb
 *              down into
 * arguments: the file path to the room, the distance
 *            in meters down (default is 10)
 */
public nomask varargs void
set_downroom(object where, int distance)
{
  downroom = where;

  if(distance)
   distance_down = distance;
  else
   distance_down = 10;
}

/*
 * function: query_downroom
 * returns: the room below you
 */
public object 
query_downroom()
{
  return downroom;
}

/*
 * function: query_distance_down
 * returns:  the distance down from this room to the
 *           next room.
 */
public int 
query_distance_down()
{
  return distance_down;
}

/*
 * function: set_uproom
 * description: sets the room that you will be able to climb
 *              up to
 * arguments: the file path to the room, the distance
 *            in meters up (default is 10)
 */
public nomask varargs void
set_uproom(object where, int distance)
{
  uproom = where;

  if(distance)
   distance_up = distance;
  else
   distance_up = 10;
}

/*
 * function: query_uproom
 * returns: the room above you
 */
public object 
query_uproom()
{
  return uproom;
}

/*
 * function: query_distance_up
 * returns:  the distance down from this room to the
 *           next room.
 */
public int 
query_distance_up()
{
  return distance_up;
}

/*
 * function: set_total_distance
 * arguments: The total climbing distance.
 */
void set_total_distance(int how_far)
{
   total_distance = how_far;
}

/*
 * function: query_total_distance
 * returns:  the total climbing distance in meters
 */
int query_total_distance()
{
  return total_distance;
}

/*
 * function: set_distance_from_top
 * argument: the distance (in meters) from the top
 *           of the climbing area (where a rope would
 *           be tied)
 */
void set_distance_from_top(int how_far)
{
   distance_from_top = how_far;
}

/*
 * function: query_distance_from_top
 * returns:  the distance from the top of the climbing
 *           area, where a rope would be tied.
 */
int query_distance_from_top()
{
  if(distance_from_top)
    return distance_from_top;
  else if(total_distance)
    return total_distance - distance_from_bottom;
  else
    return 0;
}

/* function: set_distance_from_bottom
 * argument: the distance (in meters) from the
 *           bottom of the climbing area.
 * nb: not really used, yet.
 */
void set_distance_from_bottom(int how_far)
{
  if(how_far < 1)
   distance_from_bottom = 1;
  else
   distance_from_bottom = how_far;
}

/*
 * function: query_distance_from_bottom
 * returns:  the distance, in meters, from the bottom
 *           of the climbing area (eg, the ground).
 */
int query_distance_from_bottom()
{
  if(distance_from_bottom)
    return distance_from_bottom;
  else if(total_distance)
    return total_distance - distance_from_top;
  else
    return 0;
}

/*
 * function: set_jump_msg
 * argument: the strings to be printed (to the player and
 *           his environment) when a player
 *           jumps down.
 */
void set_jump_msg(string str1, string str2)
{
  jump_msg1 = str1;
  jump_msg2 = str2;
}

/*
 * function: fall_down
 * argument: the person or thing falling
 * use:      moves the person or thing to the
 *           downroom (if it is defined), and
 *           adds the distance fallen onto the
 *           prop DISTANCE_FELL in the player
 */
void fall_down(object what)
{
  if(!present(what)) return;

  if(!downroom)
     return;

  if(!living(what))
   {
     tell_room(environment(what), "The " + QSHORT(what) +
               " falls downwards.\n");
     what->move(downroom);
     tell_room(environment(what), LANG_ADDART(QSHORT(what)) +
               " falls down from above.\n");
     return;
   }
  if(!what->query_prop(DISTANCE_FELL)) return;

  if(what->query_prop(DISTANCE_FELL) < 10)
   what->catch_msg("You start to fall straight down!\n");
  else
   what->catch_msg("You continue to fall.\n");

  what->add_panic(30);
  what->move_living("falling down", downroom, 0, 0);
  what->add_prop(DISTANCE_FELL, 
                query_distance_down() + 
                what->query_prop(DISTANCE_FELL) );
}

void enter_inv(object to, object from)
{
  ::enter_inv(to, from);

  if(!to->query_prop(DISTANCE_FELL) && living(to)) return;

  if(!downroom)
   {
     set_alarm(0.1, 0.0, &calc_damage(to));
     return;
   }

  if(!living(to) && 
     environment(to)->query_prop(ROOM_I_TYPE) == ROOM_IN_AIR)
   {
     to->add_prop(DISTANCE_FELL, 1);
     fall_down(to);
   }
   else if(to->query_prop(DISTANCE_FELL))
     set_alarm(3.0, 0.0, &fall_down(to));
}

void try_up(object who)
{
  int success, fat;
  string how;

  if(!uproom)
   {
     who->catch_msg("You cannot climb up from here.\n");
     return;
   }

  success = who->resolve_task(TASK_ROUTINE,
         ({ TS_DEX, TS_STR, SKILL_AVG, SS_CLIMB,
               SS_ACROBAT, SKILL_END }) );
  if(success < climb_diff)
   {
     who->catch_msg("Your hands slip from the rope as you "
         +"try to climb up it.\n");
     tell_room(environment(who), QCTNAME(who) + " looses " + 
          who->query_possessive() +
          " grip on the rope.\n");
     who->add_prop(DISTANCE_FELL, 1);
     fall_down(who);
     return;
   }
  switch(success - climb_diff)
   {
     case 0 .. 3:
      fat = 25;
      how = " with great difficulty";
      break;
     case 4 .. 10:
      fat = 20;
      how = " with massive effort";
      break;
     case 11 .. 20:
      fat = 15;
      how = " with some difficulty";
      break;
     case 21 .. 30:
      fat = 10;
      how = " with a bit of effort";
      break;
     case 31 .. 40:
      fat = 7;
      how = " gracefully";
      break;
     default:
      fat = 2;
      how = " effortlessly";
      break;
    }
 if(who->query_fatigue() - fat < 0)
  {
    who->add_fatigue(-fat);
    who->catch_msg("You try to pull yourself up the rope, "
                 +"but you are too tired.\n");
    return;
  }
 who->add_fatigue(-fat);
 who->catch_msg("You pull yourself up the rope"+how+".\n");
 tell_room(environment(who), QCTNAME(who) + " pulls " +
   who->query_possessive() + "self up the rope"+how+".\n", who);
 who->move_living("M", uproom, 0, 0);
 tell_room(environment(who), QCTNAME(who) + " climbs up from below.\n", who);
 return;
}

void try_down(object who)
{
  int success, fat;
  string how;

  if(!downroom)
   {
    who->catch_msg("You cannot climb down from here.\n");
    return;
   }

  if(!downroom->rope_here())
   {
     if(this_object() == toproom)
      {
        if(present("rope"))
         who->catch_msg("You would need to throw the rope "
           +"down to climb down it.\n");
        else
         who->catch_msg("You would need a rope to attempt to "
           +"climb down.\n");
        return;
       }

     who->catch_msg("The rope does not reach down any further. "
                   +"You will have to try to jump the rest of the "
                   +"way or climb back up.\n");
     return;
   }

  success = who->resolve_task(TASK_SIMPLE,
         ({ TS_DEX, TS_STR, SKILL_AVG, SS_CLIMB,
               SS_ACROBAT, SKILL_END }) );
  if(success < climb_diff)
   {
     who->catch_msg("Your hands slip from the rope as you "
         +"try to climb down it.\n");
     tell_room(environment(who), QCTNAME(who) + " looses " + 
          who->query_possessive() +
          " grip on the rope.\n");
     who->add_prop(DISTANCE_FELL, 1);
     fall_down(who);
     return;
   }
  switch(success - climb_diff)
   {
     case 0 .. 3:
      how = " with great difficulty";
      break;
     case 4 .. 10:
      how = " with massive effort";
      break;
     case 11 .. 20:
      how = " with some difficulty";
      break;
     case 21 .. 30:
      how = " with a bit of effort";
      break;
     case 31 .. 40:
      how = " gracefully";
      break;
     default:
      how = " effortlessly";
      break;
    }

 who->add_fatigue(-1);
 who->catch_msg("You climb down the rope"+how+".\n");
 tell_room(environment(who), QCTNAME(who) + " climbs down "+
           "the rope"+how+".\n", who);
 who->move_living("M", downroom, 0, 0);
 tell_room(environment(who), QCTNAME(who) + " climbs down from above.\n", 
           who);
 return;
}

int try_climb(string str)
{
  int success, fat;
  string how;

  notify_fail("Climb what?\n");
  if(!str) return 0;

  if(parse_command(str, ({}), "'up' [the] / [a] [rope]"))
   {
     notify_fail("There is no rope for you to climb up.\n");
     if(!rope_here())
       return 0;
     if(uproom)
     {
       try_up(this_player());
       return 1;
     }
   notify_fail("You cannot climb up from here.\n");
   return 0;
   }

  if(parse_command(str, ({}), "'down' [the] / [a] [rope]"))
   {
     notify_fail("There is no rope for you to climb down.\n");
     if(!rope_here())
       return 0;
     if(downroom)
      {
        try_down(this_player());
        return 1;
      }
     notify_fail("You cannot climb down from here.\n");
     return 0;
   }
}

int try_grab(string str)
{
  if(!this_player()->query_prop(DISTANCE_FELL))
    return 0;
  notify_fail(capitalize(query_verb()) + " what?\n");
  if(!str) 
    return 0;
  notify_fail(capitalize(query_verb()) + " for what?\n");
  if(!parse_command(str, ({}), "[for] / [at] [the] / [a] 'rope'") ||
     !rope_here())
    return 0;
  if(this_player()->resolve_task(TASK_DIFFICULT,
         ({ TS_DEX, TS_STR, SKILL_AVG, SS_CLIMB,
               SS_ACROBAT, SKILL_END }) ) < 
           this_player()->query_prop(DISTANCE_FELL))
  {
    write("You try to grab for the rope, but miss it "
         +"with your hands.\n");
    say(QCTNAME(this_player()) + " tries to reach for the rope, but "
         +"misses.\n");
    return 1;
  }
  write("You reach out and grab onto the rope with all your "
       +"strength.\nYou manage to halt you fall, and hang "
       +"onto the rope.\n");
  say(QCTNAME(this_player()) + " graps the rope and stops " + 
       this_player()->query_possessive() + " fall.\n");
  this_player()->remove_prop(DISTANCE_FELL); // Stops the player's fall
  return 1;
}

int do_jump(string str)
{
  notify_fail("You cannot really do that while you are falling.\n");
  if(this_player()->query_prop(DISTANCE_FELL))
   {
    write("You cannot really do that while you are falling.\n");
    return 1;
   }

  if(query_distance_from_bottom() > this_player()->query_stat(SS_DIS))
  {
    write("You are too high up, you don't dare to jump.\n");
    return 1;
  }

  if(!this_player()->query_prop("_Avenir_climbing_jumping"))
   {
     write("Looking down, you take a moment to reconsider "+
           "before you jump.\n");
     this_player()->add_prop("_Avenir_climbing_jumping", 1);
     return 1;
   }
  this_player()->remove_prop("_Avenir_climbing_jumping");
  if(jump_msg1)
   write(jump_msg1);
  else
   write("You let go of the rope and let yourself "
        +"fall straight down.\n");

  if(jump_msg2)
   say(QCTNAME(this_player()) + " " + jump_msg2);
  else
   say(QCTNAME(this_player()) + " lets go of the rope and "
      +"starts to fall striaght down.\n");

  this_player()->add_prop(DISTANCE_FELL, 1);
  fall_down(this_player());
  return 1;
}

int do_throw(string str)
{
  object ob;
  string dummy;

  notify_fail(capitalize(query_verb()) + " what?\n");
  if(!str) return 0;

  if(!parse_command(str, environment(this_player()),
     "[the] / [a] / [an] %o %s", ob, dummy))
    return 0;

  if(!CAN_SEE(this_player(), ob))
    return 0;

  notify_fail("You would need to be holding it to do that.\n");
  if(!present(ob, this_player()))
    return 0;

  if(ob->query_prop(OBJ_M_NO_DROP))
  {
    if(ob->query_prop(OBJ_M_NO_DROP) == 1)
      notify_fail("It cannot be dropped.\n");
    else
      notify_fail(ob->query_prop(OBJ_M_NO_DROP));
    return 0;
  }

// Is it a rope?
  if(function_exists("create_rope", ob))
  {
    if(ob->query_tied_to())
     {
      this_player()->catch_msg("You " + query_verb() +
        " the end of " + QSHORT(ob) + " downwards.\n" +
        "It uncoils as it drops down.\n");
      say(QCTNAME(this_player()) +
        " throws the end of " + LANG_ADDART(QSHORT(ob)) + 
        " downwards.\n");
      ob->move(environment(this_player()));
      ob->add_prop(DANGLING, 1);
      return 1;
     }
    write("You probably should have tied it "
       +"to something first.\n");
   }  
  this_player()->catch_msg("You " + query_verb() +
    " the " + QSHORT(ob) + ".\n");
  say(QCTNAME(this_player()) +
    " throws " + LANG_ADDART(QSHORT(ob)) + ".\n");

  ob->add_prop(DISTANCE_FELL, 1);
  ob->move(environment(this_player()));
  fall_down(ob);
  return 1;
}

void init()
{
  ::init();

  add_action("try_climb","climb",1);
  add_action("try_grab", "grab", 1);
  add_action("try_grab", "hold", 1);
  add_action("try_grab", "reach",1);

  if(!downroom) return;

  add_action("do_jump",  "fall", 1);
  add_action("do_jump",  "jump", 1);
  add_action("do_jump",  "leap", 1);
  add_action("do_throw", "toss", 1);
  add_action("do_throw", "throw",1);
}
