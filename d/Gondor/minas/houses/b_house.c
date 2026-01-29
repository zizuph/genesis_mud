#pragma strict_types

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

object baranor;

void reset_room();

void
create_room()
{
  set_short("living room");
  set_long(BSN("You are standing in the living room of the house. The stone "+
    "walls are decorated by tapestries. A large table stands here, a few "+
    "chairs beside it, and a small desk in a corner."));

  add_item(({"walls", "tapestries", }), BSN(
      "The stone walls are decorated by large tapestries. They show scenes "
    + "out of the legends of the First Age. You can make out Beren listening "
    + "to Luthien Tinuviel in the forests of Neldoreth, Tuor and Voronwe in "
    + "front of Amon Gwareth in the valley of Tumladen, and Earendil at the "
    + "prow of his ship Vingilot."));
  add_item("table",BSN("The table is large and skillfully crafted, with "
    + "well-turned legs."));
  add_item("chairs",BSN("Obviously crafted by the same artisan as the table "
    + "with the same well-turned legs."));
  add_prop(ROOM_I_INSIDE,1);
  clone_object(MINAS_DIR + "obj/bar_indoor")->move(TO);
  clone_object(MINAS_DIR + "obj/bar_desk")->move(TO);

  reset_room();
}

void
init()
{
    ::init();
    add_action("sit_chair","sit");
    add_action("stand_up","stand");
    add_action("stand_up","rise");
}

int
sit_chair(string str)
{
    if (!str)
        NFN0("Sit where?");
    if (str != "chair" && str != "in chair" && str != "on chair")
        NFN0("Sit in a chair, maybe?");
    if (TP->query_prop("_sitting"))
        NFN0("But you are already sitting in one of the chairs!");

    write("You sit down in one of the chairs by the table.\n");
    say(QCTNAME(TP)+" sits down in one of the chairs by the table.\n",TP);
    TP->add_prop("_sitting",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT,", sitting in a chair");
    return 1;
}

int
stand_up(string str)
{
    if (str != "up")
        NFN0(CAP(query_verb())+" what? Up?");
    if (!TP->query_prop("_sitting"))
        NFN0("But you are not sitting!");

    write("You rise up from the chair fearing it could break.\n");
    say(QCTNAME(TP)+" rises up from the chair.\n",TP);
    TP->remove_prop("_sitting");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
        return;
    if (living(ob) && ob->query_prop("_sitting"))
    {
        write("You rise up from the chair you are sitting in.\n");
        say(QCTNAME(TP) + " rises up from the chair.\n");
        TP->remove_prop(LIVE_S_EXTRA_SHORT);
    }
}

void
add_stuff()
{
    if (!objectp(baranor))
    {
      baranor = clone_object(MINAS_DIR + "npc/baranor");
      baranor->arm_me();
      baranor->move_living("down", TO);
      tell_room(TO,QCNAME(baranor) + " arrives.\n");
      baranor->command("sit in chair");
    }
    present("desk")->reset_container();
}

void 
reset_room()
{
    set_alarm(0.0, 0.0, add_stuff);
    present("desk")->reset_container();
}
