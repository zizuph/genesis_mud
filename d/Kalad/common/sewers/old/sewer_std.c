inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SEWER_I_NO_STENCH   "_sewer_i_no_stench"
/* modified by Antharanos */
   void
create_room()
{
   ::create_room();
   
   add_prop(ROOM_I_INSIDE,1); /*underground: indoor room*/
   add_prop(ROOM_I_HIDE,0); /*dim light: easy to hide*/
   add_prop(ROOM_I_LIGHT,0); /*default dark: change if you want light*/
      
   add_cmd_item(({"stench","odor","foul stench","foul odor",
            "nauseating stench","nauseating odor","sewage"}), "smell",
      "@@stench");
}

string
stench()
{
   
   if(!TO->query_prop(SEWER_I_NO_STENCH))
      return "The nauseating odor is ever-present down here. "+
   "You take a deep breath and are barely able " +
   "to choke back the bile rising in your throat.\n";
   else
      return "Amazingly, the usual odor characteristic "+
   "of the underground seems to have spared this area.\n";
}

/*
* No sense of time in the sewers but we'll write a
* description based on whether or not the player has a light source.
*/
string
query_time_desc()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->query_prop(OBJ_I_LIGHT))
      /* if(!TO->query_prop(ROOM_I_LIGHT)) */
      return "Your light-source barely seems to penetrate the darkness here.\n";
   else
      return "Visibility is extremely poor here, for deep shadows and "+
   "total darkness lie but a short distance away.\n";
}
