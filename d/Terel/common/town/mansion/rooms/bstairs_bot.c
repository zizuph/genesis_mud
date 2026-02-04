
inherit "/std/room";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define TP              this_player()

#define SAYNAME(x1,x2)  say(                                             \
     ({ break_string(capitalize(x1+this_player()->query_name()+x2), 70), \
        break_string(capitalize(x1+"the " + this_player()                \
                                   ->query_nonmet_name()+x2),       70), \
        break_string(capitalize(x1+"someone"+x2),                   70)  \
     }), this_player())  

#define UP_ROOM MANSION + "rooms/bstairs_mid"

#define CLEVERNESS  80  /* wisdom + intelligence */

create_room()
{
    set_short("Bottom of the Old Stairs");
    set_long(BS(
        "This strange looking room appears to be some kind of store " +
        "room - or rather, used to be.  Despite the easy access of a " +
        "rickety old staircase leading upwards, the place looks as though " +
        "it hasn't been visited in years.  Your light casts eerie shadows " +
        "on some shapes around the edges of the room.\n"));

    add_item("shapes", "@@shapes");
    add_item("corpses", "@@legs");
    add_item(({"patella", "knee", "knees"}),
               "These knee caps have been shattered into many pieces.\n");
    add_item(({"thigh", "thighs", "femur"}),
               "These leg bones are broken in many places.\n");
    add_item(({"bones", "bone"}), "Please specifiy the type bone.\n");
    add_item(({"stairs", "staircase", "rickety stairs", "old stairs"}),
               "Don't breath too heavily or they might fall down!\n");
    
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);
    
    add_exit(UP_ROOM, "up", "@@creak");
}

creak()
{
    write("The rickety old stairs wobble dangerously as you climb them.\n");
    SAYNAME("The rickety old stairs wobble dangerously as ",
            " climbs up them.\n");
    return 0;
}

shapes()
{
    string gender;
    gender = TP->query_pronoun();

    say(QCTNAME(TP) + " recoils as " + gender + " looks at the" +
        " eerie shapes.\n");
    return "On closer examination, they appear to be corpses!\n";
}

legs()
{
    string mesg;
    mesg = "Long dead corpses that are now beginning to rot with " +
           "age.  You notice something very odd about the legs of " +
           "these corpses; ";
    if (((TP->query_stat(SS_WIS)) + (TP->query_stat(SS_INT))) > (CLEVERNESS))
        {
        mesg = mesg + "the femur and the patella bones";
        }
    else {
        mesg = mesg + "the thigh and knee bones";
        }
    mesg = BS(mesg + " seem to be very badly damaged.\n");
    return mesg;
}
