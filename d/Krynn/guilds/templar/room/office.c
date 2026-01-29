/**
* Office room
* This is where Priest of Takhisis can do some roleplay functions
* to promote/demote/etc members within the Templars, who are under
* their control.
* Louie  2004
*/

#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GUILD_IR;

/** prototypes **/
string scroll_descrip();
string priest_descrip();
string lord_descrip();
string officer_descrip();
string default_descrip();
int assign_rank(string str);
int expel_templar(string str);
int read_sign(string str);
int is_templar(object ob);
int templarlist(string str);

void
reset_guild_room()
{
    
}

void
create_guild_room()
{
    set_short("office of the Templar Knights");
    
    set_long("This room contains various records used "+
        "by the Priesthood of Takhisis to keep track "+
        "of their loyal servants within the Templars.  "+
        "There is a sign here, as well as a desk with "+
        "various papers on it.  "+      
        "\n");
        
    add_item(({"sign"}),
        &scroll_descrip());
        
    add_item(({"desk","paper","papers","record","records"}),
        "Papers litter the desk.  Perhaps sometime in the "+
        "future a wizard will organize things a bit better.\n");
        
    
    add_exit(ROOM+"joinroom","west");
    reset_guild_room();

}

void
init()
{
    ::init();
    add_action(read_sign, "read");
    add_action(assign_rank, "assign");
    add_action(templarlist, "list");
//    add_action(expel_templar, "templar");
    
}

/*Is templar*/
int
is_templar(object ob)
{
    return ob->query_templar_member();
}

/**
 * List the Templars in the game
 */

int
templarlist(string str)
{
    object *players;
    string txt = "", mem_txt = "", tmp;
    int i, wwidth = TP->query_option(1);
    int all = 0;
    mixed l_ar, o_ar, k_ar, w_ar, b_ar;

    if (!strlen(str) || 
        (str != "templar" && str != "templars"
        && str != "active templars" && str != "all templars")) {
        NF("List active templars or all templars?\n");
        return 0;
    }

    if (!TP->query_templar_knight() &&
        !TP->query_templar_officer() &&
        !TP->query_templar_lord() &&
        !TP->query_pot_member() &&
        !TP->query_wiz_level())
    {
        NF("That is restricted to full Templars and Priests.\n");
        return 1;
    }
    if(wwidth < 11)
    wwidth = 78;

    //Display all templars
    if (str == "all templars")
    {
        l_ar = ADMIN->query_lords();
        o_ar = ADMIN->query_officers();
        k_ar = ADMIN->query_knights();
        w_ar = ADMIN->query_warriors();
        b_ar = ADMIN->query_betrayers();
        int i;

        write("Looking at the files you see the list of all Templars:\n\n");

        //Lords
        txt  = "The Lord of the Templar Knights\n";
        txt += "-------------------------------\n";
        i = sizeof(l_ar);
        mem_txt = "";
        while (i--)
        {
            mem_txt += capitalize(l_ar[i] + " ");
        }

        txt += break_string(mem_txt, wwidth-10, 5) + "\n\n";

        //Officers
        txt += "Officers of the Templar Knights\n";
        txt += "-------------------------------\n";
        mem_txt = "";
        i = sizeof(o_ar);
        while (i--)
        {
            mem_txt += capitalize(o_ar[i] + " ");
        }

        txt += break_string(mem_txt, wwidth-10, 5) + "\n\n";

        //Knights
        txt += "Full Templar Knights\n";
        txt += "--------------------\n";
        mem_txt = "";
        i = sizeof(k_ar);
        while (i--)
        {
            mem_txt += capitalize(k_ar[i] + " ");
        }

        txt += break_string(mem_txt, wwidth-10, 5) + "\n\n";

        //Warriors
        txt += "Warriors of Neraka\n";
        txt += "------------------\n";
        mem_txt = "";
        i = sizeof(w_ar);
        while (i--)
        {
            mem_txt += capitalize(w_ar[i] + " ");
        }

        txt += break_string(mem_txt, wwidth-10, 5) + "\n\n";

        //Betrayers
        txt += "Betrayers of Her Dark Majesty\n";
        txt += "-----------------------------\n";
        mem_txt = "";
        i = sizeof(b_ar);
        while (i--)
        {
            mem_txt += capitalize(b_ar[i] + " ");
        }

        txt += break_string(mem_txt, wwidth-10, 5) + "\n\n";

        write(txt+"\n");

        return 1;
    }

    //Display active Templars
    players = filter(users(), "is_templar", this_object());

    write("The following Templars are protecting Her interests:\n\n");
    for(i = 0; i < sizeof(players); i++)
    {
        if(players[i]->query_invis() == 0
            || !players[i]->query_wiz_level())
        {
            txt += break_string(players[i]->query_name() + " the " +
                players[i]->query_guild_title_lay() +"\n",wwidth-10,5)[5..];
        }
    
    }
    
    write(txt);
    return 1;
      
}


int
assign_rank(string str)
{
    string name, rank;
    int irank;
    
    if (!TP->query_pot_member() &&
        !TP->query_templar_officer() &&
        !TP->query_templar_lord() &&
        !TP->query_wiz_level())
    {
        NF("What?\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        NF("Assign <name> [to] <rank>.  Read the sign for help.\n");
        return 0;
    }
    
    if (!parse_command(str, E(TP), " %w [to] %w ", name, rank))
    {
        NF("Assign <name> [to] <rank>.  Read the sign for help.\n");
        return 0;
    }
    
    if (!(rank == "warrior") &&
        !(rank == "Warrior") &&
        !(rank == "knight") &&
        !(rank == "Knight") &&
        !(rank == "officer") &&
        !(rank == "Officer") &&
        !(rank == "lord") &&
        !(rank == "Lord") &&
        !(rank == "betrayer") &&
        !(rank == "Betrayer"))
    {
        NF("Valid ranks are betrayer, warrior, knight, officer, and lord.\n");
        return 0;
    }
    
    if (!ADMIN->query_member(name))
    {
        NF("The person '"+name+"' is not in the guild.\n");
        return 0;
    }
    
    if (!(ADMIN->query_templar_rank(name) < ADMIN->query_templar_rank(TP))
        && !TP->query_pot_member() && !TP->query_wiz_level())
    {
        NF("That person is not ranked lower than you, "+
            "you have no power to promote/demote!\n");
        return 0;
    }
        
    if ((rank == "lord") || (rank == "Lord")) {
        if (!TP->query_pot_member() && !TP->query_wiz_level())
        {
            NF("You do not have the authority to make someone Lord.\n");
            return 0;
        } else {
            if (ADMIN->set_templar_rank(name, TEMPLAR_RANK_LORD))
            {
                write("You promote "+capitalize(name)+
                    " to Lord Templar Knight.\n");
                return 1;
            } else
            {
                write("There was an error promoting "+
                    capitalize(name)+" to Lord.\n");
                return 1;
            }
        }       
    }
    
    if ((rank == "officer") || (rank == "Officer")) {
        if (!TP->query_pot_member() && !TP->query_wiz_level()
            && !TP->query_templar_lord())
        {
            NF("You do not have the authority to make someone an Officer.\n");
            return 0;
        } else {
            if (ADMIN->set_templar_rank(name, TEMPLAR_RANK_OFFICER))
            {
                write("You assign "+capitalize(name)+
                    " to the rank of Officer of the Templar Knights.\n");
                return 1;
            } else
            {
                write("There was an error assigning "+
                    capitalize(name)+" to Officer.\n");
                return 1;
            }
        }       
    }

    if ((rank == "knight") || (rank == "Knight")) {
        if (!TP->query_pot_member() && !TP->query_wiz_level()
            && !TP->query_templar_lord() && !TP->query_templar_officer())
        {
            NF("You do not have the authority to make someone a Knight.\n");
            return 0;
        } else {
            if (ADMIN->set_templar_rank(name, TEMPLAR_RANK_KNIGHT))
            {
                write("You assign "+capitalize(name)+
                    " to the rank of Templar Knight.\n");
                return 1;
            } else
            {
                write("There was an error assigning "+
                    capitalize(name)+" to Knight.\n");
                return 1;
            }
        }       
    }

    if ((rank == "warrior") || (rank == "Warrior")) {
        if (!TP->query_pot_member() && !TP->query_wiz_level()
            && !TP->query_templar_lord() && !TP->query_templar_officer())
        {
            NF("You do not have the authority to make someone a Warrior.\n");
            return 0;
        } else {
            if (ADMIN->set_templar_rank(name, TEMPLAR_RANK_WARRIOR))
            {
                write("You assign "+capitalize(name)+
                    " to the rank of Warrior.\n");
                return 1;
            } else
            {
                write("There was an error assigning "+
                    capitalize(name)+" to Warrior.\n");
                return 1;
            }
        }       
    }

    if ((rank == "betrayer") || (rank == "Betrayer")) {
        if (!TP->query_pot_member() && !TP->query_wiz_level()
            && !TP->query_templar_lord())
        {
            NF("You do not have the authority to make someone a Betrayer.\n");
            return 0;
        } else {
            if (ADMIN->set_templar_rank(name, TEMPLAR_RANK_BETRAYER))
            {
                write("You assign "+capitalize(name)+
                    " to the rank of Betrayer.\n");
                return 1;
            } else
            {
                write("There was an error assigning "+
                    capitalize(name)+" to Betrayer.\n");
                return 1;
            }
        }       
    }

    
    
}

int
expel_templar(string str)
{
    write("Expel is not implemented.\n");
    return 1;
}

int
read_sign(string str)
{
    string descrip;
    
    if (!strlen(str))
    {
        NF("Read what?\n");
        return 0;
    }
    
    if (!(str == "sign"))
    {
        NF("Read what?\n");
        return 0;
    }
    
    descrip = scroll_descrip();
    
    write(descrip);
    return 1;
}


string
scroll_descrip()
{
    string desc;
    
    if (TP->query_templar_lord())
    {
        desc = lord_descrip();
    } else 
        if (TP->query_templar_officer())
    {
        desc = officer_descrip();
    } else
        if (TP->query_pot_member() || TP->query_wiz_level())
    {
        desc = priest_descrip();
    } else
    {
        desc = default_descrip();
    }
    
    
    return desc;
}

string
priest_descrip()
{
    string desc;
    
    desc =
    "\t"+
    " ______________________________________________\n\t"+
    "|                                              |\n\t"+ 
    "| +                                          + |\n\t"+
    "|    Commands available:                       |\n\t"+
    "|    Priests -                                 |\n\t"+
    "|    * assign <templar name> [to] <rank>       |\n\t"+
    "|    * list templars                           |\n\t"+
    "|    * list all templars                       |\n\t"+
    "|                                              |\n\t"+
    "|      <rank> may be betrayer, warrior,        |\n\t"+
    "|        knight, officer, or lord.             |\n\t"+
    "|                                              |\n\t"+
    "|      Betrayer - Marked as a Betrayer of      |\n\t"+
    "|        the cause of the Priesthood.          |\n\t"+
    "|                                              |\n\t"+
    "|      Warrior - Outside the favor and control |\n\t"+
    "|        of the Priesthood.  There are no      |\n\t"+
    "|        special commands available to Priests |\n\t"+
    "|        or Templars to punish Warriors,       |\n\t"+
    "|        only the option to make them          |\n\t"+    
    "|        Betrayers.                            |\n\t"+    
    "|                                              |\n\t"+    
    "|      Knight - Grants the title of Templar    |\n\t"+
    "|        Knight instead of Warrior.  These     |\n\t"+
    "|        individuals are under the control of  |\n\t"+
    "|        the Priesthood and may receive        |\n\t"+
    "|        special benefits.  They may also be   |\n\t"+
    "|        demoted or expelled by the Priesthood |\n\t"+
    "|        or the Templar Lord.                  |\n\t"+
    "|                                              |\n\t"+
    "|      Officer - An Officer of the Templar     |\n\t"+
    "|        Knights.  May be demoted/expelled by  |\n\t"+
    "|        the Priesthood or the Templar Lord.   |\n\t"+
    "|        Officers can promote Warriors to      |\n\t"+
    "|        Templar Knights.  Officers can demote |\n\t"+
    "|        Templar Knights to Warriors.          |\n\t"+
    "|                                              |\n\t"+
    "|      Lord - The Lord Templar is the leader   |\n\t"+
    "|        of the Templar Knights and Officers.  |\n\t"+
    "|        May promote Warriors to Knights and   |\n\t"+
    "|        Knights to Officers.  May demote      |\n\t"+
    "|        Officers (to Knight/Warrior) and      |\n\t"+
    "|        Knights (to Warrior).  May expel      |\n\t"+
    "|        Officers and Knights.                 |\n\t"+
    "|                                              |\n\t"+
    "| +                                          + |\n\t"+
    "|______________________________________________|\n";
    
    return desc;
 }
 
string
lord_descrip()
{
    string desc;
    
    desc =
    "\t"+
    " ______________________________________________\n\t"+
    "|                                              |\n\t"+ 
    "| +                                          + |\n\t"+
    "|    Commands available:                       |\n\t"+
    "|    Lord Templar -                            |\n\t"+
    "|    * assign <templar name> [to] <rank>       |\n\t"+
    "|    * list templars                           |\n\t"+
    "|    * list all templars                       |\n\t"+
    "|                                              |\n\t"+
    "|      <rank> may be betrayer, warrior,        |\n\t"+
    "|        knight, or officer.                   |\n\t"+
    "|                                              |\n\t"+
    "|      Betrayer - Marked as a Betrayer of      |\n\t"+
    "|        the cause of the Priesthood.          |\n\t"+
    "|                                              |\n\t"+
    "|      Warrior - Outside the favor and control |\n\t"+
    "|        of the Priesthood.  There are no      |\n\t"+
    "|        special commands available to Priests |\n\t"+
    "|        or Templars to punish Warriors,       |\n\t"+
    "|        only the option to make them          |\n\t"+    
    "|        Betrayers.                            |\n\t"+    
    "|                                              |\n\t"+    
    "|      Knight - Grants the title of Templar    |\n\t"+
    "|        Knight instead of Warrior.  These     |\n\t"+
    "|        individuals are under the control of  |\n\t"+
    "|        the Priesthood and may receive        |\n\t"+
    "|        special benefit.  They may also be    |\n\t"+
    "|        demoted or expelled by the Priesthood |\n\t"+
    "|        or the Templar Lord.                  |\n\t"+
    "|                                              |\n\t"+
    "|      Officer - An Officer of the Templar     |\n\t"+
    "|        Knights.  May be demoted/expelled by  |\n\t"+
    "|        the Priesthood or the Templar Lord.   |\n\t"+
    "|        Officers can promote Warriors to      |\n\t"+
    "|        Templar Knights.  Officers can demote |\n\t"+
    "|        Templar Knights to Warriors.          |\n\t"+
    "|                                              |\n\t"+
    "| +                                          + |\n\t"+
    "|______________________________________________|\n";
    
    return desc;
 }
 
string
officer_descrip()
{
    string desc;
    
    desc =
    "\t"+
    " ______________________________________________\n\t"+
    "|                                              |\n\t"+ 
    "| +                                          + |\n\t"+
    "|    Commands available:                       |\n\t"+
    "|    Officers -                                |\n\t"+
    "|    * assign <templar name> [to] <rank>       |\n\t"+
    "|    * list templars                           |\n\t"+
    "|    * list all templars                       |\n\t"+
    "|                                              |\n\t"+
    "|      <rank> may be warrior or knight.        |\n\t"+
    "|                                              |\n\t"+
    "|      Warrior - Outside the favor and control |\n\t"+
    "|        of the Priesthood.  There are no      |\n\t"+
    "|        special commands available to Priests |\n\t"+
    "|        or Templars to punish Warriors.       |\n\t"+
    "|                                              |\n\t"+    
    "|      Knight - Grants the title of Templar    |\n\t"+
    "|        Knight instead of Warrior.  These     |\n\t"+
    "|        individuals are under the control of  |\n\t"+
    "|        the Priesthood and may receive        |\n\t"+
    "|        special benefit.  They may also be    |\n\t"+
    "|        demoted or expelled by the Priesthood |\n\t"+
    "|        or the Templar Lord.                  |\n\t"+
    "|                                              |\n\t"+
    "| +                                          + |\n\t"+
    "|______________________________________________|\n";
    
    return desc;
 }
 
 string
 default_descrip()
 {
    string desc;
    
    desc = "The sign appears completely black.\n";
    
    return desc;
 }