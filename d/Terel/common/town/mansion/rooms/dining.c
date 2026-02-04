inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#include <stdproperties.h>

#define TO          this_object()
#define TP          this_player()
#define MAX_NO_SERV 3

#define HERE        (MANSION + "rooms/dining")
#define SSECRET     (MANSION + "rooms/s_stair1")

#define FIREPLACE   (MANSION + "second/fireplace")
#define STAIRS      (MANSION + "rooms/bstairs_mid")

void do_add_exits();
void do_remove_exits();

int p_mantle, called, raised=0;
object servant, table;

public void
reset_room()
{
    if (p_mantle) do_remove_exits();
    p_mantle = 0;
    called = MAX_NO_SERV;
}

public void
create_room()
{
   set_short("Dining Hall");
   set_long("This opulent and grand dining hall stands in a state of slow "
          + "decay and disintegration.  Though it is in bad shape, it's "
          + "nowhere near the state of most of the mansion.  Its oaken floor "
          + "is smooth and uncracked, though layered in dust.  The ornate "
          + "tiles and wall paper still decorate the walls, they are unstained "
          + "but somewhat covered in webs.  A large fireplace decorates the "
          + "south side of the hall, its marble polished and gleaming.\n"
          + "A small silver bell hangs from the ceiling, suspended on a "
          + "long silver chain.\n");

    seteuid(getuid());
    table = clone_object(MANSION + "obj/table");
    table->move(TO);

    add_item(({"mantle", "long mantle", "mantlepiece"}),
     "It is rose coloured and carved with roses.\n");
    add_item(({"wall", "walls"}), "There are still pieces of wall paper " +
             "left on the walls. Under a piece of loose wall paper " +
             "in the northern wall, you notice a small metal lever.\n");
    add_item(({"lever", "metal lever"}), "It is made of iron. It looks " +
             "as if it can be raised or lowered.\n");
    add_item("fireplace", "It is a massive fireplace, " +
     "one of a particular beauty.  It is carved from a white marble " +
     "and appears to be very large.  A long mantle of rose coloured " +
     "marble stands in contrast.\n");
    add_item("bell", "It is a small silver bell, it is ornate and has "
     + "a bright cheerful sound.\n");
    add_item("chain", "It is a silver chain that hangs from the ceiling, "
     + " on which hangs a silver bell.\n");
    add_item("floor", "The floor is made of sturdy oak, and appears to be"
     + " undamaged. A thick layer of dust shows that the floor has not been"
     + " cleaned in quite some time.\n");

    add_cmd_item("bell", "ring", "@@bring_food@@");
    add_cmd_item(({"mantle", "long mantle", "mantlepiece"}),
           ({"press", "push"}), ({"@@press_mantle@@", "@@press_mantle@@"}));
    add_cmd_item("fireplace", "enter", "@@enter_fireplace@@");

    add_exit(MANSION + "rooms/kitchen", "east", 0);
    add_exit(MANSION + "wing_n5", "southwest", 0);

    add_prop(OBJ_S_WIZINFO, "To open/close the secret passage use: \n" +
      "call here open_stairs,\n" +
      "call here rem_stairs.\n");

    reset_room();
}

public void
do_add_exits()
{
    seteuid(getuid());
    FIREPLACE->add_exit(STAIRS, "southwest", 0);
    STAIRS->add_exit(FIREPLACE, "northeast", 0);
}

public void
do_remove_exits()
{
    seteuid(getuid());
    FIREPLACE->remove_exit("southwest");
    STAIRS->remove_exit("northeast");
}

public string
press_mantle()
{
   write("You press the mantle.\n");
   say(QCTNAME(TP) + " presses the mantle.\n");
   tell_room(TO, "A low grinding sound emerges from the fireplace.\n");
   if (p_mantle) {
       do_remove_exits();
       p_mantle = 0;
       return "";
   } else {
       do_add_exits();
       p_mantle = 1;
       return "You feel a stream of air coming from the fireplace.\n";
   }
}

public void
d_move(object ob, string how, mixed where)
{
    if (ob) {
        if (interactive(ob) && !present(ob)) return;
        ob->move_living(how, where);
    }
}

public string
enter_fireplace()
{
    if (!p_mantle) return "It's far too small.\n";
    
    set_alarm(1.0, -1.0,
              &d_move(TP, "into the fireplace", FIREPLACE));
    return "You start to enter the fireplace.\n";
}

public void
fetch_food()
{
    if (!servant) return;
    seteuid(getuid());
    clone_object(MANSION + "obj/meal")->move(servant);
    servant->command("west");
    if (!present("servant")) return;
    servant->serve_food();
}

public void
put_stuff()
{
    if (!servant || !present(servant)) return;
    servant->lay_table();
    servant->command("say Dinner will soon be served!");
    servant->command("bow");
    servant->command("east");
    set_alarm(30.0, -1.0, fetch_food);
}

public string
bring_food()
{
    say(QCTNAME(TP) + " rings the little silver bell.\n");
    if (!servant && called > 0) {
        seteuid(getuid());
        servant = clone_object(MANSION + "mon/servant");
        set_alarm(1.0, -1.0, &d_move(servant, "xx", TO));
        called--;
        set_alarm(6.0, -1.0, put_stuff);
    }
    return "You ring the little silver bell.\n";
}

public void
open_stairs()
{
   if (p_mantle) {
       write("The stairs are already open!\n");
   } else {
       do_add_exits();
       p_mantle = 1;
   }
}

public void
rem_stairs()
{
   if (!p_mantle) {
        write("The stairs aren't here at the moment!\n");
   } else {
       do_remove_exits();
       p_mantle = 0;
   }
}

public int
do_raise(string str)
{
    if (str != "lever" && str != "metal lever") return 0;
    
    if (raised) {
        write("The lever cannot be raised more.\n");
        return 1;
    }
    write("You raise the lever. A secret door appears in the northern wall.\n");
    say("A secret door appears in the northern wall.\n");
    add_my_desc("A small staircase stands open in the northern wall.\n");
    add_exit(SSECRET, "north", 0);
    SSECRET->add_exit(HERE, "south", 0);
    raised = 1;
    return 1;
}

public int
do_lower(string str)
{
    if (str != "lever" && str != "metal lever") return 0;
    
    if (!raised) {
        write("The lever cannot be lowered more.\n");
        return 1;
    }
    write("You lower the lever. The door in the northern wall closes.\n");
    say("The door in the northern wall closes.\n");
    remove_my_desc();
    remove_exit("north");
    SSECRET->remove_exit("south");
    raised = 0;
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_raise, "raise");
    add_action(do_lower, "lower");
}
