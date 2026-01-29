/* Dragon by percy*/

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <const.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/xak/xlocal.h"


inherit C_FILE
inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

int darkness;
object darkobj;
object *attackers;

void
create_creature()
{
    int i;

    set_name("khisanth");
    set_short("black dragon");
    set_race_name("dragon");
    set_long("A fearsome black dragon of legends. It looks very powerful and very evil..\n");
    set_adj("black");
    set_gender(G_FEMALE);
    for (i = 0; i < 6; i++)
        set_base_stat(i, 60 + random(20));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 20);

    set_alignment(-600);
    set_knight_prestige(900);

    set_attack_unarmed(0, 35, 25, W_IMPALE, 50, "bite");
    set_attack_unarmed(1, 35, 20, W_BLUDGEON, 20, "wing");
    set_attack_unarmed(2, 35, 20, W_SLASH, 30, "claw");

    set_hitloc_unarmed(0, 20, 10, "head");
    set_hitloc_unarmed(1, 20, 60, "body");
    set_hitloc_unarmed(2, 20, 30, "tail");
    /*add_leftover("/d/Roke/common/carisca/obj/skin","skin",1,"",1,1);*/
    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_option(OPT_BLOOD) == 0)
            ob[i]->catch_msg(str);
}

void
second_life(object killer)
{
    int prp = killer->query_prop("_player_i_black_dragon_quest");
    killer->add_prop("_player_i_black_dragon_quest",prp | 2);

    call_other(DDIR + "cavern.c", "spuddles");
    tell_room(environment(this_object()), "Khisanth dies leaving behind several puddles of acid.\n");
    return 0;
}


int
special_attack(object enemy)
{

    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = this_object();

    attacktype = random(10);
    if (attacktype == 1)
    {
        say(BS("You hear a sharp intake of breath and then a devastating"
            + " stream of acid flows from the dragons mouth at you!", 70));

        ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });

        for (i = 0; i < sizeof(ob); i++)
        {
            penet = 50 + random(50);
            penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_ACID) / 100;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

            how = "just scathed";
            if (hitresult[0] > 0)                  
                how == "barely burned";
            if (hitresult[0] > 10)
                how = "slightly burned";
            if (hitresult[0] > 20)
                how = "burned quite badly";
            if (hitresult[0] > 40)
                how = "burned very badly";
            if (hitresult[0] > 60)
                how = "utterly devastated";

            ob[i]->catch_msg("You were " + how + " by the dragon breath!\n");
            tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the dragon breath!\n", ob[i]);


            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        return 1;
    }

    if (attacktype == 2)
    {
        if (present("lightobj", this_object()))
            return 0;
        say(BS("The dragon mumbles a few words and casts a darkness spell!", 70));
        darkobj = clone_object(OBJ + "darkobj");
        darkobj->set_duration(30);
        darkobj->move(TO);
        return 1;
    }

    return 0;
}


int
solamnian_knight(object who)
{
    if (who->test_bit("krynn", 1, 0))
        return 1;

    if (who->test_bit("krynn", 1, 1))
        return 1;

    if (who->test_bit("krynn", 1, 2))
        return 1;

    return 0;
}


void 
react_to_token(object who)
{
    string victim;
    int    prp = who->query_prop("_player_i_black_dragon_quest");

    if (solamnian_knight(who))
    {
        victim = who->query_real_name();

        command("glare evil " + victim);
        command("say A worshipper of Paladine!");
        command("say You will meet your God sooner than you think.");
        command("kill " + victim);

        return;
    }

    if ((REALAGE(who) < 691200) || (who->query_alignment() > 100))
    {
        command("growl");
        command("say His Lordship would never have trusted someone "
          + "like you with this medallion.");
        command("say I suggest you leave now.");
        command("emote inhales deeply.");

        return;
    }

    who->add_prop("_player_i_black_dragon_quest", prp | 2);

    command("growl");
    command("say What is this ?");
    command("emote glares at the medallion.");
    command("say Does he not trust me to keep the Disks safe ?");
    command("emote inhales deeply.");
    command("emote spouts forth a cloud of acid vapors, leaving "
      + "behind several puddles of acid on the ground.");
    call_other(DDIR + "cavern.c", "spuddles");
    command("fume");
    command("say Very well, I assume his Lordship is right.");
    command("say The Disks of Mishakal are your responsibilty now.");
    command("say Be gone from here when I return.");
    command("emote turns and leaves the cave.");

    remove_object();
}


void
return_it(string what)
{
    command("say I have no need for this!");
    command("drop " + what);

    return;
}


void
enter_inv(object ob, object from)
{
    string what = ob->query_name();

    ::enter_inv(ob, from);

    if (ob->id("_krynn_magic_darkness_"))
    {
        return;
    }

    if (ob->id("_krynn_evil_disks_token_"))
    {
        set_alarm(1.0, 0.0, &react_to_token(from));
        return;
    }

    set_alarm(1.0, 0.0, &return_it(what));
}









