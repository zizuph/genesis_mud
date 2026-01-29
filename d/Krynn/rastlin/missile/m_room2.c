/* An example missile room.  This room uses more complete calls to set up
 * the links to other rooms but is otherwise still a very basic example
 */

#pragma warnings all

inherit "/d/Wiz/rastlin/missile/room";

#include <stdproperties.h>
#include <composite.h>

#define PATH "/d/Wiz/rastlin/missile/"

void
create_room()
{
   set_short("Outside tower - north side");
   set_long("You are standing in a courtyard outside of a tower.  This part "+
      "of the courtyard is cluttered with a old crates and barrels.  The "+
      "tower is to the south.  The courtyard circles around the tower to the "+
      "southwest.\n");

   /* this item is unusual because we want to be able to see who, or what
    * is standing in the window of the tower 
    */
   add_item("window", "@@see_in_window");
   add_item(({"tower", "stone tower"}), "A stone tower with a "+
      "window facing you.\n");
   add_item("doorway", "The way into the tower.\n");
   add_item("courtyard", "@@courtyard");
   add_item("clutter", "Old crates and barrels\n");
   add_item(({"crates", "barrels"}), "They are old, empty and not really "+
      "useful anymore.\n");

   add_exit(PATH+"m_room1", "southwest");

   /* Here we add the necessary calls for missile combat.  Note that the 
    * firer is not visible to targets in open courtyard but is visible from
    * the tower window.  Also, the crates and barrels provide considerable
    * cover to anyone in here.
    */
   add_other_missile_room(PATH+"m_tower", "into the window", 
      "from behind the clutter");
   add_other_missile_room(PATH+"m_room1", "", "from behind the clutter", 0);
   set_cover(75);

}

/* We want to see who is in the courtyard so we will ask it for a list
 * of objects visible.
 */
string
courtyard()
{
   object ob, *things;
   string str = "This part of the courtyard is cluttered with crates and "+
      "barrels.  The part to the southwest is clear";

   if(ob = find_object(PATH+"m_room1"))
   {
      /* get the list of objects in the window and add them to the desc */
     things = ob->query_target_list(this_object());
     if(sizeof(things))
        str += " and  you can see "+ COMPOSITE_LIVE(things) +" there.\n";
     else
        str += ".\n";
      
   }
   else
     str += ".\n";

   return str;
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


