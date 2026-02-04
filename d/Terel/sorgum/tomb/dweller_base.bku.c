/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * Tomb dweller common code
 *
 * This file should be inherited by all tomb dwellers
 *
 * some code based on the LoD guard and the monsters in
 * Mortricia's haunted house.
 *
 * Sorgum June 1994.
 *
 *  Modified: 29 Apr 2003, by Bleys
 *      - fixed numerous typos
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>

#include "/d/Terel/sorgum/tomb/tomb.h"

#define ARM_DIR  SORGUM_DIR + "armour/"
#define WEP_DIR  SORGUM_DIR + "weapon/"

/*
 * Prototypes
 */

void set_spell_prop(object ob);

/*
 * Global variables
 */

string *chats = ({
"You don't belong here! Get Lost!",
"Killing you would be easy for me.",
"You want to know how much blood juts out of someone's neck when " +
         "his throat's been cut?",
"You want to find out what happenes to an eyeball when " +
         "it's punctured?",
"Have you ever tried to pick up your teeth with broken " +
         "fingers?",
"You would look pretty stupid with my sword sticking out of your ass!",
"What? Do you think you're tough?",
"Are you talking to me?",
"Mess with me and I'll break you in half!",
"You better walk on home, boy.",
"I'll snap your neck like a toothpick!",
"I am the last monster in Genesis that you ever want to mess with!",
"What the hell are you looking at?",
"Open your trap again and I'll nail it shut!",
"I'll bash your ugly head in with the butt of my sword.",
"You want some of this? Come and get it!",
"I eat guys like you for breakfast!",
"I have been training with Benton, and I just keep getting tougher.",
"I know you... you love the killin' but you're an empty shell inside.",
"I'll pulp and splatter your head over a wide area!",
"Dwellers rock!  Even better than Vamps."
});

string *cchats = ({
"Yes! That was almost a critical hit! Next time you'll eat crow for sure!",
"You should have never come back!",
"Keep it up and I'LL SLIT YOUR THROAT!!!",
"I know more ways to kill you than you know ways to die!",
"I hope you brought a body bag! You'll need it.",
"Come on! My grandmother hits harder than that!",
"I own you now! You are mine.",
"Had enough? I'm just getting started.",
"HA! Check your stats buddy, you are losing strength fast!",
"I'll get my friend Benton to kick your ass!",
"I'll get Benton to break you frickin arms!",
"I am going to knock you into next week.",
});

int berzerked = 0;

public int
query_dweller_level()
{
    return 1;
}

public void
go_berzerk()
{
    int base_stat;
    int i;

    for (i = 0; i < 6; i++)
    set_base_stat(i, query_stat(i) + 10);

    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, query_skill(SS_UNARM_COMBAT) + 10 + random(10));
    set_skill(SS_DEFENCE,      query_skill(SS_DEFENCE)      + 10 + random(10));
    set_skill(SS_WEP_SWORD,    query_skill(SS_WEP_SWORD)    + 10 + random(10));

    command("glare");
    tell_room(environment(TO), "A strange look comes over the face of the " +
          "tomb deller; he looks completely insane now.\n");
    command("say Now I am pissed! You are in trouble now.");
    set_whimpy(0);
}

int return_growl(object obj, int ran);
int return_cackle(object obj, int ran);
int return_smile(object obj, int ran);
int return_smirk(object obj, int ran);
int return_grin(object obj, int ran);
int return_burp(string who, int ran);
int return_laugh(string who, int ran);
int return_fart(string who, int ran);
int return_giggle(string who, int ran);
int return_slap(object obj, int ran);

/*
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this NPC, or when it
 *                is performed on in the room in general, this function is
 *                called to let the NPC know about the emotion. This way we
 *                can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 */

public void
emote_hook(string emote, object actor, string adverb=0)
{
    int ran;
    string who;

    if (!present(actor, ETO)) return;

    who = actor->query_real_name();
    if (who == "dweller") return;

    ran = random(3);

    switch (emote)
    {
    case "growl":  return_growl(actor, ran);  break;
    case "cackle": return_cackle(actor, ran); break;
    case "smile":  return_smile(actor, ran);  break;
    case "grin":   return_grin(actor, ran);   break;
    case "burp":   return_burp(who, ran);     break;
    case "laugh":  return_laugh(who, ran);    break;
    case "fart":   return_fart(who, ran);     break;
    case "giggle": return_giggle(who, ran);   break;
    case "smirk":  return_smirk(actor, ran);  break;
    case "slap":   return_slap(actor, ran);   break;
    }
}

create_monster()
{
    int i;

    set_name("dweller");
    set_short("tomb dweller");
    set_long("A being that dwells here in the tomb.  Its eaten away and " +
         "bone-revealing form is a leering abhorrent travesty of its " +
         "once human shape.\n");
    set_adj("decayed");
    set_race_name("dweller");
    set_gender(0);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(20, 20);

    set_whimpy(63);
    set_act_time(7);
    add_act(({"frown"}));
    add_act("get weapons from backpack");
    add_act("@@dump_pack");
    set_chat_time(1);
    set_cchat_time(1);

    for (i = 0; i < sizeof(chats); i++) {
    add_chat(chats[i]);
    add_cchat(chats[i]);
    }

    for (i = 0; i < sizeof(cchats); i++) {
    add_cchat(cchats[i]);
    }

    set_spell_prop(TO);

    trig_new("%w 'drops' %s", "react_drop");
    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
    trig_new("%s 'died.\n' %s","react_death");


}

dress_me()
{
    int level = query_dweller_level();

    seteuid(getuid());

    clone_object(ARM_DIR + "dw_helmet"    + level)->move(TO);
    clone_object(ARM_DIR + "dw_shield"    + level)->move(TO);
    clone_object(ARM_DIR + "dw_chainmail" + level)->move(TO);
    clone_object(ARM_DIR + "dw_boots"     + level)->move(TO);
    clone_object(WEP_DIR + "dw_sword"     + level)->move(TO);

    command("wield sword");
    command("wear armours");
    command("frown");
}

void
set_spell_prop(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
}

public void
run_away()
{
    if (berzerked)
    return;
    else {
    go_berzerk();
    berzerked = 1;
    }
}

react_death(s,ss)
{
    if (s == "The decayed dweller") {
    command("scream");
    command("shout You killed me brother!  Now I'm gonna kill you!");
    command("get all from corpse");
    }
    return 1;
}

react_attacked(s,ss)
{
  set_alarmv(1.0, -1.0, "att",({TP}));
  return 1;

}

att(object tp)
{
    string msg;

    switch (random(10)) {
     case 0:
    msg = "You just made the biggest mistake of your life!";
    break;
     case 1:
    msg = "I didn't think you had the balls to attack me.";
    break;
     case 2:
    msg = "Now I'm going to take your head off.";
    break;
     case 3:
    msg = "I can't believe you had the dis to attack me.";
    break;
     case 4:
    msg = "You are in trouble now!";
    break;
     case 5:
    msg = "I will destroy you now!";
    break;
     case 6:
    msg = "Now I am going to crush you like the bug you are.";
    break;
     case 7:
    msg = "You are going to regret this.";
    break;
     case 8:
    msg = "I'll make you wish you were never born.";
    break;
     case 9:
    msg = "What a puny attack! This is going to be a joke.";
    break;
    }


    command("shout " + msg);

    switch (random(4)) {
     case 0:
    command("kick " + tp->query_real_name());
    break;
     case 1:
    command("slap " + tp->query_real_name());
    break;
     case 2:
    command("say You are so wimpy it makes me sick!");
    command("puke " + tp->query_real_name());
    break;
     case 3:
    command("poke " + tp->query_real_name() + " eye");
    break;
    }
  return 1;
}

int
react_drop(string who, string dummy1)
{
    command("get coins");
    command("get armours");
    command("get weapons");
    command("get all from sack");
    command("get all from backpack");
    command("say Thanks!");
}

void
return_cackle(object obj, int ran)
{
    if (ran == 0)
    command("say You cackle like a duck, " + obj->query_race_name() + ".");
    if (ran == 1)
    command("say Throw your head back again, it gives me a better " +
        "shot at your neck.");
    if (ran == 2)
    command("say You remind me of the wicked witch when you cackle " +
        "like that.");
}

void
return_smile(object obj, int ran)
{
    if (ran == 0)
    command("say I'll be the one smiling when you are on the " +
        "ground dying.");
    if (ran == 1)
    command("say Look at that--- a vertical smile!");
    if (ran == 2)
    command("say smile while you can, " + obj->query_nonmet_name()+ ".");
}

void
return_smirk(object obj, int ran)
{
    string who = obj->query_nonmet_name();
    if (ran == 0)
    command("say Wipe that stupid smirk off your ugly face, " +
        obj->query_nonmet_name() + "...");
    if (ran == 1)
    command("say What's with the stupid smirking?");
    if (ran == 2)
    command("grin at " + who);
}

void
return_grin(object obj, int ran)
{
    if (ran == 0)
    command("say What's with that shit-eating grin, " +
        obj->query_nonmet_name() + "?");
    if (ran == 1)
    command("grin");
    if (ran == 2)
    command("say I'll knock that grin off your face, "+
        obj->query_race() + ".");
}

void
return_burp(string who, int ran)
{
    if (ran == 0)
    command("say You woulnd't burp so much if you stopped eating " +
        "dogshit.");
    if (ran == 1)
    command("say Knock it off, you burping wanker.");
    if (ran == 2)
    command("say Nice burp! That was almost puke, eh?");
}

void
return_laugh(string who, int ran)
{
    if (ran == 0)
    command("say You won't be laughing when I chop your head off!");
    if (ran == 1)
    command("say What the hell is so funny?");
    if (ran == 2)
    command("say What are you laughing at?");
}

void
return_fart(string who, int ran)
{
    if (ran == 0)
    command("say You are a real class act, you farting wanker!");
    if (ran == 1)
    command("say Clearing your throat, eh?");
    if (ran == 2)
    tell_room(ETO, "The dweller fans the fart-cloud in your " +
          "general direction.\n");

}

void
return_giggle(string who, int ran)
{
    if (ran == 0)
    command("say You giggle like a wuss!");
    if (ran == 1)
    command("say Why are you giggling when I am going to kick your ass?");
    if (ran == 2)
    command("say Hey, I'll give you something to giggle about!");
}

void
return_growl(object obj, int ran)
{
    if (ran == 0)
    command("say You are not very menacing, my friend.");
    if (ran == 1)
    command("say Why growl at me, " + obj->query_race_name() + "?");
    if (ran == 2)
    command("frown");
}

void
return_slap(object obj, int ran)
{
    command("say Dont EVER slap me again you " +
        obj->query_race_name() + " bastard!");
    obj->catch_msg("The decayed dweller punches your face VERY hard!\n");
    tell_room(ETO, "The decayed dweller punches " +
          QCTNAME(obj) + " in the face, VERY hard!\n", obj);
}

dump_pack()
{
    object room;
    object *pl;
    object victim;
    object pack;
    object *pack_items;
    int i;

    if (TO->query_prop("pack_dump"))
    return 1;

    room = environment(TO);
    pl = FILTER_PLAYERS(all_inventory(room));

    if (!sizeof(pl))
    return 0;

    for (i = 0; i < sizeof(pl); i++) {
    victim = pl[i];
    pack = present("backpack", victim);

    if (pack) {
        pack_items = all_inventory(pack);
        if (sizeof(pack_items)) {
        command("say Lets see what you have inside this stupid " +
            "looking backpack...");
        tell_room(environment(victim), "The dweller grabs " +
              QCTNAME(victim)
              + "'s backpack and dumps out the contents.\n",
              victim);
        victim->catch_msg("The dweller grabs your backpack and " +
                  "dumps the contents out.\n");
        for (i = 0; i < sizeof(pack_items); i++) {
            pack_items[i]->move(room);
        }
        command("get all");
        TO->add_prop("pack_dump", 1);
        return 1;
        }
    }

    pack = present("sack", victim);

    if (pack) {
        pack_items = all_inventory(pack);
        if (sizeof(pack_items)) {
        command("say Oh look you have one of those sacks... ");
        tell_room(environment(victim), "The dweller grabs " +
              QCTNAME(victim)
              + "'s sack and dumps out the contents.\n",
              victim);
        victim->catch_msg("The dweller grabs your sack and " +
                  "dumps the contents out.\n");
        for (i = 0; i < sizeof(pack_items); i++) {
            pack_items[i]->move(room);
        }
        command("get all");
        TO->add_prop("sack_dump", 1);
        return 1;
        }
    }


    }
    return 0;
}


void
attacked_by(object ob)
{
   object *arr;
   int i;

   ::attacked_by(ob);

   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
       arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
* Function name: notify_ob_attacked_me
   * Description:   This is called when someone attacks a team member of mine
* Arguments:     friend - My team mate
*                attacker - The attacker
*/
void
notify_ob_attacked_me(object friend, object attacker)
   {
   if (query_attack())
      return;

   set_alarmv(1.0, -1.0, "help_friend", ({attacker}));
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
    string msg;

    switch (random(5)) {
     case 0:
    msg = "Hey scumbag, you mess with him, you mess with me!";
    break;
     case 1:
    msg = "How dare you attack my brother?";
    break;
     case 2:
    msg = "Buttmunch! You attacked my brother, now I'll kill you!";
    break;
     case 3:
    msg = "Hey Buttnugget! Leave him alone!";
    break;
     case 4:
    msg = "What were you thinking? I am going to just _watch_ this fight?";
    break;
    }

    if (ob && !query_attack() && present(ob, environment())) {
    command("say " + msg);
    command("kill " + lower_case(ob->query_real_name()));
    command("kill " + lower_case(ob->query_real_name()));
    }
}



