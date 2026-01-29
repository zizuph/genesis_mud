#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <state_desc.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WIZ_DIR    "/d/Gondor/"

public string  print_stats();

public void
create_gondor() 
{
    set_short("the workroom of Councellor Olorin");
    set_long(BS("Heaps of papers lying around on a desk and on the floor "
        + "almost completely fill the room. Nevertheless, that's the place "
        + "where Olorin works. There is a single window here. On the "
        + "wall opposite the window hangs a painting.\n"));
    add_exit("/d/Genesis/wiz/entrance","entrance","@@check_exit@@");
    add_exit("/d/Genesis/wiz/virtual","virtual","@@check_exit@@");
    add_exit("/d/Genesis/wiz/domain","tower","@@check_exit@@");
    add_exit("/d/Debug/debuglord/lordroom","lords","@@check_exit@@");
    add_exit("/d/Genesis/wiz/admin","admin","@@check_exit@@");
    add_exit("/d/Genesis/start/human/town/tower","human","@@check_exit@@");
    add_exit("/d/Genesis/start/hobbit/v/guild","hobbit","@@check_exit@@");
    add_exit("/d/Genesis/start/elf/room/vill_board","elf","@@check_exit@@");
    add_exit(GONDOR_DIR + "workroom",       "meeting", "@@check_exit@@");
    add_exit(RANGER_DIR + "startchamber",   "guild",   "@@check_exit@@");
    add_exit(RANGER_DIR + "gondor_council", "council", "@@check_exit@@");
    add_exit(RANGER_DIR + "gondor/post",    "post",    "@@check_exit@@");
    add_exit(EDORAS_DIR + "guild",          "rohan",    "@@check_exit@@");
    add_exit(MAGES_DIR + "startroom",       "mages",   "@@check_exit@@");
    add_exit(MAGES_DIR + "throne_room",      "nazgul",  "@@check_exit@@");
    add_exit(SHIRE_DIR + "guild/rooms/hguild2","shire","@@check_exit@@");
    add_exit("/d/Terel/common/town/street/guild","terel","@@check_exit@@");
    add_exit(WIZ_DIR + "olorin/Sorry_Im_idle","idle","@@check_exit@@");
    add_exit(WIZ_DIR + "olorin/battle_test","battle","@@check_exit@@");
    add_exit(WIZ_DIR + "olorin/battle_test","back","@@back_exit@@");
    add_exit("/d/Gondor/olorin/robot", "robot", "@@check_exit");
    add_item(({"heap","heaps","heaps of papers","papers"}),BSN(
        "The papers with numbers and letters in all "
      + "possible combinations. Only a real wiz might be able to "
      + "make anything out of them."));
    add_item(({"picture","painting"}),BSN(
        "Not what one would call a nice painting, but "
      + "very impressive. It's beauty stems from its profund depth "
      + "and great clarity. It shows an artist's impression of the "
      + "death of Isildur at the beginning of the Third Age."));
    add_item(({"window","view"}),BSN("Looking out of the window you realize that "
      + "you must be somewhere in the White Tower of Minas Tirith. "
      + "Below, you can see the city with it's seven circles. Looking "
      + "farther, you can see the river Anduin and across the river you "
      + "see the lands of Ithilien lying under the Shadow of Mordor."));
    add_item(({"desk"}), BSN(
        "This ancient desk is covered with many papers."));

    add_cmd_item( "stats", "print", print_stats);

    clone_object("/d/Gondor/mercade/bagpipes")->move(TO);
    clone_object("/d/Gondor/mercade/kilt")->move(TO);
}

int 
query_prevent_snoop()
{
    return 1;
}

int 
check_exit()
{
    if(TP->query_wiz_level())
        return 0;

    write("You cannot go there! You can only go 'back'!\n");
    return 1;
}

int 
back_exit()
{
    TP->move_living("back", TP->query_prop(LIVE_O_LAST_ROOM));
    return 1;
}

void 
init()
{
    ::init();

    if (TP->query_real_name() == "olorin" &&
        !present("_reader_", TP))
        clone_object("/secure/mail_reader")->move(TP,1);
}

public int
remove_herb_file(string file)
{
    if (member_array(file, herbs) < 0)
        return 0;
    herbs -= ({ file });
    return 1;
}

public string
print_stats()
{
    int     st = sizeof(SD_AV_TITLES),
	    s,
	    i,
	    sum;
    object *all = filter(users(), not @ &->query_wiz_level());
    string  msg = "";

    for (i = 0; i < st; i++)
	msg += sprintf("%-16s %5d\n", 
		       CAP(SD_AV_TITLES[i]),
		       sizeof(filter(all, &operator(==)(SD_AV_TITLES[i]) @
				     &->query_exp_title())));

    for (i = 0, s = sizeof(all); i < s; i++)
	sum += all[i]->query_average_stat();

    sum /= s;
    msg += "Average stat of all mortals = " + sum;
    sum = sum * st / 100;
    sum = ((sum >= st) ? st - 1 : sum);

    msg += " (" + SD_AV_TITLES[sum] + ").\n";
    return msg;
}

    
