#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;


object ghost;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
    add_item(({"ancient stone walls","stone walls","walls"}),
      "Ancient walls of stone rise to a low ceiling in this "+
      "cairn.\n");
    add_item(({"ceiling","low ceiling"}),
      "Just above your head is the ceiling of the cairn. It is "+
      "low, typical of dwarven design.\n");
    add_item(({"cairn","ancient dwarven cairn","dwarven cairn"}),
      "You stand within the resting place of a dwarven warrior "+
      "of the Neidar clan.\n");
    add_item(({"floor","dust"}),
      "The floor here is covered with dust. You doubt anyone has "+
      "been here for a long time.\n");
    add_item(({"lid","coffin's lid"}),
      "The lid of the coffin looks very heavy. You doubt " +
      "you could lift it.\n");
    add_item(({"stone coffin","coffin"}),
      "This stone coffin is where the remains of Teregul Skybolt, " +
      "Hero of the Neidar, now rests. It is covered with inscriptions " +
      "and bas-reliefs of his exploits.\n");
    add_item(({"inscriptions","bas-reliefs","bas reliefs"}),
      "The inscriptions and bas-reliefs on the coffin detail " +
      "this fallen warrior's achievements. From the looks " +
      "of things, no small amount of goblins, ogres, " +
      "and giants fell to his mighty axes.\n");
    add_item(({"crypt","room"}),
      "This is the crypt of a dwarven hero, Teregul Skybolt. " +
      "\n");

    DARK;
    add_cmd_item(({"coffin","stone coffin"}),
      "open","@@open_coffin");

    add_exit(ROOM + "c4","south",0);

    reset_dwarf_room();
}

string
open_coffin()
{
    if(TP->query_alignment() > 100)
    {
	write("You would desecrate the grave of a noble warrior? Shame " +
	  "on you. Regardless, the coffin's lid is far too heavy to lift.\n");
	TP->set_alignment(TP->query_alignment() - 400);
	TP->change_prestige(-4);
	return "";
    }
    write("The lid of the coffin is far too heavy to lift.\n");
    return "";
}

string
short_descr()
{
    return "the crypt of a dwarven hero";
}

string
long_descr()
{
    return "You stand at the final resting place of one " +
    "of the greatest dwarven warriors, Teregul Skybolt. Apart from a " +
    "large stone coffin in the center of the room, this " +
    "crypt is bare of decoration, and all that fills it is dust, undisturbed until now.\n";
}

void
ghost_makes_entrance(object ob)
{
    tell_room(TO, "\nFrom out of the stone coffin, a dwarven " +
       "ghost arises!\n");
    ghost = clone_object(LIVING + "ghost_teregul");
    ghost->move(TO);
    ghost->quest_spool();
    ob->add_prop(SPOKEN_TO_TEREGUL, 1);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if(ob->query_prop(FREED_SPIRIT) &&
    !ob->query_prop(SPOKEN_TO_TEREGUL))
    {
    set_alarm(2.0, 0.0, &ghost_makes_entrance(ob));
    }
}
