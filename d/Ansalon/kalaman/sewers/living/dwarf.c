/* A gully dwarf created to live in the sewers of Kalaman
 * Created by Arcturus
 * Latest update 26.04.05
 */

#include "/d/Ansalon/common/defs.h"
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit AM_FILE
inherit AUTO_TEAM

private string attacker;

void
create_krynn_monster()
{
    int i;
    string name, *first, *second, temp1, temp2;

    first = ({"small", "stout", "fat", "short", "stupid", "smelly", "dirty", "little", "proud" });
    second = ({"red-haired", "blue-eyed", "red-bearded", "elderly", "white-haired", "brown-eyed", "black-haired", "young", "bronzed", "brown-bearded" });
    
    temp1 = one_of_list(first);
    temp2 = one_of_list(second);
    
    i = random(2);
    set_gender(i);
    
    set_adj(temp1);
    add_adj(temp2);
    
    set_long("This is a dwarf from the Aghar race, or better known as the gully dwarf. " +
             "The " + temp1 + " " + temp2 + " " + query_gender_string() + " dwarf looks rather filthy. You wonder why " +
             "these gully dwarves are living in the sewers of Kalaman in the first place.\n");
    
    set_race_name("gully dwarf");
    add_name("dwarf");

           /* STR DEX CON INT WIS DIS */
    set_stats(({ 60 + random(10), 20 + random(10), 60 + random(10),  23,  23, 70 }));

    set_hp(1000);
    set_alignment(10 + random(40));

    set_default_answer("The " + temp1 + " " + temp2 + " " + query_gender_string() + " dwarf counts on " + query_possessive() + " fingers. One, two. " + 
        "Two! \n" + capitalize(query_pronoun()) + " smiles proudly, showing big gaps in " + query_possessive() + " teeth.\n", 1);
    
    add_ask("plegh", "emote mumbles: Me believes he is king.\n",1);
    add_ask("kalaman", "say Kalaman? Me do not understand.",1);
    add_ask(({"sewer", "sewers"}), "emote frowns and says: Where are those sewers? Me do not see them.",1);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(8 + random(8));
    add_act("@@brain");

    set_cact_time(5);
    add_cact("@@attacked");

    set_all_hitloc_unarmed(30);
    set_knight_prestige(-7);
    
    set_skill(SS_WEP_SWORD, 20 + random(30));
    set_skill(SS_WEP_CLUB, 20 + random(30));
    set_skill(SS_WEP_KNIFE, 20 + random(30));
    set_skill(SS_WEP_POLEARM, 20 + random(30));
    
    set_skill(SS_PARRY, 10 + random(30));
    set_skill(SS_DEFENCE, 10 + random(30));
    set_skill(SS_AWARENESS, 10 + random(15));
    
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_random_height_desc();
    
    set_aggressive(VBFC_ME("check_aggressive"));

    set_alarm(1.0, -1.0, "equipme");
}

int
check_aggressive()
{
    int aggressive;
    
    aggressive = TP->query_prop(I_KILLED_GULLY_DWARF);
    
    return aggressive;
    
}

public void renew_attack();

public void
aggressive_attack(object ob)
{
    int get_attacked = random(3);
    
    if(get_attacked)
    {
        switch(random(5))
        {
        case 0:
            command("shout You hurt me friends! Now you go hurt!!");
        break;
        case 1:
            write("The " + short() + " looks very angry at you.\n");
            say("The " + short() + " looks very angry at " + QTNAME(ob) + "\n");
        break;
        case 2:
            command("emote says: Watch it! I use me magic on you! ");
        break;
        }
        
        ::aggressive_attack(ob);
    }
    else
    {
        switch(random(2))
        {
            case 0:
                write(capitalize(short()) + " looks at you with a strange look in " + query_possessive() + " eyes, and tries to remember what " + query_pronoun() + " has to do.\n");
                say(capitalize(short()) + " looks at " + QCTNAME(ob) + " with a strange look in " + query_possessive() + " eyes, and tries to remembers what " + query_pronoun() + " has to do.\n");
            break;
            case 1:
                command("emote scratches " + query_possessive() + " head, and thinks deeply at what " + query_pronoun() + " was supposed to do.");
            break;
        }
        
        attacker = ob->short();
        
        set_alarm(4.0 + 3.0*rnd(), 0.0, "renew_attack");
    }
        
    
}

void
renew_attack()
{
    switch(random(2))
    {
        case 0:
            command("emote suddenly remembers and shouts a fierce battlecry!");
            command("kill " + attacker);
        break;
        case 1:
            command("emote shrugs briefly. It seems " + query_pronoun() + " forgot what " + query_pronoun() + " had to do.");
        break;
    }
}

void
equipme()
{
    seteuid(getuid());
    
    string *kalaman_armours, *kalaman_hats, *kalaman_weapons, *dwarf_weapons;
    int wear_kalaman_hat, wear_kalaman_armour, weapon_kalaman;
    
    //Armour from the guards, dresses, helmets.. all sort of stuff lying around..
    kalaman_armours = 
                ({"/d/Ansalon/kalaman/obj/armour/chainmail", 
                "/d/Ansalon/kalaman/obj/armour/dress",
                "/d/Ansalon/kalaman/obj/armour/shirt"
                });
    
    kalaman_hats = 
             ({"/d/Ansalon/kalaman/obj/armour/cap",
             "/d/Ansalon/kalaman/obj/armour/winged_helmet"
             });    
    
    kalaman_weapons =
             ({"/d/Ansalon/kalaman/obj/weapon/shortsword",
               "/d/Ansalon/kalaman/obj/weapon/sword",
               "/d/Ansalon/kalaman/obj/weapon/mace",
               "/d/Ansalon/kalaman/obj/weapon/halberd"
             });                    
    
    dwarf_weapons = 
             ({DWARF_OBJECTS + "knife",
               DWARF_OBJECTS + "club",
             }); 
             
    wear_kalaman_hat = random(5);
    wear_kalaman_armour = random(5);
    weapon_kalaman = random(4);
    
    //If its zero, we may wear it..
    if(!wear_kalaman_hat)
    {
        clone_object(one_of_list(kalaman_hats))->move(TO);
    }
    else
    {
        if(random(3))
        {
            clone_object(DWARF_OBJECTS + "hat")->move(TO);
        }
    }
    
    //If its zero, we may wear it..
    if(!wear_kalaman_armour)
    {
        clone_object(one_of_list(kalaman_armours))->move(TO);
    }
    else
    {
        if(random(3))
        {
            clone_object(DWARF_OBJECTS + "rag")->move(TO);
        }
    }
    
    //If its zero, we may wield a kalaman thing..otherwise a homemade item!
    
    if(!weapon_kalaman)
    {
        clone_object(one_of_list(kalaman_weapons))->move(TO);
    }
    else
    {
        if(random(3))
        {
            clone_object(one_of_list(dwarf_weapons))->move(TO);
        }
    }
             
    command("wear all");
    command("wield all");
}


void
brain()
{
    int i;
    
    i = random(5);
    if (i == 1)
    {
        command("say One day me will be king!");
        command("strut");
    }
    else if (i == 2)
    {
        command("emote says: Me can count to two! See?");
        command("emote proudly shows three fingers to you.");
    }
    else if( i == 3 )
    {
        command("emote says: Me saw Highsleg Plegh find new thing! Me think it holy.");
    }
    else if( i == 4 )
    {
        command("emote says: Me see magic stone one time!");
        command("smile broadly");
    }
    else
    {
        command("emote scratches " + query_possessive() + " dirty head.");
    }
}

void
attacked()
{
    int i;
    
    i = random(5);
    if (i == 1)
    {
        command("emote says: What did me do to you?!");
        command("emote squeels fearfully.");
    }
    else if (i == 2)
    {
        command("emote bursts into tears.");
    }
    else if( i == 3 )
    {
        command("emote says: Me heard Calof plans to join knights.. Please don't hurt me!!");
    }
    else if( i == 4 )
    {
        command("emote shuts " + query_possessive() + " eyes fearfully.");
    }
    else
    {
        command("emote says: You bad! Me not do you anthing.");
    }
}

/*
 * Function:      notify_attacked
 * Description:   Called from an associated npc when it is attacked,
 *                for example one in the same team. This npc will
 *                assist if not already fighting.
 * Arguments:     object friend -   the friend who was attacked
 *                object attacker - the attacker
 */
void
notify_attacked(object friend, object attacker)
{
    // If not fighting anyone, assist.
    if (!objectp(query_attack()))
    {
        switch(random(3))
        {
        case 0:
            command("emote says: Why you doing that?!");
            command("assist " + OB_NAME(friend));
        break;
        case 1:
            command("emote looks strangely at you, but doesn't realize " + query_possessive() + " friend is under attack.");
        break;
        case 2:
            command("say to " + OB_NAME(attacker) + " Hey, that not very nice of you! ");
            command("assist " + OB_NAME(friend));
        break;
        }
    }
}

void
do_die(object killer)
{
    switch(random(5))
    {
        case 0:
            command("emote cries so loud, that the entire dwarven clan must have heard " + query_possessive() + " cries.");
            TP->add_prop(I_KILLED_GULLY_DWARF, 1);
        break;
        case 1:
            command("shout Help!! Someone is hurting me bad!");
            TP->add_prop(I_KILLED_GULLY_DWARF, 1);
        break;
        case 2:
            command("emote looks around with a haunting look in " + query_possessive() + " eyes.");
        break;
    }
    
    ::do_die(killer);
}



