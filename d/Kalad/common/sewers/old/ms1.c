/*      Created by:	Sir Toby  97-06-17
 *
 *      Location:	The main tunnel of sewers
 *      Modified:	97-06-23, Toby	
*/

#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/path.h"
//#include "/d/Kalad/common/sewers/tells.h"


void
create_room()
{
  ::create_room();

    set_short("Inside the main tunnel of the sewers");
    set_long("This is the main tunnel of the sewer-system. You are " +
          "wading in calf-high water. The floor can not be seen " +
          "due to the dirty water. The brick walls are covered " +
          "with moss and slime and the vaulted ceiling is covered " +
          "with a layer of lime. There are a number of stalactites " +
          "found in the ceiling as well. It is almost as if the " +
          "tunnel had ears and eyes, but you can hear nothing else " +
          "but the rushing water.\n" +
          "There are connecting tunnels " +
          "to the northeast and to the northwest. Looking south you " +
          "see the main-tunnel continue.\n");

//    TELL1 ("ms2.c");
//    TELL1 ("ls1.c");
//    TELL1 ("rs1.c");
//    TELL2 ("ms3.c");
//    TELL2 ("ls2.c");
//    TELL2 ("rs2.c");

    add_item( ({"water","dirty water"}),
              "The water is black and thick and smells awful. " +
              "There is various slobby things floating downstream. " +
              "It would not be a good idea to taste the water.\n");
    add_item("floor", "The floor can not be seen due to the dirty water.\n");
    add_item( ({"wall","walls","brick wall","brick walls"}),
              "The walls are covered with thick brown moss and slime.\n");
    add_item( ({"moss","brown moss"}), "It is some ordinary wet brown moss.\n");
    add_item("stalactites", "It is a number of stalactites in various " +
                            "sizes. Water is dripping from them.\n");
    add_item("ceiling","It is a vaulted ceiling and it is covered " +
                      "with a layer of lime. There are a number of " +
                      "stalactites grown from there too.\n");
    add_item( ({"brick","bricks"}), "There is nothing special with the " +
        			    "bricks.\n");
    add_item("lime","It is the regular lime that appears after many " +
                    "years of damp atmosphere.\n");
    add_item("things","It is rat corpses and old papers among all the stuff. " +
                      "And there is an eye floating from the latest " +
 		      "kill above.\n");
    add_item("slime","The slime is transparent and smells awful. It seems " +
                     "almost alive as it drops and slides down the wall.\n");

    add_cmd_item("stalactites","count","You count " + random(12) +
      		 " stalactites.\n");
    add_cmd_item(({"water","dirty water"}),({"taste","drink"}),"@@taste");
    add_cmd_item("air", ({"smell","sniff"}),
                 "The air smells really awful from the rotting things " +
                 "floating in the dirty water.\n");
    add_cmd_item(({"moss","brown moss"}),"touch",
                "The moss feels very soft and moisty.\n");

    add_exit(PATH + "ls1.c","northwest",0,2);
    add_exit(PATH + "rs1.c","northeast",0,2);
    add_exit(PATH + "ms2.c","south",0,1);
    set_noshow_obvious(1);
   
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,-2);

}



/*      Function will command player who tastes the water
 *      to puke and it will drain health and hunger from him.
 *      It returns the text the player will read.
 */

string
taste()
{

    TP->heal_hp(-(random(50) + 50)); /* it is really bad water.. */
        if(TP->query_hp() <= 0)
	    TP->do_die();

    TP->set_stuffed(TP->query_stuffed()-100); /* Make them hungry */

    write("You bend down to get some water in your hands and you " +
          "taste it. The bad taste is overwhelming, you have to " +
   	  "puke.\n\n\n");

    say("\n" + QCTNAME(TP) + "bends down to get some water " +
        "in " + TP->query_pronoun() + 
        "s hands and " + TP->query_pronoun() + "tastes it.\n");

    TP->command("puke");
    TP->command("scream");
    TP->command("shiver");


/*   tell_room(PATH + "ms2.c","You hear someone puke real close to you." +
 *                           "The sound of it echoes away and dies.\n");
 *   tell_room(PATH + "ls1.c","You hear someone puke real close to you." +
 *                           "The sound of it echoes away and dies.\n");
 *   tell_room(PATH + "rs1.c","You hear someone puke real close to you." +
 *                           "The sound of it echoes away and dies.\n");
 */

/* Perhaps I should let the echo of it sound through the whole sewers
 * that way get a 'global' call for it...
 */

  return("\nYour scream echoes through the sewers and now everybody " +
         "knows that you are here.\n");
}

                                          
