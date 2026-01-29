#include "defs.h"
#include "/d/Shire/imladris/guild/guild.h"

create_rivendell_room()
{
    set_short("Guildhall");
    set_long(
	"You have entered the magnificient Guildhall of the Healers of Imladris. "+
	"This is a large hall, but it seems somehow very cosy and inviting. "+
	"On the walls are shelfs after shelfs with tomes and heavy books, "+
	"and on the other side of a long table sits a very old looking elf "+
	"with deep eyes and a white beard.");

    add_item( ({"hall","guildhall"}),
	"This is a wooden hall, and most of the walls and interior seems to\n"+
	"be of animate origin. You feel that this must be a room of importance\n"+
	"since so many books are stored here in the shelfs.\n");

    add_item( ({"books","tomes","book","tome","shelfs"}),
	"As you turn to examine the books, you hear a certain 'Eherm' from\n"+
	"the old elf, suggesting that this was an inappropiate act.\n");

    add_item( ({"elf","old elf","guildmaster", "elwin"}),
	"@@exa_elf");


    add_exit(STAND_DIR + "passage2", "south", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);
}

#define OK_RACES ({ "hobbit", "elf", "human", "dwarf" })

mixed
acceptable(object who)
{
    if (member_array(who->query_race_name(), OK_RACES) == -1)
	return
	    "The wizened elf gazes upon you with an empty stare.\n" +
	    "He says: Sorry, we do not allow " +
	    LANG_PWORD(who->query_race_name()) +" to learn our magic.\n";

    if (who->query_alignment() < 200)
	return
	    "The wizened elf gazes upon you with an empty stare.\n"+
	    "He says: Oh, my poor child who has lost the track of life.\n"+
	    "         Your soul is perverted, and I have no power to release\n"+
	    "         this evil, but with the power of advice. Go now, and\n"+
	    "         may true good and heroic deeds follow your path!\n";
    return 1;
}

string
exa_elf()
{
    string guild;
    mixed reason;

    reason = acceptable(TP);
    if (stringp(reason))
	return reason;

    guild=TP->query_guild_name_occ();
    if(guild==0)
	return
	    "The wizend elf gazes upon you with his cunningly eyes.\n"+
	    "He says: Ah! So you wanted to join the guild of magicians?\n"+
	    "         If you do, you may <join guild>, and you might learn our magic.\n";
    if(guild==GUILD_NAME)
	return
	    "The wizend elf gazes upon you with his cunningly eyes.\n"+
	    "He says: Ah! Nice to see you again, "+TP->query_name()+"!\n"+
	    "         If you wish, you may <leave guild>, but we hope\n"+
	    "         that is not nescessary.\n";
    else return
	    "The wizend elf gazes upon you with cunningly eyes.\n"+
	    "He says: Alas! If you want to join this guild, you can not be\n"+
	    "         a member of the "+guild+" guild.\n";
}

init()
{
    ::init();
    add_action("do_join", "join");
    add_action("do_leave", "leave");
}

do_join(string what)
{
    object shadow, soul, dm;
    int res;

    if (what != "guild")
	return 0;

    if(!acceptable(TP)) {
	write("The old elf says: You can not join this guild.\n");
	return 1;
    }

    if(TP->query_guild_member(GUILD_NAME)) {
	write("The old elf says: But you are already a member of the guild!\n");
	return 1;
    }

    if(TP->query_guild_member(GUILD_TYPE))
    {
	write("The old elf says: You are already a member of another " +
				 GUILD_TYPE + " guild.\n");
	return 1;
    }

    "/d/Shire/imladris/guild/guildob"->new_sula(TP);

    write("The old elf congratulates you with your new guild membership!\n");
    write("The old elf says: Now you are able to learn spells.\n");
    write("                  It may seem difficult at start, but soon you will\n");
    write("                  master the most basic things.\n\n");

    return 1;
}

do_leave(string what)
{
    if (what != "guild")
	return 0;

    if(TP->query_guild_name_occ()!=GUILD_NAME) {
	write("The old elf says: But, you are not a member of our guild!\n");
	return 1;
    }

    if(TP->remove_guild_occ())
    {
	write("The old elf says: Consider yourself no longer a member of this guild.\n");
	TP->clear_bit(1,0);
	return 1;
    }
    else
    {
	write("The old elf goes hmmm.\n");
	write("The old elf says: A failure in the system caused you to stay, I am afraid.\n");
	return 1;
    }
}
