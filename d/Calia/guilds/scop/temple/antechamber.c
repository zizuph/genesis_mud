
/*
 * antechamber.c
 *
 * Antechamber for the Spirit Circle of Psuchae Temple
 * Only members of the guild may pass through the archway
 * to the private board room beyond (or wizards).
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */

/* Navarre September 18th 2006, Added Wizard allowance to enter archway. */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <time.h>

#include "defs.h"
#include SPIRIT_HEADER

int ceremony_status = 0;
string rmonth = "";

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Antechamber");
    set_long("This is the antechamber of the temple. All of the "+
        "people that move through this temple will eventually have "+
        "to enter here, the central point. There is a hallway leading "+
        "off deeper into the temple to the north. An open black door "+
        "lies in the eastern wall, while to the south you see a golden "+
        "archway leading to the board room as well as a doorway leading "+
        "to a smaller chamber. Next to the doorway, hanging on the wall, "+
        "is a spectacular tapestry. In the middle of this chamber is a "+
        "large brass gong.\n");

    add_item("doorway","The doorway seems to lead to another chamber "+
        "south from here. Beside the doorway you notice a spectacular "+
        "tapestry.\n");
    add_item(({"beater", "padded beater"}), "The padded beater is a "+
        "pole with a padded bag on one end. You are supposed to hit "+
        "the gong with the padded end.\n");
    add_item(({"gong","brass gong","large gong","large brass gong"}),
        "In the middle of the room is a large brass gong. Next to the "+
        "gong is a padded beater to ring the gong with.\n");
    add_item(({"archway","golden archway"}),"The golden archway "+
        "in the southern wall leads off to the board room beyond "+
        "it. You could try to enter the archway if you wanted to "+
        "pass through it.\n");
    add_item(({"door","black door","open door","open black door",
        "eastern door","east door"}),"There is an open black door "+
        "set into the eastern wall. Through the door you see a "+
        "larger chamber than this one.\n");
    add_item(({"calendar","tapestry","spectacular tapestry"}),"@@calendar@@.\n");
    add_item("floor", "You are standing on a very large stone floor. It "+
      "appears to be constructed from very large stone slabs placed in "+
      "a rectangular pattern.\n");
    add_item(({"wall", "walls"}), "The walls are very plain and made "+
      "out of grey stones placed together.\n");
    add_item("ceiling", "The ceiling is made of the same plain grey "+
      "stone as the walls and floor are made from.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"hallway","north",0,1);
    add_exit(SPIRIT_TEMPLE+"post_office","south",0,1);
    add_exit(SPIRIT_TEMPLE+"chapel","west","@@check_ceremony@@",1);
    add_exit(SPIRIT_TEMPLE+"great_hall","east",0,1);
    TO->calendar();
}

string
calendar()
{
    int real_time, real_day;
    string day, month, image;

    real_time = time();
    
    day = TIME2FORMAT(real_time,"d");
    real_day = atoi(day);

    month = TIME2FORMAT(real_time,"mmm");

    image = "This finely woven tapestry is a myriad of colours "+
        "and shapes. Focusing your energies upon the cloth, you are "+
        "granted a vision ";

    switch (month)
    {
        case "Jan":
            rmonth = "Moon of Frost On the Temple";
            image += "of the Holy Temple of Psuchae surrounded by the "+
                "dark forest. All things are covered with a gentle white "+
                "frost, glowing in the full moon above them.";
            break;
        case "Feb":
            rmonth = "Moon of the Dark Red Calves";
            image += "of a farmer kneeling in waning moonlight as a coming "+
                "dawn welcomes the birth of a calf, and the joy of new life.";
            break;
        case "Mar":
            rmonth = "Moon of the Snowblind";
            image += "of a full moon piercing the clouded night sky, its "+
                "light glinting off flakes of heavily falling snow, marking "+
                "the final fury of the season. You can barely make out a "+
                "conclave of pilgrims huddled in prayer in the midst of "+
                "five stone obelisks.";
            break;
        case "Apr":
            rmonth = "Moon of the Grass Appearing";
            image += "of small strands of grass just breaking the surface "+
                "of the ground, reaching up to touch the moon far above "+
                "them.";
            break;
        case "May":
            rmonth = "Moon When the Ponies Shed";
            image += "of dapple-grey pony, grazing contentedly among dogwood "+
                "trees. Strands of silvery hair are caught among the pink "+
                "blooms of the branches, and shine softly in the moonlight.";
            break;
        case "Jun":
            rmonth = "Moon of the Dancing Satyrs";
            image += "of pagan satyrs, dancing in celebration of the "+
                "solstice. They hold large bowls raised above their heads "+
                "in a gesture of celebration in the afternoon sun, even as "+
                "the new moon rises behind them.";
            break;
        case "Jul":
            rmonth = "Moon When the Cherries are Ripe";
            image += "of a small bird carrying a dark red fruit in its "+
                "beak as it flies near a babbling stream. The water appears "+
                "to glow as moonlight dances across its surface.";
            break;
        case "Aug":
            rmonth = "Moon of Golden Grasses";
            image += "of a lone cottage in a field of tall grasses, heavily "+
                "laden with grains. The scene is bathed in the firey glow of "+
                "a golden harvest moon.";
            break;
        case "Sep":
            rmonth = "Moon of the Changing Seasons";
            image += "of fishermen mending their nets and preparing their "+
                "boats to stand against the storms of winter seas. You can "+
                "just make out a tattoo on one of the sailors of a moon "+
                "enshrouded in thunderclouds.";
            break;
        case "Oct":
            rmonth = "Moon of the Olive Harvest";
            image += "of several ceramic amphorae stacked against a "+
                "crumbling brick wall. Each cask is filled with fresh "+
                "olive oil, and is stamped with the symbol of the olive "+
                "grower, a full moon flanked by five stars.";
            break;
        case "Nov":
            rmonth = "Moon of the Falling Leaves";
            image += "of yellow and golden brown leaves falling to the "+
                "ground illuminated by the moon shining high above them.";
            break;
        default:
            rmonth = "Moon of the Popping Trees";
            image += "of a stark landscape thickly populated with leafless "+
                "trees. Shadows cast by a young moon dramatically emphasize "+
                "the movement of the branches as they snap in the bitter "+
                "winter winds.";
            break;
    }
     
    return image+" Delicately embroidered along the bottom of the "+
        "tapestry are celestial symbols indicating that it is the "+
        LANG_ORD2WORD(real_day)+" day of the "+rmonth; 
}

string
query_rmonth()
{
    return rmonth;
}

void
set_ceremony(int i)
{
    ceremony_status = i;
}

int
check_ceremony()
{
    if (ceremony_status)
    {
        if (!is_spirit(TP))
        {
            write("The chapel is closed at the moment as there is a "+
                "ceremony taking place. Please come back later.\n");
            return 1;
        }
        else
        {
            write("\n\nThere is a ceremony taking place right now. You are "+
                "permitted to enter but please be quiet.\n\n");
            return 0;
        }
    }

    return 0;
}

int
do_enter(string str)
{
    if (!str)
    {
        NF("Enter what? The archway? <enter archway>\n");
        return 0;
    }

    if (str != "archway")
    {
        NF("Enter what? The archway? <enter archway>\n");
        return 0;
    }

    if (is_spirit(TP) || TP->query_wiz_level())
    {
        write("You pass under the golden archway and into the sanctuary "+
            "beyond.\n");
        say(QCTNAME(TP)+" passes under the golden archway and into the "+
            "sanctuary beyond.\n");
        set_dircmd("archway");
        TP->move_living("M",SPIRIT_TEMPLE+"board_room");
        tell_room(environment(TP),QCTNAME(TP)+" enters the sanctuary through "+
                  "the golden archway to the north.\n",TP);
        return 1;
    }

    write("Some magical force is blocking your entrance to the "+
        "board room.\n");
    say(QCTNAME(TP)+" attempts to enter the sanctuary but is "+
        "blocked by some magical force.\n");
    return 1;
}

int
do_ring(string str)
{
    if (!str)
    {
        NF("Ring what? The gong? <ring gong>\n");
        return 0;
    }

    if (str != "gong")
    {   
        if (str != "brass gong")
        {
            NF("Ring what? The gong? <ring gong>\n");
            return 0;
        }
    }

    write("You pick up the beater and hit the gong with the "+
        "padded end.\n");
    say(QCTNAME(TP)+" picks up the beater and hits the gong with "+
        "the padded end.\n");
    if (is_spirit(TP))
    {
        write("The gong rings loudly and echoes throughout the "+
            "entire chamber, perhaps even beyond!\n");
        say("The gong rings loudly and echoes throughout the entire "+
            "chamber, perhaps even beyond!\n");
        tell_room(SPIRIT_TEMPLE+"chapel","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"meeting_room","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"councilroom","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"board_room","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"post_office","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"hallway","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"startroom","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"great_hall","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"ritual_chamber","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        tell_room(SPIRIT_TEMPLE+"divination_chamber","You hear the gong from the "+
            "antechamber ringing loudly.\n");
        return 1;
    }

    write("The gong rings loudly throughout the chamber.\n");
    say("The gong rings loudly throughout the chamber.\n");
    tell_room(SPIRIT_TEMPLE+"chapel","You hear the gong from the "+
              "antechamber ringing.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_ring,"ring");
}
