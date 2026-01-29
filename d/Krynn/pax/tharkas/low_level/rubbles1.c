/*
   Pax Tharkas, Low level, entrance into the fortress cellar.

   rubbles1.c
   ----------

   Coded ........: 95/01/03
   By ...........: Jeremiah
 
   Latest update : 04/10/08
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

int    light_intens;
string ret_str;

object *rats = ({ 0, 0, 0, 0 });

void
reset_pax_room()
{
    int i, size;
    
    /* Reset one rat each time, up to max of 4 */
    size = sizeof(rats);
    for (i = 0, size = sizeof(rats); i < size; i++)
    {
        if (!objectp(rats[i]))
        {
            rats[i] = clone_object(PMONSTER + "rat");
            rats[i]->move_living("arrives", TO);
            break;
        }
    }

    if(light_intens)
        tell_room(TO, "The torch goes out.\n");
    
    light_intens = 0;
    add_prop(ROOM_I_LIGHT,light_intens);
}

void
create_pax_room()
{
   reset_pax_room();

   set_short("Room filled with rubble.");
   set_long("@@long_descr");

   INSIDE;

   add_item(({"crates", "boxes"}), "Some of these has been labelled " +
            "SOLACE, and some GATEWAY. They have all been very " +
            "effectively sealed, you probably can't open them.\n");

   add_item(({"rubble", "rubbles"}), "These are rubble of different " +
            "sizes and shapes, a small tunnel has been cleared, leading " +
            "east into darkness.\n");

   add_item("debris" ,"Pieces of old wood and cloth, probably from " +
            "smashed up crates, old furniture and boxes.\n");     

   add_item("door", "It is an old wooden door, or rather the remains " +
            "of an old door. What's left isn't much more than the " +
            "hinges. The door opening leads into a corridor.\n");

   add_item(({"torch", "large torch"}), "@@torch_descr");  

   set_tell_time(90);
   add_tell("@@do_flicker@@");

   
   add_exit(LOW_LEVEL + "rubbles_entr", "east", 0);
   add_exit(LOW_LEVEL + "rubbles2", "south", 0);
   add_exit(LOW_LEVEL + "corridor1", "west", 0); 
}


void
init()
{
   ::init();
   add_action("light_torch", "light");
   add_action("ext_torch", "extinguish");
}


string 
long_descr()
{
   ret_str = "You are standing in a large open room. The eastern part " +
             "of this room is filled to the ceiling with a large heap of " +
             "rubble. A small tunnel leads east into this heap of rubble. " +
             "The rest of the room is packed from floor to ceiling with " +
             "stacks of wooden crates and boxes. Debris of different " +
             "sorts lies scattered all over the floor. " +
             "You realize that you are standing in the cellar of Pax " +
             "Tharkas! There's an old wooden door leading west, " +
             "and a large opening leading south into another part " +
             "of the cellar.\n";   
 
   if (light_intens == 1) 
   {
      ret_str = ret_str + "Flames flicker from a large lit torch " +
                          "mounted in a torch holder on the wall.\n";   
   }
   else
   {
      ret_str = ret_str + "There's an unlit large torch mounted in " +
                          "a torch holder on the wall.\n";   
   }
   return ret_str;
}


string
torch_descr()
{
   if (light_intens == 0)
   {
      write("It's a rather large unlit torch solidly placed in an iron " +
            "holder on the wall.\n");
   }
   else
   {
      write("It's a rather large lit torch solidly placed in an iron " +
            "holder on the wall. The flickering light from it, creates " +
            "ever changing shadows in the room.\n");
   }
   return "";
}


int
light_torch(string what)
{
   if (what == "torch")
   {
      if (light_intens == 0)
      {
         light_intens = 1;
         write("You light the large torch.\n");
         say(QCTNAME(TP) + " lights the large torch.\n");
         add_prop(ROOM_I_LIGHT,light_intens);
      }  
      else
      {
         write("It's already lit.\n");
      }
      return 1;
   }
   else
   {
      NF("light what?\n");
      return 0;
   }
}
   

int
ext_torch(string what)
{
   if (what == "torch")
   {
      if (light_intens == 1)
      {
         light_intens = 0;
         write("You extinguish the large torch.\n");
         say(QCTNAME(TP) + " extinguishes the large torch.\n");
         add_prop(ROOM_I_LIGHT, light_intens);
      }
      else 
      {
         write("but .. The torch isn't lit.\n");
      }
      return 1;
   }
   else
   {
      NF("extinguish what?\n");
      return 0;
   }
}


string
do_flicker()
{
   if(light_intens == 1)
   {
       return "The burning torch flickers, casting strange " +
           "shadows on the wall.\n";
   }
   return "";
}


construction()
{
    write("This area is still under construction. Please come back later.\n");
    return 1;
}
