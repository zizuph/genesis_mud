/*
    add_spell_data(
	"lift poison", "parse_lift", TO, "cast_lift", TO,
	16, TO,
	SS_SPELLCRAFT, 100,
	SS_FORM_ABJURATION, 100,
	SS_ELEMENT_LIFE, 100,
	"Lifts poisons from a living being.",
	({ "from <who>" })
    );
    add_spell_data(
	"regeneration", "parse_regeneration", TO, "cast_regeneration", TO,
	([1:5, 2:10, 3:15, 5:20, 10:25]), TO,
	SS_SPELLCRAFT, 100, SS_FORM_ABJURATION, 100, SS_FORM_LIFE, 100,
	"Makes the target heal continuely over a period of time.",
	({ "on <who>" })
    );
    add_spell_data(
	"ease", "parse_ease", TO, "cast_ease", TO,
	([1:1, 2:3, 5:6, 10:9]), TO,
	SS_SPELLCRAFT, 100, SS_FORM_ABJURATION, 100, SS_FORM_LIFE, 100,
	"The targets fatigue is lowered, thereby easing his burdens.",
	({ "<who>" })
    );
    add_spell_data(
	"burn relief", "parse_burn_relief", TO, "cast_burn_relief", TO,
	([1:5, 2:8, 3:10, 5:13, 10:18]), TO,
	SS_SPELLCRAFT, 100, SS_FORM_ABJURATION, 100, SS_FORM_LIFE, 100,
	"The target is relieved from burn injuries.",
	({ "from <who>" })
    );

*/
mixed
parse_healing(string str) 
{
    object *targets;
    int mana;
    string fail;
    
    if(!str)
	return SERR_SYNTAX;

    if(parse_command(str, EP, "[on] %l", targets))
	return get_parsed_objects(targets);
    if(str=="me" || str=="on me")
	return ({ this_player() });
    return "Healing on who?\n"+SERR_SYNTAX;
}

void
heal_one(object tp, object ob, int amount)
{
    int hp;

    hp = Hp(ob);
    ob->heal_me(success*20);
    hp = Hp(ob) - hp;
    switch(hp*100/MaxHp(obs[i]));
    {
	case 0..5:   how = "a teeny weeny bit";	break;
	case 6..10:  how = "a little";		break;
	case 11..20: how = "somewhat";		break;
	case 21..30: how = "quite";		break;
	case 31..50: how = "much";		break;
	case 51..70: how = "very much";		break;
	case 71..90: how = "increadibly";	break;
	default:     how = "devastatingly";	break;
    }
    tellem(tp, ob,
	"[Oth] {looks;feel that you are;looks} "+how+" {healthier;better} now.\n");
    if(obs[i]->query_max_hp() - obs[i]->query_hp() < 10)
	tp->catch_msg(QCTNAME(obs[i])+" is completely healed.\n");
}

mixed
cast_healing(object obs) {
    int i, success, no,	amount;

    obs = FILTER_PRESENT_LIVE(obs);
    obs = FILTER_CAN_SEE(obs, TP);

    if(!(no=sizeof(obs)))
	tellem(TP, 0, "[You] cast[*s] a healing spell, but [he] fail[s] utterly.\n", 1);
	return 1;
    }

/*    tellem(tp, 0, "[You] cast[*s] a spell on "+COMPOSITE_LIVE(obs)+"\n", obs); */
    TP->catch_msg("You cast the spell on "+COMPOSITE_LIVE(obs)+"\n", obs);
    for(i=0;i<no;i++)
	obs[i]->catch_msg(QCTNAME(TP)+" casts a spell on you!\n");
    tell_room(EP,
	QCTNAME(TP)+" casts a spell on "+QCOMPOSITE_LIVE(obs)+".\n");

    success = spell_success(TP);

    if(success<=0) {
	if(TP==ob) tellem(TP, 0, "[Your] healing spell failed miserably!\n", 1);
	else tellem(TP, ob, "[Your] healing spell failed miserably!\n", 1);
    }

    success = rnd_dist(no, success);
    for(i=0;i<no;i++)
	heal_one(TP, obs[i], success[i]);
}

/*-------------------------------------------------------------------*/

mixed
parse_lift(string str) 
{
    object victim;
    string fail;
    int mana;

    if(!str)
	return SERR_SYNTAX;

    victim = ({ 0, this_player() });
    if(!parse_command(str, ({ environment(this_player()) }),
	"[ 'from' / 'upon' / 'on' ] %l", victim) &&
       !parse_command(str, ({ }),
	   "[ 'from' / 'upon' / 'on' ] 'me'") )
	return SERR_SYNTAX;

    return this_object_first(TP, get_parsed_objects(victim));
}

void
lift_one(object TP, object target, int power)
{
    int i;
    object *inv = all_inventory(target);

    for (i = 0; i < sizeof(inv); i++ )
    {
        if (function_exists("cure_poison", inv[i]))
	{
	    inv[i]->cure_poison( ({ "all" }), power);
	    power /= 2;
        }
    }
}

void
cast_lift(object *target)
{
    object victim;
    object *inv;
    int i;
    mixed succ;
    int no;
    int power;
    string comp_str;

    target = FILTER_CAN_SEE(FILTER_PRESENT_LIVE(target), TP);

    succ = spell_success(TP);

    if(succ<=0) {
	tellem(TP, 0, "[Your] {lift spell;odd spell} failed.\n",1);
	return;
    }

    succ = rnd_dist(no, succ);

    if(TP==target[0])
	comp = "[your]self and "+COMPOSITE_LIVE(target-({TP}));
    else
	comp = COMPOSITE_LIVE(target);

    tellem(TP, 0, "[You] cast[*s] a Lift Poison spell on "+comp+".\n", 1);

    for(i=0;i<no;i++)
	lift_one(TP, target[i], succ[i]);
}

mixed
parse_burn_relief(string str) 
{
    object *victim;
    string fail;
    int mana;

    victim = ({ 1, this_player() });
    if(!parse_command(str, ({ environment(this_player()) }),
	"[ 'upon' / 'on' ] %l", victim) &&
       !parse_command(str, ({ }),
	   "[ 'upon' / 'on' ] 'me'") )
	return SERR_SYNTAX;

    return victim;
}

void
do_injurie_healing(object who, object TP, string type, int strength, int reduce)
{
    object *inv;
    int i;

    inv = all_inventory(who);

    if(reduce<0) reduce = 0;
    if(reduce>100) reduce = 100;

    for (i = 0; i < sizeof(inv); i++ )
    {
        if ( 
	    (function_exists("heal_injurie", inv[i]) && 
	     inv[i]->query_type()==type) ||
	    (function_exists("heal_injurie", inv[i]) &&
	     type=="all")
	)
        {
            inv[i]->heal_injurie(strength);
            strength = strength * reduce / 100;
        }
    }
}

void
cast_burn_relief(object TP, mixed b)
{
    int class;
    int strength;
    int reduce;

    class = query_spell_class();
    if(class==10) {
	strength = 100;
	reduce   = 100;
    } else {
	strength = random(class*40);
	reduce	 = 20 + random(level(TP)*4);
    }
    if(TP==b[0]) {
	TP->catch_msg("You cast a Burn Relief spell on yourself.\n");
	tell_room(E(TP),QCTNAME(TP)+" casts a spell on "+Him(TP)+"self.\n");
    } else {
	TP->catch_msg("You cast a Burn Relief spell on "+QTNAME(b[0])+".\n");
	b[0]->catch_msg(QCTNAME(TP)+" casts a Burn Relief spell on you.\n");
	tell_room(E(TP),
	    QCTNAME(TP)+" casts a spell on "+QTNAME(b[0])+".\n", ({TP, b[0] }));
    }
    do_injurie_healing(b[0], TP, "burn", strength, reduce);
    return;
}

mixed
parse_regeneration(string str) {
    object v;
    int mana;
    string fail;

    NF("Syntax: SPELL on <who>\n");

    v = this_player();    
   
    if(str && 
       !parse_command(str, ({ EP }), "'on' / 'upon' %l", v) &&
       !parse_command(str, ({ }), "'on' / 'upon' 'me'") )
	return 0;
	
    mana = query_spell_class()*MANA_REGENERATION;
    if(fail=check_room())
	Fail(fail);
    if(fail=check_player(TP, mana))
	Fail(fail);
    if(present("_regen_obj_", v))
	Fail("Sorry. Victim already regenerates.\n");
    return ({ v });
}    

mixed
cast_regeneration(object TP, mixed a)
{
    object reg_ob, victim;
    int class;
    
    class = query_spell_class();
    victim = a[0];
    TP -> catch_msg(
	"You cast a regeneration "+roman_str(class)+" spell on "+
	(victim==TP?"yourself": QTNAME(victim))+ ".\n");
    if(TP!=victim)
	victim -> catch_msg(
	    QCTNAME(TP)+" casts a regeneration spell on you!\n");
    tell_room(E(TP),
	QCTNAME(TP)+" casts a regeneration spell on "+
	(victim==TP? Him(TP)+"self": QTNAME(victim) ), ({ TP, victim }) );
    
    seteuid(getuid());
    reg_ob = clone_object(STD_DIR + "regen_obj");
    reg_ob -> set_time(level(TP)*18+60);
    reg_ob -> set_interval(10);
    reg_ob -> set_strength(class*100);
    reg_ob -> move(victim);
    reg_ob -> start_regeneration();
}

mixed 
parse_ease(string str) 
{
    mixed *r;
    object *o;
    int mana;
    string fail;
    
    NF("Syntax: SPELL <who>\n");
    
    if(!str || str=="") return 0;
    if(str=="me")
	o = ({ this_player() });
    else
	o = FIND_STR_IN_OBJECT(str, EP);
    
    if(!sizeof(o)) 
	Fail("Ease who?\nSyntax: SPELL <who>\n");
    if(sizeof(o)>1 || !living(o[0])) 
	Fail("You can only ease one living.\n");

    mana = query_spell_class()*MANA_EASE;
    if(fail=check_room())
	Fail(fail);
    if(fail=check_player(TP,mana))
	Fail(fail);
    return ({ o[0] });
}

mixed
cast_ease(object TP, mixed res) {
    int i;

    if(TP==res[0]) {
	TP->catch_msg("Your tired muscles recieves ease.\n");
	tell_room(E(TP), QCTNAME(TP)+" casts a spell on "+him(TP)+"self.\n", TP);
    } else {
	TP->catch_msg("You ease "+QTNAME(res[0])+"'s tired muscles.\n");
	res[0]->catch_msg(QCTNAME(TP)+" touches you easing your tired muscles.\n");
	tell_room(E(TP),  QCTNAME(TP)+" touches "+QTNAME(res[0])+
	    " easing "+his(TP)+" tired muscles.\n", ({TP, res[0]}));
    }
    if(query_spell_class()==10) 
	res[0]->set_fatigue(res[0]->query_max_fatigue());
    else
	for(i=0;i<query_spell_class();i++)
	    res[0]->add_fatigue(random(10)+1); /* <class>d10 */
    return 1;
}
