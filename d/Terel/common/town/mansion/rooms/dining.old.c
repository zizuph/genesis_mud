inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#include <stdproperties.h>

#define TO          this_object()
#define TP          this_player()
#define OTHER       MANSION + "rooms/s_stair1.c"
#define MAX_NO_SERV 3

#define FIREPLACE   (MANSION + "second/fireplace")
#define STAIRS      (MANSION + "rooms/bstairs_mid")

void do_add_exits();
void do_remove_exits();

int p_mantle, called;
object servant, table;

reset_room()
{
    if (p_mantle) do_remove_exits();
    p_mantle = 0;
    called = MAX_NO_SERV;
}

create_room(){
   set_short("Dining Hall");
   set_long(
      "This opulent and grand dining hall stands in a state of slow\n"
      + "decay and disintegration.  Though it is in bad shape, it's\n"
      + "nowhere near the state of most of the mansion.  Its oaken floor\n"
      + "is smooth and uncracked, though layered in dust.  The ornate\n"
      + "tiles and wall paper still decorate the walls, they are unstained\n"
      + "but somewhat covered in webs.  A large fireplace decorates the\n"
      + "south side of the hall, its marble polished and gleaming.\n"
    + "A small silver bell hangs from the ceiling, suspended on a\n"
    + "long silver chain.\n"
   );
   
   seteuid(getuid(TO));
   table=clone_object(MANSION + "obj/table");
   table->move(TO);
   
    add_item(({"mantle", "mantlepiece"}),
     "It is rose coloured and carved with roses.\n");
    add_item("fireplace", break_string("It is a massive fireplace, " +
     "one of a particular beauty.  It is carved from a white marble " +
     "and appears to be very large.  A long mantle of rose coloured " +
     "marble stands in contrast.\n",70));
    add_item("bell", "It is a small silver bell, it is ornate and has "
     + "a bright cheerful sound.\n");
    add_item("chain", "It is a silver chain that hangs from the ceiling,\n"
     + " on which hangs a silver bell.\n");
   
    add_cmd_item("bell", "ring", "@@bring_food");
    add_cmd_item("mantle", ({"press", "push"}), ({"@@press_mantle", "@@press_mantle"}));
    add_cmd_item("fireplace", "enter", "@@enter_fireplace");
   
    add_exit(MANSION + "rooms/kitchen", "east", 0);
    add_exit(MANSION + "wing_n5", "southwest", 0);
   
    add_prop(OBJ_S_WIZINFO, "To open/close the secret passage use: \n" +
      "call here open_stairs,\n" +
      "call here rem_stairs.\n");

    p_mantle = 0;
    called = MAX_NO_SERV;
}

void
do_add_exits()
{
    seteuid(getuid());
    TO->add_exit(MANSION + "rooms/s_stair1", "stairs", 0);
    TO->add_my_desc("A small staircase stands open next to the fireplace.\n");
    FIREPLACE->add_exit(STAIRS, "southwest", 0);
    STAIRS->add_exit(FIREPLACE, "northeast", 0);
}

void
do_remove_exits()
{
    seteuid(getuid());
    TO->remove_exit("stairs");
    TO->remove_my_desc();
    FIREPLACE->remove_exit("southwest");
    STAIRS->remove_exit("northeast");
}

press_mantle(){
   say(QCTNAME(TP) + " presses the mantle.\n");
   if (p_mantle) {
      write("You press the mantle.... \n" +
         "With a low grinding sound the small secret passage closes!\n");
      do_remove_exits();
      p_mantle = 0;
      return 1;
   }
   write("You press the mantle.... \n" +
      "With a low grinding sound a small secret passage opens!\n" +
      "It is a staircase leading down!\n");
   do_add_exits();
   p_mantle = 1;
   return 1;
}

enter_fireplace()
{
    TP->move_living("into the fireplace", MANSION + "second/fireplace");
    return 1;
}

bring_food(){
    seteuid(getuid(TO));
    write("You ring the little silver bell.\n");
    say(QCTNAME(TP) + " rings the little silver bell.\n");
    if (!servant && called > 0) {
        servant = clone_object(MANSION + "mon/servant");
        servant -> move_living("xx", MANSION + "rooms/dining");
	called--;
        call_out("put_stuff", 6);
    }
    return "";
}

put_stuff()
{
    if (!servant) return;
    if (!present("servant", TO)) return;
    servant -> lay_table();
    servant -> command("say Dinner will soon be served!");
    servant -> command("bow");
    servant -> command("east");
    call_out("fetch_food", 30);
}

fetch_food()
{
    if (!servant) return;
    clone_object(MANSION + "obj/meal") -> move(servant);
    servant -> command("west");
    if (!present("servant", TO)) return;
    servant -> serve_food();
}

open_stairs()
{
   if (p_mantle) {
       write("The stairs are already open!\n");
   }
   else {
   TO->add_exit(MANSION + "rooms/s_stair1", "stairs", 0);
   TO->add_my_desc("A small staircase stands open next to the fireplace.\n");
   p_mantle = 1;
   }
}
    
rem_stairs()
{
   if (!p_mantle) {
        write("The stairs aren't here at the moment!\n");
   } else {
       TO->remove_exit("stairs");
       TO->remove_my_desc();
       p_mantle = 0;
   }
}
