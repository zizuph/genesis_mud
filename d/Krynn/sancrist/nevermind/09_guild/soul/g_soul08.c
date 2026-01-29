/********************* glint *********************************************/

int
glint(string str)
{
 [32m    object *target; [0m

    if(!str)
    {
        write("A nasty gleam appears in your eyes.\n");
        tell_room(E(TP), "A nasty gleam appears in " + QTNAME(TP)
 [33m          + "'s eyes and you wonder what " + PRONOUN(TP) + " might " [0m
          + "be thinking.\n", TP);
        return 1;

    }
    NF("You try to glint at yourself but fail.\n");
    if(C(str) == TP->query_name() || str == "me")
        return 0;
    NF("You don't see " + str + " here.\n");
 [32m    if(!(sizeof(target = get_target(str)))) [0m
        return 0;
 [32m    if(living(target[0])) [0m
    {
 [32m        actor("You look at", target, " with a nasty gleam " [0m
          + "in your eyes.");
 [32m        targetbb(" looks at you with a nasty " [0m
 [32m          + "gleam in " + POSSESSIVE(TP) + " eyes.", target); [0m
 [32m        all2actbb(" looks at", target, " with a nasty gleam in " [0m
          + POSSESSIVE(TP) + " eyes.");
        return 1;
    }
 [32m    write("You look at the " + target[0]->query_adj() + " " [0m
 [32m      + target[0]->query_name() + " with a nasty gleam " [0m
      + "in your eyes.\n");
 [32m    tell_room(E(TP), QCTNAME(TP) + " looks at the " + target[0]->query_adj() [0m
 [32m      + " " + target[0]->query_name() + " with a nasty gleam " [0m
      + "in " + POSSESSIVE(TP) + " eyes.\n");
    return 1;
}

/********************* gmarvel *******************************************/

int
gmarvel(string str)
{

    NF("Which race?\n");
    if (!str)
    {
 [33m        write("You marvel at the wonder of it all!\n"); [0m
 [33m        SAY(" is in awe of such a marvellous idea!"); [0m
        return 1;
    }
    if (str == "gnome" || str == "gnomes")
    {
        write("You marvel at the intelligence of your fellow "
          + "gnomes.\n");
 [33m        SAY(" marvels at the amazing intelligence of "  [0m
          + POSSESSIVE(TP) + " fellow gnomes.");
        return 1;
    }
    if (str == "dwarf" || str == "dwarves")

    {
        write("You can't help but laugh at the stupidity of these "
          + "dwarves.\n");
 [33m        SAY(" shakes " + POSSESSIVE(TP) + " head in disbelief at the stupidity [0m
"
          + "of dwarves.");
        return 1;
    }
    if (str == "elf" || str == "elves")
    {
        write("Ha! Sometimes elves can be soooo stupid!\n");
 [33m        SAY(" can't believe elves could be soooo stupid!"); [0m
        return 1;
    }
    if (str == "goblin" || str == "goblins")
    {
        write("Well noone said goblins were gifted with intelligence.\n");
 [33m        SAY(" smiles sympathetically at the stupidity of some " [0m
          + "goblins.");
        return 1;
    }
    if (str == "human" || str == "humans")
    {
        write("I guess bigger doesn't mean brainier in this case "
          + "anyway.\n");

 [33m        SAY(" wonders if the size of some humans is proportionate " [0m
          + "to their stupidity!");
        return 1;
    }
    if (str == "hobbit" || str == "hobbits")
    {
        write("Ye gods! are these hobbits really as stupid as they "
          + "look!\n");
 [33m        SAY(" sighs in exasperation at the lack of intelligence to " [0m
          + "be found in the average hobbit.");
        return 1;
    }
    return 0;
}

/********************* gnlist ********************************************/

int
gnlist(string str)
{       
    object *players;
    int i;

    players = users();
    write("The following Inventors are currently logged on:\n");
    for (i = 0; i < sizeof(players); i++)
    {
        if (players[i]->query_guild_name_race() == GNOME_NAME && 
          players[i]->query_invis() == 0 &&
          extract(players[i]->query_name(), -2) != "jr")
            write(": " + players[i]->query_name() + " the " +
              players[i]->query_guild_title_race() + "\n");
    }
    return 1;
}

