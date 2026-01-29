/*
 * outer_arch.c
 *
 * This is the entrance into the black tower area.
 * Two gargoyles guard the entrance, and will attack
 * anyone trying to enter, unless someone is holding
 * them in check with an artifact that can be found
 * on the shipwreck southwest of the tower.
 * 
 * Khail - July 7/97
 */
#pragma strict_types

#include <macros.h>
#include <cmdparse.h>
#include "grounds.h"
#include "/d/Khalakhor/sys/defs.h"

inherit STDGROUNDS;

object *gargoyles;

public void
reset_room()
{
    object ob;
    int i;

    for (i = 0; i < sizeof(gargoyles); i++)
    {
        if (!gargoyles[i])
        {
            ob = clone_object(NPC + "gargoyle");
            ob->move(TO);
            tell_room(TO, "A statue of a gargoyle shimmers " +
                "into view atop the archway.\n");
            gargoyles[i] = ob;
        }
    }
}
 
public string
gargoyles_present()
{
    object *temp;

    temp = filter(gargoyles, objectp);

    if (!sizeof(temp))
        return "";
    if (sizeof(temp) == 1)
        return "A statue of a lone gargoyle crouches " +
            "atop the archway.";
    return "A pair of gargoyle statues crouch atop " +
        "the archway.";
}

public int
gargoyles_react()
{
    object *temp,
           *players,
           has_stone,
           stone;
    int i;

    temp = filter(gargoyles, objectp);
    players = filter(all_inventory(), interactive);

    if (!sizeof(temp))
        return 0;

    for (i = 0; i < sizeof(players); i++)
    {
        if (stone = present(ANTI_GARGOYLE_OBJECT_NAME, players[i]))
        {
            has_stone = players[i];
            break;
        }
    }

    if (!has_stone)
    {
        temp->animate_gargoyle();
        temp->command("$kill " + OB_NAME(TP));
        return 1;
    }

    if (sizeof(temp) == 1)
    {
        tell_room(TO, "The gargoyle statue shivers slightly, " +
            "but a web of light springs from the " +
            stone->short() + " held by " + QTNAME(has_stone) +
            " and surrounds the statue. The shivering ceases " +
            "immediately.\n", ({has_stone}));
        tell_object(has_stone, "The gargoyle statue shivers " +
            "slightly, but a web of light springs from your " +
            stone->short() + " and surrounds the statue. The " +
            "shivering ceases immediately.\n");
    }
    else
    {
        tell_room(TO, "The gargoyle statues shiver slightly, " +
            "but a web of light springs from the " +
            stone->short() + " held by " + QTNAME(has_stone) +
            " and surrounds the statues. The shivering ceases " +
            "immediately.\n", ({has_stone}));
        tell_object(has_stone, "The gargoyle statues shiver " +
            "slightly, but a web of light springs from your " +
            stone->short() + " and surrounds the statues. " +
            "The shivering ceases immediately.\n");
    }
    return 0;
}

public void
create_khalakhor_room()
{
    set_short("outside an ancient archway");
    set_long("You stand on the outside of an ancient " +
        "stone archway that leads into the grounds " +
        "of an old tower. Both sides of the archway " +
        "are flanked by natural embankments of stoney " +
        "earth which are hopelessly tangled in brambles " +
        "and thistles. " + VBFC_ME("gargoyles_present") +
        "\n");

    add_exit(PATH + "road/road_end", "east");
    add_exit(GROUNDS + "inner_arch", "west",
        VBFC_ME("gargoyles_react"));

    gargoyles = allocate(2);
    reset_room();
}