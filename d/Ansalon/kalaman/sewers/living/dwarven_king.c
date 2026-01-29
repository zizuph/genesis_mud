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
inherit "/lib/unique";

object attacker;

void
create_krynn_monster()
{
    int i;
    string name, *first, *second, temp1, temp2;

    set_gender(0);

    set_name("plegh");

    set_living_name("Plegh");
    set_title("the King of the Sleg Dwarven Clan");

    set_adj("proud");
    add_adj("gray-haired");

    set_long("Althrough the dwarf looks pretty old, he stands ground with much pride. " +
             "This dwarf probably holds authority here, and has earned a lot of respect " +
             "amongst the other dwarves. \n");


    set_race_name("gully dwarf");
    add_name("dwarf");

           /* STR DEX CON INT WIS DIS */
    set_stats(({ 70 + random(10), 100 + random(20), 70 + random(10),  53,  43, 110 }));

    set_hp(1000);
    set_alignment(10 + random(40));

    set_default_answer("emote shrugs briefly, clearly not interested in what you have to say.", 1);

    add_ask(({"plegh", "king"}), "say Me is Plegh!.",1);
    add_ask("kalaman", "emote says: Kalaman? Me do not understand.",1);
    add_ask(({"sewer", "sewers"}), "emote frowns and says: Where are those sewers? Me do not see them.",1);

    add_prop(NPC_I_NO_RUN_AWAY, 1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(8 + random(8));
    add_act("@@brain");

    set_cact_time(5);
    add_cact("@@attacked");

    set_all_hitloc_unarmed(30);
    set_knight_prestige(-20);

    set_skill(SS_WEP_SWORD, 50 + random(30));
    set_skill(SS_WEP_CLUB, 50 + random(30));
    set_skill(SS_WEP_KNIFE, 50 + random(30));
    set_skill(SS_WEP_POLEARM, 50 + random(30));

    set_skill(SS_PARRY, 50 + random(30));
    set_skill(SS_DEFENCE, 50 + random(30));
    set_skill(SS_AWARENESS, 50 + random(15));

    add_prop(NPC_I_NO_LOOKS, 1);

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

public void
aggressive_attack(object ob)
{

    switch(random(5))
    {
        case 0:
            command("shout You hurt me clan! Now you go hurt!!");
        break;
        case 1:
            write(QCTNAME(TO) + " looks very angry at you.\n");
            say(QCTNAME(TO) + " looks very angry at " + QTNAME(ob) + "\n");
        break;
        case 2:
            command("emote says: Now you die! ");
        break;
    }

    ::aggressive_attack(ob);
}

/*
 * Function name: answer_question
 * Description:   This function is called after a short delay when this mobile
 *                wants to react to a question
 * Arguments:     An array ({ mixed msg, int cmd })
 */
void
answer_question(mixed msg, int cmd)
{
   /* object env;

    tell_object(find_player("arcturus"), "test")

    if ((env = environment(this_object())) == environment(this_player()) ||
            env == this_player() || (not_here_func &&
                call_other(this_object(), not_here_func, this_player())))
    {
        msg = this_object()->check_call(msg, this_player());

        command(msg);
    }*/
}


void
add_introduced(string name)
{
    command("introduce me to " + name);
}

void
equipme()
{
    seteuid(getuid());

    object stone;
    string *kalaman_armours, *kalaman_hats, *kalaman_weapons, *dwarf_weapons;

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

    clone_object(one_of_list(kalaman_hats))->move(TO);
    clone_object(one_of_list(kalaman_armours))->move(TO);
    clone_object(one_of_list(kalaman_weapons))->move(TO);
    clone_object("/d/Ansalon/kalaman/obj/armour/gauntlets")->move(TO);
    clone_object("/d/Ansalon/kalaman/obj/armour/leggings")->move(TO);


    stone = clone_unique(OBJECTS + "magic_stone", 15,
          OBJECTS + "plain_stone");

    stone->move(TO);


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
        command("say Highsleg is hard work!");
        command("smile");
    }
    else if (i == 2)
    {
        command("emote says: Me wield important weapon!");
        command("show weapon");
    }
    else if( i == 3 )
    {
        command("emote says: I think stone is holy!");
    }
    else if( i == 4 )
    {
        command("emote says: Me used magic stone on human one time!");
        command("giggle mischievously");
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
        command("emote says: Please do not take me holy stone!");
        command("sob");
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

string
query_presentation()
{
    return "High " + ::query_presentation();
}

int
special_attack(object enemy)
{

    attacker = enemy;

    //1 on 4 times, we let it through..
    if(random(4))
        return 0;

    switch(random(3))
    {
        case 0:
            enemy->catch_msg(QCTNAME(TO) +
              " takes something from his pocket, points it at you, and shouts: MAGIC!\n");

            tell_room(QCTNAME(TO) +
              " takes something from his pocket, points it at " + QTNAME(enemy) + ", and shouts: MAGIC!\n");
            break;
        case 1:
                command("emote throws up his hands as if conjuring magic.");
            break;
        case 2:
                command("emote closes his eyes and quickly mumbles something.");
            break;
    }

    set_alarm(2.0 + 2.0*rnd(), 0.0, "exec_special");

    return 1;

}


void
exec_special()
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    rock;

    attacktype = random(4);

    if(!attacktype)
    {
        hitloc = ({"left arm","right arm","body","left leg","right leg"});

        pen = 400 + random(200);
        hitres = attacker->hit_me(pen, W_IMPALE, TO, -1);

        wloc = random(5);
        att  = random(2);

        rock = "Suddenly a big sharp rock falls down and ";

        if (hitres[0] <= 0)
            how = "barely misses ";
        if(hitres[0] > 0)
            how = "lightly grazes ";
        if(hitres[0] > 10)
            how = "slices a shallow wound in ";
        if(hitres[0] > 20)
            how = "cuts a gash across ";
        if (hitres[0] > 40)
            how = "cuts a deep gash into ";
        if (hitres[0] > 60)
            how = "lethally injures ";

        attacker->catch_msg(rock + how + "your " + one_of_list(hitloc) + ".\n");

        tell_room(rock + how + OBJECTIVE(attacker) + one_of_list(hitloc) + ".\n");

        if (attacker->query_hp() <= 0)
        {
            attacker->do_die(TO);
        }
    }
    else
    {
        switch(random(3))
        {
            case 0:
                command("emote look at the ceiling expectantly.");
                break;
            case 1:
                command("emote frowns deeply at the ceiling.");
                break;
            case 2:
                command("emote looks confused, because nothing seems to happen.");
                break;

        }

    }

}



