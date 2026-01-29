/*
 *  Tom Bombadil, the happy fellow
 *  Recoded by Finwe, January 2002
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"

inherit "/std/monster";
inherit "/lib/unique";
inherit KILL_LOGGER;

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/common/monster/tobacco.h"
#include <tasks.h>

#define LILIES_QUEST_NAME 	"lilies"
#define FEATHER_QUEST_NAME  	"new_feather"

string my_long ();
void add_stuff ();

void create_monster()
{
   if (!IS_CLONE) return;

    set_name("tom");
    add_name(({"bombadil"}));
    set_living_name("bombadil");
    set_title("Bombadil");
    set_race_name("man"); 
    set_adj(({"short","happy"}));
    set_long(&my_long ());

    add_prop(CONT_I_WEIGHT,67000);   /*  67 Kg */
    add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
    add_prop(LIVE_I_ALWAYSKNOWN,1);  /* Always known by people */
    add_prop(LIVE_I_QUICKNESS, 150); /* speed up attacks */
    add_prop(LIVE_I_SEE_DARK,	10); /* Night vision. */

            /* STR DEX CON INT WIS DIS */

    set_stats(({ 190+random(25), 
                 210+random(25), 
                 190+random(25), 
                 200+random(25), 
                 170+random(25), 
                 150+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 80+random(20));
    set_skill(SS_WEP_SWORD, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));
    set_skill(SS_PARRY, 80+random(20));
    set_skill(SS_BLIND_COMBAT, 80+random(20));
    set_skill(SS_AWARENESS, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));

    clone_tobacco();
    set_aggressive(0);
    set_attack_chance(0);
    set_alignment(900);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(5);
    set_act_time(5);
    add_chat("Hey merry dol! Derry dol!");
    add_chat("Lighten up, my friend!");
    add_chat("Hey dol! merry dol! ring a dong dillo!");
    add_chat("Don't fear Old Man Willow, he means you no harm!");
    add_chat("Hey diddle-dillo, I'm Tom Bombadillo!");
    add_act("emote dances around merrily.");
    add_act("emote starts sing about the birds in the trees and " +
        "the clouds in the sky.");
    add_act("emote sings about something cheerful.");
    add_act("emote smiles happily and dances around with you.");
    add_act("emote sings about the lovely Goldberry.");
    add_act("emote smiles cheerfully.");

    set_cchat_time(5);
    add_cchat("It is not wise to fight me.");
    add_cchat("Did I do anything wrong?");
    add_cchat("Was it something I said?");
    add_stuff();

// log killers
    set_kill_log_name("bombadil");
   	set_kill_log_size(50000);

// quest
    add_ask(({"quest","help", "quests"}), "Tom says: Thank you " +
        "for asking. I need help getting a new lily for Goldberry, " +
        "and I need a new feather for my hat.\n");
    add_ask(({"lilies","lily", "new lily"}), VBFC_ME("ask_lilies"));
    add_ask(({"feather", "new feather"}), VBFC_ME("ask_feather"));
}

string my_long()
{
    if (notmet_me(this_player())) this_player()->add_introduced("tom");
    return "This is Tom Bombadil. He is a merry fellow with a " +
        "cheerful disposition. He's not quite as tall as human, " +
        "but is not a hobbit. He has bright blue eyes and a long " +
        "beard. His face is as red as a ripe apple and creased " +
        "with hundreds of laugh lines with a long brown beard. " +
        "This happy-go-lucky man can often be found wandering " +
        "around the forest, dancing and singing. Nonetheless, do " +
        "not underestimate him, for he is strong in his own right.\n";
}


void
add_stuff()
{
    object sword, water;
    object hat, boots, shirt, pants;

    FIXEUID;

    sword = clone_object(WEP_DIR+"shortsword");
    sword->move(this_object());

    water = clone_object(OBJ_DIR + "tomdrink");
    water->move(this_object());

    hat = clone_object(ARM_DIR + "hat");
    hat->move(this_object());

    boots = clone_object(ARM_DIR + "boots");
    boots->move(this_object());

    pants = clone_object(ARM_DIR + "pants");
    pants->move(this_object());

    shirt = clone_object(ARM_DIR + "shirt");
    shirt->move(this_object());

    command("wear armours");
    command("wield sword");
}

int
drink_withy_water()
{
    object water;
    {
        if (!present("_withy_water_", TO))
        {
            water = clone_object(OBJ_DIR + "tomdrink");
            water->move(this_object());
            TP->heal_hp(500);
            say("He looks refreshed.\n");
            return 0;
         }
    command("drink liquid");
    return 1;
    }
    return 0;

}


void
check_my_weapon() 
{
    if (!query_skill(SS_UNARM_COMBAT) && !sizeof(query_weapon(-1)))
    {
    set_skill(SS_UNARM_COMBAT, 94);
    map(query_combat_object()->query_attack_id(), cr_reset_attack);
    }
    else
    if (query_skill(SS_UNARM_COMBAT))
    {
    remove_skill(SS_UNARM_COMBAT);
    map(query_combat_object()->query_attack_id(), cr_reset_attack);
    map(query_weapon(-1), update_weapon);
    }
}



int
find_valid_enemy(object foe)
{
    if (ENV(foe) != ENV(TO))   
    return 0;
    if (!sizeof(foe->query_weapon(-1)))
    return 0;

    // Passed all checks.    
    return 1;
}

int
special_attack(object ob)
{
    object *foes, *weapons, *my_weapons, weapon, me;
    int rnd = random(2), x;
    mixed* hitresult, *hit_type;
    string how;

    switch(rnd)
    {
        case 0:
            drink_withy_water();
            return 1;
            break;

        case 1:
            check_my_weapon();

            if (random(7))
            return 0;
            my_weapons = query_weapon(-1);
            weapons = ob->query_weapon(-1);

// If I have no weapon wielded I can't do this attack.
            if (!sizeof(my_weapons))
            {
// Possibly do an unarmed attack here?
                return 0;
            }

// My enemy has no weapon so lets look for another :)
            if (!sizeof(weapons))
            {
                if (!sizeof(foes = filter(query_enemy(-1), find_valid_enemy)))
                    return 0;
                ob = foes[random(sizeof(foes))];
                weapons = ob->query_weapon(-1);
            }

// Sanity check
            if (!sizeof(weapons))
                return 0;
// What weapon are we attacking.
            weapon = weapons[random(sizeof(weapons))];

// Do we hit with this attack?
            if (query_combat_object()->cb_tohit(-1,100,ob) >= 0)
            {
                if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
                {
// See if we are able to break non-magical weapons.
                    if (resolve_task(TASK_DIFFICULT, ({TS_DEX, SS_WEP_POLEARM}), ob,
                        ({SKILL_AVG, TS_DEX, TS_WIS, SKILL_END, SS_PARRY})) >= 0)
                    {
                        ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
                        weapon->short()+" with "+HIS_HER(TO)+" "+
                            my_weapons[0]->short()+" with tremendous force damaging "+
                            "your "+weapon->short()+" beyond repair.\n");
                        tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QTNAME(ob)+
                            "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
                        my_weapons[0]->short()+" with tremendous force damaging "+
                            QTNAME(ob)+"'s "+weapon->short()+" beyond repair.\n", 
                            ({TO,ob}));
                       weapon->remove_broken();
                        return 1;
                    }
                }
                ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
                weapon->short()+" with "+HIS_HER(TO)+" "+
                    my_weapons[0]->short()+" leaving your "+weapon->short()+
                    " somewhat damaged from the blow.\n");
                tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QTNAME(ob)+
                    "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
                my_weapons[0]->short()+" leaving "+QTNAME(ob)+"'s "+
                    weapon->short()+" somewhat damaged by the blow.\n",({TO,ob}));
// The weapon condition gets worse by 1-2 levels.
                weapon->set_dull(weapon->query_dull() + random(2) + 1); 
                return 1;
            }
            else
            {
// we missed so nothing bad happens.. but we better let people
// know we tried to do something.
                ob->catch_tell("The "+query_nonmet_name()+" attempts to strike "+
                    "your "+weapon->short()+" with "+HIS_HER(TO)+" "+
                my_weapons[0]->short()+", but you manage to avoid the blow.\n");
                tell_room(ENV(TO), QCTNAME(TO) + " attemptes to strike "+QTNAME(ob)+
                    "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
                    my_weapons[0]->short()+", but "+QTNAME(ob)+" manages to "+
                    "avoid the blow.\n",({TO,ob}));    
                return 1;
            }
        break;


    }
}

public void give_back(object from, object obj)
{
    command("say This is nice, but I don't need it.");
    write("Tom gives it back to you.\n");
    obj->move(from);
    return;
}


/****************************************************************
 * Quests                                                       *
 ***************************************************************/

/*
 * Gives out lily quest
 */
string ask_lilies()
{
// player asks for quest again while doing it
    if (TP->query_prop(QUEST_LILY_PROP))
    {
    command("say Hey there. Merry Dol! Having a hard time finding " +
        "lilies?");
    command("emote dances around merrily.");
    command("say I think you can find lilies for my fair " +
        "Goldberry if you ");
    command("say try hard enough.");
    command("emote sings a merry tune.");
    return "";
    }

// asks for quest again after completing it
    if (CHECK_QUEST(TP, LILIES_QUEST_NAME))
    {
    command("say Hiho, merry dol! But you have helped me already.");
    command("say Goldberry and I thank you for your help!");
    return "";
    }

// gives out quest
    command("say Goldberry loves her lilies.");
    command("say They are as fair as she.");
    command("say Please help me and find some.");
    command("say She'll be as grateful as can be.");
    command("smile hopefully");

// adds prop to player
    TP->add_prop(QUEST_LILY_PROP,1);

    return "";
}

void test_lily (object player, object obj)
{
  // Is doing the quest ?
  if (player->query_prop(QUEST_LILY_PROP))
  {
    // Did this before ?
    if (!REWARD_QUEST(player, LILIES_QUEST_NAME))
    {
      command("say Thank you for the lily, but you have helped me before.");
      return;
    };

    command("emote dances around gleefully.");
    command("say Oh, thank you, thank you, the lilies are " +
            "just beautiful!");
    command("say My Goldberry, she is gone right now.");
    command("say But I know her face will light up when I " +
            "tell her you brought them for her!");
    player->remove_prop(QUEST_LILY_PROP);
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");
    return;
  };

  // Not doing the quest ...
  command("say This is a nice item, but why give it to me?");
  command("drop " + OB_NAME (obj));
}

/*** End of lily quest ******************************************/

/*
 * Gives out new feather quest
 */
string ask_feather()
{
    if (TP->query_prop(QUEST_FEATHER_PROP))
    {
    command("say Merry dol! I didn't think you'd have a hard time.");
    command("emote dances around merrily.");
    command("say Try harder, I know you can do it!");
    command("say Go, try again!");
    command("emote sings a merry tune.");
    return "";
    }

    if (CHECK_QUEST(TP, FEATHER_QUEST_NAME))
    {
    command("say Hiho, merry dol! But you have helped me already.");
    command("say Thanks for the feather!");
    return "";
    }

    command("say The feather in my hat is looking a little old.");
    command("say Getting a good one is difficult sometimes.");
    command("say Please help me and get a pheasant feather.");
    command("say They are one of my favorites!");
    command("smile hopefully");

    TP->add_prop(QUEST_FEATHER_PROP,1);

    return "";
}

void test_feather (object player, object obj)
{
  // Is doing the quest ?
  if (player->query_prop(QUEST_FEATHER_PROP))
  {
    // Did this before ?
    if (!REWARD_QUEST(player, FEATHER_QUEST_NAME))
    {
      command("say Thank you for the feather, but you have helped me before.");
      return;
    };

    command("emote dances around excitedly.");
    command("say Oh, thank you, thank you!");
    command("say It looks beautiful!");
    command("say I shall take it home, clean it, and wear it tomorrow!");
    player->remove_prop(QUEST_FEATHER_PROP);
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");
    return;
  };

  // Not doing the quest ...
  command("say This is a nice item, but why give it to me?");
  command("drop " + OB_NAME (obj));
}
/*** End of new feather quest ***********************************/

public void
enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);

  if (!living(from)) return;

  // If the object is a lily, test for lily quest.
  if (obj->id(LILY_PROP)) 
  {
    set_alarm (2.0, 0.0, &test_lily(from, obj));  
    return;
  };
    
  // If the object is a feather, test for feather quest.
  if (obj->id(FEATHER_PROP)) 
  {
    set_alarm (2.0, 0.0, &test_feather(from, obj));  
    return;
  }

  // Thanks, but give the item back to player. we don't want it.
  set_alarm(2.0,0.0, &give_back(from, obj));
}

/*
public int
volume_left()
{
    command("say I just got a call to volume_left() from the object " + file_name(calling_object()) + "\n");
    return ::volume_left();
}
*/