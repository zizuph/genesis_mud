/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * This spell detects various kinds of magic in various kinds of
 * objects
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <cmdparse.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP            this_player()
#define ETP           environment(this_player())
#define PENV          (all_inventory(ETP) + all_inventory(TP))
#define TPDEATH       TP->query_skill(SS_ELEMENT_DEATH)
#define TPLIFE        TP->query_skill(SS_ELEMENT_LIFE)
#define TO            this_object()
#define CAST_LIMIT    50
#define MANA_COST     30    /* minimum cost of mana                  */
#define FOOL_MAX      25    /* Maximum fool offset (when skill=0)    */
#define FOOL_LIM      80    /* Skill at which no fool offset is made */
#define PARA_OBJ      "/std/paralyze"
#define RETFAIL(xx)   return "Sentire what in "+(xx)+"?\n"

#define MAGIC         MAGIC_AM_MAGIC
#define ID_INFO       MAGIC_AM_ID_INFO
#define MWEAPON       OBJ_I_IS_MAGIC_WEAPON
#define MARMOUR       OBJ_I_IS_MAGIC_ARMOUR
#define WHATS         ({"acid", "air", "cold", "death", "earth",\
                        "fire", "identify", "life", "light",\
                        "magic", "poison", "water"})
#define EWHATS        ({"form of acid", "element of air", "form of cold",\
                        "form of death", "element of earth", "element of fire",\
                        "form of identify", "form of life", "form of light",\
                        "form of magic", "form of poison", "element of water"})
#define MRES          ({MAGIC_I_RES_ACID,     MAGIC_I_RES_AIR,\
                        MAGIC_I_RES_COLD,     MAGIC_I_RES_DEATH,\
                        MAGIC_I_RES_EARTH,    MAGIC_I_RES_FIRE,\
                        MAGIC_I_RES_IDENTIFY, MAGIC_I_RES_LIFE,\
                        MAGIC_I_RES_LIGHT,    MAGIC_I_RES_MAGIC,\
                        MAGIC_I_RES_POISON,   MAGIC_I_RES_WATER})
#define ORES          ({OBJ_I_RES_ACID,     OBJ_I_RES_AIR,\
                        OBJ_I_RES_COLD,     OBJ_I_RES_DEATH,\
                        OBJ_I_RES_EARTH,    OBJ_I_RES_FIRE,\
                        OBJ_I_RES_IDENTIFY, OBJ_I_RES_LIFE,\
                        OBJ_I_RES_LIGHT,    OBJ_I_RES_MAGIC,\
                        OBJ_I_RES_POISON,   OBJ_I_RES_WATER})

public string query_res_info(int true_res, int iw, int skill);
public int fool_offset(int skill);
public void reveal_info(object who);

int all=0;
object ob;
string wa_str="", id_str="";
string *prop_str;

/* Function name: sentire
 * Description:   a magic identify spell
 * Arguments:     str - name of object to investigate
 * Returns:       mixed (1/0 or failure msg string)
 */
nomask mixed
sentire(string str)
{
    int i, iw, mana_limit, suc, res;
    int iw1, iw2;
    int *value;
    object para;
    string what, foo;
    mixed *info;

    if (!str)
        RETFAIL("what");

    ob = 0;
    if (sscanf(str, "%s in %s", what, foo) == 2) {
        if (foo == "me" || foo == "myself")
            ob = TP;
    }

    if (ob != TP)
        if (!parse_command(str, PENV, " %w 'in' %o ", what, ob))
            RETFAIL("what");

    if (ob != TP && !CAN_SEE(TP, ob))
        RETFAIL("what");

    if (NPMAGIC(ob))
        return "Somehow your spell fails.\n";

    mana_limit = MANA_COST + TP->query_skill(SS_SPELLCRAFT)/10;

    if (lower_case(what) == "all" || lower_case(what) == "everything") {
        iw1 = 0;
        iw2 = sizeof(WHATS);
        all = 1;
    } else {
        iw1 = member_array(lower_case(what), WHATS);
        iw2 = iw1 + 1;
        if (iw1 < 0)
            RETFAIL(ob->short());
        mana_limit /= sizeof(WHATS);
    }

    if (TP->query_mana() < mana_limit)
        return "You do not have the strength.\n";

    suc = random(TP->query_skill(SS_SPELLCRAFT));
    if (living(ob) && ob != TP)
    {
        suc += random(TPLIFE);
        suc -= random(ob->query_magic_res(MAGIC_I_RES_IDENTIFY));
    }
    else
    {
        suc += random(TPDEATH);
        value = (int *)ob->query_prop(MAGIC_I_RES_IDENTIFY);
        if (pointerp(value)) suc -= random(value[0]);
    }

    if (suc < random(CAST_LIMIT))
    {
        TP->add_mana(-mana_limit/3);
        return "Your call is not heard.\n";
    }
    TP->add_mana(-mana_limit);

    say(QCTNAME(TP) + " intones a mystic chant.\n");
    wa_str = "";
    id_str = "";
    prop_str = ({ });
    if (living(ob))
    {
        if (ob != TP)
            TP->catch_msg("You focus your mind on " + QTNAME(ob) + ".\n");
        else
            TP->catch_msg("You focus your mind on yourself.\n");
        for (iw=iw1; iw<iw2; iw++) {
            res = ob->query_magic_res(MRES[iw]);
            prop_str += ({ query_res_info(res, iw, TPLIFE) });
        }
    }
    else
    {
        TP->catch_msg("You focus your mind on the " + ob->short() + ".\n");
        if (ob->query_prop(MWEAPON) || ob->query_prop(MARMOUR) ||
            ob->query_prop(MAGIC) || ob->query_prop(ID_INFO))
            wa_str = "The "+ob->short()+" seems to be magical.\n";
        if (ob->query_prop(ID_INFO))
        {
            if (stringp(ob->query_prop(ID_INFO)))
                id_str = (string)ob->query_prop(ID_INFO);
            else if (pointerp(ob->query_prop(ID_INFO)))
            {
                info = (mixed *)ob->query_prop(ID_INFO);
                for (i=0; i<sizeof(info); i+=2)
                    if (TPDEATH >= (int)info[i+1])
                        id_str += (string)info[i];
            }
        }
        for (iw=iw1; iw<iw2; iw++) {
            value = (int *)ob->query_prop(MRES[iw]);
            res = 0;
            if (pointerp(value)) res = value[0];
            prop_str += ({ query_res_info(res, iw, TPDEATH) });
        }
    }
    seteuid(getuid());
    para = clone_object(PARA_OBJ);
    para->set_stop_verb("");                     /* No stop verb!    */
    para->set_remove_time(10+random(res/5));     /* Duration         */
    para->set_stop_fun("reveal_info");           /* Stop func called */
    para->set_stop_object(TO);                   /* in this object   */
    para->set_stop_message("You stop concentrating.\n");
    para->set_fail_message("You cannot do that while trying " +
                           "to detect magic.\n");
    para->move(TP);
    return 1;
}

public string
query_res_info(int true_res, int iw, int skill)
{
    int res;
    string str;

    if (T_WIZ(TP))
        str = "" + true_res + " % of";
    else
    {
        res = true_res + fool_offset(skill);
        switch (res)
        {
            case 95..999: str= "unbelievable"; break;
            case 80..94:  str= "outstanding"; break;
            case 66..79:  str= "extraordinary"; break;
            case 50..65:  str= "excellent"; break;
            case 40..49:  str= "very good"; break;
            case 30..39:  str= "good"; break;
            case 21..29:  str= "rather good"; break;
            case 16..20:  str= "decent"; break;
            case 11..15:  str= "some"; break;
            case  6..10:  str= "little"; break;
            case  1..5:   str= "almost no"; break;
            default:      str= "no"; break;
        }
    }
    return " "+str+" magic protection against the "+EWHATS[iw]+".\n";
}

public int
fool_offset(int skill)
{
    int tmp1, tmp2, seed;

    sscanf(OB_NUM(TP), "%d", seed);

    if (skill >= FOOL_LIM) return 0;
    if (skill <= 0) return (random(2*FOOL_MAX+1, seed) - FOOL_MAX);

    tmp1 = (FOOL_MAX*(FOOL_LIM - skill))/FOOL_LIM;
    tmp2 = (2*FOOL_MAX*(FOOL_LIM - skill))/FOOL_LIM + 1;
    return (random(tmp2, seed) - tmp1);
}

public void
reveal_info(object who)
{
    int i, first=1;

    if (!who || !ob)
        return;

    if (living(ob)) {
        for (i=0; i<sizeof(prop_str); i++) {
            if (!strlen(prop_str[i])) continue;
            if (first) {
                if (who != ob)
                    who->catch_msg(QCTNAME(ob) + " has" + prop_str[i]);
                else
                    who->catch_msg("You have" + prop_str[i]);
                first = 0;
            } else {
                if (who != ob)
                    who->catch_msg(capitalize(ob->query_pronoun()) +
                                   " has" + prop_str[i]);
                else
                    who->catch_msg("You have" + prop_str[i]);
            }
        }
    } else {
        if (wa_str)
            who->catch_msg(wa_str);
        if (id_str)
            who->catch_msg(id_str + "\n");
        for (i=0; i<sizeof(prop_str); i++) {
            if (!strlen(prop_str[i])) continue;
            if (first) {
                who->catch_msg("The " + ob->short() + " provides" +
                               prop_str[i]);
                first = 0;
            } else
                who->catch_msg("It provides" + prop_str[i]);
        }
    }
}
