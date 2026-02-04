/*
    ailin.c
 
    This is an elven child named Ailin. He wanders the streets
        of Calathin and plays with his toys. He is cloned by
        CALATHIN_DIR + "square3_2.c"
    
    Created: 15 Sep 2003, by Bleys

    Modified: 16 Sep 2003, by Bleys
        - I had problems expressing him as a child in the short
            desc. If you set a short(), then that is used even
            after the kid introduces himself. So when a mortal
            looks in the room, he sees "Ailin," but when he
            sees an emote, he saw "The golden-haired boy smiles."
            At Cotillion's suggestion, I masked query_nonmet_name(),
            which solved that problem. 

*/

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";
inherit "/std/act/domove";

#include <ss_types.h>

// Globals
object toy;

// Prototypes
void add_introduced(string swho);

create_monster()
{
    // The master object doesn't need to be configured for interaction
    if (!IS_CLONE)
    {
        return;
    }

    set_name("ailin");
    set_living_name("ailin");
    set_race_name("elf");
    set_title("of the House of Sky");
    set_adj("young");
    set_adj("golden-haired");
    add_name("boy");
    // Using query_nonmet_name here because short() shows the introduced
    //   string ("This Ailin is overflowing...")
    set_long("This " + TO->query_nonmet_name() + " is overflowing " +
        "with youthful energy and the best features of elven childhood. " +
        capitalize(HE_SHE) + " has the innocent appearance " +
        "of a trusting child. You would expect " + HIM_HER + " to be at " +
        "home playing outdoors on a sunny day.\n");
    set_gender(0);

    default_config_npc(35);

    set_skill(SS_DEFENCE, 15);
    set_skill(SS_UNARM_COMBAT, 15);

    // Set up the movement parameters.
    set_random_move(20);
    set_restrain_path(CALATHIN_DIR);
    set_monster_home(CALATHIN_DIR + "square3_2");

    // Give him some personality.
    set_chat_time(3);
    add_chat("My friend Jonas can jump over the brook without getting wet.");
    add_chat("Have you ever seen a goblin?");
    add_chat("I dress myself.");
    add_chat("Ramil smells bad. I'm not allowed to talk to him.");
    
    set_act_time(2);
    add_act("smile all");
    add_act("spin top");
    add_act("wind top");
    add_act("jump youthfu");
    add_act("emote runs quickly from spot to spot, as if following an " +
        "unseen pattern.");
    // This one is for that old Terel flavor. I figure the elven
    //   houses of Terel have their own dialects.
    add_act("emote speaks in a language you don't understand.");

    // What kind of kid doesn't have a toy?
    toy = clone_object(CALATHIN_DIR + "obj/toy_top");
    toy->move(TO);

}


public string
query_nonmet_name()
{
    return("golden-haired young elven boy");
}


public void 
add_introduced(string s_who)
{
    object o_who = find_player(s_who);

    if ( o_who && !o_who->query_met(TO) )
    {
        set_alarm(itof(random(5) + 1), 0.0, "command",
            "introduce myself to " + s_who);
    }

}


