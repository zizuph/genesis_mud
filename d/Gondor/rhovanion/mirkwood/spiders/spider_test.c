#include "../defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#define FANG   1
#define LEGS_B 2
#define LEGS_I 4

#define HEAD  1
#define BODY  2
#define LEGS  4

int special_attack_chance = 50; // Percentage
object victim; // Focus of our attacks
object last_target; // Target we attacked last
object origin_nest; // Nest that spawned us

string restrain_path;
object spider_home;
int removal_alarm = -1;
int target_check_alarm = -1;

string physlook();
string emotelook();
string longlook();

public void set_armour_modifier(float modifier);
public void set_attack_modifier(float modifier);
void notify_lost_target(object target);

void
create_creature()
{
    set_race_name("spider");
    add_name(MIRKWOOD_SPIDER_ID);

    set_adj(({emotelook(),physlook()}));

    set_long(({longlook()}));

    set_stats(({ 30, 30, 30, 30, 30, 30}));

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_FEAR, 1);

    set_armour_modifier(1.0);
    set_attack_modifier(1.0);
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"big", "hulking", "yellow-spotted", "green-spotted",
        "hairy", "red-eyed", "fat", "massive", "blue-spotted", "black",
        "red-striped", "white-striped", "long-fanged", "sharp-fanged",
        "beady-eyed", "black-eyed", "yellow", "brown", "grotesque", "sleek",
        "orange-spotted", "orange-striped", "grey", "green-eyed", "yellow-eyed",
        "hairy-legged", "long-legged", "white-backed","dead-eyed", "orange-backed"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"angry", "venemous", "hungry", "bloodthirsty",
        "vicious", "ravenous", "mean", "cruel", "deadly", "dangerous",
        "demonic", "poisonous", "devilish", "evil", "ferocious", "fierce",
        "strong", "ghastly", "ghostly", "chittering", "insane", "mad",
        "mean", "murderous", "nasty", "hissing", "vindictive", "raging",
        "savage", "sinister", "terrifying", "wicked", "abhorrent", "watchful",
        "hateful", "hate-filled", "screaming", "silent", "gruesome"});
    return emotelooks[random(sizeof(emotelooks))];
}

string
longlook()
{
    string *longlooks;
    longlooks = ({"This spinder looks both angry and hungry.\n",
        "This deadly looking spider is searching for a victim, perhaps you?\n"});
    return longlooks[random(sizeof(longlooks))];
}    

public void
set_victim(object focus_victim)
{
    victim = focus_victim;
}

public object
query_victim()
{
    return victim;
}

public void
setup_stats(int con)
{
    set_stats(({ con, con, con, con / 2, con / 2, con }), 10);
    refresh_living();
}

public void
set_armour_modifier(float modifier)
{
    int ac = ftoi(40.0 * modifier);

    set_hitloc_unarmed(HEAD, ac, 10, "head");
    set_hitloc_unarmed(BODY, ac, 50, "body");
    set_hitloc_unarmed(LEGS, ac, 30, "legs");
}

public void
set_attack_modifier(float modifier)
{
    int attack = ftoi(40.0 * modifier);

    set_attack_unarmed(FANG,   attack, attack, W_IMPALE,   50, "fangs");
    set_attack_unarmed(LEGS_B, attack, attack, W_BLUDGEON, 25, "legs");
    set_attack_unarmed(LEGS_I, attack, attack, W_IMPALE,   25, "legs");
}

public void
set_special_attack_chance(int percentage)
{
    special_attack_chance = percentage;
}

public int
special_attack(object victim)
{
    if (random(100) < special_attack_chance)
    {
        mixed result = do_stat_based_attack(this_object(), victim, W_IMPALE);
        if (result ==  ({ -1, -1, -1, -1, -1 })) 
        {
            this_object()->tell_watcher(QCTNAME(this_object()) + " misses " 
                + QTNAME(victim) + " with " + this_object()->query_possessive()
                + " special.\n");
        } 
        else if (pointerp(result)) 
        {
            this_object()->tell_watcher(QCTNAME(this_object()) + " hits " 
                + QTNAME(victim) + " with " + this_object()->query_possessive()
                + " special.\n");
        }

        return 1;
    }
}

void
attack_focus_target()
{
    if (query_attack() == victim) return;

    if (present(victim, environment(this_object())))
    {
        tell_room(environment(this_object()), QCTNAME(this_object())
            + " attacks " + QTNAME(victim) + ".\n", ({ victim }),
            this_object());

        victim->catch_tell(this_object()->query_The_name(victim) 
            + " attacks you!\n");

        this_object()->attack_object(victim);
    }
}

void
target_check()
{
    if (objectp(query_attack())) return;
    notify_lost_target(0);
}

void 
enter_env(object to, object from)
{
    ::enter_env(to, from);
    set_alarm(0.1, 0.0, attack_focus_target);

    if (target_check_alarm == -1) 
    {
        target_check_alarm = set_alarm(30.0, 30.0, target_check);
    }
}

void
set_restrain_path(string path) 
{
    restrain_path = path;
}

string
query_restrain_path()
{
    return restrain_path;
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);    

    if (removal_alarm != -1) 
    {
        remove_alarm(removal_alarm);
        removal_alarm = -1;
    }
}

void
attack_object(object target)
{
    ::attack_object(target);

    if (removal_alarm != -1) 
    {
        remove_alarm(removal_alarm);
        removal_alarm = -1;
    }

    if (objectp(last_target)) 
    {
        last_target->remove_following_spider(this_object());
    }

    setuid();
    seteuid(getuid());
    MIRKWOOD_SPIDER_FOLLOW_SHADOW->add_follow_shadow(this_object(), target);
    last_target = target;
}

void
set_home(object home) 
{
    spider_home = home;
}

object
query_home()
{
    return spider_home;
}

private void
remove_spider()
{
    if (objectp(query_attack())) return;
    tell_room(environment(this_object()), QCTNAME(this_object()) + " crawls away.\n");
    remove_object();
}

private void
find_and_attack_next_target_in_environment()
{
    object *targets = FILTER_IS_MORTAL(filter(all_inventory(environment(this_object())),
        interactive));

    if (!sizeof(targets))
    {
        if (removal_alarm == -1) 
        {
            removal_alarm = set_alarm(20.0, 0.0, remove_spider);
        }
        return;
    }

    object new_target = targets[random(sizeof(targets))];
    attack_object(new_target);
}

void
notify_lost_target(object target)
{
    if (objectp(spider_home) && (environment(this_object()) != spider_home)) {
        tell_room(environment(this_object()), 
            QCTNAME(this_object()) + " crawls off.\n");

        move_living("M", spider_home);

        tell_room(spider_home, QCTNAME(this_object()) 
            + " crawls in to defend " + this_object()->query_possessive()
            + " nest.\n");
    }

    find_and_attack_next_target_in_environment();
}

void
set_origin_nest(object nest)
{
    origin_nest = nest;
}

object
query_origin_nest()
{
    return origin_nest;
}

void
do_die(object killer) 
{
    if (objectp(origin_nest)) origin_nest->report_death(this_object());
    ::do_die(killer);
}