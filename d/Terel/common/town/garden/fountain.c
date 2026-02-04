// modified by Lilith, Mar 2022: cleaned up file, added desc.

inherit "std/object";

#include <macros.h>
#include <stdproperties.h>

int drinks;

void
reset_object()
{
   drinks = 20;
}

void
create_object(){
   
   drinks = 20;
   set_short("small silver fountain");
   add_name("fountain");
   add_name("small fountain");
   add_name("spring");
   set_long("A small silver fountain set with precious stones\n" +
      "and alabaster. The fountain takes the shape of a small\n" +
      "sylph holding a basin, out of which runs clear spring\n" +
      "water. The water cascades down into a pool.\n");
   
   add_prop(OBJ_I_NO_GET, 1);
   
   add_item(({"stones", "precious stones", "alabaster", "sylph", 
      "basin", "silver", "silver fountain"}),
      "The fountain is cast in silver in the shape of a sylph. "+
	  "She holds a basin of alabaster inset with various precious "+
      "stones.\n");
   
   reset_object();
  
}
void
init()
{
   add_action("drink_water", "drink");   
   ::init();
}

int
drink_water(string str)
{
   object ob;
   if (str!="from fountain" && str!="fountain" && str!="water") 
	  return 0;
    drinks--;
   if(drinks < 0) {
      write("The water has not refilled yet.\n");
      return 1;
   }
   seteuid(getuid(this_object()));
   write("You take water from the fountain's basin.\n");
   ob=clone_object("/d/Terel/common/town/garden/spring_water");
   ob->move(this_player());
   this_player()->command("drink water");
   return 1;
}
