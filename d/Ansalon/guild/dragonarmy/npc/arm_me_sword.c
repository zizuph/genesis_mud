void
arm_me_sword()
{
    string *swords;
    int s;

    switch(query_stat(SS_OCCUP))
    {
    case 0..50:
	swords = ({
		"da_shortsword",	/*19,15*/
		"sabre",		/*20,15*/
		"da_rapier",		/*31,18*/
		"shortsword2",		/*23,20*/
		"shortsword",		/*26,20*/
		"scimitar",		/*30,21*/
		"cutlass2",		/*29,22*/
		"da_sabre",		/*26,23*/
		"longsword3",		/*25,25*/
		"da_scimitar",		/*25,25*/
		"longsword2",		/*28,26*/
		"longsword",		/*26,26*/
		"cutlass1",		/*20,27*/
	});
	break;
    case 51..100:
	swords = ({
		"longsword3",		/*25,25*/
		"da_scimitar",		/*25,25*/
		"longsword2",		/*28,26*/
		"longsword",		/*26,26*/
		"da_sword",		/*27,27*/
		"broadsword",		/*30,27*/
		"sword3",		/*35,28*/
		"scimitar2",		/*35,30*/
		"sword",		/*30,32*/
	});
	break;
    case 101..130:
	swords = ({
		"da_sword",		/*27,27*/
		"broadsword",		/*30,27*/
		"sword3",		/*35,28*/
		"scimitar2",		/*35,30*/
		"sword",		/*30,32*/
		"claymore",		/*39,33*/
		"2hsword",		/*35,40*/
	});
	break;
    default:
	swords = ({
		"claymore",		/*39,33*/
		"2hsword",		/*35,40*/
		"da_claymore",		/*49,40*/
	});
    }
    s = random(sizeof(swords));
    clone_object(WEP_DIR+"sword/"+swords[s])->move(TO,1);
}
