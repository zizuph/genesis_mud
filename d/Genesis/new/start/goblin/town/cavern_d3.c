/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_d3.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : Goblin Bathing Pool
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>

int max_occupancy = 6;
int current_occupancy = 0;

#define LIVE_I_BATHES        "_live_i_bathes"

/* Prototypes */
string pool_desc();
int bathe();
int unbathe();
int query_current_occupancy();
int gs_catch_all(string arg);
int gs_hook_catch_error(string str);

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are at the goblin Bathing Pool");

    set_long("You are at the goblin Bathing Pool.\n" +
    "Nestled at the foot of the majestic Temple, the Pool is the " +
    "source of spiritual as well as physical rejuvenation for the " +
    "faithful of Kalerus. East and west of here, small gangways " +
    "lead into the Temple. The Central Plaza is south of here, " +
    "leading off to other parts of town.\n");

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
    "Lying at the base of the waterfall, the Temple is the city's " +
    "most prominent structure. Like most of the other Kalerian " +
    "architecture, the Temple seems to be more of a sculpture " +
    "than a building. Indeed, all of these enclosures appear to " +
    "have been carved directly from the surrounding limestone. " +
    "The magnificent Temple is topped with several ornate spires.\n");

    add_item(({"spires", "ornate spires", "carving", "carvings",
    "goblin carvings"}),
    "The Temple's many spires are adorned with carvings of goblins " +
    "reaching up to the massive waterfall which pours down behind " +
    "the structure.\n");

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

    add_item(({"pool", "bathing pool"}), pool_desc);

    add_cmd_item(({"pool", "bathing pool"}), ({"enter", "use", "bathe in"}), bathe);

    add_item(({"gangway", "gangways", "stone gangway", "stone gangways"}),
    "Access to the Temple is afforded by two small stone gangways " +
    "located east and west of here.\n");

    add_item(({"plaza", "central plaza"}),
    "The Plaza is located at the heart of the cavern floor. It is " +
    "surrounded on all sides by the astonishing stone sculpture that " +
    "is the city of Kalerus.\n");

    add_exit("cavern_d4", "east");
    add_exit("cavern_c3", "south");
    add_exit("cavern_c2", "southwest");
    add_exit("cavern_d2", "west");
}

string
pool_desc()
{
    string desc_str = "";

    if (current_occupancy == 0)
    {
        desc_str += "The crystal blue Bathing Pool waters are still " +
        "and quiet.";
    }
    else
    {
        if (current_occupancy == 1)
        {
            desc_str += "Someone is soaking in the Bathing Pool.";
        }
        else
        {
            desc_str += "Some individuals are soaking in the Bathing Pool.";
        }
    }

    desc_str += " The Pool is continuously supplied with " +
    "fresh water from the falls which is channeled beneath the " +
    "Temple. So intense is the cleansing sensation, both internal " +
    "and external, that visitors from many distant lands have been " +
    "known to make pilgrimages here to the Kalerus Bathing Pool.\n";

    return desc_str;
}

int
bathe()
{
    if (!this_player()->query_prop(LIVE_I_BATHES))
    {
        if (current_occupancy < max_occupancy) {
            this_player()->add_prop(LIVE_I_BATHES, 1);
            this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is in the pool");
            current_occupancy++;
            write("You enter the pool. The crystal blue water is surprisingly " +
            "warm. It seems to soothe your tired body and spirit.\n");
            say(QCTNAME(this_player()) + " enters the pool.\n");
            add_action(gs_catch_all, "", 1);
            return 1;
        }
        else
        {
            write("The pool is full.\n");
            say(QCTNAME(this_player()) + " tries to enter the pool but fails.\n");
            return 1;
        }
    }
    else
    {
        write("You are already in the pool.\n");
        return 1;
    }
}

int
unbathe()
{
    if (this_player()->query_prop(LIVE_I_BATHES))
    {
        this_player()->remove_prop(LIVE_I_BATHES);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT);
        current_occupancy--;
        write("You leave the pool feeling clean and refreshed.\n");
        say(QCTNAME(this_player()) + " leaves the pool .\n");
        return 1;
    }
    else
    {
        write("You are not in the pool!\n");
        return 1;   
    }
}

int
query_current_occupancy()
{
    return current_occupancy;
}

/*
 * Function name: leave_inv
 * Description  : Should be called if someone leaves the room while bathing
 *                (ex. they might be teleported out)
 * Arguments    : object ob - the object that is leaving.
 *                object to - the new destination of the object.
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv();

    if (ob->query_prop(LIVE_I_BATHES))
    {
        ob->remove_prop(LIVE_I_BATHES);
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        current_occupancy--;
    }
}

/*
 * Function name: gs_catch_all
 * Description  : Catch all commands the player makes while meditating.
 * Returns      : int 1/0 - success/failure.
 */
int
gs_catch_all(string arg)
{
    if (!this_player()->query_prop(LIVE_I_BATHES))
    {
        return 0;
    }

    switch(query_verb())
    {
    case "bathe":
        return bathe();

    case "leave":
    case "exit":
        if (arg == "pool")
        {
            return unbathe();
        }

    case "get":
        if (arg == "out of pool")
        {
            return unbathe();
        }

    case "quit":
        current_occupancy--;
        return 0;

    case "help":
    case "stats":
    case "save":
    case "drop": /* For those that quit from meditation */
    case "commune":
    case "reply":
    case "bug":
    case "typo":
    case "idea":
    case "praise":
    case "sysbug":
    case "systypo":
    case "syspraise":
    case "sysidea":
        return 0;

    default:
        return gs_hook_catch_error(arg);
    }
}

/*
 * Function name: gs_hook_catch_error
 * Description  : This hook is called when a player tried to do something strange
 *                while bathing like examining things or leave the room. You
 *                can mask this function to give a different message.
 * Arguments    : string str - Argument the player tried to send to his command.
 * Returns      : int 1 - normally.
 */
int
gs_hook_catch_error(string str)
{
    write("You cannot do that while bathing.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(bathe, "bathe");
}
