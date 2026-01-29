// file name: chair.c
// creator(s): Ilyian, April 1995
// last update: Cirion, January 22: fixed a few
//                 bugs, made the code more
//                 sturdy
// purpose: A standard chair, to be sat on
// note: Not worth much, tho.
//       With a little changing, this can be made into realistic
//         other things, like benches, etc., to add more life
// bug(s):
// to-do:

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/common.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOUL_EXTRA, x))

object sat_on;

void
create_object()
{
   set_name("chair");
   add_name("wooden chair");
   set_short("wooden chair");
   add_adj(({"strong","wooden"}));
   set_long("This is a large and heavy chair made from sturdy wood. It "
       +"looks like it would hold your weight.\n");

   add_prop(OBJ_I_WEIGHT, 6000);
   add_prop(OBJ_I_VOLUME, 4000);
   add_prop(OBJ_I_VALUE, 54);
   add_prop(OBJ_M_NO_GET, "The chairs are far too bulky to be "
     +"carrying around.\n");

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
   add_action("do_nothing","kick");
   add_action("do_nothing","bow");
   add_action("do_nothing","bounce");
   add_action("do_nothing","curtsey");
   add_action("do_nothing","kill");
   
// Anyone feel free to add more if there are other things you couldn't
// logically do while sitting in a chair.

}

int
do_sit(string str)
{
   if(str != "on chair")
   {
     NF("Sit on what?\n");
     return 0;
    }

   if(TP->query_prop("i_am_sitting_on_a_chair"))
   {
     NF("You're already sitting down!\n");
     return 0;
   }

   if(sat_on && present(sat_on, ENV(TO)))
   {
     NF(QCTNAME(sat_on)+" is sitting in the chair already.\n");
     return 0;
   }
   if(sat_on)
   {
   sat_on->remove_prop("i_am_sitting_on_a_chair");
   sat_on->remove_prop(LIVE_S_EXTRA_SHORT);
   }
   TP->add_prop("i_am_sitting_on_a_chair",1);
   TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in a chair");
   sat_on = TP;
   write("You sit down on the chair.\n");
   say(QCTNAME(TP)+ " sits down on a chair.\n");
   return 1;
}

int
do_stand()
{
   if(!TP->query_prop("i_am_sitting_on_a_chair"))
      {
        NF("You are not sitting down.\n");
        return 0;
      }
   if(sat_on != TP)
      {
        NF("You are not sitting on this chair.");
        return 0;
       }
   write("You stand up from the chair.\n");
   TP->remove_prop("i_am_sitting_on_a_chair");
   TP->remove_prop(LIVE_S_EXTRA_SHORT);
   sat_on = 0;
   say(QCTNAME(TP)+ " stands up from a chair.\n");

   return 1;

}

int
do_nothing()
{
   if (TP->query_prop("i_am_sitting_on_a_chair"))
   {
   write("You must stand up from the chair before you can do that.\n");
   return 1;
   }

   return 0;
}

