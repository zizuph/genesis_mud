// file name: latch.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995); April: added north exit towards
//                 bridge that leads to the bazaar island.
// purpose:
// note: removed exit to horn_rm until something can be done with it
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/*
init()
{
        ::init();
        add_action("openlatch","search");
}
*/

create_room()
{
set_short("Clearing");
set_long("This large clearing is paved like"
        +" the stone path outside. It is kept immaculately"
        +" clean and dust-free, and the dense foliage around its"
        +" edges is kept at bay by some strange force."
        +" A dirt path leads off to the south, and a nice "
        +"stone paved path leaves out of the north end of the clearing.\n");

AE(PK+"w_path9","south",0);
AE(PK+"shore","north",0);

add_prop(ROOM_I_LIGHT,1);
IN

add_item(({"pile","leaves","pile of leaves"}), "It is a pile "
        +"of green-grey leaves that have fallen down from the "
        +"canopy above. How they became arranged in a pile is "
        +"a mystery, though.\n");
add_item(({"vines","vine","growth","plants","undergrowth",
        "brush","underbrush",
        "plant",
        "canopy"}),"The vines, brush and other plant life"
        +" are held back at the edge of this clearing, almost as if by some"
        +" magical power.\n");
add_item(({"pavement","stones","stone","floor","ground"}),"This"
        +" clearing is paved with squarely-cut stones in an almost too perfect"
        +" fashion.\n");
add_item(({"canopy","ceiling"}),"The canopy is so dense overhead that "
        +"you can see nothing past it except a faint glow from the "
        +"light source you know is far overhead. For a moment, though, "
        +"it is almost reminiscent of an overcast day in the outside "
        +"world. You long for the open air.\n");
AI(({"path","stone","dirt"}),"The path on the north end of the clearing "
        +"is nicely paved with intricate cobblestones, while the one to "
        +"the south was once paved, but has since fallen into disrepair "
        +"and is covered in dirt and vines.\n");
}

openlatch(string str)
{
     if ((str=="pile")||(str="leaves")||(str=="leaf")||(str="pile of leaves"))
                {
                write("As you reach into the pile of"
                        +" leaves, your hand brushes against a hidden"
                        +" latch. There is a loud snap as a trapdoor"
                        +" opens beneath you, and you fall into a darkened"
                        +" chamber.\n");
                say(QCTNAME(this_player())+ "reaches"
                        +" into the pile of leaves. There is a loud snap,"
                        +" and when you look again,"
                        +"\n"
                        + this_player()->query_pronoun() +" is gone!\n");
                tell_room(PK+"horn_rm","The trapdoor opens with a snap, and\n"
                        + QCTNAME(this_player())+"comes crashing down!\n");
                this_player()->move_living("",PK+"horn_rm",0);
                return 1;
                }
return 1;
}
