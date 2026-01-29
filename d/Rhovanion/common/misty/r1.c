/* highpass */
/*
 *  Here player is rewarded for success in climbing down.
 *  Reward is XP + possibility to train SS_CLIMB up to 60
 *
 *   Milan
 */

inherit "/lib/skill_raise";
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <language.h>
#include <money.h>
#include "climb.h"

#define PLAYER_HAS_FOUND    "_found_hole_in_roots"

#define REWARD  1500
#define GROUP   0
#define BIT     4

create_room()
{
    set_noshow_obvious(1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(OBJ_S_SEARCH_FUN, "search_roots");
    add_prop(OBJ_I_SEARCH_TIME, 15);
    set_short("top of the rock");
    set_long(VBFC("climber_guild")+
                "You are standing on small plateau on the top of the "+
                "high dark rock. It is a very good feeling to be here, "+
                "resting. You still can't believe that you have climbed "+
                "up. But eventually you will "+
                "have to go down again. Of course, it is much easier "+
                "than climbing up. The worst thing that can happen is "+
                "that you will fall down. So what? On your way up you "+
                "fell many times. Now it will be only once.\n"+
             VBFC("you_see_hole"));


    add_item("rock", "Dont look around too long! You must climb down "+
                      "now. Or if you are crazy enough then you may "+
                      "simply jump down.\n");
    add_item("plateau", "Very strange that there is a tree "+
                        "on this plateau. You wonder how this tree could "+
                        "grow on such compact rock.\n");
    add_item("tree", "It is a nearly dry oak. You can see many twisted "+
                        "roots that are desperately trying to find some "+
                        "hole or crack in the rock and so give some support "+
                        "and life to this tree.\n");
    add_item("roots", "You see a huge maze of roots here.\n");
    add_item("maze", "You see a huge maze of roots here.\n");
    add_item("hole", "@@hole_desc@@");

    add_exit(ROOM_D, "_never_use_1", 1);
    add_exit(ROOM_CLIMB, "_never_use_2", 1);

    create_skill_raise();
    set_up_skills();
}

string
you_see_hole(){
  if(TP->query_prop(PLAYER_HAS_FOUND)){
    return "You can also see a hole hidden between roots.\n";
  }
  return "";
}

string
hole_desc(){
  if(TP->query_prop(PLAYER_HAS_FOUND)){
    return "This hole was well hidden among the roots. It is small but "+
           "maybe you can squeeze through it.\n";
  }
  return "You find no hole.\n";
}

init()
{
    init_skill_raise();
    ::init();
    add_action("climb_down", "climb");
    add_action("look_down", "look");
    add_action("jump_down", "jump");
    add_action("enter_hole", "enter");
}

int climb_down(string down) {
int _how_high_;
 if(down=="down")
  {
   TP->remove_prop(PLAYER_HAS_FOUND);
   _how_high_ = random(TP->query_skill(SS_CLIMB));
   if(sizeof(TP->query_weapon(-1)))
     _how_high_ = MIN(_how_high_ , 10+random(20));

   TP->move_living(0,ROOM_CLIMB);
   if(sizeof(FILTER_LIVE(all_inventory(find_object(ROOM_CLIMB)))) > 1)
    {
     TP->catch_msg("You decided to wait until the other climber "+
                      "finishes. It is really safer...\n");
     TP->move_living(0,ROOM_U);
     return 1;
    }
   else
    {
     START_UP_D; START_UP_U; START_UP;
     call_out("climb_5",DELAY,_how_high_);
     return 1;
    }
  }
 else
  {
   NF("Where do you want to climb?\n");
   return 0;
  }
}

int climb_5(int _how_high_){
 if(_how_high_ < 5)
  {
   FALL_DOWN_W; FALL_DOWN_D; SHOUT_D_W; SHOUT_U; TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*(30-_how_high_));
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_25; HIGH_25_D;
 call_out("climb_10",DELAY,_how_high_);
 return 1;
}

int climb_10(int _how_high_){
 if(_how_high_ < 10)
  {
   FALL_DOWN_W; FALL_DOWN_D; SHOUT_D_W; SHOUT_U; TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*(30-_how_high_));
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_20; HIGH_20_D;
 call_out("climb_15",DELAY,_how_high_);
 return 1;
}

int climb_15(int _how_high_){
 if(_how_high_ < 15)
  {
   FALL_DOWN_W; FALL_DOWN_D; SHOUT_D_W; SHOUT_U; TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*(30-_how_high_));
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_15; HIGH_15_D;
 call_out("climb_20",DELAY,_how_high_);
 return 1;
}

int climb_20(int _how_high_){
 if(_how_high_ < 20)
  {
   FALL_DOWN_W; FALL_DOWN_D; SHOUT_D_W; SHOUT_U; TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*(30-_how_high_));
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_10; HIGH_10_D;
 call_out("climb_25",DELAY,_how_high_);
 return 1;
}

int climb_25(int _how_high_){
 if(_how_high_ < 25)
  {
   FALL_DOWN_W; FALL_DOWN_D; SHOUT_D_W; SHOUT_U; TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*(30-_how_high_));
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_5; HIGH_5_D;
 call_out("climb_30",DELAY,_how_high_);
 return 1;
}

int climb_30(int _how_high_){
 if(_how_high_ < 30)
  {
   FALL_DOWN_W; FALL_DOWN_D; SHOUT_D_W; SHOUT_U; TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*(30-_how_high_));
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 END_DOWN_D; END_DOWN; TP->move_living("M",ROOM_D);

 /****************************************/
 /*   HERE I REWARD FOR GOOD CLIMBING    */
 /****************************************/
 if(TP->test_bit("Rhovanion",GROUP,BIT)) return 1; /* did it before */
 if(TP->set_bit(GROUP,BIT))
 {
   TP->catch_msg("You feel more experienced.\n"+
                 "Only now you are THE CLIMBER!\n");
   TP->add_exp(REWARD,0);
   write_file("/d/Rhovanion/log/climbing", TP->query_name() +
              " got " + REWARD + " exp. " + ctime(time()) + ".\n");
   SORT_FILE("/d/Rhovanion/log/climbing");
   TP->save_me(1);
   return 1;
 }
 NF("There was something wrong. Please report this and try climb again.\n");
 return 0;
}


int look_down(string down){
object *in_room_d, *in_room_climb;
string l_o_names="";
int i;
 if(down=="down")
  {
   say(QCTNAME(TP)+" bends over the edge and looks down.\n");
   tell_room(ROOM_D,QCTNAME(TP)+" peeps from the top of the rock.\n");
   tell_room(ROOM_CLIMB,QCTNAME(TP)+" peeps from the top of the rock.\n");
   TP->catch_msg("After you bend over the edge you can see the whole "+
                    "rock that you have climbed up.\n");
   in_room_d=FILTER_LIVE(all_inventory(find_object(ROOM_D)));
   in_room_climb=FILTER_LIVE(all_inventory(find_object(ROOM_CLIMB)));
   if(sizeof(in_room_d) == 1)
    {
     TP->catch_msg("You see "+QSHORT(in_room_d[0])+" below the rock.\n");
    };
   if(sizeof(in_room_d) > 1)
    {
     for (i = 0; i < (sizeof(in_room_d)-2); i++) 
               l_o_names += (QSHORT(in_room_d[i])+", ");
     l_o_names += (QSHORT(in_room_d[sizeof(in_room_d)-2])+" and "+
                   QSHORT(in_room_d[sizeof(in_room_d)-1]));
     TP->catch_msg("You see "+l_o_names+" below the rock.\n");
    };
   if(sizeof(in_room_climb) > 0)
    {
     TP->catch_msg(QCTNAME(in_room_climb[0])+" is climbing the rock.\n");
    }
   return 1;
  }
 NF("Where do you want to look?\n");
 return 0;
} 

int jump_down(string down){
 if(down=="down")
  {
   TP->remove_prop(PLAYER_HAS_FOUND);
   TP->catch_msg("With a mad laugh you run to the edge of the rock and "+
                "jump down.\n"+"You are so mad that you don't even "+
                "feel how it hurts when you fall to the ground.\n");
   say("With a mad laugh "+QSHORT(TP)+" runs to the edge of the rock and "+
       "jumps down.\n");
   tell_room(ROOM_D,"You hear someone laugh from above.\n");
   tell_room(ROOM_CLIMB,"You hear someone laugh from above.\n");
   tell_room(ROOM_D,"You look up and see "+
             "how "+QSHORT(TP)+" jumps from the top of the rock.\n");
   tell_room(ROOM_CLIMB,"You look up and see "+
             "how "+QSHORT(TP)+" jumps from the top of the rock.\n");
   TP->move_living("M",ROOM_D);
   TP->reduce_hit_point(DAMAGE*35);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 NF("Where do you want to jump? Down???/n");
 return 0;
}

string
search_roots(object searcher, string str)
{
int sum_skills = searcher->query_skill(SS_AWARENESS);

  if(str == "roots")
   {
   if(CAN_SEE_IN_ROOM(searcher))
    {
      if(searcher->query_prop(PLAYER_HAS_FOUND))
       {
         return "Your search reveals nothing more.\n";
       }
      if(sum_skills > 40)
       {
           searcher->add_prop(PLAYER_HAS_FOUND, 1);
           return "You have found a hole hidden between roots.\n";
       }
      else
           return "Your search reveals nothing special.\n";
    }
   else
     return "Your search reveals nothing special.\n";
   }
  return "";
}

int enter_hole(string hole){
  object *in_room=FILTER_LIVE(all_inventory(TO));
  int i;

  if((hole=="hole") && TP->query_prop(PLAYER_HAS_FOUND))
   {
     for (i = 0; i < sizeof(in_room); i++)
       in_room[i]->add_prop(PLAYER_HAS_FOUND,1);
     TP->catch_msg("You squeeze through a hole under the roots.\n");
     say(QCTNAME(TP)+" squeezes through a hole under the roots.\n");
     tell_room(MISTY_DIR+"r2",QCTNAME(TP)+" enters through hole.\n");
     TP->move_living("M",MISTY_DIR+"r2");
     return 1;
   } 
  NF("Enter what?\n");
  return 0;
}

/*****************/
/*  GUILD STUFF  */
/*****************/

set_up_skills()
{
    sk_add_train(SS_CLIMB, "climb walls and mountains", 0, 0, 60 );
}

int
sk_improve(string str)
{
  int steps;

  seteuid(getuid());

  if(!(TP->test_bit("Rhovanion",GROUP,BIT))) return 0;

  if (!str || sscanf(str, "%d", steps))
    return sk_list(steps);

  return ::sk_improve(str);
}

string
climber_guild(){
  if(TP->test_bit("Rhovanion",GROUP,BIT))
    return "Welcome THE CLIMBER! You may improve your skill here.\n";
  return "";
}
