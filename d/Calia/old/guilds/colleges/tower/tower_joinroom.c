/*
   A room on in the Marble Tower. This is where you join the guild. 
   Created July 2003, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h";

#define ROOM_O_TOME_OPENED_BY "_room_o_tome_opened_by"

#define TOME_CLOSED 0
#define TOME_JOINING 1
#define TOME_LEAVING 2
#define TOME_MEMBERLIST 3

static int book_state = 0;


string
tome_desc()
{
    string str = "This huge, carefully bound tome is among the biggest" +
        " you have seen. It appears to be well maintained, for each sheet" +
        " is as pristine as if it were printed yesterday. The covers are" +
        " made of thin wood.";

    if (!(TP->is_college_member()))
    {
        str += " You can open the book at the sections 'joining' and" +
            " 'leaving'.";
    }
    else
    {
        str += " You can open the book at the sections 'joining', 'leaving'" +
            " and 'memberlist'.";
    }
                
    if (book_state)
    {
        str += " The tome is open."; 
    }
    else 
    {
        str += " The tome is closed.";
    }
    
    return str;
}

create_room()
{
    set_short("Tower Records"); // Heh, heh, heh.

    set_long("This small chamber is where the Colleges keep their records." +
        " A huge tome is secured to a solid table at the center of the room. "+ 
        basic_desc + " To the east, a corridor stretches past.\n"); 

    add_item(({"book", "tome"}), "@@tome_desc@@\n");
    add_item("table", "This wooden table looks very sturdy. It would have to" +
        " be, to carry the weight of the massive tome.\n");

    add_exit(TOWER + "tower_corr_2_4.c", "east", 0, 1);

    make_college_room();
}

int
read_book(string str)
{

    if (str != "book" && str != "tome")
    {
        NF("Read what?\n");
        return 0;
    }
    else 
    if (book_state == TOME_CLOSED)
    {
        NF("The tome is closed!\n");
        return 0;
    }
    else
    if (TP != TO->query_prop(ROOM_O_TOME_OPENED_BY))
    {
        book_state = 0;
        say(QCTNAME(TP) + " tries to read in the tome, but it slams shut!");
        NF("You try to read the tome, but it slams shut before you can" +
            " catch a single word!\n");
        return 0;
    }
    else
    if (book_state == TOME_JOINING)
    {
        write("In order to become an apprentice, one must fulfill the" +
            " following requirements:\n" +
            "    - You must be an adept or greater in mortal stature.\n" +
            "    - Have a sponsor who is willing to be your mentor, guiding" +
            " you in your studies, and who is present in the room with" +
            " you.\n" +
            "    - Be approved by the Assembly.\n" +
            "If these requirements are in place, you may join the guild here" +
            " by inscribing your name in the tome.\n");
        if (TP->query_wiz_level())
        {
            write("Alternatively, if you are a wizard, you may simply" +
                " inscribe your name in the tome. Make sure to ask the" +
                " guildmaster for permission first.\n");
        }
        
        say(QCTNAME(TP) + " reads in the tome.\n");
        return 1;
    }
    else
    if (book_state == TOME_LEAVING)
    {
        write("Leaving the guild has serious consequences. We must make sure" +
            " you do not betray our secrets, so the memories you have from" +
            " your life in the Marble Tower will be completely erased. A full"+
            " third of your combat experience will also be lost. To go ahead" +
            " with this betrayal, erase your name from the tome.\n");
        say(QCTNAME(TP) + " reads in the tome.\n");
        return 1;
    }
    else
    if (book_state == TOME_MEMBERLIST)
    {
        write("Not implemented yet, please be patient!\n");
        say(QCTNAME(TP) + " reads in the tome.\n");
        return 1;
    }
    else
    {
        NF("Something odd has happened to the tome. Please contact the" +
           " guildmaster.\n");
        return 0;
    }
}    


int
do_open(string str)
{
    if (str == "joining" || str == "at joining" || str == "tome joining" ||
        str == "tome at joining" || str == "time joining section" ||
        str == "tome at joining section")
    {
        write("You open the tome at the section concerning joining.\n");
        TO->add_prop(ROOM_O_TOME_OPENED_BY, TP);
        book_state = TOME_JOINING;        
        say(QCTNAME(TP) + " opens the tome.\n");
        return 1;
    }
    else
    if (str == "leaving" || str == "at leaving" || str == "tome leaving" ||
        str == "tome at leaving" || str == "tome leaving section" ||
        str == "tome at leaving section")
    {
        write("You open the tome at the section concerning leaving.\n");
        TO->add_prop(ROOM_O_TOME_OPENED_BY, TP);
        book_state = TOME_LEAVING;            
        say(QCTNAME(TP) + " opens the tome.\n");
        return 1;   
    }
    else
    if ((str == "memberlist" || str == "at memberlist" || 
        str == "tome memberlist" ||
        str == "tome at memberlist" ||
        str == "tome memberlist section" ||
        str == "tome at memberlist section")  && TP->is_college_member())
    {
        write("You open the tome at the memberlist section.\n");
        TO->add_prop(ROOM_O_TOME_OPENED_BY, TP);
        book_state = TOME_MEMBERLIST;                    
        say(QCTNAME(TP) + " opens the tome.\n");
        return 1;
    }
    else
    {
        NF("Open tome where?\n");
        return 0;
    }
}
        

int
do_close(string str)
{
    if (str == "tome" || str == "book")
    {
        TO->remove_prop(ROOM_O_TOME_OPENED_BY);
        write("You close the tome.\n");
        book_state = TOME_CLOSED;
        return 1;
    }
    else
    {
        NF("Close what?\n");
        return 0;
    }
}


int
do_join(object ob)
{
    object shadow;
    
    setuid();
    seteuid(getuid());
    
    shadow = clone_object(FIRE_SPECIALS + "fireshadow.c");
    
    if (shadow->shadow_me(ob, "occupational", "magic",
        "College of Fire Magic","") != 1)
    {
        shadow->remove_shadow();
        return 0;
    }
    
    ob->clear_guild_stat(SS_OCCUP);
    clone_object(FIRE_OBJECTS + "fire_ring")->move(ob);
    ob->set_skill(SS_COLLEGE_BITS, APPRENTICE_LVL_BIT);
    ob->set_skill(SS_COLLEGE_SPELL_STATUS, 0);
    ob->set_skill(SS_RITUAL_MAGIC, 0);
    
    //This might look a little weird. The reason I OR the level bit
    //with 8 is that I want to include the element used in the member
    //mapping that is stored in COUNCIL_OB, not just the rank. For this 
    //purpose I have defined fire as 8, air 16, water 32 and earth 64. 
    COUNCIL_OB->add_member(ob->query_name(), APPRENTICE_LVL_BIT | 8);  
    COUNCIL_OB->cleanup_approved_applicants(); 
    
    write_file(COLLEGE_LOGS + "joinleavelog", ob->query_name() + 
        " joined the " +
        capitalize(ob->is_college_member()) + " College on " + 
        ctime(time())+".\n");

    ob->catch_tell("You joined the College of " + 
        capitalize(ob->is_college_member()) + " Magic!\n");

    return 1;
}


int
join_guild(string str)
{
    if (str == "my name in tome" || str == "name in tome")
    {
        if (TP->is_college_member())
        {
            NF("You are already a member!\n");
            return 0;
        }
       
        if (TP->query_wiz_level())
        {
            if (!do_join(TP))
            {
                NF("A bug prevented you from joining. Contact the" +
                    " guildmaster.\n");
                return 0;
            }
            
            return 1;
        }
        else
        if (TP->query_average_stat() < 64)
        {
            NF("You are of too small stature to be accepted into the" +
               " guild!\n"); 
            return 0;
        }
        else
        if (!(COUNCIL_OB->check_approved_applicant(TP->query_name())))
        {
            NF("The Assembly has not approved you!\n");
            return 0;
        }
        /*
        
          Here we add check for sponsor presence.
        
        */
        else
        {
            if (!do_join(TP))
            {
                NF("A bug prevented you from joining. Contact the" +
                    " guildmaster.\n");
                return 0;
            }      
            
            return 1;  
        }
    }
    else
    {
        NF("Inscribe what?\n");
        return 0;
    }       
}

int
leave_guild(string str)
{
    if (str == "my name from tome" || str == "name from tome")
    {
        if (!(TP->is_college_member()))
        {
            NF("You are not a member of the guild!\n");
            return 0;
        }
        else
        {
            setuid();
            seteuid(getuid());
        
            present("college_ring", TP)->remove_object();
            
            TP->remove_skill(SS_COLLEGE_BITS);
            TP->remove_skill(SS_COLLEGE_SPELL_STATUS);
            TP->remove_skill(SS_RITUAL_MAGIC);
            
            TP->clear_guild_stat(SS_OCCUP);
            TP->remove_cmdsoul(FIRE_SPECIALS + "firesoul");
            TP->update_hooks();
                        
            COUNCIL_OB->remove_member(TP->query_name());            
           
            write_file(COLLEGE_LOGS + "joinleavelog", TP->query_name() + 
                " left the " + capitalize(TP->is_college_member()) + 
                " College on " + ctime(time())+".\n");                       
            TP->remove_guild_occ();

            write("You left the guild. Penalties not implemented yet.\n");
           
            return 1;
        }
    }
    else
    {
        NF("Erase what?\n");
        return 0;
    }   
}

void
init()
{
    ::init();
    
    add_action("do_close", "close");
    add_action("read_book", "read");
    add_action("do_open", "open");
    add_action("join_guild", "inscribe");
    add_action("leave_guild", "erase");
}