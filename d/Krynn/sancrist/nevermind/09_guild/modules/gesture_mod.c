/********************** module: Gesturemaker ******************************
 *                        flag: 9                                         *
 **************************************************************************/

/* Various general checks specific to the GestureMatic.
 * Returns:     "Ok"     (Nothing's wrong)
 *              The fail string
 */

string
check_gest()
{
    if(!flag(9,0))
    {    
        return "What?\n";
    }
    if(!QUERY_OPERATIONAL(TP))
    {    
        return "Your GestureMatic isn't operational.\n";
    }
    if(random(5 + ((TP->query_stat(1)) / 10)) == 0) /* Check for entangling */
    {
        SET_ENTANGLED(TP);
        TP->remove_subloc(GEST_SUB);
        TP->add_subloc(GEST_SUB_ENT, TO);
        return "You have been completely tangled up in the wires and "
        + "levers of your GestureMatic. Better unentangle it and "
        + "try again...\n";
    }
    if(QUERY_ENTANGLED(TP))
    {
        return "You are still entangled in the GestureMatic.\n";
    }
    return "Ok";
}


/* Finished with pointing etc? Fold it again!
 */

int
fold(string str)
{
    if(!flag(9,0))
        return 0;
    NF("Fold what?\n");
    if(str != "gesturematic")
        return 0;
    NF("The GestureMatic is already folded.\n");
    if(!QUERY_OPERATIONAL(TP))
        return 0;
    NF("You are still entangled in the GestureMatic.\n");
    if(QUERY_ENTANGLED(TP))
        return 0;
    if(!darkcheck(TP))
        return 1;

    write("You repack the GestureMatic for convenient transport.\n");
    allbb(" pulls a lever and the giant mechanical arm folds back into "
      + POSSESSIVE(TP) + " gizmo.");
    UNSET_OPERATIONAL(TP);
    P("_g_stopper_", TP)->remove_object();
    TP->remove_subloc(GEST_SUB);
    return 1;
}

/* Unfold the GestureMatic to ready it for action
 */

int
unfold(string str)
{
    if(!flag(9,0))
        return 0;
    NF("Unfold what?\n");
    if(str != "gesturematic")
        return 0;
    if(!darkcheck(TP))
        return 1;
    NF("You are busy fighting.\n");
    if(TP->query_enemy())
        return 0;
    NF("The GestureMatic is already operational.\n");
    if(QUERY_OPERATIONAL(TP))
        return 0;


    write("You unfold the GestureMatic for use.\n");
    allbb(" does something to " + POSSESSIVE(TP)
      + " gizmo and a giant mechanical arm begins to unfold.");
    SET_OPERATIONAL(TP, 1);
    TP->add_subloc(GEST_SUB, this_object());
 [32m    setuid();seteuid(getuid()); [0m
    clone_object(GOBJ + "stopper")->move(TP);
    return 1;
}

/* Once entangled, unentangle the GestureMatic!
 */

int
unentangle(string str)
{
    int time;

    if(!(flag(9,0)))
        return 0;
    NF("Unentangle what?\n");
    if(str != "gesturematic")
        return 0;

    if(!(QUERY_OPERATIONAL(TP)))
    {     
        NF("The GestureMatic is neither operational nor entangled.\n");
    }
    else
    {     
        NF("The GestureMatic is not entangled.\n");
    }
    if(!QUERY_ENTANGLED(TP))
        return 0;
    if(!darkcheck(TP))
        return 1;

    write("You sit down and start to unentangle the crossed wires.\n");
    allbb(" sits down and starts to unentangle " 
      + POSSESSIVE(TP) + " useless mechanical arm.");
    time = 15 - (TP->query_stat(1)) / 10 + random(10);
    paralyze_player(TP, "You are entangled into the wires of your "
      + "GestureMatic.\n", "", time);
    set_alarm(itof(time), -1.0, "rem_entangle", TP);
    return 1;
}

void
rem_entangle(object player)
{
    tell_room(E(player), QCTNAME(player) + " finished unentangling "
      + POSSESSIVE(player) + " mechanical arm", player);
    if(flag(9,1) == -1)
    {     
        player->catch_msg(" You finished unentangling your mechanical arm "
          + "destroying it in the process.\n");
        tell_room(E(player), ", but somehow seems unhappy.\n"
          + PRONOUN(player) + " drops something.\n", player);
        UNSET_OPERATIONAL(player);
        P("_g_stopper_", player)->remove_object();
 [32m        setuid();seteuid(getuid()); [0m
        clone_object(GOBJ + "junk")->move(E(player));
    }
    else
    {     
        player->catch_msg("Your GestureMatic is operational again.\n");   
 [35m        tell_room(E(player), " and smiles happily.\n", player); [0m
        player->add_subloc(GEST_SUB, TO);
    }
    REMOVE_ENTANGLED(player);
    player->remove_subloc(GEST_SUB_ENT);
}


int
gpoint(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;
    }

    if(str == "west" || str == "southwest" || str == "south" || 
      str == "southeast" || str == "east" || str == "northeast" || 
      str == "north" || str == "northwest" || str == "up" ||
      str == "down")
    {
        write("You point " + str + " with your GestureMatic.\n");
        tell_room(E(TP), QCTNAME(TP) + " fiddles with " + POSSESSIVE(TP) 
          + " gizmo and suddenly the giant mechanical hand is "
          + "pointing " + str + ".\n", TP);
        return 1;

    }
 [32m    who = get_target(str);    [0m
    NF("Gpoint at whom?\n");
    if(!(sizeof(who)))
        return 0;
 [32m    targetbb(" fiddles with " + POSSESSIVE(TP) + " gizmo and suddenly " [0m
      + "the giant mechanical hand is pointing at you.", who);
    actor("You point at", who, " with your GestureMatic.");
    all2actbb(" fiddles with " + POSSESSIVE(TP) + " gizmo and suddenly "
      + "the giant mechanical hand is pointing at", who, "."); 
    return 1;
}


int
gwave(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;

    }

    if(!str)
    {
 [32m        write("You pull the GestureMatic back and forth, waving happily.\n"); [0m
        tell_room(E(TP), QCTNAME(TP) + " fiddles a bit with some levers and "
 [35m          + "the giant mechanical hand waves happily.\n", TP); [0m
        return 1;
    }

 [32m    who = get_target(str); [0m
    NF("Gwave whom?\n");
    if(!(sizeof(who)))
        return 0;
 [32m    actor("You pull the GestureMatic back and forth, waving at", who, "."); [0m
 [32m    targetbb(" fiddles a bit with some levers and the giant mechanical " [0m
 [35m      + "hand waves at you.", who); [0m
    all2actbb(" fiddles a bit with some levers and the giant mechanical "
 [35m      + " hand waves at", who, "."); [0m
    return 1;
}

int
gpoke(string str)

{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;
    }

 [32m    who = get_target(str);    [0m
    NF("Gpoke whom?\n");
    if(!(sizeof(who)))
        return 0;

    actor("You wheel your GestureMatic around and poke", who, " in the "
      + "ribs.");
 [32m    target(" wheels around abruptly and pokes you in the ribs " [0m
      + "with " + POSSESSIVE(TP) + " giant mechanical hand.", who);
 [35m    all2actbb(" suddenly pokes", who, " in the ribs with " [0m
      + POSSESSIVE(TP) + " giant mechanical hand.");
    return 1;
}

int
gslap(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;
    }

 [32m    who = get_target(str);    [0m
    NF("Gslap whom?\n");
    if(!(sizeof(who)))
        return 0;

    actor("Suddenly provoked, you yank at the control levers to make "
      + "the GestureMatic slap", who, " hard in the face, "
      + "creating some nasty welts.");
 [32m    target(" suddenly looks ticked. " + C(PRONOUN(TP)) + " fiddles with " [0m
      + POSSESSIVE(TP) + " gizmo, and the giant mechanical hand "
      + "blindsides you, slapping you in the face and stunning you "
      + "for a moment.", who);

 [32m    all2actbb(" gets an angry look and backhands", who, " with " [0m
      + POSSESSIVE(TP) + " giant mechanical hand.");
    return 1;
}


int
gfinger(string str)
{
    object *who;
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;
    }

 [32m    who = get_target(str);    [0m
    NF("Gfinger whom?\n");
    if(!(sizeof(who)))
        return 0;

 [32m    actor("You pull at the control levers closing the GestureMatic " [0m

      + "except for one finger, directing it at", who, ".");
 [32m    targetbb(" fiddles with " + POSSESSIVE(TP) + " gizmo and you find " [0m
      + "yourself face to face with a long, steel finger. Can you "
      + "guess which one?", who);
 [32m    all2actbb(" gives", who, " the finger with " + POSSESSIVE(TP) [0m
      + " giant mechanical hand.");
    return 1;
}

int
gscratch(string str)
{
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;
    }

    write("You scratch your head with your GestureMatic.\n");
    tell_room(E(TP), QCTNAME(TP) + " pulls at a lever, and " + POSSESSIVE(TP)
 [35m      + " giant mechanical hand scratches thoughtfully at " + POSSESSIVE(TP) [0m
      + " gnomish noggin.\n", TP);
    return 1;
}

int
ggesture(string str)
{
    string check;

    if((check = check_gest()) != "Ok")
    {    
        NF(check);
        return 0;
    }

    write("You try to show your point with the GestureMatic.\n");
    tell_room(E(TP), QCTNAME(TP) + " flails " + POSSESSIVE(TP)
      + " mechanical hand around emphatically, apparently trying to "
      + "tell you something.\n", TP);
    return 1;
}


