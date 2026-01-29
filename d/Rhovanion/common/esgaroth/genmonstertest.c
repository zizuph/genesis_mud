/* This is the default orc in the Cirith Ungol.  This orc will also patrol in
 * Torech Ungol from time to time.  It is a very nice orc, for everything
 * in this orc is adjustable with only one patch.  His armour and weapons are
 * dependant on his average stats and his skills will also be dependant on
 * his stats.  The orc has several attack cries, which he obviously not waists
 * on wizards.  With a slight chance he will get a key to the tower at 
 * Cirith Ungol and you can also give him a whip.
 *
 * I spent some time time coding this sucker and even more on debugging and
 * enhancing it.  If you want to copy this orc and adjust it for your own
 * purposes, I do not mind you doing so IF you leave this header in tact.
 * You can add your own header AFTER this one.
 *
 * /Mercade 27 September 1993
 *
 * Revision history:
 */

/* See my help file in ~quetzl/open/monsterhelp */

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define NEO_FO_LSIT(x) x[random(sizeof(x))]
#ifndef MED_MONST
#define MED_MONST 50
#endif
#ifndef HIGH_MONST
#define HIGH_MONST 80
#endif
#ifndef SUP_MONST
#define SUP_MONST 120
#endif

static int do_i_matter,
           base,
           doing_random,
           will_help,
           victory_shout,
           num_of_picks;

static object *objects_on_list,
              current_object;

static string *gather_how,
              *help_how;

static mixed *pick_list;
              
void create_monster()
{
}

void set_base(int arg1, int arg2)
{
    base = arg1 + random(arg2);

    set_base_stat(SS_STR, ((base * 3 / 4) + random(base / 2)));
    set_base_stat(SS_DEX, ((base * 3 / 4) + random(base / 2)));
    set_base_stat(SS_CON, ((base * 3 / 4) + random(base / 2)));
    set_base_stat(SS_INT, ((base * 3 / 4) + random(base / 3)));
    set_base_stat(SS_WIS, ((base * 3 / 4) + random(base / 3)));
    set_base_stat(SS_DIS, ((base * 4 / 5) + random(base / 2)));
}

void begin_monster(int base, int rand)
{
    set_base(base, rand);
    objects_on_list = (({ }));
    current_object = this_object();
    gather_how = (({ }));
    pick_list = (({ }));
    help_how = (({ }));
}

object query_current_object()
{
    return current_object;
}

void begin_random_list(int howmany)
{
    doing_random = 1;
    num_of_picks = howmany;
}

void begin_object(string file, int chance)
{
    object ob;
    reset_euid();
    ob = clone_object(file);

    do_i_matter = ((chance - random(100)) > 0) ? 1 : 0;

    current_object = ob;
}

void end_object()
{
    if (!do_i_matter)
        return;

    if(doing_random)
        objects_on_list += (({ current_object }));
    else
        current_object->move(this_object());

    return;
}

void end_random_list()
{
    int i;

    for (i=0; i<num_of_picks; i++)
        NEO_FO_LSIT(objects_on_list)->move(this_object());

    doing_random = 0;
    objects_on_list = (({ }));
    return;
}

void slide_pen()
{
    if (base > SUP_MONST)
        current_object->set_pen((current_object->query_pen()) * 2);
    else if (base > HIGH_MONST)
        current_object->set_pen((current_object->query_pen()) * 3 / 2);
    else if (base > MED_MONST)
        current_object->set_pen((current_object->query_pen()) * 1);
    else
        current_object->set_pen((current_object->query_pen()) * 6 / 10);
}

void slide_hit()
{
    if (base > SUP_MONST)
        current_object->set_hit((current_object->query_hit()) * 2);
    else if (base > HIGH_MONST)
        current_object->set_hit((current_object->query_hit()) * 3 / 2);
    else if (base > MED_MONST)
        current_object->set_hit((current_object->query_hit()) * 1);
    else
        current_object->set_hit((current_object->query_hit()) * 6 / 10);
}

void slide_ac()
{
    if (base > SUP_MONST)
        current_object->set_ac((current_object->query_ac()) * 2);
    else if (base > HIGH_MONST)
        current_object->set_ac((current_object->query_ac()) * 3 / 2);
    else if (base > MED_MONST)
        current_object->set_ac((current_object->query_ac()) * 1);
    else
        current_object->set_ac((current_object->query_ac()) * 6 / 10);
}

void slide_skill(int skil)
{
    set_skill(skil, MIN(100, ((base * 3 / 4) + random (base / 2))));
}

void slide_alignment(int arg)
{
    set_alignment(arg * base);
}

void cash_flow(int types)
{
    object cash;
    reset_euid();

    if (types & 1)
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("copper");
        cash->set_heap_size(random(base));
        cash->move(this_object());
    }

    if ((types & 2) && (base >= MED_MONST))
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("silver");
        cash->set_heap_size(random(base / 2));
        cash->move(this_object());
    }

    if ((types & 4) && (base >= HIGH_MONST))
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("gold");
        cash->set_heap_size(random(base / 4));
        cash->move(this_object());
    }

    if ((types & 8) && (base >= SUP_MONST))
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("platinum");
        cash->set_heap_size(random(base / 8));
        cash->move(this_object());
    }
}

void i_help_out()
{
    will_help = 1;
}

void help_friend(object ob, object me)
{
    int i;

    if (ob && !(me->query_attack()) && present(ob, environment(me)))
    {
        for (i=0; i<sizeof(help_how); i++)
            me->command(help_how[i]);
        me->command("kill " + ob->query_real_name());
    }
}

void notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    set_alarm("help_friend", 5, 0, attacker, this_object());
}

void attacked_by(object ob)
{
    object *arr;
    int i;

    if (!will_help)
        return;

    ::attacked_by(ob);
    arr = (object *)query_team_others();
    for (i=0; i<sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

void love_my_friends(string *arg)
{
    help_how = arg;
}

void love_my_loot(string *arg)
{
    gather_how = arg;
}

void my_pick_list(mixed *arg)
{
    pick_list = arg;
}

mixed opinion()
{
    return NEO_FO_LSIT(pick_list);
}

void react_kill(string who)
{
    int i;

    if (victory_shout)
        command("shout I killed " + who);

    for (i=0; i<sizeof(gather_how); i++)
        command(gather_how[i]);

    command("get all from corpse");
}

void i_gather_loot()
{
    trig_new("'You' 'killed' %s", "react_kill");
}

void i_gloat()
{
    victory_shout = 1;
}

void return_introduction(object me)
{
    me->command("introduce myself");
}

void react_intro()
{
    set_alarm("return_introduction", 5, 0, this_object());
}

void im_friendly()
{
    trig_new("%l 'introduces' %s", "react_intro");
}

void end_monster()
{
    command("wear all");
    command("wield all");
}
