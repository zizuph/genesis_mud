/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "climb.h"


/*
 * Prototypes
 */
void reset_room();

create_room()
{
  seteuid(getuid());

    if(!(find_object(ROOM_CLIMB))) clone_object(ROOM_CLIMB);

    set_noshow_obvious(1);
    add_prop(ROOM_I_INSIDE, 0);
    set_short("behind rock.\nThere are three obvious exits: west, north, in");
    set_long("You are crawling the slope of the Misty Mountains trying to " +
             "pass a huge rock. It seems that you haven't chosen the right " +
             "way. The other one must be much easier than this one. You " +
             "also notice a cave here.\n"+"There are three obvious "+
             "exits: west, north, in.\n"+"@@who_climbs");


    add_item("rock", "It is big and dark. No way to pass it except " + 
                     "walk around. You may try to climb it too but " +
                     "beware!!! It is quite high and if you fall down " +
                     "you can be severely hurt.\n"+"@@exa_rock");
    add_item("cave", "It is dim and looks dangerous. Better stay out of it.\n");

/* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p3", "west",     0,    10);
    add_exit(MISTY_DIR+"p4", "north",    0,    10);
    add_exit(MISTY_DIR+"c1", "in",       0,    4);
    add_exit(ROOM_U, "_never_use_1", 1);
    add_exit(ROOM_CLIMB, "_never_use_2", 1);

    reset_room();
}

void
reset_room()
{
  object monster;

  seteuid(getuid());

    monster = present("mimo");
    if (!monster){
      monster = clone_object(NPC_DIR+"climber");
      monster->move_living("xxx", this_object());
    }
}

string
exa_rock()
{
  say(QCTNAME(TP)+" studies the rock carefully.\n");
  return "";
}

init()
{
    ::init();
    add_action("climb_rock", "climb");
}

climb_rock(string rock) {
int _how_high_;
 if(rock=="rock")
  {
   _how_high_ = random(TP->query_skill(SS_CLIMB));
   if(sizeof(TP->query_weapon(-1)))
     _how_high_ = MIN(_how_high_ , 29);

   TP->move_living(0,ROOM_CLIMB);
   if(sizeof(FILTER_LIVE(all_inventory(find_object(ROOM_CLIMB)))) > 1)
    {
     TP->catch_msg(BS("You decided to wait until the other climber "+
                      " finishes. It is really safer...\n"));
     TP->move_living(0,ROOM_D);
     return 1;
    }
   else
    {
     START_DOWN_D; START_DOWN;
     call_out("climb_5",DELAY,_how_high_);
     return 1;
    }
  }
 else
  {
   NF("What do you want to climb?\n");
   return 0;
  }
}

climb_5(_how_high_){
 if(_how_high_ < 5)
  {
   FALL_DOWN_U; FALL_DOWN_D; SHOUT_D_U; SHOUT_U; TP->move_living(0,ROOM_D);
   TP->reduce_hit_point(DAMAGE*_how_high_);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_5; HIGH_5_D;
 call_out("climb_10",DELAY,_how_high_);
 return 1;
}

climb_10(_how_high_){
 if(_how_high_ < 10)
  {
   FALL_DOWN_U; FALL_DOWN_D; SHOUT_D_U; SHOUT_U; TP->move_living(0,ROOM_D);
   TP->reduce_hit_point(DAMAGE*_how_high_);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_10; HIGH_10_D;
 call_out("climb_15",DELAY,_how_high_);
 return 1;
}

climb_15(_how_high_){
 if(_how_high_ < 15)
  {
   FALL_DOWN_U; FALL_DOWN_D; SHOUT_D_U; SHOUT_U; TP->move_living(0,ROOM_D);
   TP->reduce_hit_point(DAMAGE*_how_high_);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_15; HIGH_15_D;
 call_out("climb_20",DELAY,_how_high_);
 return 1;
}

climb_20(_how_high_){
 if(_how_high_ < 20)
  {
   FALL_DOWN_U; FALL_DOWN_D; SHOUT_D_U; SHOUT_U; TP->move_living(0,ROOM_D);
   TP->reduce_hit_point(DAMAGE*_how_high_);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_20; HIGH_20_D;
 call_out("climb_25",DELAY,_how_high_);
 return 1;
}

climb_25(_how_high_){
 if(_how_high_ < 25)
  {
   FALL_DOWN_U; FALL_DOWN_D; SHOUT_D_U; SHOUT_U; TP->move_living(0,ROOM_D);
   TP->reduce_hit_point(DAMAGE*_how_high_);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 HIGH_25; HIGH_25_D;
 call_out("climb_30",DELAY,_how_high_);
 return 1;
}

climb_30(_how_high_){
 if(_how_high_ < 30)
  {
   FALL_DOWN_U; FALL_DOWN_D; SHOUT_D_U; SHOUT_U; TP->move_living(0,ROOM_D);
   TP->reduce_hit_point(DAMAGE*_how_high_);
   if(TP->query_hp()==0) TP->do_die(TO);
   return 1;
  }
 END_UP_D; END_UP_U; END_UP; TP->move_living("M",ROOM_U);
 return 1;
}

string
who_climbs(){
object *in_room_climb;
 in_room_climb=FILTER_LIVE(all_inventory(find_object(ROOM_CLIMB)));
 if(sizeof(in_room_climb) > 0)
 {
  call_out("who_climb",0,({TP,in_room_climb[0]}));
 }
 return "";
}

void
who_climb(mixed foo)
{
  foo[0]->catch_msg(QCTNAME(foo[1])+" is climbing the rock.\n");
}
