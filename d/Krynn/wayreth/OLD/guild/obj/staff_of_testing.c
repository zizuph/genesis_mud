/*
 *  The Staff of Testing for the Wizards of High Sorcery
 *
 *  by Karath Dec 10, 1997
 *  Andrew Smith
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include "../local.h"
#include "../../local.h"
#include <macros.h>

inherit "/std/weapon.c";

static gTmp;

#define CHECK_SO_CONCLAVE if (!IS_CONCLAVE(RNAME(TP))) return 0;
#define CHECK_IN_TOWER    if (!TP->query_wiz_level() && \
			      !(E(TP) && sscanf(file_name(E(TP)), WTOWER + \
		              "%s", gTmp))) return NF("This command may " + \
			      "only be performed while inside a Tower " + \
			      "of High Sorcery.\n");

private int test_control(string str);
public void do_test_start(object conclave, object apprentice);

public void
create_weapon()
{
    set_name("staff");
    add_name( ({"_wohs_staff_of_testing", "staff of Testing",
	"staff of testing", "Staff of Testing"}) );
    set_pname("staves");
    add_pname( ({"staves of Testing", "staves of testing"}) );

    add_adj( ({"testing", "ornate", "platinum-sheathed"}) );

    set_short("ornate platinum-sheathed staff");
    set_long("This staff is a most impressive piece of work. It seems "+
	"rather ornate for a weapon, or even just any mage's personal "+
	"equipment. The shaft is carved from some very dark and heavy "+
	"wood, then three ribbons of what appears to be platinum have "+
	"been woven into a sheath that goes from the bottom of the staff "+
	"to the top, where the ribbons meld together forming three faces "+
	"looking in all three directions. Each face has two eyes. The "+
	"first with a solemn, but not unkind face has two brilliant pearls "+
	"for eyes. The second, bearing a face full of wisdom showing no "+
	"emotion except perhaps clarity stares out through two brilliant "+
	"flaming rubies. The last bears almost a cruel sneer upon it's "+
	"visage, it's eyes of darkest opal piercing at all before it.\n");

    add_prop(OBJ_M_NO_BUY, "This staff is not sellable!");
    add_prop(OBJ_M_NO_SELL, "This staff is not sellable!");
	
    set_default_weapon( 30, 15, W_POLEARM, W_BLUDGEON, W_BOTH);

    set_wf(TO);
}

public void
init()
{
    if(IS_CONCLAVE(RNAME(TP)))
      {
	add_action(test_control, "test");
      }
    ::init();
}

public int
test_control(string str)
{
    int i;
    string player_st, stage_st, footemp;
    object whom, *conclaves;

    CHECK_IN_TOWER;

    NF("Test what stage for whom?\n");

    if( !str && !strlen(str))
	return 0;

    if(str == "help")
      {
	write(
		"Syntax for the Staff of Testing:\n"+
		"-------------------------------\n"+
		"To begin a Test, the Apprentice being Tested must be "+
		"within the Tower of Wayreth and the Conclave member "+
		"must also be within the Tower.\n"+
		"The syntax for this command is in the form of:\n"+
		"- test <stage> for <apprentice>\n\n"+
		"Here are the possible stages:\n"+
		"- test begin for <apprentice>\n\tBegin the Test\n\n"+
		"- test battle for <apprentice>\n\tSummon the Apprentice "+
			"to battle where they will fight for their "+
			"life.\n\n"+
		"- test questioning for <apprentice>\n\tSummon the Apprentice "+
			"to a Spectral Guardian who you can control "+
			"to ask questions of the Apprentice and "+
			"judge the responses.\n\n"+
		"- test personal for <apprentice>\n\tBegin the stage where "+
			"the Apprentice is tested in a way that is "+
			"personally meaningful for them that tests "+
			"a personal weakness of theirs. This can be "+
			"role-played by council, or have special "+
			"setups for the individuals.\n\n"+
		"- test succeed for <apprentice>\n\tPass the apprentice and "+
			"start the automatic ceremony of passage "+
			"where the apprentice is promoted to Full "+
			"wizard.\n\n"+
		"- test grant success for <apprentice>\n\tPass the apprentice "+
			"without going through all three stages of "+
			"the Test. Useful for quickly granting full "+
			"wizard status to someone when code or time "+
			"is not available.\n\n"+
		"- test failure with punishment for <apprentice>\n\tFail the "+
			"apprentice and start the ceremony. They "+
			"will be punished with 3 levels but may "+
			"take the Test after growing again.\n\n"+
		"- test failure with death for <apprentice>\n\tFail the "+
			"apprentice and have them killed in the "+
			"ceremony and punish them 3 levels.\n\n"+
		"- test failure with banishment for <apprentice>\n\tFail the "+
			"apprentice and banish them from the guild "+
			"and kill them. Only for such absolute utter "+
			"failures that the person has proven a lost "+
			"cause and is to never be granted full Wizard "+
			"status.\n");
	return 1;
      }

    if( !parse_command(str, ({ }), "%s 'for' %s", stage_st, player_st))
	return 0;

    player_st = lower_case(player_st);
    whom = find_player(player_st);

    NF("There is no apprentice member by that name in the lands.\n");

    if( !objectp(whom) || !THIS_GUILD(whom))
	return 0;

    NF("But that person isn't in the tower!\n");
    if( !E(whom) || !sscanf(file_name(E(whom)), WTOWER + "%s", gTmp))
	return 0;

    NF("But that person isn't an apprentice and can't be Tested!\n");
    if(ADMIN->query_member_type(whom) != TYPE_APPRENTICE)
	return 0;

    conclaves = INTERACTIVE_CON - ({ TP });

    NF("That option is not yet implimented.\n");
    switch(stage_st)
      {
      case "start":
      case "begin":
	{
	for(i = 0; i < sizeof(conclaves); i++)
	  {
		conclaves[i]->catch_tell("The very fabric of Magic crackles "+
			"as " + C(TP->query_real_name()) + " begins the "+
			"Test of " + C(whom->query_real_name()) + ".\n");
	  }
	write("The very fabric of Magic crackles as you begin the Test of "+
		C(whom->query_real_name()) + ".\n");
	set_alarm( 2.0, 0.0, &do_test_start(TP, whom));
	return 1;
	}
      case "battle":
	{


	break;
	}
      case "questioning":
	{

	break;
	}
      case "personal":
	{

	break;
	}
      case "failure with punishment":
	{

	break;
	}
      case "failure with death":
	{

	break;
	}
      case "failure with banishment":
	{

	break;
	}
      case "succeed":
	{
	
	break;
	}
      case "success given":
      case "grant success":
	{
	if(whom->query_prop(WOHS_TEST_CONTROL) != TO)
	  {
	    write("You have to start the Test before success can "+
		"be given!\n");
	    return 1;
	  }
	whom->add_prop(TEST_RESULT, TEST_SUCCESS_GIFT);
	ADMIN->endtest_seq(whom);
	write("You raise the " +short()+" aloft and with a loud voice "+
		"cry out to the spirits of Magic!\n");
	say(QCTNAME(TP) + " raises the " +short()+" aloft and cries out "+
		"with a loud, ringing voice!\n");
	return 1;
	}
      default:
	write("Type: test help\n");
	return 1;
      }
    return 0;
}

public void
do_test_start(object conclave, object apprentice)
{
    apprentice->add_prop(WOHS_TEST_CONTROL, TO);
    return;
}

public mixed
wield(object staff)
{
    if(!IS_CONCLAVE(RNAME(TP)))
      {
	/* Hurt them for 1/4 of their remaining HP */
	TP->heal_hp(-(TP->query_hp()/4));
	return "You grasp the " +short()+ " in your hands but recoil "+
	    "from a severe shock of energy!\n";
      }
    write("You grasp the " +short()+ " in both hands, appearing quite "+
	"an awesome figure.\n");
    say(QCTNAME(TP) + " grasps the " +short()+ " in both hands, appearing "+
	"quite an awesome figure.\n");
    return 1;
}

public void
force_unwield(object wielder)
{
    wielder->catch_tell("You lose your grip on the "+short()+" as you swing!\n");
    wielder->command("$unwield staff");
}

public varargs int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
    set_alarm(0.5, 0.0, &force_unwield(wielder));
    return 0;
}
