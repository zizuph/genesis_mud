/*
 * /d/Gondor/guilds/rangers/soul/diagnose.c
 *
 * Included in the soul. Diagnose ability to determine strength and type 
 * of poison in someone. 
 *
 * Originally coded by Elessar 
 * (I think, but there were no credits on original.)
 *
 * Modification log:
 * 13 April 2001 Gwyneth: General cleanup and move, no major modifications
 */
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>

/* Function name: is_poison
 * Description  : Determines if an object is a poison or not
 * Arguments    : object ob - the object to test
 * Returns      : 1 if poison, 0 if not
 */
public int
is_poison(object ob)
{
    return (function_exists("create_poison_effect", ob) != 0);
}
 
/* Function name: diagnose
 * Description  : Handles diagnosing of poisons.
 * Arguments    : string str - as entered by the ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
diagnose(string str)
{
    object *oblist, *invlist, poison_ob, patient;
    string  name, temp_txt, txt, ptype;
    int     index, size, seed, skill, tmp_skill,
            strength, dur, strongest, name_length,
            *dam;
 
    if (!strlen(str))
    {
        notify_fail("Diagnose whom?\n");
        return 0;
    }

    switch(lower_case(str))
    {
    case "me":
    case "myself":
        oblist = ({ this_player() });
        break;
    default:
        if (this_player()->query_real_name() == str)
            oblist = ({ this_player() });
        else
        {
            oblist = PARSE_THIS(str, "[the] %l");
        
            if (!oblist || !sizeof(oblist))
            {
                notify_fail("Diagnose whom?\n");
                return 0;
            }
        }
    }
 
    if (sizeof(oblist) > 1)
    {
        write("You can only diagnose one being at a time, so " +
            "you focus your attention on " + oblist[0]->query_the_name(TP) + 
            ".\n");
    }

    patient = oblist[0];
 
    invlist = all_inventory(patient);
    invlist = filter(invlist, is_poison);
 
    if (!sizeof(invlist) || (this_player()->query_stat(SS_OCCUP) <= 20))
    {
        write("You don't believe that " + 
            (this_player() == patient ? "you are" : "that person is") + 
            " poisoned.\n");
        return 1;
    }

    skill = (this_player()->query_stat(SS_OCCUP) / 2) +
        (this_player()->query_skill(SS_HERBALISM) / 2);
    skill = (skill >= 100 ? 100 : skill);
 
    for (index = 0, size = sizeof(invlist); index < size; index++)
    {
        if (invlist[index]->query_strength() > strength)
        {
            strongest = index;
            strength = invlist[index]->query_strength();
        }
    }

    poison_ob = invlist[strongest];
    log_file("diagnose", this_player()->query_name() + " skill: " +
        skill + ", diagnosing " + MASTER_OB(poison_ob) + ", str: " +
        poison_ob->query_strength() + ".\n");
 
    /* We have found the strongest of the poisons, so we
     * will diagnose it.
     * query_poison_type, query_strength, query_interval,
     * query_time, query_damage -- query_damage and query_interval
     * not used in original code so have been removed.
     */
 
    strength = poison_ob->query_strength();
    ptype = poison_ob->query_poison_type();
    dur = poison_ob->query_time_left();
    dam = poison_ob->query_damage();
 
    /* Distort values if low skill */
    tmp_skill = 1000 / (skill + 1);
    sscanf(OB_NUM(poison_ob), "%d", seed);
    tmp_skill = random(tmp_skill, seed);
    strength = this_player()->cut_sig_fig(strength +
        (tmp_skill % 2 ? -tmp_skill % 70 : tmp_skill) * strength / 100);
    dur = this_player()->cut_sig_fig(dur + 
        (tmp_skill % 2 ? -tmp_skill % 70 : tmp_skill) * dur / 100);

    txt = (patient == this_player() ? "You are " : 
        patient->query_The_name(this_player()) + " is ");

    temp_txt = "suffering from some kind of poison.\n";

    /* Test for certain poisons to give special output here */
    switch(ptype)
    {
    case "bee":
        if (skill > 20)
            temp_txt = "affected by some kind of bee sting.\n";
        break;
    case "snake":
        if (skill > 20)
            temp_txt = "suffering from the venom of a snake.\n";
        break;
    case "spider":
        if (skill > 40)
            temp_txt = "affected by the sting of some poisonous spider.\n";
        break;
    case "sumac":
        if (skill > 40)
            temp_txt = "seemingly suffering some kind of skin rash from " +
                "coming in contact with some sumac.\n";
        break;
    case "ivy":
        if (skill > 40)
            temp_txt = "seemingly suffering from some kind of rash, " +
                "probably caused by being in contact with poison ivy.\n";
        break;
    case "black_breath":
        if (skill > 60)
            temp_txt = "suffering from the feared Black Breath " +
                "from a Nazgul!\n";
        break;
    case "sickness":
        if (skill > 60 &&
          function_exists("create_poison_effect", poison_ob) == 
          "/d/Krynn/common/poisons/sick")
            temp_txt = "suffering from some kind of disease or plague.\n";
        break;
    case "black_touch":
        if (skill > 80)
            temp_txt = "suffering from the feared Black Touch from " +
                "a Nazgul!\n";
        break;
    case "standard":
        if (skill > 80 &&
          function_exists("create_poison_effect", poison_ob) == 
          "/d/Avenir/common/port/obj/uw_poison")
            temp_txt = "suffering from some kind of paralyzing poison.\n";
        else if (skill > 100 &&
          function_exists("create_poison_effect", poison_ob) == 
          "/d/Avenir/common/bazaar/Obj/misc/j_poison")
            temp_txt = "affected by some sort of vile and painful " +
                "nerve poison.\n";
        break;
    case "Morgul_Sulambar_Poison":
        if (skill > 100)
            temp_txt = "suffering from some kind of noxious Morgul gas " +
                "poisoning!\n";
        break;
    default:
        temp_txt = "suffering from some kind of poison.\n";
        break;
    }

    txt += temp_txt;

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
    default:
        txt += "a hopelessly long time";
        break;
    }

    txt +=" unless it is cleansed first, but you don't know how " +
        "much longer it will take to wear off.\n";
 
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
    /* Test damage types -- In development? */
 
    /* Hint on likelyhood of survival? -- In development? */
 
    write(txt);
    return 1;
}
