#include <ss_types.h>
#include <macros.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

#define FIRST_ADJ	({ "quiet", "happy", "hot-tempered", "comely", \
			"proud", "youthful", "fair", "wary", "spiritual", \
			"strong", "passionate", "lighthearted", "cheerful", \
			"cautious", "alert", "watchful", "ardent" })
#define SECOND_ADJ	({ "brown-skinned", "tattooed", "painted", \
			"dark-haired", "brown-haired", "hazel-eyed", \
			"feather-dressed", "decorated", "black-haired", \
			"muscular", "well-built", "athletic", "sinewy" })

/*
#define KARGONESTI_GODS ({ "Habbakuk, the Blue Phoenix", \
			"Branchala, the Song of Life", \
			"Chislev, the Beast", \
			"Zivilyn, the Tree of Life" })
*/

inherit M_FILE
inherit "/d/Krynn/std/equip";

nomask public void create_krynn_monster()
{
    string *equipment;
    
    setuid();
    seteuid(getuid());

    set_race_name("wilder elf");
    add_name("elf");
    add_name("_kagonesti_elf_");
    set_adj(({one_of_list(FIRST_ADJ), one_of_list(SECOND_ADJ)}));
    set_gender(random(2));
    set_alignment(random(400));
    set_height_desc("short");
    set_whimpy(10);
    set_long("This is a wilder elf of the Kagonesti, a deeply spiritual breed "
        + "that enjoys harmony with nature. They prefer life in wilderness "
	+ "in small villages and are wary of all outsiders. They are much "
	+ "stronger than their elvish cousins and are skilled hunters and "
	+ "warriors.\n");
//    set_stats(({160,165,160,110,135,140}), 25);
    set_stats(({80,85,80,65,65,70}), 25);
    set_skill(SS_DEFENCE,       70);
    set_skill(SS_PARRY,         50);
    set_skill(SS_WEP_POLEARM,   70);
    set_skill(SS_WEP_SWORD,     70);
    set_skill(SS_WEP_MISSILE,	70);
    set_skill(SS_AWARENESS,     70);
    set_skill(SS_UNARM_COMBAT,	50);
    set_skill(SS_BLIND_COMBAT,	40);
    set_skill(SS_2H_COMBAT,     50);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HIDE,          50);
    set_skill(SS_SNEAK,         50);
    set_skill(SS_TRACKING,      80);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    set_random_move(10);
    set_restrain_path(ROOMS);
    set_default_answer("The wilder elf ignores you, clearly not wishing to "
        + "deal with outsiders.\n");
/* Don't really like acts for these elves
    set_act_time(10);
    add_act("rsay Our family members are held by the Silvanesti and Qualinesti"
        + " as slaves, yet they say we are the barbarians!");
    add_act("smile . ");
    add_act("emote closes " + this_object()->query_possessive() + " eyes and "
        + "whispers a prayer to " + one_of_list(KARGONESTI_GODS) + ".");
    add_act("pace .");
    add_act("emote looks around admiringly.");
*/
    set_cact_time(10);
    
    set_knight_prestige(-4);

    equipment = ({ARMOUR + "kagonesti_coat", ARMOUR + "kagonesti_leggings",
        ARMOUR + "kagonesti_boots"});

    switch(random(3))
    {
        case 0:
            equipment += ({WEAPONS + "kagonesti_lightblade"});
            break;
        case 1:
            equipment += ({WEAPONS + "kagonesti_longspear"});
            break;
        default:
            equipment += ({ARMOUR + "kagonesti_aguard",
                ARMOUR + "kagonesti_sglove", WEAPONS + "kagonesti_bow",
                WEAPONS + "kagonesti_arrows", OBJ + "kagonesti_quiver"});
            break;
    }

    if(!random(5))
        equipment += ({ARMOUR + "kagonesti_ring"});

    equip(equipment);

    set_alarm(0.5, 0.0, &command("put arrows in quiver"));
}

void player_left_room(object player, string room, string exit)
{
    if(this_object()->query_attack() == player
        && wildmatch(ROOMS + "*", room))
    {
        int ptotal = player->query_skill(SS_TRACKING)
                + player->query_stat(SS_INT) + player->query_stat(SS_WIS),
            npctotal = this_object()->query_skill(SS_TRACKING)
                + this_object()->query_stat(SS_INT)
                + this_object()->query_stat(SS_WIS);

        if(random(ptotal) < random(npctotal))
            this_object()->command(exit);
        else
            player->catch_tell("You think you have managed to throw "
                + this_object()->query_the_name(player)
                + " off of your trail.\n");
    }
}

public void attacked_by(object ob)
{
    int noshout = 0;
    int error;
    
    if(!this_object()->query_relaxed_from_combat())
        noshout = 1;
    
    ::attacked_by(ob);
    
    if(!noshout)
    {
        this_object()->command("shout We are under attack!");
        foreach(string room : environment(this_object())->query_exit_rooms())
        {
            if(LOAD_ERR(room))
            {
                tell_room(this_object(), "There is a rift in the fabric of "
                    + "time and space. Please write a bug report for this "
                    + "room, and mention that " + room + " is responsible.\n",
                    0, this_object());
                    break;
            }

            foreach(object obj : filter(all_inventory(find_object(room)),
                &->id("_kagonesti_elf_")))
                if(!obj->query_attack())
                {
                    mixed rooms = environment(obj)->query_exit();
                    int i;

                    for(i = 0; i < sizeof(rooms); i += 3)
                        if(file_name(environment(this_object())) == rooms[i])
                        {
                            obj->command(rooms[i + 1]);
                            break;
                        }
                }
        }

        foreach(object obj : filter(all_inventory(environment(this_object())),
            &->id("_kagonesti_elf_")))
        {
            switch(random(10))
            {
                case 0:
                    obj->command("rsay You shall serve as a warning to "
                        + "others!");
                    break;
                case 1:
                    obj->command("explode");
                    break;
                case 2:
                    obj->command("scowl furiously");
                    break;
                case 3:
                    obj->command("emote 's eyes burn with rage.");
                    break;
                default:
                    break;
            }

            obj->command("$kill " +
                OB_NAME(this_object()->query_attack()));
        }
    }
}

public void run_away()
{
    ::run_away();
    this_object()->command("hide");
}

public int query_option(int opt)
{
    if(opt == OPT_NO_FIGHTS)
        return 1;
    else
        return ::query_option(opt);
}
