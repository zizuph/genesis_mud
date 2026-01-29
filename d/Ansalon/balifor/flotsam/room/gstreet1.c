/* Flotsam sidestreet by Gorr 8.12.96 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

create_flotsam_room()
{
   set_short("Side street in the town of Flotsam");
   set_long("@@long_descr");

   add_item(({"side street","street","sidestreet","alley"}),
      "A narrow side street, leading in south-north direction. \n");
   add_item(({"house","houses","buildings","deserted houses"}),
      "Tall, stone houses look lifeless and deserted. \n");
   add_item(({"windows","window","dark windows"}),
      "No sign of life could be seen in this dark windows. \n");
   add_item("main street",
      "To your north, this narrow alley opens into the main street.");

   add_exit(FROOM + "street33.c","north",0);
   add_exit(FROOM + "gstreet2","south",0);

   set_tell_time(90);
   add_tell("A black cat runs through the street, chasing nearly the " +
       "same size rat.\n");
   add_tell("You hear a woman cry from one of the houses. Unfortunately " +
       "you can't say from which one. \n");
   add_tell("You are nearly sure you saw someones shadow just behind " +
       "your back. \n");
   add_tell("You step in a pool of dirty water, splashing the stinking " +
       "fluid all around. \n");
   add_tell("Something moves in one of the windows. Or maybe it is just " +
       "your imagination. \n");
    
}

string
long_descr()
{
   return tod_descr1() + "You are standing on a small " +
   "side street in the wretched town of Flotsam. The overwhelming stink of " +
   "rotten food is hard to stand. All the houses around look deserted, with " +
   "dark windows like the eyes of some evil beast. " +
   "This alley leads further south while just north of you the main street " +
   "can be seen. " + season_descr() + "\n";

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
