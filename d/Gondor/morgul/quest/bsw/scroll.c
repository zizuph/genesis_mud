/*
 * /d/Gondor/morgul/quest/bsw/scroll.c
 *
 * The scroll with the hint for the quest of retrieving
 * 	the battle standard of the Witchking
 *
 * Olorin, July 1994
 */
#pragma strict_types

inherit "/std/scroll";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

#define MIN_SKILL	20
#define GOOD_SKILL	50

public string  long_desc();

static  int     al_flag = 1;

public void
create_scroll()
{
    set_name("scroll");
    add_name(BSW_YRCHOR_SCROLL);
    set_short("old scroll");
    set_adj("old");
    set_long(long_desc);
}

string
long_desc()
{
    int     ls;
    string  desc = "There is some text written onto the " +
                   "scroll in Elvish tengwar, ";

    ls = TP->query_skill(SS_LANGUAGE);
    if (!stringp(query_prop(BSW_S_SCROLL_OWNER)))
        ls = MIN(ls, MIN_SKILL);

    if (ls < MIN_SKILL)
        desc = "The scroll is covered by strange signs. You " +
            "think that they might be tengwar, letters of an " +
            "Elvish writing system, but you lack the skill to " +
            "read them.";
    else if (ls < GOOD_SKILL)
        desc += "letters of an Elvish alphabet. You might manage " +
            "to decipher some of them, but you lack the skill " +
            "to read all of the scroll.";
    else
        desc += "letters of the alphabet developed by " +
            "Feanor, mightiest of the Noldor, in Aman. Luckily, " +
            "you are skilled enough to read the scroll.";

    return BSN(desc);
}

public void
init_arg(string arg)
{
    string  foo,
            tmp1,
            tmp2;

    if (!arg || !strlen(arg))
        return;

    sscanf(arg, "%s#BSW#%s##%s", foo, tmp1, tmp2);

    add_prop(BSW_S_SCROLL_OWNER, tmp1);

    if (tmp2 == "0")
        add_prop(OBJ_M_NO_DROP, 0);
    else if (tmp2 == "1")
        add_prop(OBJ_M_NO_DROP, 1);
    else
        add_prop(OBJ_M_NO_DROP, tmp2);
}

public string
query_auto_load()
{
    string  owner = query_prop(BSW_S_SCROLL_OWNER);

    if (al_flag && (owner == ENV(TO)->query_real_name()) &&
	!ENV(TO)->test_bit("Gondor", MORGUL_GROUP, ANGMAR_STANDARD_BIT))
        return MASTER + ":" + "#BSW#" +
                owner + "##" +
                query_prop(OBJ_M_NO_DROP);
    else
        return 0;
}

/*
 * Function name: read_it
 * Description:   Perform the actual read
 */
void
read_it(string str)
{
    int     ls,
            i,
            lack,
            seed;
    mixed   year;
    string  name,
            text,
           *t;

    FIX_EUID

    say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");

    ls = TP->query_skill(SS_LANGUAGE);
    if (stringp(name = query_prop(BSW_S_SCROLL_OWNER)))
    {
        year = (BSW_QUEST_MASTER)->query_random_year("stewards", name);
    }
    else
    {
        ls = MIN(ls, MIN_SKILL);
        year = "####";
    }

    if (ls < MIN_SKILL)
    {
        write(BSN("The scroll is covered by strange signs. You " +
            "think that they might be tengwar, letters of an Elvish " +
            "writing system, but you lack the skill to read them."));
        return;
    }

    text = "\n"+
        "\tTo Valandil,\n"+
        "\tWarden of Emyn Arnen,\n\n" +
        "\tGreetings!\n\n" +
        break_string(
        "The Steward has granted your request to evacuate the two " +
        "farms due to their dangerous position. The families will " +
        "be resettled in Lebennin.\n\n", 65, "    ") +
        break_string(
        "At the same time, the Steward wants you once more to stress "+
        "to the farmers in Ithilien the importance that that land is " +
        "not depopulated. That would be a terrible victory for the " +
        "Enemy! But your difficult situation is of course acknowledged, " +
        "and none in the Steward's council deny the dangers " +
        "threatening our people in Ithilien.\n\n", 65, "    ") +
        break_string(
        "Since evacuation of parts of the Steward's own household " +
        "would be a very bad example, it was decided not to bring " +
        "the heirlooms into the City, even though the Steward is " +
        "much concerned about their safety. To protect them against " +
        "raids, you are ordered to bring them at once into the " +
        "strong-room prepared for them. The Steward expects your " +
        "report that the strong-room has been sealed within one week.\n\n",
        65, "    ") +
        "\tMay the Valar protect us!\n\n" +
        "\tMinas Tirith, New Year's Day, of the year "+year+
        " of the Third Age\n" +
        "\tSigned,\n"+
        "\t\tVardamir, Secretary to the Steward\n\n";

    if (ls < GOOD_SKILL)
    {
        t = explode(text, "");
        seed = TP->query_name()[0];
        lack = ((ls - MIN_SKILL) / 3 + 2);
        for (i = 1; i < sizeof(t); i++)
            if (!random(lack, seed++) &&
                t[i] != " " && t[i] != "\n" && t[i] != "\t")
                t[i] = "#";
        text = implode(t, "");
    }
    write(text);
}

void
set_no_auto_load()
{
    al_flag = 0;
}

string query_recover() { return 0; }
