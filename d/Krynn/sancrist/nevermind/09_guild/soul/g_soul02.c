        return who;
    return parse_this(str, "[at] [the] %i");
}


/* paralyzes the player for some time
 */

void
paralyze_player(object player, string fail_msg, string stop_msg, int time)
{
    object paralyze;
 [32m    setuid(); seteuid(getuid(TO)); [0m
    paralyze = clone_object("/std/paralyze");
    paralyze->set_name("_paralyzed_by_gnome_soul_");
    paralyze->set_no_show(1);
    paralyze->set_remove_time(time);
    paralyze->set_stop_message(stop_msg);
    paralyze->set_fail_message(fail_msg);
    paralyze->set_stop_verb("depart"); /* No command to stop the paralyze! */
    paralyze->set_stop_object(0);   /* Use the messages set above */
    paralyze->move(player);       /* Now DO the paralyze */
}


int
darkcheck(object player)
{
    if(!CAN_SEE_IN_ROOM(player))
    {
        player->catch_msg("It's too dark to do that.\n");
        return 0;
    }
    return 1;
}


/**************************************************************************
 * Here follow the functions. New functions should be added in alphabetic
 * order.
 **************************************************************************/

/********************* analyze ********************************************/

int
analyze(string str)
{
    mixed *info;
    int success, anzahl, i;

    float ti;
    object ob;

    ti = 42.0;
 [32m    setuid(); seteuid(getuid(TO)); [0m
    NF("You don't know how to do that.\n");
    if((TP->query_skill(SS_BUILD)) < 1)
        return 0;
    NF("Analyze what?\n");
    if(!str)
        return 0;
    if(!darkcheck(TP))
        return 1;
    NF("You do not hold a " + str + ".\n");
    ob = P(str, TP);
    if(!ob)
        return 0;
    NF("You cannot analyze " + QTNAME(ob) + ".\n");
    if(living(ob))
        return 0;
    NF("The " + ob->short() + " is too badly damaged to be analyzed.\n");
    if(ob->query_prop(OBJ_I_BROKEN))
        return 0;
    NF("You see no way of taking the " + ob->short() + " apart.\n");
    if(ob->query_prop(OBJ_M_NO_DROP))
        return 0;

    NF("You are still busy with another object.\n");
    if(ANALYZE_ALARM(TP))
        return 0;

    write("You sit down and start to take apart the " + ob->short()
      + " with your gizmo.\n");
 [33m    say(QCTNAME(TP) + " seats " + OBJECTIVE(TP) + "self on the ground " [0m
      + "and starts to take apart " + POSSESSIVE(TP) + " " + ob->short() +
".\n");

    success = (40 * ((TP->query_skill(SS_BUILD)+10) * (60+random(50))) /100) *
((TP->query_stat(3))/5+(TP->query_stat(4)*2/5)+40) /10000;
    if (ob->query_prop(OBJ_I_RES_IDENTIFY))
        success =- (ob->query_prop(OBJ_I_RES_IDENTIFY));
    info = (P(str, TP)->query_prop(MAGIC_AM_ID_INFO));

    SET_ANALYZE_ALARM(TP, set_alarm(6.0, 6.0, "analyze_msg", TP));
    set_alarm(110.0, -1.0, "emergency_remove", ob, TP, str);

    if (!info)
    {
        set_alarm(40.0, -1.0, "no_magic", TP);
        set_alarm(42.0, -1.0, "end", ob, TP, str, ti);

        return 1;
    }
    anzahl = sizeof(info) / 2;
    if(anzahl == 1)
    {
        if(success >= info[1])
 [32m            set_alarm(40.0, -1.0, "give_info", info[0], TP); [0m
        else
            set_alarm(40.0, -1.0, "fail", TP);
        set_alarm(42.0, -1.0, "end", ob, TP, str);
        return 1;
    }

    if(info[1]<info[anzahl*2-1])
    {
        for (i=0; i<anzahl; i++)
        {
            if(success>=info[2*i+1])
            {
                ti = 42.0+itof(i*3);
 [32m                set_alarm(40.0+itof(i*3), -1.0, "give_info", info[2*i], [0m
                  TP, ti);
            }
        }
    }
    else
    {
        for (i=anzahl-1; i>-1; i--)
        {
            if(success>=info[2*i+1])
            {
                ti = 42.0+itof(anzahl*3)-itof(i*3);
 [32m                set_alarm(40.0+itof(anzahl*3)-itof(i*3), -1.0, "give_info", [0m
                  info[2*i], TP, ti);
            }
        }
    }
    if (ti < 42.5)
        set_alarm(ti , -1.0, "fail", TP);
    else
        paralyze_player(TP, "You are too absorbed with taking apart "
          + "your " + ob->short() + ".\n", "", ftoi(ti));
    set_alarm(ti, -1.0, "end", ob, TP, str, ti);
    return 1;
}

void
analyze_msg(object player)
{
    int a;
    string *msg;

    msg = ({"take", " away some parts", "remove", " some bits", "look",
      " at some bits", "check", " some especially interesting parts", 
      "look", " thoughtfully", "put", " aside some parts", "rest",
      " a little bit", "turn", " around one piece", "ponder", 
      " the situation", "throw", " away a seemingly useless part",
      "break", " something in two"});
    a = random(11);
    player->catch_msg("You " + msg[a*2] + msg[a*2+1] + ".\n");
    tell_room(E(player), QCTNAME(player) + " " + msg[a*2] + "'s" 
      + msg[a*2+1] + ".\n", player);
}

void
 [32mgive_info(string str, object player, float ti) [0m
{
    if (ti < 42.5)
 [32m        player->catch_msg("You get to know the following:\n"); [0m
    remove_alarm(ANALYZE_ALARM(player));
    SET_ANALYZE_ALARM(player,0);
    player->catch_msg(str);
}

void
fail(object player)
{
    player->catch_msg("You couldn't find anything out.\nThis task seems to "
      + "be beyond your skill.\n");
    tell_room(E(player), QCTNAME(player) + " seems to be finished but looks"
      + " unhappy.\n", player);
    remove_alarm(ANALYZE_ALARM(player));
    SET_ANALYZE_ALARM(player,0);
}

void
end(object ob, object player, string str, float time)
{
    object heap;

    if(abs(time) > 42.5)
        player->catch_msg("This is all information you could find out.\n");
 [32m    setuid(); seteuid(getuid(TO)); [0m
    heap = clone_object(GOBJ + "heap");
    heap->add_prop(OBJ_I_WEIGHT, (ob->query_prop(OBJ_I_WEIGHT)));
    heap->add_prop(OBJ_I_VOLUME, (ob->query_prop(OBJ_I_VOLUME)));

    heap->move(E(player));
    tell_room(E(player), PRONOUN(player) + " drops something.\n", player);
    player->catch_msg("You drop the now useless parts of the " 
      + ob->short() + ".\n");
    ob->remove_object();
}

void
no_magic(object player)
{
    player->catch_msg("This object doesn't seem to be magical.\n");
    remove_alarm(ANALYZE_ALARM(player));
    SET_ANALYZE_ALARM(player,0);
}

void
emergency_remove(object ob, object player, string str)
{
    if(ANALYZE_ALARM(player))
    {
        fail(player);
        player->catch_msg("Something seems to be wrong with the item you "
          + "tried to analyze. Please leave a bugreport where you "
          + "found it.\n");

        end(ob, player, str, 1.0);
    }
}

