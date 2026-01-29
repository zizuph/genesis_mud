/* The sign language command soul. Mucalytic  2nd of February 1996.
 *
 *        Modifications/additions: <name>     <day> <date>   <year>
 */

inherit "/cmd/std/command_driver";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/composite.h"
#include "/sys/stdproperties.h"

int query_cmd_soul()
{
    return 1;
}

string get_soul_id()
{
    return "Secret signallers guild";
}

mapping query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return(["lhelp":			"language_help",
            "sign":			"gesture_message",
            "gesture":			"gesture_message"]);
}

int language_help(string str)
{
    if(!strlen(str))
    {
        cat(HELP_FILES + "lhelp");
        return 1;
    }

    if(str == "?")
    {
        cat(HELP_FILES + "language_help");
        return 1;
    }
    return 0;
}

/*
 * Function name:	gesture_message
 * Description:		Displays a message to environment of this player via
 *			sign-language.
 * Returns:		1 or 0.
 */

int gesture_message(string what)
{
    object *players;
    string *msg_arr, stmp, *str_arr;
    int chance, skill, num, itmp, i, j, *taken, *tmp_arr;

    if(what == "?")
    {
        cat(HELP_FILES + "gesture");
        return 1;
    }

    if(!strlen(what))
    {
        notify_fail(C(query_verb())+" what?\n");
        return 0;
    }

    if(!TP->query_skill(SS_LANGUAGE))
    {
        notify_fail("You do not know enough about language to "+query_verb()+
            " properly.\n");
        return 0;
    }

    TP->catch_msg("You "+query_verb()+": "+what+"\n");

    msg_arr = explode(what, " ");
    players = filter(I(E(TP)), "check_living", TO);

    for(j = 0; j < sizeof(players); j++)
    {
        skill = players[j]->query_skill(SS_LANGUAGE);

        if(!skill)
            players[j]->catch_msg(QCTNAME(TP)+" makes a strange gesture with "+
                POSSESSIVE(TP)+" hands.\n");
        else
        {
            i = 0;

            taken   = ({ });
            str_arr = ({ });
            tmp_arr = ({ });

            chance = (skill > 50 ? 100 : (skill * 2));
            num    = (chance * sizeof(msg_arr)) / 100;

            while(i < num)
            {
                itmp = random(sizeof(msg_arr));

                if(member_array(itmp, tmp_arr) == -1)
                {
                    tmp_arr += ({ itmp });
                    i++;
                }
            }

            taken = sort_array(tmp_arr, "sort_numerical");

            for(i = 0; i < sizeof(msg_arr); i++)
            {
                stmp = "";

                if(member_array(i, taken) != -1)
                    str_arr += ({ msg_arr[i] });
                else
                {
                    while(strlen(stmp) < strlen(msg_arr[i]))
                        stmp += ".";

                    str_arr += ({ stmp });
                }
            }

            players[j]->catch_msg(QCTNAME(TP)+" gestures with "+POSSESSIVE(TP)+
                " hands. You realise that "+PRONOUN(TP)+" is using sign "+
                "language.\n");
            players[j]->catch_msg(QCTNAME(TP)+" "+query_verb()+"s: "+
                implode(str_arr, " ")+"\n");
        }
    }
    return 1;
}

int sort_numerical(int a, int b)
{
    return(a > b ? 1 : -1);
}

int check_living(object ob)
{
    if(ob == TP)
        return 0;
    else
        return LIVING(ob);
}
