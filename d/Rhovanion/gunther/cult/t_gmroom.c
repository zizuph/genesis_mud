
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/secure/std.h"
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

init()
{
	::init();
	add_action("ban_player","ban");
	add_action("expel_member","expel");
	add_action("resign_position","resign");
	add_action("reaccept_banned_player","reaccept");
}

create_room()
{
	reset_euid();
	set_short("Room of the Disciples.");
	set_long("This is the private room of the"
		+" Disciples of Melkor. Here they can exercise their"
		+" great powers over the other guildmembers.  Here they"
		+" may <expel> any lower members.  They may <ban> any player from"
		+" entering the unholy guild home, or <reaccept> a previously"
		+" banned player. Additionally, any Disciple may resign from"
		+" his/her/its position by using simply <resign>.  Please"
		+" note that players to be expelled, banned, etc. must"
		+" be in the world at the time the action is performed."
		+" Also, in order to ban, expel or reaccept a player, two"
		+" Disciples must agree to the decision. These commands"
		+" can therefore only be carried out when at least two"
		+" Disciples are in the room. Abuse of these powers will, of course,"
		+" result in the wrath of Melkor with ensuing demotion and possible"
		+" expulsion from the Cult."
		+"\n");

	add_exit(CULT_DIR +"t_med","east",0);

	add_prop(ROOM_I_LIGHT,1);
   add_prop(ROOM_I_INSIDE,1);
}

int
resign_position()
{
	string *names;
	int n, m;
	
	names = allocate(3);
	if(!TP->test_bit("Rhovanion", GM_BIT))
	{
		write("You are no Disciple! Leave this room immediately!\n");
		return 0;
	}

	write("You resign from the position of Disciple of Melkor.\n");
	say(QCTNAME(TP)+" resigned.\n");
		
	for(m = 0; m < 3; m ++)
		if(m == n) names[m] = "none";
		else names[m] = read_file(GMFILE, m + 1, 1);
	rm(GMFILE);
	for(m = 0; m < 3; m++)
		write_file(GMFILE, names[m]+"\n");

	TP->clear_bit(0, 13); /* Always step down completely */
	/* upon startup the shadow must check that the player's name is still in
		the file */
}

int
ban_player(string who)
{
	object ob;
	int n;

	NF("Only Disciples of Melkor can do that!\n");
	if(TP->test_bit("Rhovanion", GM_BIT) == 0 && 
		!(SECURITY->query_wiz_level(TP->query_real_name())&&
                (TP->query_guild_member(CULT_NAME)))) return 0;
   
   /* mortal gms and wiz members can ban */
   NF("Your decision needs to be ratified by another Disciple.\n");
   if(!query_any_other_disciple_here()) return 0;

	NF("Ban whom from entering the guild?\n");
	if(!strlen(who)) return 0;
		
	NF("That player does not exist or is not currently in the game.\n");
	if(!(ob == find_player(who))) return 0;
		
	NF("That player is already banned from entering the guild.\n");
	if(ob->test_bit("Rhovanion", BAN_BIT)) return 0;
		
	write("You ban "+who+" from entering the guild.\n");
	ob->set_bit(BAN_BIT);
	return 1;	
}

int
expel_member(string who)
{
	object ob, odis;
	
	NF("Only Disciples can do that!\n");
	if(TP->test_bit("Rhovanion", GM_BIT) == 0 && 
		!(SECURITY->query_wiz_level(TP->query_real_name())&&
	       (TP->query_guild_member(GUILD_NAME))) return 0;

   NF("Your decision needs to be ratified by another Disciple.\n");
   odis = query_any_other_disciple_here();
   if(!odis) return 0;

	NF("Expel whom from the guild?\n");
	if(!strlen(who)) return 0;
	
	NF("That player does not exist or is not currently in the game.\n");
	if(!(ob=find_player(who))) return 0;
	
	NF("That player is not a member of the Cult of Melkor!\n");
	if(!(ob->query_guild_member(GUILD_NAME))) return 0;
		
	/* See if the member to be expelled is a GM-- if so, they must
	* retire or be fired first.
	*/
	NF("That player is a Disciple and must retire or be replaced"
		+" before being expelled.\n");
		
	if(ob->test_bit("Rhovanion", GM_BIT) > 0) return 0;
		
	TP->catch_msg("You expel "+QCNAME(ob)+" from the Cult of Melkor.\n");
	ob->catch_msg(QCTNAME(TP)+" and " + QCTNAME(odis) + " have expelled you"
		+" from the Cult of Melkor!\n");
		
	/* Death */
	ob->set_hp(0);
	ob->do_die("Expulsion from Cult of Melkor");
		
	/* Remove guild shadow/soul*/
	TP->remove_guild_occ();
		
	/* Removal of skills */
	ob->set_skill(SS_SPELLCRAFT, 0);
	ob->set_skill(SS_FORM_ILLUSION, 0);
	ob->set_skill(SS_FORM_DIVINATION, 0);
	ob->set_skill(SS_FORM_ABJURATION, 0);
	ob->set_skill(SS_ELEMENT_DEATH, 0);
	ob->set_skill(SS_ELEMENT_EARTH, 0);
	ob->set_skill(SS_ELEMENT_WATER, 0);
		
	/* Reset start location if you start here */
	if ((ob->query_default_start_location()) == (CULT_DIR+"t_start"))
	{
		if (ob->query_race_name()=="elf")
			ob->set_default_start_location("/d/Genesis/start/elf/room/begin");
		if (ob->query_race_name()=="dwarf")
			ob->set_default_start_location("/d/Genesis/start/dwarf/lvl1/temple");
		if (ob->query_race_name()=="hobbit")
			ob->set_default_start_location("/d/Genesis/start/hobbit/v/church");
		if (ob->query_race_name()=="goblin")
			ob->set_default_start_location("/d/Genesis/start/goblin/caverns/quarters");
		if ((ob->query_race_name()=="human") ||(ob->query_race_name()=="gnome"))
			ob->set_default_start_location("/d/Genesis/start/human/town/church");
	}
	return 1;
}

int
reaccept_banned_player(string who)
{
	object ob, odis;
	  
	NF("Only Disciples can do that!\n");
	if(TP->test_bit("Rhovanion", GM_BIT) == 0 && 
		!(SECURITY->query_wiz_level(TP->query_real_name())&&
	       (TP->query_guild_member(GUILD_NAME))) return 0;

   NF("Your decision needs to be ratified by another Disciple.\n");
   odis = query_any_other_disciple_here();
   if(!odis) return 0;
		
	NF("Reaccept what banned player?\n");
	if(!strlen(who)) return 0;
		    
	NF("That player does not exist or is not currently in the game.\n");
	if(!(ob = find_player(who))) return 0;
		
	NF("That player was never banned!\n");
	if(!ob->test_bit("Rhovanion", BAN_BIT)) return 0;
		    
	TP->catch_msg("You remove the ban on "+QCNAME(ob)+".\n");
	ob->catch_msg(QCTNAME(TP)+" and " + QCTNAME(odis) + " have released "
		+" the Cult of Melkor ban on you.\n");
	ob->clear_bit(BAN_BIT);
		
	return 1;
}

object query_another_disciple_here()
{
	/* checks to see if another disciple is here and if so return him */
	object *livs;
	int n;
	
	livs = FILTER_OTHER_LIVE(all_inventory(TO));
	for(n = 0; n < sizeof(livs) && !livs[n]->test_bit("Rhovanion", GM_BIT); n++);
	if(n == sizeof(livs) return 0;
	return livs[n];
}	
