
/*
 * statue_chamber.c
 *
 * Statue Chamber for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <cmdparse.h>
#include <math.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#include "/d/Genesis/specials/debugger/debugger_tell.h"

string *spirit_elders = ({ });
int candles = 0;

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Statue chamber");
    set_long("This large chamber is known in the temple as the "+
        "statue chamber. Each Elder Member of the Circle has a "+
        "statue constructed here of them. Each time a member is "+
        "promoted to the Elder ranking, a new statue will be constructed "+
        "here. If an Elder member happens to be demoted for whatever "+
        "reason, their statue will crumble. If however a member leaves "+
        "the Circle and they were an Elder member, their statue will "+
        "remain here forever. There @@check_num_elders@@ in this chamber. "+
        "On a small table against the north wall you see some white "+
        "candles. There is a curtain in the south section of the west "+
        "wall and the south section of the east wall.\n");

    add_item(({"statue","statues"}),"@@check_elders@@");
    add_item(({"candle","candles","white candle","white candles"}),
        "@@check_candles@@");
    add_item(({"table","small table","small maple table","maple table"}),
        "The small table is made from maple, and inlaid with quartz and "+
        "marble. Several white candles rest on it, along "+
        "with a brazier with smoldering coals. A cup full of long, dry "+
        "bits of straw is also there, for use when lighting candles.\n");
    add_item(({"curtain","curtains","west curtain","east curtain","walls",
        "wall","west wall","east wall"}),"There are two curtains hanging in "+
        "this room, one in the southern section of the west wall and one "+
        "in the southern section of the east wall. Upon closer examination "+
        "you notice there are chambers beyond them. You could enter the "+
        "curtains if you wanted to travel past them. <enter west curtain> "+
        "<enter east curtain>\n");
    add_item("floor", "The floor is made from the same plain grey stone "+
      "as the walls and ceiling are made from.\n");
    add_item(({"wall","walls"}), "The walls are very plain and made out "+
      "of grey stones placed together.\n");
    add_item("ceiling", "The ceiling is made of the same plain grey stone "+
      "as the walls and floor are made from.\n");
    add_item("stand", "The stand is old, and covered in hardened wax in "+
      "many places. Candles are arranged in rows of intertwining circles, "+
      "allowing their soft light to fill the room.\n");
    add_item("circles", "The circles form the shape of three same-sized, "+
      "perfect circles intertwined, surrounded by one large circle. "+
      "Moonstones are set in the larger circle adorn a plate etched with "+
      "the following:\n\n"+
      " You have noticed that everything a Cleric does is in a circle, and "+
      "that is because the Power of the World always works in circles, and "+
      "everything tries to be round. The sky is round, and I have heard "+
      "that the earth is round like a ball, and so are all the stars. The "+
      "wind, in its greatest power, whirls. Birds make their nests in circles, "+
      "for theirs is the same religion as ours. The sun comes forth and "+
      "goes down again in a circle. The moon does the same, and both are "+
      "round. Even the seasons form a great circle in their changing, and "+
      "always come back again to where they were. The life of a mortal is a "+
      "circle from childhood to childhood, and so it is in everything "+
      "where power moves.\n");
    add_item( ({ "statue of psuchae" }), "The statue of Psuchae depicts a "
        + "shadowy figure. You sense a deep presence within the lifeless "
        + "statue, and you feel a great sense of awe and reverence.\n");
    add_item( ({ "statue of jardeth" }), "The statue of Jardeth depicts "
        + "an ancient white-robed male elf who appears to be holding an "
        + "herb in his hands and sniffing it carefully.\n");
    add_item( ({ "statue of tahla" }), "The statue of Tahla depicts a "
        + "captivating brown-robed female elf who is examining "
        + "some clerical items.\n");
    add_item( ({ "statue of arial" }), "The statue of Arial is of a "
        + "beautiful white-robed female elf who holds a gem up to her eye "
        + "and is carefully examining it.\n");
    add_item( ({ "statue of tiashe" }), "The statue of Tiashe depicts a "
        + "beautiful white-robed female elf smiling warmly. She reaches "
        + "forward in benevolence as if to share the bread in her hands.\n");
        
    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"pool_room","north",0,1);
    add_exit(SPIRIT_TEMPLE+"storage_chamber","west",0,1);
    add_exit(SPIRIT_TEMPLE+"library","east",0,1);
}

int
do_enter(string str)
{
    NF("Enter what? The west curtain or the east curtain perhaps? "+
           "<enter west curtain> <enter east curtain>\n");
    
    if (!str)
        return 0;

    if (str == "west curtain")
    {
        write("You push the western curtain aside and make your way past it "+
            "and into the chamber beyond.\n");
        set_dircmd("west curtain");
        TP->move_living("by pushing the western curtain aside and making "+
            HIS+" way past it and into the chamber beyond",
            SPIRIT_TEMPLE+"refectory");
        return 1;
    }

    if (str == "east curtain")
    {
        write("You push the eastern curtain aside and make your way past it "+
            "and into the chamber beyond.\n");
        set_dircmd("east curtain");
        TP->move_living("by pushing the eastern curtain aside and making "+
            HIS+" way past it and into the chamber beyond",
            SPIRIT_TEMPLE+"startroom");
        return 1;
    }

    return 0;
}

string
check_num_elders()
{
    string str;
    int i;

    i = sizeof(spirit_elders);

    switch(i)
    {
        case 0:
            str = "is one statue";
            break;
        case 1..3:
            str = "are a few statues";
            break;
        case 4..6:
            str = "are several statues";
            break;
        default:
            str = "are many statues";
            break;
    }
    return str;
}

private int
query_is_spirit_npc(string name)
{
    switch (lower_case(name))
    {
    case "jardeth":
    case "arial":
    case "tiashe":
    case "tahla":
        return 1;
    }
    
    return 0;
}

private int
cleanup_elders()
{
    string * spirit_npcs, * spirit_players;
    string nonmetname, desc;
    // Clean up juniors
    spirit_elders = filter(spirit_elders, &not() @ &wildmatch("*jr"));
    spirit_npcs = filter(spirit_elders, query_is_spirit_npc);
    spirit_players = spirit_elders - spirit_npcs;
    foreach (string elder : spirit_players)
    {
        if (!SECURITY->exist_player(elder))
        {
            spirit_elders -= ({ elder });
            continue;
        }
        
        object player_obj;
        int offline = 0;
        if (!objectp(player_obj = find_living(elder)))
        {
            if (!objectp(player_obj = SECURITY->finger_player(elder)))
            {
                // Should never occur.
                send_debug_message("scop_statue", "Was not able to find "
                    + elder + " anywhere.");
                continue;
            }            
            offline = 1;
        }
        // We should have a valid player_obj at this point
        send_debug_message("scop_statue", "Elder " + elder + " is a "
            + player_obj->query_nonmet_name() + ".");
        nonmetname = player_obj->query_nonmet_name();
        remove_item("statue of " + elder);
        switch (NAME_TO_RANDOM(elder, 0, 5))
        {
        case 0:
            desc = "standing piously in prayer.\n";
            break;
        
        case 1:
            desc = "deep in thought.\n";
            break;
        
        case 2:
            desc = "gazing heavenward.\n";
            break;
        
        case 3:
            desc = "with blurred shadowy features.\n";
            break;
        
        case 4:
        default:
            desc = "with arms extended grasping a mandala.\n";
            break;
        }
        
        add_item( ({ "statue of " + elder }), "The statue of "
            + capitalize(elder) + " has been constructed meticulously "
            + "and shows a " + nonmetname + " " + desc);
        if (offline)
        {
            player_obj->remove_object();
        }
    }
}

string
check_elders()
{
    string str;
    int i,j;

    setuid();
    seteuid(getuid());
    restore_object(COUNCIL);
    cleanup_elders();
    
    i = sizeof(spirit_elders);

    if (i == 0)
        str = "There is only one statue: Psuchae.\n";
    
    else if (i == 1)
        str = "There are two statues: Psuchae and "+
            capitalize(spirit_elders[0]) + ".\n";
    
    else
    {
        j = i + 1;
        str = "There are "+LANG_NUM2WORD(j)+" statues: Psuchae, ";
        str += (COMPOSITE_WORDS(map(spirit_elders, capitalize)) + ".\n");
    }
    return str;
}

string
check_candles()
{
    string str;
    str = "The small, round candles are of varying height are displayed "+
          "in a large metal stand. ";
    if (candles == 0)
        str += "There are no candles lit.\n";

    else if (candles == 1)
        str += "There is only one candle lit.\n";

    else
        str += "There are "+LANG_NUM2WORD(candles)+" candles lit.\n";

    return str;
}


int
do_light(string str)
{
    string for_who;
    object who;

    if (!str)
    {
        NF("Light what? A candle for whom?\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[a] 'candle' [for] %s", for_who))
    {
        NF("Light what? A candle for whom?\n");
        return 0;
    }

    who = find_player(lower_case(for_who));

    if (!who)
    {
        write("You light a small white candle and pray for "+
            capitalize(for_who)+".\n");
        say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
            "before it.\n");
        candles += 1;
        return 1;
    }

    if (is_spirit(who))
    {
        write("You light a small white candle and pray for "+
            capitalize(for_who)+".\n");
        say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
            "before it.\n");
        candles += 1;
        tell_object(who,"You feel that "+capitalize(TP->query_real_name())+
            " has lit a candle in your honour and is praying to Psuchae "+
            "for the well being of your soul.\n");
        return 1; 
    }

    if (who->query_wiz_level())
    {
        write("You light a small white candle and pray for "+
            capitalize(for_who)+".\n");
        say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
            "before it.\n");
        candles += 1;
        tell_object(who,"You feel that "+capitalize(TP->query_real_name())+" cares enough for you to "+
            "light a candle in your honour in the mortal realm.\n");
        return 1;
    }

    write("You light a small white candle and pray for "+
        capitalize(for_who)+".\n");
    say(QCTNAME(TP)+" lights a small white candle and prays briefly "+
        "before it.\n");
    tell_object(who,"You feel someone has prayed for you somewhere "+
        "in the realms, to ask Psuchae to help watch over your soul.\n");
    candles += 1;
    return 1;
}

int
do_extinguish(string str)
{
    if (!str)
        return 0;

    write("You do not dare extinguish any of the holy candles.\n");
    say(QCTNAME(TP)+" thinks about extinguishing the candles, but "+
        "decides against it at the last moment.\n");
    return 1;
}

void
reset_room()
{

}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_light,"light");
    add_action(do_extinguish,"extinguish");
    add_action(do_extinguish,"unlight");
}
