/*
 * divination_chamber.c
 *
 * Divination chamber for the Spirit Circle of Psuchae Temple
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
#include <ss_types.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

void
create_room()
{
    set_short("Divination chamber");
    set_long("You have entered a strangely shaped chamber. "+
        "There is a large rectangular portion heading north "+
        "south then on the far eastern side it looks as though "+
        "someone has attached half of a circle to it, curved "+
        "outwards towards the east. This chamber is darker than "+
        "most others, likely because the walls here are painted "+
        "a very dark brown and there appear to be no lamps of any "+
        "kind. The only light that enters this room is through the "+
        "two windows in the half circle section on the eastern side "+
        "of the room. On the floor you see three different circles.\n");

    add_item("floor", "The floor is made of stone and is painted the "+
        "same very dark brown colour as both the walls and the ceiling. "+
        "Painted on the floor are three circles.\n");
    add_item(({"roof", "ceiling"}), "The ceiling is painted the same "+
        "very dark brown colour as the walls and floor.\n");
    add_item(({"wall", "walls"}), "The walls of this chamber are "+
        "painted a very dark brown colour and are fairly rough to the "+
        "touch. It is almost like they are unfinished or raw stone "+
        "that has been painted.\n");
    add_item("light","The only light to enter this room is from the "+
        "two windows set into the half circle section on the eastern "+
        "side of the room.\n");
    add_item(({"window", "windows","two windows"}),"There are two tall "+
        "windows set into the half circle shaped section in the eastern "+
        "portion of this chamber. Through these windows shines the only "+
        "light in the entire chamber.\n");
    add_item(({"circle section","half circle section"}),"The eastern "+
        "portion of this chamber is shaped like half of a circle and "+
        "looks as though it was attached to the rectangular portion of "+
        "the chamber.\n");
    add_item(({"circle","circles"}),"These circles are meant for members "+
        "to enter and divine for their gifts from Psuchae. Each level of "+
        "membership has their own circle. Which circle would you like to "+
        "look at? The apprentice circle, the master circle, or the elder "+
        "circle?\n");
    add_item("apprentice circle","The circle of Apprentices is meant for the "+
        "Apprentices of the Spirit Circle. It is a white circle drawn on "+
        "the ground in the northern section of the chamber. If you are an "+
        "apprentice member, you may enter the apprentice circle to divine "+
        "for your gifts from Psuchae.\n");
    add_item("master circle","The circle of Masters is meant for the Master "+
        "clerics of the Spirit Circle. It is a silver circle drawn on the "+
        "ground in the southern section of the chamber. If you are a Master "+
        "cleric, you may enter the master circle to divine for your gifts "+
        "from Psuchae.\n");
    add_item("elder circle","The circle of Elders is meant for the Elders "+
        "of the Spirit Circle. It is a golden circle drawn on the ground in "+
        "the eastern section of the chamber. If you are an Elder member, "+
        "you may enter the elder circle to divine for your gifts "+
        "from Psuchae.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"great_hall","west","@@check_circle",1);
}

int
check_circle()
{
    if (TP->query_prop(ENTERED_TEMPLE_CIRCLE))
    {
        write("You must leave the circle before you can leave. "+
            "<leave circle>\n");
        return 1;
    }

    return 0;
}

int
do_enter(string str)
{
    if (!str)
    {
        NF("Enter what? One of the circles? <enter first circle>, "+
           "<enter second circle>, or <enter third circle>?\n");
        return 0;
    }

    if (TP->query_prop(ENTERED_TEMPLE_CIRCLE))
    {
        write("You are already in the "+TP->query_prop(ENTERED_TEMPLE_CIRCLE)+
            " circle! If you want to enter another circle, please leave that "+
            "one first. <leave circle>\n");
        return 1;
    }

    if (str == "first circle")
    {
        write("You enter the Circle of Apprentices. You may <leave circle> "+
            "when you are ready.\n");
        say(QCTNAME(TP)+" enters the Circle of Apprentices.\n");
        TP->add_prop(ENTERED_TEMPLE_CIRCLE,"Apprentice");
        return 1;
    }

    if (str == "apprentice circle")
    {
        write("You enter the Circle of Apprentices. You may <leave circle> "+
            "when you are ready.\n");
        say(QCTNAME(TP)+" enters the Circle of Apprentices.\n");
        TP->add_prop(ENTERED_TEMPLE_CIRCLE,"Apprentice");
        return 1;
    }

    if (str == "second circle" && TP->query_spirit_circle_level() > 3)
    {
        write("You enter the Circle of Masters. You may <leave circle> "+
            "when you are ready.\n");
        say(QCTNAME(TP)+" enters the Circle of Masters.\n");
        TP->add_prop(ENTERED_TEMPLE_CIRCLE,"Master");
        return 1;
    }

    if (str == "master circle" && TP->query_spirit_circle_level() > 3)
    {
        write("You enter the Master circle. You may <leave circle> "+
            "when you are ready.\n");
        say(QCTNAME(TP)+" enters the Master circle.\n");
        TP->add_prop(ENTERED_TEMPLE_CIRCLE,"Master");
        return 1;
    }

    if (str == "second circle" && TP->query_spirit_circle_level() < 4)
    {
        write("You are not of Master ranking, therefore you cannot "+
            "enter the Circle of Masters.\n");
        return 1;
    }

    if (str == "master circle" && TP->query_spirit_circle_level() < 4)
    {
        write("You are not of Master ranking, therefore you cannot "+
            "enter the Circle of Masters.\n");
        return 1;
    }

    if (str == "third circle" && TP->query_spirit_circle_level() > 7)
    {
        write("You enter the Circle of Elders. You may <leave circle> "+
            "when you are ready.\n");
        say(QCTNAME(TP)+" enters the Circle of Elders.\n");
        TP->add_prop(ENTERED_TEMPLE_CIRCLE,"Elder");
        return 1;
    }

    if (str == "elder circle" && TP->query_spirit_circle_level() > 7)
    {
        write("You enter the Circle of Elders. You may <leave circle> "+
            "when you are ready.\n");
        say(QCTNAME(TP)+" enters the Circle of Elders.\n");
        TP->add_prop(ENTERED_TEMPLE_CIRCLE,"Elder");
        return 1;
    }

    if (str == "third circle" && TP->query_spirit_circle_level() < 8)
    {
        write("You are not of Elder ranking, therefore you cannot "+
            "enter the Circle of Elders.\n");
        return 1;
    }

    if (str == "elder circle" && TP->query_spirit_circle_level() < 8)
    {
        write("You are not of Elder ranking, therefore you cannot "+
            "enter the Circle of Elders.\n");
        return 1;
    }

    NF("Enter what? One of the circles? <enter apprentice circle>, "+
           "<enter master circle>, or <enter elder circle>?\n");
    return 0;
}

int
do_divine(string str)
{
    object apprentice, master, elder, *excess;

    if (!str)
    {
        NF("Divine what? For gifts? <divine for gifts>\n");
        return 0;
    }

    /* Are they already in a circle? */
    if (!(TP->query_prop(ENTERED_TEMPLE_CIRCLE)))
    {
        NF("You must enter a circle before you can divine for your gifts.\n");
        return 0;
    }

    if (str != "for gifts")
    {
        NF("Divine what? For gifts? <divine for gifts>\n");
        return 0;
    }

    write("You divine for your gifts from the "+
          TP->query_prop(ENTERED_TEMPLE_CIRCLE)+" circle.\n");
    say(QCTNAME(TP)+" kneels down to pray briefly.\n");
    
    /* Are they in the Apprentice circle? */
    if ((TP->query_prop(ENTERED_TEMPLE_CIRCLE)) == "Apprentice")
    {
        excess = filter(all_inventory(TP), 
            &operator(==)("_spirit_apprentice_spells_") @ &->query_name());
        excess->remove_object();

        /* They don't have it, are they a member? */
        if (!apprentice && IS_MEMBER(TP))
        {
            /* They don't have it and ARE members, give it to them */
            apprentice=clone_object(SPIRIT_OBJECTS+"apprentice_spells");
            apprentice->move(TP, 1);
        }

        /* They don't have it still, probably not a member */
        if (!apprentice && !(IS_MEMBER(TP)))
        {
            /* Indeed they are not members, tell them so, and get them out */
            write("\nYou cannot divine for gifts as you are not a member "+
               "of the Circle! In fact, you shouldn't be in here!\n");
            write("Now get out! You feel yourself being thrown through the "+
               "double doors and back out into the great hall, landing "+
               "hard on the floor.\n\n");
            say(QCTNAME(TP)+" is ejected from the divination chamber!\n");
            TP->remove_prop(ENTERED_TEMPLE_CIRCLE);
            TP->move_living("M",SPIRIT_TEMPLE+"great_hall",1);
            say(QCTNAME(TP)+" comes flying out of the eastern double "+
                "doors, landing hard on the floor.\n");
            NF("\n");
            return 0;
        }

        /* They have their apprentice spells object */
        if (apprentice)
        {
            /* Add the first level spells */
            apprentice->update_first_spells();

        /* Check their chosen count, make sure it has the first level flag */
            if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_ONE_FLAG))
            {
                /* They didn't have first level flag, set it and reset tax */
                TP->set_skill(SS_SPIRIT_CHOSEN,
                    (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_ONE_FLAG));
                TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
            }
            
            /* Are they second level? */
            if (TP->query_spirit_circle_level() >=2)
            {
                /* Add the second level spells */
                apprentice->update_second_spells();

        /* Check their chosen count, make sure it has the second level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_TWO_FLAG))
                {
                /* They didn't have second level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_TWO_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }

            /* Are they third level? */
            if (TP->query_spirit_circle_level() >= 3)
            {
                apprentice->update_third_spells();
        /* Check their chosen count, make sure it has the third level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_THREE_FLAG))
                {
                /* They didn't have third level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_THREE_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }
        }   
    }   /* End of Apprentice circle stuff */


    /* Are they in the Master circle? */
    if ((TP->query_prop(ENTERED_TEMPLE_CIRCLE)) == "Master")
    {
    
        excess = filter(all_inventory(TP), 
            &operator(==)("_spirit_master_spells_") @ &->query_name());
        excess->remove_object();   
         
        /* They don't have it, are they a member and high enough level? */
        if (!master && IS_MEMBER(TP))
        {
            /* They don't have it and ARE members, give it to them */
            master=clone_object(SPIRIT_OBJECTS+"master_spells");
            master->move(TP, 1);
        }

        /* If they don't have it, are members, and too low of a level */
        if (!master && IS_MEMBER(TP))
        {
            NF("You are not in the Master ranking, therefore cannot divine "+
               "for the Master ranking gifts.\n");
            TP->command("leave circle");
            return 0;
        }

        /* They don't have it still, probably not a member */
        if (!master && !(IS_MEMBER(TP)))
        {
            /* Indeed they are not members, tell them so, and get them out */
            write("\nYou cannot divine for gifts as you are not a member "+
               "of the Circle! In fact, you shouldn't be in here!\n");
            write("Now get out! You feel yourself being thrown through the "+
               "double doors and back out into the great hall, landing "+
               "hard on the floor.\n\n");
            say(QCTNAME(TP)+" is ejected from the divination chamber!\n");
            TP->remove_prop(ENTERED_TEMPLE_CIRCLE);
            TP->move_living("M",SPIRIT_TEMPLE+"great_hall",1);
            say(QCTNAME(TP)+" comes flying out of the eastern double "+
                "doors, landing hard on the floor.\n");
            NF("\n");
            return 0;
        }

        /* They have their master spells object */
        if (master)
        {
            /* Are they fourth level? */
            if(TP->query_spirit_circle_level() >= 4)
            {
                /* Add the fourth level spells */
                master->update_fourth_spells();

        /* Check their chosen count, make sure it has the fourth level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FOUR_FLAG))
                {
                /* They didn't have fourth level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_FOUR_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }
            
            /* Are they fifth level? */
            if (TP->query_spirit_circle_level() >=5)
            {
                /* Add the second level spells */
                master->update_fifth_spells();

        /* Check their chosen count, make sure it has the fifth level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_FIVE_FLAG))
                {
                /* They didn't have fifth level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_FIVE_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }

            /* Are they sixth level? */
            if (TP->query_spirit_circle_level() >= 6)
            {
                master->update_sixth_spells();
        /* Check their chosen count, make sure it has the sixth level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SIX_FLAG))
                {
                /* They didn't have sixth level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_SIX_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }

            /* Are they seventh level? */
            if (TP->query_spirit_circle_level() >= 7)
            {
                master->update_seventh_spells();
        /* Check their chosen count, make sure it has the seventh level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_SEVEN_FLAG))
                {
                /* They didn't have seventh level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_SEVEN_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }
        }   
    }   /* End of Master circle stuff */


    /* Are they in the Elder circle? */
    if ((TP->query_prop(ENTERED_TEMPLE_CIRCLE)) == "Elder")
    {
        excess = filter(all_inventory(TP), 
            &operator(==)("_spirit_elder_spells_") @ &->query_name());
        excess->remove_object();      

        /* They don't have it, are they a member and high enough level? */
        if (!elder && IS_MEMBER(TP))
        {
            /* They don't have it and ARE members, give it to them */
            elder=clone_object(SPIRIT_OBJECTS+"elder_spells");
            elder->move(TP, 1);
        }

        /* If they don't have it, are members, and too low of a level */
        if (!elder && IS_MEMBER(TP))
        {
            NF("You are not in the Elder ranking, therefore cannot divine "+
               "for the Elder ranking gifts.\n");
            TP->command("leave circle");
            return 0;
        }

        /* They don't have it still, probably not a member */
        if (!elder && !(IS_MEMBER(TP)))
        {
            /* Indeed they are not members, tell them so, and get them out */
            write("\nYou cannot divine for gifts as you are not a member "+
               "of the Circle! In fact, you shouldn't be in here!\n");
            write("Now get out! You feel yourself being thrown through the "+
               "double doors and back out into the great hall, landing "+
               "hard on the floor.\n\n");
            say(QCTNAME(TP)+" is ejected from the divination chamber!\n");
            TP->remove_prop(ENTERED_TEMPLE_CIRCLE);
            TP->move_living("M",SPIRIT_TEMPLE+"great_hall",1);
            say(QCTNAME(TP)+" comes flying out of the eastern double "+
                "doors, landing hard on the floor.\n");
            NF("\n");
            return 0;
        }

        /* They have their apprentice spells object */
        if (elder)
        {
            /* Are they eighth level?  (Call it a paranoid check) */
            if (TP->query_spirit_circle_level() > 7)
            {
                /* Add the eighth level spells */
                elder->update_eighth_spells();

        /* Check their chosen count, make sure it has the eighth level flag */
                if (!(TP->query_skill(SS_SPIRIT_CHOSEN) & SPELLS_EIGHT_FLAG))
                {
                /* They didn't have eighth level flag, set it and reset tax */
                    TP->set_skill(SS_SPIRIT_CHOSEN,
                        (TP->query_skill(SS_SPIRIT_CHOSEN) | SPELLS_EIGHT_FLAG));
                    TP->set_guild_pref(SS_OCCUP,TP->query_guild_tax_occ());
                }
            }
        }   
    }   /* End of Elder circle stuff */

    return 1;
}

int
do_leave(string str)
{
    if (!str)
    {
        NF("Leave what? A circle? <leave circle>\n");
        return 0;
    }

    if (!parse_command(str, ({}), 
        "[the] [first] [second] [third] [apprentice] [master] [elder] 'circle'"))
    {
        NF("Leave what? A circle? <leave circle>\n");
        return 0;
    }

    if (!(TP->query_prop(ENTERED_TEMPLE_CIRCLE)))
    {
        NF("You are not in a circle!\n");
        return 0;
    }

    write("You leave the Circle of "+TP->query_prop(ENTERED_TEMPLE_CIRCLE)+"s.\n");
    say(QCTNAME(TP)+" leaves the Circle of "+TP->query_prop(ENTERED_TEMPLE_CIRCLE)+
        "s.\n");
    TP->remove_prop(ENTERED_TEMPLE_CIRCLE);
    return 1;
}


void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_divine,"divine");
    add_action(do_leave,"leave");
}
