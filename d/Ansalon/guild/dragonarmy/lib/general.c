/* Navarre July 3rd 2006, fixed line:
 * write("You punish " +C(str)+ " by "+punishment+"!\n");
 * Changed it to:
 * write("You punish " +C(name)+ " by "+punishment+"!\n");
 */

/* Code for general commands */
#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include <macros.h>
#include <mail.h>
#include <cmdparse.h>

int
add_master_title(string str)
{
    string div, title;

    if(TP->query_dragonarmy_promotions() < 4)
	return 0;

    setuid();
    seteuid(getuid());

    if(!str || !sscanf(str, "master title %s", title))
    {
	NF("Add what? Master title?\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();

    if (MANAGER->add_master_title(title, div))
	TP->catch_tell("Title '"+title+"' added to master titles.\n");
    else
	TP->catch_tell("Title '"+title+"' not added to master titles.\n"+
			"A modification already exists.\n"+
			"Do 'check masters' please.\n");
    return 1;
}

int
remove_master_title(string str)
{
    string div, title;

    if(TP->query_dragonarmy_promotions() < 4)
	return 0;

    setuid();
    seteuid(getuid());

    if(!str || !sscanf(str, "master title %s", title))
    {
	NF("Remove what? Master title?\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();

    if (MANAGER->remove_master_title(title, div))
	TP->catch_tell("Title '"+title+"' removed from master titles.\n");
    else
	TP->catch_tell("Title '"+title+"' is not a master title.\n"+
			"Do 'check masters' please.\n");
    return 1;
}

int
set_master(string str)
{
    string div, title, who;

    if(TP->query_dragonarmy_promotions() < 4)
	return 0;

    setuid();
    seteuid(getuid());

    if(!str || sscanf(str, "%s with the duty of %s", who, title) != 2)
    {
	NF("Charge who with the duty of what?\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();

    switch (MANAGER->set_master(who, title, div))
    {
    case 0:
	TP->catch_tell("You charge "+C(who)+" with the duty of "+title+".\n");
	break;
    case 1:
	TP->catch_tell("Charge WHO with the duty of what?\n");
	break;
    case 2:
    case 3:
	TP->catch_tell(C(who)+" is not a member of your army.\n");
	break;
    case 4:
	TP->catch_tell("First you must add some master titles.\n");
	break;
    case 5:
	TP->catch_tell("There is no master title '"+title+"'. "+
			"Do 'check masters' please.\n");
	break;
    case 6:
	TP->catch_tell(C(who)+" already has a master position. "+
			"Do 'check masters' please.\n");
	break;
    default:
	TP->catch_tell("Unnown error. Contact your guildmaster.\n");
    }
    return 1;
}

int
remove_master(string str)
{
    string div, title, who;

    if(TP->query_dragonarmy_promotions() < 4)
	return 0;

    setuid();
    seteuid(getuid());

    if(!str || sscanf(str, "%s of the duty of %s", who, title) != 2)
    {
	NF("Revoke who of the duty of what?\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();

    switch (MANAGER->remove_master(who, title, div))
    {
    case 0:
	TP->catch_tell("You revoke "+C(who)+" of the duty of "+title+".\n");
	break;
    case 1:
	TP->catch_tell("Revoke WHO of the duty of what?\n");
	break;
    case 4:
	TP->catch_tell("No masters defined.\n");
	break;
    case 5:
	TP->catch_tell("There is no master title '"+title+"'. "+
			"Do 'check masters' please.\n");
	break;
    default:
	TP->catch_tell("Unnown error. Contact your guildmaster.\n");
    }
    return 1;
}

int
query_masters(string str)
{
    string div, *titles, *names;
    mapping masters;
    int i, j, st;

    setuid();
    seteuid(getuid());

    if(str != "masters")
    {
	NF("Check what? Masters?\n");
	return 0;
    }

    masters = MANAGER->query_masters(TP->query_dragonarmy_division());
    titles = m_indices(masters);
    if (!(st = sizeof(titles)))
    {
	TP->catch_tell("No master positions were assigned.\n");
	return 1;
    }
    TP->catch_tell("These master positions are assigned:\n");
    for (i=0; i < st; i++)
    {
	str = titles[i] + ": ";
	for (j=0; j < sizeof(masters[titles[i]]); j++)
	    str += (j ? ", " : "") + C(masters[titles[i]][j]);
	TP->catch_tell(str+"\n");
    }
    return 1;
}

int
make_general(string str)
{
    object ob, *obj;
    string div;

    if(TP->query_dragonarmy_promotions() < 4)
	return 0;

    setuid();
    seteuid(getuid());
    if(!str || !sizeof(obj = PARSE_THIS(str, "'leadership' 'to' [the] %l")))
    {
	NF("Relinquish leadership to who?\n");
	return 0;
    }
    if(sizeof(obj) > 1)
    {
	NF("Be more specific! You can relinquish leadership only to one.\n");
	return 0;
    }

    ob = obj[0];
    if(!IS_MEMBER(ob))
    {
	NF(ob->query_The_name(TP)+" is not a part of the dragonarmy.\n");
	return 0;
    }
    div = TP->query_dragonarmy_division();
    if(div != ob->query_dragonarmy_division())
    {
	NF(ob->query_The_name(TP)+" is not member of the "+C(div)+" dragonarmy.\n");
	return 0;
    }
    if(!interactive(ob))
    {
	NF(ob->query_The_name(TP)+" cannot accept such position.\n");
	return 0;
    }

    ob->set_promotion_level(4, TP);
    TP->set_promotion_level(2, TP);
    TP->catch_tell("You relinquish the leadership of the "+C(div)+" dragonarmy to "+
	ob->query_the_name(TP)+".\n");
    ob->catch_tell(TP->query_the_name(ob)+" relinquishes leadership of the "+C(div)+
	" dragonarmy to you.\n");
    tell_room(E(TP), QCTNAME(TP)+" relinquishes leadership of the "+C(div)+
	" dragonarmy to "+QTNAME(ob)+".\n", ({TP, ob}) );
    return 1;
}

int
punish_soldier(string str)
{
    string div, name, punishment, toatt = "";
    int percent, rank = TP->query_dragonarmy_promotions();
    mixed tmp;

    /*Only HO++ can punish*/
    if(rank < 3)
	return 0;

    if(!str || sscanf(str, "%s by %s", name, punishment) != 2)
    {
	NF("Syntax is 'punish <person> by <punishment>'.\n");
	return 0;
    }

    setuid();
    seteuid(getuid());
    name = MANAGER->get_name(name);

    if(!MANAGER->query_member(name))
    {
	NF(C(name)+" is not a part of the dragonarmy.\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();
    if(MANAGER->query_division(name) != div)
    {
	NF(C(name)+" is from a different division of the dragonarmy.\n");
	return 0;
    }

    if(MANAGER->query_promotions(name) >= rank)
    {
	NF("Your rank is not high enough to punish "+C(name)+" .\n");
	return 0;
    }

    switch(punishment)
    {
/*******************************************        DEATH        ***********/
    case "death":
	if (rank < 4)
	{
	    write("Only General can punish by death.\n");
	    return 1;
	}
	if (MANAGER->query_punishment(name, PUN_DEATH))
	{
	    write(C(name)+" was already sentenced to death. Execution pending.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_DEATH);
	break;
/*******************************************    ERASING RECORD   ***********/
    case "erasing the record":
	if (rank < 4)
	{
	    write("Only General can punish by erasing the record.\n");
	    return 1;
	}
	if (MANAGER->query_punishment(name, PUN_NOGUILDXP))
	{
	    write("Clerks already process "+C(name)+"'s record.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOGUILDXP);
	break;
/*******************************************     NO TRAINING     ***********/
    case "banning from training":
	if (rank < 3)
	{
	    write("Only High Officers can punish by banning from training.\n");
	    return 1;
	}
	if (MANAGER->query_punishment(name, PUN_NOTRAIN))
	{
	    write(C(name)+" has already denied training.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOTRAIN);
	break;
/*******************************************    FUNDRISING 3/4   ***********/
    case "lowering fundrising account to three quarters":
	if (rank < 3)
	{
	    write("Only High Officers can punish by lowering fundrising account.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOFUND_TQ);
	break;
/*******************************************    FUNDRISING 1/2   ***********/
    case "lowering fundrising account to half":
	if (rank < 3)
	{
	    write("Only High Officers can punish by lowering fundrising account.\n");
	    return 1;
	}
	if (MANAGER->query_punishment(name, PUN_NOFUND_H))
	{
	    write("Clerks already process "+C(name)+"'s fundrising record.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOFUND_H);
	break;
/*******************************************   FUNDRISING ERASE  ***********/
    case "erasing fundrising account":
	if (rank < 3)
	{
	    write("Only High Officers can punish by erasing fundrising account.\n");
	    return 1;
	}
	if (MANAGER->query_punishment(name, PUN_NOFUND_O))
	{
	    write("Clerks already process "+C(name)+"'s fundrising record.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOFUND_O);
	break;
/*******************************************        NO GURU      ***********/
    case "deeming unworthy":
	if (rank < 3)
	{
	    write("Only High Officers can punish by deeming unworthy.\n");
	    return 1;
	}
	if (MANAGER->query_punishment(name, PUN_NOGURU))
	{
	    write("Clerks already process "+C(name)+"'s worthines record.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOGURU);
	break;
/*******************************************      ARMOURY        ***********/
    case "restricting armoury access":
	if (MANAGER->query_punishment(name, PUN_NOARMOURY))
	{
	    write(C(name)+" already has restricted armoury access.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOARMOURY);
	break;
/*******************************************        BOARD        ***********/
    case "restricting board access":
	if (MANAGER->query_punishment(name, PUN_NOBOARD))
	{
	    write(C(name)+" already has restricted board access.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOBOARD);
	break;
/*******************************************        DLIST        ***********/
    case "restricting dlist":
	if (MANAGER->query_punishment(name, PUN_NOWHO))
	{
	    write(C(name)+" already has restricted dlist access.\n");
	    return 1;
	}
	MANAGER->add_punishment(name, PUN_NOWHO);
	break;
/*******************************************     BAD COMMAND     ***********/
    default:
	NF("There is no such punishment.\n");
	return 0;
    } /* end of swith */

    CREATE_MAIL("PUNISHMENT", "dragonarmy", name, "", ctime(time())+"\n"+
	TP->query_name()+" punished you by "+punishment+
	".\nDragonarmy Informer" );

    if (rank < 4 && (tmp = MANAGER->query_member_list(div)))
    {
	while(++rank < 5)
	    toatt += implode(tmp[rank], ",") + ",";
	CREATE_MAIL("PUNISHMENT", "dragonarmy", toatt, "", ctime(time())+"\n"+
	    TP->query_name()+" punished "+C(name)+" by "+punishment+
	    ".\nDragonarmy Informer" );
    }

    write("You punish " +C(name)+ " by "+punishment+"!\n");
    return 1;
}

int
ban_from_dragonarmy(string str)
{
    string name, div;

    if(TP->query_dragonarmy_promotions() < 4)
	return 0;

    if(!str || sscanf(str, "%s from dragonarmy", name) == 0)
    {
	NF("Syntax is 'ban <name> from dragonarmy'.\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();

    if (!SECURITY->exist_player(name))
    {
	NF("There is no player named '"+C(name)+"'.\n");
	return 0;
    }
    if (MANAGER->query_banned(name, div))
    {
	NF(C(name)+" was already banned from the "+C(div)+" dragonarmy!\n");
	return 0;
    }
    MANAGER->set_banned(name, div);
    write("You banned "+C(name)+" from the "+C(div)+" dragonarmy!\n");
    return 1;
}

int
remove_ban(string str)
{
    string ban, name, div, toatt = "";
    int rank = TP->query_dragonarmy_promotions();
    mixed tmp;

    /*Only HO++ can remove bans - Louie*/
    if (rank < 3)
	return 0;

    if (!str || sscanf(str, "%s ban from %s", ban, name) < 2 ||
	member_array(ban, ({"joining","training","armoury","board","dlist"})) < 0)
    {
	NF("Syntax is 'lift joining ban from <name>' or\n"+
	   "          'lift training ban from <name>' or\n"+
	   "          'lift armoury ban from <name>' or\n"+
       "          'lift dlist ban from <name>' or\n"+
	   "          'lift board ban from <name>'.\n");
	return 0;
    }

    setuid();
    seteuid(getuid());
    name = L(name);
    div = TP->query_dragonarmy_division();

    if (MANAGER->query_division(name) != div && ban != "joining")
    {
	NF(C(name)+" is not a member of "+C(div)+" Dragonarmy.\n");
	return 0;
    }

    if(rank < 4 && MANAGER->query_promotions(name) >= rank)
    {
	NF("Your rank is not high enough to lift ban from "+C(name)+" .\n");
	return 0;
    }

    switch(ban)
    {
/*******************************************     NO TRAINING     ***********/
    case "training":
	if (rank < 3)
	{
	    NF("Only High Officers can lift training ban.\n");
	    return 0;
	}
	if (!MANAGER->query_punishment(name, PUN_NOTRAIN))
	{
	    NF(C(name)+" is not banned from training.\n");
	    return 0;
	}
	MANAGER->remove_punishment(name, PUN_NOTRAIN);
	break;
/*******************************************      ARMOURY        ***********/
    case "armoury":
	if (!MANAGER->query_punishment(name, PUN_NOARMOURY))
	{
	    NF(C(name)+" does not have restricted armoury access.\n");
	    return 0;
	}
	MANAGER->remove_punishment(name, PUN_NOARMOURY);
	break;
/*******************************************        BOARD        ***********/
    case "board":
	if (!MANAGER->query_punishment(name, PUN_NOBOARD))
	{
	    NF(C(name)+" does not have restricted board access.\n");
	    return 0;
	}
	MANAGER->remove_punishment(name, PUN_NOBOARD);
	break;
/*******************************************        DLIST        ***********/
    case "dlist":
	if (!MANAGER->query_punishment(name, PUN_NOWHO))
	{
	    NF(C(name)+" does not have restricted dlist access.\n");
	    return 0;
	}
	MANAGER->remove_punishment(name, PUN_NOWHO);
	break;
/*******************************************       JOINING       ***********/
    case "joining":
	if (rank < 4)
	{
	    NF("Only General can lift joining ban.\n");
	    return 0;
	}
	if (!MANAGER->query_banned(name, div))
	{
	    NF(C(name)+" is not banned from joining.\n");
	    return 0;
	}
	MANAGER->remove_banned(name, div);
	break;
/*******************************************     IMPOSSIBLE      ***********/
    default:
	NF("This is impossible!!!\n");
	return 0;
    } /* end of swith */

    CREATE_MAIL("PUNISHMENT", "dragonarmy", name, "", ctime(time())+"\n"+
	"Your "+ban+" ban has been lifted by "+TP->query_name()+
	".\nDragonarmy Informer" );

    if (rank < 4 && (tmp = MANAGER->query_member_list(div)))
    {
	while(++rank < 5)
	    toatt += implode(tmp[rank], ",") + ",";
	CREATE_MAIL("PUNISHMENT", "dragonarmy", toatt, "", ctime(time())+"\n"+
	    TP->query_name()+" lifted "+ban+" ban from "+C(name)+
	    ".\nDragonarmy Informer" );
    }

    write("You lifted "+ban+" ban from "+C(name)+".\n");
    return 1;
}

int
submit_life(string str)
{
    object ob, *obj;

    setuid();
    seteuid(getuid());
    if(!str || !sizeof(obj = PARSE_THIS(str, "'life' 'to' [the] %l")))
	return 0;

    if(!MANAGER->query_punishment(TP, PUN_DEATH))
    {
	NF("You were not punished by death. No need to submit life.\n");
	return 0;
    }
    if(sizeof(obj) > 1)
    {
	NF("Be more specific! You can submit life only to one.\n");
	return 0;
    }
    ob = obj[0];
    if(!IS_MEMBER(ob))
    {
	NF(ob->query_The_name(TP)+" is not a part of the dragonarmy.\n");
	return 0;
    }
    TP->add_prop("_dragonarmy_submited_life", ob);
    TP->catch_tell("You kneel before "+ob->query_the_name(TP)+
	" submitting your life into "+HIS(ob)+" hands.\n");
    ob->catch_tell(TP->query_The_name(ob)+" kneels before you submitting "+
	HIS(TP)+" life into your hands.\n");
    tell_room(E(TP), QCTNAME(TP)+" kneels before "+QTNAME(ob)+
	" submitting "+HIS(TP)+" life into "+HIS(ob)+" hands.\n", ({TP, ob}) );

    if(!interactive(ob))
    {
	MANAGER->remove_punishment(TP, PUN_DEATH);
	ob->command("say In the name of the Queen of Darkness, Takhisis!");
	TP->catch_tell(ob->query_The_name(TP)+" moves behind you...\n");
	tell_room(E(TP), QCTNAME(ob)+" moves behind "+QTNAME(TP)+
	    " and quickly breaks "+HIS(TP)+" neck.\n", ({TP, ob}) );

	TP->heal_hp(-TP->query_hp());
	TP->heal_hp(-10000);
	TP->do_die(TO);
    }
    return 1;
}

int
exterminate(string str)
{
    object ob, *obj;

    setuid();
    seteuid(getuid());
    if(!str || !sizeof(obj = PARSE_THIS(str, "[the] %l")))
    {
	NF("Exterminate who?\n");
	return 0;
    }
    if(sizeof(obj) > 1)
    {
	NF("Be more specific! You can exterminate only one at a time.\n");
	return 0;
    }
    ob = obj[0];
    if(ob->query_prop("_dragonarmy_submited_life") != TP)
    {
	NF(ob->query_The_name(TP)+" has not submitted life to you.\n");
	return 0;
    }

    MANAGER->remove_punishment(ob, PUN_DEATH);
    TP->command("say In the name of the Queen of Darkness, Takhisis!");
    TP->catch_tell("You move behind "+ob->query_the_name(TP)+
	" and quickly break "+HIS(ob)+" neck.\n");
    ob->catch_tell(TP->query_The_name(ob)+" moves behind you...\n");
    tell_room(E(TP), QCTNAME(TP)+" moves behind "+QTNAME(ob)+
	" and quickly breaks "+HIS(ob)+" neck.\n", ({TP, ob}) );

    ob->heal_hp(-ob->query_hp());
    ob->heal_hp(-10000);
    ob->do_die(TO);
    return 1;
}

