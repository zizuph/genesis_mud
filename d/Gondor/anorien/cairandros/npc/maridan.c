/*
 * /d/Gondor/anorien/cairandros/npc/maridan.c
 *
 * A quest NPC in Cair Andros, he is looking for some help in
 * repairing a broken ballista. He arrives in the room
 * /d/Gondor/anorien/cairandros/basement/ba31 and is looking
 * for the rope /d/Gondor/anorien/cairandros/obj/ca_rope
 *
 * Varian - December, 2020
 */

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c"; 

#include "/d/Gondor/bits.h"
#include "../../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>  
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Gondor/common/lib/logkill.c"

#define TOWN    one_of_list(towns)
#define RANK    one_of_list(ranks)
#define TITLE   TOWN + " " + RANK
#define WEP     weapons[0]->short()

int alarm_id;

string *weapons = ({ AN_WEP_DIR + "ca_sword", AN_WEP_DIR + "ca_mace",
        AN_WEP_DIR + "ca_spear", AN_WEP_DIR + "ca_axe" }); 
string *helmets = ({ AN_ARM_DIR + "ca_helm", AN_ARM_DIR + "ca_helm2" });
string *body = ({ AN_ARM_DIR + "ca_chain", AN_ARM_DIR + "ca_chain2" });
string *shield = ({ AN_ARM_DIR + "ca_shield", AN_ARM_DIR + "ca_shield2" });
string *arms = ({ AN_ARM_DIR + "ca_bracer", AN_ARM_DIR + "ca_bracer2" });
string *legs = ({ AN_ARM_DIR + "ca_greaves", AN_ARM_DIR + "ca_greaves2" });
string *ranks= ({"Fresh Soldier of Cair Andros", "Veteran Soldier of Cair Andros",
        "Soldier of Cair Andros", "Hardened Soldier of Cair Andros"});
string *towns = ({"of Edhellond,", "of Dol Amroth,", "of Linhir,",
        "of Ethring,", "of Minas Tirith,", "of Belfalas,", "of Anfalas,",
        "of Pelargir,", "of Anorien,", "of Lossarnach,", "of Lebennin,",
        "of Lamedon,", "of Thornlin,"});

object rope;

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("maridan");
    add_name( ({"ca_soldier", "guard", "soldier"}) );
    set_race_name("human");
    set_title(TITLE);
    set_adj( ({"lean", "thin-faced"}) );
    set_stats( ({160, 160, 175, 160, 160, 175}), 20);
    set_alignment(1000);

    set_pick_up_team( ({"ca_soldier", "ca_officer"}) );

    int base_skill = query_skill_by_stat(this_object()->query_average_stat());

    set_skill(SS_WEP_SWORD, base_skill);
    set_skill(SS_WEP_AXE, base_skill);
    set_skill(SS_WEP_CLUB, base_skill);
    set_skill(SS_WEP_POLEARM, base_skill);
    set_skill(SS_PARRY, base_skill);
    set_skill(SS_DEFENCE, base_skill);
    set_skill(SS_SWIM, 50);
    set_skill(SS_AWARENESS, 50);

    set_gender(G_MALE);

    set_chat_time(20);
    
    add_chat("If they couldn't give me more time, they could at least " +
        "have given me someone to help!");
    add_chat("I'm sure I can fix this ballista!");
    add_chat("Can anyone help me out here?");
    add_chat("Why am I always the one given these tasks?");
    add_chat("These orcs are getting bolder by the day.");
    add_chat("The armies of Mordor are on the move.");
    add_chat("The forces of the East test us, but Gondor is strong.");
    add_chat("Now that Osgiliath is contested, our job here is even " +
        "more important.");
    add_chat("The orcs may have taken Ithilien, but they will have " +
        "trouble crossing the Anduin!");
    add_chat("My heart is heavy knowing that Osgiliath is nothing " +
        "but ruins now.");
    add_chat("I hear that orcs have met our men in battle near " +
        "Osgiliath.");
    add_chat("I'm very busy here, I have a job to do.");
    add_chat("I only earn a handful of silver for my service here, " +
        "but I am proud to serve Gondor.");
    add_chat("This island is a blessing, the forces of Mordor " +
        "will not find it easy to cross the Anduin with our " +
        "fortress here to guard the ford.");

    set_chat_time(24);

    add_ask( ({"task", "tasks", "quest", "quests"}), VBFC_ME("ask_task") );
    add_ask( ({"help", "job"}), VBFC_ME("ask_help") );
    add_ask( ({"money", "coins", "silver"}), VBFC_ME("ask_money") );
    add_ask( ({"orc", "orcs"}), VBFC_ME("ask_orc") );
    add_ask( ({"mordor", "morgul", "east"}), VBFC_ME("ask_mordor") );
    add_ask( ({"anorien", "gondor", "ithilien"}), VBFC_ME("ask_gondor") );
    add_ask( ({"anduin", "river"}), VBFC_ME("ask_anduin") );
    add_ask( ({"ruins", "battle", "osgiliath"}), VBFC_ME("ask_ruins") );
    add_ask( ({"island", "cair andros", "andros"}), VBFC_ME("ask_island") );
    add_ask( ({"ballista", "broken", "repair"}), VBFC_ME("ask_ballista") );
    add_ask( ({"windlass", "rope"}), VBFC_ME("ask_rope") );

    set_default_answer(VBFC_ME("default_answer"));

    set_act_time(25);

    add_act("emote scratches his chin in thoughtful contemplation.");
    add_act("emote tinkers with the broken ballista.");
    add_act("emote looks in dismay at the frayed rope wrapped around " +
        "the broken windlass.");
    add_act("emote examines a rounded piece of wood that could be useful " +
        "in repairing the windlass.");
    add_act("emote turns to the east and stares off in the distance with " +
        "a grim expression on his face.");
    add_act("emote swings his hands in the air, attempting to swat a fly.");
    add_act("emote pauses to look at you, attempting to assess your " +
        "motives.");
    add_act("brood");
    add_act("cough");
    add_act("greet all");
    add_act("ponder");
    add_act("worry");

    add_object(OBJ_DIR + "torch_tmp", -1 + random(3));

    add_prop(NPC_I_NO_FEAR, 1);
   
    equip(({ 
        one_of_list(weapons),
        one_of_list(helmets),
        one_of_list(body),
        one_of_list(shield),
        one_of_list(arms),
        one_of_list(legs),
    }));
}

public int query_knight_prestige() { return -500; }

string
ask_task()
{
    command("say They told me to fix this ballista!");
    command("sigh");
    command("say I don't suppose you could help me with this?");
    command("smile hopefully");
    return "";
}

string
ask_help()
{
    command("say Well, it seems the windlass of this ballista " +
        "is broken. Maybe if you could help me find a good " +
        "length of rope?");
    return "";
}

string
ask_ballista()
{
    command("say They say the forces of Mordor are on the march, and " +
        "we need this ballista to be ready so we can help defend the " +
        "fortress and the rest of Gondor!");
    command("frown");
    command("say But it seems like the windlass is broken, and I think " +
        "I could fix it in time if you could help me find a length of " +
        "rope!");
    return "";
}

string
ask_rope()
{
    command("say I know there is some rope stored down here somehere, " +
        "but I don't have enough time to grab it myself. Do you think " +
        "you could find some for me? Make sure it doesn't have any " +
        "knots in it however!");
    command("emote fiddles with the broken windlass.");
    command("say If you find some, please just <hand> it to me.");
    return "";
}

string
ask_gondor()
{
    command("say We are in the land of Gondor right now, in the province " +
        "of Anorien to be exact. The evil forces of Mordor have already " +
        "attacked us and stolen Ithilien, the land across the Anduin.");
    return "";
}

string
ask_money()
{
    command("say I have bigger problems than money to worry about.");
    return "";
}

string
ask_orc()
{
    command("say Orcs? They seem to be everywhere these days! " +
        "Hopefully we will be able to kick them out of Ithilien " +
        "soon!");
    return "";
}

string
ask_mordor()
{
    command("say Mordor is a foul land, far to the east.");
    command("frown");
    command("say There are thousands of orcs living there, and men of evil " +
        "heart. Gondor will do everything possible to keep these villains " +
        "from harming innocent people.");
    return "";
}

string
ask_anduin()
{
    command("say The Anduin is also known as the great river, it flows " +
        "around us here in Anorien. On the east side of the river are " +
        "the lands of Ithilien, stolen from us by the foul forces of " +
        "Mordor.");
    command("frown");
    return "";
}

string
ask_ruins()
{
    command("say Alas, the great city of Osgiliath is now nothing but " +
        "a collection of ruins. Still, there are stout men of Gondor " +
        "who remain there to defend the land, and perhaps to rebuild " +
        "it one day.");
    return "";
}

string
ask_island()
{
    command("say The island? It is Cair Andros, our fortress here " +
        "guards the ford across the Anduin.");
    return "";
}


public string
default_answer()
{
   string  answer = one_of_list( ({
        "Well, that isn't something I know much about.",
        "Oh, that's a good question. Unfortunately I don't know.",
        "I really don't know.",
        "You will have to ask someone else about that.",
        "Well, I can't rightly say.",
        "Sorry, that isn't really something I know about.",
        "I don't think I have a good answer for that."}) );
    command("emote looks at you in a thoughtful manner");
    command("say " + answer);
    return "";
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say That was a huge mistake!");
    command("wield all");
    command("wear all");
    command("shout For Gondor!");
    command("light torch");
    /*add_prop(LIVE_O_ENEMY_CLING, obj);*/
}

void
attack_object(object obj)
{
    ::attack_object(obj);
    command("say For Gondor!");
    /*add_prop(LIVE_O_ENEMY_CLING, obj);*/
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

int
hand(string str)
{
    object *items;
    int i;

    notify_fail("Hand what?\n");

    items = FIND_STR_IN_OBJECT(str, this_player());

    if (sizeof(items))
    {   
        if (sizeof(items)>1)
        {
            notify_fail("It looks like he only needs one length of rope!\n");
            return 0;
        }

      if (!items[0]->id("caquest_rope")) 
      {
        notify_fail("You really need to find the proper length of rope.\n");
        return 0;
      }

    seteuid(getuid(this_object()));

    this_player()->catch_msg("You hand over the length of rope.\n");

    if(interactive(this_player()))
    {
        if(this_player()->test_bit("gondor", CANDROS_GROUP, 
            CANDROS_MARIDAN_BIT)) 
        {
            this_player()->catch_msg("You have already helped to repair " +
                "the windlass before!\n");
        }
        else
        {
            this_player()->add_exp(CANDROS_MARIDAN_EXP, 0);
            this_player()->set_bit(CANDROS_GROUP, CANDROS_MARIDAN_BIT);
            this_player()->catch_msg("You feel more experienced!\n");
        }

        say(QCTNAME(this_player())+" hands over a length of rope to help " +
            "repair the windlass!\n");

        if (rope = present("caquest_rope", this_player()))
        {
            rope->remove_object();
        }
    }
    return 1;
}
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
    add_action(hand, "hand");
}

/* Function:         query_my_enemies() : written by Mortricia
 * What's it do:     Creates an array of enemies to be used for randomizing
 */
public varargs object * 
query_my_enemies(int how_to_sort = 0)
{
    int i, j, swap = 0;
    object foo, *all, *enemies = ({ });
    all = all_inventory(environment(TO)) - ({ TO });
    for (i=0; i<sizeof(all); i++) {
        if (living(all[i]) && member_array(TO, all[i]->query_enemy(-1)) >= 0)
            enemies += ({ all[i] });
    }
    if (how_to_sort == 0) return enemies;
    
    for (i=0; i<sizeof(enemies)-1; i++) {
        for (j=i+1; j<sizeof(enemies); j++) {
            switch (how_to_sort) {
                case -1:     /* Sort in decreasing stat order */
                    if (enemies[i]->query_average_stat() <
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                case 1:      /* Sort in increasing stat order */
                    if (enemies[i]->query_average_stat() >
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                default:
                    return enemies;
            }
            if (swap) {
                foo = enemies[i];
                enemies[i] = enemies[j];
                enemies[j] = foo;
                swap = 0;
            }
        }
    }
    return enemies;
}/*query_my_enemies*/

/*
 * Function name: special_attack()
 * Description  : The special attack for soldiers in Cair Andros
 */

int
special_attack(object enemy)
{
    object me = this_object();
    object *enemies = query_my_enemies();
    object kill_enemy;
    int pen;

    mixed *hitresult, *weapons = this_object()->query_weapon(-1);
    
    string how;
    string ohow;
    string tar;

    int     n = -1;

    /* We want this to be hard, so guards randomly switch targets */
    if (!random(9))
    {   
         enemy = enemies[random(sizeof(enemies))];
         kill_enemy = enemy;
         command("kill "+kill_enemy->query_real_name());
    }

    if (random(9))
    {
        return 0;  /* Continue with the normal attacks */
    }

    /* The special, based on average stats. */
    pen = query_pen_by_stat(this_object()->query_average_stat());

    hitresult = enemy->hit_me(query_pen_by_stat(pen) + random(100), 
        W_IMPALE | W_SLASH | W_BLUDGEON, me, -1);

    how = " barely injuring them";
    ohow = " barely injuring you";

    if (hitresult[0] >= 0)

    {
        how = " hurting ";
        ohow = " hurting ";
        tar = " body";
    }

    if (hitresult[0] > 10)
    {
        how = " wounding ";
        ohow = " wounding ";
        tar = " body";
    }

    if (hitresult[0] > 20)
    {
        how = " crippling ";
        ohow = " crippling ";
        tar = " body";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your " + WEP + how + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with his " + WEP + "," + how + ".\n");
 
        tell_watcher(QCTNAME(me) + " strikes out at "+ QCTNAME(enemy) 
            + " with his " + WEP + how + ".\n");

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your " + WEP +
            how + enemy->query_possessive() + tar + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with his " + WEP + "," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "+ QCTNAME(enemy) 
            + " with his " + WEP + "," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);         
            
        if (enemy->query_hp() <= 0);
            enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}