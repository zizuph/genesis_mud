/* Gully dwarf pigeon keeper in Kendermore, Gwyneth, June 1999 
 * 
 *
 * 2011-08-31: Fixed see_rat that printed a 0, Lunatari
 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
#define PLAYER_I_GOT_RAT "_player_i_got_rat"
string see_rat();

void
create_krynn_monster()
{
    set_name("mop");
    add_name("dwarf");
    set_living_name("mop");
    set_title("the Pigeon Keeper");
    set_introduce(1);
    set_race_name("gully dwarf");
    set_adj("small");
    add_adj("dirty");
    add_adj("gully");
    set_long("This is one of the dirtiest creatures you've ever seen! " +
        "His clothes are rags, and his hair looks as if the only time " +
        "it gets washed is when it rains. This gully dwarf is not very " +
        "bright, but he's very friendly.\n");
    set_gender(G_MALE);
    set_alignment(50);
    set_knight_prestige(-5);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(5);
    add_act("emote coos to his pigeons. He seems to love them very much.");
    add_act("emote scratches his dirty head.");
    add_act("emote mumbles: Where my rat go?");
    
    add_ask(" [about] 'rat'", "emote mumbles: Me have rat, want see " + 
        "rat?",1);
    add_ask(({"see", "see rat"}), see_rat); 
    add_ask(({"help", "task", "job", "quest"}), "emote mumbles: Me want my " + 
        "rat!",1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

/* Function name : See rat
 * Description : Gives a hint to questers that he wants his rat
 * Returns : Null
*/

string
see_rat()
{
    command("emote looks in his pockets, but comes up empty-handed.");
    set_alarm(1.0,0.0,"command","emote screams: Where my rat go?");
    set_alarm(2.0,0.0,"command","emote bursts into tears.");
    return "";
}

/* Function name : Calculate experience
 * Description : Gives experience to questers who successfully complete the
 *     Rat Quest, and haven't done so before. Sets the right quest bit. Logs
 *     the quest as being done by the player.
 * Returns : Null
*/
 
void
calculate_experience(object who)
{
    int xp_base = 1000;

    if(who->test_bit("ansalon",0,2))
    {
        who->catch_msg("You've already helped Mop!\n");
        return;
    }

    who->catch_msg("You feel a bit more experienced!\n");
    if(who->query_wiz_level())
    {
        who->catch_msg("xp : " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0,2);

    A_QUEST_LOG("quest", "Kendermore_Rat_Quest", who, xp_base);
    return;
}

/* Function name : Give rat
 * Description : Checks to see if quester got the quest item themselves
 *     and calls the calculate experience function for those who did.
 * Returns : Null
*/

void
give_rat(object from)
{
    string who;

    who = from->query_real_name();

    if(TP->query_prop(PLAYER_I_GOT_RAT))
    {
        command("dance " + who);
        command("shout Me have rat back! Me happy!");

        calculate_experience(from);
    }
    else
    {
        command("dance " + who);
        command("shout Me have rat back! Me happy!");
        command("emote forgets all about you.");
    } 
}

/* Function name : Give it back
 * Description : Let's questers know they didn't get the right item.
 * Returns : Null
*/

void
give_it_back(object ob, object from)
{
    command("emote mumbles: That not rat!");
    set_alarm(1.0,0.0,"command","sob");
}

/* Function name : Enter inventory
 * Description : Checks items entering the gully dwarf's inventory for
 *     the quest item.
 * Returns : Null
*/

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_d_rat_"))
    {
        set_alarm(1.0, 0.0, &give_rat(from));
        return;
    }

    if(ob->query_no_show())
        return;

    set_alarm(1.0,0.0, &give_it_back(ob, from));
    return;
}

