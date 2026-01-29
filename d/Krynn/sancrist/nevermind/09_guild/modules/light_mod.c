/********************************* module: idea light *********************

 *                                   flag: 0
 **************************************************************************/

int
idea_light()
{
    NF("You forgot to attach that module.\n");;
    if (!flag(0,0))
        return 0;

    NF("You're already having a fantastic idea.\n");
    if(IDEALIGHT_ON(TP))
        return 0;
    if(!random(10))       /* Fewer break-tests */  
        if(flag(0,1) == -1)
            return 1;

    write("You switch on your idea light to indicate a fantastic idea.\n");
    all(" switches on a tiny light to indicate that "
      + PRONOUN(TP) + " has a great idea.");
    find_gizmo(TP)->add_prop(OBJ_I_LIGHT, 1);
    set_alarm(itof(4 + random(6) + TP->query_skill(SS_BUILD) / 6), -1.0,
"outout", TP);
    SET_IDEALIGHT_ON(TP,1);
    return 1;

}

void
outout(object player)
{
    player->catch_msg("The light flickers and goes out.\n");
    tell_room(E(player), QCTNAME(player) + "'s light flickers and goes "
      + "out.\n", player);
    find_gizmo(player)->add_prop(OBJ_I_LIGHT, 0);
    SET_IDEALIGHT_ON(player,0);
}



