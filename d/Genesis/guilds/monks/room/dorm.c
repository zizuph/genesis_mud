/*
 * File:    dorm.c
 * Creator: Cirion, 1998.06.14
 * Purpose: Start location for the monks
 */
#pragma strict_types
#include "defs.h"
#include <composite.h>

inherit ROOMBASE;

// list of objects we can take from this room
string *equip = ({ MONK_OBJ + "robe", MONK_OBJ + "belt", MONK_OBJ + "sandals",
        MONK_OBJ + "pants", MONK_OBJ + "shirt" });

// mapping of people who have taken stuff from this room so they
// cannot abuse it.
static mapping    people_equip = ([ ]);

string
equip_desc()
{
    // get the short descs from all the master objects
    return COMPOSITE_WORDS(equip->query_pname());
}

int
get_equip(string str)
{
    int       i;
    string    ob_path = "";
    string    check_ob = "";
    object    tp = this_player(), ob;
    string    desc;
    string    thing;
    object    pres;

    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!strlen(str))
        return 0;

    thing = str;

    if (parse_command (str, ({}), "[the] %s 'robe'", desc))
        thing = "robe";


    for(i=0;i<sizeof(equip);i++)
    {
        check_ob = equip[i];
        if(check_ob->id(thing))
        {
            ob_path = check_ob;
            break;
        }
    }

    // didn't find the item...
    if (ob_path == "")
        return 0;

    if(pres = present(ob_path, tp))
    {
        write("You already have " + LANG_ADDART(pres->short(TP)) + ". Taking "
            + "another one would be greedy.\n");
        return 1;
    }

    if(!m_query_monk(tp))
    {
        write("These items are reserved for members of the Order.\n");
        return 1;
    }

    // 3 hours until they can get the stuff again
    if(people_equip[tp->query_name() + ob_path] > (time() - (3600 * 3)))
    {
        write("You recently got that article of clothing from the rack -- "
            + "it would be unlawful to take more.\n");
        return 1;
    }


    ob = clone_object(ob_path);

    if (strlen (desc) > 0)
    {
        if (!ob->set_colour (desc))
        {
            write ("There is no " + thing + " in that colour.\n");
            ob->remove_object ();
            return 1;
        }
    }

    if(ob->move(tp))
        ob->move(environment(tp));
    tp->catch_msg("You take " + LANG_ADDART(ob->short(tp))
        + " from the racks.\n");

    // maintain a mapping of this player's equipment gathering
    // so they can't keep doing it over and over and sell or give away
    // the stuff. Unique mapping of the form:
    // nameobject path : time
    // e.g., Cirion/d/Genesis/guilds/monks/obj/shirt : 1000000
    people_equip[tp->query_name() + ob_path] = time();

    say(QCTNAME(tp) + " takes " + QSHORT(ob) + " from the shelves.\n");
    return 1;
}

void
create_room ()
{
    set_short("dormitory");
    set_long("Low wooden pallets are arranged evenly "
        + "all around the floor. This room is dark and "
        + "quiet, and has a very restful air to it. The basalt "
        + "blocks of the walls are lined with dry reeds to "
        + "keep out the cold air of the night, allowing those "
        + "who rest to wander down the peaceful venues of sleep.\n"
        + "Racks along the east wall contain clothing worn by members "
        + "of the Order: "
        + equip_desc() + ". A small doorway leads south into "
        + "a cleanly-swept room.\n");
    add_item(({"pallet","pallets","bed","beds"}),
        "They are simple wood-slat pallets, covered in "
        + "soft, thin bedding. Though simple, they look "
        + "comfortable and warm.\n");
    add_item(({"block","blocks","wall","walls"}),
        "The walls consist of great basalt stone blocks. "
        + "The spaces between them are filled with dry "
        + "reeds, so there is little draft.\n");
    add_item(({"reed","reeds"}),
        "They are dry with age.\n");
    add_item(({"rack","racks","clothes","robe","robes","belt","belts","sandals","sandal","trouser","trousers","shirt","shirts"}),
        "The rack on the east wall hold the standard "
        + "garments of the Dragon Order. They are simple and "
        + "comfortable, and free to those members who wish "
        + "to use them.\n");
    add_item(({"floor","ground"}),
        "Evenly spaced on the floor throughout the length "
        + "of this long room are simple wooden pallets.\n");

    // the dreams grow like slow ice....

    WIZINFO("This is wizard info for the monks room.\n");

    // where, command
    add_exit("hall_top", "north");
    add_exit("armoury", "south", VBFC_ME ("check_armoury_exit"));

}

public int
check_armoury_exit ()
{
    if ((!(this_player ()->m_query_monk ())) &&
        (!(this_player()->query_wiz_level ())))
    {
        write("You may not enter there.\n");
        return 1;
    }
    else
        return 0;
}

void
check_start(object who)
{
    if(who->query_default_start_location() != MASTER_OB(this_object()))
        return;

    // reset the start location if they start here, but are no
    // longer a monk

    if(!m_query_monk(who))
        who->set_default_start_location(who->query_def_start());

    // reset the start location if they are punished
    if(m_query_punishment(who, M_PUNISH_EXILE))
    {
        who->catch_msg("You are no longer allowed to begin within "
            + "the monestary.\n");
        who->set_default_start_location(who->query_def_start());
    }
}

int
start_here(string str)
{
    if(!m_query_monk())
        return 0;

    if(m_query_punishment(this_player(), M_PUNISH_EXILE))
    {
        write("You are forbidden by the Council from starting here.\n");
        return 1;
    }

    this_player()->set_default_start_location(file_name(this_object()));
    write("You pick out a pallet where you will rest from now on.\n");
    say(QCTNAME(this_player()) +" chooses a pallet for " + 
        this_player()->query_objective() + "self.\n");
    return 1;
}

void
enter_inv(object who, object from)
{
    ::enter_inv(who, from);

    if(!interactive(who))
        return;

    if(!(who->query_prop(LIVE_O_LAST_ROOM)))
    {
        tell_room(this_object(), QCNAME(who)+" awakens and gets up from "
            + who->query_possessive() + " pallet.\n", ({ who }) );
        set_alarm(1.0, 0.0, &check_start(who));
    }
}

void
leave_inv(object who, object from)
{
    ::leave_inv(who, from);

    if(!interactive(who) || !m_query_monk(who) || !who->query_hp()
        || from)
        return;

    tell_room(this_object(), QCTNAME(who) + " lies down on "
        + who->query_possessive() + " pallet and goes to sleep.\n",
        ({ who }) );
}

void
init()
{
    ::init();

    add_action(start_here, "start");
    add_action(get_equip, "get");
    add_action(get_equip, "take");
}

