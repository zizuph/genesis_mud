/* Salamic, the good man sitting in prison */

#include "/d/Krynn/common/defs.h"

inherit M_FILE

#include "../local.h"
#include <macros.h>
#include <cmdparse.h>
#include QUESTH
#define QQNAME "major1"

/*prototype*/
void reward(object who);

void
create_krynn_monster()
{
    int i;

    set_name("salamic");
    set_living_name("salamic");
    set_long("Salamic is a good elf.\n" +
      "He is chained to the wall, it looks like he has been sitting\n" +
      "here quite some time.\n");
    add_item(({"chain", "chains"}), 
      "It's well built but has a small lock put into it.\n");
    add_item("lock", "It's made of bronze.\n");

    set_race_name("elf");
    set_adj("good");

    add_act(({"sigh", "say Why did they put me here, I never hurt anyone."}));
    add_act("say Do you think you can find the key to these chains?"); 
    add_act(({"moan", "say These chains hurts."}));
    add_act(({"scream", "blush", "say I thought you were the Dragon " +
	"Highlord, he often comes here."}));
    set_act_time(10);

    for (i = 0; i < 6; i++)
	set_base_stat(i, 7 + random(5));

    set_alignment(360);
    set_knight_prestige(-2);

    set_all_attack_unarmed(7, 6);
    set_all_hitloc_unarmed(2);

    ALWAYSKNOWN;

}

void
init_living() 
{
    ADA("unlock");
}

int
unlock(string str)
{
    string str1, str2, nm;
    object *obj;

    NF("Unlock what with what?\n");
    if (!str || (sscanf(str, "%s with %s", str1, str2) != 2))
	return 0;
    NF("unlock what?\n");
    if ((str1 != "chain") && (str1 != "chains") && (str1 != "lock"))
	return 0;
    NF("The hobgoblin guard eyes you suspiciously and you stop at once.\n");
    if (CAN_SEE(present("sal_guard", E(TO)), TP))
	return 0;
    if (present("sal_guard", E(TO)))
	TP->add_prop(PLAYER_I_HELP_SALAMIC, 
	  TP->query_prop(PLAYER_I_HELP_SALAMIC) | 4);
    NF("You don't have no " + str2 + ".\n");
    obj = FIND_STR_IN_OBJECT(str2, TP);
    if (!sizeof(obj))
	return 0;

    NF("The " + str2 + " doesn't fit.\n");
    if (obj[0]->query_key() != SALAMIC)
	return 0;
    nm = QUEST_DIR + QQNAME;
    nm->load_me();
    if (REALAGE(TP) <= nm->age())
    {
	write("You are just too nervous, accidentally break the key " +
	  "and fail to free Salamic!\n");
	obj[0]->remove_object();
	return 1;
    }
    reward(TP);
    write("The key crumbles to dust.\n");
    obj[0]->remove_object();
    set_alarm(0.5,0.0,"remove_object");
    return 1;
}

void
reward(object who)
{
    seteuid(getuid(TO));
    (QUEST_MASTER)->load_me();
    if ((QUEST_MASTER)->query_quest_number(MAJADV, who) > 0)
    {
	who->catch_msg("You unlock the chain from Salamic and " +
	  "he is once again a free man. Thanks for " +
	  "helping me again, he says.\n");
    }
    else /*if (QUEST_MASTER->query_quest_number(MAJADV, who) <= 0) */
    {
	who->catch_msg("You manage to unlock the chain from Salamic " +
	  "and he is once again a free man. 'Go back to " +
	  "my friend the Quest Master', says Salamic. 'I'm " +
	  "sure he will reward you, thank you my friend.'");
	(QUEST_MASTER)->inc_quest_number(MAJADV, who);
    }
    tell_room(E(TO), QCTNAME(who) + " unlocked the chain from Salamic the " +
      "good.\n", who);
    tell_room(E(TO), " At once Salamic is gone.\n");
}
