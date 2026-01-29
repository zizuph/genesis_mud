

#pragma save_binary

inherit "/std/room";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include "defs.h"
#include WORSHIP_HEADER

void set_up_skills();
#include "medskills.h"

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

string
long_desc()
{
    string ret;

    switch(TP->query_prop("worship_meditate"))
    {
        case "air":
            ret = "You are standing atop a windy cliff. Strong "+
                "gusts almost blow you right off of it, which would "+
                "almost certainly result in death. Looking down "+
                "over the cliff you notice that you cannot see the "+
                "bottom.\n";
            break;
        case "fire":
            ret = "You are standing in the middle of a scorching "+
                "hot desert. The heat from the blazing sun is "+
                "almost unbearable to you. You see nothing but "+
                "sand and sand dunes all around you.\n";
            break;
        case "water":
            ret = "You seem to be immersed deeply in a "+
                "clear body of water, yet to your amazement "+
                "you can still breathe. The water is exactly "+
                "the same temperature as your body making it "+
                "very relaxing and comfortable to stand in.\n";
            break;
        case "earth":
            ret = "You are standing in a large cave. There is "+
                "barely enough light to see the walls close at "+
                "hand around you. Feeling the walls, you "+
                "sense there are no exits around you whatsoever.\n";
            break;
        default: 
            ret = "You have entered the focus chamber of the "+
                "temple. A single white candle inside of a "+
                "candle box provides a dim soft glow for the "+
                "entire room. Here in the centre of the room you "+
                "see a single silver altar, much like the one "+
                "in the main chamber. The walls are a pale "+
                "white colour and appear to be solid blocks of "+
                "stone. The ground is covered in soft, evenly "+
                "cut green grass. There is a small archway in the "+
                "north wall heading back out to the bed chamber, "+
                "and an exit leading southwards.\n";
           break;
    }
    return ret;
}

int
vis_exit()
{
    return stringp(TP->query_prop("worship_meditate"));
}

int
block_exit()
{
    if (stringp(TP->query_prop("worship_meditate")))
    {
        write("You do not see any exits.\n");
        return 1;
    }

    return 0;
}

void
create_room()
{
    set_short("The focus and contemplation chamber");
    set_long("@@long_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_S_WIZINFO, 
        "The trainroom has some special commands which may require " +
        "explanation for wizards. Just to be different, players " +
        "do not 'improve' or 'learn' here. These commands are " +
        "available for wizards to use as usual, however. " +
        "Players must use the contemplate, pray, and focus " +
        "commands. Contemplate may be used to list the available " +
        "skills (the different elemental forms here). Players " +
        "actually learn and improve by praying to one of four " +
        "Elementals, which will lock them onto that element. Then " +
        "while praying, they use 'focus <num>' to learn/improve " +
        "the skill in that element. Rising again will return " +
        "then from the prayer lock. Note that the long desc is " +
        "VBFC'd to change depending on what they're praying to, " +
        "if players think they've been transed somehow. NOTE: " +
        "the focus and contemplate commands use tp->command " +
        "in places, therefore will fail when a wizard attempts to " +
        "use them. This is why improve and learn remain available " +
        "for wizards to satisfy their curiousity.\n");
    add_prop(ROOM_I_IS,1);

    add_item(({"candle","box"}),"It is a small white candle inside of "+
        "a candle box. The light from the candle bathes the room with "+
        "a soft white glow.\n");

    add_item("altar","A small silver altar rests in the middle of this "+
        "chamber. You feel a strong urge to pray to one of the Elementals "+
        "just by looking at it.\n");

    add_item(({"walls","wall","stone","stones","block","blocks"}),
        "The walls are made from large blocks of perfect, evenly "+
        "cut pieces of pale white coloured stones.\n");

    add_item(({"grass","ground"}),"The entire ground of this chamber "+
        "is covered by a soft green grass.\n");

    add_item("archway","The archway is carved into the north wall, and "+
        "leads back into the bed chamber.\n");

    create_skill_raise();
    set_up_skills();
    add_exit(WOR_TEMPLE + "startroom", "north", "@@block_exit", 1, "@@vis_exit");
    add_exit(WOR_TEMPLE + "estiroom","south","@@block_exit",1,"@@vis_exit");
}

void
init()
{
    ::init();
    init_skill_raise();
    add_action("focus", "focus");
    add_action("contemplate", "contemplate");
    add_action("try_improve", "improve");
    add_action("try_improve", "learn");
    add_action("pray","pray");
    add_action("arise","arise");
    add_action("all_cmd", "", 1);
}

int
try_improve(string str)
{
    if (MASTER == file_name(previous_object()) && !TP->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }
    return sk_improve(str);
}

int
focus(string str)
{
    string skill,
           temp;
    mapping misc = (["fire":  SS_ELEMENT_FIRE,
                     "water": SS_ELEMENT_WATER,
                     "air":   SS_ELEMENT_AIR,
                     "earth": SS_ELEMENT_EARTH]);

    if (str && strlen(str))
    {
        if (sizeof(explode(str, " ")) > 1)
        {
            NF("Focus how many times?\n");
            return 0;
        }
    }
    
    temp = TP->query_prop("worship_meditate"); 
    skill = temp + " spells";
    if (str)
        skill += " " + str;
    
    if (!TP->query_skill(misc[temp]))
        skill = "learn " + skill;
    else
        skill = "improve " + skill;

    TP->command(skill);
    return 1;
}

int
contemplate(string str)
{
    if (!str || !strlen(str))
    {
        TP->command("improve -1");
        return 1;
    }

    if (sizeof(explode(str, " ")) > 1)
    {
        NF("Contemplate how far?\n");
        return 0;
    }

    TP->command("improve " + str);
    return 1;
}

int
arise()
{
    write("You suddenly find yourself back in the focus chamber.\n");
    TP->remove_prop("worship_meditate");
    return 1;
}


int
pray(string str)
{
    if (!is_worship(TP))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }
    if (str == "to Aeria")
    {
        write("You suddenly find yourself elsewhere...\n");
        write("You feel that if you were to arise, that you "+
            "would return to where you came from.\n");
        TP->add_prop("worship_meditate","air");
        return 1;
    }
    if (str == "to Gu")
    {
        write("You suddenly find yourself elsewhere...\n");
        write("You feel that if you were to arise, that you "+
            "would return to where you came from.\n");
        TP->add_prop("worship_meditate","earth");
        return 1;
    }
    if (str == "to Diabrecho")
    {
        write("You suddenly find yourself elsewhere...\n");
        write("You feel that if you were to arise, that you "+
            "would return to where you came from.\n");
        TP->add_prop("worship_meditate","water");
        return 1;
    }
    if (str == "to Pyros")
    {
        write("You suddenly find yourself elsewhere...\n");
        write("You feel that if you were to arise, that you "+
            "would return to where you came from.\n");
        TP->add_prop("worship_meditate","fire");
        return 1;
    }
    write("Pray to whom?\n");
    return 1;
}

int
all_cmd(string str)
{
    if (TP->query_wiz_level())
        return 0;

    if (!stringp(TP->query_prop("worship_meditate")))
    {
        if (query_verb() == "focus" ||
            query_verb() == "arise")
        {
            write("What?\n");
            return 1;
        }
        else
            return 0;
    }

    switch (query_verb())
    {
        case "l":
        case "look":
            if (strlen(str) &&
                explode(str, " ")[0] == "at")
                {
                    write("Your eyes refuse to focus.\n");
                    return 1;
                    break;
                }
        case "arise":
        case "focus":
        case "learn":
        case "improve":
        case "say":
        case "'":
            return 0;
            break;
    }

    write("You feel it would be wrong to do that here.\n");
    return 1;
}

int
sk_hook_cant_train(string skill, int to_lev)
{
    NF("You fail to focus properly and do not understand what has been taught to you.\n");
    return 0;
}

public int
sk_improve(string sk)
{
    if (TP->query_skill(SS_PUNISHMENT) == 2)
    {
        write("You have been banned from training by the council!\n");
        return 1;
    }
    return ::sk_improve(sk);
}
