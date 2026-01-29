inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

object person_in_bed, ioreth, patient;

create_room()
{
  set_short("The Healing room for men");
  set_long("@@long_func");
  add_prop(ROOM_I_NO_ATTACK,1);
  add_prop(ROOM_I_INSIDE,1);
  add_item("bed","@@exa_bed");
  add_item("fireplace","In the fireplace a nice little fire is burning.\n");
  add_item("table","On the wooden table stands a few vials with herbs and potions.\n");
  add_item(({"herbs","vials","potions"}),
    "The herbs and potions are probably for use in the curing of the sick\n"+
    "people that visit this place.\n");
  clone_object(HOH_DIR + "doors/hr2indoor")->move(TO);
  add_stuff();
}

add_stuff()
{
  if (!ioreth) ioreth = clone_object(MINAS_DIR+"npc/ioreth");
  ioreth->move(TO);
  if (!patient) { patient = clone_object(MINAS_DIR+"npc/patient");
    patient->move(TO);
    }
}

reset_room()
{
  add_stuff();
}

long_func()
{
  string longstr;
  write("This is where male patients are brought for treatment.\n"+
    "A few beds are standing by the south wall, and there is a fireplace in the\n"+
    "north wall. On a table stands some vials with herbs and potions.\n");
  if (person_in_bed)
    this_player()->catch_msg(QCNAME(person_in_bed)+" is lying in a bed.\n");
  return "A doorway leads out to the main hall west.\n";
}

exa_bed()
{
  if (person_in_bed) return QCNAME(person_in_bed)+" is lying in a bed, awaiting medical care.\n";
  return "One bed is empty, awaiting the next patient to be tended.\n";
}

check_bed()
{
  if (this_player() == person_in_bed) {
    write("But you are lying in bed! You will have to stand up first.\n");
    return 1;
    }
  return 0;
}

init()
{
  ::init();
  add_action("lie_bed","lie");
  add_action("stand_up","stand");
  add_action("stand_up","rise");
}

lie_bed(string str)
{
  if (!str) {
    write("Lie where?\n");
    return 1;
    }
  if (str == "bed" || str == "in bed" || str == "down in bed" || str == "down on bed") {
    if (person_in_bed) {
      write("There are no free beds!\n");
      return 1;
      }
    write("You lie down in the bed, awaiting the healers attention.\n");
    person_in_bed = this_player();
    tell_room(this_object(),QCTNAME(this_player())+" lies down in the bed.\n",this_player());
    return 1;
    }
  write("Better to lie down in bed.\n");
  return 1;
}

stand_up(string str)
{
  if (this_player() != person_in_bed) return 0;
  write("You stand up from the bed.\n");
  tell_room(this_object(),QCTNAME(this_player())+" stands up from the bed.\n",this_player());
  person_in_bed = 0;
  return 1;
}

leave_inv(object ob, object to)
{
  if (living(ob)) {
    if (check_bed()) return 1;
    }
  ::leave_inv(ob,to);
}

