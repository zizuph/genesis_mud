/* This comment tells emacs to use c++-mode  -*- C++ -*- */

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";

object dolmoor;
object person_sitting;
int sit(string str);
int stand(string str);
int sitting = 0;

public void
reset_room()
{
    if (!dolmoor) {
        dolmoor=clone_object(MOUNTAIN_DIR + "elderwood/npc/dolmoor");
        dolmoor->move(this_object());
    }
}


void init()
{
    ::init();
       add_action(sit,"sit");
       add_action(stand,"stand");
}

public void
create_room()
{
    ::create_room();
    set_short("on the porch of a quaint little log cabin.");
    set_long("You stand before a small porch leading " +
       "to the door of a quaint little log cabin. The " +
       "porch overlooks the large mirror lake to the north. " +
       "The forest extends in every other direction.\n");


    add_item(({"cabin","log cabin"}),
       "The quaint little log cabin was built from thick solid " +
       "logs and mortar. A small porch extends from the front of the " +
       "cabin overlooking the lake to the north.\n");

    add_item(({"door"}),"The door looks quite solid and " +
       "is void of any handle or knob. You dont see " +
       "anyway into cabin.\n");
    add_item(({"crosses","cross","window","windows"}),
       "The windows of the cabin are little more than slits " +
       "in the walls which resemble the form of a cross " +
       "on either side of the porch.\n");
    add_item(("porch"),"The porch extends the length of the front of the " +
       "log cabin. It faces the mirror lake to the north. The porch stoop " +
       "looks like a nice place to relax on while enjoying the quiet " +
       "forest.\n");
    add_item(({"steps","stoop"}),"The porch stoop or steps look like a nice place " +
       "to sit and relax.\n");
    add_item(({"mirror lake","mirror","lake"}),
       "The lake is very quiet, hardly a ripple. It reminds you of a smooth looking " +
       "mirror.\n");


    reset_room();
}

int
sit(string str)
{
    if((str != "on stoop" && str != "on the stoop"))
    {
       notify_fail("Sit on what, the stoop maybe?\n");
       return 0;
    }
       if(sitting == 0)
       {
          write ("You sit down on the porch stoop resting " +
                 "your weary bones.\n");
          say(QCTNAME(TP) + " sits on the porch stoop, sighing " +
                 "in relief.\n");
          sitting = 1;
        if(sitting == 1)
        {
        person_sitting = TP;
        person_sitting ->add_prop(LIVE_S_EXTRA_SHORT, 
           " is sitting on a porch stoop.\n");
        return 1;
        }
   }
       NF(QCTNAME(person_sitting) + " is already sitting on the porch " +
           "stoop. There isn't any room for you.\n");
       return 0;
}


int
stand(string str)
{
    if((sitting == 1 && person_sitting == TP))
    {
       if(str != "stand" && str != 0)
       {
          return 0;
       }
       write("You stretch wearily, then stand up from the porch stoop.\n");
       say (QCTNAME(TP) + " stretches wearily, then stands from the porch " +
           "stoop.\n");
       sitting = 0;
       person_sitting->remove_prop(LIVE_S_EXTRA_SHORT);
       person_sitting = 0;
       return 1;
     }
     notify_fail("You are already standing.\n");
     return 0;
}
