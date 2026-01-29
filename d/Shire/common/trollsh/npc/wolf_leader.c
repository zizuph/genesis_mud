inherit "/d/Shire/common/trollsh/npc/wolf_team";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <options.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/lib/evilkill.h"
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#define WOLF_HOME "/d/Shire/common/trollsh/shaws16"
#define WOLFLOOK ({ "massive", "swarthy", "strong", "eerie" })

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

object wolf;

create_creature()
{
    seteuid(getuid());
    if (!IS_CLONE)
        return;
    create_random_wolf(random(4));
}

create_random_wolf(int i)
{
    set_name("wolf");
    set_pname("wolves");
    set_race_name("wolf");
    set_adj(WOLFLOOK[i]);
    set_short(WOLFLOOK[i] + " wolf");
    set_pshort("black wolves");
    set_gender(G_NEUTER);
    set_long(
    	"This looks like a wolf that has been wandering a lot. It is thin, yet "
    	+"it looks strong. It has cruel, yellow eyes, and thick, black fur.\n");
    
    set_stats(({ 65+random(11), 40+random(21), 63, 58, 69, 73}));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(-75-random(51));
    add_leftover("/d/Khalakhor/common/obj/leftover/skin",
                 "skin",1,"",1,1);
        
    set_aggressive(1);
    set_attack_chance(80);
    
    wolf->set_restrain_path(({ "shaws12", "shaws11","shaws9", "shaws7", "shaws8", 
    			"shaws13", "shaws14", "shaws15", "shaws16", "shaws17", 
    			"shaws18", "shaws19", "shaws20", "shaws21", "shaws22", 
    			"shaws23", "shaws24", "shaws25" }));
    set_monster_home(WOLF_HOME);
    set_random_move(random(6)); 
    
    set_skill(SS_DEFENCE, 35+random(11));
    set_attack_unarmed(A_BITE, 35, 30, W_IMPALE, 60, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 28, W_SLASH, 20, "left claw");
    set_attack_unarmed(A_RCLAW, 20, 28, W_SLASH, 20, "right claw");
    
    set_hitloc_unarmed(H_HEAD, ({ 20, 25, 20, 30 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 20, 30, 25, 20 }), 80, "body");

    set_act_time(4);
    add_act("emote snarls savagly.");
    add_act("emote howls eerily.");
    add_act("emote sniffs the air.");
    add_act("emote smells blood in the air....");
}

static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;
    
    me = TO;
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD))
            ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    
    me = TO;
    if(random(10))
        return 0;
        
    hitresult = enemy->hit_me(30+random(50), W_IMPALE, me, -1);
    how = " without effect";
    if (hitresult[0] > 20)
        how = " very hard";
    if (hitresult[0] > 10)
        how = " hard";
    if (hitresult[0] > 0)
        how = " but barely scratched";
        
    me->catch_msg("You leap for your opponents throat!\n" +
        CAP(enemy->query_pronoun()) + " is hit" + 
        how + ".\n");
    
    enemy->catch_msg(QCTNAME(me) + " leaps onto your throat!\n" +
    	"You are hit" + how + ".\n");
    
    tell_watcher(QCTNAME(me)+" leaps onto "+QCTNAME(enemy)+"!\n"+
    	CAP(enemy->query_pronoun())+" is hit"+ how+".\n", enemy);
    
    if(enemy->query_hp() <= 0)
        enemy->do_die(me);
        
    return 1;
}
