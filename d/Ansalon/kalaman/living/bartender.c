#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/local.h"

inherit AM_FILE

#define MAXLIST 30

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("barkeeper");
    set_race_name("dwarf");
    set_short("dwarven barkeeper");
    set_long("This stout dwarf is the barkeeper on this inn. He doesn't look pleased " +
      "with the fact that he has had to close his inn, but makes use of his time " +
      "by cleaning stubborn areas of his bar.\n");

    set_stats(({55,30,70,40,40,50}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_AXE, 40);

    set_act_time(5);
    add_act("emote rubs the bar vigorously with a rag, cleaning it of stubborn spots.");
    add_act("say By Reorx I hate goblins!");

    set_default_answer("The barkeeper says to you: What sort of a question is that?\n");

    add_ask(({"store","cave","equipment"}),VBFC_ME("cave_list"));
    add_ask(({"goblin steaks","steaks"}),VBFC_ME("goblin_hint"));
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(KWEAPON + "notched_axe")->move(TO,1);
    command("wield all");
}

string
cave_list()
{
    object *item_arr;
    int i, max;
    string str;

    item_arr = all_inventory(find_object("/d/Ansalon/estwilde/iron_delving/cave2"));


    if(!P("ansalon_rune_object",TP)
      && !TP->query_guild_member("Dwarven Warriors of the Neidar Clan"))
    {
	command("peer suspicious " +TP->query_real_name());
	command("emote replies loftily: Ain't none of your business!");
	return "";
    }
    if(!sizeof(item_arr))
    {
	command("whisper " +TP->query_real_name()+
	  " Sorry my friend, nothing stored away.");
	return "";
    }

    command("emote peers around suruptitiously.");
    command("whisper " +TP->query_real_name()+
      " Axes high to ye! Lessee, stored away in " +
      "the cave is:");

    max = MIN(MAXLIST, sizeof(item_arr));
    for (i = 0; i < max; i++)
    {
	str = sprintf("%-1s",capitalize(LANG_ASHORT(item_arr[i])));
	command("whisper " +TP->query_real_name() +
	  " " +break_string(str+ "...",75));
    }
    command("say ...and thats about it.");
    command("wink sly");
    return "";
}

string
goblin_hint()
{
    if(TP->query_race() == "dwarf")
    {
	command("say Greetings fellow dwarf!");
	command("say I gather ye have heard of me speciality, goblin steaks!");
	command("grin hungrily");
	command("say Bring me a corpse of one of those skum, and " +
	  "i'll cook you up one.");
	command("wink sly");
	return "";
    }
    command("say What about goblin steaks? You want one? Make it " +
      "yourself.");
    return "";
}

void
attack_func(object enemy)
{
    if (enemy->query_race_name() == "goblin" || enemy->query_race_name() == "hobgoblin")
    {
	command("shout Goblin filth! I'm going to make steak out of ye!");
    }
    command("kill "+enemy->query_real_name());
}

void
init_living()
{
    if (TP->query_race_name() == "goblin" || TP->query_race_name() == "hobgoblin")
	set_alarm(0.5, 0.0, "attack_func", TP);
    ::init_living();
}
