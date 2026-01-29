/*
 * Merc NPC Memberlist
 *
 * This is the memberlist for the NPC's of the Merc guild.
 * This will make the npcs answer "mercenaries", "mercs" with
 * whom is online/awake in the guild.
 *
 * Created by Lunatari 2006
 */

int
query_wizard(object ob)
{

    if(ob->query_wiz_level()) return 1;

    return 0;
}

int 
query_member(object ob)
{
    if(MJOIN->query_member(ob->query_real_name())) return 1;

    return 0;
}

int
query_inside_camp(object ob)
{
    if(ob->query_prop(MERC_CAMP_ENTRY) == 1) return 1;

    return 0;
}

int
query_outside_camp(object ob)
{
    if(ob->query_prop(MERC_CAMP_ENTRY) == 2) return 1;

    return 0;
}

int
query_myself(object ob)
{
    if(ob->query_real_name() == TP->query_real_name()) return 1;
}

string
query_member_list()
{
    object *wizards, *members, *icamp, *ocamp;
    string title, list_r, list_i, list_o, res, aft;
    int    i, k;

    if(TP->query_wiz_level())
	write("You are called "+capitalize(TP->query_real_name())+"\n");


    if(!query_member(TP)) 
	return "say What is in it for me? Why should I tell you anything";

    wizards = filter(users(), query_wizard);
    members = filter(users(), query_member);
    
    members -= wizards;
    members -= filter(users(), query_myself);

    i = -1;
    k = sizeof(members);

    if (!k) 
    {
	TO->command("say There are no other Mercenaries awake in the realm");
	return "sigh"; 
    }

    icamp   = filter(members, query_inside_camp);
    members -= icamp;

    ocamp   = filter(members, query_outside_camp);
    members -= ocamp;

    i = -1;
    k = sizeof(icamp);

    if (!k) list_i = "";

    else
    {
	list_i = "I have seen ";

	while (++i < k)
	{
	    if(i == (k-2))
		aft = " and ";
	    else if (i <= (k-2))
		aft = ", ";
	    else
		aft = " returning to the camp.";
	    
	    list_i += capitalize(icamp[i]->query_real_name())+aft;
	}

        TO->command("say "+list_i);
    }

    i = -1;
    k = sizeof(ocamp);

    if (!k) list_o = "";

    else
    {
	list_o = "I have notes of ";

	while (++i < k)
	{
	    if(i == (k-2))
		aft = " and ";
	    else if (i <= (k-2))
		aft = ", ";
	    else
		aft = " leaving the camp today.";
	    
	    list_o += capitalize(ocamp[i]->query_real_name())+aft;
	}

        TO->command("say "+list_o);
    }

    i = -1;
    k = sizeof(members);

    if (!k) list_r = "";

    else
    {
        list_r = "I have heard rumours that ";

        while (++i < k)
        {
            if(i == (k-2))
                aft = " and ";
            else if (i <= (k-2))
                aft = ", ";
            else
                aft = " should be awake.";

            list_r += capitalize(members[i]->query_real_name())+aft;
        }

	TO->command("say "+list_r);
    }

    return "mumble";
}
