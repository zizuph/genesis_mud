inherit "/std/monster";
 
#include "default.h"
#define G_MALE 0
 
void
create_monster()
{
    set_name("paladin");
    set_living_name("_mylos_paladin1_");
    set_race_name("elf");
    set_short("paladin");
    set_long("This powerful warrior is dedicated to the elven Gods to " +
             "protect the inhabitants of Telberin. He is well-built and " +
             "looks very confident with his sword.\n");
 
    set_base_stat(SS_STR, 101);
    set_base_stat(SS_DEX, 155);
    set_base_stat(SS_CON, 146);
    set_base_stat(SS_INT, 114);
    set_base_stat(SS_WIS, 112);
    set_base_stat(SS_DIS, 106);
 
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_WEP_KNIFE, 77);
    set_skill(SS_DEFENCE, 54);
    set_skill(SS_PARRY, 55);
    set_alignment(1000);
 
    set_all_hitloc_unarmed(5); /* Inherent AC of 5 */
 
    add_prop(CONT_I_WEIGHT, 71000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 71000);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_chat_time(15);                             /* Set speaking interval */
    add_chat("Hmmm. Things art quiet around here.");
    add_chat("Greetings stranger! How art thou?");
 
 
    set_cchat_time(8);                      /* Set combat speaking interval */
    add_cchat("Thou art making a mistake my friend.");
    add_cchat("I think that thee ought to reconsider thy actions.");
 
 
    set_act_time(10);                    /* Set action interval           */
    add_act("ponder");
    add_act("smile");
    add_act("hmm");
 
    trig_new("%w 'smiles' %s", "react_smile");
    trig_new("%w 'shakes' %w 'head' %s", "react_shake");
    trig_new("%w 'bows' %s", "react_bow");
}
 
int
react_bow(string who, string dummy)
{
    object obj;
 
    if(who)
    {
        who = lower_case(who);
        obj = present(who, environment());
        if (obj && !obj->query_npc())
        {
            switch(random(3))
            {
            case 0:
                command("say Greetings.");
                break;
            case 1:
                command("bow to " + who);
                break;
            default:
                command("say Nice to meet you, " +
                        obj->query_nonmet_name() +".");
                break;
            }
        }
    }
    return 1;
}
 
int
react_smile(string who, string dummy)
{
    object obj;
 
    if (who)
    {
        obj = present(lower_case(who), environment());
        if (obj && !obj->query_npc())
        {
            switch (random(3))
            {
            case 0:
                command("say Nice to see that you are happy, " +
                        obj->query_nonmet_name() + "?");
                break;
            case 1:
                command("shake " + who);
                break;
            default:
                command("say It's a lovely day today, " +
                        obj->query_nonmet_name() + "?");
                break;
            }
        }
    }
    return 1;
}
 
 
 
void
add_introduced(string who)
{
    object obj;
    int ran;
 
    if (who)
    {
        obj = present(who, environment());
        if (obj && !obj->query_npc())
        {
            switch (random(3))
            {
            case 0:
                command("say Nice to meet you, " + obj->query_name() + ".");
                command("bow to " + who);
                break;
 
            case 1:
                command("bow to " + who);
                break;
            default:
                command("say How are you, " + obj->query_race() + "?");
                command("bow to " + who);
                break;
            }
        }
    }
}
 
string
fix_name(object player)
{
    switch(player->query_race())
    {
    case "elf":
        return "elves";
        break;
    case "dwarf":
        return "dwarves";
        break;
    case "human":
        return "humans";
        break;
    case "gnome":
        return "gnomes";
        break;
    case "hobbit":
        return "hobbits";
        break;
    case "goblin":
        return "goblins";
        break;
    default:
        return "some";
        break;
    }
}
 
 
int
react_shake(string who, string dummy1, string dummy2)
{
    object obj;
 
    if (who)
    {
        obj = present(lower_case(who), environment());
        switch (random(3))
        {
        case 0:
            command("say Really, " + obj->query_race() + "?");
            break;
        case 1:
            command("say I agree with you, " +
                    ((obj->query_gender() == G_MALE) ? "master" : "lady") +
                    ".");
            break;
        default:
            who = fix_name(obj);
            command("say Why " + who + " always disagree?");
        }
    }
    return 1;
}
 
void
arm_me()
{
    clone_object(WEP_DIR + "e_longs")->move(this_object(), 1);
    clone_object(WEP_DIR + "dirk")->move(this_object(), 1);
    clone_object(ARM_DIR + "w_plate")->move(this_object(), 1);
    clone_object(ARM_DIR + "w_hel")->move(this_object(), 1);
    command("wield all");
    command("wear all");
 
}
 
void
attacked_by(object attacker)
{
    int i;
    object *guards;
 
    tell_object(attacker, "Hey you attacked me!\n");
    command("shout We are under attack!");
    command("shout Attack " + attacker->query_objective() + "!");
    command("point " + attacker->query_real_name());
    tell_room(environment(this_object()), "The guards shouts, 'Yes, Sir!' " +
              "in unison.\n");
    dump_array(guards = query_team());
    map(guards, &->attack_object(attacker));
    return;
}
