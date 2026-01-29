/* Vladimir date */

inherit "/std/room";
inherit "/d/Roke/gresolle/open/librarian";
#include <macros.h>
#define PERS METNAME
#define TP this_player()
#define TO this_object()
static void create_board();
create_room()
{
object board;
   set_short("Workroom");
   set_long(
      "This room is extremely messy, you get the "+
      "impression that the current occupant just moved in. "+
      "There is a large round table protruding rom the mess "+
      "in the corner. Surprisingly enough you notice that it is "+
      "kept rather clean and well organized. The walls are "+
      "adorned with many strange and foreign rugs that no doubt "+
      "came from far away lands. "+
      "There is a small hole in the floor near the southeast corner of the "+
      "room, it looks like an exit. On the opposite corner there is a "+
      "medium sized redwood desk. Mounted upon the north wall is a strange "+
      "painting. The whole room smells of trees and meadows.\n");
   
   add_item(({"painting", "picture"}),
      break_string("Death himself is depicted in this picture. Holding his "+
         "scythe close at hand he looks over all of the unfortunate "+
         "lost souls within his realm, within ever lasting Hell "+
         "His eyes glow red with an evil malevolence unlike any "+
         "other. He seems to be pointing at someone, someone not "+
         "from within the painting. Who could he be pointing to? "+
         "The red inside his sockets glow brighter as you realize, "+
         "Death wants you!\n", 70));
   add_item(({"statues", "miniature statues"}),
      break_string("These staues are carved from Oak wood, and have very "+
         "fine detail carved on them. Most are representations "+
         "of nomads, vagabonds, and a few monks. Each has it's "+
         "own individual look to it. Each seems so real. The "+
         "longer you stare at them, te more they look like they "+
         "are moving. In fact they have begun to flow in a gradual "+
         "hypnotic pattern. You start to become entranced. Then, "+
         "suddenly, you turn away. You feel extremely dizzy, and "+
         "begin to fall. Luckily you are able to catch yourself "+
         "in time before you have a chance to seriously injure "+
         "yourself.You make a quick "+
         "glance back at the figurines, and notice a new one. This "+
         "looks vaguely familiar, it's features, simaller to your "+
         "own.\n", 70));
   add_item(({"desk", "desks"}),
      break_string("This desk is made of Redwood, and shines with a blinding "+
         "gloss. There is only one drawer on the desk however. On the top of "+
         "the desk sits quite a few miniature statues, carved from wood.\n", 70));
   add_item(({"drawer", "drawers"}),
      break_string("As you examine the drawer closer you notice just how "+
         "large it is. There is a strange ornately carved handle "+
         "on the front of the drawer.\n", 70));
   add_item(({"handle", "drawer handle"}),
      break_string("You take a closer look at the handle and notice that "+
         "it seems to be made from ivory. At the very end of the "+
         "there is a small button.\n", 70));
   add_item(({"button", "handle button"}),
      break_string("The button looks like it is made of obsidian, wonder "+
         "what it is for?\n", 70));
   add_exit("/d/Immortal/mrpr/workroom", "mrpr");
add_exit("/d/Roke/workroom", "roke");
add_exit("/d/Kalad/milashk/workroom2", "millhouse");
add_exit("/d/Genesis/start/human/town/jetty2", "relax");
   add_exit("/d/Kalad/antharanos/workroom", "antharanos");
   add_exit("/d/Genesis/wiz/post", "post");
   add_exit("/d/Roke/vladimir/arena", "hole");
   add_exit("/d/Roke/vladimir/temp", "south");
   add_exit("/d/Immortal/workroom", "imm");
   add_exit("/d/Roke/varl/atuan/cape/guild/board", "board");
   add_item("rug", "@@suit");
set_lsave("/d/Roke/vladimir/workroom");
set_lib("/d/Roke/varl/atuan/cape/guild/l");
config_librarian();
 reset_room();
}
void
init()
{
   ::init();
init_lib();
   write("The workroom greets you.\n");
   add_action("push", "push");
}
int
push(string arg)
{
   if(!arg)
      {
      notify_fail("Push what?\n");
      return 0;
   }
   if(arg == "button" || arg == "drawer button")
      {
      write("You here the sound of grinding metal.\n");
      say(PERS + " steps over and pushes the button on the desk.\n");
      write(break_string("Suddenly, some of the rugs on the wall part, revealing "+
            "an exit.\n", 70));
   add_exit("/d/Roke/varl/atuan/cape/guild/councilrm", "north");
      return 1;
   }
}
string
suit()
{
   if(TP->query_name() == "Vladimir")
      {
      write("The rugs remind you of your many long journeys over the years.\n");
      return"";
   }
   else
      {
      write(break_string("These rugs all but completely cover the walls. They look "+
            "exotic, and old. You get the impression that they have travelled "+
            "long distances to get here. They seem to be made of a very fine "+
            "material unknown to you. In fact there are so many rugs on the walls "+
            "you hardly notice if there are any walls.\n", 70));
      return"";
   }
}
void
reset_room()
{
    if (!present("board", TO))
        create_board();
   remove_exit("north");
}
static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name("/d/Roke/Cirath/board");
        board->set_num_notes(27);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_lvl(19);
        board->set_remove_str("Sorry, mortals are not allowed to remove notes.\n");
        board->move(TO);
    }
    return 0;
}
