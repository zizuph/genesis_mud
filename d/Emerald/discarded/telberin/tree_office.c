inherit "/std/room";

#include "default.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <macros.h>

void reset_room();
int do_read(string str);

object genealogist;

void
create_room()
{
   set_short("Neat office");
   set_long("This neat little office is hidden away from the rest of the " +
            "main offices. A small amount of light filters in through a " +
            "small window, illumating the desk and cabinets. Rows upon rows " +
            "of files are stacked neatly on top of the cabinets, and in the " +
            "far corner you spy a strongbox beneath a veritable pile of " +
            "paperwork. There is a sign proudly displayed on the desk in " +
            "front of you.\n");
   
   add_prop(ROOM_I_INSIDE, 1);

   add_exit(THIS_DIR + "office", "south");
   
   add_item("window","The window is small, only a few feet across, if "+
	"that. A mediocre amount of light is coming through it.\n");
   add_item("desk", "The desk is quite neat, made from a beautiful "+
	"type of oak, dark and rich. There are a few files stacked "+
	"neatly on the desk, next to the small sign.\n");
   add_item(({"cabinets","cabinet"}), "The cabinets are old, made of some " +
   "dark wood and hold at least a few hundred files each. On top of them " +
   "there are even more files, indicating perhaps a requirement for a new " +
   "cabinet or two.\n");
   add_item("files", "There are files everywhere: piles of them on top of " +
            "the cabinets and a large amount sitting on a strongbox in the " +
            "far corner. Also there are a few files neatly stacked on the " +
            "desk.\n");
   add_item(({"box","strongbox"}), "It is in the far corner "+
	"buried beneath a huge pile of paperwork. It looks to be made "+
	"from iron, heavy and nearly indestructable.\n");
   add_item(({"papers","paperwork"}), "The paperwork consists of a few " +
   "files and lots of unsheathed papers just piled on top of each other.\n");
   add_item("sign", "The sign is written in delicately ornate writing, " +
            "which you may have to bend closer to read properly.\n");

    set_alarm(1.0, 0.0, reset_room);
}

void
reset_room()
{
    if (!genealogist)
    {
        genealogist = clone_object(NPC_DIR + "gnome");
        genealogist->move(TO);
	tell_room(TO, "The owner of this office arrives from his quarters.\n");
    }
    return;
}

void
init()
{
   ::init();
   add_action(do_read, "read");
}

int
do_read(string str)
{
   NF("Read what?\n");
   if(!strlen(str) || str != "sign")
	return 0;

   write("\t\t\tGENEALOGICAL REGISTER!\n\n"+
	 break_string("If you ask me one of the following questions, I "+
	"shall do the best I can to answer you at a reasonable fee. If "+
	"you want to know my fee for the answer to a certain question, "+
	"you can precede the question by the word 'test'\n", 76) +
	"\n\tWho are my ancestors?\n"+
	"\tWho are the ancestors from <name>?\n"+
	"\tWho are my descendants?\n"+
	"\tWho are the descendants from <name>?\n"+
	"\tIs <name> related to me?\n"+
	"\tIs <name> related to <name>?\n\n");
   say(QCTNAME(TP)+" reads the sign.\n");
   return 1;
}

   
