/* The india-rubber man. ~solace/puzzle/npcs/india_rubber_man */

inherit "/std/monster";

#include "../defs.h"

inherit STD + "intro";
inherit STD + "object_add";

#include "/sys/const.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/composite.h"
#include "/sys/stdproperties.h"
#include "../../../mucalytic/sys/npc_defs.h"

#define TAUNTS    ({ "cackle",                                       \
                     "emote kicks the cage repeatedly.",             \
                     "emote shakes the cage tauntingly.",            \
                     "emote taunts the monkey in the cage.",         \
                     "emote rocks the cage from side to side.",      \
                     "emote screams at the monkey in the cage.",     \
                     "say How are you my pretty? Hooharharheheh!",   \
                     "emote shouts really loudly, making you jump." })

#define TRANS_MSG ({ "[me] closes his eyes and concentrates.",            \
                     "Suddenly, there is an flash of brilliant white "+   \
                     "light so bright that you are temporarily blinded.", \
                     "[me] seems now to be different. His skin has "+     \
                     "changed hue and his eyes stare hatefully at you!",  \
                     "[me] cackles insanely.",                            \
                     "[me] rasps: You cannot hurt me, pathetic mortal. "+ \
                     "I have become INVINCIBLE!"                         })

#define MY_EMOTES  ({ "think making some lunch",                            \
                      "think making some dinner",                           \
                      "think becoming human again",                         \
                      "think making some breakfast",                        \
                      "think finding that damn cuckoo",                     \
                      "ponder life",                                        \
                      "ponder life!",                                       \
                      "ponder LIFE!",                                       \
                      "ponder LIFE!!!",                                     \
                      "ponder being an india-rubber man",                   \
                      "ponder thieves, murderers and madmen",               \
                      "ponder the death of D. Rudolph Goettel",             \
                      "emote barks like a dog.",                            \
                      "emote scratches his head.",                          \
                      "emote scratches his nose.",                          \
                      "emote stands on his head.",                          \
                      "emote jumps up in the air.",                         \
                      "emote shakes his left foot.",                        \
                      "emote mumbles incoherently.",                        \
                      "emote runs around like mad-hatter.",                 \
                      "emote slaps own his face repeatedly.",               \
                      "emote does forward-rolls around the room.",          \
                      "emote twists his head through 360 degrees.",         \
                      "emote kicks the wall but his foot bounces off.",     \
                      "emote jumps up and down like a jack-in-the-box.",    \
                      "emote contorts his limbs into unimaginable shapes." })

#define REPRIMANDS ({ "Get out of my home!!!",                        \
                      "Thief! Leave my domain at once!!",             \
                      "Go before I become REALLY angry!",             \
                      "Get out! What are you doing here?",            \
                      "Who are you? Begone from this place!",         \
                      "What do you think you're doing here??!",       \
                      "Who are you? Why are you here? Go away!!",     \
                      "Go! Go from here! Leave this place at once!",  \
                      "What do you think you're doing in my home??!" })

int tran_alarm, rep_alarm, tnt_alarm, heal_alrm, is_rubber = 0;

string set_rubber_adj()
{
    set_adj(({ "crazed", "rubber" }));
}

void create_monster()
{
    set_name("dominium");
    set_gender(G_MALE);
    set_race_name("human");
    set_alignment(-200 + random(200));
    set_adj(({ "manic", "black-robed" }));
    set_title("the Master Necromancer. Wizard of the Dark Lore");
    set_long("This man has burning, malicious eyes that glare out of "+
        "hollowed sockets sunk into his head. The yellowed skin of his "+
        "face and hands is stretched taughtly across his bones giving him "+
        "an almost cadaver-like appearance. Robes the colour of deepest "+
        "night surround his lithe body, covering his apparent frailty.\n");

    add_prop(LIVE_I_NO_CORPSE, 1);

    change_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    add_prop(CONT_I_WEIGHT, (KILOS * 65));
    add_prop(CONT_I_HEIGHT, ftoi((6.0 * FEET) + (2.0 * INCHES)));

    set_stats(({ (25 + random(10)),	/* str */
                 (45 + random(15)),	/* dex */
                 (25 + random(15)),	/* con */
                 (20 + random(30)),	/* int */
                 (20 + random(30)),	/* wis */
                 (30 + random(20)) }));	/* dis */

    set_hp(10000); // Heal to max hp.

    set_skill(SS_DEFENCE,	15 + random(25)); 
    set_skill(SS_UNARM_COMBAT,	35 + random(20));
    set_skill(SS_BLIND_COMBAT,	10 + random(10));

    set_act_time(1 + random(3));
    add_act("@@my_emote_acts@@");
    add_act("@@std_emote_acts@@");

    set_random_move(1);
}

string my_emote_acts()
{
    return MY_EMOTES[random(sizeof(MY_EMOTES))];
}

string std_emote_acts()
{
    return EMOTES[random(sizeof(EMOTES))];
}

string set_long_desc()
{
    set_long("This man looks quite normal, but for the crazed, maddened "+
            "expression on his face and the fact that his entire torso is "+
            "blanched an unnaturally white colour. He seems to be made "+
            "totally from a pliable, resistant type of rubber.\n");
}

int query_not_attack_me(object who, int aid)
{
    mixed *hitloc_data;
    int *ids, wep_aid, i;
    string attob, hitstr, *hitlocs = ({ });
    object *wep_arr, weapon, att_weapon, cb;

    wep_arr = who->query_weapon(-1);

    if(sizeof(wep_arr))
    {
        for(i = 0; i < sizeof(wep_arr); i++)
        {
            weapon  = wep_arr[i];
            wep_aid = weapon->query_attack_id();

            if(wep_aid == aid)
                att_weapon = weapon;
        }

        if(objectp(att_weapon))
        {
            if(MASTER_OB(att_weapon) == (WEAPONS + "glass"))
                return 0;
        }
    }

    cb = query_combat_object();

    if(!objectp(cb))
        return 0;

    ids = cb->query_hitloc_id();

    if(sizeof(ids))
    {
        for(i = 0; i < sizeof(ids); i++)
        {
            hitloc_data = cb->query_hitloc(ids[i]);
            hitlocs    += ({ hitloc_data[2] });
        }
    }

    hitstr = hitlocs[random(sizeof(hitlocs))];

    if(objectp(att_weapon))
    {
        who->catch_msg("Your "+att_weapon->short()+" hits the "+hitstr+" of "+
            QTNAME(TO)+" and bounces off!\n");

        TO->catch_msg(QCTNAME(who)+" hits your "+hitstr+" with "+
            POSSESSIVE(who)+" "+att_weapon->short()+", but it bounces off.\n");

        tell_room(E(TO), QCTNAME(who)+" hits the "+hitstr+" of "+QTNAME(TO)+
            " with "+POSSESSIVE(who)+" "+att_weapon->short()+", but it "+
            "bounces off!\n", ({ who, TO }));
    }
    else
    {
        attob = cb->cb_attack_desc(aid);

        who->catch_msg("You hit the "+hitstr+" of "+QTNAME(TO)+" with "+
            "your "+attob+", but it bounces off!\n");

        TO->catch_msg(QCTNAME(who)+" hits your "+hitstr+" with "+
            POSSESSIVE(who)+" "+attob+", but it bounces off.\n");

        tell_room(E(TO), QCTNAME(who)+" hits the "+hitstr+" of "+
            QTNAME(TO)+" with "+POSSESSIVE(who)+" "+attob+", but it "+
            "bounces off!\n", ({ who, TO }));
    }

    return 1;
}

string query_presentation()
{
    return query_name()+" "+query_title()+", "+query_gender_string()+
        " human ("+query_align_text()+")";
}

set_ghost(int flag)
{
    seteuid(getuid(TO));
    clone_object(OBJECTS + "rubber_pile")->move(E(TO));

    tell_room(E(TO), "As "+QTNAME(TO)+" ends his death-throes, he "+
        "glows with an intense white light and before you know what has "+
        "happened, nothing remains but a heap of singed rubber on the "+
        "floor.\n", TO);

    ::set_ghost(flag);
}

int filter_players(object obj)
{
    return LIVING(obj);
}

void catch_msg(mixed str, object from_player)
{
    string msg, who;

    if(pointerp(str))
        msg = str[0];
    else
        msg = str;

    if(strlen(msg))
    {
        if(sscanf(msg, "%s arrives.", who))
        {
            if(sizeof(filter(I(E(TO)), "filter_players", TO)))
            {
                if(!is_rubber)
                {
                    is_rubber = 1;
                    tran_alarm = set_alarm(2.0, 0.0, "transform", 0); 
                }
                else
                {
                    if(!pointerp(get_alarm(tran_alarm)))
                        if(!pointerp(get_alarm(rep_alarm)))
                            rep_alarm = set_alarm(1.0, 0.0, "reprimand_player");
                }
            }
        }
    }

    ::catch_msg(str, from_player);
}

void enter_env(object dest, object old)
{
    if(sizeof(filter(I(E(TO)), "filter_players", TO)))
    {
        if(!is_rubber)
        {
            is_rubber = 1;
            tran_alarm = set_alarm(2.0, 0.0, "transform", 0); 
        }
        else
        {
            if(!pointerp(get_alarm(tran_alarm)))
                if(!pointerp(get_alarm(rep_alarm)))
                    rep_alarm = set_alarm(1.0, 0.0, "reprimand_player");
        }
    }

    if(file_name(dest) == (LOCATIONS + "nuitari"))
        tnt_alarm = set_alarm(1.0, itof(random(4) + 2), "taunt_monkey"); 

    ::enter_env(dest, old);
}

void leave_env(object from, object to)
{
    if(pointerp(get_alarm(tnt_alarm)))
        remove_alarm(tnt_alarm);

    ::leave_env(from, to);
}

void taunt_monkey()
{
    object cage = present("cage", E(TO));

    if(objectp(cage))
        if(!cage->query_monkey_released())
            command(TAUNTS[random(sizeof(TAUNTS))]);
}

void reprimand_player()
{
    command("say "+REPRIMANDS[random(sizeof(REPRIMANDS))]);
}

void heal_hp(int hp)
{
    int i;
    object wep, *weps, att = query_attack();

    weps = att->query_weapon(-1);

    if(sizeof(weps))
    {
        for(i = 0; i < sizeof(weps); i++)
        {
            wep = weps[i];

            if(MASTER_OB(wep) == (WEAPONS + "glass"))
                ::heal_hp(hp); 
            else
            {
                if(!pointerp(get_alarm(heal_alrm)))
                    heal_alrm = set_alarm(itof(random(9) + 3), 0.0, "heal_msg");

                break;
            }
        }
    }
}

void heal_msg()
{
    tell_room(E(TO), LANG_POSS(QCTNAME(TO))+" body glows with white light "+
        "and "+POSSESSIVE(TO)+" recently inflicted wound begins to heal.\n");
}

void transform(int index)
{
    if(index <= sizeof(TRANS_MSG))
    {
        if(extract(TRANS_MSG[index], 0, 3) != "[me]")
            tell_room(E(TO), TRANS_MSG[index] + "\n", TO);
        else
            tell_room(E(TO), QCTNAME(TO) + extract(TRANS_MSG[index], 4,
                strlen(TRANS_MSG[index])) + "\n", TO);

        if(index == 2)
        {
            set_long_desc();
            set_rubber_adj();
        }

        index++;

        tran_alarm = set_alarm(1.0, 0.0, "transform", index);
    }
}
