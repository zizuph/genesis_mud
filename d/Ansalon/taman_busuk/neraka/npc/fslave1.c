/* Ashlar, 13 Jul 97 - a slave */
/* Navarre 24th June 2006, added remove_object to slave if you free her
 * after having solved the quest. Earlier she just kept standing there.
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define Q_GROUP 0
#define Q_BIT   14

int freed = 0;

void
create_krynn_monster()
{

	set_name("slave");
    add_name("neraka_slave");
    set_race_name("human");
    set_adj("young");
    set_gender(1);
    set_short("young female slave");
    set_long("The young slave girl wears an iron collar that chains " +
        "her to the wall. She is dirty, and her long brown hair is " +
        "unkempt. She cowers in a corner of the stone hut, trembling " +
        "in fear.\n");

    set_stats(({12,20,14,16,16,15}));

    set_alignment(350);
    set_knight_prestige(-20);

    set_all_attack_unarmed(15,20);
    set_all_hitloc_unarmed(5);

}

void
thank_and_reward(object pl)
{
    int reward;

    if (pl->test_bit("ansalon", Q_GROUP, Q_BIT))
    {
        command("thank " + pl->query_real_name());
        command("say I'm just sorry I have no reward for you..");
        command("emote sneaks out of the hut.");
        pl->catch_msg("Nice job, but you will only be rewarded once for " +
        "the quest.\n");
        remove_object();
        return;
    }

    command("thank " + pl->query_real_name());
    command("say Finally free.. Now I must hurry away. Thank you, once more.");
    command("emote sneaks out of the hut.");

    reward = 8000;
    if (pl->query_prop(NERAKA_I_KILLED_KORDHEK) != 1)
    {
        reward -= 500;
    }
    if (!pl->query_prop(NERAKA_I_KILLED_KORDHEK))
    {
        reward -= 2000;
    }

    if (!pl->query_prop(NERAKA_I_FOUND_THE_SLAVE_KEY))
    {
        reward -= 4500;
    }

    /* Make sure we do not give more than the player has */
    if (reward > pl->query_exp())
        reward = pl->query_exp();

    pl->catch_msg("You feel more experienced!\n");
    if (pl->query_wiz_level())
    {
        pl->catch_msg("xp: " + reward + "\n");
    }

    /* Add the reward and set the bit */
    pl->add_exp(reward, 0);
    pl->set_bit(Q_GROUP, Q_BIT);

    /* And make sure we log it */
    A_QUEST_LOG("quest", "Free Slave Girl", pl, reward);

    remove_object();
}

void
freed_by(object pl)
{
    set_alarm(1.0,0.0,&thank_and_reward(pl));
}
