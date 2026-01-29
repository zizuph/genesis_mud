// file name: bench.c
// creator(s): Ilyian, April 1995
// last update: Lilith 2003
// purpose: a bench for using throughout sybarus
// note: This is based on the bench Ilyian made for the Green.
// bug(s):
// to-do:

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/macros.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOUL_EXTRA, x))

void
create_object()
{
    set_name("bench");
    add_name("stone bench");
    set_short("stone bench");
    add_adj(({"large","stone","long","carved","marble","quartz","slabs"}));
    set_long("It is a long bench made from marble and quartz slabs. "+
        "It appears to be fairly comfortable, for a stone bench. "+
        "There are carvings along the sides of the bench, and "+
        "the top has been polished smooth.\n");

    add_item(({"carving", "carvings"}), "Chains of ivy interwoven "+
        "through trefoils have been carved into the sides of the "+
        "bench.\n");
    add_cmd_item(({"carving", "carvings"}), ({"touch","feel"}),
        "They feel smooth to the touch, as if they were carved "+
        "long ago.\n");
    add_item(({"top", "top of bench" }), "The top is made of mable "+
        "that has been polished smooth and shiny s glass.\n");

    add_prop(OBJ_I_WEIGHT, 600000);
    add_prop(OBJ_I_VOLUME, 400000);
    add_prop(OBJ_I_VALUE, 540);
    add_prop(OBJ_M_NO_GET, "The bench is too heavy.\n");

   set_no_show_composite(1);  //don't want it to show up in room desc.

}

void
init()
{
    ::init();
    add_action("do_sit","sit");
    add_action("do_stand","stand");
    add_action("do_nothing","north");
    add_action("do_nothing","south");
    add_action("do_nothing","east");
    add_action("do_nothing","west");
    add_action("do_nothing","up");
    add_action("do_nothing","down");
    add_action("do_nothing","southeast");
    add_action("do_nothing","southwest");
    add_action("do_nothing","northeast");
    add_action("do_nothing","northwest");
    add_action("do_nothing","enter");
    add_action("do_nothing","get");
    add_action("do_nothing","search");

// Anyone feel free to add more if there are other things you couldn't
// logically do while sitting in a chair.

}

int
do_sit(string str)
{
    if(str != "on bench")
    {
        write("Sit on what?\n");
        return 1;
    }

    if(TP->query_prop("i_am_sitting_on_a_bench"))
    {
        write("You're already sitting down.\n");
        return 1;
    }

    TP->add_prop("i_am_sitting_on_a_bench",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting on a bench");
    write("You sit down on the bench.\n");
    say(QCTNAME(TP)+ " sits down on a bench.\n");
    return 1;

}

int
do_stand()
{
   if (TP->query_prop("i_am_sitting_on_a_bench"))
   {
       write("You stand up from the bench, feeling rested.\n");
       TP->remove_prop("i_am_sitting_on_a_bench");
       TP->remove_prop(LIVE_S_EXTRA_SHORT);
       say(QCTNAME(TP)+ " stands up from the bench.\n");
   }
   else
       write("You are already standing.\n");
   return 1;

}

int
do_nothing()
{
    if (TP->query_prop("i_am_sitting_on_a_bench"))
    {
        write("You must stand up from the bench before you can do that.\n");
        return 1;
    }
   return 0;
}

