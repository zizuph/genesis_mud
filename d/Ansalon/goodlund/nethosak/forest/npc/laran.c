/*
 * Navarre Feb 3rd 2008.
 * Who ever coded the Hacchak quest did a check on the
 * wrong quest bit when they gave out the quest.
 * Luckily they did check on the right quest bit before
 * handing out the reward. So the only problem we saw
 * was that certain people couldn't get the quest and
 * was told that they had already done it.
 * This has now been fixed.
 *
 * Added a revelation for the OotS guild - Arman 2017
 */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Krynn/guilds/OotS/defs.h"

inherit "/std/act/action.c";
inherit AM_FILE

string *random_loc = ({MROOM + "forest16", MROOM + "forest89",
                       MROOM + "forest40",MROOM + "forest72",
                       MROOM + "forest34",MROOM + "forest54",
                       MROOM + "forest12",MROOM + "forest51",
                       MROOM + "forest62",MROOM + "forest80"});

int has_been_attacked = 0;
int removed;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

public void
create_krynn_monster()
{
    set_name("laran");
    add_name("woman");
    add_name("witch");
    set_living_name("laran");
    set_race_name("human");
    set_title("the Witch");
    add_adj(({"wise", "old"}));
    set_short("wise old female human");
    set_long("Before you stands the most warty witch you "+
             "have ever seen. She's dressed in some old dirty "+
             "rags, which once were grey, but now they have "+
             "become black. Some of her white hair is hidden "+
             "under a big pointy black hat.\n");
    
    set_stats(({40, 50, 60, 100, 100, 10}));
    set_alignment(1000);
    set_gender(1);
    set_introduce(1);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000); 
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    change_prop(LIVE_I_QUICKNESS, 150);

    clone_object(MWEP +"staff")->move(this_object(),1);
    clone_object(MARM +"hooded_robe")->move(this_object(),1);
    command("wield all");
    command("wear all");
    command("hood robe");

    set_default_answer("emote ignores you.", 1);
    add_ask(({"circle","stones", "gate"}), VBFC_ME("tell_password"));
    add_ask(({"task","quest", "help"}), VBFC_ME("quest_hint"));
    add_ask(({"paladin","paladine","gods","old gods","god"}),
         VBFC_ME("oots_hint"));
}

void
provide_revelation(object player)
{
    if(IS_OOTS(player))
    {
          if(!OOTS_QUERY_REV(player, "divinehammer"))
          {
            player->catch_msg("\n\nAs the old witch talks of times past, you feel " +
                "enlightened by a divine revelation!\n\n\n");
            OOTS_ADD_REV(player,"divinehammer","enlightenment - the order of the divine hammer");  
          }
    }
    return;
}

string
oots_hint()
{
    command("say The Old Gods you ask of?");
    set_alarm(1.5,0.0, &command("sigh sadly"));
    set_alarm(3.0,0.0, &command("say They have been gone, gone a long time."));
    set_alarm(4.5,0.0, &command("say My ancestors once were warriors in the " +
          "service of the Gods of Light before the Cataclysm..."));
    set_alarm(6.0,0.0, &command("say Fighting for an Order know as the Knights " +
          "of the Divine Hammer."));
    set_alarm(7.0,0.0, &command("say The Order vanished with the fall of Istar."));
    set_alarm(7.5,0.0, &command("ponder"));
    set_alarm(8.0,0.0, &provide_revelation(TP));
    return "";
}

string
quest_hint()
{
    /***********************************************************************
     *                  QUEST NR. 1 - Find Hacchak                         *
     ***********************************************************************/
    if(TP->test_bit("ansalon", 0, 4))
    {
        command("say But you already helped me!");
        return "";
    }

    if (TP->query_prop(I_MUST_FIND_JILANS_WEAPON))
    {
        set_alarm(0.5,0.0, &command("say Please find the hacchak, and return it to me."));
        return "";
    }

    command("say A traveller! Welcome to my humble hut.");
    set_alarm(2.0,0.0, &command("say I have been searching for someone like you."));
    set_alarm(6.0,0.0, &command("say A few years ago, a kender friend of mine was "+
                                "attacked and killed here, in this forest. She "+
                                "was a good friend and an impressive fighter."));
    set_alarm(12.0,0.0, &command("say But that was obviously not enough."));
    set_alarm(14.0,0.0, &command("say She was murdered, and a few hours later, I found "+
                                 "her mangled corpse."));
    set_alarm(18.0,0.0, &command("sniff"));
    set_alarm(20.0,0.0, &command("say The murderer took everything from it, including "+
                                 "her magical weapon, a hacchak called 'The Seeker'."));
    set_alarm(24.5,0.0, &command("say I do not know what killed her, but the strange thing was "+
                                 "that there was no footprints at the scene. Perhaps, it "+
                                 "still lurks somewhere deeper inside this forest."));
    set_alarm(30.0,0.0, &command("say Please, find the murderer and the weapon."));
    set_alarm(32.0,0.0, &command("say You shall have your reward once you bring me her weapon, "+
                                 "and I shall have my vengeance."));
    set_alarm(37.0,0.0, &command("say Good luck, adventurer."));
    TP->add_prop(I_MUST_FIND_JILANS_WEAPON, 1);
    return "";
}

string
tell_password()
{
    /***********************************************************************
     *                              QUEST HINT                             *
     ***********************************************************************/
    if(!TP->test_bit("ansalon",0,4) && TP->query_prop(I_MUST_FIND_JILANS_WEAPON))
    {
        set_alarm(2.0,0.0, &command("say Ahh, you found the circle of stones!"));
        set_alarm(6.0,0.0, &command("say That was where the murder happened."));
        set_alarm(12.0,0.0, &command("say That gate leads into the cellar of the house, "+
                                     "but it has been locked for years."));
        set_alarm(13.0,0.0, &command("say I lost the key a few days ago."));
        set_alarm(14.0,0.0, &command("say The last time I had the key, I was on my way to the stream "+
                                     "to catch some fish. I might have lost it there."));
        set_alarm(16.0,0.0, &command("say If you can find it again, you might be able to get "+
                                     "down there."));
        return "";
     }
     return "";
}

void
attacked_by(object ob)
{
    if (has_been_attacked == 0)
    {
        command("shout Attacking an innocent old woman!");
        command("shout Paladin, Master of Law. Aid me in this battle!");
        tell_room(E(TO), "A bright light surrounds the wise old female human!\n");
        set_stats(({130, 160, 130, 190, 180, 120}));
        set_skill(SS_WEP_POLEARM, 100);
        set_skill(SS_PARRY, 100);
        set_skill(SS_DEFENCE, 100);
        TO->heal_hp(20000);
        TO->update_state();
        has_been_attacked = 1;
    }
    ::attacked_by(ob);
}

void
calculate_experience2(object who)
{

    /***********************************************************************
     *                  REWARD: Find Hacchak quest                         *
     ***********************************************************************/

    int xp_base = 13000;

    if(who->test_bit("ansalon", 0, 4))
    {
        this_player()->catch_msg("You've already done this quest!\n");
        return;
    }
    this_player()->catch_msg("You feel much more experienced!\n");
    if(who->query_wiz_level())
    {
       who->catch_msg("xp : " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 4);
    who->remove_prop(I_MUST_FIND_JILANS_WEAPON);

    A_QUEST_LOG("quest","Hacchak quest", who, xp_base);
    return;
}

void
return_weapon(object from)
{
    object herb;
    string who, what;

    who = from->query_real_name();
    command("smile");
    command("say Thank you! Now her death has been avenged");
    command("hmm");
    command("say I think you should keep the weapon. I don't know how to use it anyway.");
    herb->remove_name("_jilans_weapon_");
    command("give hacchak to " + who);
    calculate_experience2(from);
}

void
remove_herb(object ob)
{
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
	return;

    if(ob->id("_jilans_weapon_"))
    {
        ob->remove_name("_jilans_weapon_");
        ob->update_state();
	set_alarm(1.0, 0.0, &return_weapon(from));
	return;
    }
    else
    {
        command("say Thanks for the gift.\n");
    }
    return;
}
