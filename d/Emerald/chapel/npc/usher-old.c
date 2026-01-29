/* chapel/npc/usher.c is cloned by chapel/chapel.c */
inherit "/std/monster";
 
#include "../chapel.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
 
#define EXIT    CHAPEL_DIR + "outside"

/* Prototypes */
int not_allowed(string arg);
int kill(string str);

 
create_monster()
{ 
    set_name("usher");
    set_adj("big");
    add_adj("large");
    set_race_name("human");
    set_short("large usher");
    set_long("This usher is here to make sure that "+
       "there is no interruptions during the ceremony.\n");
 
    set_stats(({ 150, 150, 150, 150, 150, 150 }));
 
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
 
    set_hp(query_max_hp());
 
    set_alignment(50);
 
    add_prop(OBJ_I_WEIGHT, 91000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
}
 
void
arm_me()
{
    clone_object(CHAPEL_DIR + "arm/tux")->move(TO,1);
    clone_object(CHAPEL_DIR + "wep/shatter")->move(TO,1);
    command("wear all");
}
 
void
attacked_by(object ob)
{
    object *ushers;
    int    i;
 
    seteuid(getuid());
 
    command("wield sword");
 
    ::attacked_by(ob);
 
    ushers = FILTER_OTHER_LIVE(all_inventory(environment()));
 
    for (i=0 ; i<sizeof(ushers) ; i++)
        if (ushers[i]->id("usher"))
            ushers[i]->help_me(ob);
}
 
void
help_me(object ob)
{
    command("wield sword");
    attack_object(ob);
}
 
void
init_living()
{
    ::init_living();    
    add_action(kill, "kill");
    add_action(not_allowed, "shout");
    add_action(not_allowed, "scream");
    add_action(not_allowed, "puke");
    add_action(not_allowed, "burp");
    add_action(not_allowed, "finger");
    add_action(not_allowed, "ack");
    add_action(not_allowed, "choke");
    add_action(not_allowed, "complain");
    add_action(not_allowed, "confuse");
    add_action(not_allowed, "confused");
    add_action(not_allowed, "cough");
    add_action(not_allowed, "cringe");
    add_action(not_allowed, "despair");
    add_action(not_allowed, "duh");
    add_action(not_allowed, "eeks");
    add_action(not_allowed, "explode");
    add_action(not_allowed, "fart");
    add_action(not_allowed, "fume");
    add_action(not_allowed, "grope");
    add_action(not_allowed, "growl");
    add_action(not_allowed, "hiccup");
    add_action(not_allowed, "jump");
    add_action(not_allowed, "kick");
    add_action(not_allowed, "knee");
    add_action(not_allowed, "moan");
    add_action(not_allowed, "oops");
    add_action(not_allowed, "poke");
    add_action(not_allowed, "pout");
    add_action(not_allowed, "shiver");
    add_action(not_allowed, "slap");
    add_action(not_allowed, "snap");
    add_action(not_allowed, "snarl");
    add_action(not_allowed, "smirk");
    add_action(not_allowed, "snore");
    add_action(not_allowed, "spit");
    add_action(not_allowed, "startle");
    add_action(not_allowed, "steam");
    add_action(not_allowed, "stomp");
    add_action(not_allowed, "stretch");
    add_action(not_allowed, "sulk");
    add_action(not_allowed, "swear");
    add_action(not_allowed, "tackle");
    add_action(not_allowed, "tickle");
    add_action(not_allowed, "twiddle");
    add_action(not_allowed, "whine");
    add_action(not_allowed, "whistle");
    add_action(not_allowed, "wiggle");
    add_action(not_allowed, "yawn");
    add_action(not_allowed, "yodel");
}
 
void
throw_out(object ob)
{
    int times;
 
    times = ob->query_prop(THROWN_OUT);
    ob->add_prop(THROWN_OUT, times + 1);
    ob->catch_msg("You are ejected from the chapel by the usher.\n");
    tell_room(EXIT, QCTNAME(ob) + " is thrown out of the chapel by an usher!\n");
    ob->move_living("M", EXIT);
    tell_room(environment(), QCTNAME(ob) + " is thrown out of the chapel!\n");
}
 
int
kill(string str)
 {
    if(str!="usher" && str!="large usher") {
        throw_out(this_player());
        return 1;
    }
    return 0;
}
 
int
not_allowed(string str)
{
    throw_out(this_player());
    return 1;
}
