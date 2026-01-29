#include <poison_types.h>
#include <macros.h>

public int
is_poison(object ob)
{
    return (function_exists("create_poison_effect", ob) != 0);
}

public int
diagnose(string str)
{
    object *oblist,
           *invlist,
            ob,
            pl;
    string  txt,
            type;
    int     i, n,
            seed,
            skill,
            tmp_skill,
            strength,
            dur,
            interv,
            strongest;
    mixed  *fx;

    if (!strlen(str))
    {
        NFN("Diagnose whom?");
        return 0;
    }
    if (str == "me" || str == "myself" || str == TP->query_real_name())
    {
        oblist = ({ TP });
    }
    else
    {
        oblist = parse_this(str, "[the] %l");
        NFN("Diagnose whom?");
        if (!oblist || !sizeof(oblist))
            return 0;
    }

    NF("You can only diagnose one being at a time!\n");
    if (sizeof(oblist) > 1)
        return 0;
    pl = oblist[0];

    invlist = all_inventory(pl);
    find_living("elessar")->catch_msg(TP->query_name() + " diagnoses "
      + pl->query_name() + " for poisoning.\n");
    invlist = filter(invlist, is_poison);

    skill = (TP->query_stat(SS_OCCUP)/2) 
          + (TP->query_skill(SS_HERBALISM)/2);
    if (skill >= 100)
        skill = 100;

    if (!sizeof(invlist) || (TP->query_stat(SS_OCCUP) <= 20))
    {
        write("You don't believe that " + (TP == pl ? "you are" :
          "that person is") + " poisoned.\n");
        return 1;
    }

    while (i < sizeof(invlist))
    {
        if (invlist[i]->query_strength() > n)
        {
            strongest = i;
            n = invlist[i]->query_strength();
        }
        i++;
    }
    ob = invlist[strongest];
    log_file("diagnose", this_player()->query_name() + " skill: " 
      + skill + ", diagnosing " + MASTER_OB(ob) + ", str: "
      + ob->query_strength() + ".\n");

    /* We have found the strongest of the poisons, so we
     * will diagnose it.
     * query_poison_type, query_strength, query_interval,
     * query_time, query_damage
     */

    fx = ob->query_damage();
    strength = ob->query_strength();
    type = ob->query_poison_type();
    interv = ob->query_interval();
    dur = ob->query_time();
    find_living("elessar")->catch_msg("Type: " + type + ", Str: "
      + strength + ", Time: " + dur + ", Int: " + interv + ".\n");

    /* Distort values if low skill */
    tmp_skill = 1000 / (skill + 1);
    sscanf(OB_NUM(ob), "%d", seed);
    tmp_skill = random(tmp_skill, seed);
    strength = TP->cut_sig_fig(strength 
      + (tmp_skill % 2 ? -tmp_skill % 70 : tmp_skill) * strength/100);
    dur = TP->cut_sig_fig(dur 
      + (tmp_skill % 2 ? -tmp_skill % 70 : tmp_skill) * dur / 100);
    find_living("elessar")->catch_msg("Distorted to Str: "
      + strength + " and Dur: " + dur + " because of skill: "
      + skill + ".\n");
    if (pl == TP)
        txt = "You are ";
    else
        txt = QCTNAME(pl) + " is ";
/* Test for certain poisons to give special output here */
    if (skill <= 20)
    {
        txt += "suffering from some kind of poison.\n";
    }
    if (skill > 20)
    {
        if (type == "bee")
            txt += "affected by some kind of bee sting.\n";
        else if (type == "snake")
            txt += "suffering from the venom of a snake.\n";
    }
    if (skill > 40)
    {
        if (type == "spider")
            txt += "affected by the sting of some poisonous spider.\n";
        else if (type == "sumac")
            txt += "seemingly suffering some kind of skin rash from "
              + "coming in contact with some sumac.\n";
        else if (type == "ivy")
            txt += "seemingly suffering from some kind of rash, "
              + "probably caused by being in contact with poison ivy.\n";
    }
    if (skill > 60)
    {
        if (type == "black_breath")
            txt += "suffering from the feared Black Breath from a "
              + "Nazgul!\n";
        else if (type == "sickness" &&
             function_exists("create_poison_effect", ob)
               == "/d/Krynn/common/poisons/sick")
        txt += "suffering from some kind of disease or plague.\n";
    }
    if (skill > 80)
    {
        if (type == "black_touch")
            txt += "suffering from the feared Black Touch from a "
              + "Nazgul!\n";
        else if (type == "standard" && 
               function_exists("create_poison_effect", ob) 
               == "/d/Avenir/common/port/obj/uw_poison")
            txt += "suffering from some kind of paralyzing poison.\n";
        else if (type == "Morgul_Sulambar_Poison")
            txt += "suffering from some kind of noxious Morgul "
              +"gas poisoning!\n";
    }
    if (skill > 100)
    {
        if (type == "standard" &&
              function_exists("create_poison_effect", ob)
              == "/d/Avenir/common/bazaar/Obj/misc/j_poison")
            txt += "affected by some sort of vile and painful nerve "
              + "poison.\n";
    }
    txt += "affected by " + LANG_ADDART(type)
      + " poison.\n";
/* Use a switch statement to give a rough estimate of duration */
    txt += "You suspect such poisons last ";
    switch (dur / 60)
    {
        case 0:
            txt += "only very briefly";
            break;
        case 1..5:
            txt += "just a few minutes";
            break;
        case 6..10:
            txt += "just a short while";
            break;
        case 11..20:
            txt += "a little while";
            break;
        case 21..40:
            txt += "for some time";
            break;
        case 41..90:
            txt += "for quite a while";
            break;
        case 91..180:
            txt += "for a long time";
            break;
        case 181..100000:
            txt += "a hopelessly long time";
            break;
    }
    txt +=" unless it is cleansed first, but you don't know how "
      + "much longer it will take to wear off.\n";

/* Use a switch statement to estimate strength */
    txt += "You believe this is a ";
    switch (strength)
    {
        case -100..10:
            txt += "really weak";
            break;
        case 11..20:
            txt += "quite weak";
            break;
        case 21..30:
            txt += "weak";
            break;
        case 31..40:
            txt += "rather mild";
            break;
        case 41..50:
            txt += "mild";
            break;
        case 51..60:
            txt += "pretty modest";
            break;
        case 61..70:
            txt += "modest";
            break;
        case 71..80:
            txt += "not very strong";
            break;
        case 81..90:
            txt += "moderately strong";
            break;
        case 91..100:
            txt += "somewhat strong";
            break;
        case 101..110:
            txt += "rather strong";
            break;
        case 111..120:
            txt += "quite strong";
            break;
        case 121..130:
            txt += "very strong";
            break;
        case 131..140:
            txt += "dangerously strong";
            break;
        case 141..150:
            txt += "quite dangerous";
            break;
        case 151..160:
            txt += "very dangerous";
            break;
        case 161..180:
            txt += "very dangerous, possibly lethal";
            break;
        case 181..250:
            txt += "quite lethal";
            break;
        default:
            txt += "simply deadly";
            break;
    }
    txt += " dose.\n";
/* Test damage types */
    
/* Hint on likelyhood of survival? */

    TP->catch_msg(txt);
    return 1;
}
