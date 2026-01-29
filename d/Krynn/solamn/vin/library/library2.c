/*  Library Writing Room,   Vingaard Keep     */
/*  Coded by Teth, 09/02/96     */
/*  modified from /d/Krynn/solamn/vkeep/guntroom.c  */
    
#include "lib.h"

inherit IN_BASE;

#define     IS_SITTING     "_player_i_is_sitting"
#define     SIT_SUBLOC     "_subloc_sitting"

void
create_vin_room()
{
    set_short("A writing room");
    set_long("This small room is perfectly suited for someone to " +
        "compose fine texts of quality. The room is well-lit by " +
        "candles which cast a soft light. Several desks are " +
        "present, each complete with a fairly comfortable chair. " +
        "The main portion of the library exists to the west, " +
        "where books are stored and indexed.\n");
    
    add_item("candles", "These elongate columns of wax are lit, " +
        "casting a soft and subdued light through the entire " +
        "alcove. They create enough light for any potential author.\n");
    add_item("desks", "Composed of solid oak from the forests near " +
        "Kalaman, these desks are sturdy and practical. Each is " +
        "covered with smudge marks.\n");
    add_item(({"smudge marks", "marks", "smudges"}), "These smudge " +
        "marks exist in only one colour, black. Presumably, " +
        "they are spots created by ancient incidents of spilled " +
        "ink.\n");
    add_item("chairs", "Somewhat comfortable looking, each chair is " +
        "constructed from black chestnut and is topped with a " +
        "slim cushion. It looks very possible to sit on any " +
        "of them.\n");
    add_item("chair", "One chair is fairly indistinguishable from the " +
        "next. Each is slightly pillowed, giving some measure of " +
        "comfort, and is ideal to sit in if one is composing " +
        "a book.\n");
    
    add_exit(VLIB+"library", "west", 0);
    LIGHT;
    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
        "teleportation in this area... or is it something else?\n");
    add_my_desc("@@chair_desc@@", this_object());
}

void
init()
{
    ::init();
    ADD("do_sit", "sit");
    ADD("do_rise", "rise");
    ADD("do_rise", "stand"); 
}

void
leave_inv(object ob, object to)
{
    if (this_player()->query_prop(IS_SITTING))
        {
        this_player()->remove_prop(IS_SITTING);
        this_player()->unset_no_show_composite();
        this_player()->remove_subloc(SIT_SUBLOC);
    }
} 

nomask static int
do_sit(string str)
{
    object *pl;
    int i;
    
    pl = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    pl = filter(pl, "filter_sitting_in_chair", this_object());
    
    NF("Sit where?\n");
    if (str && str != "chair" && str != "in chair" &&
            str != "on chair" && str != "down")
    return 0;
    
    NF("You cannot sit in two chairs at once!\n");
    if (this_player()->query_prop(IS_SITTING))
        return 0;
    else
        {
        this_player()->add_prop(IS_SITTING, 1);
        write("You sit in one of the chairs, perhaps readying yourself " +
            "to compose a book.\n");
        say(QCTNAME(this_player()) + " sits in one of the chairs, "+
            "perhaps for the purpose of composing a book.\n");
    }
    this_player()->set_no_show_composite(1);
    this_player()->add_subloc(SIT_SUBLOC, this_object());
    return 1;
}        
nomask static int
do_rise(string str)
{
    
    NF("Rise from where?\n");
    if (str && str != "chair" && str != "from chair")
        return 0;
    
    NF("You are already standing.\n");
    if (!this_player()->query_prop(IS_SITTING))
        return 0;
    
    else
        {
        this_player()->remove_prop(IS_SITTING);
        this_player()->unset_no_show_composite();
        this_player()->remove_subloc(SIT_SUBLOC);
        write("You get up from the chair.\n");         
        say(QCTNAME(this_player()) + " gets up from the chair.\n");
    }
    return 1;
}


static int
filter_sitting_in_chair(object pl)
{
    return pl->query_prop(IS_SITTING) == 1;
}

static int
filter_remove_sit(object pl)
{
    pl->unset_no_show_composite();
    return 1;
}

static int
filter_add_sit(object pl)           
{
    pl->set_no_show_composite(1);
    return 1;
}

static string
map_live(object pl)
{
    if (pl == this_player())
        return "you";
    return pl->query_the_name(this_player());
}

nomask string
chair_desc()
{
    object *pls;
    string *who, str = "";
    int i;
    
    pls = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());           
    pls = filter(pls, "filter_sitting_in_chair", this_object());
    filter(pls, "filter_remove_sit", this_object());
    
    who = map(pls, "map_live", this_object());
    filter(pls, "filter_add_sit", this_object());
    if (sizeof(pls) == 1 && pls[0] == this_player())
        str += " You are sitting in one of the chairs, perhaps composing " +
    "a book.";
    else if (sizeof(pls) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
    " are sitting in " + LANG_WNUM(sizeof(pls)) +
    " of the chairs, perhaps composing books.";
    
    else if (sizeof(pls))
        str += "" + capitalize(COMPOSITE_WORDS(who)) +
    " is sitting in a chair, perhaps composing a book.";
    
    str += "\n";
    return break_string(str, 70); 
}

nomask string
show_subloc(string subloc, object on, object for_pl)
{
    string str;
    
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
            subloc != SIT_SUBLOC)
    return "";
    if (for_pl == on)
        str = "You are";
    else
        str = capitalize(on->query_pronoun()) + " is";
}                                
