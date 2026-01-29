public int
wfury (string str)
{
    object *oblist;
    int size;
    oblist = parse_this(str, "%l");
    if(!(size = sizeof(oblist)))
    return NF("Wfury who?\n");
    actor("You raise your head and your eyes, aglow with magical, demonic fire, " +
        "meet ", oblist, "'s gaze. Startled ", oblist, " back away from you. \n");
    target(" raises " + POSSESSIVE(TP) + " head and " + POSSESSIVE(TP) + " eyes, " +
        "aglow with magical, demonic fire, meet your gaze. Startled you back " +
        "away from the mage. \n");
    all2act("  raises " + POSSESSIVE(TP) + " head and " + POSSESSIVE(TP) + " eyes, " +
        "aglow with magical, demonic fire, meet ", oblist, "'s gaze. " +
        "Startled ", oblist, " back away from the mage. \n");
    return1;
}
  
