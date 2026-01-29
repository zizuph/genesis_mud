inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define DOWN_ROOM      (MORGUL_DIR + "tunnel/deadend1")

int    web_closed = 1; /* 0 = wep is open */

void
create_room()
{
    add_exit(DOWN_ROOM, "down", "@@climb_down", 4);
    add_exit(MORGUL_DIR + "tunnel/hiding2", "southwest", "@@pass_web", 2);

    make_the_room(" A dark hole in the floor is leading down. " +
        "The cave continues to the southwest where it becomes a bit larger. " +
        "But between here and that part of the cave a giant cobweb is " +
        "hanging. ");

    add_item(({"hole","opening","entrance"}), VBFC_ME("exa_hole"));
    add_item(({"boulder"}), VBFC_ME("exa_boulder"));
    add_item(({"web","cob-web","cobweb","cob web"}), VBFC_ME("exa_web"));
    add_item(({"thread","threads","cord","cords"}), BSN(
        "Each cords of the giant web is as large as a rope. The material of which the " +
        "threads are made seems to be very tough, hard like metal, but resilient at the " +
        "same time. Most of the cords are covered by a gleaming substance."));

    web_closed = 1;
    seteuid(getuid());
}

int climb_down()
{
    if(DOWN_ROOM->query_boulder())
    {
        write("You climb down through the hole in the floor.\n");
        return 0;
    }
    write("You cannot climb down.\n" +
        "The hole is blocked by a large boulder.\n");
    return 1;
}

string exa_hole()
{
    string desc;

    desc = "Close to the northern wall, there is a hole in the floor. ";

    if(DOWN_ROOM->query_boulder())
        desc += "You can climb down through the hole to leave this part of the cave. ";
    else
        desc += "But the hole is blocked by a large boulder on the other side. ";

    return BSN(desc);
}

string exa_boulder()
{
    if(DOWN_ROOM->query_boulder())
        return "You find no boulder.\n";
    else
        return BSN("Through the hole in the floor you can see that the hole is blocked " +
            "by a large boulder that someone rolled under the hole in the part of the " +
            "cave just below this one. From up here, there is no way to remove the boulder.");
}

int do_climb(string str)
{
    NF("Climb where?\n");
    if(!str || (str != "down" && str != "through hole" && str != "hole"))
        return 0;
    TP->command("down");
    return 1;
}

void init()
{
    ::init();
    add_action("do_climb","climb");
    add_action("do_push","push");
    add_action("do_push","move");
    add_action("do_cut","cut");
}

void clings_to_web(object victim, object armour)
{
    object stick_ob;

    seteuid(getuid());
    stick_ob = clone_object(MORGUL_DIR + "obj/stick_ob");
    stick_ob->move(victim,1);
    stick_ob->set_stick_object(armour);
    if(victim == armour)
        victim->catch_msg("You cling to the web with your body.\n");
    else
        victim->catch_msg("You cling to the web with your "+armour->query_name()+".\n");
}

int filter_noautoload(object x) { return (x->query_auto_load() ? 0 : 1); }

int check_wep_capture()
{
    object *armours;

    if(TP->resolve_task(TASK_ROUTINE, ({TS_INT, TS_DEX})) > 0)
        return 0;
    /* player gets caught in the web */
    write("Clumsily, you run right into the giant cobweb.\n"+
          BSN("When you touch the thick threads, you notice that they are covered " +
          "with a sticky substance."));
    LSAY("Clumsily, "," runs right into the giant cobweb. "+
          CAP(TP->query_pronoun())+" is caught by the thick threads, which " +
          "are covered with a sticky substance.");
    armours = filter(TP->query_armour(-1),"filter_noautoload",TO);
    if(!sizeof(armours))
        clings_to_web(TP,TP);
    else
        clings_to_web(TP,armours[random(sizeof(armours))]);
    return 1;
}

int pass_web()
{
    if(web_closed)
    {
        write("The cobweb is completely blocking the way to the southwest.\n");
        check_wep_capture();
        return 1;
    }
    write(BSN("You walk through the cut in the giant cobweb, careful not to touch one of the sticky cords."));
    say(QCTNAME(TP) + " carefully walks through the cut in the cobweb.\n");
    return 0;
}

int filter_slash(object wep) { return (wep->query_dt() & W_SLASH); }

int filter_elfdagger(object wep) 
{ 
    return ((wep->query_prop(OBJ_I_IS_MAGIC_WEAPON)) &&
            (sizeof(wep->query_prop(MAGIC_AM_MAGIC)) > 1) &&
            (wep->query_prop(MAGIC_AM_MAGIC)[1] == "abjuration") &&
            (member_array("elven", wep->query_adjs()) > -1));
}

int do_cut(string str)
{
    string vb = query_verb();
    string dummy;
    string pron = TP->query_pronoun();
    string poss = TP->query_possessive();
    string wname;
    object *weapons = TP->query_weapon(-1);
    object *elfdagger;
    int    sw = sizeof(weapons);

    NF(CAP(vb) + " what?\n");
    if(!str || (str != "web" && sscanf(str,"%sweb%s", dummy, dummy) == 0 
            &&  str != "thread" && sscanf(str,"%sthread%s", dummy, dummy) == 0))
        return 0;

    NF("You do not wield any weapon to cut the threads of the cobweb!\n");
    if(!sw)
        return 0;

    weapons = filter(weapons,"filter_slash",TO);

    NF("You need a sharper weapon than the one" + (sw==1?"":"s")+
        " you are wielding!\n");
    if(!sizeof(weapons))
        return 0;

    NF(BSN("Someone already cut a large rent into the middle of the cobweb. " +
        "You don't need to cut the web again!"));
    if(!web_closed)
        return 0;

    elfdagger = filter(weapons,"filter_elfdagger",TO);

    if(!sizeof(elfdagger))
    {
        wname = weapons[0]->query_name();
        write(BSN("You hew at the web with your " + wname + ", but the thread " +
            "you strike does not break. It gives a little and then springs " +
            "back like a plugged bowstring, tossing up both " + wname + " and arm."));
        SAY(" hews at the web with " + poss + " " + wname + ", but the thread " +
            pron + " strikes does not break. It gives a little and then springs " +
            "back like a plugged bowstring, tossing up both " + wname + " and arm.");
        if(!random(10))
            weapons[0]->set_dull(weapons[0]->query_dull()+1);
        weapons[0]->set_weapon_hits(weapons[0]->query_weapon_hits()+20);
    }
    else
    {
        wname = elfdagger[0]->query_name();
        write(BSN("You hew the web with a wide sweeping stroke. The blade " +
            "of your " + wname + " shears " +
            "through the close-strung cords like a scythe through grass. You make " +
            "a great rent in the middle of the vast cobweb."));
        SAY(" hews the web with a wide sweeping stroke. The blade of " + poss +
            " " + wname + " shears through the close-strung cords like a " +
            "scythe through grass. " + CAP(pron) + " makes a great rent in " +
            "middle of the vast cobweb."); 
        web_closed = 0;
    }
    return 1;
}

string exa_web()
{
    string desc;

    desc = "Across the width and height of the cave to the southwest a vast web is spun, " +
        "orderly as the web of some huge spider, but denser-woven and far greater, and with " +
        "threads as thick as a rope. The cords of the web glitter strangely in the shine " +
        "of your light source. ";
    if(web_closed)
        desc += "The web completely blocks the passage to the southwest. ";
    else
        desc += "Someone has cut a great rent through the middle of the web through which " +
            "you could walk to the southwest. ";

    return BSN(desc);
}

void reset_room()
{
    web_closed = 1;
}

int query_web_closed() { return web_closed; }

int do_push(string str)
{
    string vb = query_verb();

    NF(CAP(vb) + " what?\n");
    if(!str || (str != "boulder" && str != "rock"))
        return 0;

    NF("You find no " + str + ".\n");
    if(DOWN_ROOM->query_boulder())
        return 0;

    NF("From up here, it is impossible to "+vb+" the "+str+" in the cave below.\n");
        return 0;
}
