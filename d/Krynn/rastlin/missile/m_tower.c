/* An example missile room.  This room, a tower, has 2 windows, each of 
 * which looks out over a different room.  The targets available to the
 * two other rooms vary depending on who is in the windows.
 */

#pragma warnings all

inherit "/d/Wiz/rastlin/missile/room";
 
#include <stdproperties.h>
#include <macros.h>
#include <composite.h> 
 
#define PATH "/d/Wiz/rastlin/missile/"
#define W_WIN "_at_west_window"    /* properties to keep track of who is */
#define N_WIN "_at_north_window"   /* at which window.                   */
 
int do_approach(string str);
int do_leave(string str);

void
create_room()
{
   set_short("Inside tower");
   set_long("You are standing inside a stone tower.  There are two windows "+
      "in the tower, one facing west and the other north.  If you 'approach' "+
      "a window you can see into the courtyard below.  Some stairs lead "+
      "down, out of the tower.\n");

   add_item(({"tower", "stone tower"}), "You are standing in it.\n");
   add_item("stairs", "They are the way out.\n");
   add_item("windows", "There are two of them, one facing north and the "+
      "other facing west.\n");
   add_item("window", "Which one?\n");
   add_item(({"north window", "north facing window"}), "@@north_view");
   add_item(({"west window", "west facing window"}), "@@west_view");
   add_item("courtyard", "@@courtyard");

   add_exit(PATH+"m_room1", "down", "@@go_down");

   /* add the missile_combat calls.  Here the message is changed so we use
    * the second argument to add_other_missile_room(), but because someone
    * shooting from the window is visible, we leave off the 3d arg, using the
    * default setting.  Also, the window provides some cover to the firer.
    */
   add_other_missile_room(PATH+"m_room1", "out the west window", 
      "from the window");
   add_other_missile_room(PATH+"m_room2", "out the north window", 
      "from the window");
   set_cover(30);

}

void
init()
{
   ::init();
   add_action(do_approach, "approach");
   add_action(do_leave, "leave");
}

/* player leaves the tower.  Remember to remove any props you added.
 */
int
go_down()
{
   object tp = this_player();
   
   tp->remove_prop(W_WIN);
   tp->remove_prop(N_WIN);

   write("You climb down the stairs and leave the tower.\n");
   return 0;
}


/* We want to be able to see who or what is in the rooms outside the tower
 * so they can be targeted.  We use query_target_list() to be sure we aren't
 * going to get objects the room thinks we can't see.
 * First though we need to make sure the potential firer can see out the
 * window.
 */
string
west_view()
{
   string str = "A west facing window";

   if(!this_player()->query_prop(W_WIN))
      str += ".\n";
   else
     str += " through which you can see a courtyard.\n";

   return str;
}

string
north_view()
{
   string str = "A north facing window";

   if(!this_player()->query_prop(N_WIN))
      str += ".\n";
   else
     str += " through which you can see a cluttered courtyard.\n";

   return str;
}

/* Now let us see what is in the courtyard we might want to shoot at.
 */
string
courtyard()
{
   string str;
   object ob, *things;

   if(this_player()->query_prop(W_WIN))
   {
      str = "A courtyard";
      if(ob = find_object(PATH+"m_room1"))
      {
        /* get the list of objects in the window and add them to the desc */
        things = ob->query_target_list(this_object());
        if(sizeof(things))
           str += " which contains "+ COMPOSITE_LIVE(things) +".\n";
        else
           str += " which is empty.\n";
      }
   }
   else if(this_player()->query_prop(N_WIN))
   {
      str = "A cluttered courtyard";
      if(ob = find_object(PATH+"m_room2"))
      {
         /* get the list of objects in the window and add them to the desc */
        things = ob->query_target_list(this_object());
        if(sizeof(things))
           str += " which contains "+ COMPOSITE_LIVE(things) +".\n";
        else
           str += ".\n";
      }
   }
   else
      str = "You can't see any courtyard from where you are standing.\n";

   return str;
}

/* Here we do the bookkeeping for players who approach the windows, thus
 * making them visible from the outside and also those who 'leave' the window
 * without leaving the room.
 */

int
do_approach(string str)
{
   object tp;

   if(str != "window" && str != "west window" && str != "north window")
   {
      notify_fail("approach what?\n");
      return 0;
   }

   tp = this_player();
   switch(str)
   {
      case "west window":
         if(tp->query_prop(N_WIN))
            tp->remove_prop(N_WIN);
         tp->add_prop(W_WIN, 1);
         write("You approach the west window.\n");
         say(QCTNAME(tp) +" approaches the west window.\n");
         return 1;
         break;
      case "north window":
         if(tp->query_prop(W_WIN))
            tp->remove_prop(W_WIN);
         tp->add_prop(N_WIN, 1);
         write("You approach the north window.\n");
         say(QCTNAME(this_player()) +" approaches the west window.\n");
         return 1;
         break;
      default:
         notify_fail("Which window did you want to approach?\n");
         return 0;
   }
}

int
do_leave(string str)
{
   if(str != "window")
   {
      notify_fail("Leave what?\n");
      return 0;
   }

   this_player()->remove_prop(W_WIN);
   this_player()->remove_prop(N_WIN);
   write("You move away from the window.\n");
   say(QCTNAME(this_player()) +" moves away from the window.\n");
   return 1;
}

/* Now we start redefining missile_combat functions to be sure they only 
 * check the correct room for tarets, and only return the people in the 
 * correct window when asked for a target list.
 */

object *
query_target_rooms(object firer)
{
   object list;

   /* set the value of list based on which window the firer is in, if any. */
   if(firer->query_prop(W_WIN))
      list = find_object(PATH+"m_room1");
   if(firer->query_prop(N_WIN))
      list = find_object(PATH+"m_room2");

   if(list)
      return ({list});
   else
      return ({}); /* we should never see this happen, but just in case... */
}

/* A filter function to test whether a potential target is in sight of the 
 * firer, ie. the target is in the window the firer can see.
 */
int
filter_my_prop(object ob, int prop)
{
   if(ob->query_prop(prop))
      return 1;
   else
      return 0;
}

object *
query_target_list(object firer_env)
{
   object *targets = all_inventory();

   if(firer_env == (find_object(PATH+"m_room1")))
   {
      targets = filter(targets, &filter_my_prop(,W_WIN));
      return targets;
   }

   if(firer_env == (find_object(PATH+"m_room2")))
   {
      targets = filter(targets, &filter_my_prop(,N_WIN));
      return targets;
   }
   
   /* we should never reach here, but because errors do occur... */
   return ({});
}

