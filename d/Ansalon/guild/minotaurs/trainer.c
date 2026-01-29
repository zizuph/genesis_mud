#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "guild.h"
#include <wa_types.h>

inherit AM_FILE
inherit "/lib/unique";

#define WEP1 "/d/Ansalon/guild/minotaurs/mino_axe"
#define WEP2 "/d/Ansalon/guild/minotaurs/steel_axe"


object weapon = 0;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("audarius");
    add_name("trainer");
    set_living_name("audarius");
    set_title("Et-Thentius the Elder, Fabled Minotaur Sage of Nethosak");
    set_race_name("minotaur");
    set_adj("long-horned");
    add_adj("grey-maned");
    set_gender("G_MALE");
    set_long("Before you stands a massive and gnarled minotaur, his fur " +
      "greyed with age. He wanders through the forest unarmed and unarmoured, " +
      "however not for a second are you deceived into thinking he is helpless... " +
      "Great horns sweep out from his bullish head, and his battle-scarred hide " +
      "thick. He glances at you with intelligence and wisdom, and you get the " +
      "feeling this one knows more than just battle, but also a lot about the " +
      "minotaur kind.\nHe is a Bloodsea minotaur with extremely long horns.\n");

    set_stats(({300,200,240,150,150,150}));
    set_hp(query_max_hp());
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    set_alignment(0);
    set_knight_prestige(0);
    set_all_hitloc_unarmed(200);


    set_default_answer("The minotaur looks at you funnily, as if " +
      "you should already know the answer to that.\n");

    set_act_time(5);
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote snorts loudly.");
    add_act("emote rumbles: Minotaurs are often underestimated by the lesser " +
      "races.");
    add_act("emote rumbles: Everyone must die. So why not die gloriously? That " +
      "is the mindset of the minotaur.");
    add_act("emote rumbles: Our kind have been enslaved by the empires of man, " +
      "ogres, and dwarves. Their kind are now fallen, and the glorious destiny " +
      "of the minotaurs will soon be at hand!");
    add_act("emote eyes you cunningly.");
    add_act("emote rumbles: Honour, strength, family. That is what the minotaur " +
      "kind values above all else. It is what makes us superior to the lesser " +
      "races of Krynn.");


    set_cact_time(0);
    add_cact("emote bellows 'By Sargas!' in fury!");
    add_cact("emote lowers his horned head threateningly.");
    add_cact("emote roars: Fool! You cannot defeat me!");

    set_introduce(1);

/*
    trig_new("%w 'introduces' %s","react_to_intro");
*/
}

void
arm_me()
{
    seteuid(getuid(TO));
}

public void
attacked_by(object ob)
{
    command("shout By Sargas! You shall taste steel!");
    seteuid(getuid(TO));
    if(!weapon)
    {
        weapon = clone_unique(WEP1, 3, WEP2);
        weapon->move(TO, 1);
        command("wield all");
    }
}



void
return_intro(string who)
{
    who = L(who);
    if (P(who, E(TO)))
    {
	command("introduce myself");
    }
}


int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me=TO;

    if(random(3))
    {
        return 0;
    }
    penet = query_stat(SS_STR)*3/2;
 
    hitresult = enemy->hit_me(penet, W_IMPALE, me, -1);
    how = "misses, momentum carries " + HIM(TO) + " by. At " +
        "the verge of falling on " + HIS(TO) + " belly " +
        HE(TO) + " twists the body and, in amazing display " +
        "of agility, " + HE(TO) + " rolls over the arm and " +
        "ends up on " + HIS(TO) + " feet";
    if (hitresult[0] > 0)
        how = "his horns leaving just a scratch as he charges past";
    if (hitresult[0] > 10)
        how = "cutting wildly with his horns, leaving bloody wounds";
    if (hitresult[0] > 30)
        how = "hitting solidly with the flat of his head, causing a " +
            "resounding 'crack'! " + C(HIS(TO)) + " horns pierce two " +
            "round holes and blood begins to flow";
    if (hitresult[0] > 50)
        how = "goring deeply as he attempts to disembowel his opponent";
    if (hitresult[0] > 70)
        how = "impaling with his horns, then thrashing around madly, " +
            "causing extreme damage";
 
    enemy->catch_msg("The minotaur charges directly at you, " + how +
        "!\n");
    tell_watcher("The minotaur rushes at " + QTNAME(enemy) + ", "
        + how + "!\n",enemy);
 
    if (enemy->query_hp() <= 0)
    {
        write("The minotaur shakes his head madly as he throws the " +
            "lifeless body of " + QTNAME(enemy) + " across the room!\n");
        enemy->do_die(TO);
    }
    return 1;
}


void
catch_question(string str)
{
    string question, answ;
    mixed minfo;
 
    if(!TP->check_seen(TO) || !CAN_SEE_IN_ROOM(TO))
    {
        set_alarm(rnd()*3.0 + 1.0, 0.0, &command("emote peers around puzzled."));
        return;
    }
 
    if(!parse_command(str, ({}), "[about] [the] %s", question))
    {
        set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
            OB_NAME(TP)+" I do not understand your question."));
        return;
    }
    question = lower_case(question);
 
    if (question == "minotaurs" || question == "minotaur kind" || question == "minotaur")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("scratch chin");
        command("say There is much I can tell you about the minotaurs...");
        set_alarm(1.0,0.0,&command("say I can tell you of our <history>, from our awakening by " +
            "the magic of the Graygem..."));
        set_alarm(2.0,0.0,&command("say I can tell you of the prime values of the minotaur... " +
            "<honour>, <strength>, and <family>. These values set us above the lesser " +
            "races, who are weak and riddled with dishonourable folk. A fallow field waiting " +
            "to be cropped by Krynn's master race. It is why we are the chosen of the gods, and it " +
            "will be key to our future glory as rightful rulers of Krynn!"));
        set_alarm(3.0,0.0,&command("smile violent"));
        set_alarm(4.0,0.0,&command("emote takes a deep breath."));
        set_alarm(5.0,0.0,&command("say I am also willing to teach minotaurs the <skills> of our kind. " +
            "They will however need to recite the <litany of the bloodsea minotaurs> before I " +
            "do so."));
        set_alarm(5.5,0.0,&command("emote stretches out his massive body, his muscles rippling."));

        return;
    }

    if (question == "history")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("scratch chin");
        command("say The history of the minotaurs begins with the release of the magical and " +
            "chaotic artifact, the Graygem of Gargath...");
        set_alarm(1.0,0.0,&command("say The Graygem broke its bonds and spun crazily across the " +
            "lands of Krynn. In the path of its passage was a village of high ogres, who were painfully " +
            "transformed into the man-beasts known as the minotaurs."));
        set_alarm(2.0,0.0,&command("say These new children of the gods, disoriented and confused by " +
            "these changes, sought out the help of their ogrish brethren... instead, they were enslaved."));
        set_alarm(3.0,0.0,&command("emote snorts angrily at the betrayal."));
        set_alarm(4.0,0.0,&command("say And such was the beginning for our kind. However, we were not meant " +
            "to remain in chains. We broke free, and much ogre blood was spilt. Our kind took to the sea and " +
            "sailed to a new land to build a new life... the lands of Ansalon."));
        set_alarm(5.0,0.0,&command("say However this land treated our kind no better. Once again our kind was " +
            "enslaved, this time by the cursed dwarves."));
        set_alarm(5.5,0.0,&command("say The dwarven empire of Kal-Thax sent battalions of dwarves to our coastal " +
            "towns, slaughtering those who would not enter slavery peacefully. For centuries, the minotaurs " +
            "endured this brutal captivity. However, there then came a hero amongst our kind..."));
        set_alarm(6.0,0.0,&command("say The mighty Ambeoutin!"));
        set_alarm(6.5,0.0,&command("emote smiles bloodthirstily in obvious pleasure."));
        set_alarm(7.0,0.0,&command("say The minotaurs rose to his call and revolted against their captors. " +
            "The dwarves were overthrown, with every last dwarf in Kal-Thax slain by our hands, thus ending " +
            "their empire in bloody fashion."));
        set_alarm(8.0,0.0,&command("say To the coast we returned, with Ambeoutin acclaimed as our first King. " +
            "He founded our society on honour, strength, and family. Never again would the minotaurs allow " +
            "themselves to be enslaved!"));
        set_alarm(9.0,0.0,&command("say In time Ambeoutin sired two sons, Mithas and Kothas, who later ruled " +
            "the northern and southern parts of Ambeoutin's kingdom. 1500 years of peace followed, until " +
            "once again our realms ran afoul of another race... this time the humans of the Istarian Empire."));
        set_alarm(10.0,0.0,&command("say While powerful and noble warriors, our kind was no match for the " +
            "hordes of self-righteous humans. The minotaur race faced certain doom at their hands, however " +
            "the gods themselves decreed it not to be..."));
        set_alarm(11.0,0.0,&command("say The gods vengeance at the actions of the Istarians was terrible. " +
            "A fiery mountain fell from the heavens and struck down Istar, turning its fertile lands into " +
            "what is now the Bloodsea. Our lands were seperated from Ansalon, making us finally safe from " +
            "oppressors."));
        set_alarm(12.0,0.0,&command("say Others view this act of the gods as the beginning of a time of " +
            "darkness. To us, it is a sign of the future glory of our kind."));
        set_alarm(13.0,0.0,&command("say And that is our history. Any other questions?"));

        return;
    }
 
    if (question == "honour")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("emote snorts in obvious pleasure.");
        command("say I knew you would ask of this... minotaurs are an honour-bound race, who " +
            "believe strongly in preserving their honour and emerging victorious in the struggle " +
            "for dominance of Krynn.");
        set_alarm(1.0,0.0,&command("say Above ALL else, we value honour. Without it, we are no better " +
            "than the lesser races."));
        set_alarm(2.0,0.0,&command("say A minotaur will honour his word, no matter how painful the " +
            "consequences are. We take promises and oaths seriously..."));
        set_alarm(3.0,0.0,&command("say So don't pledge such oaths lightly!"));

        return;
    }

    if (question == "strength")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("emote flexes his arms impressively.");
        command("say A simple question, with a simple answer. Might makes right.");
        set_alarm(1.0,0.0,&command("say Any problem can be solved with strength, cunning, and skill. " +
            "Our kind firmly believes this, and are more than willing to take problems to arena!"));

        return;
    }

    if (question == "family")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("emote looks at you solemnly.");
        command("say Families are the building blocks of minotaur society. Without a line of " +
            "parentage, an individual minotaur is cut off from the noble and glorious history " +
            "of our kind.");
        set_alarm(1.0,0.0,&command("say Without a family, an individual has no source of honour and " +
            "pride, which is the meat and drink of minotaur existence."));

        return;
    }

    if (question == "litany of the bloodsea minotaurs" || question == "litany")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("emote looks at you seriously.");
        command("say The litany of the Bloodsea minotaurs encompasses our history and all our " +
            "values.");
        set_alarm(1.0,0.0,&command("say For those minotaurs who embrace this litany as part " +
            "of their lives and recite it before me, I will train them in the ways of the minotaur."));

        return;
    }


    if (question == "skills")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("emote snorts in amusement.");
        command("say It is good to see you keen to learn.");
        set_alarm(1.0,0.0,&command("say I will teach you certain skills that will help you " +
            "assert your might. I will teach you some combat skills so you are not as helpless " +
            "as a newborn calf, namely skills in axe, defence, parry, and blind fighting...")); 
        set_alarm(2.0,0.0,&command("say I will teach you how to appraise your enemies, as well " +
            "as how to gore your foes with your horns. I will also teach you seafaring crafts, " +
            "such as location sense and swimming."));

        return;
    }

    if (question == "leave" || question == "quit" || question == "forsake" || question == "leave guild")
    {
        if(TP->query_race_name() != "minotaur")
        {
            command("eyebrow suspic");
            command("say What would one of the lesser races want to know of the " +
                "minotaurs for?");
            command("say Begone! You are not worthy of my knowledge!");
            return;
        }
 
        command("emote looks at you curiously.");
        command("say You would want to leave? Why?");
        set_alarm(1.0,0.0,&command("sigh"));
        set_alarm(2.0,0.0,&command("say I cannot imagine why anyone would want to " +
           "<forsake the bloodsea minotaurs>!"));

        return;
    }
 
    set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
        " You can find that answer elsewhere."));
}
