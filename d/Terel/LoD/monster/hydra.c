/*
 *  A three-headed hydra. Mortricia 960110
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

#define PHURT_CHOP_LIM 13
#define HEAD_GROW_BACK (250 + random(50))

#define ACTS   ({"grins", "hisses", "looks at you", "stares at you"})
#define CACTS  ({"spits at you", "hisses at you", "screams"})

#define A_CLAWS       0
#define A_LEFTBITE    1
#define A_MIDDLEBITE  2
#define A_RIGHTBITE   3

#define H_BODY        0
#define H_LEFTHEAD    1
#define H_MIDDLEHEAD  2
#define H_RIGHTHEAD   3

public void add_head_attack();
public void add_head_hitloc();
public int query_heads();

int   *heads = ({1, 1, 1});
int   *h_alarms = ({0, 0, 0});
int    alarm_id = 0;
object chain = 0;

public void
create_creature()
{
    ::create_creature();

    set_name("hydra");
    set_adj(({"giant", "three-headed"}));
    set_long("A giant three-headed hydra.@@head_long@@ " +
             "It has also three long necks protruding from " +
             "the huge, fat body, all covered with scales. " +
             "Two relatively small limbs with claws extend " +
             "from the body. The hind legs are hidden, " +
             "but you can discern a large muscular tail.\n");
    set_race_name("hydra");

    set_stats(({100, 104, 95, 70, 82, 90}));
    set_hp(9999);
    set_mana(9999);
    set_gender(2);
    set_alignment(0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME,  200000);
    add_prop(CONT_I_MAX_WEIGHT, 280000);
    add_prop(CONT_I_MAX_VOLUME, 280000);
    add_prop(LIVE_I_QUICKNESS, 80);
    add_prop(LIVE_I_SEE_DARK, 10);
    set_skill(SS_DEFENCE,      87);
    set_skill(SS_PARRY,        55);
    set_skill(SS_AWARENESS,    95);
    set_skill(SS_LOC_SENSE,    50);

    add_item(({"head", "heads"}),  "@@head_item@@\n");
    add_item("left head", "@@left_head_item@@\n");
    add_item("middle head", "@@middle_head_item@@\n");
    add_item("right head", "@@right_head_item@@\n");
    
    add_item("body", "It's covered with thick scales.\n");
    add_item("scales", "They seem to provide excellent protection.\n");
    add_item("claws", "They are very sharp.\n");
    
    set_act_time(4);
    set_cact_time(2);
    add_act("@@head_act");
    add_cact("@@head_cact");
}

public string
head_long()
{
    int n = query_heads();
        
    if (n == 0)
        return " It has no heads! Someone must have chopped them off. " +
               "It's amazing that the " + short() + " still is alive.";
    if (n == 1)
        return " It has only one head left.";
    if (n == 2)
        return " One of the heads is missing though.";

    return " Maybe you can chop the heads off?";
}

public string
head_item()
{
    string end = " The heads resemble to some extent that of a snake.";
    int n = query_heads();

    if (n == 0)
        return "It has no heads! Amazing it's still alive.";
    if (n == 1)
        return "It has only one head left." + end;
    if (n == 2)
        return "It has two heads." + end;

    return "There are three heads." + end +
           " Maybe you can chop them off?";
}

public string
left_head_item()
{
    if (heads[0])
        return "The left head is looking at you.";
    else
        return "The left head has been chopped off. Strangely, " +
               "there is no blood pouring from the wound on the neck.";
}

public string
middle_head_item()
{
    if (heads[1])
        return "The middle head is sniffing at you.";
    else
        return "The middle head has been chopped off. Strangely, " +
               "there is no blood pouring from the wound on the neck.";
}

public string
right_head_item()
{
    if (heads[2])
        return "The right head seems to be listening in your direction.";
    else
        return "The right head has been chopped off. Strangely, " +
               "there is no blood pouring from the wound on the neck.";
}

public object
find_victim()
{
    object *all = filter(all_inventory(ETO) - ({ TO }), living);
    
    all = filter(all, &operator(<)(,60) @ &->query_average_stat());
    
    if (!sizeof(all))
        return 0;
    
    return all[random(sizeof(all))];
}

public string
head_act()
{
    int h = random(3), dam;
    string desc = "emote shivers from the loss of a head.";
    string which = "left", what;
    object victim = find_victim();
    
    if (h == 1) which = "middle";
    if (h == 2) which = "right";

    if (heads[h])
    {
        if (victim && !random(4))
        {
            if (victim->query_race_name() == "bat")
            {
                tell_room(ETO, QCTNAME(TO) + " flings out its " + which +
                          " head and snatches " + QTNAME(victim) +
                          " in mid air!\n", victim);
                victim->command("scream");
                victim->remove_object();
                desc = "emote spits out some bones with its " + which +
                       " head.";
            }
            else
            {
                victim->catch_msg(QCTNAME(TO) + " flings out its " +
                          which + " head toward you and bites you!\n");
                tell_room(ETO, QCTNAME(TO) + " flings out its " + which +
                          " head toward " + QTNAME(victim) +
                          " and bites " + victim->query_objective() +
                          "!\n", victim);
                tell_room(ETO, CAP(victim->query_pronoun()) +
                               " was taken completely off-guard!\n",
                               victim);
                victim->catch_msg("Ouch! That hurt!\n");
                victim->command("$scream");
                dam = 1500 - 10*(victim->query_stat(SS_CON));
                if (dam < 100) dam = 100;
                victim->reduce_hit_point(dam);
                if (victim->query_hp() > 0)
                    victim->add_panic(40);
                else
                    victim->do_die(TO);
                desc = "emote spits out something with its " + which +
                       " head.";
            }
        }
        else
        {
            what = (string)ACTS[random(sizeof(ACTS))];
            desc = "emote " + what + " with its " + which + " head.";
        }
    }
    
    return desc;
}

public string
head_cact()
{
    int h = random(3);
    string desc = "emote shivers from the wounds.";
    string which = "left", what;
    
    if (h == 1) which = "middle";
    if (h == 2) which = "right";
    
    if (heads[h]) {
        what = (string)CACTS[random(sizeof(CACTS))];
        desc = "emote " + what + " with its " + which + " head.";
    }
        
    return desc;
}

public int
query_heads()
{
    int i, n = 0;
    
    for (i=0; i<3; i++)
        if (heads[i]) n++;
        
    return n;
}

public void
cr_configure()
{
    add_head_attack();
    add_head_hitloc();
}

public void
add_head_attack()
{
    int n = query_heads();
    int h, p;
    
    add_attack(20, 25, W_SLASH, 100 - n*30, A_CLAWS);
    
    if (n == 0) return;
    
    h = 55 + random(11) + 3*n;
    p = 55 + random(11) - 3*n;
    if (heads[0]) add_attack(h, p, W_IMPALE, 30, A_LEFTBITE);
    if (heads[1]) add_attack(h, p, W_IMPALE, 30, A_MIDDLEBITE);
    if (heads[2]) add_attack(h, p, W_IMPALE, 30, A_RIGHTBITE);
}

public void
add_head_hitloc()
{
    int n = query_heads();
    
    add_hitloc(({70, 75, 80}), 100 - n*10, "body",  H_BODY);
    
    if (n == 0) return;
    
    if (heads[0]) add_hitloc(({30, 30, 35}), 10, "left head",   H_LEFTHEAD);
    if (heads[1]) add_hitloc(({30, 30, 35}), 10, "middle head", H_MIDDLEHEAD);
    if (heads[2]) add_hitloc(({30, 30, 35}), 10, "right head",  H_RIGHTHEAD);
}

public void
remove_all()
{
    remove_hitloc(H_BODY);
    if (heads[0]) remove_hitloc(H_LEFTHEAD);
    if (heads[1]) remove_hitloc(H_MIDDLEHEAD);
    if (heads[2]) remove_hitloc(H_RIGHTHEAD);
    
    remove_attack(A_CLAWS);
    if (heads[0]) remove_attack(A_LEFTBITE);
    if (heads[1]) remove_attack(A_MIDDLEBITE);
    if (heads[2]) remove_attack(A_RIGHTBITE);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
      case A_CLAWS:return "sharp claws";
      case A_LEFTBITE:return "deadly fangs in its left head";
      case A_MIDDLEBITE:return "deadly fangs in its middle head";
      case A_RIGHTBITE:return "deadly fangs in its right head";
    }
}

public void
new_head(int h)
{
    string what = "left neck";
    
    h_alarms[h] = 0;
    
    if (heads[h]) return;
    
    remove_all();
    heads[h] = 1;
    
    add_head_attack();
    add_head_hitloc();
    
    if (h == 1) what = "middle neck";
    if (h == 2) what = "right neck";
    
    tell_room(ETO, "A new head emerges on " + QTNAME(TO) + "'s " +
                   what + "!\n", TO);
                   
    if (chain) {
        tell_room(ETO, QCTNAME(TO) + " notices the " + chain->short() +
                  ". It simply eats it up with its new head!\n");
        chain->remove_object();
        chain = 0;
    }
}

public void
chop_off_head(object who, string what, string with, int h)
{
    remove_all();
    
    heads[h] = 0;
    
    add_head_attack();
    add_head_hitloc();
    
    alarm_id = 0;
    
    h_alarms[h] = set_alarm(itof(HEAD_GROW_BACK), -1.0, &new_head(h));
    
    if (!who) {
        tell_room(ETO, "Due to its severe wounds, " + QTNAME(TO) +
                       "'s " + what + " falls off!\n", TO);
        return;
    }
    
    if (ETO == ENV(who)) {
        who->catch_msg("You chop off the " + what + " of " +
                       QTNAME(TO) + " with your " +  with + "!\n");
        tell_room(ETO, QCTNAME(who) + " chops off the " + what +
                       " of " + QTNAME(TO) + " with " +
                       who->query_possessive() + " " + with +
                       "!\n", ({who, TO}));
    } else {
        tell_room(ETO, "Due to the fierce attack by " + QTNAME(who) +
                       ", " + QTNAME(TO) + "'s " + what +
                       " falls off!\n", TO);
    }
    
    if (heads[0])
        command("emote screams painfully using its left head.");
    if (heads[1])
        command("emote screams with anger using its middle head.");
    if (heads[2])
        command("emote screams threatingly using its right head.");
    
    return;
}

public varargs void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    int h;
    string desc = "", with = "fierceful attack";
    object cob;
    
    if (alarm_id) return;
    
    if (dt != W_IMPALE && dt != W_SLASH) return;
    
    if (ph <= PHURT_CHOP_LIM || dam <= 0) return;
    
    switch (hid) {
        case H_LEFTHEAD:
            desc = "left head";
            h = 0;
            break;
        case H_MIDDLEHEAD:
            desc = "middle head";
            h = 1;
            break;
        case H_RIGHTHEAD:
            desc = "right head";
            h = 2;
            break;
        default:
            return;
    }
    
    cob = att->query_combat_object();
    if (cob)
        with = (string)cob->cb_attack_desc(aid);
    
    alarm_id = set_alarm(1.0, -1.0,
                         &chop_off_head(att, desc, with, h));
}

public int
try_pass(object who, string where)
{
    if (!who || !present(who, ETO))
        return 0;
    
    if (heads[0] && CAN_SEE(TO, who))
    {
        who->catch_msg(QCTNAME(TO) + "'s left head sees you " +
                       "and blocks the way.\n");
        tell_room(ETO, QCTNAME(TO) + " stops " + QTNAME(who) +
                       " from going " + where + ".\n", who);
        return 0;
    }
    if (heads[1])
    {
        who->catch_msg(QCTNAME(TO) + "'s middle head smells you " +
                       "and blocks the way.\n");
        tell_room(ETO, QCTNAME(TO) + " stops " + QTNAME(who) +
                       " from going " + where + ".\n", who);
        return 0;
    }
    if (heads[2])
    {
        who->catch_msg(QCTNAME(TO) + "'s right head hears you " +
                       "and blocks the way.\n");
        tell_room(ETO, QCTNAME(TO) + " stops " + QTNAME(who) +
                       " from going " + where + ".\n", who);
        return 0;
    }
    if (!chain || random(who->query_stat(SS_DEX)) <
                  45 + random(query_skill(SS_AWARENESS)))
    {
        who->catch_msg("Despite that " + QTNAME(TO) + " has lost " +
                       "all its heads it somehow senses your " +
                       "movement and blocks your way with its tail.\n");
        tell_room(ETO, QCTNAME(TO) + " stops " + QTNAME(who) +
                       " from going " + where + ".\n", who);
        return 0;
    }
    return 1;
}

/* We don't want the hydra to die until all heads have been chopped */
public void
do_die(object killer)
{
    int i;
    
    if (query_hp() > 0 || alarm_id) return;
    
    for (i=0; i<3; i++)
        if (heads[i])
            return;
        
    ETO->hydra_died(TO, killer);
    
    ::do_die(killer);
}

public int
tie_object(object ob, string what)
{
    if (chain || !ob || !id(what))
        return 0;
        
    if (query_heads())
    {
        TP->catch_msg("One of " + QTNAME(TO) + "'s heads notices " +
                      "what you are trying to do.\n");
        TP->catch_msg(QCTNAME(TO) + " lashes out its tail toward " +
                      "you and hits you head-on!\n");
        tell_room(ETO, QCTNAME(TO) + " lashes out its tail toward " +
                       QTNAME(TP) + " who is hit head-on.\n", TP);
        TP->reduce_hit_point(300 + random(300));
        if (TP->query_hp() <= 0)
            TP->do_die(TO);
        return 0;
    }
    
    if (random(TP->query_stat(SS_DEX)) <
                  45 + random(query_skill(SS_AWARENESS)))
    {
        TP->catch_msg("You were not quick enough and " + QTNAME(TO) +
                      " lashes out its tail toward " +
                      "you and hits you head-on!\n");
        tell_room(ETO, QCTNAME(TO) + " lashes out its tail toward " +
                       QTNAME(TP) + " who is hit head-on.\n", TP);
        TP->reduce_hit_point(150 + random(200));
        if (TP->query_hp() <= 0)
            TP->do_die(TO);
        return 0;
    }
    
    if (!ob->id(DQ_HYDRA_CHAIN))
    {
        TP->catch_msg("The " + ob->short() + " doesn't seem to fit.\n");
        tell_room(ETO, QCTNAME(TP) + " tries, in vain, to chain " +
                       QTNAME(TO) + ".\n", TP);
        return 0;
    }
    
    chain = ob;
    return 1;
}

public varargs int
untie_object(object ob, string what = "")
{
    object key;
    
    if (!chain || chain != ob)
        return 0;
        
    notify_fail("Unlock chain with what?\n");
    if (!strlen(what) || !(key = present(what, TP)))
        return 0;
        
    notify_fail("The " + key->short() + " does not fit the lock.\n");
    if (!key->id(DQ_CHAIN_KEY))
        return 0;
        
    chain = 0;
    return 1;
}
