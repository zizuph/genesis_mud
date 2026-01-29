/* file name:        /d/Avenir/common/holm/t_camp/c8.c
 *  creator(s):      (Rangorn , Feb 97)
 *  revisions:
 *  purpose:
 *  note:
 *  bug(s):
 *  to-do:
 */

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/t_camp/camp_base";

/* Include the local area defines, etc */
#include "../holm.h"

/* Now create the room.  */
void
create_camp_room()
{
  
    set_short("Eastern part of camp");
    set_long("A desolate place that is barren except for the "+
           "stubborn and ever-present thorn bushes that " +
           "embrace it. A narrow path through the thorns "+
           "has been cleared to the east. You can also climb " +
           "over some rocks to the north. " +
           "A big puddle filled with boiling water and mud takes up a " +
           "large portion of this area. " +
           "A horrible smell is eminating from the east.\n");

    add_exit("c6", "north", 0);
    add_exit("c9", "east", 0);            

    add_ground();  
    add_bushes();
 
    add_item(({"east", "east trail", "east path", "path", "trail"}),
             "You bend down and examine the trail and you notice " + 
             "that it isn't well-travelled.\n");
  
    add_item(({"puddle"}),
             "You examine the puddle closer and you notice some kind of "+
             "crack beneath the water and the mud.\n");
  
    add_item(({"crack"}),
             "A small crack from which the hot water is coming from.\n");   

    add_item(({"mud", "water"}), "Warm mud and water have seemed up "+
        "from a crack in the bedrock.\n");
    
    set_tell_time(60);
    add_tell("Suddenly the ground starts to shudder and with a "+
           "deafening roar water erupts from the boiling puddle.\n " +
           "The water sprouts high up in the air and for a brief "+
           "moment you capture a glimpse of a rainbow as droplets " +
           "of mud and water rains down on you.\n ");     
  
}

void
do_troloby_jump()
{
    object trol;

    if (trol = (present("troloby", this_object())))
    {
        trol->move_living("gives a blood-curdling yell and heads "+
            "for the chasm",  T_CAMP + "w1", 1, 0);   
        trol->command("assist nemur");
        return;
    }
    return;
}                                                                              
