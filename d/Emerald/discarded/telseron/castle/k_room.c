/*
 * King's bedroom in the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
 
#define IS_LIEING       "_player_i_is_lying"
#define LIE_SUBLOC      "subloc_lying"
 
#include <options.h>
 
int do_lie(string arg);
int do_rise(string arg);
int enter_passage(string str);
int reset_passage;      // flag to open and close passageway
 
void reset_room();
void
create_room()
{
    reset_room();
    add_prop(ROOM_I_INSIDE, 1);
    set_short("King's bedroom");
    set_long( "   You are in the royal chambers of the King. The room " +
        "is richly decorated. Unlike the rest of the castle, this " +
        "room isn't decorated in the usual manner. The walls are " +
        "decorated with shifting scenes of his homeland. A large " +
        "carpet covers the room. It is decorated with the King's " +
        "insignia and roses, symbolizing the uniting of two great " +
        "elven nations. The ceiling is vaulted and from it hangs " +
        "the largest chandelier you have ever seen. It glows like " +
        "a star that was plucked from the sky. You see various " +
        "furniture here. Servants stand in the shadows, waiting " +
        "to serve the King. ");
 
    add_item("under bed",  "You can't seem to find a way to "+
             "look there, as the bed extends all "+
             "the way to the floor.\n");
    add_item(({"pillow", "pillows"}),
        "The pillows are stuffed with feathers and sit on the bed.\n");
    add_item(({"comforter", "feather comforter"}),
        "The feather comforters are thick and filled with feathers.\n");
    add_item("furniture",
        "The furniture is carved from from fine oak. You see a bed, " +
        "a night stand, a bench, and a sofa.\n");
    add_item("sofa", 
        "The sofa is quite large over stuffed. It looks inviting " +
        "and is decorated with a paisley pattern.\n");
    add_item(({"table", "night stand" }),
        "The night stand sits at one end of the bed and holds various " +
        "items of the the King.\n");
    add_item("bench",
        "This bench is ornately carved with scenes of the King's " +
        "childhood. It sits at the foot of the bed for the King to " +
        "sit on.\n");
    add_item(({"light", "star"}),
        "This light source hangs above you, unattached to the " +
        "ceiling or walls. It is large and fills the room with " +
        "light. It appears to be a large crystal with an internal " +
        "flame brightly burning within its center.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling is painted a light blue, resembling the sky. " +
        "A large light fills the room with light.\n");
    add_item(({"wall", "walls", "scenes"}),
        "The scenes on the walls shift and change. They are scenes " +
        "of the King's homeland back among the Silvanesti. " +
        "Occaisonally, you see members of his family.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs", 
               "carpet", "carpets"}),
        "The carpet is a rich deep blue. A mighty lion, wearing a " +
        "cape of roses, adorns the carpet. It signifies the strength " +
        "and power of the King and the uniting of the Silvanesti of " +
        "Krynn with the elves of Emerald.\n");
 
    add_my_desc("@@bed_desc@@", this_object());
    add_item("bed", "@@bed_desc2@@");
 
    setuid();
    seteuid(getuid());
    reset_passage = 0;
 
    add_exit( TCASTLE_DIR + "k_lib", "east");
    add_exit( TCASTLE_DIR + "k_dr",     "west");
 
 
}
 
void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    if (ob->query_prop(IS_LIEING))
    {
        ob->remove_prop(IS_LIEING);
        ob->unset_no_show_composite();
        ob->remove_subloc(LIE_SUBLOC);
    }
}
 
void
init()
{
    ::init();
 
    add_action(do_lie, "lie");
    add_action(do_lie, "enter");
    add_action(do_rise, "rise");
    // add_action("knock_wall", "knock");
    // add_action("enter_passage","enter");   
}
 
int
do_lie(string arg)
{
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (query_verb() == "lie" && arg != "in bed" && arg != "on bed")
        return 0;
    else if (query_verb() == "enter" && arg != "bed")
        return 0;
    notify_fail("But you resting on bed the already.\n");
    if (this_player()->query_prop(IS_LIEING))
        return 0;
    this_player()->add_prop(IS_LIEING, 1);
    this_player()->set_no_show_composite(1);
    this_player()->add_subloc(LIE_SUBLOC, this_object());
    write("You crawl onto the bed and lie down.\n");
    say(QCTNAME(this_player()) + " leaps onto the bed and lies down.\n");
    return 1;
}
 
int
do_rise(string arg)
{
    notify_fail("Rise what?\n");
    if (arg && arg != "from bed")
        return 0;
    notify_fail("But you aren't lying in the bed!\n");
    if (!this_player()->query_prop(IS_LIEING))
        return 0;
    this_player()->remove_prop(IS_LIEING);
    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(LIE_SUBLOC);
    write("You get up from the bed.\n");
    say(QCTNAME(this_player()) + " leaps out of the bed.\n");
    return 1;
}
 
int
filter_lying(object ob)
{
    return ob->query_prop(IS_LIEING);
}
 
int
filter_remove_lie(object ob)
{
    ob->unset_no_show_composite();
    return 1;
}
 
int
filter_add_lie(object ob)
{
    ob->set_no_show_composite(1);
}
 
string
bed_desc()
{
    object *obs;
    string str;
 
    obs = FILTER_OTHER_LIVE(all_inventory());
    obs = filter(obs, filter_lying);
    filter(obs, filter_remove_lie);
    str = "A large feather bed is here.\n";
    if (sizeof(obs) > 1)
        str += " " + COMPOSITE_LIVE(obs) + " are lying in it.";
    else if (sizeof(obs))
        str += " " + COMPOSITE_LIVE(obs) + " is lying on the bed.";
    str += "\n";
    filter(obs, filter_add_lie);
    return str;
}
 
string
bed_desc2()
{
    object *obs;
    string str;
 
    obs = FILTER_OTHER_LIVE(all_inventory());
    obs = filter(obs, filter_lying);
    filter(obs, filter_remove_lie);
    str = "It dominates the room. The bed has four posters shaped " +
          "as large trees. A veil of silk surrounds the bed, " +
          "offering privacy to the bed. The veil is parted in the " +
          "middle. A thick feather mattress fills the bed frame and " +
          "is covered by feather comforters and several pillows.";
    if (sizeof(obs) > 1)
        str += " " + COMPOSITE_LIVE(obs) + " are lying in it.";
    else if (sizeof(obs))
        str += " " + COMPOSITE_LIVE(obs) + " is lying in it.";
    str += "\n";
    filter(obs, filter_add_lie);
    return str;
}
 
nomask string
show_subloc(string subloc, object on, object for_ob)
{
    string str;
 
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != LIE_SUBLOC)
        return "";
    if (for_ob == on)
        str = "You are";
    else
        str = capitalize(on->query_pronoun()) + " is";
    return str + " lying in the huge bed.\n";
}
 
 
void
reset_room()
{
}
 
int knock_wall(string str)
{
    int chance;
 
    if( str == "on wall" || str == "wall")
        {
            chance = (random(5));
            if (chance !=1)          // wall doesn't open
            {
                write("You feel dumb knocking on a stone wall.\n");
                say (QCTNAME(this_player()) + " knocks on a stone wall.\n");
                if (reset_passage == 1)
                {
                    tell_room("k_room", "The wall closes, hiding all " +
                        "traces of the secret passage.\n");
                    reset_passage = 0;
                }
            }
            else
            {
                write ("The wall opens up, revealing a secret " +
                    "passage.\n");
                reset_passage = 1;
            }
            return 1;
        }
        else
        {
            write ("Knock on what?\n");
            return 1;
        }
}
 
 
int
enter_passage(string str)
{
 
    if ((str == "passage" || str == "passageway") && reset_passage == 1)
    {
        write ("You step into a dark passage.\n");
        say (QCTNAME(TP) + " leaves into a dark passage.\n");
        TP->move_living( "M", TCASTLE_DIR + "q_room", 0, 0);
        tell_room( TCASTLE_DIR + "q_room",
            QCTNAME(TP) + " arrives from a secret passage.\n", TP);
        return 1;
    }
    else
    {
        write ("You run into a wall.\n");
        say (QCTNAME(TP) + " runs into a wall.\n");
        return 1;
    }
    reset_passage = 0;
   
}
