/*
 * Elven Scout - /d/Gondor/rhovanion/dolguldur/npc/scout.c
 *
 * Varian - November 2020
 */

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Shire/common/auto_teaming";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>  
#include <macros.h>
#include <tasks.h>

string physlook();
string emotelook();
string scoutname();

#define WEP     weapons[0]->short()

void
create_monster()
{
   
   set_name( ({scoutname()}) );
   add_name("elf");
   set_adj( ({emotelook(), physlook()}) );
   set_title(", Scout of the Woodland Realm");
   set_long("Tall as a small tree, lithe and immensely strong, " +
      "this elf stands before you firm and resolute in his " +
      "battle against his enemies in Dol Guldur.\n");
   set_race_name("elf");
   set_gender(0);

   set_pick_up_team( ({"scout", "silmelen"}) );

   add_ask( ({"task", "quest", "job"}), VBFC_ME("ask_task") );
   add_ask( ({"amon lanc", "dol guldur", "city"}), VBFC_ME("ask_home") );
   add_ask( ({"orc", "orcs", "mordor"}), VBFC_ME("ask_orc") );
   add_ask( ({"necromancer", "the necromancer", "sauron", "dark lord"}),
      VBFC_ME("ask_necro") );
   add_ask( ({"oropher", "lord", "elven lord", "king"}),
      VBFC_ME("ask_oropher") );
   set_default_answer(VBFC_ME("default_answer"));
   
   add_act("emote peers at the city walls through the trees.");
   add_act("say We shall not allow the Necromancer to establish " +
      "himself once again to settle upon Amon Lanc!");
   add_act("say Orcs have once again settled upon Amon Lanc, " +
      "this cannot be tolerated!");
   add_act("frown");
   add_act("emote wanders around the eastern edge of the " +
      "clearing.");
   add_act("emote sits on the edge of the large flat rock.");
   add_act("emote studies the sky for a long moment.");
   add_act("breathe frustrate");
   add_act("wait impatient");

   set_act_time(10);

   set_skill(SS_WEP_SWORD, 75);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_PARRY, 75);
   set_skill(SS_BLIND_COMBAT, 75);

   set_stats( ({150, 175, 160, 150, 150, 160}), 10);
   
   set_alignment(700);
   
   equip( ({"../wep/elf_sword.c", "../arm/elf_armour.c", 
      "../arm/elf_shield.c"}) );
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}

string
ask_task()
{
    command("say You should ask Silmelen about that, he's the Captain.");
    command("point silmelen");
    return "";
}

string
ask_home()
{
    command("say This is Amon Lanc. That is the rightful name of this " +
      "place, once the heart of the Silvan realm. Then the Necromancer " +
      "came one day. Now men have named it Dol Guldur, the Hill of Dark " +
      "Sorcery.");
    command("sigh deep");
    command("say The Necromancer was forced out during the Battle " +
      "of Five Armies, but orcs from Mordor have come once again in " +
      "an attempt to restore it. I will do everything in my power " +
      "to prevent that from ever happening!");
    return "";
}

string
ask_orc()
{
    command("say Filthy orcs! They destroy everything and leave " +
      "their garbage behind! They have once again come to Amon " +
      "Lanc from Mordor and I shall do everything I can to drive " +
      "them away!");
    return "";
}

string
ask_necro()
{
    command("say The Necromancer. For many years did he live here, " +
      "in the one-time seat of Oropher. His sorcery was terrible, and " +
      "Greenwood the Great became known as Mirkwood. When he was " +
      "driven from here to flee back to Mordor, we all felt relief. " +
      "Yet now his orcs have returned!");
    return "";
}

string
ask_oropher()
{
    command("say Oropher was a great elven lord, King of the Silvan " +
      "Realm. He ruled from Amon Lanc when this forest was known as " +
      "Greenwood the Great. Alas, he fell at the end of the Second " +
      "Age in the Battle of Dagorlad.");
    command("sigh deep");
    command("sat One day, I pray the Dark Lord shall be banished " +
      "for good!");
    return "";
}

public string
default_answer()
{
   string  answer = one_of_list( ({
        "That is not a conversation I have time for right now.",
        "I'm sorry, I do not want to get into that right now.",
        "It is not really my place to say anything about that.",
        "That is a question you should ask to someone else.",
        "No, I don't think I can help you with that."}) );
    command("emote pauses a moment, studying you.");
    command("say " + answer);
    return "";
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

string
scoutname()
{
    string *scoutname;
    scoutname = ({"mindion", "beleron", "aphadon", "felrod", "orodir",
        "silon", "narthedir", "horon", "penedir", "melion", "ferion",
        "bainion", "glerion", "dolthion", "ruindor", "galion", "horthir"});
    return scoutname[random(sizeof(scoutname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"slender", "tall", "grey-eyed", "brown-haired", "lean",
        "lithe", "golden-haired", "strong", "lanky", "wiry"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"stern", "serious", "intense", "silent", "secretive",
        "quiet", "grim", "reserved", "stubborn", "aloof", "taciturn"});
    return emotelooks[random(sizeof(emotelooks))];
}

/* Function:         query_my_enemies() : written by Mortricia
 * What's it do:     Creates an array of enemies to be used 
 *                   for randomizing
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
}
/*query_my_enemies*/

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
    mixed *others = (query_enemy(-1) & all_inventory(environment())) 
        - ({ enemy });
    
    string how;
    string ohow;
    string tar;

    int     n = -1;

    /* We want to randomly switch targets */
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
        W_IMPALE | W_SLASH, me, -1);

    how = " barely scratching them";
    ohow = " barely scratching you";

    if (hitresult[0] >= 0)

    {
        how = " slashing ";
        ohow = " slashing ";
        tar = " body";
    }

    if (hitresult[0] > 10)
    {
        how = " cutting ";
        ohow = " cutting ";
        tar = " body";
    }

    if (hitresult[0] > 20)
    {
        how = " cleaving into ";
        ohow = " cleaving into ";
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

    /*  Important! Should not have two attacks in a round. */
    return 1;
}
/*special_attack*/