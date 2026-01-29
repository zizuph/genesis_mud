/* This is the workroom which is currently rented by Tulix. */

inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

/* Prototype function */
public string poster_text();

public void
create_room()
{
    set_short("Tulix's workroom");
    set_long("This is Tulix's workroom. It is a modest room, " +
        "which has an understated (but none the less stylish) elegance. " +
        "The reserved nature of the furniture suggests that this is a " +
        "place for industrious experimentation rather than for resting on " + 
        "one's laurels. Although it is peaceful at the moment, it is " + 
        "almost as if the room is just waiting to burst into life " +
        "once more.\nA small poster is fixed to the wall nearest to you.\n");
    
    add_prop(ROOM_I_INSIDE, 1);

    add_item("furniture", "The furniture consists of a desk, a couple " +
        "of chairs, and a well used bench, all made from nicely grained " +
        "walnut. There are no sumptuous gold trimmings or lavish silk " +
        "cusions, just tastefully styled and functional furnishings.\n");
    
    add_item("desk", "The desk is contains stationary and journals " +
        "for recording the results of various experiments. There is also " + 
        "small collection of momentos, from mortal days long ago.\n");
    
    add_item(({"journal", "journals"}), "You pick up a journal and take " +
        "a quick look through its pages. Unfortunately, the journals " +
        "have been written in some kind cipher that you cannot decode.\n");

    add_item(({"momentos", "collection"}), "There is a medallion of Calia, " +
        "an old pipe of the Shires, a glowing gem, a dusty tome, and " +
        "a host other useful little items with personal value, but little " +
        "which is of worth to others.\n");

    add_item("medallion", "Its a looks a little rusty now, but you can " +
        "still make out the words 'swarm' and 'move behind' on it. " +
        "It must belong to someone who used to be a Calian.\n");

    add_item("pipe", "Pipes such as these used to be very common indeed, " +
        "but alas are now a rare sight. The owner was obviously a proud " +
        "Hin warrior when mortal.\n");
        
    add_item("gem", "The gem glows so brightly that you can hardly look at " +
        "it. They don't make them like this anymore....\n");

    add_item(({"dusty tome", "tome"}), "It is a dusty old tome that " +
        "contains the old version of the 'melt' spell, which melts " +
        "all of your opponents armour, and requires no spell components. " +
        "You would have great difficulty finding one these days.\n");

    add_item(({"chair", "chairs"}), "It is only when you sit down on one " + 
        "of the chairs that you appreciate how comfortable they are. " +
        "The chairs would probably make good money at an auction.\n");

    add_item("bench", "The bench has been used for many different " +
        "types of experiment, judging by the scratches, burn marks, and " +
        "occasional dents. A few colourful stains are visible on one " +
        "corner of the bench, presumably where something has been spilled. " +
        "A large dragon scale has been fixed in the centre on the bench, " +
        "to protect the bench from heat damage. Judging by the scorched " + 
        "wood around it, an even bigger piece would have been a wise " +
        "investment.\n");

    add_item(({"scale", "dragon scale"}), "The dragon scale is fixed to " +
        "the desk because of its heat-resistant properties. The dragon " +
        "scale is from a black dragon, and it must have been quite a big " +
        "one, too.\n");
    
    add_item("laurels", "If you're looking for laurels to rest on, " +
        "I'm afraid you'll be disappointed!\n");

    add_item("poster", "The poster reads:\n" + poster_text() + "\n");

    add_cmd_item("poster", "read", "The poster reads:\n" +
        poster_text() + "\n");
    
}

public string
poster_text()
{
    return  "Tulix's plans for the future are:\n\n" +
        "Short term:  1) Get pearl quest up and running.\n" +
        "             2) Minor modifications to the Grunts guild.\n" +
        "\n" +
        "Long term:   1) Recode caves in line with new code standards.\n" +
        "             2) Complete heraldry quests.\n" +
        "             3) Complete conquest tower.\n";
}
