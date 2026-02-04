inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

#define BRANCH "/d/Terel/mecien/valley/branch"
#define NBRANCHES 2

int nbranches;

public void
reset_room()
{
   nbranches = NBRANCHES;
   if (present("branch")) return;
   clone_object(BRANCH)->move(this_object());
}

public void
create_room()
{
   set_short("Ledge");
   set_long("This is a ledge jutting out from the mountains, it stands " +
      "out to provide a majestic view of a large valley below it. " +
      "This valley, covered mostly in forests, seems to be divided " +
      "up in the midst of the four seasons. In the middle of the " +
      "valley there seems to be a small lake, but it is difficult " +
      "to see. Here on the ledge is a strange withered tree. There " +
      "are steps carved in the mountains that lead down, east or " +
      "west, into the valley. There is a mist to the south.\n");
   
   add_item("valley", "It streches out below you, beautiful and majestic.\n");
   add_item("lake", "It rests in the middle of the valley below.\n");
   add_item("steps", "They lead down to the east and west. They are excellently carved and look very ancient.\n");
    add_item("forests", "There seem to be four different forests in the valley.\n");
   add_item("mist", "It lingers to the south.\n");
   add_exit("/d/Terel/mecien/valley/wlanding", "west", "@@descend");
   add_exit("/d/Terel/mecien/valley/elanding", "east", "@@descend");
   add_exit("/d/Terel/mecien/valley/entrance", "south", 0);
   
   add_item(({"tree", "withered tree"}),
      "A strange old withered tree, it has been covered with\n" +
      "some kind of inscription. There are a few branches left on it.\n");
   add_item(({"branch", "branches"}),
            "They look old, but would probably make excellent torches. " +
   "They seem to be rather fragile.\n");
   add_cmd_item("branch", "break", "@@do_break");

   reset_room();
}

public int
descend()
{
   write("You descend the stairs.\n");
   say(QCTNAME(this_player()) + " descends the stairs.\n");
   return 0;
}

public int
do_read(string str)
{
   notify_fail("Read what?\n");
   if (str != "tree" && str != "inscription") return 0;
   
   if (this_player()->query_skill(SS_LANGUAGE) < 5)
   {
      write("You cannot understand the words.\n");
      return 1;
   }

   write("The withered tree reads: When the four seasons are " +
         "brought before the foundation, then shall we see " +
         "the light.\n");
   say(QCTNAME(this_player()) + " looks closely at the tree.\n");
   return 1;
}

public void
init()
{
   ::init();
   add_action(do_read, "read");
}

public string
do_break()
{
    if (nbranches <= 0)
        return "There are no branches within your reach.\n";

    say(QCTNAME(this_player()) + " breaks of a branch from the tree. " +
        "The branch falls to the ground.\n");

    seteuid(getuid());
    clone_object(BRANCH)->move(this_object());
    nbranches--;
    
    return "You break of a branch from the tree. It falls to the ground.\n";
}

public int
block()
{
   write("That exit isn't ready yet, please come back later.\n");
   return 1;
}
