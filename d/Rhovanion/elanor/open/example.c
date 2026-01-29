inherit "/d/Emerald/plugh/private/lock_room";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>

#define MAILREADER      "/secure/mail_reader"

#define IS_SITTING      "_player_i_is_sitting"
#define SIT_SUBLOC      "_subloc_sitting"

nomask void
create_room()
{
    set_short("Elanor's workroom");
    set_long(break_string("You are in a dark and eerily lit office with "+
             "a large mahogony desk.  Strewn over the desk are plans and "+
             "maps of Middle Earth which seem to be protected by some "+
             "strange and mystical force.  Sitting on the middle of the "+
             "desk is a large worm riddled black book while in shelves "+
             "that surround the walls of the office are other books that "+
           "again seem to be protected by a mystic force\n", 70));

    add_item(({"shelf", "shelves"}),
             break_string("The shelves covers all the walls, from floor "+
             "to ceiling. They are filled with books that you suspect are "+
             "filled with the history of Middle Earth and arcane crafts.\n", 70));
    add_item(({"book", "books"}),
             break_string("Upon examining the books more closely you see "+
             "that they deal with the chivalry of the Rohirim the war of "+
             "The Ring and arcane crafts of the old ones.  Unfortunately or "+
             "fortunately for your sake you seem unable to touch them.\n", 70));
    add_item(({"black book", "open book"}),
             break_string("You feel an uneasy dread as you examine this "+
             "most evil of books it is totally black and open to the Title Page.  "+
             "You feel you must avert your eyes from the title of this most "+
             "infamous of books Necromicon or book of the dead by that mad Arab author.\n", 70));
    add_item(({"map", "maps"}),
             break_string("Maps of the like you have never seen before you "+
             "can tell they are cartographic masterpieces without touching "+
             "them.  As you gaze more closely at these maps you notice that "+
             "depict Middle Earth.  In particular the Gap of Rohan and Gondor.  \n", 70));
    add_item(({"plan", "plans"}),
             break_string("Notes and jottings written down on endless pieces "+
             "of paper.  You feel that they must have details of Elanor's "+
             "future projects unfortunately you cannot make them out.\n", 70));
    add_item(({"chair", "chairs"}),
             "@@chair_desc2@@");

    add_cmd_item(({ "book", "books" }),
                 ({ "get", "take" }),
                 "Some magical force is keeping you away.\n");
    add_cmd_item(({ "chair", "chairs" }),
                 ({ "get", "take" }),
                 "The chair shies away!\n");

    create_lock("/d/Rhovanion/elanor/private/workroom");

    add_my_desc("@@chair_desc@@", this_object());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT,
             "That is not the correct way of getting there.\n");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
    add_prop(ROOM_I_NO_EXTRA_DESC, 1);
    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    add_prop(ROOM_I_NO_EXTRA_ITEM, 1);

    set_lock();
}

nomask void
leave_inv(object ob, mixed to)
{
    object reader, *obs;
    int i;

    ::leave_inv(ob, to);
    reader = present("mailread", ob);
    if (reader)
        reader->remove_object();
    if (ob && !present(ob) && ob->query_prop(IS_SITTING)) {
        ob->catch_msg("You get up and leave the room.\n");
        ob->remove_prop(IS_SITTING);
        ob->unset_no_show_composite();
        ob->remove_subloc(SIT_SUBLOC);
    }
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_in_lap", this_object());
    for (i=0 ; i<sizeof(obs) ; i++)
        if (obs[i]->query_prop(IS_SITTING) == ob) {
            obs[i]->remove_prop(IS_SITTING);
            obs[i]->unset_no_show_composite();
            obs[i]->catch_msg("You are dumped on the floor.\n");
            tell_room(this_object(), QCTNAME(obs[i]) + " is dumped on the "+
                      "floor.\n", obs[i]);
        }
}

nomask void
enter_inv(object ob, mixed from)
{
    object reader;

    ::enter_inv(ob, from);
    if (ob && present(ob) && interactive(ob) &&
        (ob->query_real_name() == getuid() ||
	is_trusted(ob))) {
        reader = clone_object(MAILREADER);
        if (!reader) {
            ob->catch_msg("No mailreader is available at this time.\n");
            return;
        }
        if (reader->move(ob))
            reader->remove_object();
    }
}

nomask void
init()
{
    ::init();
    add_action("do_sit", "sit");
    add_action("do_rise", "rise");
}

nomask string
wizinfo()
{
    return "This is MY workroom. It is pretty secure too.\n";
}

nomask static int
do_sit(string arg)
{
    object *obs, *obs2;
    int i;

    notify_fail("Sit where?\n");
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_in_chair", this_object());
    if (arg && arg != "chair" && arg != "in chair" && arg != "on chair" &&
        arg != "down" && !sizeof(obs2 = FIND_STR_IN_ARR(arg, obs)))
        return 0;
    notify_fail("But you ARE sitting!\n");
    if (this_player()->query_prop(IS_SITTING))
        return 0;
    if (sizeof(obs2)) {
        notify_fail("Sit in whom's lap?\n");
        if (sizeof(obs2) > 1)
            return 0;
        obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
        obs = filter(obs, "filter_sitting_in_lap", this_object());
        notify_fail("Someone is sitting there!\n");
        for (i=0 ; i<sizeof(obs) ; i++)
            if (obs[i]->query_prop(IS_SITTING) == obs2[0])
                return 0;
        this_player()->add_prop(IS_SITTING, obs2[0]);
        write("You sit down in " + obs2[0]->query_the_name(this_player()) +
              "'s lap.\n");
        obs2[0]->catch_msg(QCTNAME(this_player()) + " sits down in your "+
                           "lap.\n");
        say(QCTNAME(this_player()) + " sits down in " + QTNAME(obs2[0]) +
            "'s lap.\n", ({ obs2[0], this_player() }));
    }
    else {
        if (getuid(this_player()) == getuid())
            this_player()->add_prop(IS_SITTING, 2);
        else
            this_player()->add_prop(IS_SITTING, 1);
        write("You sit down in one of the comfortable chairs.\n");
        say(QCTNAME(this_player()) + " sits down in one of the comfortable "+
            "chairs.\n");
    }
    this_player()->set_no_show_composite(1);
    this_player()->add_subloc(SIT_SUBLOC, this_object());
    return 1;
}

nomask static int
do_rise(string arg)
{
    object ob, *obs;
    int i;

    notify_fail("Rise from where?\n");
    if (arg && arg != "chair" && arg != "from chair" && arg != "from lap")
        return 0;
    notify_fail("But you AREN'T sitting!\n");
    if (!this_player()->query_prop(IS_SITTING))
        return 0;
    if (objectp(this_player()->query_prop(IS_SITTING))) {
        ob = this_player()->query_prop(IS_SITTING);
        this_player()->remove_prop(IS_SITTING);
        this_player()->unset_no_show_composite();
        this_player()->remove_subloc(SIT_SUBLOC);
        write("You get up from " + ob->query_the_name(this_player()) +
              "'s lap.\n");
        ob->catch_msg(QCTNAME(this_player()) + " gets up from your lap.\n");
        say(QCTNAME(this_player()) + " gets up from " + QTNAME(ob) +
            "'s lap.\n", ({ this_player(), ob }));
    }
    else {
        this_player()->remove_prop(IS_SITTING);
        this_player()->unset_no_show_composite();
        this_player()->remove_subloc(SIT_SUBLOC);
        write("You get up from the chair.\n");
        say(QCTNAME(this_player()) + " gets up from the chair.\n");
        obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
        obs = filter(obs, "filter_sitting_in_lap", this_object());
        for (i=0 ; i<sizeof(obs) ; i++)
            if (obs[i]->query_prop(IS_SITTING) == this_player()) {
                obs[i]->remove_prop(IS_SITTING);
                obs[i]->unset_no_show_composite();
                obs[i]->catch_msg("You are dumped on the floor.\n");
                tell_room(this_object(), QCTNAME(obs[i]) + " is dumped on "+
                          "the floor.\n", obs[i]);
        }
    }
    return 1;
}

static int
filter_sitting_in_chair(object ob)
{
    return ob->query_prop(IS_SITTING) == 1;
}

static int
filter_sitting_behind_desk(object ob)
{
    return ob->query_prop(IS_SITTING) == 2;
}

static int
filter_sitting_in_lap(object ob)
{
    return objectp(ob->query_prop(IS_SITTING));
}

static int
filter_remove_sit(object ob)
{
    ob->unset_no_show_composite();
    return 1;
}

static int
filter_add_sit(object ob)
{
    ob->set_no_show_composite(1);
    return 1;
}

static string
map_live(object ob)
{
    if (ob == this_player())
        return "you";
    return ob->query_the_name(this_player());
}

static string
map_lap(object ob)
{
    if (ob == this_player())
        return " You are sitting in " +
               (ob->query_prop(IS_SITTING))->query_the_name(this_player()) +
               "'s lap.";
    if (ob->query_prop(IS_SITTING) == this_player())
        return " " + ob->query_The_name(this_player()) + " is sitting in " +
               "your lap.";
    return " " + ob->query_The_name(this_player()) + " is sitting in " +
           (ob->query_prop(IS_SITTING))->query_the_name(this_player()) +
           "'s lap.";
}

nomask string
chair_desc()
{
    object *obs;
    string *who, str;
    int i;

    str = "There is a desk with a chair here. In front of the desk there "+
          "are some more comfortable-looking chairs.";
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_behind_desk", this_object());
    filter(obs, "filter_remove_sit", this_object());
    who = map(obs, "map_live", this_object());
    if (sizeof(obs) == 1 && obs[0] == this_player())
        str += " You are sitting in the chair behind the desk.";
    else if (sizeof(obs) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " are sitting in " + LANG_WNUM(sizeof(obs)) + " of the "+
               "chairs behind the desk.";
    else if (sizeof(obs))
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " is sitting in the chair behind the desk.";
    filter(obs, "filter_add_sit", this_object());
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_in_chair", this_object());
    filter(obs, "filter_remove_sit", this_object());
    who = map(obs, "map_live", this_object());
    filter(obs, "filter_add_sit", this_object());
    if (sizeof(obs) == 1 && obs[0] == this_player())
        str += " You are sitting in one of them.";
    else if (sizeof(obs) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " are sitting in " + LANG_WNUM(sizeof(obs)) + " of them.";
    else if (sizeof(obs))
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " is sitting in one of them.";
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_in_lap", this_object());
    filter(obs, "filter_remove_sit", this_object());
    who = map(obs, "map_lap", this_object());
    for (i=0 ; i<sizeof(who) ; i++)
        str += who[i];
    filter(obs, "filter_add_sit", this_object());
    str += "\n";
    return break_string(str, 70);
}

nomask string
chair_desc2()
{
    object *obs;
    string *who, str;
    int i;

    str = "The chairs looks very comfortable.";
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_behind_desk", this_object());
    filter(obs, "filter_remove_sit", this_object());
    who = map(obs, "map_live", this_object());
    if (sizeof(obs) == 1 && obs[0] == this_player())
        str += " You are sitting in the chair behind the desk.";
    else if (sizeof(obs) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " are sitting in " + LANG_WNUM(sizeof(obs)) + " of the "+
               "chairs behind the desk.";
    else if (sizeof(obs))
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " is sitting in the chair behind the desk.";
    filter(obs, "filter_add_sit", this_object());
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting", this_object());
    filter(obs, "filter_remove_sit", this_object());
    who = map(obs, "map_live", this_object());
    filter(obs, "filter_add_sit", this_object());
    if (sizeof(obs) == 1 && obs[0] == this_player())
        str += " You are sitting in one of them.";
    else if (sizeof(obs) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " are sitting in " + LANG_WNUM(sizeof(obs)) + " of them.";
    else if (sizeof(obs))
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " is sitting in one of them.";
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    obs = filter(obs, "filter_sitting_in_lap", this_object());
    filter(obs, "filter_remove_sit", this_object());
    who = map(obs, "map_lap", this_object());
    for (i=0 ; i<sizeof(who) ; i++)
        str += who[i];
    filter(obs, "filter_add_sit", this_object());
    str += "\n";
    return break_string(str, 70);
}

nomask string
show_subloc(string subloc, object on, object for_ob)
{
    string str;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != SIT_SUBLOC)
        return "";
    if (for_ob == on)
        str = "You are";
    else
        str = capitalize(on->query_pronoun()) + " is";
    if (on->query_prop(IS_SITTING) == for_ob)
        return str + " sitting in your lap.\n";
    if (objectp(on->query_prop(IS_SITTING)))
        return str + " sitting in " +
               (on->query_prop(IS_SITTING))->query_the_name(for_ob) +
               "'s lap.\n";
    if (on->query_prop(IS_SITTING) == 2)
        return str + " sitting in the chair behind the desk.\n";
    return str + " sitting in a comfortable chair.\n";
}

nomask void
report_try_snoop(object snooper)
{
    tell_trusted(QCTNAME(snooper) + " tried to snoop someone.\n");
}
