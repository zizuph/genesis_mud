
/*
 * entryway.c
 *
 * Entryway for the Spirit Circle of Psuchae Temple
 * To enter the temple, one must <wash myself> in the bath chamber 
 * to the west and <pray at the altar> in the altar chamber to the east.
 * Wizards need not do either of these, but they can if they like.
 *
 * Changed south exit to become a portal to the new Elementalists Temple
 * (the new home for SCoP). - Jaacar, July 2016
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#ifndef TEMPLE_ENTRY_LOG
#define TEMPLE_ENTRY_LOG "spirit_circle/spirit_temple_entry_log"
#endif

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Temple entryway");
    set_long("You are standing in the entryway to a temple. "+
        "This small chamber has four exits, one on each of "+
        "the four main compass points. A large set of solid "+
        "oak double doors lie to the north. To the south lies "+
        "a glowing portal. In the small chamber to the west "+
        "you see a bath while in the chamber to the east "+
        "lies a small altar. On the ceiling above hangs a "+
        "crystal chandelier, giving off plenty of light for "+
        "this entry chamber. The walls are smooth to the touch "+
        "and painted a deep red colour. The floor is made from "+
        "several stone tablets placed symetrically together.\n");

    add_item(({"double doors", "double door","door","doors"}),
        "Which set of double doors do you want to look at? "+
        "The oak double doors or the redwood double doors?\n");
    add_item(({"oak double doors", "oak double door",
        "solid oak double doors","solid oak double door",
        "north double doors","north double door"}), "To "+
        "the north lies a set of solid oak double doors. "+
        "They are closed. Engraved across both doors you "+
        "see an inscription.\n");
    add_item("inscription", "The inscription spread across "+
        "the oak double doors to the north reads:\n\nOnly "+
        "the purified may enter.\n\n");
    add_item(({"redwood double doors", "redwood double door",
        "south double doors","south double door"}), "South "+
        "of you is a set of redwood double doors that lead "+
        "back outside of the temple.\n");
    add_item("chamber", "Which chamber do you want to look "+
        "at? The small chamber to the west or the chamber "+
        "to the east?\n");
    add_item(({"small chamber", "west chamber","bath chamber"}),
        "In the small chamber to the west you see a bath.\n");
    add_item("bath", "Details about the bath are hard to "+
        "see from this room but you can tell it is made "+
        "from white marble.\n");
    add_item(({"east chamber", "altar chamber"}), "To the east "+
        "you see a chamber with a small altar.\n");
    add_item(({"small altar", "altar"}), "Except that the fact "+
        "that the altar is white, you cannot make out any other "+
        "details about it from the entryway.\n");
    add_item(({"ceiling", "crystal chandelier","chandelier"}),
        "The ceiling is painted the same deep red colour as "+
        "the walls are. Hanging from the centre of it is a "+
        "large crystal chandelier. A large light in the centre "+
        "of the chandelier is surrounded by a circular pattern "+
        "of long, thin shards of crystal. The chandelier gives off "+
        "enough light to illuminate this room very brightly.\n");
    add_item(({"wall", "walls","red wall","red walls","deep red wall",
        "deep red walls"}), "The walls are smooth to the touch and "+
        "painted a deep red colour.\n");
    add_item("floor", "The floor is made from several stone tablets "+
        "place symetrically together to form a smooth walking "+
        "surface.\n");
    add_item(({"tablet", "tablets","stone tablet","stone tablets"}),
        "The stone tablets are cut into perfectly square shapes, "+
        "all of them the same size, and placed on the ground to "+
        "form a floor like you would see tile placed. They are "+
        "quite comfortable to walk on.\n");
    add_item("temple", "Rising seamlessly from the bosom of the "+
      "earth, the Temple of the Spirit Circle of Psuche stands "+
      "towering before you.\n");
    add_item(({"portal","glowing portal"}),"The glowing portal "+
        "has replaced the double doors that used to be here. "+
        "Looking into the portal, you see the the new Elementalists "+
        "Temple.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");
    add_prop(ROOM_I_NO_ALLOW_STEED,1);

    add_exit(SPIRIT_TEMPLE+"bath_chamber","west",0,1);
    add_exit(SPIRIT_TEMPLE+"altar_chamber","east",0,1);
//    add_exit("/d/Calia/guilds/elementalists/temple/ec_rack","south",0,1);
    add_exit(SPIRIT_TEMPLE+"entry_path4","south",0,1);
    add_exit(SPIRIT_TEMPLE+"great_hall","north","@@do_enter",1);
}

void
welcome(object who)
{
    string race_title, occ_title, lay_title, full_title;

    if (is_spirit(who))
    {
        race_title = who->query_guild_title_race();
        occ_title = who->query_guild_title_occ();
        lay_title = who->query_guild_title_lay();

        full_title = capitalize(who->query_real_name())+ " ";
        
        if (race_title && race_title != "")
            full_title += race_title+", ";
        
        full_title += occ_title;
            
        if (lay_title && lay_title != "")
            full_title += ", "+lay_title;
        
        tell_object(who,"\n\nThe voice of Psuchae echoes in your mind:  Welcome "+
            "home, "+full_title+".\n\n");
    }
    else
        tell_object(who,"\n\nAn eerie voice echoes in your mind: Welcome.\n\n");
}

int
do_enter()
{
    if (TP->query_wiz_level())
    {
        write("Being a wizard, you do not require purifying and "+
            "therefore you reach forth and open the oak double "+
            "doors before you, and enter the temple. The doors "+
            "close quickly behind you.\n");
        say(QCTNAME(TP)+" reaches forth and opens the oak double doors "+
            "before "+TP->query_objective()+" and enters the temple. The "+
            "doors close quickly behind "+TP->query_objective()+".\n");
        
        // We'll remove these props just in case the wizard actually did
        // wash themself and prayed at the altar. We wouldn't want a wizard
        // full of unnecessary properties running around in the game!
        TP->remove_prop(PRAYED_AT_TEMPLE_ALTAR);  
        TP->remove_prop(BATHED_IN_TEMPLE_BATH);
        if (!is_spirit(TP))
        {
            log_file(TEMPLE_ENTRY_LOG, ctime(time())+" Temple entry by "+ 
                TP->query_name() +".\n",-1);
        }
        set_alarm(1.0,0.0,&welcome(TP));
        return 0;
    }

    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("You hear a voice booming from above:\n"+
            "The Soulless may not enter here!\n");
        log_file(TEMPLE_ENTRY_LOG, ctime(time())+" "+TP->query_name() +
            " attempted to enter the Temple.\n",-1);
        return 1;
    }

    if (COUNCIL_CODE->is_temple_banned(TP->query_real_name()))
    {
        write("You hear a voice booming from above:\n"+
            "You have been banned from entering this holy place. GO!\n");
        log_file(TEMPLE_ENTRY_LOG, ctime(time())+" "+TP->query_name() +
            " attempted to enter the Temple.\n",-1);
        return 1;
    }

    if (!(TP->query_prop(BATHED_IN_TEMPLE_BATH)))
    {
        write("\nYou hear a voice booming from above:\n"+
           "Only the purified may enter!\n\n");
        say(QCTNAME(TP)+" attempts to enter the temple, but "+
            "as "+TP->query_pronoun()+" reaches for the door a "+
            "voice booms out from above saying:\nOnly the "+
            "purified may enter!\n\n");
        return 1;
    }

    if (!(TP->query_prop(PRAYED_AT_TEMPLE_ALTAR)))
    {
        write("\nYou hear a voice booming from above:\n"+
           "Only the purified may enter!\n\n");
        say(QCTNAME(TP)+" attempts to enter the temple, but "+
            "as "+TP->query_pronoun()+" reaches for the door a "+
            "voice booms out from above saying:\nOnly the "+
            "purified may enter!\n\n");
        return 1;
    }

    write("You reach forth and open the oak double doors before "+
        "you, entering the temple. The doors close quickly behind "+
        "you.\n");
    say(QCTNAME(TP)+" reaches forth and opens the oak double doors "+
        "before "+TP->query_objective()+" and enters the temple. The "+
        "doors close quickly behind "+TP->query_objective()+".\n");
    TP->remove_prop(PRAYED_AT_TEMPLE_ALTAR);
    TP->remove_prop(BATHED_IN_TEMPLE_BATH);
    if (!is_spirit(TP))
    {
        log_file(TEMPLE_ENTRY_LOG, ctime(time())+" Temple entry by "+ 
            TP->query_name() +".\n",-1);
    }
    set_alarm(1.0,0.0,&welcome(TP));
    return 0;
}

int
do_read(string str)
{
    if (!str)
    {
        NF("Read what? The inscription? <read inscription>\n");
        return 0;
    }

    if (str != "inscription")
    {
        NF("Read what? The inscription? <read inscription>\n");
        return 0;
    }

    write("The inscription spread across the oak double doors "+
        "to the north reads:\n\nOnly the purified may enter.\n\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read,"read");
}
