/**********************************************************************
 * - captain.c                                                      - *
 * - Captain of the Bella Diaz                                      - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Updated by Damaris@Genesis 08/2005                             - *
 **********************************************************************/
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/captain";
inherit "/d/Khalakhor/lib/knowledge_base";
#include "local.h"
#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h>
 
public void
create_monster()
{
	set_name("kristo");
	add_name("_kristo_");
	add_name("captain");
	add_name("macduff");
        set_living_name("kristo");
        set_race_name("human");
        add_adj(({"muscular","red-bearded"}));
        set_title("MacDuff, Captain of the Bella Diaz");
        set_long("This red-bearded ship captain is one of the most "+
        "muscular men you have ever met, the normal dangers of "+
        "ocean-going not affecting his serene and peaceful face. "+
        "He seems to be a quiet but very adept fellow who loves his "+
        "work, sailing this modest but impressive ship, the Bella "+
        "Diaz.\n");
        
        set_stats(({ 90, 85, 90, 80, 86, 90 }));
        heal_hp(10000);
        set_skill(SS_AWARENESS, 62);
        set_skill(SS_WEP_SWORD, 55);
        set_skill(SS_DEFENCE, 73);
        set_skill(SS_PARRY, 40);
        set_size_descs("tall","thin");
 
        seteuid(getuid());
        MONEY_MAKE_GC(random(5) + 3)->move(this_object());
        MONEY_MAKE_CC(random(100) + 100)->move(this_object());
 
        add_prop(NPC_I_NO_LOOKS, 1);
 
        set_act_time(15);
        add_act("emote gazes out over the waters as if beholding "+
        "a lover.");
        add_act("emote lovingly admires his ship as if it were "+
        "his daughter.");
        add_act("say The seas, the seas, they call to me.");
        add_act("emote rubs his red-bearded chin gazing at the skies.");
        add_act("emote breathes in the salt air deeply.");
        add_act("emote smiles in satisfaction.");
        add_act("emote hums an old celtic tune.");
        add_act("say The south seas are magical.");
        add_act("say I hear tales that that elves have been "+
        "appearing more and more.");
 
        set_default_answer("I'm not sure about that.");
        add_ask(({"khalakhor"}),
        "say Ah, me beloved Khalakhor. The mainland is " +
        "fairly safe, but some of the islands I wouldn't dock at.",1);
        add_ask(({"mainland","continent","main continent"}),
        "say Stay out of the northlands and you'll be fine.",1);
        add_ask(({"islands","surrounding islands"}),
        "say Powerful beings there. Not sure they're mortal.",1);
        add_ask(({"beings"}),
        "say Don't worry, we'll not be landing on the islands if "+
        "the winds are with us.",1);
        add_ask(({"ocean"}),
        "say The ocean is like a wife, lover, sister, my best friend.",1);
        add_ask(({"north","northlands"}),
        "say Evil abounds in the north. Pray ye never wreck there.",1);
        add_ask(({"route"}),
        "say Port Macdunn to SaMorgan and back, around the southwestern "+
        "and southeaster speirs of Khalakhor.",1);
        add_ask(({"samorgan"}),
        "say It's a small village but lately there has been a lot "+
        "of visitors.",1);
        add_ask(({"port macdunn","port","macdunn","town"}),
        "say The big city on the west coast of the speir.",1);
        add_ask(({"bella diaz","boat","ship"}),
        "say Aye, she's beautiful isn't she? Like me lover she is.",1);
        add_ask("destination","@@query_destination",1);
        add_ask(({"Kheldour","kheldour"}),
        "say Kheldour is an elven city at the tip of the southeastern "+
        "speir of the continent of Khalakhor. Its ports are closed.",1);
        add_ask(({"Rhemouth","rhemouth"}),
        "say Rhemouth is a dwarven city on the east coast of the meidh. "+
        "Its a very old and dangerous place, where chaos and order "+
        "battle constantly.",1);
        add_ask(({"meidh","speir"}),
        "say The continent is formed of three speirs, like pinwheel, "+
        "which radiate from the central highlands of the meidh.",1);
        add_ask(({"isles"}),
        "say You never know what you'll find on the isles. I hear "+
        "Eil-Galaith is on Galaith isle.",1);
        add_ask(({"eil-galaith", "sanctuary"}),
        "say I heard Eil-Galaith is what the elves are calling "+
        "sanctuary. Something about a tower..",1);
        add_ask(({"tower"}),
        "say Well I'm not so sure. Maybe you mean that tower the elves "+
        "are calling Sanctuary Tower.",1);
        add_ask(({"sanctuary tower"}),
        "say Well I'm no elf, but I heard they call it Eil-Galaith.",1);
        
        set_ticket(TICKET);
        set_price(PRICE);
}
 
public int buy(string str)
{
	if (this_player()->query_average_stat() < 20)
	{
		command("say to " + OB_NAME(this_player()) + " No "+
		"need to pay. Little ones ride for free.");
		notify_fail("");
		return 0;
	}
	return ::buy(str);
}
 
public string query_destination()
{
	if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM))) == ("/d/Khalakhor/ship/macdunn/pier4"))
	{
		return ("say We're headed to Port MacDunn matey.");
	}
	if((file_name(this_object()->query_prop(LIVE_O_LAST_ROOM))) == ("/d/Khalakhor/sw_speir/samorgan/pier/pier1306"))
	{
		return ("say We're headed to SaMorgan matey.");
	}
	else return ("say I'm not sure matey, but I think we're headed "+
	"to SaMorgan or Port Macdunn.");
}
 
public void arm_me()
{
	object wep, arm1, arm2, arm3;
	wep=clone_object(PARENT + "common/wep/claymore");
        wep->move(this_object());
        arm1=clone_object(PARENT + "common/arm/vest_hard_leather");
        arm1->move(this_object());
        arm2=clone_object(PARENT + "common/arm/breeches");
        arm2->move(this_object());
        arm3=clone_object(PARENT + "common/arm/belt");
        arm3->move(this_object());
        command("wield all");
        command("wear all");
        command("lace vest");
}
 
public void add_introduced(string who)
{
	kb_add_introduced(who);
}
 
public void init_living()
{
	::init_living();
        kb_init_living();
}
 
public void enter_env(object to, object from)
{
	::enter_env(to, from);
        kb_enter_env(to, from);
}
