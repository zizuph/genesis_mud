/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_c3.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : Kalerus Central Plaza
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>

object ob;

/* Prototypes */
string long_desc();
object make_board();
string pool_desc();
public string cross_bridge();

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    ::create_room();

    set_short("You are in the Kalerus Central Plaza");

    set_long("@@long_desc");

    /* 
     * Begin - Things that are visible from any "outdoor" location 
     * in the cavern.
     */

    add_item(({"cavern", "walls", "cavern walls"}),
    "The cavern is quite enormous. Whether it was created by natural " +
    "forces or otherwise, it must have taken quite some time.\n");

    add_item(({"north face", "north wall", "waterfall", 
    "enormous waterfall", "massive waterfall", "giant waterfall",
    "falls", "ghiza falls"}),
    "The giant waterfall enters the cavern near the top of the north " +
    "wall and disappears behind the city's largest structure.\n");

    add_item(({"cells", "sleeping cells", "faces", "east face",
    "east wall", "west face", "west wall"}),
    "All but the north face of the cavern interior are dotted with " +
    "the hundreds of goblin sleeping cells.\n");

    add_item(({"south face", "south wall"}),
    "The south wall of the cavern is dotted with many goblin " +
    "sleeping cells. In the distance, you can see the river " +
    "disappear into a large tunnel at the base of the wall. " +
    "Nearby, there is also a smaller tunnel leading south.\n");

    add_item(({"floor", "stone floor", "cavern floor"}),
    "The stone floor is extremely smooth. It is covered with a thin " +
    "layer of water.\n");

    add_item(({"tunnel", "large tunnel", "river tunnel",
    "ghiza river tunnel"}),
    "The river disappears into the tunnel as abruptly as it appears " +
    "from beneath the museum.\n");

    add_item(({"city", "small city", "kalerus"}),
    "There is a wonderful stillness to the city, a vast amount of " +
    "open space overhead gives the illusion of continuous night " +
    "time.\n");

    add_item(({"stone", "limestone", "architecture", "enclosures"}),
    "The interior of the cavern and all of the enclosures within it " +
    "are constructed of a highly polished, slightly damp limestone.\n");

    add_item(({"structure", "large structure", "largest structure",
    "temple", "temple of xi voch"}),
    "The city's most prominent structure lies at the base of the " +
    "waterfall. It is topped with several ornate spires, though you " +
    "can't make out much detail from this distance.\n");

    add_item(({"spires", "ornate spires"}),
    "You can't make out much detail from this distance.\n");

    add_item(({"glow", "green glow"}),
    "The walls are covered with tiny, worm-like creatures. Their " +
    "bodies give off a faint, green glow, illuminating the cavern " +
    "mist.\n");

    add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
    "The tiny, glowing worms slither blindly about on the rock " +
    "walls.\n");

    add_item(({"mist", "heavy mist"}),
    "A thick mist fills the air, presumably given off by the falls " +
    "and trapped here in the cavern.\n");

    /*
     * End - Things that are visible from any "outdoor" location 
     * in the cavern.
     */

    add_item(({"plaza", "central plaza"}),
    "The Plaza is located at the heart of the cavern floor. It is " +
    "surrounded on all sides by the astonishing stone sculpture that " +
    "is the city of Kalerus.\n");

    add_item(({"pillar", "limestone pillar", "large limestone pillar"}),
    "Reaching high into the air, the pillar is nearly a perfect " +
    "cylinder. You cannot see a seam where it attaches to the " +
    "cavern floor.\n");

    add_item(({"fire", "ceremonial fire", "proud ceremonial fire"}),
    "High above your head, the large fire burns with the pride of " +
    "many generations of Kalerian goblins.\n");

    add_item("board",
    "Which board?\n");

    add_item(({"common", "common board"}),
    "The Common Board has an ethereal glow about it. You feel you " +
    "can access it by moving in the direction \"common\".\n");

    add_item(({"path", "paths"}),
    "The paths extend off in many directions.\n");

    add_item(({"channel", "channels", "water channel", 
    "water channels"}),
    "The channels pass beneath the Training Hall and the Shop, " +
    "continuing south where they rejoin beneath the Museum.\n");

    add_item(({"water", "channel water"}),
    "The water running through the channels is crystal clear.\n");

    add_item(({"bridge", "footbridge", "small bridge", 
    "small footbridge"}),
    "The small, limestone bridge crosses the water channel to the " +
    "southeast.\n");

    add_cmd_item(({"bridge", "footbridge", "small bridge", 
    "small footbridge"}),
    "cross", "@@cross_bridge");

    add_item(({"pool", "bathing pool"}), pool_desc);

    add_exit("common", "common");
    add_exit("cavern_d2", "northwest");
    add_exit("cavern_d3", "north");
    add_exit("cavern_d4", "northeast");
    add_exit("shop", "east");
    add_exit("cavern_b5", "southeast");
    add_exit("museum", "south");
    add_exit("cavern_c2", "west");
}

object
make_board()
{
  object board;

    board = clone_object("/std/board");
    if (board) {
        board->set_board_name("/d/Genesis/new/start/goblin/board_save");
        board->set_num_notes(25);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_lvl(30);
        board->set_remove_str("Sorry, mortals are not allowed to " +
        "remove notes.");
        board->set_err_log("/d/Genesis/new/start/goblin/log/board_err");
        board->set_no_show_composite(1);

        board->move(this_object());
        return board;
    }
    return 0;
}

string
long_desc()
{
    string desc_str = "";
    desc_str += "You are in the Kalerus Central Plaza.\n" +
    "A large, limestone pillar rises from the ground here. At its " +
    "top burns a proud ceremonial fire. On one side of the pillar is " +
    "a bulletin board marked \"Common Board\". ";

    if(!(ob = make_board()))
    {
        desc_str += "Board could not be created.\n";
    }
    else
    {
        desc_str += "On the other side of the pillar is a bulletin " +
        "board marked \"Goblin Board\". ";
    }

    desc_str += "Paths lead off of the Plaza in all " +
    "directions. To the north are the Bathing Pool and the Temple, " +
    "to the east is the Shop. The Kalerus Museum is south of here " +
    "and the Training Hall is to the west. Emerging from beneath " +
    "the Temple are water channels cut into the cavern floor. " +
    "Your path to the southeast is intersected by a channel carrying " +
    "water from the Shop to the Museum. A small footbridge crosses the " +
    "channel.\n";

    return desc_str;
}

string
pool_desc()
{
    int pool_occupancy = "/d/Genesis/new/start/goblin/town/cavern_d3"->query_current_occupancy();

    string desc_str = "";

    if (pool_occupancy == 0)
    {
        desc_str += "The crystal blue Bathing Pool waters are still " +
        "and quiet.\n";
    }
    else
    {
        if (pool_occupancy == 1)
        {
            desc_str += "You can see someone soaking in the Bathing Pool.\n";
        }
        else
        {
            desc_str += "You can see some individuals soaking in the Bathing Pool.\n";
        }
    }

    return desc_str;
}

public string
cross_bridge()
{

   say(QCNAME(this_player()) + 
   " leaves crossing over the footbridge.\n", this_player());

   tell_room("/d/Genesis/new/start/goblin/town/cavern_b5",
   QCNAME(this_player()) + " arrives crossing over the footbridge.\n",
   this_player());

   this_player()->move_living("M", "/d/Genesis/new/start/goblin/town/cavern_b5", 0, 0);

   return "";
}
