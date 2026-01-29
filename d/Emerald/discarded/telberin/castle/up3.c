inherit "/std/room";

#include "default.h"
#include <ss_types.h>
#include <stdproperties.h>

#define MIN_AWARENESS_NEEDED 25

int searched;
object maid;

void reset_room();

void
create_room()
{
   set_short("Master bedroom");
   set_long("The master bedroom itself:  the Lord and Lady's abode. It is " +
            "currently empty, but it is kept thoroughly clean to say the " +
            "least. The artwork here is tremendously breathtaking, a " +
            "beautiful walnut dresser against the north wall, with a large " +
            "silver mirror on it. The cabinets are all in finished oak and " +
            "the four-poster bed is draped in satin, with silk sheets.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(OBJ_S_SEARCH_FUN, "search_fun");
   add_prop(OBJ_I_SEARCH_TIME, 6);

   add_exit(THIS_DIR + "up1", "west");
   
   add_item("dresser","The dresser is full of the Lady's equipment that "+
        "she uses to keep herself beautiful, balms and the like. There are "+
        "also a few wigs here for the top and back of the head for "+
        "formal occasions.\n");
   add_item("wigs","The wigs are used for formal occasions when Elven "+
        "Ladies have their hair bunched on top.\n");
   add_item("mirror","You see some scruffy individual staring back at you.\n");
   add_item("cabinets","The cabinets are exquisite in their design, and "+
        "polished so they are a rich oaken colour.\n");
   add_item("bed","The bed is large and has a post at each corner. Satin "+
        "is draped from the top of the posts to afford protection against "+
        "pryers or insects during the hot seasons.\n");
   add_item("posts","The posts are made of stout oak, varnished and "+
        "polished.\n");
   add_item("satin","The satin is a nice mellow cream colour to match the "+
        "colours of the woods around.\n");
   add_item(({"silk","sheets"}),"The sheets are made from silk, very "+
        "luxurious.\n");

   searched = 0;
   seteuid(getuid());
   set_alarm(1.0, 0.0, reset_room);
}

void
reset_room()
{
   searched = 0;
   if(maid)
       return;
   else
   maid = clone_object(NPC_DIR + "maid");
   maid->move_living("into a room", TO);
}


string
search_fun(object player, string str)
{
   int awareness;
   object pin;
   
  
   
   if (str != "wigs" && str != "wig")
       return 0;
   
   awareness = player->query_skill(SS_AWARENESS);
   awareness += random(awareness + 1);
   
   if ((awareness >= MIN_AWARENESS_NEEDED) && (!searched))
   {
      pin = clone_object(OBJ_DIR + "hairpin");
      pin->move(TO);
      searched = 1;
      return "You search the wigs and just as you give up hope, you come " +
          "across a hairpin.\n";
   }
   
   return "You search reveals nothing special\n";
}
