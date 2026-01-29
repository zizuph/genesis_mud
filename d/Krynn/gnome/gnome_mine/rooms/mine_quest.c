/*
    Wilziver workroom
    Here all the pickaxe quest takes place, all items are inside here, except for a diamond, 
    which you need to get from anywhere you want.

    Made by: 
        Maelstrom, 2016/05

    Updated: 
        Maelstrom, 2017/01 (final version)

*/

inherit "/std/room";
#include <stdproperties.h>

#include <macros.h>
#include <ss_types.h>
#include <terrain.h>

#include <cmdparse.h>

#include "../defs.h"

inherit "/d/Sparkle/area/city/rooms/delay_room";

object quest_giver;

string      *Locations = ({
                "first crate",
                "second crate",
                "third crate",
                "fourth crate",
                "fifth crate",
                "sixth crate",
                "seventh crate" 
            });

string      *Reactions = ({
                "After a few pulls from your trusty crowbar you manage to get the crate open but there's nothing here, just dust. ",
                "A pile of bones adorn this crate, wonder who they were from. ",
                "You find a compass that just spins around; worthless junk, you throw it back in. ",
                "You see a lot of rats eating some unrecognized meat inside this crate. ",
                "It's empty, probably used to store supplies. ",
                "Opening the crate slowly, you find what seems to be a giant cockroach infestation. " +
                "You close it back; unless you are paid to kill them, you are not going near that crate again. ",
                "Drawing on your last breath, the crate pops open, and so does the crowbar, breaking in half. " +
                "But wait, something seems to shine inside. "
            });

string      *junk = ({
                "You find a crazy looking toothbrush. ",
                "You find an old carpet. ",
                "You find some tubes. ",
                "You find a steam powered abacus. ",
                "You find a weird pencil. ",
                "You find a shovel contraption. ",
                "Nothing of interest. "
            });

string      *junk_files = ({
                "crazy_toothbrush_quest",
                "old_carpet_quest",
                "tubes_quest",
                "steam_powered_abacus_quest",
                "weird_pencil_quest",
                "shovel_contraption_quest"
            });

public mixed        Searcher = 0; /* Anyone searching the room for stuff. */

/* Prototypes */
public void         leave_inv(object ob, object dest);
public int          stop_delay_cmd(mixed arg);
public mixed        begin_item_search(string where);
public string       end_item_search(string where);
public mixed        begin_barrels_search();
public string       end_barrels_search();
public mixed        begin_junk_search();
public string       end_junk_search();
public string       end_sword_search();


int
player_solved_quest(object tp)
{
    int questIsDone = 0;
    if (tp->test_bit("Krynn", PICKAXE_GROUP, PICKAXE_BIT))
    {
        questIsDone = 1;
    }
    return questIsDone;
}

int
player_is_doing_quest(object tp)
{
    return tp->query_prop(GNOME_MINE_QUEST);
}

int
player_has_crowbar(object tp)
{
    object *obSearch = FIND_STR_IN_OBJECT("crowbar_quest", tp);
    obSearch += FIND_STR_IN_OBJECT("pickhead_quest", tp);
    return sizeof(obSearch) > 0 || player_solved_quest(tp);
}

int
player_has_shaft(object tp)
{
    object *obSearch = FIND_STR_IN_OBJECT("shaft_quest", tp);
    return sizeof(obSearch) > 0 || player_solved_quest(tp);
}

int
player_has_clockwork(object tp)
{
    object  *cq;
    object  *inv;

    inv = all_inventory(tp);
    cq = filter(inv, &->id("clockwork_quest"));

    return sizeof(cq) > 3 || player_solved_quest(tp);
}

int
player_has_tubes(object tp)
{
    object *obSearch = FIND_STR_IN_OBJECT("tubes_quest", tp);
    return sizeof(obSearch) > 0 || player_solved_quest(tp);
}

int
player_has_lava_tank(object tp)
{
    object *obSearch = FIND_STR_IN_OBJECT("lava_tank_quest", tp);
    return sizeof(obSearch) > 0 || player_solved_quest(tp);
}

int
player_has_lava_engine(object tp)
{
    object *obSearch = FIND_STR_IN_OBJECT("lava_engine_quest", tp);
    return sizeof(obSearch) > 0 || player_solved_quest(tp);
}

void
add_quest_giver()
{
    quest_giver = clone_object(NPC_DIR + "wilziver");
    quest_giver->move(this_object());
    tell_room(this_object(), QCTNAME(quest_giver) + " arrives.\n");
}

void
reset_room()
{
    if (!objectp(quest_giver)) add_quest_giver();
}

void
create_room()
{
    set_short("Mine Entrance");

    set_long("This seems to be the entrance to an old mine. " +
        "Inside it has been completely remade, although the mud and dust remain. " +
        "The walls are adorned with inventions of all kinds, endless wonder one could say; " +
        "The roof is pretty much the same as the walls, but the inventions are hanging all over the place instead. " +
        "The floor seems to be made of black stone, " +
        "with a big pile of junk in the corner, a couple of barrels near a wall, " +
        "and a few crates scattered around.\n" +
        "A gnome sits near a work table filled with diagrams and schematics. " +
        "\n");

    add_item(({"crates"}),
        "There seems to be seven of them.\n");

    add_delay_cmd_item( ({"crates"}),
                    "search",
                    "searching crates",
                    1,
                    "You start looking around the crates.\n",
                    "You don't know where to start, why not search the <first> crate.\n");

    add_item(({"roof"}),
        "You are mesmerized by all the weaponry the gnome has invented.\n");

    add_item(({"weaponry"}),
        "There's a big assortment of killing instruments, all hanging from the roof; a green tube that spins rapidly by itself, " +
        "a saw contraption that springs from a sleave, a small grey dagger that sparks like made by " +
        "lightning, a red sword that glows as fire, a purple shield with spikes that seem to spring out and " +
        "back at intervals, a blue lance that exudes ice, a flask launcher, a green pike which is dripping some acid, " +
        "a white mace made of pure white rock, many small stars that seem to spin on their own and a long bar that transforms " +
        "into other things when you look at it for extended periods.\n");

    add_item(({"green tube"}),
        "It won't stop spinning, you dont think it's safe to touch that.\n");

    add_item(({"saw contraption", "saw"}),
        "It pops unexpectedly from time to time, there doesnt seem to be a control for it.\n");

    add_item(({"grey dagger"}),
        "Jolts of energy pop back and forth from it, you cannot dissern it's power supply though, " +
        "perhaps it's enchanted though.\n");

    add_item(({"red sword"}),
        "It gets very warm as soon as you near it, so you guess it might be boiling hot to the touch.\n");

    add_delay_cmd_item( ({"red sword"}),
                    "search",
                    "searching the red sword",
                    10,
                    "You start looking around the red sword.\n",
                    &end_sword_search());

    add_item(({"purple shield"}),
        "Those spikes look pointy, enough to pierce through some weak armor.\n");

    add_item(({"blue lance"}),
        "You wonder if making ice cubes with it would make a nice party trick.\n");

    add_item(({"flask launcher"}),
        "Labeled 'Repeating flask launcher', a small chamber for vials is under it; there's no disserning way " +
        "of operating it, but sure seems dangerous.\n");

    add_item(({"green pike"}),
        "You can't find the source of the acid, but the hole it's making on the floor speaks for itself.\n");

    add_item(({"white mace"}),
        "Solid.\n");

    add_item(({"stars"}),
        "A throwing weapon of sorts, you can't figure out why they won't stop spinning though.\n");

    add_item(({"long bar"}),
        "It seems to transform into a tank of sorts, but maybe it's just your imagination.\n");

    add_item(({"thin rope"}),
        "Perhaps if you <throw> something to it.\n");

    add_item(({"floor"}),
        "Cracks are all over the place.\n");

    add_item(({"cracks"}),
        "Dirt and bugs.\n");

    add_item(({"walls", "wall", "inventions"}),
        "You see many inventions, a weird looking pot, a small figurine, a very long broom, " +
        "a dark thin tube, a big round sphere, an onyx table, a big clockwork statue, " +
        "a couple of drums, a small brush, a big rectangular contraption and a helmet filled with contraptions.\n");

    add_item(({"pot"}),
        "There's a button on it, labeled 'boil', and next to it, another label 'don't touch, dangerous'.\n");

    add_item(({"figurine"}),
        "Would almost resemble the gnome sitting next to the work table, if it wasn't for the clothes.\n");

    add_item(({"clothes"}),
        "There seems to be something underneath.\n");

    add_item(({"hatch"}),
        "You could probably open it.\n");

    add_item(({"broom"}),
        "An orc could use this perfectly.\n");

    add_item(({"thin tube", "dark thin tube"}),
        "It reacts to the touch, changing colors.\n");

    add_item(({"big round sphere", "sphere"}),
        "It seems to open up, a male human is inside, chained in a maze of tubes and " +
        "the sphere inner walls have stack after stack of unusual weapons hanging on them.\n");
    
    add_item(({"onyx table", "table"}),
        "Your hopes and dreams are suddently materialized before you, over this table, but as soon as you " +
        "focus on the vision, it fades.\n");
    
    add_item(({"clockwork statue", "statue"}),
        "It changes repeatedly, taking the form of all know races.\n");

    add_item(({"drums"}),
        "They seem regular at first glance, but when you touch them, the sound seems amplified " +
        "somehow.\n");

    add_item(({"brush"}),
        "A switch adorns the back, labeled 'AutoClean'.\n");

    add_item(({"contraption", "big rectangular contraption", "rectangular contraption", "tube reinforcer"}),
        "There's a lot of small door compartments, buttons and labels on it; one big label reads 'tube reinforcer'.\n");

    add_item(({"labels"}),
        "They point out how to use this contraption, apparently one would require to have: tubes and a diamond. " +
        "Then simply press the start button, and the machine will show where to put the items.\n");

    add_item(({"buttons"}),
        "There's so many of them, but one of them stands out, labeled 'start button'.\n");

    add_item(({"start button"}),
        "Big, round and red, you are not sure if you should press it.\n");

    add_item(({"helmet"}),
        "There's all sorts of nifty things attached to this helmet; retractable monocle, shapeshifting hat, " +
        "mint dispenser, portable steam-powered abacus, and even an emergency eject button.\n");

    add_item(({"diagrams", "schematics"}),
        "Assorted lot of blueprints, they seem to be in some sort of indecipherable code; " +
        "taking them would be pointless.\n");


    foreach (string place: Locations)
    {
        add_item(({place}),
            "Nothing particular about it. Perhaps you should search it.\n");

        add_delay_cmd_item( ({place}),
                        "search",
                        "searching the "+place,
                        10,
                        &begin_item_search(place),
                        &end_item_search(place));
    }

    add_item(({"barrels", "barrel"}),
        "@@spot_barrels");

    add_delay_cmd_item( ({"barrels", "barrel"}),
                    "search",
                    "searching the barrels",
                    10,
                    &begin_barrels_search(),
                    &end_barrels_search());


    add_item(({"junk", "pile of junk", "junk pile", "pile"}),
        "Nothing particular about it. Perhaps you should search it.\n");

    add_delay_cmd_item( ({"junk", "pile of junk", "junk pile"}),
                    "search",
                    "searching the junk",
                    10,
                    &begin_junk_search(),
                    &end_junk_search());

    
    add_exit("/d/Krynn/gnome/cave1", "east", 0);
    add_prop(ROOM_I_INSIDE, 1);  /* This is inside */

    reset_room();      
}

/*
 * Original by  :        Gorboth
 * Modified by  :        Maelstrom
 * Function name:        begin_item_search
 * Description  :        Provides a different message when a
 *                       player begins searching the various
 *                       locations available, based on
 *                       whether they have already done so.
 * Arguments    :        string where - the location they are searching
 * Returns      :        mixed: integer -- 0 if command fails,
 *                           or string  -- the "You begin ..." message
 */
public mixed
begin_item_search(string where)
{
    if (!Searcher)
    {
        Searcher = this_player();
        say(QCTNAME(Searcher) + " begins searching through the "
            + where + ".\n");

        if (IN_ARRAY(where, Searcher->query_prop(SEARCHED_FOR_PICKHEAD)))
        {
            return "You start searching through the "
                +  where + " again,"
                + " determined to find something useful.\n";
        }

        return "You start searching through the " + where + ".\n";
    }

    write(Searcher->query_The_name(this_player()) + " is already doing"
        + " that, and is in your way."
        + " You'll have to wait until " + Searcher->query_pronoun()
        + " is finished.\n");

    return 1;
} /* begin_item_search */


/*
 * Original by  :        Gorboth
 * Modified by  :        Maelstrom
 * Function name:        end_item_search
 * Description  :        Provides the result of having searched.
 * Arguments    :        string where - the location being searched
 * Returns      :        string - message for the player
 */
public string
end_item_search(string where)
{
    string  searcher_msg;
    string  other_msg = QCTNAME(Searcher);
    object  c_item;
    object  *ob = FIND_STR_IN_OBJECT("crowbar_quest", Searcher);
    string  *searched = Searcher->query_prop(SEARCHED_FOR_PICKHEAD);

    /* The player has already solved the Pickaxe Quest. */
    if (player_solved_quest(Searcher))
    {
        searcher_msg =  "There's nothing new here, a long feeling of de ja voo strikes you. " +
                        "You are quite sure you did this already.";
        other_msg +=    " finishes the search, which looks to have " +
                        "amounted to nothing new.";
    }
    /* Check if the player has the crowbar */
    else if (!sizeof(ob))
    {
        Searcher->add_prop(NEED_CROWBAR, 1);
        searcher_msg = "You try to open the " + where + " with your hands "
            + "but it wont budge. If only there was a handy tool "
            + "nearby specifically made for this task.";
        other_msg += " tries to open the " + where + " with "
            + Searcher->query_possessive() + " hands but it wont budge.";
    }
    else if (ob[0]->query_wielded() == 0)
    {
        searcher_msg = "You must wield the crowbar first.";
        other_msg += " looks puzzled at how a crowbar works.";
    }
    /* The player has already searched here, but tries again anyway */
    else if (IN_ARRAY(where, searched))
    {
        searcher_msg = "That crate was already opened before "
            + "and there's nothing worth taking in it. ";
        other_msg += " finishes searching the " + where
            + " again, apparently not"
            + " finding anything of value this time either.";
    }
    /* The player hasn't searched here yet, but hasn't yet searched
    * all three possible locations.
    */
    else if (sizeof(searched) < (sizeof(Locations) - 1))
    {
        if (searched)
        {
            searched += ({ where });
        }
        else
        {
            searched = ({ where });
        }

        Searcher->add_prop(SEARCHED_FOR_PICKHEAD, searched);

        searcher_msg = Reactions[sizeof(searched)-1];
        //+ search_hint(this_player(), where, searched);
        other_msg += " finishes searching the " + where
            + ", apparently not"
            + " finding anything of value.";

    }
    /* Ah ... the player finally searches the last location for the
    * first time. Here, we give them the quest object.
    */
    else
    {

        c_item = clone_object(WEP_DIR + "pickhead_quest");

        if (c_item->move(Searcher))
        {
            searcher_msg = "You are too heavily loaded to "
                + "get the crate content.";
            other_msg += " is tring to get something from a crate, "
                + "but seems to be too heavy for " + Searcher->query_objective() + ".";
            c_item->remove_object();
        }
        else
        {
            //remove crowbar (it breaks)
            ob[0]->remove_object();

            if (searched)
            {
                searched += ({ where });
            }
            else
            {
                searched = ({ where });
            }
            Searcher->add_prop(SEARCHED_FOR_PICKHEAD, searched);



            searcher_msg = Reactions[sizeof(searched)-1]
                + "After digging for a short while through the "
                + where + ", you notice a "
                + c_item->short() + " amidst the clutter. You quickly"
                + " grab it!";
            other_msg += " pulls a " + c_item->short() + " from the"
                + " confines of the " + where + "!";
            /*
            #if LOG_ACTIVITY
            write_file(LOG_DIR + "dagger", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
                + " (" + ctime(time())[11..18] + ") "
                + capitalize(Searcher->query_name())
                + " finds a nullstone dagger.\n");
            #endif

            */
        }
    }

    tell_room(this_object(), other_msg + "\n", Searcher);
    Searcher = 0;
    return searcher_msg + "\n";
} /* end_item_search */

public mixed
begin_barrels_search()
{
    if (!Searcher)
    {
        Searcher = this_player();
        say(QCTNAME(Searcher) + " begins searching through the barrels.\n");

        return "You start searching through the barrels.\n";
    }

    write(Searcher->query_The_name(this_player()) + " is already doing"
        + " that, and is in your way."
        + " You'll have to wait until " + Searcher->query_pronoun()
        + " is finished.\n");

    return 1;
}

public string
end_barrels_search()
{

    string  searcher_msg;
    string  other_msg = QCTNAME(Searcher);

    if (player_has_shaft(Searcher))
    {
        searcher_msg = "Just a few barrels, nothing of interest.";
        other_msg += " looks attentively at the barrels.";
    }
    else
    {
        searcher_msg = "You catch a glimpse of something behind the barrels. "
                + "Perhaps you should <move> them to get a better look.";
        other_msg += " looks attentively at something near the barrels.";
    }



    tell_room(this_object(), other_msg + "\n", Searcher);
    Searcher = 0;
    return searcher_msg + "\n";            
}

public mixed
begin_junk_search()
{
    if (!Searcher)
    {
        Searcher = this_player();
        say(QCTNAME(Searcher) + " begins searching through the junk.\n");

        return "You start searching through the junk.\n";
    }

    write(Searcher->query_The_name(this_player()) + " is already doing"
        + " that, and is in your way."
        + " You'll have to wait until " + Searcher->query_pronoun()
        + " is finished.\n");

    return 1;
}

public string
end_junk_search()
{

    string  searcher_msg;
    string  other_msg = QCTNAME(Searcher);
    object  c_item;

    int  junkTimes = Searcher->query_prop(JUNK_SEARCHED_TIMES);

    if (!junkTimes)
    {
        junkTimes = 0;
    }

    if (!player_is_doing_quest(Searcher))
    {
        /* The player is not doing this quest, so we don't actually
        * give them anything other than a hint that they should start
        * the quest first.
        */
        searcher_msg = "You don't seem to find anything interesting. "
            + "Perhaps if you were on a quest, searching for something.";
        other_msg += " is looking at the junk pile but doesn't find anything interesting.";
    }
    else if (player_has_clockwork(Searcher) && player_has_tubes(Searcher))
    {
        searcher_msg = "You don't seem to find anything interesting. "
            + "This sounds familiar, like something you already did.";
        other_msg += " is looking at the junk pile but doesn't find anything interesting.";
    }
    else if (junkTimes < 6)
    {
        c_item = clone_object(OBJ_DIR + junk_files[junkTimes]);

        if (c_item->move(Searcher))
        {
            searcher_msg = "You are too heavily loaded to "
                + "get that.";
            other_msg += " is tring to get something from the junk pile, "
                + "but seems to be too heavy for " + Searcher->query_objective() + ".";
            c_item->remove_object();
        }
        else
        {
            Searcher->add_prop(JUNK_SEARCHED_TIMES, junkTimes + 1);

            searcher_msg = junk[junkTimes];
            other_msg += " grabs some junk from the junk pile.";
        }
    }
    else
    {
        searcher_msg = junk[junkTimes];
        other_msg += " looks around the junk pile but finds nothing of interest.";
    }

    tell_room(this_object(), other_msg + "\n", Searcher);
    Searcher = 0;
    return searcher_msg + "\n";            
}

public string
end_sword_search()
{
    if (player_has_lava_tank(this_player()))
    {
        return "There's nothing else of interest here.\n";
    }
    else
    {
        return "There's a small glowing red tank attached to it.\n";
    }
}

/*
 * Original by  :       Gorboth
 * Function name:       leave_inv
 * Description  :       catch any searchers leaving. They can't
 *                      do it on their own, but they might be trans'd
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    if (Searcher == ob)
    {
        Searcher = 0;
    }

    ::leave_inv(ob, dest);
} /* leave_inv */

/*
 * Original by  :       Gorboth
 * Function name:       stop_delay_cmd
 * Description  :       mask parent so that if player does "stop",
 *                      we clear Searcher
 * Arguments    :       mixed arg -- if string, player did "stop"
 *                                -- if object, time ran out or
 *                                    called from leave_inv().
 * Returns      :       0 -- stop is always allowed
 */
public int
stop_delay_cmd(mixed arg)
{
    object      tp;

    if (!objectp(arg))
    {
        /* called from paralyze object when player did "stop" */
        tp = environment(previous_object());
        if (tp == Searcher)
        {
            Searcher = 0;
        }
    }
    return ::stop_delay_cmd(arg);
} /* stop_delay_cmd */

string
spot_barrels()
{
    string response;
    object tp = this_player();
    if (player_has_crowbar(tp))
    {
        if (tp->query_skill(SS_AWARENESS) > 80)
        {
            if (player_has_shaft(tp))
            {
                response = "Just a few barrels, nothing of interest.\n";
            }
            else
            {
                response = "You catch a glimpse of something behind the barrels. "
                        + "Perhaps you should move them to get a better look.\n";
            }
        }
        else
        {
            response = "At first glance, it's just a few barrels.\n";
        }
    }
    else
    {
        response = "You spot a crowbar on top of one of the barrels.\n";
    }

    return response;
}

int
ground_item(string str, string item, int playerHasItem, string itemPath, string place)
{
    object f;
    object tp = this_player();

    if (str == item)
    {
        if (!playerHasItem)
        {
            f = clone_object(itemPath);
            if (f->move(tp) != 0)
            {
                tp->catch_msg("You are too heavily loaded to " +
                              "get the " + item + ".\n"); 
                f->remove_object();
                return 1;
            }
            else
            {
                tp->catch_msg("You take the " + item + " from the " + place + ".\n");
                tell_room(environment(tp), QCTNAME(tp) + " takes " +
                    "a " + item + " from the " + place + ".\n", tp);

                return 1;
            }
        }
    }

    return 0;
}

int
do_exa(string str)
{

    int found = 0;
    string * data;
    string item;
    string place;
    object tp = this_player();

    if (!str)
    {
        notify_fail("Exa what?\n");
        return 0;
    }

    data = explode(str, " from ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        data = explode(str, " on ");
        if (sizeof(data) > 1)
        {
            item = data[0];
            place = data[1];
        }
        else
        {
            item = data[0];
            place = "";
        }
    }

    if (item == "crowbar")
    {
        if (player_has_crowbar(tp))
        {
            tp->catch_msg("There's no crowbar anymore, you took it.\n");
        }
        else
        {
            tp->catch_msg("Looks like a handy tool for opening crates, perhaps you should <take> it.\n");
        }
        found += 1;
    }

    if (found > 0)
    {
        return 1;
    }

    notify_fail("Exa what?\n");
    return 0;    
}

int
do_get(string str)
{
    int found = 0;
    string * data;
    string item;
    string place;
    object tp = this_player();
    object c_item;

    string  *wall_inventions = ({
                "pot",
                "figurine",
                "broom",
                "thin tube",
                "big round sphere",
                "onyx table",
                "clockwork statue",
                "drums",
                "brush",
                "big rectangular contraption",
                "helmet"
            });

    string  *roof_inventions = ({
                "green tube",
                "saw contraption",
                "grey dagger",
                "purple shield",
                "blue lance",
                "flask launcher",
                "green pike",
                "white mace",
                "stars",
                "long bar"
            });

    if (!str)
    {
        notify_fail("Take what from where?\n");
        return 0;
    }

    data = explode(str, " from ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        data = explode(str, " on ");
        if (sizeof(data) > 1)
        {
            item = data[0];
            place = data[1];
        }
        else
        {
            item = data[0];
            place = "";
        }
    }

    if (item == "crowbar") {
        //if you dont have the quest and if you havent tried to open the crates yet, you cant grab it (why would i want that?)
        if (tp->query_prop(NEED_CROWBAR) && player_is_doing_quest(tp))
        {
            if (player_has_crowbar(tp))
            {
                tp->catch_msg("There's no crowbar anymore, you took it.\n");
                found += 1;
            }
            else
            {
                found = found + ground_item(item, "crowbar", player_has_crowbar(tp), WEP_DIR+"crowbar_quest", "barrel");
            }
        }
        else if (player_is_doing_quest(tp))
        {
            /* The player is not doing this quest,(or he didnt try to search the crates yet)
            * so we don't actually give them anything other than a hint that they should start
            * the quest first, or find a use for the item before grabing it.
            */
            notify_fail("Why would I want that? I dont want to end up "
                    + "like that guy from that place that had to collect items for pirate lords. "
                    + "I choose to take things according to my needs. "
                    + "Like for example, if I had something that needs opening.\n");
            return 0;
        }        
        else
        {
            /* The player is not doing this quest,(or he didnt try to search the crates yet)
            * so we don't actually give them anything other than a hint that they should start
            * the quest first, or find a use for the item before grabing it.
            */
            notify_fail("Why would I want that? I dont want to end up "
                    + "like that guy from that place that had to collect items for pirate lords. "
                    + "I choose to take things according to my needs. "
                    + "Perhaps if I was on a quest, searching for something.\n");
            return 0;
        }
    }
    else if (IN_ARRAY(item, wall_inventions))
    {
        notify_fail("It's firmly attached, no way to take it.\n");
        return 0;
    }
    else if (IN_ARRAY(item, roof_inventions))
    {
        notify_fail("You can't reach it, it's too high up.\n");
        return 0;
    }
    else if (item == "red sword" || item == "red tank")
    {
        notify_fail("You can't reach it, it's too high up, but it's only attached to the roof by a thin rope.\n");
        return 0;
    }    
    else if (item == "clothes")
    {
        tp->catch_msg("You raise the " + item + " from the figurine, noticing a small hatch on the back of it.\n");
        tell_room(environment(tp), QCTNAME(tp) + " is messing around with an invention back there.\n", tp);
        found += 1;
    }
    else if ((item == "box" || item == "dusty box"))
    {
        if (!player_is_doing_quest(tp))
        {
            tp->catch_msg("Why would you want that? Perhaps if you were on a quest, searching for something.\n");
            found += 1;
        }
        else
        {
            if (tp->query_prop(FIGURINE_HATCH_QUEST))
            {
                if (player_has_lava_engine(tp))
                {
                    tp->catch_msg("You already took the box.\n");
                    found += 1;
                }
                else
                {
                    tp->catch_msg("You get the " + item + " from the figurine.\n");
                    tell_room(environment(tp), QCTNAME(tp) + " is messing around with an invention back there.\n", tp);
                    found += 1;
                        
                    c_item = clone_object(OBJ_DIR + "lava_engine_quest");
                    c_item->move(tp);        
                }
            }
        }
    }

    if (found > 0)
    {
        return 1;
    }

    notify_fail("Take what from where?\n");
    return 0;
}

int
do_open(string str)
{

    int found = 0;
    string * data;
    string item;
    string place;
    object tp = this_player();

    if (!str)
    {
        notify_fail("Open what from where?\n");
        return 0;
    }

    data = explode(str, " from ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        data = explode(str, " on ");
        if (sizeof(data) > 1)
        {
            item = data[0];
            place = data[1];
        }
        else
        {
            item = data[0];
            place = "";
        }
    }

    if (item == "hatch")
    {
        if (player_has_lava_engine(tp))
        {
            tp->catch_msg("You open the " + item + " from the figurine, there's nothing inside.\n");
            found += 1;
        }
        else
        {
            tp->catch_msg("You open the " + item + " from the figurine, there's just a dusty little box inside.\n");
            tell_room(environment(tp), QCTNAME(tp) + " is messing around with an invention back there.\n", tp);
            found += 1;
        }
        tp->add_prop(FIGURINE_HATCH_QUEST, 1);
    }

    if (found > 0)
    {
        return 1;
    }

    notify_fail("Open what from where?\n");
    return 0;    
}

int
do_move(string str)
{
    int found = 0;
    object tp = this_player();

    if (!str)
    {
        notify_fail("Move what?\n");
        return 0;
    }

    if (str == "barrel" || str == "barrels") {
        //if you dont have the quest, you cant move it (why would i want to do that?)
        if (player_is_doing_quest(tp))
        {
            found = found + ground_item("shaft", "shaft", player_has_shaft(tp), WEP_DIR+"shaft_quest", "floor behind the barrels");
        }
        else
        {
            /* The player is not doing this quest, so we don't actually
            * give them anything other than a hint that they should start
            * the quest first.
            */
            notify_fail("Why would I want to do that? The room is very zen right now. "
                    + "I choose to do things according to my needs. "
                    + "Perhaps if I was on a quest, searching for something.\n");
            return 0;
        }        
    }

    if (found > 0)
    {
        return 1;
    }

    notify_fail("Move what?\n");
    return 0;
}

int
do_throw(string str)
{
    int thrown = 0;
    string *data;
    string item;
    string place;
    object tp = this_player();
    object *ob;
    object c_item;

    string  *roof_inventions = ({
                "green tube",
                "saw contraption",
                "grey dagger",
                "red sword",
                "purple shield",
                "blue lance",
                "flask launcher",
                "green pike",
                "white mace",
                "stars",
                "long bar"
            });

    if (!str)
    {
        notify_fail("Throw what to where?\n");
        return 0;
    }

    data = explode(str, " to ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        item = data[0];
        place = "";
    }


    ob = FIND_STR_IN_OBJECT(item, tp);
    if (sizeof(ob) > 0)
    {
        ob[0]->move(this_object());
        thrown = 1;
    }

    if (thrown == 0)
    {
        notify_fail("Throw what to where?\n");
        return 0;
    }

    if (!player_is_doing_quest(tp))
    {
        tp->catch_msg("Why would you want that? Perhaps if you were on a quest, searching for something. " +
                        "Now your " + item + " lies on the floor.\n");
    }
    else
    {
        if (place == "red tank" || place == "lava tank" || place == "thin rope" || place == "rope")
        {
            tp->catch_msg("You throw your " + item + " at the " + place + ", trying to bring it down.\n");
            tell_room(environment(tp), QCTNAME(tp) + " throws " + tp->query_possessive() + " " + item +
                " at the hanging weapons.\n", tp);
            //depending on your throw skill:
            //you succeed
            if (tp->query_skill(SS_WEP_MISSILE) > random(50))
            {
                if (player_has_lava_tank(tp))
                {
                    tp->catch_msg("There's nothing to be gained anymore, you already have the lava tank.\n");                
                }
                else
                {
                    tp->catch_msg("You succeed, the lava tank detached from the sword and falls to the ground. " +
                        "You quickly grab it.\n");
                    c_item = clone_object(OBJ_DIR + "lava_tank_quest");
                    c_item->move(tp);
                }
            }
            //or you fail
            else
            {
                tp->catch_msg("You fail, but you do manage to hit something, since lava mist rains over you.\n");
                //slightly damaged
                tp->reduce_hit_point(10);
            }
        }
        else if (IN_ARRAY(place, roof_inventions))
        {
            tp->catch_msg("You throw your " + item + " at the " + place + ", hitting it. " +
                "But perhaps it wasn't such a good idea.\n");
            tell_room(environment(tp), QCTNAME(tp) + " throws " + tp->query_possessive() + " " + item +
                " at the " + place + ", hitting it. But perhaps it wasn't such a good idea.\n", tp);

            //slightly damaged
            tp->reduce_hit_point(20);

            string *random_damg_type =
                ({ 
                    "slicer",
                    "thunder",
                    "fire",
                    "pointy stuff",
                    "ice",
                    "acid",
                    "large stone"
                });
            
            tp->catch_msg("You are damaged by " + one_of_list(random_damg_type) + ".\n");
            tell_room(environment(tp), QCTNAME(tp) + " is damaged by " + one_of_list(random_damg_type) + ".\n", tp);
        }
        else
        {
            tp->catch_msg("You throw your " + item + " without particular aim, not hitting anything.\n");
            tell_room(environment(tp), QCTNAME(tp) + " throws " + tp->query_possessive() + " " + item +
                " without particular aim, not hitting anything.\n", tp);        
        }
    }

    return 1;
}

int
do_press(string str)
{
    int pressed = 0;
    object tp = this_player();
    object *ob;
    object *ob2;
    object c_item;


    if (!str)
    {
        notify_fail("Press what?\n");
        return 0;
    }


    if (str == "start button" || str == "big red button")
    {
        ob = FIND_STR_IN_OBJECT("tubes_quest", tp);
        ob2 = FIND_STR_IN_OBJECT("diamond", tp);
        if (sizeof(ob) > 0 && sizeof(ob2) > 0)
        {
            ob[0]->remove_object();
            ob2[0]->remove_object();
            pressed = 1;

            tp->catch_msg("The tube reinforcer starts up with a low hum, and suddenly a compartment pops " +
                "open, labeled 'insert tubes here'.\n" +
                "You quickly throw the tubes you found earlier into it and take a step back.\n" +
                "After a few minutes of weird humming and zizzing sounds, a second compartment pops open, " +
                "labeled 'diamond goes here'; after searching your pockets for a second, you finally find it " +
                "and throw it in.\n" +
                "Some more minutes later, all sounds come to a sudden stop and a loud 'CLING' is heard. " +
                "Followed by a third compartment ejecting some tubes.\n" +
                "You dont waste time and grab the tubes.\n");
            tell_room(environment(tp), QCTNAME(tp) + " starts up some machine, throws a few things into " + 
                "it, and gets rewarded with what looks like shiny tubes. You wonder if that's legal.\n", tp);

            c_item = clone_object(OBJ_DIR + "reinforced_tubes_quest");
            c_item->move(tp);

            return 1;
        }
        else
        {
            tp->catch_msg("The machine starts up, but when required for tubes and a diamond, " +
                "you draw a blank; it seems you are missing components.\n");
            tell_room(environment(tp), QCTNAME(tp) + " starts up a machine, " +
                "but then just stares at it till it shuts itself off.\n", tp);

            return 1;
        }
    }
    else if (str == "boil" || str == "boil button")
    {
        tp->catch_msg("You press the boil button and get your finger instantly burned. " +
            "You figure it's probably best not to do that again.\n");
        //slightly damaged
        tp->reduce_hit_point(10);
        return 1;
    }

    notify_fail("Press what?\n");
    return 0;    
}

void
init()
{
    ::init();
    add_action(do_exa, "exa");
    add_action(do_get, "take");
    add_action(do_get, "get");
    add_action(do_get, "grab");
    add_action(do_get, "remove");
    add_action(do_open, "open");
    add_action(do_move, "move");
    add_action(do_move, "push");
    add_action(do_move, "pull");
    add_action(do_throw, "throw");
    add_action(do_press, "press");
}