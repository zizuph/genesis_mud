#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#define "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit AM_FILE
#define PLAYER_I_FOUND_WAND "_player_i_found_wand"
#define GIVEN_BEGGAR_FOOD "_given_beggar_food"
#define WAND "/d/Ansalon/balifor/flotsam_forest/obj/wand2"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("human");
    set_race_name("human");
    add_adj("homeless");
    set_short("homeless human");
    set_long("This is one of the poor wretched humans forced out " +
      "of their homes and now living by any means they can. \n");

    set_stats(({15, 15, 60, 15, 15, 15}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-100);

    set_skill(SS_DEFENCE, 5);


    set_act_time(5);
    add_act("say Please, alms for the poor!");
    add_act("emote weeps pitifully.");
    add_act("emote moans in anguish.");

    add_ask("time","say How would I know?");
    add_ask("wand","say How about you grab me some soup? I am starving.",1);
    add_ask(({"cabin boy","boy","kid"}),
      "say What about him? We did a trade, whats it to you?",1);
    add_ask("help","say Please, some soup would be nice. " +
      "You could help a pour soul by getting me some soup.",1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

void
give_wand()
{
    if(TP->test_bit("ansalon",0,12))
    {
      if(this_player()->query_guild_name_occ() == GUILD_NAME &&
         !SOHM_MANAGER->query_scribed_spell(this_player(),"shochraos"))
      {
          command("emote licks his lips.");
          command("say Your are most generous!");
          command("eat all");
          command("emote slops food over himself.");
          clone_object(WAND)->move(TO);
          command("drop wand");
          command("say Oops! Oh well, don't need it. Feel free to take it " +
          "if you want.");
          command("emote shuffles out of the warehouse.");
          remove_object();
          return;
      }
	command("say Thank you! Most grateful!");
	command("eat all");
        command("pat belly");
	return;
    }

    command("emote licks his lips.");
    command("say You have no idea how grateful I am...");
    command("eat all");
    command("emote slops food over himself.");
    clone_object(WAND)->move(TO);
    TP->add_prop(PLAYER_I_FOUND_WAND, 1);
    command("drop wand");
    command("say Oops! Oh well, don't need it. Feel free to take it " +
      "if you want.");
    command("emote shuffles out of the warehouse.");
    remove_object();
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!interactive(from))
        return;

    if(ob->id("coin"))
    {
	command("say Thankyou!");
	command("emote smiles toothily.");
	return;
    }

    if(ob->id("soup"))
    {
	command("twinkle greed");
	set_alarm(1.0, 0.0, "give_wand");
	return;
    }

    return;
}
