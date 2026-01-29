 [33m/******************gsay****************************************************/ [0m


int
 [33mgsay(string str) [0m
{
    string *words, sentence;
    int i;

    if(!str)
    {
 [33m        write("You didn't say much.\n"); [0m
        return 1;
    }
    words = explode(str, " ");
    for (i = 0; i<sizeof(words); i++)
        words[i]=capitalize(words[i]);
    sentence = implode(words,"");
 [33m    TP->command("$say " + sentence); [0m
    if(TP->query_wiz_level())
    {
        write("Ok.\n");
 [33m        say(QCTNAME(TP) + " says: " + sentence + "\n"); [0m
    }
    return 1;
}



/********************* gsmile ********************************************/

int
gsmile(string str)
{
 [32m    object *target; [0m

    if(!str)
    {
 [35m        write("You smile gnomishly.\n"); [0m
 [35m        allbb(" smiles gnomishly."); [0m
        return 1;
    }
    if((C(str) == TP->query_name()) || (str == "me"))
    {
        write("You gnomishly smile to yourself.\n");
 [35m        allbb(" gnomishly smiles to " + OBJECTIVE(TP) + "self."); [0m
        return 1;
    }
 [32m    target = get_target(str); [0m
    NF("Gsmile at whom?\n");
 [32m    if(!sizeof(target)) [0m
        return 0;
 [32m    if(!living(target[0])) [0m
    {
 [32m        write("You gnomishly smile at the " + target[0]->query_adj() [0m
 [32m          + " " + target[0]->query_name() + ".\n"); [0m
 [35m        tell_room(E(TP), QCTNAME(TP) + " gnomishly smiles at the " [0m
 [32m          + target[0]->query_adj() + " " [0m
 [32m          + target[0]->query_name() + ".\n", TP); [0m
        return 1;
    }
 [32m    actor("You smile at", target, ", gnomishly."); [0m
 [32m    targetbb(" smiles at you, rather gnomishly.", target); [0m
 [32m    all2actbb(" smiles at", target, ", rather gnomishly."); [0m
    return 1;
}


/********************* gthink ********************************************/

int
gthink()
{
    write("You think hard for a solution to the problem...\n");
    allbb(" screws " + POSSESSIVE(TP) + " face up and appears "
      + "to be deep in thought.");
    return 1;
}


/********************* gtinker *******************************************/

int 
gtinker(string str)
{
    object *ob;

    NF("I can't see " + str + " here.\n");
    if (!str)
    {
 [33m        write("You must say which object to tinker with.\n"); [0m
        return 1;
    }
    if(!darkcheck(TP))
        return 1;

 [32m    ob = get_target(str); [0m
    if(sizeof(ob))
    {
        if (!living(ob[0]))
        {
            write("You tinker away at the " 
              + ob[0]->short() + " with your gizmo.\n");
 [32m            SAY(" gets out a weird device and starts tinkering " [0m
              + "with the " + ob[0]->short() + ".");
            return 1;
        }
        actor("You start looking for ways to improve", ob, ".");
 [35m        all2actbb(" looks at", ob, " strangely, as if eyeing " [0m
          + OBJECTIVE(ob[0]) + " up for some devilish experiment.");
 [32m        targetbb(" looks at you strangely, " [0m
          + "as if eyeing you up for some devilish "
          + "experiment.", ob);
        return 1;
    }
    return 0;
}

/********************* help *************************************************/

int
help(string str)
{
    string subject, filename;


    if (!str)
        return 0;

    if (str == "gnomes")
    {
        write("Try 'help gnomes topics' for an overview.\n");
        return 1;
    }
    if (sscanf(str, "gnomes %s", subject) != 1)
        return 0;

    filename = HELP_DIR + subject;
    if (file_size(filename) > 0)
    {
        write("\n");
        setuid();
 [32m        seteuid(getuid()); [0m
        cat(filename);
        write("\n");
        return 1;
    }

    NF("No help on that subject I'm afraid. You might want to try:\n"

      + "help gnomes topics.\n");
    return 0;
}

