#pragma save_binary

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define NEOQ_QFO_LSIT(x) x[random(sizeof(x))]

static int do_i_matter,
           med_lvl = 50,
           high_lvl = 80,
           sup_lvl = 120,
           base,
           doing_random = 0,
           will_help = 0,
           num_of_picks = 0;

static mixed *objects_on_list = ({ }),
              current_object = this_object();

static mixed *pick_list = ({ });

/* Function name: set_up_lvls
 * Description:   set what should be considered low, medium, high and 
 *                superior for this particular monster, normally
 *                you should leave this at default.
 * Arguments:     level: array of the form: ({ med_lvl, high_lvl, sup_lvl })
 * Returns:       void
 */

public nomask void
set_sup_lvl(int *level)
{
    sup_lvl = level[2];
    high_lvl = level[1];
    med_lvl = level[0];
}

/* Function name: set_base
 * Description:   initialize the monsters stats and level
 * Arguments:     base_lev: base level
 *                ran_lev:  random addition to base level
 * Returns:       void
 */

public void 
set_base(int base_lev, int ran_lev)
{
    base = base_lev + random(ran_lev);
    if (base < 1)
        base = 1;

    set_base_stat(SS_STR, ((base * 3 / 4) + random(base / 2)));
    set_base_stat(SS_DEX, ((base * 3 / 4) + random(base / 2)));
    set_base_stat(SS_CON, ((base * 3 / 4) + random(base / 2)));
    set_base_stat(SS_INT, ((base * 3 / 4) + random(base / 3)));
    set_base_stat(SS_WIS, ((base * 3 / 4) + random(base / 3)));
    set_base_stat(SS_DIS, ((base * 4 / 5) + random(base / 2)));
    refresh_mobile();
}

/* Function name: begin_monster
 * Description:   Calls set_base
 * Arguments:     base_lev: base level of the monster
 *                ran_lev:  random level of the monster
 * Returns:       void
 */

public nomask void
begin_monster(int base_lev, int ran_lev)
{
    set_base(base_lev, ran_lev);
}

/* Function name: query_current_object
 * Description:   see Returns
 * Arguments:     none
 * Returns:       The last object declared with begin_object, or 0 if
 *                the object does not exist.
 */

public nomask mixed
query_current_object()
{
    if (current_object != this_object())
        return current_object;
    return 0;
}

/* Function name: begin_random_list
 * Description:   tells the monster that this is a new random list
 * Arguments:     howmany: howmany items should be picked from this list
 *                         when end_random_list is called
 * Returns:       void
 */

public void
begin_random_list(int howmany)
{
    doing_random = 1;
    num_of_picks = howmany;
}

/* Function name: begin_object
 * Description:   begin a new object, essential when using slide_pen,
 *                slide_ac, slide_hit, query_current_object, and random_list
 * Arguments:     file: the file name or master object of the object to be
 *                    begun
 *                chance: % chance that the object will actually be created
 * Returns:       0 if object could not be cloned for some reason
 */
 
public void
begin_object(mixed file, int chance)
{
    object ob;
    setuid();
    seteuid(getuid());

    do_i_matter = ((chance - random(100)) > 0) ? 1 : 0;

        ob = clone_object(file);

    current_object = ob;
}

/* Function name: end_object
 * Description:   if the object exists, then move it somewhere.  If a 
 *                random list is being assembled, move it there, otherwise,
 *                move it to this_object()
 * Arguments:     none
 * Returns:       1 if added, 0 if not

public int
end_object()
{
    if (!do_i_matter)
    {
        current_object = this_object();
        return 0;
    }

    if(doing_random)
        objects_on_list += (({ current_object }));
    else
        current_object->move(this_object());

    current_object = this_object();

    return 1;
}

/* Function name: end_random_list
 * Description:   ends a random list and attempts to move the number of
 *                objects specified int begin_random_list into this_object().
 *                Will not duplicate objects, unless they are on the list
 *                more than once.
 * Arguments:     none
 * Returns:       1 if succesful, 0 if there were not enough items to move
 */

public int
end_random_list()
{
    int i;
    object ob;

    for (i=0; i<num_of_picks; i++)
    {   
        if (objects_on_list == ({ }))
            return 0;
        ob = NEOQ_QFO_LSIT(objects_on_list);
        ob->move(this_object());
        objects_on_list = exclude_array(objects_on_list, i, i);
    }

    doing_random = 0;
    objects_on_list = (({ }));
    return 1;
}

/* Function name: slide_pen
 * Description:   alter the pen of a weapon based on the base value of the
 *                monster(this_object()).  If recoverable, a special weapon
 *                file must be used, since pen does not normally recover.
 *                There should be a file in this directory for that use.
 * Arguments:     pen_limit:  The maximum pen should reach by sliding.
 *                set to 40 unless explicitly set otherwise.
 * Returns:       the new pen value, for informational purposes only, the
 *                pen of current_object will be set, so you can normally
 *                discard this value. 0 if not a weapon. 1 if it will not
 *                be added to the list anyway.
 */

public int 
slide_pen(int pen_limit = 40)
{   
    int pen;

    if (!do_i_matter)
        return 1;

    if (member_array("/std/weapon.c", inherit_list(current_object)) == -1)
        return 0;

    if (base > sup_lvl)
        pen = ((current_object->query_pen()) * 2);
    else if (base > high_lvl)
        pen = ((current_object->query_pen()) * 3 / 2);
    else if (base > med_lvl)
        pen = ((current_object->query_pen()) * 1);
    else
        pen = ((current_object->query_pen()) * 6 / 10);

    pen = MIN(pen, pen_limit);

    current_object->set_pen(pen);

    return pen;
}

/* Function name: slide_hit
 * Description:   same as slide_pen above, except for weapon hit value
 * Arguments:     hit_limit: maximum hit value that should be obtained.
 *                default is 40
 * Returns:       0 if not weapon, 1 if object will not be added, otherwise
 *                new hit value.
 */

public int
slide_hit(int hit_limit = 40)
{
    int hit;

    if (!do_i_matter)
        return 1;
    
    if (member_array("/std/weapon.c", inherit_list(current_object)) == -1)
        return 0;

    if (base > sup_lvl)
        hit = ((current_object->query_hit()) * 2);
    else if (base > high_lvl)
        hit = ((current_object->query_hit()) * 3 / 2);
    else if (base > med_lvl)
        hit = ((current_object->query_hit()) * 1);
    else
        hit = ((current_object->query_hit()) * 6 / 10);

    hit = MIN(hit, hit_limit);

    current_object->set_hit(hit);

    return hit;
}

/* Function name: slide_ac
 * Description:   as slide_pen and slide_hit, but applies to an armours ac
 * Arguments:     ac_limit: maximum ac the armour should have.  Default is 40
 * Returns:       0 if not armour, 1 if will not be added to object, ac
 *                otherwise
 */

public int
slide_ac(int ac_limit = 40)
{
    int ac;

    if (!do_i_matter)
        return 1;

    if (member_array("/std/armour.c", inherit_list(current_object)) == -1)
        return 0;

    if (base > sup_lvl)
        ac = ((current_object->query_ac()) * 2);
    else if (base > high_lvl)
        ac = ((current_object->query_ac()) * 3 / 2);
    else if (base > med_lvl)
        ac = ((current_object->query_ac()) * 1);
    else
        ac = ((current_object->query_ac()) * 6 / 10);

    ac = MIN(ac, ac_limit);

    current_object->set_ac(ac);

    return ac;
}

/* Function name: slide_skill
 * Description:   set a skill to a value based on the base level of the
 *                monster.  Default is base * 3/4 + random(base/2)
 *                only sn needs to be set for this to work.
 * Arguments:     sn: skill number of the skill to be set
 *                sn_limit: max limit of the skill.  Default is 100
 *                tbval: numerator of the value by which base is mulitplied
 *                bbval: denominator of the value by which base is multiplied
 *                trval: numerator of random part of level calculation
 *                brval: denominator of the random part of level calculation
 * Returns:       level set to.
 */

public varargs int
slide_skill(int sn, int sn_limit = 100, int tbval = 3, int bbval = 4,
            int trval = 1, int brval = 2)
{
    int skill;

    skill = MIN(sn_limit, ((base * tbval / bbval) + 
        random (base * trval / brval)));

    set_skill(sn, skill);

    return skill;
}

/* Function name: slide_alignment
 * Description:   set the alignment based on the base stats of the 
 *                monster.
 * Arguments:     tval: numerator to multiply base by.  If negative, monster
 *                   will be evil
 *                bval: denominator to multiply base by.  default is 1
 * Returns:       the new alignment
 */

public int
slide_alignment(int tval, int bval = 1)
{
    int alignment;

    alignment = (base * tval / bval);

    set_alignment(alignment);

    return alignment;
}

/* Function name: set_cash_flow
 * Description:   sets the types of coins the monster could possibly carry
 * Arguments:     types: binary sum of types: 1 = copper, 2 = silver,
 *                    4 = gold, 8 = platinum.
 * Returns:       void
 */

public void
set_cash_flow(int types)
{
    object cash;

    setuid();
    seteuid(getuid());

    if (types & 1)
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("copper");
        cash->set_heap_size(random(base));
        cash->move(this_object());
    }

    if ((types & 2) && (base >= med_lvl))
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("silver");
        cash->set_heap_size(random(base / 2));
        cash->move(this_object());
    }

    if ((types & 4) && (base >= high_lvl))
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("gold");
        cash->set_heap_size(random(base / 4));
        cash->move(this_object());
    }

    if ((types & 8) && (base >= sup_lvl))
    {
        cash = clone_object("/std/coins");
        cash->set_coin_type("platinum");
        cash->set_heap_size(random(base / 8));
        cash->move(this_object());
    }
}

/* Function name: set_team_help
 * Description:   will this monster do something when his friends are attacked.
 *                What he does is determined by defining a function in your
 *                file named team_help_how which should receive as arguments
 *                two objects, first the attacker, then the monster
 * Arguments:     yes: 1 if he will help, 0 if he won't
 * Returns:       void
 */

public void 
set_team_help(int yes)
{
    will_help = yes;
}

/* Function name: team_help_how
 * Description:   define this to say how you want your monster to react when
 *                someone is picking on his friend.
 * Arguments:     attacker: who attacked us
 *                me: this monster
 * Returns:       void
 */

public void
team_help_how(object attacker, object me)
{
    me->command("kill " + attacker->query_real_name());
}
 
/* Function name: help_out_my_friend
 * Description:   called when someone is attacked nearby, used essentially
 *                to call team_help_how
 * Arguments:     attacker: the object doing the attacking
 *                me: this monster
 * Returns:       void
 */

public nomask void 
help_out_my_friend(object attacker, object me)
{
    int i;

    if (attacker && !(me->query_attack()) && present(attacker, environment(me)))
        team_help_how(attacker, me);
}

/* Function name: notify_ob_attacked_me
 * Description:   called when somone is attacked, you don't need to call
 *                this function at all outside of attacked_by()
 * Arguments:     friend: who was attacked
 *                attacker: who did the attacking
 * Returns:       void
 */

public void 
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    set_alarm("help_friend", 5, 0, attacker, this_object());
}

/* Function name: attacked_by
 * Description:   called by the npc when someone attacks him
 * Agruments:     attacker: who did the attacking
 * Returns:       void
 */

public void 
attacked_by(object attacker)
{
    object *team;
    int i;

    if (!will_help)
        return;

    ::attacked_by(attacker);
    team = (object *)query_team_others();
    for (i=0; i<sizeof(team); i++)
        team[i]->notify_ob_attacked_me(this_object(), attacker);
}

/* Function name: pick_list_new
 * Description:   begin a new pick list, this can be used for many purposes,
 *                one of the most useful being a list of adjectives for 
 *                a description.
 * Arguments:     list: an array of any type
 * Returns:       void
 */

public void
pick_list_new(mixed *list)
{
    pick_list = list;
}

/* Function name: extract_pick
 * Description:   gets one of the elements of the array set with pick_list_new,
 *                and then deletes the element
 * Arguments:     none
 * Returns:       one of array pick_list_new defined or void if list is empty
 */

public nomask mixed 
extract_pick()
{
    mixed x;

    if (!sizeof(pick_list))
        return;
    x = NEOQ_QFO_LSIT(pick_list);

    pick_list -= ({ x });

    return x;
}

/* Function name: query_pick
 * Description:   as above, but does not remove pick from list
 * Arguments:     none
 * Returns:       element of array defined by pick_list_new
 */

public nomask mixed
query_pick()
{
    return NEOQ_QFO_LSIT(pick_list);
}

/*
 * Function name: react_to_kill_how
 * Description:   react to killing someone, define this if you want a 
 *                specialized reaction.  Standard is merely to get the loot
 * Arguments:     who: the string of who we killed
 * Returns:       void
 */

public void 
react_to_kill_how(string who)
{
    command("get all from corpse");
}

/* Function name: react_on_kill
 * Description:   whether or not the monster will react on kill, I'm
                  sure there is a better way to do this, anyone wanting
                  to fix it, feel free to do so, just test it before
                  changing this copy.
 * Arguments:     arg: 1 if yes, 0 if not
 * Returns:       void
 */

void
react_on_kill(int arg)
{
    if (arg)
        trig_new("'You' 'killed' %s", "react_kill");
    else
        trig_delete("'You' 'killed' %s");
}

/* Function name: return introduction
 * Description:   introduce myself
 * Arguments:     object to do so, almost always this_object()
 * Returns:       0
 */

void 
return_introduction(object me)
{
    me->command("introduce myself");
}

/* Function name: react_intro
 * Description:   pause for introduction
 * Arguments:     none
 * Returns:       void
 */

public void 
react_intro(object liv, string dummy)
{
    if (query_ip_number(liv))
        set_alarm("return_introduction", 5, 0, this_object());
}

/* Function name: set_polite
 * Description:   will this monster return an introduction from a pc
 * Arguments:     arg: 1 if yes, 0 if not
 * Returns:       void
 */

public void
set_polite(int arg)
{
    if (arg)
        trig_new("%l 'introduces' %s", "react_intro");
    else
        trig_delete("%l 'introduces' %s");
}

/* Function name: end_monster
 * Description:   arms the monster.
 * Arguments:     none
 * Returns:       void
 */

public void 
end_monster()
{
    command("wear all");
    command("wield all");
}