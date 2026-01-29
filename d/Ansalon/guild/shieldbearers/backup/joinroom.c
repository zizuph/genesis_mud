
#pragma strict_types

inherit "/lib/skill_raise";

#include "guild.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

#define  BOULDER_CHARGE_PROP  "_charging_at_the_boulder"

inherit  "/d/Ansalon/estwilde/std/dwarf_out.c";

public int    join(string str);
public int    leave(string str);

object        trainer;

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 30);
    sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 60);
    
    sk_add_train(SHIELDSLAM_SPECIAL, "bash enemies with a shield",
        "shield slam", 80, 100);

}

public varargs int
sk_query_max(int snum, int silent)
{
    if ( snum == SHIELDSLAM_SPECIAL )
    {
        if ( TP->query_guild_member("Dwarven Warriors of the Neidar Clan") )
            return 100;
        else
            return 85;
    }
    
    return ::sk_query_max(snum, silent);
}

public int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if ( !sk || sscanf(sk, "%d", steps) )
    {
	if ( !TP->query_guild_member(GUILD_NAME) )
	{
	    write("Only Shieldbearers may train here.\n");
	    return 1;
	}
	
	return sk_list(steps);
    }

    tmp = explode(sk, " ");

    if( sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1 )
	skill = implode(tmp[0 .. sizeof(tmp) -2], " ");
    else
    {
	skill = sk;
	steps = 1;
    }

    if( !(present("trainer", TO)) )
    {
	write("Without a trainer, you are unable to improve " +
	  "your skills to any extent.\n");
	return 1;
    }
    
    if( !TP->query_guild_member(GUILD_NAME) )
    {
	write("Only Shieldbearers may train here.\n");
	return 1;
    }
    
    return ::sk_improve(sk);
}

void
reset_dwarf_room()
{
    if(!objectp(trainer))
    {
	trainer = clone_object("/d/Ansalon/guild/shieldbearers/trainer");
	trainer->move(TO, 1);
    }
}

void
create_dwarf_room()
{
    set_short("In a clearing at the base of a steep hill");
    set_long("You stand at the base of a steep, barren hill " +
      "in a clearing set aside by the dwarves of Iron Delving " +
      "to train their skills. The ground here seem to be trodden " +
      "down, like someone was running to and fro. You notice a few " +
      "broken and dented shields laying around. The village is " +
      "to the east.\nThere is a small sign here.\n");

    add_item(({ "shield", "broken shields", "dented shields", "shields" }),
        "There are a few destroyed shields laying around on the ground. " +
        "Some of them are only dented but others are totally broken and " +
        "you wonder what caused that. It might be an effect of slamming " +
        "them into something really hard!\n");
    
    add_item(({ "steep hill", "hill", "barren hill", "hillside", "stream" }),
      "You stand at the base of a steep and barren hill. It is so " +
      "steep you doubt you could climb it even with climbing " +
      "equipment. There is a bubbling stream a bit to the north and " +
      "it disappears from your sight between the hills to the west.\n"); 

    add_item("clearing",
      "You stand in a clearing set aside for the training of Clan members. " +
      "If you are a Shieldbearer, you may <improve> or <learn> the skill " +
      "in using a shield. If you are a clan warrior, you may choose to " +
      "<become> a Shieldbearer or if you are one already you may some " +
      "day decide to <return> your insignia.\n");
    
    add_item(({ "sign", "small sign" }), "@@read_sign");
    
    add_cmd_item(({"small sign", "sign"}), "read", "@@read_sign");
        
    add_exit("/d/Ansalon/estwilde/iron_delving/r10", "east", "@@leave_check");

    room_add_object(GUILD_DIR + "obj/boulder", 1, 0);
    
    /* configure the trainer */
    set_up_skills();
    reset_dwarf_room();
}

public int
leave_check()
{
    if ( TP->query_prop(BOULDER_CHARGE_PROP) )
        TP->remove_prop(BOULDER_CHARGE_PROP);
    
    return 0;
}

string
read_sign()
{
    write("If you are a Shieldbearer, you may <improve> or <learn> the " +
        "skills here. If you are a Clan warrior, or their friend, you " +
        "may choose to <become> a Shieldbearer or if you are one " +
        "already you may some day decide to <return> your insignia.\n");
    
    return "";
}

void
init()
{
    ::init();

    add_action(join, "become");
    add_action(leave, "return");

    init_skill_raise();
}

public int
join(string str)
{
    object shadow;
    mixed  why;
    int    result;

/*   
    notify_fail("The guild is closed for new members for now.\n");
    return 0;
 */
    if ( !strlen(str) || !parse_command(str, ({}),
        "[a] [the] 'Shieldbearer' / 'shieldbearer'") )
    {
        notify_fail("Do you want to become a Shieldbearer?\n");
        return 0;
    }
    
    if ( TP->query_guild_member(GUILD_NAME) )
    {
        notify_fail("But you are a Shieldbearer already!\n");
        return 0;
    }
    
    if ( !objectp(trainer) )
    {
        notify_fail("The trainer is not present and you need him " +
            "to show you how to use a shield! You can not become a " +
            "Shieldbearer right now.\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    
    shadow = clone_object(GUILD_SHADOW);
    
    /* Check if this member is acceptable */
    if ( stringp(why = shadow->acceptable_member(TP)) )
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
        result = shadow->add_lay_shadow(TP);
        
        switch (result) 
        {
            case 1:
                TP->clear_guild_stat(SS_LAYMAN);
                write("You are given a small wooden buckler brooch.\n");

                write_file(MEMBERS, TP->query_name() + " joined " +
                    extract(ctime(time()), 4, 15) +
                    ", StatAvg: " + TP->query_average_stat() +
                    ", Race: " + TP->query_race() +
                    ", Align: " + TP->query_alignment() + "\n");
      
                return 1;
            break;
            case -4:
                write("Your other guild does not want you in this one!\n");
            break;
            case -3:
                write("Wrong guild style. Please, make a bug report.\n");
            break;
            case -2:
                write("Wrong guild type. Please, make a bug report.\n");
            break;
            case -1:
                write("Lack of guild name. Please, make a bug report.\n");
            break;
            default:
              /* Error in shadowing */
                write("An error had prevented you from joining.\n");
            break;
        }
    }
    
    /* We could not shadow the player -> remove shadow */
    
    shadow->remove_shadow();
    return 1;
}
   
public int
leave(string str)
{
    if ( !strlen(str) || !parse_command(str, ({}),
        "[an] [the] [my] 'insignia' [of] [the] [a] [shieldbearer]") )
    {
        notify_fail("Do you want to return your insignia?\n");
        return 0;
    }
    
    if ( !TP->query_guild_member(GUILD_NAME) )
    {
        notify_fail("But you are not a Shieldbearer!\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
        
    TP->remove_lay_member();
    
    write("You decide to return your insignia of the Shieldbearer.\n");
    say(QCTNAME(TP) + " returns " + HIS(TP) + " insignia of the " +
        "Shieldbearer.\n");

    write_file(MEMBERS, TP->query_name() + " left " +
        extract(ctime(time()), 4, 15) +
        ", StatAvg: " + TP->query_average_stat() +
        ", Race: " + TP->query_race() +
        ", Align: " + TP->query_alignment() + "\n");
    
    return 1;
}

