void
arm_me_armour()
{
    string *head = ({});
    string *body = ({});
    string *torso = ({});
    string *legs = ({});
    string *feet = ({});
    string *arms = ({});
    string *shield = ({});
    int s;

    switch(query_stat(SS_OCCUP))
    {
    case 0..50:
	feet = ({ "boots3" });
	body = ({ "shirt2", "cuir-boili12" });
	torso = ({ "stud_leather14" });
	if(!random(3))
	    head = ({ "helm18","helmet15","sk_helmet9" });
	if(!random(5))
	legs = ({ "breeches3" });
	break;
    case 51..100:
	feet = ({ "bboots10", "boots8" });
	body = ({ "chainmail33","scale_mail19","splint_mail21" });
	torso = ({ "black_chain_shirt31","dwarf_lplate26","breastplate20",
	    "rust_chain29","mailshirt33" });
	if(!random(3))
	    arms = ({ "gauntlets10" });
	if(random(10))
	    head = ({ "helm18","helm20","helm25", });
	if(random(7))
	    legs = ({ "bezainted_greaves17","chaingreaves18" });
	break;
    case 101..130:
	feet = ({ "bboots10", "boots8", "bheavyboots20" });
	body = ({ "bplatemail39","chainmail33" });
	torso = ({ "da_oplate40","da_omail34","mailshirt33" });
	if(random(4))
	    arms = ({ "gauntlets20" });
	head = ({ "helm25","steel_helm26","bdragonhelm31" });
	if(random(10))
	    legs = ({ "bezainted_greaves17","chaingreaves18",
		"scale_mail_greaves19" });
	break;
    default:
	feet = ({ "bheavyboots20" });
        if(!random(3))
	{
	    clone_object(ARM_DIR+"bdragonarm")->move(TO, 1);
	}
	else
	{
	    clone_object("/d/Ansalon/balifor/flotsam/obj/armour/bplatemail")->move(TO, 1);
	}
	head = ({ "bdragonhelm31","dragonmask35" });
	legs = ({ "chaingreaves18","scale_mail_greaves19","bshinguards31" });
    }

    if(s = sizeof(head))
	clone_object(ARM_DIR+"head/"+head[random(s)])->move(TO, 1);

    if((s = sizeof(body)) && (!sizeof(torso) || random(2)))
    {
	clone_object(ARM_DIR+"body/"+body[random(s)])->move(TO, 1);
    }
    else if(s = sizeof(torso))
	clone_object(ARM_DIR+"torso/"+torso[random(s)])->move(TO, 1);

    if(s = sizeof(legs))
	clone_object(ARM_DIR+"legs/"+legs[random(s)])->move(TO, 1);

    if(s = sizeof(feet))
	clone_object(ARM_DIR+"feet/"+feet[random(s)])->move(TO, 1);

    if(s = sizeof(arms))
	clone_object(ARM_DIR+"arms/"+arms[random(s)])->move(TO, 1);

    if(s = sizeof(shield))
	clone_object(ARM_DIR+"shield/"+shield[random(s)])->move(TO, 1);
}
