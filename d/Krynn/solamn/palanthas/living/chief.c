/*
 * Created by Aridor 06/19/93
 *
 * Updated with power by Mortis 02.2006
 *
 * Gave him key to his chambers in the Tower of Arms
 * Mortis 09.2014
 */

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include "../local.h"

#define MY_ARMOUR            MERCH + "arms/larmour"

inherit M_FILE
inherit "/std/act/action";

/*prototypes*/
string my_answer();
void arm_me();

int on_a_mission = 0;

object last_room;
object the_prisoner;
object para; /*paralyser of the_prisoner*/

void
create_krynn_monster()
{
    seteuid(getuid(TO));

    set_name("hagen");
    set_living_name("hagen");
    add_name(({"chief", "constable", "human"}));
    add_adj(({"pale-faced", "red-bearded"}));
    set_short("pale-faced red-bearded constable");
    set_long("The constable is a hulking, pale-faced man with thin red "
    + "hair and beard in his early forties.  He is well-groomed, manicured, "
    + "and has watchful tan eyes.\nHe has a scar on his chin.\nHe is "
    + "extremely alert.\nHe has a commanding presence among the citizenry.\n");
    set_race_name("human");
    set_title("Gerber, Chief Constable of Palanthas the Beautiful");
    
    set_gender(G_MALE);
    set_size_descs("extremely tall", "of normal width");
    set_appearance(5);
    
    set_stats(({165, 160, 195, 130, 145, 210})); // Champion

    set_skill(SS_AWARENESS,    90);
    set_skill(SS_RIDING,       30);
    set_skill(SS_PARRY,        50);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_WEP_CLUB,     90);
    set_skill(SS_BLIND_COMBAT, 85);

    set_all_attack_unarmed(85, 50);
    set_all_hitloc_unarmed(75);
    
    set_alignment(1000);
    set_knight_prestige(-225);
    set_introduce(1);

    set_act_time(30);
    add_act("say If you have a form you can show me, I'll tell you what "
    + "to do.");
    add_act("say Ahhh, boy do I feel good today!");
    add_act("say I can't wait till someone nasty comes along.");
    
    set_cact_time(9);
    add_cact("say Surrender or die!");
    add_cact("say Surrender or die.  There are no exceptions.");

    add_ask("form", "@@answer_show_form");
    add_ask("sign form", "@@sign_form_with_form");
    add_ask("to sign form", "@@sign_form_with_form");
    add_ask(({"jail","free","free from jail","free prisoner","prisoner",
    "release","release prisoner","release from jail",
    "release prisoner from jail"}), "@@free_prisoner");

    set_default_answer("@@my_answer");

    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object ilet, unif, cclub, cboots, cgloves, cbelt, carmet, tkey, jkey;

    ilet = clone_object(OBJ + "iletter");
    ilet->move(TO);

    unif = clone_object(OBJ + "uniform");
    unif->move(TO);

    cclub = clone_object(MERCH + "arms/smith_club");
    cclub->set_weapon_data("shining" + "&&"
                            + "hooked" + "&&"
                            + "hammer");
    cclub->move(TO);

    cboots = clone_object(MY_ARMOUR);
    cboots->set_armour_data("heavy" + "&&"
                            + "white" + "&&"
                            + "leather" + "&&"
                            + "boots");
    cboots->move(TO);

    cgloves = clone_object(MY_ARMOUR);
    cgloves->set_armour_data("heavy" + "&&"
                            + "white" + "&&"
                            + "leather" + "&&"
                            + "gloves");
    cgloves->move(TO);

    cbelt = clone_object(MY_ARMOUR);
    cbelt->set_armour_data("plain" + "&&"
                            + "white" + "&&"
                            + "soft" + "&&"
                            + "belt");
    cbelt->move(TO);

    carmet = clone_object(MY_ARMOUR);
    carmet->set_armour_data("noble" + "&&"
                            + "white" + "&&"
                            + "hard" + "&&"
                            + "armet");
    carmet->move(TO);

    // Tower of Arms key to Constable's quarters
    tkey = clone_object(TOA + "doors/toa_constable_key");
    tkey->move(TO);

    // Jail key
    jkey = clone_object(OBJ + "jail_key");
    jkey->move(TO);

    command("wear all");
    command("wield all");
}


/*how = 0 means someone paid the fee
 *how = 1 means prisoners are pardoned */
perform_the_release(int how)
{
    int i;
    object key, *livings;
    key = clone_object(OBJ + "jail_key");
    key->move(TO);
    command("unlock bars with key");
    command("open bars");
    command("n");
    if (how)
      command("say You are released, the Lord of Palanthas has pardoned you.");
    else
      command("say You are released, the ransom fee has been paid.");
    livings = all_inventory(environment(TO));
    command("s");
    for (i = 0; i < sizeof(livings); i++)
      livings[i]->command("south");
    command("close bars");
    command("lock bars with key");
    if (!how)
      if (sizeof(livings) < 1)
    TP->remove_prop("_has_payed_ransom");
      else
    {
        command("say Hmm, strange, no one was in jail.");
        command("shrug");
    }
    key->remove_object();
}


free_prisoner()
{
    object the_form = present("form", TP);
    string *slots, dummy;
    
    if (!the_form)
      {
      command("say I need a form filled in asking for the release of " +
          "the prisoner.");
      command("say The form must be signed by Chivo with proof of the " +
          "payment of the ransom fee and approved by the judge!");
      command("say Then I can release the prisoner.");
      }
    else
      {
      slots = the_form->query_form_slots();
      if (slots[1] == "Chivo (Tax Collector)" &&
          slots[0] == "Ransom fee paid."
          && slots[2] == "Jodico (Judge)" &&
          (sscanf(the_form->query_form_purpose(),"%srelease%s",dummy,dummy) == 2))
        {
        command("say Ok, the form you have is valid.");
        perform_the_release(0);
        the_form->remove_object();
        }
      else
        {
        command("say I'm sorry, but the form you are carrying is " +
            "not valid to free the prisoner.");
        command("say I need the signature of Chivo with the proof " +
            "of payment and the signature of the judge.");
        }
      }
    return "";
}

answer_show_form()
{
    command("say Show me the form and i'll tell you what to do.");
    return "";
}

int
react_bow(object actor)
{
    command("emote bows curtly.");
    return 1;
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

init_living()
{
    add_action("sign_form","sign");
    add_action("examine_form","show");

    ::init_living();
}

string
my_answer()
{
    set_alarm(1.0, 0.0, "command", "shrug");
    set_alarm(1.5, 0.0, "command", "say I cannot help you with that.");
    return "";
}



int
sign_form(string str)
{
    command("say I don't have the privilege to sign forms.");
    command("say Ask the supervisor for that, I know he has to signs " +
        "forms all the time.");
    return 1;
}


string
sign_form_with_form()
{
    sign_form("form");
    return "";
}


int
examine_form(string str)
{
    sign_form(str);
    return 1;
}


perform_the_arrest(string str)
{
    NF("What?\n");
    if (TP != the_prisoner)
      return 0;

    TP->command("say I surrender!");
    TP->stop_fight(TP->query_enemy(-1));
    stop_fight(TP);
    command("say You are under arrest!");

     seteuid(getuid(TO));

    para = clone_object(OBJ + "chief_paralyze");
    para->move(the_prisoner, 1);

    the_prisoner->add_prop(LIVE_O_ENEMY_CLING, TO);
    add_prop(LIVE_O_ENEMY_CLING, the_prisoner);
    tell_room(E(TO), QCTNAME(TO) + " gags " + QCTNAME(the_prisoner) + ".\n",
          the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " gags you.\n");
    tell_room(E(TO), QCTNAME(TO) + " ties " + QCTNAME(the_prisoner) + " up.\n",
          the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " ties you up.\n");
    
    set_alarm(10.0, 0.0, "go_from_here_to_judge");
    return 1;
}

fight_till_surrendered(object who)
{
    object *ene;
    if (E(who) != E(TO))
      return;
    /*add_action("perform_the_arrest","surrender"); handled below...*/
    add_action("cant_do_it","",1);
    ene = who->query_enemy(-1);
    who->stop_fight(ene);
    ene->stop_fight(who);
    attack_object(who);
    command("emote charges in to protect the citizen.");
    command("say SURRENDER or die, " + one_of_list(({"miscreant", "foul one",
        "evildoer", "ne'er do well", "B"})) + "!");
    who->attack_object(TO);
}

cant_do_it(string str)
{
    int ret;
    if (TP != the_prisoner)
      return 0;
    if (query_verb() == "surrender")
      return perform_the_arrest(str);
    switch(query_verb())
      {
    case "north":
    case "east":
    case "south":
    case "west":
    case "up":
    case "down":
    case "northwest":
    case "northeast":
    case "southwest":
    case "southeast":
    case "out":
      command("say Oh no, you're not going anywhere! Surrender!");
      command("say You don't have a chance against me, just surrender " +
          "if you want to stay alive!");
      attack_object(TP);
      ret = 1;
      break;
    default:
      ret = 0;
      }
    return ret;
}

arrest_prisoner(mixed who, object where)
{
    if (on_a_mission)
      return;/*lucky 'who'!!!!!*/
    if (stringp(who))
      the_prisoner = find_living(who);
    else if (objectp(who))
      the_prisoner = who;
    else
      return;
    if (!where->query_to_jail())
      return; /*outside the limits...*/
    if (E(the_prisoner) != where)
      return;
    on_a_mission = 1;
    move_living("dashing out the door", where); 
    fight_till_surrendered(who);
}


go_from_here_to_judge()
{
    string marke;
    object jud;
    if (last_room == E(TO))
      return;
    last_room = E(TO);
    marke = E(TO)->query_to_jail();
    if (!marke)
      return;
    if (marke == "END_TOKEN")
      {
      command("say We're here! Better behave yourself now.");
      if (jud = present("jodico", E(TO)))
        jud->sentence_prisoner(TO, the_prisoner);
      else
        put_prisoner_into_jail();
      return;
      }
    if (pointerp(marke))
      {
      command(marke[0]);
      command(marke[1]);
      }
    else
      {
      command(marke);
      }
    drag_the_prisoner_along();
    set_alarm(5.0,0.0,"go_from_here_to_judge");
}


put_prisoner_into_jail()
{
    if (the_prisoner->query_guild_member("Solamnian Knights"))
      ("/d/Krynn/solamn/vkeep/mnstrs/gunthar")->add_bad_guy(LANG_ADDART(the_prisoner->query_nonmet_name()),
                                "the Lord of Palanthas",
                                "attacked a citizen there");
    set_alarm(10.0,0.0,"start_going");
}

start_going()
{
    object key;
    command("west");
    drag_the_prisoner_along();
    command("north");
    drag_the_prisoner_along();
    command("north");
    drag_the_prisoner_along();
    command("north");
    drag_the_prisoner_along();
    command("west");
    drag_the_prisoner_along();
    (key = clone_object(OBJ + "jail_key"))->move(TO);
    command("unlock bars with key");
    command("open bars");
    command("n");
    drag_the_prisoner_along();
    command("say Enjoy your stay!");
    get_prisoner_ready_for_jail();
    command("s");
    command("close bars");
    command("lock bars with key");
    release_prisoner_from_ties();
    key->remove_object();
    on_a_mission = 0;
    set_alarm(itof(600 + random(600)),0.0,"perform_the_release", 1);
}

get_prisoner_ready_for_jail()
{  
    tell_room(E(TO), QCTNAME(TO) + " unties " + QTNAME(the_prisoner) + ".\n",
          the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " unties you, but you still are " +
                "too stiff to do anything.\n");
    para->set_fail_message("You are still too stiff to do anything.\n");
    
    write_file(TDIR + "log/jaillog", extract(ctime(time()), 4, 15)
           + " " + capitalize(the_prisoner->query_real_name()) + "\n");
}


release_prisoner_from_ties()
{
    /*remove prestige if it is a knight */
    the_prisoner->change_prestige(-4);

    para->remove_object();
    the_prisoner->catch_msg("You feel like you can move again.\n");
}


release_prisoner()
{
    release_prisoner_from_ties();
    command("west");
    command("north");
    command("north");
    command("north");
    command("west");
    on_a_mission = 0;
}


drag_the_prisoner_along()
{
    tell_room(E(the_prisoner), QCTNAME(TO) + " drags " + 
          QTNAME(the_prisoner) + " out.\n", the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " drags you along.\n");
    the_prisoner->move(E(TO));
    tell_room(E(the_prisoner), QCTNAME(TO) + " drags " +
          QTNAME(the_prisoner) + " in.\n", the_prisoner);
}

void
attacked_by(object ob)
{
    ob->add_prop(LIVE_I_ATTACKED_PALANTHAS, 1);
    command("chuckle");

    ::attacked_by(ob);
}

int
special_attack(object enemy)
{
    int pen, att;
    string hitloc, how, how2;
    mixed hitres;

    if (random(10))
    {
        pen = 200 + random(400);
        
        hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1, A_TORSO);

        switch (hitres[0])
        {
            case -1..0:
                how = " with no effect";
                how2 = " with no effect";
                break;
            case 1..9:
                how = ", collapsing your stomach painfully";
                how2 = ", collapsing " + HIS(enemy) + " stomach painfully";
                break;
            case 10..16:
                how = ", his fist sinking into your stomach.\nYou blow chunks "
                + "on your shoes";
                how2 = ", his fist sinking into " + HIS(enemy) + " stomach "
                + "painfully.\n" + QCTNAME(enemy) + " blows chunks on "
                + HIS(enemy) + " shoes";
                break;
            case 17..30:
                how = " with a painfully squishy blunk noise that bulges your "
                + "eyes out";
                how2 = " with a painfully squishy blunk noise that bulges "
                + HIS(enemy) + " eyes out";
                break;
            case 31..43:
                how = " with a massive and punishing blow that echoes through "
                + "your bowels";
                how2 = " with a massive and punishing blow that echoes "
                + "through " + HIS(enemy) + " bowels";
                break;
            case 44..66:
                how = " relentlessly until you double over with blood "
                + "trickling from all your orifaces";
                how2 = " relentlessly until " + HE(enemy) + " doubles over "
                + "with blood trickling from all " + HIS(enemy) + " orifaces";
                break;
            default:
                how = ", knocking a chunk of your stomach out your back "
                + "leaving a gaping hole.\nYou whimper meekly";
                how2 = ", knocking a chunk of " + HIS(enemy) + " stomach out "
                + HIS(enemy) + " back leaving a gaping hole.\n"
                + QCTNAME(enemy) + " whimpers meekly";
                break;
        }

        enemy->catch_msg(QCTNAME(TO) + " gut punches you" + how + ".\n");
        tell_room(E(TO), QCTNAME(TO) + " gut punches " + QTNAME(enemy) + how2
        + ".\n", ({enemy, TO}));

        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);

        return 1;
    }

    return 0;
}

void
do_die(object killer)
{
    para->remove_object();
    ::do_die(killer);
}
