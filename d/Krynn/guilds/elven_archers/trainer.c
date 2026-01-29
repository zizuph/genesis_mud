/* File : trainer.c
 *
 * The npc which allows elves to join and train with the archers
 */

/* Navarre July 3rd 2006, fixed typo, tutorage changed to tutelage */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <options.h>
#include <money.h>
#include "/d/Krynn/qualinesti/local.h"
#include "guild.h"

inherit M_FILE
inherit "/d/Ansalon/common/cheater";

void          arm_me();
object        quiver;

public int
query_archer_training(object archer)
{
    string  name;
    object  temp_player;
    int     value, skill;
    
    if (archer->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    name    = archer->query_real_name();
    
    if (!(value = OPTIONS_MANAGER->query_option("LoreMasterTraining", name)))
    {
        OPTIONS_MANAGER->set_option("LoreMasterTraining", name, 70);
        value = 70;
    }
    
    temp_player = this_player();
    set_this_player(archer);
    skill = min(archer->query_base_skill(SS_WEP_MISSILE) + 1,
                JOINROOM->sk_query_max(SS_WEP_MISSILE, 1));
    set_this_player(temp_player);
    
    if (skill < value)
        return 0;
    
    return value;
}

string
ask_for_guidance()
{
    string  name;
    int     value;
    
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
        return query_default_answer();
    
    if (!(value = query_archer_training(this_player())))
    {
        this_object()->command("say You are not ready for further guidance in "
        + "the art of archery.");
        return "";
    }
    
    name = this_player()->query_real_name();
    
    if (this_player()->test_bit("krynn", GROUP, Q_BIT))
        return "You have already achieved enlightenment, the Loremaster has "
        + "nothing left to teach you."
        + (this_player()->query_skill(SS_WEP_MISSILE) < 100 ? " "
        + "You only need more experience to better your skills." : "\n");
    
    switch(value)
    {
        case 70:
        OPTIONS_MANAGER->set_option("LoreMasterTraining", name, 80);
        this_player()->catch_msg(QCTNAME(this_object()) + " offers his "
        + "guidance to you, correcting your stance and movements in combative "
        + "archery.\nHe explains the basics of archery, stressing that the "
        + "foundation is the key to excellence.\n\nThe lesson has proven "
        + "fruitful and you feel eager to go out and utilize your new found "
        + "knowledge.\n");
        tell_room(environment(this_object()), QCTNAME(this_object()) + " "
        + "offers his guidance to " + QTNAME(this_player()) + " teaching the "
        + "intricate art of archery.\n", ({ this_object(), this_player()}),
        this_object());
            break;
        case 80:
        OPTIONS_MANAGER->set_option("LoreMasterTraining", name, 90);
        this_player()->catch_msg("As you have become skilled in the basics of "
        + "archery, you have begun your journey towards true mastery of the "
        + "skill. The Loremaster teaches you techniques for aiming and to "
        + "faster nock your arrows. You feel that you will soon be able to "
        + "utilize the 'snipe' ability that the Loremaster displays with such "
        + "brilliance.\n\nThe lesson comes to an end and you feel a burning "
        + "desire to temper your skills in combat.\n");
        tell_room(environment(this_object()), QCTNAME(this_object()) + " "
        + "offers his guidance to " + QTNAME(this_player()) + " teaching the "
        + "intricate art of archery.\n", ({ this_object(), this_player()}),
        this_object());
            break;
        case 90:
        object guru;
        
        if (!objectp(guru = clone_object(GURU_SH)) ||
            guru->shadow_me(this_player()) < 0)
            return "Something has gone horribly wrong, please contact the "
            + "wizard in charge of the archery guild, the quest for guru has "
            + "failed to load.";
        
        this_player()->init_guru_shadow();
        this_object()->command("say to " + OB_NAME(this_player()) + " You are "
        + "on the brink of true mastery, from here on out I have nothing left "
        + "to teach you. I must remind you that each lesson taught is an "
        + "opportunity missed. The wisdom that comes with time, comes from "
        + "inward reflection and experiencing difficulty, not from blindly "
        + "following those around you. The lessons I have taught you, should "
        + "with years of experience blossom.\n");
        this_object()->command("say to " + OB_NAME(this_player()) + " I do "
        + "fondly remember my own search for true mastery in my youth. The "
        + "stories that fueled the fires of desire still linger in my mind. "
        + "There are tales of an elf who prayed to Zivilyn, the World Tree, "
        + "for insight and was granted wisdom. Another of someone who fought "
        + "an illusion of himself and found clarity. I believed in my youth "
        + "that both of these were the same, but I was unable to prove my "
        + "theory correct.\n");
        this_object()->command("say to " + OB_NAME(this_player()) + " I advise "
        + "you not to spend your life seeking for the truth in tales and "
        + "nursery rhymes, but if this is where your path leads, I shall offer "
        + "you my last bit of guidance.\n");
        this_object()->command("say to " + OB_NAME(this_player()) + " In my "
        + "youth, I searched far and wide for the illusion mentioned in tales. "
        + "In my search I came upon mirages, illusory spells and dream like "
        + "states, but nothing matching what I required for inward reflection. "
        + "The closest phenomenon I found was a fetch in a reflective pool, "
        + "but it merely mirrored my appearance, not my actions. Had I only "
        + "been able to locate the druids, I might have been able to find the "
        + "wisdom I desired.\n");
        this_object()->command("say to " + OB_NAME(this_player()) + " With "
        + "this, my last bit of wisdom to offer, I wish you prosperity. May "
        + "you find what I failed to in my youth.\n");
        
        tell_room(environment(this_object()), QCTNAME(this_object()) + " "
        + "offers his guidance to " + QTNAME(this_player()) + " teaching the "
        + "intricate art of archery.\n", ({ this_object(), this_player()}),
        this_object());
            break;
    }
    return "";
}

void
notify_archer_training()
{
    object  archer;
    int     value;
    
    if (!objectp(archer = this_interactive()))
        return;
    
    if (!(value = query_archer_training(archer)))
        return;
    
    archer->catch_msg("You have reached the limit of your understanding in "
    + "archery, the loremaster may be able to offer guidance.\n");
}

void
create_krynn_monster()
{
    
    set_name("quillean");
    set_living_name("quillean");
    set_race_name("elf");
    set_adj("solemn");
    add_adj("sharp-eyed");
    set_title("Prellias of Qualinost, Loremaster of the Elven Archers");
    set_long("This tall, lithe elf has been given the duty of instructing "+
      "fellow elves in the art of archery, tracking, and other lore that "+
      "elves are renown for.\n");
    set_gender(0);
    set_alignment(800);
    set_knight_prestige(-300);
    
    set_stats(({ 180, 230, 210, 180, 180, 185 }));

    set_skill(SS_WEP_KNIFE, 150);
    set_skill(SS_WEP_MISSILE, 150);
    set_skill(SS_WEP_POLEARM, 150);
    set_skill(SS_2H_COMBAT, 150);
    set_skill(SS_PARRY, 150);
    set_skill(SS_DEFENCE, 150);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
   
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(LIVE_I_QUICKNESS, 130);    
    add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
      "do not have the self-discipline to dare!\n");

    set_introduce(1);

    set_hp(query_max_hp());

    set_act_time(10 + random(2));
    add_act("say Dragonarmies keep sending more and more draconians to Pax " +
        "Tharkas! We have to keep patrolling the forest.");
    add_act("say We must weaken the dragonarmy forces before they launch " +
        "an attack on Qualinost!");
    add_act("say Being the loremaster, it is my duty to ensure my kindred " +
        "are well trained to face the troubled times ahead.");
    add_act("say Some of those draconians are quite skilled, but they " +
        "are no match for us!");
    add_act("emote examines his bowstring carefully.");
        
    add_cact("emote scowls at you.");
    add_cact("say You really think you can stand against me?!");
    add_cact("say Defend yourself!");
    add_cact("take arrows");
    
    set_default_answer("For some reason, you are ignored. He seems somewhat "+
        "focused on his elaborate bow... perhaps you should ask him about "+
        "archery?\n");
    add_ask(({ "about archery", "archery", "tracking", "lore" }),
        "say Yes, my duty is to train elves in various skills "+
        "important to scouts and rangers guarding our forest. "+
        "I will train an elf in an occupational or layman capacity, "+
        "however in these dark days, my training time is limited. If you are "+
        "interested, ask me about the elven archers guild.", 1);
   add_ask(({"the elven archers guild", "elven archers guild",
        "archers guild", "guild", "about guild"}),
        "say For those elves interested in learning to be an "+
        "archer under my tutelage, I will train them to be a master "+
        "craftsman at the use of a bow, to move through the forest "+
        "silently and to track both beast and man. In these troubled times, " +
        "I will even stoop to teach those not of pure elven blood, those " +
        "who are half-elven. For further information, "+
        "ask me about the guilds requirements.", 1);
   add_ask(({"magic","spells"}),"say I am a dabbler in the Art like many " +
        "elves, although not to the point of taking the Test of High " +
        "Sorcery!", 1);
   add_ask(({"guild requirements","requirements","guilds requirements",
             "leaving","leave guild"}),
        "say I will only train elves of a good nature. Apart from that "+
        "I put no further requirements on my pupils. Admittedly, if they "+
        "stray down a darker path, there is little I can do stop them " +
        "apart from refusing to give them any further training. For those who "+
        "no longer wish to make use of my training, they may [leave the elven "+
        "archers] without penalty. If you are still interested, ask me "+
        "about joining.", 1);
   add_ask(({"join", "joining"," joining the elven archers", "about joining"}),
        "say To join, either [declare complete loyalty as an elven archer] " +
        "to join in an occupational capacity, or if you only wish to train " +
        "as a layman simply [declare loyalty as an elven archer]. You can " +
        "then begin your training. The basic training for archers of the "+
        "occupational and layman branch are similar. The elves joining with "+
        "an occupational capacity gets to train as a true master in missile "+
        "weapons and they receive more training to defend themselves as well"+
        "!", 1);

   add_ask(({"layman","occupational"}), "say Currently, there is little " +
        "difference in the skills or spells I train an occupational or layman "+
        "archer, apart from occupational archers getting more training in " +
        "archery and defence!", 1);
    
   add_ask(({"bow", "longbow","elven longbow","arrow","arrows","bowstring"}),
      "The solemn sharp-eyed elf says: I sell elven longbows for 14 gold coins. "+
      "20 silver for 12 arrows. And 12 copper for a bowstring!\n");
    
    add_ask(({"guidance", "training", "limit"}), "@@ask_for_guidance@@", 0);
    add_notify_meet_interactive(notify_archer_training);
    seteuid(getuid(TO));
    arm_me();
}



void
arm_me()
{
    object weapon;

    weapon = clone_object(WEP + "silver_bow");
    weapon->move(TO);
    quiver = clone_object(OBJ + "quiver");
    quiver->move(TO);
    clone_object(WEP + "leaf_arrow")->move(quiver);
    clone_object(WEP + "elven_arrow")->move(quiver);
    clone_object(WEP + "leaf_arrow")->move(quiver);
    clone_object(WEP + "piercing_arrow")->move(quiver);
    clone_object(WEP + "piercing_arrow")->move(quiver);   
    clone_object(ARM + "elven_boots")->move(TO);
    clone_object(ARM + "elven_sleeves")->move(TO);
    clone_object(ARM + "chain")->move(TO);
    clone_object(ARM + "cloak")->move(TO);
                                                   
    command("wield all");
    command("wear all");
    
}

void
init_living()
{
    ::init_living();
    ADA("buy");
    ADA("list");
}

int
list()
{
    write(capitalize(COMPOSITE_LIVE(TO)) + " says to you: I have a few " +
        "items that may be handy for an archer. I can sell you " +
        "an ashwood longbow for 14 gold coins, " +
        "a dozen white-feathered arrows for 20 silver coins " +
        "and a bowstring for only 12 copper coins. It is always good " +
        "to have spare bowstrings!\n"); 
    return 1;
}

int
buy(string str)
{
    object pig, who;

    if (check_cheater(TP, TO))
        return 1;

    if (str == "longbow" || str == "bow" || str == "ashwood bow" ||
        str == "ashwood longbow" )
    {
        NF("The solemn sharp-eyed elf says: You cannot afford an elven longbow.\n");
        if(!MONEY_ADD(TP, -2016))
	    return 0;

        write("You pay the solemn sharp-eyed elf, and he passes you an " +
          "ashwood longbow.\n");
        say(QCTNAME(TP) + " buys a longbow from the " +
          "solemn sharp-eyed elf.\n");

        who = TP;
        pig = clone_object(WEP + "elven_bow");
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the longbow, the " +
    	        "solemn sharp-eyed elf places it on the ground before you.\n");
    	      say("The elf places the longbow on the ground before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "arrows" || str == "white-feathered arrows" )
    {
        NF("The solemn sharp-eyed elf says: You cannot afford a dozen arrows.\n");
        if(!MONEY_ADD(TP, -240))
	    return 0;

        write("You pay the solemn sharp-eyed elf, and he passes you a " +
          "dozen arrows.\n");
        say(QCTNAME(TP) + " buys a dozen arrows from the " +
          "solemn sharp-eyed elf.\n");

        who = TP;
        pig = clone_object(WEP + "elven_arrow");
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the arrows, the " +
    	        "solemn sharp-eyed elf places it on the ground before you.\n");
    	      say("The elf places the arrows on the ground before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }
         return 1;
     }

    if (str == "bowstring")
    {
        NF("The solemn sharp-eyed elf says: You cannot afford a bowstring.\n");
        if(!MONEY_ADD(TP, -12))
	    return 0;

        write("You pay the solemn sharp-eyed elf, and he passes you a " +
          "bowstring.\n");
        say(QCTNAME(TP) + " buys a bowstring from the " +
          "solemn sharp-eyed elf.\n");

        who = TP;
        pig = clone_object("/d/Ansalon/kalaman/obj/weapon/bowstring");
        if (pig->move(who) != 0)
        {
              write("Noticing that you are too burdened to carry the bowstring, the " +
    	        "solemn sharp-eyed elf places it on the ground before you.\n");
    	      say("The elf places the bowstring on the ground before " + QTNAME(TP) + ".\n");
    	      /* pig?? */
    	      pig->move(environment(who));
         }

        return 1; 
     }

    NF("Buy what did you say you wanted to buy? A longbow, arrows, or bowstring?\n");
	return 0; 
}

