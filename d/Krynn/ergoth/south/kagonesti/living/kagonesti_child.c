#include <ss_types.h>
#include <macros.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit M_FILE

nomask public void create_krynn_monster()
{
    setuid();
    seteuid(getuid());

    set_race_name("wilder elf child");
    add_name("wilder elf");
    add_name("elf");
    add_name("child");
    add_name("_kagonesti_child_");
    set_adj("small");
    set_gender(random(2));
    set_alignment(random(400));
    set_height_desc("short");
    set_whimpy(99);
    set_stats(({10,11,10,6,6,8}), 25);
    set_skill(SS_DEFENCE,       15);
    set_skill(SS_WEP_POLEARM,   15);
    set_skill(SS_WEP_SWORD,     15);
    set_skill(SS_WEP_MISSILE,	15);
    set_skill(SS_AWARENESS,     15);
    set_skill(SS_UNARM_COMBAT,	10);
    set_skill(SS_BLIND_COMBAT,	10);
    set_skill(SS_2H_COMBAT,     10);
    set_skill(SS_LOC_SENSE,     15);
    set_skill(SS_HIDE,          15);
    set_skill(SS_SNEAK,         15);
    set_skill(SS_TRACKING,      15);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    set_default_answer("The wilder elf child doesn't seem to understand your "
        + "question, nor seems very interested in talking to an outsider.\n");
    set_act_time(10);
    add_act("giggle .");
    add_act("emote fires an imaginary bow into an invisible creature.");
    add_act("emote sighs to let everyone know he is bored.");
    add_act("bounce");
    add_act("pace dramatically");
    add_act("rolleyes . ");
    add_act("whine loudly");
   
    set_cact_time(5);
    add_cact("cry");
    add_cact("emote begs for " + HIS(this_object()) + " life.");
    add_cact("emote wails in despair.");
    
    set_knight_prestige(-6);
}

string generate_insult()
{
    return one_of_list(({"vile", "putrid", "demented", "wretched", "foul"}))
        + " " + one_of_list(({"excretion", "cretin", "derelict", "vermin"}));
}

public void attacked_by(object ob)
{
    int noshout = 0;
    int error;
    
    if(!this_object()->query_relaxed_from_combat())
        noshout = 1;
    
    ::attacked_by(ob);
    
    if(!noshout)
    {
        this_object()->command("scream");
        foreach(string room : environment(this_object())->query_exit_rooms())
        {
            if(LOAD_ERR(room))
            {
                tell_room(this_object(), "There is a rift in the fabric of "
                    + "time and space. Please write a bug report for this "
                    + "room, and mention that " + room + " is responsible.\n",
                    0, this_object());
                    break;
            }

            foreach(object obj : filter(all_inventory(find_object(room)),
                &->id("_kagonesti_elf_")))
                if(!obj->query_attack())
                    obj->move_living("running toward the scream",
                        environment(this_object()));
        }

        foreach(object obj : filter(all_inventory(environment(this_object())),
            &->id("_kagonesti_elf_")))
        {
            switch(random(4))
            {
                case 0:
                    obj->command("rsay " + capitalize(HE(this_object()))
                        + " is just a child you " + generate_insult() + "!");
                    break;
                case 1:
                    obj->command("explode");
                    break;
                case 2:
                    obj->command("scowl furiously");
                    break;
                case 3:
                    obj->command("emote 's eyes burn with rage.");
                    break;
                default:
                    break;
            }

            obj->command("$kill " +
                OB_NAME(this_object()->query_attack()));
        }
    }
}

public void run_away()
{
    ::run_away();
    this_object()->command("hide");
}

public int query_option(int opt)
{
    if(opt == OPT_NO_FIGHTS)
        return 1;
    else
        return ::query_option(opt);
}
