/* Ship in bottle for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

int pulled = 0;

void
create_object()
{
    set_name("bottle");
    set_adj("clear");
    set_short("clear bottle");
    set_long("@@long_descr");
    add_prop(OBJ_I_VALUE, 70);
    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 120);
    add_cmd_item("cork","pull","@@pull_cork");
}

string
pull_cork()
{
    if (pulled)
        write("The cork has already been pulled out!\n");
    else
    {
        write("You grasp the cork and pull with all your strength. The " + 
            "cork suddenly pops out sending you falling to the ground in " + 
            "surprise. Unfortunately, the ship was shaken by the force, " + 
            "and has fallen to pieces.\n");
        say(QCTNAME(TP) + "grasps the cork on the clear bottle, and pulls " + 
            "with all " + HIS(TP) + " strength. The cork suddenly pops " + 
            "out sending " + HIM(TP) + " falling to the ground in surprise.\n");
        pulled = 1;
    }
    return "";
}

string
long_descr()
{
    if (pulled)
        return("This bottle used to be a fine example of a ship in a " + 
            "bottle. However, someone ruined it by pulling the cork and " + 
            "shaking the ship apart.\n");
    else
        return("This bottle is a fine example of a ship in a bottle. " + 
            "The detailing on the ship inside the bottle is intricate, " + 
            "down to the bucket and mop sitting on the deck. The bottle " + 
            "is firmly corked, and pulling the cork would likely ruin this " + 
            "piece of artwork.\n");
}

