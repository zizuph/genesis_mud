
inherit "/std/room";
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


/*prototype*/
int exam(string str);

/*variables*/
string *wiznames, *wizdesc;

void
load_board()
{
    object bb = clone_object("/std/board");
    bb->set_board_name("/d/Ansalon/common/log/board_data");
    bb->set_silent(1);
    bb->set_num_notes(30);
    bb->set_err_log("/d/Ansalon/common/log/boarderrors");
    bb->set_show_lvl(0);
    bb->set_remove_lvl(30);
    bb->set_remove_str("You are not allowed to remove notes here.");
    bb->move(TO);
    bb->set_fuse(1);
}

void
create_room()
{
    set_short("The Ansalon Workroom");
    set_long("You have entered the Ansalon Workroom.\n" +
      "There are nine chairs around a large round table. The table " +
      "itself is made of oak, and it has a large map of Ansalon " +
      "carved in it. There are also many smaller maps on the walls. "+
      "The room is large and round, as if it were built with " +
      "the table in mind. Also on the walls are a some portraits " +
      "of some of the wizards who have contributed greatly " +
      "to Ansalon, Krynn, and Genesis over the years. " +
      " The domain entrance to Ansalon is north of here, " +
      "while the Krynn workroom is to the south." +
      "\n");

    INSIDE;
    add_prop(ROOM_I_LIGHT ,10);

    seteuid(getuid(TO));
    /*
	restore_object("/d/Ansalon/log/awizs");
    */
    add_item(({"picture", "portrait", "portraits", "pictures", "wizards",
	"wizard"}), "There are 10 pictures here. You can examine each one by examining picture 1, picture 2, etc.\n");
    add_item(({"maps", "smaller maps", "small maps"}), 
      "You see maps of Neraka, Silvanesti, Northern and Southern " +
      "Ergoth, Godshome, Sanction, Dragon Isles, Minotaur Islands, " +
      "Istar, Kendermore, and many many more.\n");
    add_cmd_item(({"chair", "in chair", "on chair"}), "sit", "You sit in one " +
      "of the nine chairs at the round oaken table. It makes " +
      "you feel like a true Wizard of Ansalon.\n");
    add_cmd_item(({"up", ""}), "stand", "You stand up from the chair.\n");
    add_item(({"chairs", "chair", "table", "oak table", "round table",
	"large table", "large round table", "oaken table"}),
      "The large round table is surrounded by nine chairs. " +
      "You could try sitting in one.\n");
    add_item(({"map", "large map", "carving", "map on table",
	"large map of Ansalon", "map of Ansalon", "map of ansalon"}),
      "@@display_map@@");

    add_exit("/d/Ansalon/common/domain_entr", "north");
    add_exit("/d/Krynn/workroom", "south");
    load_board();
}

string display_map()
{
    return(read_file("/d/Ansalon/common/maps/Ansalon", 1, 44));
}

void
init()
{
    ::init();
    ADD("exam","examine");
    ADD("exam","exa");
    ADD("exam","look");
}

int
exam(string str)
{
    string *wiznames = ({"Rastlin","Nick","Grrrr","Dorak","Percy","Aridor","Macker","Jeremiah","Arman","Ashlar"});

    string *wizdesc = ({"Rastlin is the founder of Krynn. He's the man who brought " +
      "Dragonlance to Genesis. He retired  a long time ago. Or so everyone thought... "+
      "Who knows when he will be back?\n",
      "Nick was an arch from Krynn. He did a lot for Krynn and " +
      "Genesis, but retired a while back after getting married.\n",
      "Grrrr the gnome wizard, also an ex-Lord of Krynn now alas gone.\n",
      "Dorak was also Lord of Krynn for a short time, and also " +
      "now no longer with us.\n",
      "Percy was Madwand turned Lord of Krynn and "+
      "guildmaster of the Knights, but finally got dragged away by RealLife.\n",
      "Aridor is the current Warden of Krynn, ex-lord and guildmaster " +
      "of the Cabal of Hiddekul and the Krynn racial guild. " +
      "You will most often find Aridor idling, but he will eventually " +
      "get back to any questions you raise to him. " +
      "It was his idea to create the domain of Ansalon.\n",
      "Macker was the founder of Ansalon. He was the first " +
      "Lord of Ansalon.\n",
      "Jeremiah was the second Lord of Ansalon, and the first " +
      "Lord to open an area to the mortal realms. He disappeared " +
      "into the black void known as Microsoft, and will be sadly " +
      "missed.\n",
      "Arman is the third and current Lord of Ansalon. He was " +
      "the creator of Flotsam, its surrounding forest lands, " +
      "Kalaman, Estwilde plains, and the dwarven hill dwarf " +
      "clan.\n",
      "Ashlar is the first and current Warden of Ansalon. Ashlar " +
      "is responsible for the creation of the center of the " +
      "Queen of Darkness' power, the much feared city of Neraka. " +
      "He is also working on getting the occupational Priests " +
      "of Takhisis off the ground.\n"});
    int numpics, ok,whichpic;
    if (!str)
	return 0;

    numpics = sizeof(wiznames);
    ok = sscanf(str, "picture %d", whichpic);
    if (!ok)
	ok = sscanf(str, "at picture %d", whichpic);
    if (!ok)
	ok = sscanf(str, "%d", whichpic);
    if (!ok)
	return 0;
    if (whichpic > numpics || whichpic < 1)
    {
	NF("Which picture did you want to look at?\n");
	return 0;
    }
    write("This is a picture of " + wiznames[whichpic-1] + ".\n");
    write(wizdesc[whichpic-1]);
    return 1;
}


wizcheck()
{
    if (this_player()->query_wiz_level())
	return 0;
    else
	return 1;
}


