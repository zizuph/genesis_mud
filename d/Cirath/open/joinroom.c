/* A simple room where you can join this guild. */

#pragma strict_types
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit "/d/Ansalon/estwilde/std/inside_base";
inherit "/cmd/std/command_driver";

#include "guild.h"
#define AM_SITTING "_am_sitting"
#define PUNISH_FILE "/d/Ansalon/guild/dwarf/log/punish"

string *punishlist = ({ });

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
      "members may also 'forsake' the clan here.\n");

    add_item(({"stone throne","large throne","throne"}),
      "This large stone throne is that used by the Thane of " +
      "the Hill Dwarves when he is in audience.\n");
    add_item(({"braziers","brazier"}),
      "Two long copper braziers burn sullenly in the corners " +
      "on either side of the throne, filling the room with " +
      "a dim light.\n");

    add_exit("/d/Ansalon/estwilde/iron_delving/hall1","northwest","@@go_west");

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
	NF("The shadow is missing: Tell a wizard.\n");
  	if(!(sh=clone_object(GUILD_SHADOW))) return 0;

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
	write(why);
    }
    else
    {
	/* Try to add the shadow to the player */
	//   switch (sh->add_occ_shadow(this_player()))
	// ABOVE IS OLD METHOD...
	// MOVED HERE FROM SHADOW CAUSE THE SHADOW DIDN'T LIKE DOING IT
	switch(sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME))
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

/*	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " joined the clan.\n", 500000);
	    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
	      C(TP->query_real_name())+ " joined the mighty clan warriors!\n", -1); */
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
    write("You decide to leave the clan!\n");
    write("You feel the weight of the dwarven ancestors press upon you " +
      "for forsaking the Clan. You feel weakened.\n");
    say(QCTNAME(TP) + " forsakes the clan!\n");
/*    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " left the clan.\n", 500000);
*/
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
//      if (TP->query_real_name() == "kithkanan")
    {
	if(strlen(str))
	{
	    if(!sizeof(obj = parse_this(str, "[the] %l")))
	    {
		notify_fail("Honour which dwarf?\n");
		return 0;
	    }
	    ob = obj[0];
	}

	TP->catch_msg("You honour " +QTNAME(ob)+ " by " +
	  "making " +HIM(ob)+ " an Elder of the clan, and one of your " +
	  "councillors!\n");
	TP->tell_watcher(QCTNAME(TP) + " honours " +QTNAME(ob) + 
	  " by making " +HIM(ob)+ " an Elder of the Neidar clan!\n", TP);
	ob->catch_msg(QCTNAME(TP) + " honours you by declaring you an Elder " +
	  "of the Neidar clan!\n");
	ob->set_bit(3, 4);
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
	    if(!sizeof(obj = parse_this(str, "[the] %l")))
	    {
		notify_fail("Accept who into the clan?\n");
		return 0;
	    }

	    ob = obj[0];
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

    if(!TP->query_prop(AM_SITTING))
    {
	notify_fail("Only the Thane may exile a clan " +
	  "member, and then only while " +
	  "contemplating the decision from his throne!\n");
	return 0;
    }

    if(!str)
    {
	write("Exile who from Iron Delving?\n");
	return 1;
    }

    if(member_array(str, punishlist) >= 0)
    {
	write("You have already banished that person " +
	  "from Iron Delving!\n");
	return 1;
    }


    if(!find_player(str))
    {
	write("That person is not in the realms, but the memory " +
	  "of the Thane is long... the Clan will remember " +
	  "your verdict when the perpitrator next wakes in the Hall of "+
	  "Warriors.\n");
	punishlist += ({str});
	save_object(PUNISH_FILE);
	return 1;
    }

    write("You exile " +capitalize(str)+
      ", who is now in disgrace and may not " +
      "enter Iron Delving until forgiven.\n");
    tell_object(find_player(str),
      "You have been exiled from Iron Delving " +
      "by the Thane and are now in disgrace " +
      "until forgiven.\n");

    find_player(str)->set_bit(3,4);
    find_player(str)->set_bit(3,3);
    return 1;
}

int
forgive_dwarf(string str)
{
    if(!TP->query_prop(AM_SITTING))
    {
	notify_fail("Only the Thane may forgive a " +
	  "clan member, and only then when he sits " +
	  "upon the Throne.\n");
	return 0;
    }

    if(!str)
    {
	notify_fail("Who do you wish to forgive?\n");
	return 0;
    }

    if(!find_player(str))
    {
	notify_fail("That person is not in the realms to " +
	  "be forgiven.\n");
	return 0;
    }

    write("You forgive " +capitalize(str)+
      ".\n");
    tell_object(find_player(str), 
      "You have been forgiven by the Thane " +
      "of the Hill Dwarves, and are once again " +
      "allowed to return to Iron Delving!\n");

    restore_object(PUNISH_FILE);
    punishlist -= ({str});
    save_object(PUNISH_FILE);
    find_player(str)->clear_bit(3,4);
    find_player(str)->clear_bit(3,3);
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
update(string str)
{
    	object sh;
    	int i;
  	object *souls;

    	NF("If you forget yourself, use <update membership>.\n");
  	if (str != "membership")
    		return 0;

  	NF("But you aren't a member!\n");
  	if (!MEMBER(TP))
   		return 0;
    
    //	TP->remove_guild_occ();    
       
        // Update shadow
  //      if (!(sh = CO(GUILD_SHADOW)) || 
    //  		sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)   
       	{
         	write("Couldn't update your membership...please talk to a " +
          		"wiz immediately.\n");
    		return 1;
  	}
  
 	// Add our cmdsoul if it's missing.
  /*	seteuid(getuid(TO));
    	souls = TP->query_cmdsoul_list();
    	for (i = 0; i < sizeof(souls); i++)
    	if (souls[i] = GUILD_CMDSOUL)
          	TP->remove_cmdsoul(GUILD_CMDSOUL);
      	TP->add_cmdsoul(GUILD_CMDSOUL);
      
    
    	TP->update_hooks();
        	    
   */ 	write("Ok.\n");
    	return 1;
}

void
init()
{
    ::init();
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
    add_action(exile_dwarf,"exile");
    add_action(update,"update");
}
