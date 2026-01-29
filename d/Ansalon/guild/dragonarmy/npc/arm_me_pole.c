void
arm_me_pole()
{
    string *poles;
    int s;

    switch(query_stat(SS_OCCUP))
    {
    case 0..50:
	poles = ({
		"bflance",		/*13,13*/
		"dr_spear",		/*16,15*/
		"spear",		/*24,18*/
		"spear2",		/*28,20*/
		"lance",		/*32,26*/
	});
	break;
    case 51..100:
	poles = ({
		"spear2",		/*28,20*/
		"lance",		/*32,26*/
		"gen_pike",		/*28,30*/
		"gen_halberd",		/*28,34*/
	});
	break;
    case 101..130:
	poles = ({
		"gen_pike",		/*28,30*/
		"gen_halberd",		/*28,34*/
		"halberd",		/*22,38*/
		"skelhalb",		/*35,35*/
	});
	break;
    default:
	poles = ({
		"gen_halberd",		/*28,34*/
		"halberd",		/*22,38*/
		"skelhalb",		/*35,35*/
		"pike",			/*27/37,35/40*/
	});
    }
    s = random(sizeof(poles));
    clone_object(WEP_DIR+"pole/"+poles[s])->move(TO,1);
}
