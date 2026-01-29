inherit "/std/room";

#include <cmdparse.h>
#include "/d/Emerald/common/short_defs.h"
#include <ss_types.h>
#include <tasks.h>
#include "default.h"

#define PED_LOG "/d/Emerald/telberin/castle/log/PED_LOG"

void reset_room();
void remove_wraith();
void fetch_wraith();
int do_throw(string str);
int wrong(string str);
int do_climb(string str);
int do_lift(string str);

int thrown;
int wraith_alarm;
int fetched;

void
create_room()
{
   set_short("A metal room");
   set_long(break_string("This room is entirely made from metal, apart "+
         "from the floor, which is hard granite. There is a pedestal in "+
         "the middle of the room.\n", 76));
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(OBJ_S_SEARCH_FUN, "search_fun");
   add_prop(OBJ_I_SEARCH_TIME, 5);
   
   add_item("pedestal","@@ped_desc");
   add_item(({"walls","wall"}),break_string("The walls are entirely "+
         "made of metal as is the ceiling far above. There is something "+
         "about the east wall however.\n", 76));
   add_item("east wall","The east wall looks dented in places.\n");
   add_item("floor","The floor is made of hard granite blocks "+
      "perfectly fitted together.\n");
   add_item("ceiling","The ceiling is over 25 feet above, hardly "+
      "visible in this light.\nThere is an intense beam of light from the "+
      "ceiling bathing the pedestal.\n");
   add_item(({"light","beam"}),"The light is bright and intense.\n");
   
   add_exit(CASTLE_DIR + "3k13","up","@@climb@@", 1);
   set_noshow_obvious(1);
   reset_room();
}

void
reset_room()
{
   thrown = 0;
   fetched = 0;
}

string
search_fun(object player, string what)
{
   if(what == "walls" || what == "wall")
      return "You search the walls and notice on the east wall "+
   "several indentations.\n";
   
   return "You search the "+what+" but find nothing.\n";
}


void
enter_inv(object ob, object from)
{
   object wraith;

   ::enter_inv(ob,from);
   if (interactive(ob))
   {
      wraith = present("wraith");
      if(!wraith)
      {
         if(!fetched)
         {
             set_alarm(240.0, 0.0, fetch_wraith);
             return;
         }
      }
      return;
   }
}

fetch_wraith()
{
   object wraith;
   
   wraith = clone_object(NPC_DIR + "wraith");
   wraith->move(this_object());
        wraith->attack_ob(this_player());
   fetched = 1;
   return 1;
}

void
leave_inv(object ob, object to)
{ 
   object wraith;

   ::leave_inv(ob, to);
   wraith = present("wraith");
   if(wraith)
   {
      if(fetched && interactive(ob))
      {
          wraith_alarm = set_alarm(50.0, 0.0, remove_wraith);
         return;
      }
   }
}

void
remove_wraith()
{
   object wraith;

   wraith = present("wraith");
   if(wraith)
   {
      wraith->remove_object();
      fetched = 0;
      return;
   }
}

string 
ped_desc()
{
   string ped_st;
   
   if(thrown)
      ped_st = " The pedestal has been knocked over.";
   else
      ped_st = " There is a collection of pages on the pedestal.";
   return break_string("The pedestal is made of onyx, and gleams in "+
      "the beam of light from the ceiling."+ped_st+"\n", 76);
}

climb()
{
   object name;
   
   name = QCTNAME(this_player());
   
   if((TP->resolve_task(TASK_ROUTINE, ({SKILL_WEIGHT, 40, SS_CLIMB,
                  SKILL_WEIGHT, 50, SS_AWARENESS, SKILL_END})) > 0)
      && (!(TP->query_fatigue() < (TP->query_max_fatigue() / 10))))
   {

      write("You notice the indentations and climb up.\n");
      tell_room(TO, name+" climbs up the east wall.\n", TP);
      tell_room("/d/Emerald/room/keep/3k13",name+" climbs "+
         "up from below.\n",TP);
      return 0;
   }
   write("You try to climb up the wall, but fall down and hurt yourself.\n");
   tell_room(TO, name+" tries to climb up the wall.\n", TP);
   TP->reduce_hit_point(5);
   TP->add_fatigue(-2);
   if(TP->query_hp() == 0)
      TP->do_die(this_player());
   return 1;
}

int
do_climb(string str)
{
   object name;
   
   name = QCTNAME(this_player());
   
   if((TP->resolve_task(TASK_ROUTINE, ({SKILL_WEIGHT, 40, SS_CLIMB,
                  SKILL_WEIGHT, 50, SS_AWARENESS, SKILL_END})) > 0)
      && (str == "east wall" || str == "up") &&
      (!(TP->query_fatigue() < (TP->query_max_fatigue() / 10))))
   {
      write("You notice the indentations and climb up.\n");
      TP->move_living("M","/d/Emerald/room/keep/3k13",0);
      tell_room(TO, name+" climbs up the east wall.\n", TP);
      tell_room("/d/Emerald/room/keep/3k13",name+" climbs "+
         "up from below.\n",TP);
      return 1;
   }
   notify_fail("You try to climb up the wall, but fall down and hurt "+
         "yourself.\n");
   tell_room(TO, name+" tries to climb up the wall.\n", TP);
   TP->reduce_hit_point(5);
   TP->add_fatigue(-2);
   if(TP->query_hp() == 0)
      TP->do_die(this_player());
   return 0;
}

void
init()
{
   ::init();
   add_action(do_throw,"throw");
   add_action(wrong, "take");
   add_action(wrong,"touch");
   add_action(wrong, "get");
   add_action(do_climb,"climb");
   add_action(do_lift,"lift");
}

int
do_lift(string str)
   {
   NF("Lift what?\n");
   if(!strlen(str))
      return 0;
   if(str == "pedestal")
      write("You try to lift the pedestal but can't.\n");
   return 1;
   
   return 0;
}

void
damage(string what)
{
   write("As you try to " + query_verb() + " the "+what+", you get hit by "+
      "a beam of light.\n");
   say(QCTNAME(this_player()) + " gets hit by a beam of light as "+
      this_player()->query_pronoun()+" tries to take the "+what+".\n");
   this_player()->reduce_hit_point(25);
   if (this_player()->query_hp() == 0)
      this_player()->do_die(this_player());
}

int
wrong(string str)
{
   if (str=="pedestal" || str=="pages" || str=="collection of pages") {
      damage(str);
      return 1;
   }
   return 0;
}

int
do_throw(string str)
{
   string ped;
   mixed  *items;
   int i;
   
   notify_fail("Throw what?\n");
   if (!str)
      return 0;
   if (query_verb()=="throw" && 
         parse_command(str, this_object(), "%i 'at' / 'on' %w", items, ped)) 
   {
      if (ped != "pedestal" && ped != "pages") {
         notify_fail("Throw it at what?\n");
         return 0;
       }
      items = NORMAL_ACCESS(items, "droppable", this_object());
      if (!sizeof(items))
         return 0;
      for(i=0; i<sizeof(items); i++) {
        if(member_array(items[i], all_inventory(TP)) < 0)
	 return 0;
      }
      items = filter(items, "throw_them", this_object());
      if (sizeof(items)) {
         filter(items, "fix_object", this_object());
         return 1;
       }
   }
   notify_fail("Throw what where?\n");
   return 0;
}

int
droppable(object ob)
{
   if (ob->query_prop(OBJ_M_NO_DROP))
      return 0;
   return 1;
}

int
throw_them(object ob)
{
   write("Threw " + ob->short() + " at the pedestal.\n");
   say(QCTNAME(this_player())+" threw " + ob->short() + " at the pedestal.\n");
   ob->move(this_object());
   return 1;
}

int
fix_object(object ob)
{
   object paper;
   
   if(thrown)
   {
      NF("The pedestal has been knocked over already.\n");
      return 0;
   }
   
   if (ob->query_prop(OBJ_I_WEIGHT) < 5000 || (ob->query_prop(HEAP_I_IS) && 
            ob->query_prop(HEAP_I_UNIT_WEIGHT) < 5000))
   {
      write("A beam of light strikes out and hits the "+
         ob->short()+".\n");
      if (query_verb() == "throw")
         write("A heavier object would work better...\n");
      say("A beam of light destroys the "+ob->short()+".\n");
      ob->remove_object();
      return 0;
   }
   write(capitalize(ob->short()) + " falls on the floor.\n");
   say(capitalize(ob->short()) + " falls on the floor.\n");
   
   if((ob->query_prop(OBJ_I_WEIGHT) >= 5000) || 
         ((ob->query_prop(HEAP_I_IS)) &&
         (ob->query_prop(HEAP_I_UNIT_WEIGHT) >= 5000)) && (!thrown)) 
   {
      paper = clone_here("/d/Emerald/telberin/castle/obj/part3");
      paper->move(this_object());
      write("The pedestal falls over and the collection of pages falls off "+
         "it.\n");
      say("The pedestal falls over and the collection of pages falls from "+
         "it.\n");
      WRITE_LOG(PED_LOG, TP, "has just knocked the pedestal over.");
      thrown = 1;
   }
   else 
      if((ob->query_prop(OBJ_I_WEIGHT) >= 5000) || 
         ((ob->query_prop(HEAP_I_IS)) && 
         (ob->query_prop(HEAP_I_UNIT_WEIGHT) >= 5000)) && (thrown))
   {
      write("The pedestal is already fallen over.\n");
   } 
   return 1;
}
