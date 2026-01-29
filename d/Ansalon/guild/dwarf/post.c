#pragma strict_types

inherit "/d/Ansalon/estwilde/std/inside_base";

inherit "/d/Genesis/lib/post";

#include "guild.h"

#include <files.h>
#include <mail.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

int feather_no = 0;

void
reset_dwarf_room()
{
    return;
}

void
create_dwarf_room()
{
    set_short("Post Office in Iron Delving");
    set_long("You stand in the small stone building that " +
      "has been designated as the Post Office of Iron Delving. " +
      "Many trained pigeons, the animals that carry the dwarves mail to " +
      "places all around the realms, coo quietly in their wicker " +
      "cages.\n");

    add_item(({"pigeons","trained pigeons","wicker cages","cages"}),
      "White pigeons have been trained to carry mail messages " +
      "to other post offices around the realms. Unfortunately, " +
      "none have been trained for personal use, so " +
      "unfortunately none are for sale. A few loose feathers " +
      "have fallen onto the base of the cages, which you " +
      "could probably gather.\n");

    add_exit("/d/Ansalon/estwilde/iron_delving/r10","north",0);

    add_cmd_item("feathers","gather","@@gather_feathers");

    reset_dwarf_room();
}

int
silent_room(string str)
{
    if(query_verb() == "gather")
    {
	return 0;
    }

    return ::silent_room(str);
}

void
reset_feathers()
{
    feather_no = 0;
}

string
gather_feathers()
{
    if(feather_no == 1)
    {
	write("There are no feathers to gather at the moment. "+
	  "Come back later.\n");
	return "";
    }

    write("You gather a few feathers from the pigeon cages.\n");
    say(QCTNAME(TP)+ " gathers a few feathers from the pigeon " +
      "cages.\n");
    clone_object("/d/Ansalon/estwilde/obj/feather")->move(TP);
    clone_object("/d/Ansalon/estwilde/obj/feather")->move(TP);
    clone_object("/d/Ansalon/estwilde/obj/feather")->move(TP);
    feather_no = 1;
    set_alarm(600.0, 0.0, "reset_feather");
    return "";
}

void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

void
mail_message(string new)
{
    write("\nYou have" +new+ " mail for you in the " +
      "Iron Delving" +
      " post office.\n\n");
}
