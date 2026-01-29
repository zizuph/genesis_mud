#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pirates/local.h"

inherit AM_FILE
inherit "/lib/unique";


static mapping banned_pressgangers = ([]);

int flags = 0;

void give_flags();
string make_press();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("ramerez");
    set_title("Yellowbeard, the trainer of the Pirates of the Bloodsea");
    set_race_name("human");
    set_adj("yellow-bearded");
    add_adj("one-legged");
    set_gender("G_MALE");
    set_long("You stand before a tall weatherbeaten human. " +
      "This white-yellow hair and beard are complete tangled together " +
      "and stained with bits of food and blood. One of his legs has " +
      "been replaced with a wooden one, and every time he walks around, " +
      "a loud hollow thump can be heard.\n");

    set_stats(({200, 130, 160, 100, 90, 160}));

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS, 140);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_alignment(-600);
    set_all_hitloc_unarmed(25);
    set_act_time(9);
    add_act("emote walks around in a small circle.");
    add_act("emote goes gar.");
    add_act("say You better start training those skinny arms, mate.");
    add_act("say How about some nice imported roke beer, just give me a gold coin, and I will give you "+
      "five beers.");
    add_act("say How about some nice imported roke beer, just give me a gold coin, and I will give you "+
      "five beers.");
    add_act("say How about a real pirate drink? Just give me a platinum coin, and I will give you "+
      "a nice bottle of grog.");
    add_act("say How about a real pirate drink? Just give me a platinum coin, and I will give you "+
      "a nice bottle of grog.");
    set_cact_time(0);
    set_introduce(1);
    add_cact("say Ahh, a brawl, like in the good old days.");
    add_ask(({"Jolly Roger", "flag", "flags", "for flag", "for flags", "for Jolly Roger"}), give_flags ,1);
    add_ask(({"press ganger", "Press Ganger", "Press ganger"}), "say If you are an experienced pirate " +
              "and you have what it takes to lure some landlubbers to join our crew, just ask me to " +
              "become a press ganger.", 1);
    add_ask(({"become press ganger", "make me a press ganger", "become a press ganger"}), make_press, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
}


void reset_flags()
{
  flags = 0;
}

string give_flags()
{
  if(flags>3)
  {
    set_alarm(1800.0, 0.0, &reset_flags());
    return "emote complains: But I don't have any more flags.";  
  }
  flags = flags +1;

  command("emote bellows: Avast! It's shameful!  Yer lot become such lily-livered pansies!");
  command("emote complains: Should be strung up from the yardam for it. "+
          "But ok... I give you these here flags.  It's the Jolly Roger.");
  command("emote continues: Go plant them in the ground after you raid.  You may also "+
          "want to terrorize the landlubbers by waving it.");
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  clone_object("/d/Ansalon/guild/pirates/obj/flag")->move(this_player(), 1);
  this_player()->catch_msg(QCTNAME(this_object()) +" gives you 10 Jolly Rogers.\n");
  tell_room(environment(this_object()), QCTNAME(this_object())+" gives "+QTNAME(this_player())+
            " 10 Jolly Rogers.\n", this_player());
  return "";
}

string make_press()
{
    string player;

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        return "say What are you doing in here, you aren't one of the crew!";
    }

    // See if the player is already a press ganger.
    if(PADMIN->query_pressganger(this_player()) ||
       PADMIN->query_firstmate(this_player()))
    {    
        return "emote raises an eyebrow and says: But you are already capable of recruiting new pirates " +
               "you drunken oaf.";
    }

    // If the king is asking, don't let him become a press ganger.
    if(PADMIN->query_pirate_king(this_player()))
    {
        return "emote says: What barrel of grog did you wake up in this morning. " +
               "As the king you are already capable of enlisting new recruits!";
    }

    // We require some experience for the player to enlist as a pressganger himself.
    if(this_player()->query_guild_level_lay() < 13)
    {
        return "emote points out: You are not experienced enough to take " +
               "on such responsibility yet young laddy.";
    }

    seteuid(getuid(TO));
    banned_pressgangers = restore_map(BAN_PRESSGANGER_FILE);
    // Check if this person has been banished from being a press ganger before
    player = banned_pressgangers[this_player()->query_real_name()];
    if(player)
    {
        return "emote explains: Unfortunately I have been ordered not " +
               "to let you take on this responsibility.";
    }

    PADMIN->add_pressganger(this_player());

    this_player()->catch_tell("\n\nCongratulations! You have be designated "+
                             "to recruit new pirates!\n"+
                             "You can now use the 'vote' command in the pirates "+
                             "join room.\n\n");
    return "say Very well, I hereby grant you the privilege to bring in more people " +
           "for the crew!";
}

void
return_beer(object from)
{
    object beer1,beer2,beer3,beer4,beer5;
    string who, what;

    beer1 = clone_object(GUILD_OBJ+"beer");
    beer1->move(TO);
    beer2 = clone_object(GUILD_OBJ+"beer");
    beer2->move(TO);
    beer3 = clone_object(GUILD_OBJ+"beer");
    beer3->move(TO);
    beer4 = clone_object(GUILD_OBJ+"beer");
    beer4->move(TO);
    beer5 = clone_object(GUILD_OBJ+"beer");
    beer5->move(TO);

    who = from->query_real_name();
    command("grin");
    command("say Excellent! More treasure I can bury.");
    command("give beers to " + who);
}



void
return_grog(object from)
{
    object grog;
    string who, what;

    grog = clone_object(GUILD_OBJ+"grog");
    grog->move(TO);

    who = from->query_real_name();
    command("grin");
    command("say Excellent! More treasure I can bury.");
    command("give grog to " + who);
}

void
recycle_bottle(object ob, object from)
{
  command("say Erh.. Riiiiiight, you are part of that 'Keep the forest clean' project.");
  command("emote rolls his eyes in exasperation."); 
  ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
	return;

    if(ob->short() == "a gold coin")
    {
	set_alarm(1.0, 0.0, &return_beer(from));
	return;
    }
    else if(ob->short() == "a platinum coin")
    {
	set_alarm(1.0, 0.0, &return_grog(from));
	return;
    }
    else if(ob->short() == "empty bottle of grog")
    {
        set_alarm(1.0, 0.0, &recycle_bottle(ob,from));
        return;
    }
    else
    {
	TO->command("peer");
	TO->command("say This is not a gold coin you landlubber!");
	TO->command("say But thanks for the gift.");
    }    
}

