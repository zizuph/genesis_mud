/*
 *	/d/Gondor/ithilien/emyn-arnen/palace/sthall.c
 *
 *	Coded 1994 by Olorin.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin: Changed inheritance, added items.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/ithilien/emyn-arnen/arnen_items.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

#define MIN_AWARENESS  25

int     hint_alarm = 0,
        hint_c;

public void
create_gondor()
{
    set_short("the Hall of the Stewards");
    set_long(BSN("This is a large circular hall in the House of the Stewards in "
      + "Emyn Arnen. The large dome is not supported by any pillars but is "
      + "carried by the weight of its stone blocks alone. Below the dome "
      + "there are many statues standing in a large circle."));

    add_exit(ITH_DIR + "emyn-arnen/palace/ghall", "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/palace/pass2", "west",  0, 1);

    add_item(({"roof", "ceiling", "dome", }), BSN(
        "The large dome is carried alone by the weight of the stone "
      + "blocks that it is made of."));

    add_item(({"statues", "circle", }), BSN(
        "These are the statues of all Ruling Stewards of Gondor, starting "
      + "with Mardil Voronwe, who was Steward when Earnur, last King of "
      + "Gondor died in combat with the Witch-king in the year 2050 of "
      + "the Third Age, and ending with Turgon, who died in the year "
      + "2953 of the Third Age, one year before the last inhabitants "
      + "left Ithilien fleeing from the Dark Shadow."));

    add_item(({"statue", }), BSN(
        "Which statue do you want to look at? There are dozens of them "
      + "here. You can use the name of the Steward depicted to designate "
      + "a specific statue."));

    add_palace_walls();
    add_palace_floor();
    add_palace_stones();

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 12);
}

mixed
find_statue(string str)
{
    int     no;
    string  dummy,
            st_name;
    mixed  *stewards;

    if (!strlen(str))
        return 0;

    str = LOW(str);

    FIX_EUID

    stewards = BSW_QUEST_MASTER->query_rulers("stewards");
    // 'exa statue 7'
    if (sscanf(str, "statue %d", no) == 1)
    {
        if (no < sizeof(stewards)/2 && no > 0)
            st_name = stewards[(no-1)*2];
        if (strlen(st_name))
        {
            if (BSW_QUEST_MASTER->query_rulers("stewards", st_name) >
                BSW_STEWARDS_LAST_YEAR)
                return 0;
        }
        else
            return 0;
    }
    // 'exa 7th statue'
    else if (sscanf(str, "%d%s statue", no, dummy) == 2)
    {
        if (member_array(dummy, ({"st", "nd", "rd", "th"})) == -1)
            no = -1;
        if (no < sizeof(stewards)/2 && no > 0)
            st_name = stewards[(no-1)*2];
        if (strlen(st_name))
        {
            if (BSW_QUEST_MASTER->query_rulers("stewards", st_name) >
                BSW_STEWARDS_LAST_YEAR)
                return 0;
        }
        else
            return 0;
    }
    // 'exa seventh statue'
    else if (sscanf(str, "%s statue", dummy) == 1)
    {
        if ((no = LANG_ORDW(dummy)) == 0)
            return 0;
        if (no < sizeof(stewards)/2 && no > 0)
            st_name = stewards[(no-1)*2];
        if (strlen(st_name))
        {
            if (BSW_QUEST_MASTER->query_rulers("stewards", st_name) >
                BSW_STEWARDS_LAST_YEAR)
                return 0;
        }
        else
            return 0;
    }
    // 'exa statue of <name>'
    else if ((sscanf(str, "statue of %s", dummy) == 1) ||
             (sscanf(str, "the statue of %s", dummy) == 1))
    {
        if ((no = member_array(dummy, stewards)) >= 0)
        {
            st_name = LOW(dummy);
            if (BSW_QUEST_MASTER->query_rulers("stewards", st_name) >
                BSW_STEWARDS_LAST_YEAR)
                return 0;
            no /= 2;
            no++;
        }
        else
            return 0;
    }
    // 'exa <name>'
    else if ((no = member_array(str, stewards)) >= 0)
    {
        st_name = str;
        if (BSW_QUEST_MASTER->query_rulers("stewards", st_name) >
            BSW_STEWARDS_LAST_YEAR)
            return 0;
        no /= 2;
        no++;
    }
    else
        return 0;

    if (!strlen(st_name))
        return 0;
    if (no == 1)
        return ({ st_name, no, 2050, stewards[(no-1)*2+1], });
    return ({ st_name, no, stewards[(no-1)*2-1], stewards[(no-1)*2+1], });
}

int
exa_statue(string str)
{
    int     no,
            start,
            end;
    mixed   result;
    object  scroll;
    string  vb = query_verb(),
            dummy,
            desc,
            st_name = 0;

    if (!strlen(str))
        return 0;

    if (vb == "l" || vb == "look")
    {
        if (sscanf(str, "at %s", dummy) == 1)
            str = dummy;
        else
        {
            NF("Look needs a preposition with an object.\n");
            return 0;
        }
    }

    result = find_statue(str);
    if (!result)
        return 0;

    st_name = result[0];
    no      = result[1];
    start   = result[2];
    end     = result[3];

    desc = "This is the statue of ";
    desc += BSW_QUEST_MASTER->cap_name(st_name);
    desc += ", "+LANG_WORD(no)+" Ruling Steward of Gondor.";

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if ((scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
            && (LOW(BSW_QUEST_MASTER->query_random_ruler("stewards", 
            TP->query_real_name())) == st_name))
            desc += " He held the rod and ruled in the name of the King "
                  + "from the year "+start+" to the year "+end
                  + " of the Third Age and he was the Steward who "
                  + "ordered that the heirlooms of the House of Hurin "
                  + "should be hidden to protect them against raids. "
                  + "Somehow you feel that his statue might reveal some "
                  + "hint where to look for the hidden treasure.";
    }
    write(BSN(desc));
    return 1;
}

int
search(string str)
{
    int     time;
    mixed   result;
    object  obj;
    string  item,
            rest;

    if (!str)
    {
	NF("Search what?\n");
	return 0;
    }

    if (TP->query_attack())
    {
        write("But you are in the middle of a fight!\n");
        return 1;
    }

    result = find_statue(str);
    if (!pointerp(result))
    {
        NF("You don't find any " + str + " to search.\n");
	return 0;
    }

    obj = TO;

    write("You start to search the " + str + ".\n");
    say(QCTNAME(TP) + " starts to search the " + str + ".\n");

    obj->search_object(str);
    return 1;
}

string
do_search(object pl, string str)
{
    mixed   result;
    object  scroll;
    string  st_name,
            desc;

    if (str == "statue" || str == "statues")
        return "Which statue do you want to search?\n";

    result = find_statue(str);

    if (!pointerp(result))
        return 0;

    st_name = (string)result[0];
    desc = "You search the statue of "+BSW_QUEST_MASTER->cap_name(st_name)+".";

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, pl)))
    {
        if ((scroll->query_prop(BSW_S_SCROLL_OWNER) == pl->query_real_name())
            && (LOW(BSW_QUEST_MASTER->query_random_ruler("stewards", 
            pl->query_real_name())) == st_name)
            && (pl->query_skill(SS_AWARENESS) > MIN_AWARENESS))
            desc += " After a careful examination of the statue, you find that "
                  + "it is possible to move the arm of the statue.";
        else
            desc += " You find nothing special.";
    }
    else
        desc += " You find nothing special.";

    return BSN(desc);
}

int
do_move(string str)
{
    mixed   result;
    object  scroll;
    string  statue,
            st_name;

    if (!strlen(str))
    {
        NFN0("Move what?");
    }

    if (str == "arm")
    {
        NFN0("Move the arm of which statue?");
    }

    if ((sscanf(str, "arm of %s", statue) != 1) &&
        (sscanf(str, "the arm of %s", statue) != 1))
    {
        NFN0("Move what?");
    }

    result = find_statue(statue);

    if (!pointerp(result))
        NFN0("Move the arm of which statue?");

    st_name = (string)result[0];

    if (objectp(scroll = present(BSW_YRCHOR_SCROLL, TP)))
    {
        if ((scroll->query_prop(BSW_S_SCROLL_OWNER) == TP->query_real_name())
            && (LOW(BSW_QUEST_MASTER->query_random_ruler("stewards", 
            TP->query_real_name())) == st_name)
            && (TP->query_skill(SS_AWARENESS) > MIN_AWARENESS))
        {
            if (hint_alarm)
                write("You move the arm, but the statue seems to be busy.\n");
            else
            {
                hint_c = 0;
                hint_alarm = set_alarm(1.0, 2.0, "give_hint", TP, st_name);
                write("Click!\n" +
                      "You seem to have started something inside the statue.\n");
                say("As "+QTNAME(TP)+" moves the arm of the statue of "
                    + BSW_QUEST_MASTER->cap_name(st_name)+", something inside "
                    + "goes 'Click!'.\n");
            }
            return 1;
        }
    }
    write(BSN("You try to move the arm of the statue of "
        + BSW_QUEST_MASTER->cap_name(st_name)+", but it is impossible."));
    say(QCTNAME(TP)+" fumbles around at the statue of "
        + BSW_QUEST_MASTER->cap_name(st_name)+".\n");

    return 1;
}

void
give_hint(object pl, string st_name)
{
    int     d_isil = 6666,
            d_anar = 6666;
    string  cst_name = BSW_QUEST_MASTER->cap_name(st_name),
            pname = pl->query_real_name();

    if (!present(pl, TO))
    {
        remove_alarm(hint_alarm);
        hint_alarm = 0;
        hint_c = 0;
    }

    switch(hint_c++)
    {
        case 0:
            tell_room(TO, "The statue of "+cst_name
              + " suddenly seems to become alive.\n");
            break;
        case 1:
            tell_room(TO, cst_name+" says: Below the Hall of the Stewards one "
              + "can find the heirlooms of the House of Hurin.\n");
            break;
        case 2:
            tell_room(TO, cst_name+" says: I, "+cst_name+", Steward of Gondor, "
              + "have brought them there and with the help of the Wise, I have "
              + "protected them.\n");
            break;
        case 3:
            tell_room(TO, cst_name+" says: Only the Heirs of Elendil can open "
              + "the door that leads to them.\n");
            break;
        case 4:
            d_isil = BSW_QUEST_MASTER->query_delta_year_isildur(pname),
            tell_room(TO, cst_name + " whispers something to "+QTNAME(pl)
              + ".\n", pl);
            pl->catch_msg(cst_name+" whispers to you: Call the Heir of Isildur "
              + "that reigned "+d_isil+" years before I began my Stewardship.\n");
            break;
        case 5:
            d_anar = BSW_QUEST_MASTER->query_delta_year_anarion(pname),
            tell_room(TO, cst_name + " whispers something to "+QTNAME(pl)
              + ".\n", pl);
            pl->catch_msg(cst_name+" whispers to you: Then call the Heir of "
              + "Anarion that was King "+d_anar+" years before I pledged to hold "
              + "rod and rule in the name of the Kings.\n");
            break;
        case 7:
            tell_room(TO, cst_name + " whispers something to "+QTNAME(pl)
              + ".\n", pl);
            pl->catch_msg(cst_name+" whispers to you: But be careful! "
              + "To err is to die!\n");
            break;
        case 9:
            tell_room(TO, "The statue of "+cst_name+" becomes stone again.\n");
        case 10:
            remove_alarm(hint_alarm);
            hint_alarm = 0;
            hint_c = 0;
            break;
        default:
            break;
    }
}

public void
init()
{
    ::init();

    add_action(exa_statue, "l");
    add_action(exa_statue, "look");
    add_action(exa_statue, "exa");
    add_action(exa_statue, "examine");
    add_action(search,     "search");
    add_action(do_move,    "move");
}

