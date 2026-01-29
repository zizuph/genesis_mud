/********************* kdie****************************************/
void
reset_kdie(object who)
{
    who->remove_prop("_i_typed_kdie");
    who->remove_prop("_kdie_prop");
}

int
kdie(string str)
{
    string pos = POSSESSIVE(TP);
    if (!str)
    {
	write("With a last glance at your wounds you pull yourself together "+
	  "and prepare for Paladine's embrace in your last glorious battle!\n");
	all(" looks down at "+pos+" many wounds and grits "+pos+
	  " teeth. With a final cry to Paladine "+PRONOUN(TP)+
	  " prepares to end "+pos+" life in one last glorious battle!");
	return 1;
    }

    if (str == "fake")
    {
	return kdie_fake(str);
    }

    if (str == "true")
    {
	return kdie_true(str);
    }

    write("Kdie how? The proper syntax is either 'kdie', 'kdie fake', or 'kdie true'.\n");
    return 1;
}

int
kdie_fake(string str)
{
    string pos = POSSESSIVE(TP);

    write("Looking down at your wounds, but not yet ready to commit an "+
      "act of self-sacrifice, you cunningly bluff.\n");
    all(" looks down at "+ pos+" many wounds and grits "+pos+
      " teeth. With a final cry to Paladine "+PRONOUN(TP)+
      " prepares to end "+pos+" life in one last glorious battle!");

    return 1;
}

int
kdie_true(string str)
{
    int id;
    string pos = POSSESSIVE(TP);
    object hero;

    NF("You have already done that!\n");
    if (TP->query_prop("_knight_hero_prop"))
	return 0;

    NF("You have not the devotion to sacrifice yourself so readily, and "+
      "rationally decide against the act.\n");
    if (TP->query_knight_level() < 2 || (TP->query_knight_level() == 3 &&
	TP->query_knight_sublevel() < 9))
	return 0;

    NF("You are not in battle, you cannot use this command.\n");
    if (!TP->query_attack())
	return 0;

    NF("You are not experienced enough to use this command.\n");
    if ((TP->query_exp() / 3) > TP->query_exp_combat() && !TP->query_wiz_level()
      && !TP->query_npc())
	return 0;

    NF("You are not about to die yet, your wounds are not severe enough.\n");
    if (TP->query_hp() > (TP->query_max_hp() / 5))
	return 0;
    if (!TP->query_prop("_i_typed_kdie"))
    {
	TP->add_prop("_i_typed_kdie", 1);
	id = set_alarm(6000.0, 0.0, &reset_kdie(TP));
	TP->add_prop("_kdie_prop", id);
	write("Prepare for death?? Make SURE you know what you're doing.\n"+
	  "You have been warned, repeat command to confirm.\n");
	return 1;
    }

    remove_alarm(TP->query_prop("_kdie_prop"));
    TP->remove_prop("_kdie_prop");
    TP->remove_prop("_i_typed_kdie");
    setuid();
    seteuid(getuid());
    hero = clone_object(KOBJ+"kdie_hero_object");
    hero->move(TP);
    hero->start_poison();
    write("With a last glance at your wounds you pull yourself together " +
      "and prepare for Paladine's embrace in your last glorious battle!\n");
    all(" looks down at " + pos + " many wounds and grits " + pos +
      " teeth. With a final cry to Paladine " + PRONOUN(TP) +
      " prepares to end " + pos + " life in one last glorious battle!");

    return 1;
}

