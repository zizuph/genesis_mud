/*
 * roamer.c
 *
 * A generic file for the roaming halflings of Dabaay to inherit.
 * Goldberry, November 1999
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <money.h>

string *humans   = ({"knee", "shin", "leg", "ankle"}),
       *helves   = ({"thigh", "knee", "leg", "shin"}),
       *elves    = ({"thigh", "groin", "knee", "leg"}),
       *dwarves  = ({"groin", "chest", "thigh", "stomach"}),
       *goblins  = ({"throat", "chest", "face", "nose", "mouth"}),
       *kender   = ({"ear", "face", "nose", "mouth", "chest"}),
       *gnomes   = ({"nose", "nose", "face", "mouth", "ear"}),
       *hobbits  = ({"nose", "face", "mouth", "ear"}),
       *halflings= ({"nose", "face", "mouth", "ear"}),
       *kobolds  = ({"mouth", "eye", "mouth", "throat"}),
       *ogres    = ({"toes", "ankle", "shin", "foot"}),
       *giants   = ({"toes", "ankle", "shin", "foot"}),
       *orcs     = ({"chest", "stomach", "gut", "leg"}),
       *generics = ({"midsection", "leg", "body"}),
       *horses   = ({"chest", "foreleg", "body", "nose"}),
       *wolves   = ({"head", "nose", "ear", "throat"});

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    string *chats =
        ({
"Aye, the breeze be carrying a good smell today.",
"I wonder how my 'taters are getting on.",
"Those dang mutts done tore up my cabbage again!",
"Ol' Shan sure paid a pretty penny for those penguins I caught.",
"That crazy ol' coot of a Mayor has done run off again.",
        });
    
    return chats;
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    int i;
    string *chats;
    
    ::create_monster();
       
    set_gender(MALE);
    set_alignment(100);

    set_spell_prop(TO);
   
    set_act_time(30);
    add_act(({"wink amusedly", "ponder"}));

    chats = query_chats();
    set_chat_time(10);
    for (i = 0; i < sizeof(chats); i++) 
        add_chat(chats[i]);
    
    set_cchat_time(1);
    add_cchat("I'm gonna slap you so hard you'll be calling me Ike!");
    add_cchat("Oho! You're no better than those sniveling stink-dogs!");
    add_cchat("Seems to me you be in need of a good larnin'!");
    add_cchat("If you keep talking to me like a wench, I'm gonna keep "+
              "slapping you like a wench!");
    
    add_prop(NPC_I_NO_FEAR, 1);
}

/*
 * Function name: spell_attack
 * Description:   This is called by the combat system.
 * Arguments:     me -    This object
 *                enemy - The enemy we are fighting.
 */
public int
spell_attack(object me, object enemy)
{
    mixed *hitresult;
    string how;
    string where;
    string target;
    int hurt;
    int damage;
    int intox, tox;
    object wuss;
    intox = enemy->query_intoxicated();
    tox = intox/3 + 5;

    hurt = F_PENMOD(tox + (query_stat(SS_STR) + query_stat(SS_DEX))/3,
                    tox + random(2*query_skill(SS_UNARM_COMBAT))/3);
    
    hitresult = enemy->hit_me(hurt, W_BLUDGEON, TO, -1);

    how = "barely tickled";
    where = "in the midsection";
  
    target = enemy->query_real_name();
    
    switch(hitresult[0])
    {
        case 0..10 :
            command("shout Here it comes!");
            how = "slapped hard";
            break;
        case 11..20:
            command("say to "+ target +
                    " Next lesson: how to take a hit!");
            how = "smacked good and hard";
            break;
        case 21..30:
            command("shout Body blow!");
            how = "struck convincingly";
            break;
        case 31..35:
            command("say Uppercut!");
            how = "beat hard";
            break;
        case 36..40:
            command("shout All too easy!");
            how = "thumped loudly";
            break;
        case 41..50:
            command("say to " + target +
                    " You best be running now.");
            how = "walloped nicely";
            break;
        case 51..65:
            command("say Smells like something's dying here....");
            command("smell " + target + " suspiciously");
            command("say Yep, I was right.");
            how = "brutally crushed";
            break;
        case 66..80:
            command("shout Not some! Not half! But all of my cash!");
            how = "pimp-slapped";
            break; 
        case 81..1000:
            command("shout Say good-night chump!");
            how = "pounded viciously";
            break;
        default:
            command("say Something peculiar here....");
            how = "slapped silly";
            break;
    }
 
    switch(enemy->query_race_name())
    {
        case "human":
            where = "in the " + humans[random(sizeof(humans))];
            break;
        case "half-elf":
            where = "in the " + helves[random(sizeof(helves))];
            break;
        case "elf":
            where = "in the " + elves[random(sizeof(elves))];
            break;
        case "dwarf":
            where = "in the " + dwarves[random(sizeof(dwarves))];
            break;
        case "goblin":
            where = "in the " + goblins[random(sizeof(goblins))];
            break;
        case "gnome":
            where = "in the " + gnomes[random(sizeof(gnomes))];
            break;
        case "kender":
            where = "in the " + kender[random(sizeof(kender))];
            break;
        case "hobbit":
            where = "in the " + hobbits[random(sizeof(hobbits))];
            break;
        case "halfling":
            where = "in the " + halflings[random(sizeof(halflings))];
            break;
        case "kobold":
            where = "in the " + kobolds[random(sizeof(kobolds))];
            break;
        case "ogre":
            where = "in the " + ogres[random(sizeof(ogres))];
            break;
        case "giant":
            where = "in the " + giants[random(sizeof(giants))];
            break;
        case "orc":
            where = "in the " + orcs[random(sizeof(orcs))];
            break;
        case "horse":
            where = "in the " + horses[random(sizeof(horses))];
            break;
        case "wolf":
            where = "in the " + wolves[random(sizeof(wolves))];
            break;
        default:
            where = "in the " + generics[random(sizeof(generics))];
            break;
    }

    tell_watcher(QCTNAME(TO) + " charges in at " + QTNAME(enemy) + "!\n",
                 enemy, enemy);
    tell_watcher(QCTNAME(enemy) + " is " + how + " " + where +
        ".\n", enemy, enemy);

    enemy->catch_msg(QCTNAME(me) + " charges in at you!\n");
    enemy->catch_msg("You are " + how + " " + where + ".\n");
    
    wuss = query_smallest_enemy();
    if (wuss != query_attack())
        command("kill " + wuss->query_real_name());
    if(enemy->query_hp() <= 0)
    {
        enemy->do_die(TO);
        command("shout Get back up! I ain't through with ya!");
        command("kick corpse");
    }
    if(random(10)>5)
    {
        set_stuffed(TO->eat_max());
        command("emote pulls out a bit of hardtack and begins to "+
                "munch on it thoughtfully.");
    }
    set_alarm(itof(10 + random(20)), -1.0, "set_spell_prop", TO);    
    return 1;
}

public void
notify_spell_enemy_gone(object enemy)
{
    set_alarm(itof(10 + random(20)), -1.0, "set_spell_prop", TO);    
}
