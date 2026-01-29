/*
 */
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

int
query_cmd_soul()
{
    return 1;
}

string
get_soul_id()
{
    return "Templar npc soul";
}

int
can_attack(object whom)
{
    if (environment(this_player()) != environment(whom))
        return 0;
    
    if  (whom->query_prop(OBJ_M_NO_ATTACK))
        return 0;
    
    if (environment()->query_prop(ROOM_M_NO_ATTACK))
        return 0;
    
    if (this_player()->query_prop(LIVE_I_STUNNED))
        return 0;
    
#ifdef 0
    if (!CAN_SEE_IN_ROOM(this_player()) && !CAN_SEE(this_player(), whom))
        return 0;
#endif

    return 1;
}

mapping
query_cmdlist()
{
    return ([
        "rescue"    : "do_speccommand",
        "hit"       : "do_speccommand",
        ]);
}

void
do_hit(object who)
{
    object *wep;
    mixed *hitres;
    int where = (random(3) ? A_BODY : A_HEAD);
    string *msg;
    
    wep = this_player()->query_weapon(-1);
    if (sizeof(wep) == 2)
    {
        if ((wep[0]->query_hit() + wep[0]->query_pen()) <
            (wep[1]->query_hit() + wep[1]->query_pen()))
            wep[0] = wep[1];
    }

    hitres = who->hit_me(F_PENMOD((wep[0]->query_hit() + wep[0]->query_pen()) * 2, this_player()->query_skill(SS_WEP_FIRST + wep[0]->query_wt())), wep[0]->query_dt(), this_player(), -1, where);

    write("You take a swing with your " + wep[0]->short() + " against " +
        QTNAME(who) + "'s " + (where == A_BODY ? "torso" : "head") + ".\n");
    who->catch_msg(QCTNAME(this_player()) + " takes a swing with " +
        HIS(this_player()) + " " + wep[0]->short() + " against your " +
        (where == A_BODY ? "torso" : "head") + ".\n");
    this_player()->tell_watcher(QCTNAME(this_player()) + " takes a swing " +
        "with " + HIS(this_player()) + " " + wep[0]->short() + " against " +
        QTNAME(who) + "'s " + (where == A_BODY ? "torso" : "head") + ".\n",
        who, this_player());

    switch (hitres[0])
    {
        case 0:
            msg = ({ "just barely miss", "just barely misses" });
            break;
        case 1..10:
            if (wep[0]->query_dt() == W_BLUDGEON)
                msg = ({ "just scrapes", "just scrapes" });
            else
                msg = ({ "just grazes", "just grazes" });
            break;
        case 11..20:
            if (wep[0]->query_dt() == W_BLUDGEON)
                msg = ({ "bumps into", "bumps into" });
            else
                msg = ({ "slashes into", "slashes into" });
            break;
        case 21..30:
            if (wep[0]->query_dt() == W_BLUDGEON)
                msg = ({ "bashes into", "bashes into" });
            else
                msg = ({ "bites into", "bites into" });
            break;
        case 31..40:
            if (wep[0]->query_dt() == W_BLUDGEON)
                msg = ({ "cracks some bones as it hit into",
                    "cracks some bones as it hits into" });
            else
                msg = ({ "bites deeply into", "bites deeply into" });
            break;
        default:
            if (wep[0]->query_dt() == W_BLUDGEON)
                msg = ({ "makes a sickening sound of bones breaking " +
                    "as it hits into", "makes a sickening sound of " +
                    "bones breaking as it hits into" });
            else
                msg = ({ "makes sinews visible as it slashes into",
                    "makes sinews visible as it slashes into" });
            break;
    }

    write("Your " + wep[0]->short() + " " + msg[0] + " " + HIS(who) + " " +
        (where == A_BODY ? "torso" : "head") + ".\n");
    who->catch_msg(QCTNAME(this_player()) + "'s " + wep[0]->short() +
        " " + msg[1] + " your " +
        (where == A_BODY ? "torso" : "head") + ".\n");
    this_player()->tell_watcher(QCTNAME(this_player()) + "'s " +
        wep[0]->short() + " " + msg[1] + " " + QTNAME(who) + "'s " +
        (where == A_BODY ? "torso" : "head") + ".\n", who, this_player());
}

void
do_rescue(object who)
{
    write("You step infront of " + QTNAME(who->query_attack()) + ", " +
        "facing " + HIM(who->query_attack()) + " with little choice " +
        "but to fight you.\n");
    (who->query_attack())->catch_msg(QCTNAME(this_player()) + " steps " +
        "infront of you, facing you with little choice but to fight " +
        HIM(this_player()) + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) +
        " steps infront of " +  QTNAME(who->query_attack()) + ", facing " +
        HIM(who->query_attack()) + " with little choice but to fight " +
        HIM(this_player()) + ".\n", ({ this_player(), who->query_attack() }));

    find_player("stralle")->catch_tell("[rescue] new target: " +
        file_name(who->query_attack()));
    (who->query_attack())->attack_object(this_player());
    this_player()->attack_object(who->query_attack());
}

int
do_speccommand(string arg)
{
    object *oblist = ({ });
    
    if (!arg)
    {
        if (query_verb() == "rescue")
            oblist += ({ this_player()->query_team_others()
                [random(sizeof(this_player()->query_team_others()))] });
        else
            oblist += ({ this_player()->query_attack() });
    }
    else
        oblist = parse_this(arg, "[the] %l");

    if (!sizeof(oblist) || !objectp(oblist[0]))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    if (query_verb() == "rescue" && !oblist[0]->query_attack())
    {
        notify_fail(QCTNAME(oblist[0]) + " isn't fighting anyone.\n");
        return 0;
    }

    if (query_verb() == "hit" && !sizeof(this_player()->query_weapon(-1)))
    {
        notify_fail("You need a weapon wielded.\n");
        command("$wield all");
        return 0;
    }

    if (!can_attack(oblist[0]))
        return 0;
    
    call_other(this_object(), "do_" + query_verb(), oblist[0]);
    return 1;
}
