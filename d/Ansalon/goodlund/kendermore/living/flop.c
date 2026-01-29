/* Flop, a gully dwarf in Kendermore, Gwyneth June 14, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define PLAYER_I_GOT_STONE "_player_i_got_stone"
#define PLAYER_I_GOT_RAT "_player_i_got_rat"

void
create_krynn_monster()
{
    set_name("flop");
    add_name("dwarf");
    set_living_name("flop");
    set_title("the Flower Waterer");
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

    set_act_time(20);
    add_act("emote scratches his dirty head.");
    add_act("emote mumbles: Beautiful flowers, me water!");
    add_act("emote mumbles: Want see rat? It magic!");
    add_act("emote mumbles: Me see magic stone one time!");

    set_cact_time(20);
    add_cact("emote bursts into tears.");
    add_cact("emote mumbles: Me hurt! You bad!");

    set_default_answer(QCTNAME(TO) + " counts on his fingers. One, two. " + 
        "Two! He smiles proudly, showing big gaps in his teeth.\n");
    add_ask(" [about] 'rat'", "emote mumbles: Me have rat, want " + 
        "see rat?",1);
    add_ask(({"see", "see rat"}), "emote looks in his pockets, and pulls " + 
        "out a dead husk of a rat corpse. At least it doesn't smell too " + 
        "much anymore.",1); 
    add_ask(({"help", "task", "job", "quest"}), VBFC_ME("stone_hint"));
    add_ask(({"stone", "magic stone"}), "emote mumbles: It hidden, " + 
        "but me have map!",1);
    add_ask(({"hidden", "map"}), "emote shows you a rough and " +
        "torn map. All you can tell about it is that there is a roughly " + 
        "drawn water fountain near the X.",1); 
    add_ask("flowers", "emote mumbles: Me water flowers.",1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

/* Function name : Stone hint
 * Description : Gives a hint to questers
 * Returns : Null
*/

string
stone_hint()
{
    if(TP->test_bit("ansalon",0,2))
    {
        command("scratch head");
        command("emote mumbles: Me no need nothing.");
    }
    set_alarm(1.0,0.0, &command("emote mumbles: Me want magic stone!"));
    set_alarm(3.0,0.0, &command("emote mumbles: You find stone, me give " + 
        "nice gift!"));
    set_alarm(4.0,0.0, &command("emote pats his pocket with a grin."));
    return "";
}

/* Function name : Give stone
 * Description : Trades a dead rat for an iolite stone to questers who
 *     deserve it.
 * Returns : Null
*/

void
give_stone(object from)
{
    object rat;
    string who;

    who = from->query_real_name();

    if(TP->query_prop(PLAYER_I_GOT_STONE))
    {
        command("shout Stone, me get stone!");
        command("hug " + who);
        command("emote takes a dead rat from a pocket.");
        rat = clone_object(KOBJ + "rat");
        rat->move(TO);
        command("give rat to " + who);
        command("drop rat");
        command("emote skips away happily.");
        TP->add_prop(PLAYER_I_GOT_RAT, 1);
        remove_object(); 
    }
    else
    {
        command("shout Stone, me get stone!");
        command("hug " + who);
        command("emote skips away happily, forgetting to give you anything!");
        remove_object();
    }
}

/* Function name : Give it back
 * Description : Let's questers know they got the wrong item.
 * Returns : Null
*/

void
give_it_back(object ob, object from)
{
    command("frown");
    command("emote mumbles: That not pretty magic stone!");
}

/* Function name : Enter inventory
 * Description : Checks items entering the gully dwarf's inventory for 
 *     a quest item. 
 * Returns : Null
*/

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_m_stone_"))
    {
        set_alarm(1.0,0.0, &give_stone(from));
        return;
    }

    if(ob->query_no_show())
        return;

    set_alarm(1.0,0.0, &give_it_back(ob, from));
        return;
}

