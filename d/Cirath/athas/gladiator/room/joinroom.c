/* joinroom.c: The gladiator joinroom: Shiva.
 *     Modified by Serpine: 4-26-95.
 */
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
#include <money.h>


static mapping pricing = ([]);

void
reset_room()
{
    bring_room_mob("kebes", GLAD_NPC+"gladspkr", 1);
}

void
create_room()
{
    set_short("the hall of lost freedom");
    set_long("This chamber is cramped and stuffy. Choking dust fills the "+
      "air and cobwebs line the corners. You can feel a literal "+
      "aura of despair and regret: For this is where brave or "+
      "foolish souls give up their rights as free citizens to "+
      "become one of the Champions of Kalak: The Gladiators of "+
      "Athas. Be it lust for blood or simple stupidity, many "+
      "<enter training> each year, and still more are forced to "+
      "do so as punishment for crime.\n"+
      "In this place you may also <update membership>, and feel "+
      "the noose of slavery, be it of the body or soul, grow ever "+
      "tighter.\n");

    INSIDE
    add_item(({"cobwebs", "cobweb"}), "No slaves seem willing to clean "+
      "here. It brings bad memories.\n");
    add_item("dust", "No great secrets are hidden within.\n");

    add_cmd_item("training", "enter", "Are you certain you are willing "+
      "to make such a sacrifice of blood and freedom? Have you spoken "+
      "to the Speaker of the Gladiators, the Overseers, or others of "+
      "their ilk? Are you just plain mad?\n"+
      "Fools rush in: True Champions size up their targets first.\n"+
      "If you are sure however, then <become slave>.\n");

    add_exit(GLAD_ROOM+"entrance", "east", 0, 1);
    reset_room();
}

int join(string str)
{
    string file;
    object sh;

    NF("Become a what?\n");
    if (str != "slave") return 0;

    NF("You are already a Gladiator!\n");
    if (IS_MEMBER(TP)) return 0;

    NF("You may not give your freedom away while your soul is still "+
      "owned by another occupational guild.\n");
    if (TP->query_guild_member_occ()) return 0;

    NF("The Overseers of the Gladiators have declared you unworthy to "+
      "be among the other warriors here.\n");
    if (CHECK_PUNISHMENT(TP, PUN_BAR)) return 0;

    NF("The Gladiators cast a broken shadow today: Tell a wizard.\n");
    if(!(sh=CO(GUILD_SHADOW))) return 0;

    switch(sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME))
    {
    case 1: 
	write("You throw away your freedom in exchange for blood, glory, "+
	  "and the screams of the arena audience. You are now one of "+
	  "Kalak's Champions!\nGhastly hands reach out from a hole "+
	  "in the ceiling, holding a cuirasse "+
	  "while a tiny child, in the rags of a slave, runs up "+
	  "and steals a piece of your clothing.\n"+
	  "Barely a warrior and already the mysteries begin.\n");
	say("A small child runs up to "+QCTNAME(TP)+" and steals a "+
	  "scrap of clothing. As the child runs away you can see "+
	  "ghastly hands reach out from the ceiling holding a cuirasse "+
	  "and reaching for "+QCTNAME(TP)+"'s neck.\nWhat is going on "+
	  "here?\n");
	break;
    case -4:
	NF("Your other guilds won't let you throw away your freedom so "+
	  "easily. Or perhaps its that you don't have any already.\n");
	return 0;
    default:
	NF("Couldn't join you...please notify a wizard.\n");
	return 0;
    }

    TP->clear_guild_stat(SS_OCCUP);
    TP->setup_skill_decay();
    SET_GBIT(TP, GLAD_MEMBER);

    if (!IS_WIZ(TP) && extract(TP->query_real_name(), -2) != "jr")
    {
	WRITE_LOG(LOG_JOIN, TP, "has just joined the guild.");
	MANAGER->add_member(TP->query_real_name());
    }

    TP->add_cmdsoul(GLAD_SOUL);
    TP->update_hooks();

    CO(GLAD_OBJ + "cuirasse")->move(TP, 1);
    return 1;
}

int update(string str)
{
    object sh, cuir;
    int sk, i, bits;
    string str1, str2, str3, name, file, when;
    mixed tmp;

    NF("To renew your slavery, use <update membership>.\n");
    if (str != "membership")
	return 0;

    NF("But you aren't a member!\n");
    if (!IS_MEMBER(TP))
	return 0;

    TP->remove_guild_occ();

    // Readd bit if its gone.
    if (!TEST_GBIT(TP, GLAD_MEMBER)) SET_GBIT(TP, GLAD_MEMBER);

    // Update shadow
    if (!(sh = CO(GUILD_SHADOW)) || 
      sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
    {
	write("Couldn't update your membership...please talk to a " +
	  "wiz immediately.\n");
	return 1;
    }

    // Add our cmdsoul if it's missing.
    TP->add_cmdsoul(GLAD_SOUL);
    TP->update_hooks();

    // Add a cuirasse if it's missing.
    if (!present(CUIR_ID, TP))
	clone_object(GLAD_OBJ+"cuirasse")->move(TP);

    write("Ok.\n");
    return 1;
}

int
check_leave()
{
    if ((IS_MEMBER(TP)) && (!TEST_GBIT(TP, GLAD_MEMBER)) && (!IS_WIZ(TP)))
    {
	write("You must choose to either update your membership or cease "+
	  "being a gladiator. There is no other option.\n");
	return 1;
    }
    return 0;
}

int
purchase(string str)
{
    int price;

    if (str != "freedom")
	return NF("Perhaps you would like to 'purchase freedom'?\n");

    if (!IS_MEMBER(TP))
	return NF("Only Gladiators may purchase their freedom here.\n");

    if ((price = TP->query_stat(SS_OCCUP)) < 50)
    {
	write("You have not earned the right to purchase your "+
	    "freedom yet.\n");
	return 1;
    }

    price *= MONEY_VALUES[3] * 2;
    price += random(price);

    if (pricing[str = TP->query_real_name()] > price)
	price = pricing[str];
    else
	pricing[str] = price;

    if ((TOTAL_MONEY(TP) < price) || (MONEY_ADD(TP, -price) == 0))
    {
	write("You lack the funds to purchase your freedom.\n"+
	    "Come back when you have more coin.\n");
	return 1;
    }

    write("Your pockets feel much lighter as you purchase your freedom.\n");
    TP->kick_out_glad(1);
    return 1;
}

void init()
{
    ::init();
    add_action(join, "become");
    add_action(update, "update");
    add_action(purchase, "purchase");
}

