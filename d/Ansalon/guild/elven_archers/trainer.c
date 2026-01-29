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

inherit M_FILE
inherit "/d/Ansalon/common/cheater";

void          arm_me();
object        quiver;


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
        "silently, to track both beast and man, as well as teach "+
        "them to dabble in the art of magic. In these troubled times, I " +
        "will even stoop to teach those not of pure elven blood, those " +
        "who are half-elven. For further information, "+
        "ask me about the guilds requirements.", 1);
   add_ask(({"magic","spells"}),"say I do teach a few minor spells... "+
        "I am a dabbler in the Art like many elves, although not to the "+
        "point of taking the Test of High Sorcery!", 1);
   add_ask(({"guild requirements","requirements","guilds requirements",
             "leaving","leave guild"}),
        "say I will only train elves of a good nature. Apart from that "+
        "I put no further requirements on my pupils. Admittedly, if they "+
        "stray down a darker path, there is little I can do stop them " +
        "apart from refusing to give them any further training. For those who no " +
        "longer wish to make use of my training, they may [leave the elven "+
        "archers] without penalty. If you are still interested, ask me "+
        "about joining.", 1);
   add_ask(({"join", "joining"," joining the elven archers", "about joining"}),
        "say To join, either [declare complete loyalty as an elven archer] " +
        "to join in an occupational capacity, or if you only wish to train " +
        "as a layman simply [declare loyalty as an elven archer]. You can " +
        "then begin your training. The basic training for archers of the "+
        "occupational and layman branch are similar. The elves joining with "+
        "an occupational capacity gets to train as a true master in missile "+
        "weapons and they receive more training to defend themselves as well!", 1);

   add_ask(({"layman","occupational"}), "say Currently, there is little difference "+
        "in the skills or spells I train an occupational or layman archer, " +
        "apart from occupational archers getting more training in archery and defence!", 1);
    
   add_ask(({"bow", "longbow","elven longbow","arrow","arrows","bowstring"}),
      "The solemn sharp-eyed elf says: I sell elven longbows for 14 gold coins. "+
      "20 silver for 12 arrows. And 12 copper for a bowstring!\n");
    
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
