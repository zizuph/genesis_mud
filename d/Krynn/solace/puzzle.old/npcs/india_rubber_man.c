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
                      "ponder the earth, the moon, the stars and the sun",  \
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

string mname, uname;
int rep_alarm, heal_alarm, taunt_alarm;

void create_monster()
{
    set_name("dominium");
    set_gender(G_MALE);
    set_alignment(-200 + random(200));
    set_race_name("man");
    set_adj("india-rubber");
    set_title("the Master Necromancer. Wizard of the Dark Lore");
    set_long("This man looks quite normal, but for the crazed, maddened "+
        "expression on his face and the fact that his entire torso is "+
        "blanched an unnaturally white colour. He seems to be made totally "+
        "from a pliable, resistant type of india-rubber.\n");

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

int query_not_attack_me(object who, int aid)
{
    int *ids, i;
    mixed *hitloc_data;
    object weapon, cb;
    string attob, hitstr, *hitlocs = ({ });

    weapon = who->query_weapon(aid);

    if(objectp(weapon))
        if(MASTER_OB(weapon) != WEAPONS + "glass")
            return 0;

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

    if(objectp(weapon))
    {
        who->catch_msg("Your "+weapon->short()+" hits the "+hitstr+" of "+
            QCNAME(TO)+" and bounces off!\n");

        TO->catch_msg(QCTNAME(who)+" hits your "+hitstr+" with "+
            POSSESSIVE(who)+" "+weapon->short()+", but it bounces off.\n");

        tell_room(E(TO), QCTNAME(who)+" hits the "+hitstr+" of "+QTNAME(TO)+
            " with "+POSSESSIVE(who)+" "+weapon->short()+", but it bounces "+
            "off!\n", ({ who, TO }));
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
            if(sizeof(filter(I(E(TO)), "filter_players", TO)))
                if(!pointerp(get_alarm(rep_alarm)))
                    rep_alarm = set_alarm(1.0, 0.0, "reprimand_player");
    }

    ::catch_msg(str, from_player);
}

void enter_env(object dest, object old)
{
    if(sizeof(filter(I(E(TO)), "filter_players", TO)))
        if(!pointerp(get_alarm(rep_alarm)))
            rep_alarm = set_alarm(1.0, 0.0, "reprimand_player");

    if(file_name(dest) == (LOCATIONS + "eblis"))
        taunt_alarm = set_alarm(1.0, itof(random(4) + 2), "taunt_monkey");

    ::enter_env(dest, old);
}

void leave_env(object from, object to)
{
    if(pointerp(get_alarm(taunt_alarm)))
        remove_alarm(taunt_alarm);

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

            if(MASTER_OB(wep) == WEAPONS + "glass")
                ::heal_hp(hp); 
            else
                if(!sizeof(get_alarm(heal_alarm)))
                    heal_alarm = set_alarm(1.0, 0.0, "heal_me_msg");
        }
    }
}

void heal_me_msg()
{
    tell_room(E(TO), LANG_POSS(QCTNAME(TO))+" body glows with white light "+
        "and "+POSSESSIVE(TO)+" recently inflicted wound begins to heal.\n");
}
