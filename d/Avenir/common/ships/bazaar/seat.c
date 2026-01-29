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
    set_name("seat");
    add_name("wooden seat");
    set_short("wooden seath");
    add_adj(({"small, wooden"}));
    set_long("It is a small wooden seat to sit on.\n");

    add_prop(OBJ_I_WEIGHT, 600000);
    add_prop(OBJ_I_VOLUME, 400000);
    add_prop(OBJ_I_VALUE, 540);
    add_prop(OBJ_M_NO_GET, "The seat is fastened to the boat.\n");

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
    if(str != "on seat")
    {
        write("Sit on what?\n");
        return 1;
    }

    if(TP->query_prop("i_am_sitting_on_a_seat"))
    {
        write("You're already sitting down.\n");
        return 1;
    }

    TP->add_prop("i_am_sitting_on_a_seat",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting on a seat");
    write("You sit down on the seat.\n");
    say(QCTNAME(TP)+ " sits down on a seat.\n");
    return 1;

}

int
do_stand()
{
   if (TP->query_prop("i_am_sitting_on_a_seat"))
   {
       write("You stand up from the seat, feeling rested.\n");
       TP->remove_prop("i_am_sitting_on_a_seat");
       TP->remove_prop(LIVE_S_EXTRA_SHORT);
       say(QCTNAME(TP)+ " stands up from the seat.\n");
   }
   else
       write("You are already standing.\n");
   return 1;

}

int
do_nothing()
{
    if (TP->query_prop("i_am_sitting_on_a_seat"))
    {
        write("You must stand up from the seat before you can do that.\n");
        return 1;
    }
   return 0;
}
