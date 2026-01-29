#include "../default.h"

inherit CVAN_ROOM;
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

#define NUM	sizeof(query_money_types(-1))
#define CLOSED	0

int closed;
object meditate;

void set_up_skills();

void
create_cvan_room()
{
    closed = CLOSED;

    set_short("Wayfarer Guild Training Room");
    set_long("This is the training room for the Wayfarer's Guild. Here you "+
      "can learn some new skills or improve the ones you already have, for a fee. "+
      "A large, intricately woven carpet lies in the center of the room. "+
      "There is an exit leading west, back into the entrance room of the "+
      "guild.\n");

    add_item(({"carpet"}),
      "It looks quite comfortable.\n");

    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop("_room_has_fire", 1);

    add_exit(CVAN + "shop/wayfar_guild", "west");

    create_guild_support();
    create_skill_raise();
    set_up_skills();
}

string
wizinfo()
{
    return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Anth.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_interactive(ob) || !closed)
	return;

    if (ob->query_wiz_level())
    {
	write("\n\nWARNING!\n You shouldn't be here. "+
	  "I'm doing some work on the guild.\n");
    }
    else
    {
	write("The guild is closed. Come back later.\n");
	ob->move(CVAN + "shop/wayfar_guild");
    }
}

void
init()
{
    init_guild_support();
    init_skill_raise();
    ::init();
}

string
close_guild()
{
    if (closed)
    {
	closed = 0;
	return "  **The guild is now open**";
    }

    closed = 1;
    return "  **The guild is now closed**";
}

int query_closed() {return closed;}

string
train_text(int skill)
{
    string what;

    switch(skill)
    {
    case SS_WEP_SWORD:
	what="use a sword";
	break;
    case SS_WEP_AXE:
	what="use an axe";
	break;
    case SS_WEP_CLUB:
	what="use a club";
	break;
    case SS_WEP_KNIFE:
	what="use a knife";
	break;
    case SS_PICK_POCKET:
	what="pick someone's pocket";
	break;
    case SS_HIDE:
	what="hide";
	break;
    case SS_SNEAK:
	what="sneak";
	break;
    case SS_ANI_HANDL:
	what="handle and manipulate animals";
	break;
    case SS_SWIM:
	what="swim";
	break;
    case SS_CLIMB:
	what="climb";
	break;
    case SS_TRADING:
	what="get a good bargain for goods sold";
	break;
    case SS_AWARENESS:
	what="notice things in your environment";
	break;
    default:
	what="do nothing. THIS IS A BUG";
	break;
    }
    return what;
}

void
set_up_skills()
{
    sk_add_train(SS_WEP_SWORD, train_text(SS_WEP_SWORD), 0, 0, 30);
    sk_add_train(SS_WEP_AXE, train_text(SS_WEP_AXE), 0, 0, 30);
    sk_add_train(SS_WEP_CLUB, train_text(SS_WEP_CLUB), 0, 0, 30);
    sk_add_train(SS_WEP_KNIFE, train_text(SS_WEP_KNIFE), 0, 0, 30);
    sk_add_train(SS_PICK_POCKET, train_text(SS_PICK_POCKET), 0, 0, 20);
    sk_add_train(SS_HIDE, train_text(SS_HIDE), 0, 0, 20);
    sk_add_train(SS_SNEAK, train_text(SS_SNEAK), 0, 0, 20);
    sk_add_train(SS_ANI_HANDL, train_text(SS_ANI_HANDL), 0, 0, 30);
    sk_add_train(SS_SWIM, train_text(SS_SWIM), 0, 0, 30);
    sk_add_train(SS_CLIMB, train_text(SS_CLIMB), 0, 0, 30);
    sk_add_train(SS_TRADING, train_text(SS_TRADING), 0, 0, 30);
    sk_add_train(SS_AWARENESS, train_text(SS_AWARENESS), 0, 0, 30);
}
