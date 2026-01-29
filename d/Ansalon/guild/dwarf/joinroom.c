/* A simple room where you can join this guild. 
 *
 * 22.08.2003 Modified by Blizzard:
 * Added 'distrust' command for removing the rune of friendship from people.
 *
 * Louie Feb 2005 - Fixed honour command if no string is given.
 * Louie Mar 2006 - Ability to list exiles via 'exile list'
 * Navarre July 3rd 2006 - Fixed typo 
 */

#pragma strict_types
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"

inherit "/d/Ansalon/estwilde/std/inside_base";

#include "guild.h"

#define MEMBERS      "/d/Ansalon/log/clan/members"

void
reset_dwarf_room()
{
    return;
}

void
create_dwarf_room()
{
    set_short("Audience chamber of the Hall of the Thane");
    set_long("You stand within the audience chamber of the Hall " +
      "of the Thane. This huge room is mostly empty except for " +
      "two braziers burning in the far corners, and a large throne " +
      "of stone inbetween them. Here, dwarves may 'declare' themselves " +
      "members of the clan if they have been 'accepted' as a " +
      "worthy canditate by the Thane or one of his Elders. Clan " +
      "members may also 'forsake' the clan here.  "+
      "An elder may also 'assume command' as Thane if necessary.\n");

    add_item(({"stone throne","large throne","throne"}),
      "This large stone throne is that used by the Thane of " +
      "the Hill Dwarves when he is in audience.\n");
    add_item(({"braziers","brazier"}),
      "Two long copper braziers burn sullenly in the corners " +
      "on either side of the throne, filling the room with " +
      "a dim light.\n");

    add_exit("/d/Ansalon/estwilde/iron_delving/hall1","northwest","@@go_west");

    
    setuid();
    seteuid(getuid());

    reset_dwarf_room();

}

int
go_west()
{
    if(TP->query_prop(AM_SITTING))
    {
	write("You are sitting in your throne " +
	  "at the moment. Perhaps you should stand " +
	  "before you leave the audience chamber?\n");
	return 1;
    }
    return 0;
}

int
occjoin(string str)
{
    object sh;
    mixed why;

    if(!str)
    {
	notify_fail("Declare what? Yourself as a clan member?\n");
	return 0;
    }

    if(str != "myself clan member")
    {
	notify_fail("Syntax to join the Clan: " +
	  "'declare myself clan member'.\n");
	return 0;
    }

    if(!this_player()->query_prop(I_CAN_JOIN_ANSALON_CLAN))
    {
	notify_fail("You have not yet been accepted by an " +
	  "Elder member yet.\n");
	return 0;
    }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
	write(why);
    }
    else
    {
	/* Try to add the shadow to the player */
	switch (sh->add_occ_shadow(this_player()))
	{
	case 1:
	    /* We have successfully shadowed the player, so we're set */
	    write("You step forward and proudly declare yourself to be " +
	      "a loyal member of the Neidar clan!\n");
	    say(QCTNAME(TP)+ " proudly steps foward and declares " +
	      HIM(TP)+ "self to be a loyal member of the Neidar clan!\n");
	    write("Welcome to the clan!\n");
	    write("You are presented with a long-stemmed pipe in honour " +
	      "of this occasion! Smoke it well!\n");

	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " joined the clan.\n", 500000);
	    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
	      C(TP->query_real_name())+ " joined the mighty clan warriors!\n", -1);

            write_file(MEMBERS, TP->query_name() + " joined " + 
                       extract(ctime(time()), 4, 15)+
                       ", StatAvg: "+TP->query_average_stat()+
                       ", Race: "+TP->query_race()+
                       ", Align: "+TP->query_alignment()+"\n");
	    return 1;

	case -4:
	    /* The player has an occ guild already, or one of his existing
	     * guilds has blocked this one.
	     */ 
	    write("Your other guilds don't want you in this one!\n");
	    break;

	default:
	    /* Some error in shadowing */
	    write("An error has prevented you from joining.\n");
	    break;
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
occleave(string str)
{
    if(!str)
    {
	notify_fail("Forsake what? The clan?\n");
	return 0;
    }

    if(str != "the clan")
    {
	notify_fail("Syntax to leave the clan: " +
	  "'forsake the clan'.\n");
	return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of this guild!\n");
	return 1;
    }

    this_player()->remove_occ_member();
    TP->clear_bit(3,4);
    TP->clear_bit(3,3);
    TP->clear_bit(3,5); // guru quest (added by Torqual 19.09.2001)
    write("You decide to leave the clan!\n");
    write("You feel the weight of the dwarven ancestors press upon you " +
      "for forsaking the Clan. You feel weakened.\n");
    say(QCTNAME(TP) + " forsakes the clan!\n");
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " left the clan.\n", 500000);


    write_file(MEMBERS, TP->query_name() + " left " + 
               extract(ctime(time()), 4, 15)+
               ", StatAvg: "+TP->query_average_stat()+
               ", Race: "+TP->query_race()+
               ", Align: "+TP->query_alignment()+"\n");

    return 1;
}

int
make_elder(string str)
{
    object ob, *obj;

    if(this_player()->test_bit("Ansalon", 3,4) &&
      this_player()->test_bit("Ansalon",3,3))
    {
	notify_fail("Ha! An outcast cannot honour himself, let alone " +
	  "another dwarf!\n");
	return 0;
    }

    if(this_player()->test_bit("Ansalon", 3,3))
    {
	if(strlen(str))
	{
	    if(!sizeof(obj = PARSE_THIS(str, "[the] %l")))
	    {
		notify_fail("Honour which dwarf?\n");
		return 0;
	    }
	    ob = obj[0];
    } else {
        notify_fail("Honour which dwarf?\n");
        return 0;
    }

	TP->catch_msg("You honour " +QTNAME(ob)+ " by " +
	  "making " +HIM(ob)+ " an Elder of the clan, and one of your " +
	  "councillors!\n");
	TP->tell_watcher(QCTNAME(TP) + " honours " +QTNAME(ob) + 
	  " by making " +HIM(ob)+ " an Elder of the Neidar clan!\n", TP);
	ob->catch_msg(QCTNAME(TP) + " honours you by declaring you an Elder " +
	  "of the Neidar clan!\n");
	ob->set_bit(3, 4);

        log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
            C(ob->query_real_name())+ 
            " was declared an Elder of the Neidar Clan!\n", -1);

	return 1;
    }
    write("Only the Thane may honour another clan member with the title of " +
      "Elder.\n");
    return 1;
}

int
joinup(string str)
{
    object ob,*obj;

    if(this_player()->test_bit("Ansalon",3,3) &&
       this_player()->test_bit("Ansalon",3,4))
    {
	notify_fail("You are in disgrace! You have no say in " +
	            "the goings on of the Clan.\n");
	return 0;
    }

    if(this_player()->test_bit("Ansalon",3,3) ||
       this_player()->test_bit("Ansalon",3,4))
    {

	if(strlen(str))
	{
	    if(!sizeof(obj = PARSE_THIS(str, "[the] %l")) || !objectp(obj[0]))
	    {
		notify_fail("Accept who into the clan?\n");
		return 0;	
            }
	    ob = obj[0];
	}
        else
        {
		notify_fail("Accept who into the clan?\n");
		return 0;
        }
        
	TP->catch_msg("You solemnly accept " +QTNAME(ob)+ " as being " +
	  "worthy to join the clan.\n");
	TP->tell_watcher(QCTNAME(TP)+ " solemnly accepts " +QTNAME(ob)+
	  "as being worthy to join the clan!\n", ob);
	ob->catch_msg("You have been accepted as one worthy to join " +
	  "the clan! Now is the time to declare yourself as " +
	  "a clan member.\n");
	ob->add_prop(I_CAN_JOIN_ANSALON_CLAN, 1);
	return 1;
    }
    write("You are not Thane or an Elder! You cannot " +
      "accept another dwarf into the clan.\n");
    return 1;
}

int
sit_throne(string str)
{
    if(!str || str == "throne" || str == "down")
    {
	if(TP->test_bit("Ansalon", 3,3) && TP->test_bit("Ansalon",3,4))
	{
	    write("A disgraced dwarf may not sit in the throne of the Thane!\n");
	    return 1;
	}
	if(!TP->test_bit("Ansalon", 3, 3))
	{
	    write("Only the Thane may sit in this throne.\n");
	    return 1;
	}

	if(TP->query_prop(AM_SITTING))
	{
	    write("You are already sitting in the throne.\n");
	    return 1;
	}
	TP->catch_msg("You sit yourself down on the throne of the " +
	  "Thane of the Hill Dwarves.\n\n" +
	  "   Here you can:\n" +
	  "       'tap' your fingers impatiently on your throne\n" +
	  "       'lean' back in your throne thoughtfully\n" +
	  "       'stand' up from your throne\n" +
	  "       'summon' your crown\n" +
	  "       'exile' a member from Iron Delving\n" +
      "       'exile list' to see the list of exiles\n" +
      "       'exile info <name>' to see when one was exiled\n" +
	  "       'distrust' a so-called friend of the Clan\n" +
	  "       'forgive' a disgraced member who has been exiled\n" +
	  "       and 'honour' a clan member by making them an Elder,\n" +
	  "       one of your councillors and advisors.\n\n");
	TP->tell_watcher(QCTNAME(TP) + " sits " +HIM(TP)+ "self down " +
	  "on the throne of the Thane of the Hill Dwarves.\n", TP);

	TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting on the throne");
	TP->add_prop(AM_SITTING, 1);
	return 1;
    }
    return 0;
}

int
summon_crown()
{

    if(!TP->query_prop(AM_SITTING))
    {
	write("You must be sitting in the throne to summon someone " +
	  "to bring you your crown.\n");
	return 1;
    }

    write("You regally wave your hand, and a young dwarf dashes " +
      "to you, bringing you your crown.\n");
    say(QCTNAME(TP) + " regally waves his hand, and a young dwarf " +
      "dashes to him, bringing him his crown.\n");
    clone_object("/d/Ansalon/estwilde/obj/thane_crown")->move(TP);
    
    return 1;
}

int
stand_throne(string str)
{
    if(!TP->query_prop(AM_SITTING))
    {
	write("You are not sitting in the throne.\n");
	return 1;
    }
    TP->catch_msg("You stand up and step down from the Throne of the Thane.\n");
    TP->tell_watcher(QCTNAME(TP) + " stands up and steps down from the throne.\n", TP);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop(AM_SITTING);
    return 1;
}

int
lean_back()
{
    if(TP->query_prop(AM_SITTING))
    {
	TP->catch_msg("You lean back in your throne thoughtfully.\n");
	TP->tell_watcher(QCTNAME(TP) + " leans back " +
	  "in " +HIS(TP) + " throne thoughtfully.\n", TP);
	return 1;
    }
    return 0;
}

int
exile_dwarf(string str)
{
    string * args;
    
    setuid();    
    seteuid(getuid());
    
    if(!TP->query_prop(AM_SITTING))
    {
        notify_fail("Only the Thane may exile a clan " +
          "member, and then only while " +
          "contemplating the decision from his throne!\n");
        return 0;
    }

    if(!str)
    {
        write("Exile who from Iron Delving, or view the 'exile list'?\n");
        return 1;
    }

    str = lower_case(str);
    args = explode(str, " ");
    if (sizeof(args) == 2 && args[0] == "info")
    {
        EXILE_MASTER->see_info(TP, args[1]);
        return 1;
    }
    
    if (str == "list")
    {
        EXILE_MASTER->list_exiles(TP);
        return 1;
    }

    if (str == "info")
    {
        write("To get info on an exile, do 'exile info <name>'\n");
        return 1;
    }
    
    if (!EXILE_MASTER->add_exile(str))
    {
        // Some error occurred, just return
        return 1;
    }

    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
        C(str) + " was exiled from Iron Delving!\n", -1);
                                
    write("You exile " +capitalize(str)+
      ", who is now in disgrace and may not " +
      "enter Iron Delving until forgiven.\n");

    return 1;
}

int 
distrust(string str)
{
    object rune;

    if( !TP->query_prop(AM_SITTING) )
    {
	notify_fail("Only the Thane may distrust someone, " +
	  "who is considered a friend of the Clan, and then only while " +
	  "contemplating the decision from his throne!\n");
	return 0;
    }
 
    if( !str )
    {
	write("Whom do you want to distrust?\n");
	return 1;
    }

    if ( !find_player(str) )
    {
        write("The person you want to distrust must be awaken.\n");
        return 1;
    }
    
    if ( find_player(str)->query_guild_member(GUILD_NAME) )
    {
        write("You may distrust only non Clan members.\n");
        return 1;
    }
    
    if ( !find_player(str)->test_bit("Ansalon", 3, 13) )
    {
        write("But " + capitalize(str) + " is not considered a friend " +
            "of the Clan!\n");
        return 1;
    }
    
    write("You distrust " + capitalize(str) + ", who may not be called " +
        "a friend of the Clan anymore!\n");
    tell_object(find_player(str), "You have been distrusted by the " +
        "Thane of the Hill Dwarves. You are not longer considered " +
        "a friend of the Clan!\n");
        
    setuid();
    seteuid(getuid());
    
    if ( rune = present("ansalon_rune_object", find_player(str)) )
    {
        rune->destroy();
    }
    
    find_player(str)->clear_bit(3, 13);
    
    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
	 capitalize(TP->query_real_name())+ " distrusted " +
	 capitalize(str)+ " as a friend of the Clan.\n", -1);
        
    return 1;
            
}

int
forgive_dwarf(string str)
{
    setuid();
    seteuid(getuid());
    
    if( !TP->query_prop(AM_SITTING) && !TP->test_bit("Ansalon", 3, 4) )
    {
    	notify_fail("Only the Thane or Elders may forgive a " +
    	  "clan member!\n");
    	return 0;
    }

    if(!str)
    {
    	notify_fail("Who do you wish to forgive?\n");
    	return 0;
    }

    str = lower_case(str);
    if (!EXILE_MASTER->remove_exile(str))
    {
        return 1;
    }

    write("You forgive " + capitalize(str) + ".\n");

    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
        C(str) + " was forgiven by the Thane of the Hill Dwarves!\n", -1);
             
    return 1;
}

int
tap_throne()
{
    if(TP->query_prop(AM_SITTING))
    {
	TP->catch_msg("You tap your fingers impatiently " +
	  "on the arm of your throne.\n");
	TP->tell_watcher(QCTNAME(TP) + " taps " +HIS(TP)+
	  " gnarled fingers impatiently on the arm " +
	  "of " +HIS(TP)+ " throne.\n", TP);
	return 1;
    }
    return 0;
}

int
assume(string str)
{
    object who = TP;

    if (!TP->query_guild_member(GUILD_NAME))
    {
	    notify_fail("But you aren't a member of this guild!\n");
	    return 0;
    }

    if (!strlen(str) || !(str == "command")) {
        notify_fail("Assume command?\n");
        return 0;
    }

    if(TP->test_bit("Ansalon", 3,3) && TP->test_bit("Ansalon",3,4))
	{
	    notify_fail("A disgraced dwarf may not become Thane!\n");
        return 0;
	}

    if (!ADMIN->check_replace_leader(who)) {
        NF("You are unable to assume command.  The current Thane "+
            "must have not logged in for 22 days for someone else "+
            "to take charge.\n");
        return 0;
    }

    if(!TP->test_bit("Ansalon",3,4))
    {
      NF("Only one of the elders can assume leadership.\n");
      return 0;
    }

    //If they were council remove the bit
    if (who->test_bit("Ansalon",3,4))
        who->clear_bit(3,4);

    if (!who->test_bit("Ansalon",3,3))
        who->set_bit(3,3);

    write("You assume command as Thane!\n");
    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
        C(TP->query_real_name())+ 
        " assumed command as Thane.\n", -1);
    return 1;
}

void
init()
{
    ::init();
    add_action(assume, "assume");
    add_action(occjoin, "declare");
    add_action(occleave,"forsake");
    add_action(joinup,"accept");
    add_action(sit_throne, "sit");
    add_action(stand_throne, "stand");
    add_action(lean_back,"lean");
    add_action(tap_throne,"tap");
    add_action(summon_crown,"summon");
    add_action(make_elder,"honour");
    add_action(forgive_dwarf,"forgive");
    add_action(distrust, "distrust");
    add_action(exile_dwarf,"exile");
}
