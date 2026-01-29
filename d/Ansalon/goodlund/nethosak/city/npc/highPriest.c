#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <options.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

#define KRHERB "/d/Krynn/common/herbs/"
#define I_MUST_FIND_MINOTAUR_EYE "_i_must_find_the_eye"

inherit "/d/Ansalon/std/monster";

void arm_me();
int has_been_attacked = 0; // The High priest hasn't been attacked.
string race;

void
create_krynn_monster()
{
    set_name("Suranir");
    set_race_name("minotaur"); 
    add_name(({"priest", "minotaur", "suranir", }));
    set_adj("black-robed");
    add_adj("white-haired");
    set_title("the High Priest of the Holy Order of the Stars");
    set_gender(0);

    set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws. This minotaur is dressed in a black robe, that "+
             "shrouds most of his face. His hair is white, something "+
             "that is rarely seen among minotaurs. On his left wrist he "+
             "bears the mark of Sargonnas which indicates that this must "+
             "be the high priest of this village.\n"+
             "He is a priest of the Dark Order of Sargonnas.\n"+
             "He has a pouch with herbs tied to his belt.\n");

    // Set stats, alignment.
    set_base_stat(SS_STR, random(50)+170);
    set_base_stat(SS_DEX, random(60)+200);
    set_base_stat(SS_CON, random(20)+180);
    set_base_stat(SS_INT, random(20)+160);
    set_base_stat(SS_WIS, random(15)+70);
    set_base_stat(SS_DIS, random(15)+100);
    
    set_alignment(-300);
    set_all_hitloc_unarmed(30);
    set_introduce(1);

    // Set weight, height and volume.
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000);
    add_prop(LIVE_I_QUICKNESS, 50);
   
    // Set skills.
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_FORM_ENCHANTMENT, 100);

    add_ask(({"task","quest","job","eye"}), VBFC_ME("quest_hint"));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
                                                               
    set_cact_time(1);
    add_cact("emote whispers: Sargonnas will reward me "+
                             "greatly for slaying you!");
    arm_me();
}

string
quest_hint()
{
    if (TP->query_prop(I_MUST_FIND_MINOTAUR_EYE))
    {
        command("say Find the Holy Eye!");
        return "";
    }
    if(TP->test_bit("ansalon",0,3))
    {
	command("say I don't need your help.");
	return "";
    }
    race = TP->query_race_name();
    command("say What? You dare speak to me?!\n");
    set_alarm(1.0,0.0, &command("say I should sacrifice you to "+
                                 "Sargonnas instantly.\n"));
    set_alarm(2.0,0.0, &command("hmm"));
    set_alarm(2.5,0.0, &command("emote looks at you.\n"));
    set_alarm(4.0,0.0, &command("say Even though you look quite pathetic, you "+
                                "might be able to help me anyway.\n"));
    set_alarm(8.0,0.0, &command("say The Minotaur Emperor has had some "+
                                "trouble with the local pirates.\n"));
    set_alarm(13.0,0.0, &command("say This band of rogue thieves call themselves "+
                                "'The Pirates of the Bloodsea' and these "+
                                "fiends has proved to be most troublesome.\n"));
    set_alarm(18.0,0.0, &command("say They have murdered several of our guards and "+
                                 "citizens but a few days ago something "+
                                 "happened that made both the Emperor and me "+
                                 "furious.\n"));
    set_alarm(24.0,0.0, &command("say In the cover of night they broke into this temple "+
                                 "and descerated our holy statue of Sargonnas.\n"));

    set_alarm(28.0,0.0, &command("emote points slightly at the statue.\n"));

    set_alarm(29.0,0.0, &command("say They succedeed in removing one of the statues "+
                                 "gemstone eyes, before they ran away.\n"));

    set_alarm(33.5,0.0, &command("say I have no information about their leader, or their "+
                                 "hideout. However they seem to have slipped into "+
                                 "the city unnoticed, perhaps they have a secret "+
                                 "entrance that we haven't discoved yet...\n"));

    set_alarm(40.0,0.0, &command("say Return the Holy Eye of Sargonnas to "+
                                 "me and I'll reward you handsomely.\n"));
    set_alarm(46.0,0.0, &command("say Good luck..."+race+".\n"));
    TP->add_prop(I_MUST_FIND_MINOTAUR_EYE, 1);
    set_alarm(47.0,0.0, &command("emote snorts violently.\n"));
    return "";
}

void
arm_me()
{
    MONEY_MAKE(random(10),"gold")->move(this_object(),1);
    //clone_object(MWEP + "wound_halberd")->move(this_object(),1); 
    clone_object(MARM + "crimsonrobe")->move(this_object(),1);
    clone_object(MARM + "belt")->move(this_object(),1);
    clone_object(MOBJ + "mortar")->move(this_object(),1);
    clone_object(MOBJ + "vial")->move(this_object(),1);
    clone_object(MOBJ + "comp_pouch")->move(this_object(),1);
    command("wield all");
    command("wear all");
    clone_object(KRHERB + "soapweed")->move(this_object(),1);
    clone_object(KRHERB + "fdlhead")->move(this_object(),1);
    clone_object(KRHERB + "mandrake")->move(this_object(),1);
    clone_object(KRHERB + "skullcap")->move(this_object(),1);
    clone_object(KRHERB + "sargassum")->move(this_object(),1);
    set_alarm(1.0,0.0, &command("say What do you think you are doing here?!"));
    set_alarm(1.5,0.0, &command("put herbs in pouch"));
    set_alarm(2.0,0.0, &command("close pouch"));
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    attacktype = random(10);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    if (attacktype == 1)
    {
        pen = 600 + random(200);
        pen -= pen * enemy->query_prop(MAGIC_I_RES_FIRE) /100;
        hitres = enemy->hit_me(pen, 40, TO, -1);

        wloc = random(5);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "missing";
        if(hitres[0] > 0)
            how = "slightly burning";
        if(hitres[0] > 10)
            how = "burning";
        if(hitres[0] > 20)
            how = "igniting";
        if (hitres[0] > 40)
            how = "surrounding";
        if (hitres[0] > 60)
            how = "engulfing";

        enemy->catch_msg(QCTNAME(TO) + 
          " mumbles strange words while pointing a finger"
          + " towards you. A bolt of fire leaps from the "+
            "palm of his hand, " +how+ " your " + hitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " points a finger" +
          "at " + QTNAME(enemy) + ". A bolt of fire " +
          "leaps from the palm of his hand, " + how + " " + QTNAME(enemy) +
          "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }

        return 1;
    }

    return 0;
}

void
attacked_by(object ob)
{
    if (has_been_attacked == 0)
    {
       object weapon;
       weapon = clone_object(MWEP + "wound_halberd");
       weapon->move(this_object());
       command("wield halberd");
       has_been_attacked = 1;
    }
    command("say I'll teach you the meaning of the word fear!");
    ::attacked_by(ob);
    
}


int
query_option(int opt)
{
    if (opt==OPT_UNARMED_OFF)
    {
        return 1;
    }
    else
    {
        return ::query_option(opt);
    }
}

void
calculate_experience(object who)
{
    int xp_base = 20000;

    if(who->test_bit("ansalon", 0, 3))
    {
        this_player()->catch_msg("You've already done this quest!\n");
        return;
    }

    this_player()->catch_msg("You feel MUCH more experienced!\n");
    if(who->query_wiz_level())
    {
        who->catch_msg("xp : " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 3);

    //A_QUEST_LOG("quest","Minotaur Eye quest", who, xp_base);
    return;
}

void
return_eye(object from)
{
    object eye;
    string who, what;

    who = from->query_real_name();
    command("say The Holy Eye of Sargonnas! Thank you!\n");
    command("cackle");
    command("emote inserts the eye in the golden statue.\n");
    write("The eye magically melts inself into the statue.\n");
    calculate_experience(from);
}


void
remove_eye(object ob)
{
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(from))
	return;

    if(ob->id("_holy_eye_quest_"))
    {
	set_alarm(1.0, 0.0, &return_eye(from));
	set_alarm(1.5, 0.0, &remove_eye(ob));
	return;
    }
    if(!ob->id("_holy_eye_quest_") && TP->query_prop(I_MUST_FIND_MINOTAUR_EYE))
    {
        command("say This is not what I asked for!");
        command("drop "+ob->query_name());
	return;
    }
    if(!ob->id("_holy_eye_quest_"))
    {
        command("say I do not need your charity! Begone feeble one!");
        command("drop "+ob->query_name());
	return;
    }
    return;
}

