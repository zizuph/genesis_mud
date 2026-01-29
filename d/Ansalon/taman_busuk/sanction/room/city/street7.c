// Make the quest reset, so its not just once per arma.

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit SANCOUTROOM;

#define FREED_MERCHANT "_i_rescued_the_sanction_merchant"

int merchant_freed = 0;

void
reset_sanction_room()
{
    merchant_freed = 0;
}

void
create_sanction_room()
{
    set_short("A street passing through the center of Sanction.\n"+
      "An iron stanchion stands here, a cage hanging from it");
    set_long("@@long_descr");
    add_item("street","You are standing on a cobbled street that " +
      "runs through the middle of the slums of Sanction. You see " +
      "an entrance to one of these districts to your east.\n");

    add_item(({"stanchion","iron stanchion"}),
      "Rising about thirty feet into the air on the western side of " +
      "the street is a great iron stanchion. Hanging from it by a " +
      "chain is a cage, used to house those who defy the " +
      "Dragon Highlord Ariakas.\n");
    add_item("chain","An iron chain runs from the stanchion to the " +
      "cage.\n");
    add_item("cage","Hanging from the tall iron stanchion is a " +
      "cage, the final punishment for those who defy the rule of the " +
      "dragonarmies here in Sanction. Within you see the rotting " +
      "remains of various men and women. A large lock keeps the " +
      "cage closed shut.\n");
    add_item(({"large lock","lock"}),"A large padlock, used to " +
      "keep the cage closed.\n");
    add_item(({"remains","men","women"}),
      "The sad remains of those who have defied the Dragonlords sit " +
      "in a pile in the cage before you. The remains are little more " +
      "than bones, having been picked clean by kites and crows.\n");

    add_cmd_item(({"lock","lock on cage","cage"}),
      ({"pick","unlock"}),"@@pick");


    add_exit(SCITY + "street6","south",0);
    add_exit(SCITY + "street8","north",0);
    add_invis_exit(SCITY + "slum5","east",0);

    slum_descriptions();
}

string
long_descr()
{
    return tod_short_descr() + volcanoes() + tod_long_descr()+
    "Here you walk along a street that cuts through the "+
    "center of a teeming slum consisting of filthy, closely-packed "+
    "buildings that create a maze of winding alleys.\n"+
    "An iron stanchion stands here, a cage hanging from it.\n";
}

void
free_merchant(object who)
{
    object merchant;

    if(TP->test_bit("ansalon",0,15))
    {
	write("The cage is empty, and there appears to be "+
	  "nothing of interest in there, so you close the cage again.\n");
	say(QCTNAME(TP)+ " peers inside the cage, and then swiftly closes it.\n");
	return;
    }

    tell_room(TO, "A ragged merchant leaps stiffly from the cage, " +
      "closing it with a bang behind him.\n");

    merchant = clone_object(SNPC + "quest_merchant");
    merchant->move(TO);
    merchant->quest_spool();
    who->add_prop(FREED_MERCHANT, 1);
    merchant_freed = 1;
}

string
pick()
{
    if(TP->query_skill(SS_OPEN_LOCK) < 30)
    {
	write("You just don't have the skills or tools to " +
	  "be able to pick the lock on the cage.\n");
	return "";
    }

    if(merchant_freed)
    {
	write("The lock is broken, you cannot pick it.\n");
	return "";
    }

    write("With a furtive glance, you quickly pick the lock on the cage... it's " +
      "door squeaks open.\n");
    say(QCTNAME(TP)+ " furtively glances around, and then quickly picks " +
      "the lock on the cage. It's door squeaks open.\n");

    free_merchant(TP);
    return "";
}

