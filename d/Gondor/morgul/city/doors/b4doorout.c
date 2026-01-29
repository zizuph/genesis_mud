inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgul_b4");
  set_pass_command(({"w","west"}));
  set_door_name(({"winged gate","wings","black gate", "gate","door"}));
  set_door_desc("The gate leading into the house is made up of two " +
    "heavy wings, painted black and studded with iron nails.\n");
  set_other_room(MORGUL_DIR + "city/barrack4");
  set_lock_name("lock");
  set_lock_desc("From the outside, there is no lock visible on the gate.\n");
  set_locked(1);
  set_open(0);
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
