
inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_b4");
  set_pass_command(({"e","east"}));
  set_door_name(({"winged gate","wings","black gate", "gate","door",
    "wooden beams","beams","beam","wooden beam"}));
  set_door_desc(
    "The gate leading out the house is made up of two heavy wooden wings, "+
    "painted black and secured with two heavy wooden beams.\n");
  set_door_desc(VBFC_ME("door_desc"));
  set_other_room(MORGUL_DIR + "city/darkstr4");
  set_lock_name(({"lock","wooden beams","beams","beam","wooden beam"}));
  set_lock_desc("On this side of the gate there are two heavy wooden beams "+
    "which can be used to bar the gates. Before you can open the gates, you " +
    "have to unbar them.\n");
  set_lock_command(({"bar","block"}));
  set_lock_mess(({"bars the gates with the two wooden beams.\n",
                  "You hear some sounds from the gate.\n"}));
  set_lock_name("lock");
  set_unlock_command(({"remove","unbar"}));
  set_unlock_mess(({"removes the two wooden beams so that the gates can be opened.\n",
                    "You hear some sounds from the gate.\n"}));
  set_fail_open(({"The winged gate is already open.\n",
      "The wooden beams block the wings of the gate so it cannot be opened.\n"}));
  set_open(0);
  set_locked(1);
}

void init()
{
    ::init();

    add_action("do_knock","knock");
}

int do_knock(string str)
{
    string *arr;

    NF(CAP(query_verb()) + " on what?\n");
    if(!str)
        return 0;

    if(!id(str))
    {
        arr = explode(str," ");
        if(sizeof(arr) <= 1 || arr[0] != "on")
            return 0;
        str = implode(arr[1..sizeof(arr)]," ");
        if(!id(str))
            return 0;
    }

    write("You knock on the winged gate.\n");
    SAY(" knocks on the winged gate.\n");

    tell_room(other_room,"Someone knocks at the gate.\n");

    return 1;
}

string door_desc()
{
    string desc = "The gate leading out the house is made up of two " +
        "heavy wooden wings, painted black and secured with two heavy wooden beams. ";

    if(!lock_status)
        desc = "The gate leading out the house is made up of two " +
             "heavy wooden wings which are painted black. The wings can be blocked " +
             "with two heavy wooden beams fastened to the backside of one wing. ";

    return BSN(desc);
}
