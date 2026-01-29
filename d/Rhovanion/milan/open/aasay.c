int
aasay(string str)
{
    int i, j, dots, lan_skill;
    object *oblist, *tmp = ({ });
    string *words, what_get;

    if (!ENV(TP))
	return 0;

    if (!strlen(str))
    {
	NF("What do you want to say in Angmar language?\n");
	return 0;
    }

    oblist = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));

    for (i = 0; i < sizeof(oblist); i++)
    {
	if (IS_MEMBER(oblist[i]) || (oblist[i]->query_wiz_level()) ||
            (oblist[i]->query_skill(SS_LANGUAGE) >= LANGUAGE_TO_UNDERSTAND))
	{
	    oblist[i]->catch_msg(QCTNAME(TP)+" says in Angmar: "+str+"\n");
            tmp += ({ oblist[i] });
	}
    }
    words = explode(str, " ");
    oblist -= tmp;
    for (i = 0; i < sizeof(oblist); i++)
    {
      dots = 0;
      what_get = "";
      lan_skill = oblist[i]->query_skill(SS_LANGUAGE);
      for (j = 0; j < sizeof(words); j++)
	if(random(lan_skill)+random(lan_skill) > (LANGUAGE_TO_UNDERSTAND / 2))
	{
	  what_get += words[j]+" ";
          dots = 0;
	}
        else if(!dots)
	{
          dots = 1;
	  what_get += "... ";
	}
      oblist[i]->catch_msg(QCTNAME(TP)+" says something like: "+what_get+"\n");
    }

    if (TP->query_get_echo())
	write("You say in Angmar: " + str + "\n");
    else
	write("Ok.\n");

    return 1;
}
