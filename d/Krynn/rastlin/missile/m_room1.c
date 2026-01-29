/* An example missile room.  This is a very simple room with only minimal
 * work being done.
 */

#pragma warnings all


inherit "/d/Wiz/rastlin/missile/room";

#include <stdproperties.h>
#include <composite.h>

#define PATH "/d/Wiz/rastlin/missile/"

void
create_room()
{
   set_short("Outside tower - west side");
   set_long("You are standing in a courtyard outside of a tower.  The tower " +
      "is to your east.  There is a doorway at the base of the tower and a "+
      "window higher up.  The courtyard circles around the tower to the "+
      "northeast.  That part of the courtyard is cluttered with old crates "+
      "and barrels.\n");

   /* this item is unusual because we want to be able to see who, or what
    * is standing in the window of the tower. see_in_window is a vbfc *
    */
   add_item("window", "@@see_in_window");
   add_item(({"tower", "stone tower"}), "A stone tower with a doorway and a "+
      "window facing you.\n");
   add_item("doorway", "The way into the tower.\n");
   add_item("courtyard", "A courtyard which circles to the northeast.  The "+
      "northeast part of the courtyard is cluttered with old crates and "+
      "barrels.\n");
   add_item(({"clutter", "crates", "barrels", "old crates", "old barrels",
      "old crates and barrels"}), "@@see_clutter");

   add_exit(PATH +"m_tower", "east", "@@up_stairs");
   add_exit(PATH +"m_room2", "northeast");

   /* Here we add the necessary calls for missile combat.  Note that only a
    * single argument is used for add_other_missile_room().  This causes the
    * default arguments to come into play.  Also, there is no cover here so,
    * the default value of 0 will be used (and there is no reason to make 
    * the call).
    */
   add_other_missile_room(PATH+"m_tower");
   add_other_missile_room(PATH+"m_room2");

}


int
up_stairs()
{
   write("You enter the tower and climb the stairs.\n");
   return 0;
}


/* We want to see who is in the window upstairs so we will ask it for a list
 * of objects visible.
 */
string
see_in_window()
{
   object ob, *things;
   string str = "A dark opening in the side of the tower";

   if(ob = find_object(PATH+"m_tower"))
   {
      /* get the list of objects in the window and add them to the desc */
     things = ob->query_target_list(this_object());
     if(sizeof(things))
        str += " in which you can see "+ COMPOSITE_LIVE(things) +".\n";
     else
        str += ".\n";
      
   }
   else
     str += ".\n";

   return str;
}

/* We want to see who is in the other part of the courtyard so we will ask it 
 * for a list of objects visible.
 */
string
see_clutter()
{
   object ob, *things;
   string str = "Just old barrels and crates that have been piled in the "+
      "northeastern part of the courtyard";

   if(ob = find_object(PATH+"m_room2"))
   {
      /* get the list of objects in the window and add them to the desc */
     things = ob->query_target_list(this_object());
     if(sizeof(things))
        str += ".  Half hidden among them you can see "+ 
           COMPOSITE_LIVE(things) +".\n";
     else
        str += ".\n";
      
   }
   else
     str += ".\n";

   return str;
}

