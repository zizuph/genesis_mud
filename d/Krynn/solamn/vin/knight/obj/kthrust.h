/************************* kbrush ******************************/
int kbrush(string str)
{
    object *armours = TP->query_armour(-1), armour, cloak;
    int i;
    string *pre, ob;

    if (present("_knight_cloak", TP))
	cloak = present("_knight_cloak", TP);

    if (cloak && str == "cape" || str == "c")
	ob = cloak->short();
    else
	ob = "tunic";

    if (sizeof(armours))
	for (i = 0; i < sizeof(armours); i++)
	{
	    if (armours[i]->query_at() == A_HANDS ||
	      armours[i]->query_at() == A_R_HAND ||
	      armours[i]->query_at() == A_L_HAND)
		armour = armours[i];
	}

    if (armour)
	pre = ({ "Removing your "+armour->short()+" briefly, you ",
	  "Removing "+POSSESSIVE(TP)+" "+armour->short()+
	  "briefly, "+QTNAME(TP)+" " });
    else
	pre = ({ "You ", QCTNAME(TP)+" " });

    write(pre[0]+" brush the dust away that has gathered on your "+
      ob+".\n");
    say(pre[1]+" brushes away the dust that has gathered on "+
      POSSESSIVE(TP)+" "+ob+".\n");
    return 1;
}

