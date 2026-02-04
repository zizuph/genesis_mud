/*
 * goblet.c
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>

#include "/d/Terel/include/quest_bits.h"
#include "/d/Terel/LoD/dungeon/quest.h"

#define MAX_FILLS   10
#define HEAL_AMOUNT 50
#define SHADOW      (LOD_DIR + "obj/goblet_shadow")

int nfills = 0, a_id = 0, too_quick = 0;
string solver = "";
object shadow;

public int
check_solver(object ob)
{
    if (!ob)
        return 0;
    
    if (ob->query_real_name() != solver)
        return 0;
    
    /* We assume that all NPC's have solved the quest */
    if (ob->test_bit("Terel", QUEST_DUNGEON_GROUP, QUEST_DUNGEON_BIT) ||
        ob->query_npc())
        return 1;
    
     return 0;   
}

/*
 * Function name: query_auto_load
 * Description:   Make this object autoloading
 * Returns:       The filename of this object
 */
public string
query_auto_load()
{
    if (ETO && living(ETO) && check_solver(ETO))
        return MASTER + ":" + nfills + "##" + solver;
    else
        return "";
}

/*
 * Function name: init_arg
 * Description:   Called when autoloading
 */
public void
init_arg(string arg)
{
    sscanf(arg, "%d##%s", nfills, solver);
}

public void
set_solver(mixed who)
{
    if (objectp(who))
        solver = who->query_real_name();
    else if (stringp(who))
        solver = who;
}

public string
query_solver()
{
    return solver;
}

public void
create_object()
{
    set_name("goblet");
    add_name(DQ_GOBLET);
    set_adj(({"small", "golden"}));
    
    set_long("A goblet made of pure gold. @@my_long@@\n");
    
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 690 + random(50));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_S_WIZINFO, "This is the treasure of the LoD dungeon quest. " +
                            "It can be filled with " + MAX_FILLS + " " +
                            "mouthfulls of healing water from the pool " +
                            "behind the three-headed hydra. Each mouthfull " +
                            "represent " + HEAL_AMOUNT + " of hp. " +
                            "One cannot drink while fighting and it's " +
                            "very difficult to get past the hydra to " +
                            "refill it. The object is autoloading. " +
                            "It uses a special shadow to check if the " +
                            "players dies, since then the goblet is " +
                            "lost forever.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"This is Sawoq's golden goblet. It can be filled with " +
          "the sparkling waters.\n", 20,
          "This magic water will heal you, unless you drink too much " +
          "of it.\n", 35,
          "You will lose it forever when you die.\n", 45,
          "Beware, the one who kills you might be able to use it.\n", 70}));
}

public string
my_long()
{
    switch ((10*nfills)/MAX_FILLS) {
        case 0: return "It is empty.";
        case 1: return "There is only one mouthful of water left at the bottom.";
        case 2: return "It is almost empty.";
        case 3: return "There is a quarter of water left.";
        case 4: return "It is almost half-full with water.";
        case 5: return "It is half-full with water.";
        case 6: return "It is slightly more than half-full with water";
        case 7: return "It contains about three quarters of water.";
        case 8: return "It contains quite a lot of water.";
        case 9: return "It is filled with water almost to the brim.";
        case 10: return "It is filled with water to the brim.";
        default: return "It is buggy.";
    }
}

public int
fill_it_with_water(object who)
{
    if (!check_solver(who))
        return 0;
    
    if (nfills >= MAX_FILLS)
        return 2;
        
    nfills = MAX_FILLS;
    return 1;
}

public void
do_heal(object who)
{
    int heal;
    
    a_id = 0;
    
    if (!who)
        return;
        
    if (too_quick) {
        too_quick = 0;
        who->catch_msg("The water you drank had a bitter taste. " +
                       "Maybe you drank too much of it?\n");
        who->heal_hp(-HEAL_AMOUNT);
        if (who->query_hp() < 0)
            who->do_die(TO);
        return;
    }
    
    heal = who->query_max_hp() - who->query_hp();
    if (heal) {
        if (heal > HEAL_AMOUNT)
            heal = HEAL_AMOUNT;
        who->catch_msg("The water feels very refreshing and " +
                       "good for your health.\n");
        who->heal_hp(heal);
    } else
        who->catch_msg("The water feels refreshing.\n");
}

public int
do_drink(string str)
{
    object ob;
    
    if (!str)
        return 0;
        
    if (!parse_command(str, all_inventory(TP), "[water] [from] %o", ob))
        return 0;
        
    if (ob != TO)
        return 0;
        
    if (TP->query_attack()) {
        write("You are too busy with other things to even " +
              "think about it!\n");
        return 1;
    }
        
    if (!nfills) {
        write("You cannot do that. The " + short() + " is empty.\n");
        return 1;
    }
    
    write("You drink some water from your " + short() + ".\n");
    say(QCTNAME(TP) + " drinks from " + TP->query_possessive() + " " +
        short() + " .\n");
        
    if (a_id)
        too_quick = 1;
    else
        a_id = set_alarm(itof(4 + random(4)), 0.0, &do_heal(TP));
    
    nfills--;        
        
    return 1;
}

public void
init()
{
    ::init();
    if (ETO == TP)
        add_action(do_drink, "drink");
}

public void
empty_me(object who)
{
    if (who && nfills) {
        who->catch_msg("You cannot hold the " + short() +
                       " steadily and you pour water all over you!\n");
        tell_room(ENV(who), QCTNAME(who) + " pours water from " + 
                  LANG_ASHORT(TO) + " all over " + who->query_objective() +
                  ".\n", who);
    }
        
    nfills = 0;
}

public void
rem_ob(object ob)
{
    if (ob) {
        if (ENV(ob) && living(ENV(ob)))
            ENV(ob)->catch_msg("The " + ob->short() + " disintegrates.\n");
        ob->remove_object();
    }
}

public void
enter_env(object new, object old)
{
    object *all;
    int i;
    
    ::enter_env(new, old);
    
    if (!new || !living(new))
        return;
    
    if (new->query_npc() && new->query_real_name() == "sawoq")
    {
        set_solver(new);
        fill_it_with_water(new);
    }
    
    if (!check_solver(new)) 
        set_alarm(1.0, 0.0, &empty_me(new));
    else
    {
        all = all_inventory(new) - ({ TO });
        for (i=0; i<sizeof(all); i++)
        {
            if (MASTER_OB(all[i]) == MASTER)
            {
                set_alarm(1.0, 0.0, &rem_ob(TO));
                return;
            }
        }
        if (!query_prop(OBJ_M_NO_SELL))
            add_prop(OBJ_M_NO_SELL, 1);
        if (!shadow)
        {
            FIX_EUID;
            shadow = clone_object(SHADOW);
            if (shadow->shadow_me(new))
                shadow->set_goblet(TO);
            else
                shadow->remove_shadow();
        }
    }
}

public void
leave_env(object old, object new)
{
    ::leave_env(old, new);
    
    if (!old || !living(old))
        return;
    
    if (query_prop(OBJ_M_NO_SELL))
        remove_prop(OBJ_M_NO_SELL);
}

public void
solver_died(object who, object killer)
{
    if (who->query_real_name() == solver) {
        solver = "";
        if (shadow)
            shadow->remove_shadow();
        if (killer && living(killer))
            set_solver(killer);
    }
}
