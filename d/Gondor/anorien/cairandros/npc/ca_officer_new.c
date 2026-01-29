/*
 * Officers inhabiting the basement in Cair Andros
 * (Thanks to Nerull and Arman for helping
 *  with the special attack)
 *
 * Varian - February, 2020
 */

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Genesis/specials/npc/stat_based_specials.c"; 

#include "../../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>  
#include <macros.h>
#include <tasks.h>
#include "/d/Gondor/common/lib/logkill.c"

#define TOWN    one_of_list(towns)
#define RANK    one_of_list(ranks)
#define TITLE   TOWN + " " + RANK
#define WEP     weapons[0]->short()

int alarm_id;
string physlook();
string emotelook();
string guardname();

string *weapons = ({ AN_WEP_DIR + "ca_sword", AN_WEP_DIR + "ca_mace", 
        AN_WEP_DIR + "ca_spear", AN_WEP_DIR + "ca_axe" }); 
string *helmets = ({ AN_ARM_DIR + "ca_helm", AN_ARM_DIR + "ca_helm2" });
string *body = ({ AN_ARM_DIR + "ca_chain", AN_ARM_DIR + "ca_chain2" });
string *shield = ({ AN_ARM_DIR + "ca_shield", AN_ARM_DIR + "ca_shield2" });
string *arms = ({ AN_ARM_DIR + "ca_bracer", AN_ARM_DIR + "ca_bracer2" });
string *legs = ({ AN_ARM_DIR + "ca_greaves", AN_ARM_DIR + "ca_greaves2" });
string *ranks= ({"Sergeant of Cair Andros", "Corporal of Cair Andros",
        "Sergeant of Cair Andros", "Corporal of Cair Andros",
        "Sergeant of Cair Andros", "Corporal of Cair Andros",
        "Sergeant of Cair Andros", "Corporal of Cair Andros",
        "Sergeant of Cair Andros", "Corporal of Cair Andros",
        "Captain of Cair Andros", "Lieutenant of Cair Andros"});
string *towns = ({"of Edhellond,", "of Dol Amroth,", "of Linhir,",
        "of Ethring,", "of Minas Tirith,", "of Belfalas,", "of Anfalas,",
        "of Pelargir,", "of Anorien,", "of Lossarnach,", "of Lebennin,",
        "of Lamedon,", "of Thornlin,"});
string *lamp = ({ OBJ_DIR + "oil_lamp" });
string *oil = ({ OBJ_DIR + "oilflask" });

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name( ({guardname()}) );
    add_name( ({"ca_officer", "guard", "soldier", "officer"}) );
    set_race_name("human");
    set_title(TITLE);
    set_adj( ({emotelook(), physlook()}) );
    set_stats( ({180, 180, 200, 180, 180, 200}), 20);
    set_alignment(1000);

    set_pick_up_team( ({"ca_soldier"}) );

    int base_skill = query_skill_by_stat(this_object()->query_average_stat());

    set_skill(SS_WEP_SWORD, base_skill);
    set_skill(SS_WEP_AXE, base_skill);
    set_skill(SS_WEP_CLUB, base_skill);
    set_skill(SS_WEP_POLEARM, base_skill);
    set_skill(SS_PARRY, base_skill);
    set_skill(SS_DEFENCE, base_skill);
    set_skill(SS_SWIM, base_skill);

    set_gender(G_MALE);

    set_chat_time(20);
    
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
    add_chat("Please don't bother me right now, I have a job to do.");
    add_chat("I only earn a handful of silver for my service here, " +
        "but I am proud to serve Gondor.");
    add_chat("This island is a blessing, the forces of Mordor " +
        "will not find it easy to cross the Anduin with our " +
        "fortress here to guard the ford.");

    set_chat_time(24);

    add_ask( ({"task", "tasks"}), VBFC_ME("ask_task") );
    add_ask( ({"help", "job"}), VBFC_ME("ask_help") );
    add_ask( ({"quest", "quests"}), VBFC_ME("ask_quest") );
    add_ask( ({"money", "coins", "silver"}), VBFC_ME("ask_money") );
    add_ask( ({"orc", "orcs"}), VBFC_ME("ask_orc") );
    add_ask( ({"mordor", "morgul", "east"}), VBFC_ME("ask_mordor") );
    add_ask( ({"anorien", "gondor", "ithilien"}), VBFC_ME("ask_gondor") );
    add_ask( ({"anduin", "river"}), VBFC_ME("ask_anduin") );
    add_ask( ({"ruins", "battle", "osgiliath"}), VBFC_ME("ask_ruins") );
    add_ask( ({"island", "cair andros", "andros"}), VBFC_ME("ask_island") );

    set_default_answer(VBFC_ME("default_answer"));

    set_act_time(25);

    add_act("emote scratches his chin in thoughtful contemplation.");
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

    add_prop(NPC_I_NO_FEAR,1);
   
    equip(({ 
        one_of_list(weapons),
        one_of_list(helmets),
        one_of_list(body),
        one_of_list(shield),
        one_of_list(arms),
        one_of_list(legs),
        one_of_list(lamp),
        one_of_list(oil),
    }));

}

public int query_knight_prestige() { return -500; }

string
ask_task()
{
    command("say I am too busy with my own task to give you one.");
    command("smile grim");
    command("say The forces of the East have been growing bolder " +
        "and my job here is to help protect Gondor from invasion.");
    return "";
}

string
ask_help()
{
    command("say I am not the right person to ask about that, " +
        "perhaps you could ask someone in Minas Tirith if you " +
        "wanted to help protect Gondor.");
    command("smile help");
    return "";
}

string
ask_quest()
{
    command("say This is no time for quests, the armies of " +
        "Mordor are on the move.");
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
    command("say Let's get some light in here!");
    command("fill lamp with oil");
    command("light lamp");
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

string
guardname()
{
    string *guardname;
    guardname = ({"amalin", "andal", "avendir", "adagil", "auladin",
        "aulendil", "aratamir", "avanwar", "basnir", "belagor",
        "bendir", "bregil", "balisel", "bormil", "beligan", "burundil",
        "cenemir", "cargil", "clendir", "curugan", "cordil", "cerinal",
        "curnil", "carinar", "caniforn", "dranil", "durnir", "dalin",
        "durigal", "druvian", "demigil", "damwar", "donimil", "dentan",
        "endil", "ealenmir", "elovan", "easnil", "eolgan", "elhir",
        "eonwer", "edanvir", "fenelad", "fadil", "fostnar", "falandil",
        "farilan", "falathen", "fiden", "felnos", "fenmir", "furnil",
        "garafel", "grandon", "galmir", "gurdil", "glan", "gandin",
        "galeborn", "govil", "glevanir", "gralorn", "hathor", "hagor",
        "hasmur", "harodil", "halthin", "hamlir", "hestal", "huldir",
        "ideran", "iracandir", "imalan", "inadel", "iorwin", "ivin",
        "lamdon", "lodir", "lameran", "lemrod", "lagund", "lendil",
        "murvin", "magil", "melethar", "modil", "mariadun", "mogir",
        "merithor", "melandor", "malgun", "nagilthor", "naramil",
        "nergan", "naradil", "nilvan", "navadil", "nidal", "nesdil",
        "ondil", "orantir", "otadir", "onmir", "oradan", "onvil",
        "pendil", "piran", "palachor", "prandir", "pawdil", "pegil",
        "regil", "ramdir", "remilar", "runaril", "rogthon", "rulan", 
        "senmir", "sandil", "slanmir", "spegil", "sarmanil", "setil",
        "silandor", "stathor", "tarigan", "turwin", "tandil", "tador",
        "turanmir", "tumandil", "talpen", "tiranir", "talanbur",
        "talenfil", "tormil", "turadon", "tambur", "terfendal",
        "vilamil", "vardil", "vilrod", "verandil", "vidarion"});
    return guardname[random(sizeof(guardname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"towering", "blue-eyed", "grey-eyed", "brown-eyed", 
        "stern", "black-haired", "brown-haired", "grey-haired", 
        "green-eyed", "bald", "balding", "huge", "red-haired", 
        "brown-bearded", "black-bearded", "wiry", "red-bearded", 
        "clean-shaven", "powerful", "brawny", "vigorous", "massive", 
        "husky", "athletic", "stout", "mighty", "agile", "nimble", 
        "swift", "compact"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"surly", "bold", "intense", "angry", "boisterous",
        "resolute", "serious", "obstinate", "stubborn", "gloomy", 
        "somber", "tenacious", "truculent", "stubborn", "ruthless", 
        "glowering", "dire", "imposing", "daunting", "sensible", 
        "honourable", "grinning", "smirking", "beaming", "frowning", 
        "scowling"});
    return emotelooks[random(sizeof(emotelooks))];
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
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

/* Function:         push_out_enemy() : written by Varian, inspired by
 *                   both the anaconda coil in the Holm and Burzum
 *                   in Moria
 * What's it do:     Pushes an enemy out of the room, in particular to
 *                   make things a little more difficult for botters
 */
void
push_out_enemy(object enemy) 
{
    string *exit_cmds;
    string exit, dest;
    int ind;

    exit_cmds = environment()->query_exit_cmds();
    if (!sizeof(exit_cmds))
        return;
  
    ind = random(sizeof(exit_cmds));
    exit = exit_cmds[ind];
    dest = (environment()->query_exit_rooms())[ind];

    if (!objectp(enemy) || environment(enemy) != 
        environment(this_object()))
        return;

    enemy->catch_msg("A flurry of blows rains down upon you, " +
        "pushing you back out and you are forced to flee to " +
        "save yourself!\n");
    tell_room(ENV(enemy), "A sudden flurry of blows forces " +
        QTNAME(enemy) + " back, causing them to flee.\n");
    set_alarm(0.5, 0.0, enemy->move_living(exit, dest, 1));
}
/*push_out_enemy*/

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

    /* We hate botters, let's kick people out of the room on occasion
     * and mess them up. But not too often, don't want to annoy legit
     * players!
     */
    if (random(21) > 19)
    {
        object target = enemy;

        if (random(5) <= 2)
            target = others[random(sizeof(others))];

        push_out_enemy(target);
    }

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
/*special_attack*/