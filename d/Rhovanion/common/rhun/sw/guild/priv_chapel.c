inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/secure/std.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw.h"

init()
{
	::init();
	add_action("answer_prayers","worship");
	add_action("enter_gm_room","e");
	add_action("enter_gm_room","east",0);
}
                      
create_room()
{
	set_short("Private chapel");
	set_long("This is the sacred private chapel."
		+"  Only full members of the Spellweavers are allowed in"
		+" this place.  The room almost vibrates in its unholiness as"
		+" the spirits of darkness wrap themselves around your body,"
		+" intertwining with your soul.  The entire chapel is carved"
		+" from jet-black stone of unknown origins.  At the head"
		+" of the room is an intricately carved statue of a tall figure"
		+" cowled in black, the face hidden from view.  It, too, is made"
		+" from that same unidentifiable dark stone.  You feel the statue"
		+" and the powers behind it watching you as you approach."
		+"  Along the base of the statue are carved hundreds of tiny"
		+" runes.  You may leave the chapel by entering the rune-chamber"
		+" back to the northwest, or a small square room to the west."
		+"  There is also a strange chamber to the east-- it is for"
		+" the Guildmaster and Assistant Guildmasters only."
		+"\n");
	
	add_exit(SWG+"occrune_","northwest",0);
	add_exit(SWG+"armory","west",0);

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 1);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago."
		+"\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
	add_item(({"statue","figure"}),"The figure depicted in this"
		+" dark statue holds a dark, inner power that reaches out to grasp"
		+" at your very soul.  You feel somehow compelled to worship it."
		+"\n");
	add_item(({"rune","runes","base","carving","carvings"}),"The"
		+" runes of power cover the base of this statue.  Even to your"
		+" trained eye, many are indecipherable, having had their meanings"
		+" lost in the eons of persecution that faced the Spellweavers"
		+" of the past.\n");
	
}

answer_prayers(string str)
{
	NF("Worship what?\n");
	if ((str=="statue")||(str=="figure"))
	{
		write("You fall down before the statue,"
			+" worshipping its dark power and the shadows"
			+" which lurk behind it.  In answer to your"
			+" prayers of adoration, a shadowy hand reaches"
			+" out to touch you, and your mind is filled"
			+" with power!\n");
		say(QCTNAME(TP)+"falls down in worship before the statue,\n"
			+" and is touched by the dark powers of the"
			+" Spellweavers.\n");
		TP->set_mana(TP->query_max_mana());
		return 1;
	}
	return 0;
}

int
enter_gm_room()
{
	NF("Only Guildmasters can go there!\n");
	if((TP->test_bit("Rhovanion",0,12))||(TP->test_bit("Rhovanion",0,13))
		||(TP->test_bit("Rhovanion",0,14))
		||((SECURITY->query_wiz_level(TP->query_real_name()))&&
		(TP->query_guild_member(GUILD_NAME))))
	    {
	    TP->move_living("east",SWG+"gm_room",1,0);
	    return 1;
	    }
	else
		return 0;

}

