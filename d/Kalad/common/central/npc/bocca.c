inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>
void
/* by Korat */
create_monster()
{
    ::create_monster();
    set_name("bocca");
    add_name("council lord");
    set_race_name("human");
    set_adj("bored");
    add_adj("arrogant");
    set_long("This arrogant man seems to be bored of his power as the Lord of the "+
        "city council. Dressed in his decorated robe, the silver threads seems "+
        "be reflected in his eyes as thin glittering lines, giving him a "+
        "hypnotic look...It is like he knows your thoughts.\n");
    set_stats(({100,150,100,90,100,100}));
    set_alignment(-100);
    set_knight_prestige(200);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_PARRY,60);
    set_skill(SS_AWARENESS,80);
    set_act_time(3);
    add_act("emote gets a wishful expression in his eyes as he stares out the "+
        "window and lets his eyes linger on the Citadel.");
    add_act("emote twists a ring around with a wishful expression "+
        "in his face.");
    add_act(({"say What can I do for you...and what can you pay?","cackle"}));
    add_act("emote gets a troubled look as he mutters something about "+
        "unreliable carrier pigeons.");
    add_act(({"hmm","say I have work to do. Your time is up. "+
                "Leave...","point east"}));
    add_act("yawn");
    add_act("emote mumbles something about his town being swarmed with creeps.");
    add_act(({"emote looks out the window.","say a hobbit! In my town...","smirk"}));
    add_act("emote strokes his robe with a smile on his face.");
    add_act(({"grumble","say Are you here to pay taxes?"}));
    set_cact_time(1);
    add_cact("say How dare you to attack me!");
    add_cact("shout Guards! Kill them!");
    add_cact("say Ahh finally some fun. But don't spill any of your blood on "+
        "my robe!\n");
    set_title("the Lord of the City Council");
    add_speak("An interesting story that. But it still bores me.\n");
    add_ask("lord","The bored arrogant human says: "+
        "Yes, I am the Lord of this cit..ehmm the "+
        "City Council.\n");
    add_ask("high lord","The bored arrogant human says: "+
        "The High Lord?? I deeply respect him and his decisions! "+
        "He has my undying loyalty, and any wish he has is my command. "+
        "My power is his to use...\n");
    set_default_answer("The Lord says: Don't bore me with questions. I have "+
        "employees to answer them.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}

void
arm_me()
{
    int i;
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/central/arm/bocca_robe");
    arm -> move(TO);
    for (i=0; i<3; i++)
    {
        arm = clone_object("/d/Kalad/common/central/arm/bocca_ring");
        arm -> move(TO);
    }
    command("wear all");
    wep = clone_object("/d/Kalad/common/central/wep/bocca_knife");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_GC(random(10))->move(TO,1);
}
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
    if (random(5))
        return 0;
    hitresult = enemy->hit_me(400 + random(400), W_SLASH, me, -1);
    how = " barely scratched";
    if (hitresult[0] > 0)
        how == "";
    if (hitresult[0] > 10)
        how = " bleeding somewhat when hit";
    if (hitresult[0] > 20)
        how = " bleeding profousely when hit hard";
    if (hitresult[0] > 30)
        how = " hit extremely hard";
    if (hitresult[0] > 40)
        how = " crushed, with flesh and blood splattering around when hit";
    me -> catch_msg("You hit the throat of your enemy!\n"+
        capitalize(enemy->query_pronoun()) + " is"+
        how + " by the sharp rings.\n");
    enemy->catch_msg(QCTNAME(me) + " hits you in the throat with his hand!\n"+
        "You are"+ how + " by the sharp rings.\n");
    tell_watcher(QCTNAME(me) + " hits " + QTNAME(enemy) + "!\n"+
        capitalize(enemy->query_pronoun()) + " is" +
        how + " by the sharp rings.\n", enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1;
}
