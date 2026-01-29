#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("herl");
    set_adj("ancient");
    add_adj("white-bearded");
    set_race_name("dwarf");
    set_long("This ancient white-bearded dwarf is the historian " +
      "and wise man of Iron Delving. He is probably full of information " +
      "on the Neidar Clan, and many other things.\n");

    set_stats(({55,30,70,40,40,50}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_AXE, 40);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(5);
    add_act("say By Reorx my bones are sore...");
    add_act("emote grumbles about the weather.");
    add_act("emote notes something in his book.");

    set_cact_time(5);
    add_cact("say I remember when the youth of today respected " +
      "their elders!");
    add_cact("say Very brave! Attack an unarmed, old man!");

    set_default_answer("The ancient dwarf says to you: My memory " +
      "isn't what it once was. Perhaps the answers you seek " +
      "are in my book?\n");

    add_ask(({"clan","neidar clan","joining","join",
	"information","neidar"}),
      VBFC_ME("clan_info"));
}

void
arm_me()
{
    seteuid(getuid(TO));
    command("wield all");
}

string
clan_info()
{
    if(TP->query_race() == "dwarf")
    {
	command("say Greetings fellow dwarf!");
	command("say You're after information about the clan eh?");
	command("cackle");
	command("say Well, everything you need to know is in that " +
	  "book.");
	command("emote points to the book on the desk.");
	return "";
    }
    command("say What you interested in the clan for? You ain't " +
      "no dwarf!");
    command("emote crosses his arms with a loud 'Hmph'!");
    return "";
}

