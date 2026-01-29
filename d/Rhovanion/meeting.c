/* This is the meeting room for the Wizards of Rhovanion.
 * the room has been coded by major help from Plugh
 * Coded by Daneel 14 november 1993.
 */

inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>

#define IS_SITTING  "_player_i_is_sitting"
#define SIT_SUBLOC  "_subloc_sitting"

void create_room()
{
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 1);

  set_short("Meeting room");
  set_long(BS("This is the meeting room for the wizards of Rhovanion. " +
              " \n"));

  add_item("table","A large oval table made of dark wood.\n");
  add_item(({"chair","chairs"}),"@@chair_desc2@@");
  add_cmd_item(({"chair","chairs"}),
               ({"get",  "take"  }),
               "The chair shies away!\n");

  add_my_desc("@@chair_desc@@",TO);
    add_exit("/d/Rhovanion/workroom", "rhovanion");
}

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
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
    obs = filter(obs, "filter_sitting_in_lap", this_object());
    for (i=0 ; i<sizeof(obs) ; i++)
        if (obs[i]->query_prop(IS_SITTING) == ob) {
            obs[i]->remove_prop(IS_SITTING);
            obs[i]->unset_no_show_composite();
            obs[i]->catch_msg("You are dumped on the floor.\n");
            tell_room(TO, QCTNAME(obs[i]) + " is dumped on the "+
                      "floor.\n", obs[i]);
        }
}


nomask void
init()
{
  ;
  ::init();
  add_action("do_sit", "sit");
  add_action("do_rise", "rise");
}

nomask int
do_sit(string arg)
{
    object *obs, *obs2;
    int i;
 
    notify_fail("Sit where?\n");
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
    obs = filter(obs, "filter_sitting_in_chair", TO);
    if (arg && arg != "chair" && arg != "in chair" && arg != "on chair" &&
        arg != "down")
        return 0;
    notify_fail("But you ARE sitting!\n");
    if (TP->query_prop(IS_SITTING))
        return 0;
    if (sizeof(obs2)) {
        if (sizeof(obs2) > 1)
            return 0;
        obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
        for (i=0 ; i<sizeof(obs) ; i++)
            if (obs[i]->query_prop(IS_SITTING) == obs2[0])
                return 0;
        TP->add_prop(IS_SITTING, obs2[0]);
    }
    else {
        TP->add_prop(IS_SITTING, 1);
        write("You sit down in one of the comfortable chairs.\n");
        say(QCTNAME(TP) + " sits down in one of the comfortable "+
            "chairs.\n");
    }
    TP->set_no_show_composite(1);
    TP->add_subloc(SIT_SUBLOC, TO);
    return 1;
}

nomask int
do_rise(string arg)
{
    object ob, *obs;
    int i;
 
    notify_fail("Rise from where?\n");
    if (arg && arg != "chair" && arg != "from chair" )
        return 0;
    notify_fail("But you AREN'T sitting!\n");
    if (!TP->query_prop(IS_SITTING))
        return 0;
    if (objectp(TP->query_prop(IS_SITTING))) {
        ob = TP->query_prop(IS_SITTING);
        TP->remove_prop(IS_SITTING);
        TP->unset_no_show_composite();
        TP->remove_subloc(SIT_SUBLOC);
    }
    else {
        TP->remove_prop(IS_SITTING);
        TP->unset_no_show_composite();
        TP->remove_subloc(SIT_SUBLOC);
        write("You get up from the chair.\n");
        say(QCTNAME(TP) + " gets up from the chair.\n");
        obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
        for (i=0 ; i<sizeof(obs) ; i++)
            if (obs[i]->query_prop(IS_SITTING) == TP) {
                obs[i]->remove_prop(IS_SITTING);
                obs[i]->unset_no_show_composite();
                obs[i]->catch_msg("You are dumped on the floor.\n");
                tell_room(TO, QCTNAME(obs[i]) + " is dumped on "+
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

nomask string
chair_desc()
{
    object *obs;
    string *who, str;
    int i;
 
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
    obs = filter(obs, "filter_sitting_in_chair", TO);
    filter(obs, "filter_remove_sit", TO);
    str = "There are some comfortable-looking chairs here.";
    who = map(obs, "map_live", TO);
    filter(obs, "filter_add_sit", TO);
    if (sizeof(obs) == 1 && obs[0] == TP)
        str += " You are sitting in one of them.";
    else if (sizeof(obs) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " are sitting in " + LANG_WNUM(sizeof(obs)) + " of them.";
    else if (sizeof(obs))
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " is sitting in one of them.";
    str += "\n";
    return break_string(str, 76);
}

nomask string
chair_desc2()
{
    object *obs;
    string *who, str;
    int i;
 
    obs = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
    obs = filter(obs, "filter_sitting", TO);
    filter(obs, "filter_remove_sit", TO);
    str = "The chairs stands by the table and they looks very comfortable.";
    who = map(obs, "map_live", TO);
    filter(obs, "filter_add_sit", TO);
    if (sizeof(obs) == 1 && obs[0] == TP)
        str += " You are sitting in one of them.";
    else if (sizeof(obs) > 1)
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " are sitting in " + LANG_WNUM(sizeof(obs)) + " of them.";
    else if (sizeof(obs))
        str += " " + capitalize(COMPOSITE_WORDS(who)) +
               " is sitting in one of them.";
    str += "\n";
    return break_string(str, 76);
}

map_live(object ob)
{
    if (ob == TP)
        return "you";
    return ob->query_the_name(TP);
}
