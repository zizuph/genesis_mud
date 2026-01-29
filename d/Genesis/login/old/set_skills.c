
/* 
 * This is an object that allows people to choose skills.
 */

#define PATH "/d/Genesis/login/"

inherit "/std/object";
inherit "/lib/skill_raise";

#include "login.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

static	int coins;

create_object() 
{
    int lev;
    object opl;

    set_name("trainer"); 
    set_short("skill trainer");

    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show(1);
    
    lev = 2;

    opl = this_player()->query_old_player();
    if (opl)
	lev += opl->q_level();

    lev *= 3;
    lev /= 2; /* We should have 3 - 30 */

    coins = (lev * lev * lev * 80) / 100;   /* Coins / skill */
    coins *= 10;   /* Number of skills to be able to train */

    create_skill_raise();
    /* Weapon skills */
    sk_add_train(SS_WEP_SWORD	       ,0 ,0, 0, 32);  /* W_SWORD */
    sk_add_train(SS_WEP_POLEARM	       ,0 ,0, 0, 29);  /* W_POLEARM */
    sk_add_train(SS_WEP_AXE	       ,0 ,0, 0, 30);  /* W_AXE */
    sk_add_train(SS_WEP_KNIFE	       ,0 ,0, 0, 31);  /* W_KNIFE */
    sk_add_train(SS_WEP_CLUB	       ,0 ,0, 0, 32);  /* W_CLUB */
/*
    sk_add_train(SS_WEP_MISSILE	       ,0 ,0, 0, 30);
    sk_add_train(SS_WEP_JAVELIN	       ,0 ,0, 0, 28);
*/

    /* General fighting skills */
/*   
    sk_add_train( SS_2H_COMBAT	,0,0,0, 30);
    sk_add_train( SS_UNARM_COMBAT	,0,0,0, 30);
    sk_add_train( SS_BLIND_COMBAT	,0,0,0, 30);
*/
    sk_add_train( SS_PARRY		,0,0,0, 33);
    sk_add_train( SS_DEFENCE		,0,0,0, 27);

    /* Magic skills */
    sk_add_train( SS_SPELLCRAFT		,0,0,0, 30);
/*
    sk_add_train( SS_HERBALISM		,0,0,0, 30);
    sk_add_train( SS_ALCHEMY		,0,0,0, 30);

    sk_add_train( SS_FORM_TRANSMUTATION ,0,0,0, 30);
    sk_add_train( SS_FORM_ILLUSION      ,0,0,0, 30);
    sk_add_train( SS_FORM_DIVINATION    ,0,0,0, 30);
    sk_add_train( SS_FORM_ENCHANTMENT   ,0,0,0, 30);
    sk_add_train( SS_FORM_CONJURATION   ,0,0,0, 30);
    sk_add_train( SS_FORM_ABJURATION    ,0,0,0, 30);

    sk_add_train( SS_ELEMENT_FIRE       ,0,0,0, 30);
    sk_add_train( SS_ELEMENT_AIR        ,0,0,0, 30);
    sk_add_train( SS_ELEMENT_EARTH      ,0,0,0, 30);
    sk_add_train( SS_ELEMENT_WATER      ,0,0,0, 30);
    sk_add_train( SS_ELEMENT_LIFE       ,0,0,0, 30);
    sk_add_train( SS_ELEMENT_DEATH      ,0,0,0, 30);

*/

    /* Thief skills */
/*
    sk_add_train( SS_OPEN_LOCK		,0,0,0, 30);
    sk_add_train( SS_PICK_POCKET	,0,0,0, 30);
    sk_add_train( SS_ACROBAT		,0,0,0, 30);
    sk_add_train( SS_FR_TRAP		,0,0,0, 30);
    sk_add_train( SS_SNEAK		,0,0,0, 30);
    sk_add_train( SS_HIDE		,0,0,0, 30);
    sk_add_train( SS_BACKSTAB		,0,0,0, 30);
*/
    /* General skills */
    sk_add_train( SS_APPR_MON		,0,0,0, 53);
    sk_add_train( SS_APPR_OBJ		,0,0,0, 51);
    sk_add_train( SS_APPR_VAL		,0,0,0, 50);
    sk_add_train( SS_SWIM		,0,0,0, 50);
    sk_add_train( SS_CLIMB		,0,0,0, 54);
    sk_add_train( SS_ANI_HANDL		,0,0,0, 50);
    sk_add_train( SS_LOC_SENSE		,0,0,0, 52);
    sk_add_train( SS_TRACKING		,0,0,0, 50);
    sk_add_train( SS_HUNTING		,0,0,0, 49);
    sk_add_train( SS_LANGUAGE		,0,0,0, 50);
    sk_add_train( SS_AWARENESS		,0,0,0, 48);
    sk_add_train( SS_TRADING		,0,0,0, 50);
}

init()
{
    if (this_player()->query_skill_coins())
	coins = this_player()->query_skill_coins();

    add_action("list", "list");
    add_action("show", "show");
    add_action("improve", "improve");
    add_action("cost", "cost");
    add_action("levels", "levels");
    add_action("done", "done");
    add_action("instruct", "instructions");
    add_action("instruct", "help");
    add_action("instruct", "ask");
}

public int instruct(string str)
{
    write(
"The face says: I can help you raise your skills magically for a small fee.\n" + 
"The face says: You can request the following:\n\n" +
"  list                 I'll tell you all possible skills to advance in\n" +
"  show                 I'll tell you your current skills and virtual coins left\n" +
"  improve <skill> num  I'll improve one of your skills a number of times\n" +
"  cost <skill> num     I'll tell you the cost in coins to improve a skill\n" +
"  levels               I'll tell you the main skill educational levels\n" +
"  done                 Tell me this when you are done improving skills\n\n" +
"  Examples:\n" +
"      list\n" +
"      improve sword\n");
    return 1;
}

public int 
show(string str)
{
    int il, *sklist;

    sklist = this_player()->query_all_skill_types();

    write("The face says: You currently have skill in " + sizeof(sklist) + " activities.\n");
    for (il = 0; il < sizeof(sklist); il++)
    {
	write(sprintf("%-18s %-20s ", sk_query_name(sklist[il])+":", 
		      sk_rank(this_player()->query_base_skill(sklist[il]))));
	if (il % 2)
	    write("\n");
    }
    if (coins < 1)
	write("\n\nThe face says: You have no coins left to buy skills with.\n");
    else
    	write("\n\nThe face says: You have " + coins + " coins left to buy skills with.\n");

    return 1;
}

public int 
list(string str)
{
    int il, *sklist;

    sklist = sk_query_train();

    write("The face says: You can train " + sizeof(sklist) + " different activities,\n");
    write("to the below maximum levels.\n");

    for (il = 0; il < sizeof(sklist); il++)
    {
	write(sprintf("%-18s %-20s ", sk_query_name(sklist[il])+":", 
		      sk_rank(sk_query_max(sklist[il]))));
	if (il % 2)
	    write("\n");
    }
    return 1;
}

public int 
cost(string str)
{
    int sk, cur, num;
    string *st;
    
    if (strlen(str))
    {
	st = explode(str," ");
	if (sizeof(st) > 1 && sscanf(st[sizeof(st) - 1], "%d", num))
	    str = implode(st[0 .. sizeof(st) - 2], " ");
    }

    if (!str || (sk = sk_find_skill(str)) < 0)
    {
	write("The face says: I can not help you with: " + str + ".\n");
	return 1;
    }
    cur = this_player()->query_base_skill(sk);

    if (num > 1)
	write("The face says: To improve " + sk_query_name(sk) + " " + num + 
	      " times, you must pay " +
	      sk_cost(sk, cur, cur + num) + " coins.\n");
    else
	write("The face says: The improvement cost for " + sk_query_name(sk) + " is: " +
	      sk_cost(sk, cur, cur + 1) + " coins.\n");
    return 1;
}
    
public int
improve(string str)
{
    int sk, cur, num, rcost;
    string *st;

    if (strlen(str))
    {
	st = explode(str," ");
	if (sizeof(st) > 1 && sscanf(st[sizeof(st) - 1], "%d", num))
	    str = implode(st[0 .. sizeof(st) - 2], " ");
    }

    if (!str || (sk = sk_find_skill(str)) < 0)
    {
	write("The face says: No such skill to train here: " + str + ".\n");
	return 1;
    }
    cur = this_player()->query_base_skill(sk);

    if (num < 1)
	num = 1;

    rcost = sk_cost(sk, cur, cur + num);

    if (rcost > coins)
    {
	write("The face says: You do not have " + rcost + " coins left.\n");
	return 1;
    }
    
    if (!sk_do_train(sk, this_player(), cur + num))
    {
	if (num == 1)
	    write("The face says: You can not train any more in " + 
		  sk_query_name(sk) + ".\n");
	else
	    write("The face says: You can not train that much more in " + 
		  sk_query_name(sk) + ".\n");
	return 1;
    }
    else
    {
	write("The face says: The cost was " + rcost + " coins.\n");
	coins -= rcost;
	if (coins == 0)
	    coins = -1;
	this_player()->set_skill_coins(coins);
    }
    return 1;
}
	
public int
done(string str)
{
    if (coins > 0)
    {
	if (str != "improving")
	{
	    write("The face says: You must say 'done improving'\nNote you will lose " +
		  "the " + coins + " coins, that you still have.\n");
	    return 1;
	}
    }

    coins = 0;
    write("Ok.\n");
    if (this_player()->query_ghost() & GP_SKILLS)
	this_player()->set_ghost(this_player()->query_ghost() - GP_SKILLS);
    destruct();
    return 1;
}

public int
levels(string str)
{
    int il;
    string *levs;

    levs = sk_query_main_levels();

    write("The face says: These are the levels of education:\n");
    write(break_string(implode(levs,", "), 70,3) + "\n");

    levs = sk_query_sub_levels() - ({""});
    write("The face says: In those you can be:\n");
    write(break_string(implode(levs,", "), 70,3) + "\n");
    return 1;
}

    
