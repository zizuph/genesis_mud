inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_monster()
{
    ::create_monster();
    set_name("horse");
    set_adj("old");
    add_adj("gassy");
    set_short("old gassy horse");
    set_long("This is an old horse with grey fur. Its black tail "+
    "swings leisurly back and forth as it munches on its oats. "+
    "You can see that it really has no more strength in its legs.\n");
    set_act_time(6);
    add_act("fart");
    add_act("emote grunts.");
    add_act("emote whines.");
    add_act("emote chews some oats.");
    add_act("burp");
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
}

void
init_living()
{
    ::init_living();
    AA(do_kick,kick);
}

int
do_kick(string str)
{
    NF("Kick the ass of whom?\n");
    if(str == "horse" || str == "the ass of the horse")
    {
        write("You kick the ass of the horse with your foot!\n");
        say(QCTNAME(TP)+" kicks the ass of the horse with "+HIS(TP)+
        " foot!\n");
        command("emote yelps.");
        tell_room(E(TO),"A large piece of crap plops out of its "+
        "ass.\n");
        seteuid(getuid());
        clone_object("/d/Kalad/common/guilds/shadow_walkers/horse_crap")->move(E(TO));
        return 1;
    }
    return 0;
}

