/*
 * /d/Gondor/guilds/rangers/obj/raise.c
 * 
 * Coded by Gwyneth
 *
 * For testing purposes. Sets the skills of a player to newbie,
 * AG level, apprentice, north or ithilien.
 */
inherit "/std/object";

#include <cmdparse.h>
#include <ss_types.h>
#include "../rangers.h"
#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("raiser");
    set_short("skill raiser");
    set_long("This sets all of the skills of a character to a certain " +
        "level. For newbie and ag, brawling and hearing skills are removed. " +
        "For newbie, all ag skills are removed, leaving only special skills " +
        "such as the spell skill, reward skill, etc. Use: 'raise <name> " +
        "newbie/ag/apprentice/north/ithilien'.\n");
}

int
raise(string str)
{
    mixed *oblist;
    int i, *list;
    string which;

    if (!parse_command(str, all_inventory(ENV(TP)), "%l %w", oblist, which) ||
      !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        dump_array(oblist);
        notify_fail("Failed.\n");
        return 0;
    }

    switch(lower_case(which))
    {
    case "newbie":
        list = m_indexes(SS_SKILL_DESC);
        for (i = 0; i < sizeof(list); i++)
            oblist[0]->remove_skill(list[i]);

        oblist[0]->remove_skill(SS_BRAWLING);
        oblist[0]->remove_skill(SS_HEARING);
        write(oblist[0]->skill_living());
        break;

    case "ag":
        list = m_indexes(SS_SKILL_DESC);
        for (i = 0; i < sizeof(list); i++)
            oblist[0]->set_skill(list[i], SS_SKILL_DESC[list[i]][4]);

        oblist[0]->remove_skill(SS_BRAWLING);
        oblist[0]->remove_skill(SS_HEARING);
        write(oblist[0]->skill_living());
        break;

    case "apprentice":
        for (i = 0; i < sizeof(SKILLS); i++)
            oblist[0]->set_skill(SKILLS[i], APPRENTICE_SKILLS[i]);

        write(oblist[0]->skill_living());
        break;

    case "north":
        for (i = 0; i < sizeof(SKILLS); i++)
            oblist[0]->set_skill(SKILLS[i], NORTH_SKILLS[i]);

        write(oblist[0]->skill_living());
        break;

    case "ithilien":
        for (i = 0; i < sizeof(SKILLS); i++)
            oblist[0]->set_skill(SKILLS[i], ITHILIEN_SKILLS[i]);

        write(oblist[0]->skill_living());
        break;

    default:
        break;
    }

    write("Success.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(raise, "raise");
}
